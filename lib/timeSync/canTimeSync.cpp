#include "canTimeSync.h"


// #define CAN_TIME_SYNC_DEBUG_MSGS

EddaCANTimeSync::EddaCANTimeSync(
  uint8_t _requestId_tx,
  uint8_t _requestId_rx,
  uint8_t _latencyResponseId_tx,
  uint8_t _latencyResponseId_rx,
  uint8_t _timeResponseId_tx,
  uint8_t _timeResponseId_rx
) {
  requestId_tx = _requestId_tx;
  requestId_rx = _requestId_rx;
  latencyResponseId_tx = _latencyResponseId_tx;
  latencyResponseId_rx = _latencyResponseId_rx;
  timeResponseId_tx = _timeResponseId_tx;
  timeResponseId_rx = _timeResponseId_rx;

  lastSource = 0;
  lastRequest = 0;

  currentRoundTripTime = -1;
}

// Returns true when the remote time was updated
bool EddaCANTimeSync::processFrame(uint64_t *remoteTime, const TimeSync &timeSync, const CAN_message_t &msg, int write(const CAN_message_t &msg)) {
  if(msg.id == requestId_rx) {
    auto *syncRequest = (EddaCAN::TimeSyncRequest_DataType*) msg.buf;

    CAN_message_t latencyMsg;
    latencyMsg.id = latencyResponseId_tx;
    latencyMsg.len = 8;
    latencyMsg.seq = true;
    auto *latencyResponse = (EddaCAN::TimeSyncLatencyResponse_DataType*) latencyMsg.buf;
    latencyResponse->set_destination(syncRequest->get_source());
    latencyResponse->set_requestIdentifier(syncRequest->get_requestIdentifier());
    latencyResponse->set_initiatorMicros(syncRequest->get_currentMicros());


    CAN_message_t timeMsg;
    timeMsg.id = timeResponseId_tx;
    timeMsg.len = 8;
    timeMsg.seq = true;
    auto *timeResponse = (EddaCAN::TimeSyncTimeResponse_DataType*) timeMsg.buf;
    timeResponse->set_destination(syncRequest->get_source());
    timeResponse->set_requestIdentifier(syncRequest->get_requestIdentifier());

    uint64_t time = timeSync.getMicroseconds(); // Just a range of 48 bits now... Still like 10 years though.
    uint32_t bits0through31 = (uint32_t) time;
    uint16_t bits32through47 = (uint16_t) (time >> 32);
    timeResponse->set_bits0through31(bits0through31);
    timeResponse->set_bits32through47(bits32through47);

    write(latencyMsg);
    write(timeMsg);

    return false;
  }

  if(msg.id == latencyResponseId_rx) {
    auto *latencyResponse = (EddaCAN::TimeSyncLatencyResponse_DataType*) msg.buf;
    
    if(latencyResponse->get_destination() != lastSource) {
      #ifdef CAN_TIME_SYNC_DEBUG_MSGS
      Serial.println("");
      Serial.print("Skipping request with invalid source ");
      Serial.print(latencyResponse->get_destination());
      Serial.print(" - expected ");
      Serial.println(lastSource);
      #endif
      return false;
    }
    if(latencyResponse->get_requestIdentifier() != lastRequest) {
      #ifdef CAN_TIME_SYNC_DEBUG_MSGS
      Serial.println("");
      Serial.print("Skipping request with invalid id ");
      Serial.print(latencyResponse->get_requestIdentifier());
      Serial.print(" - expected ");
      Serial.println(lastRequest);
      #endif
      return false;
    }

    noInterrupts();

    uint32_t sentTime = latencyResponse->get_initiatorMicros();
    uint32_t nowTime = micros();

    if(nowTime > sentTime) {
      currentRoundTripTime = nowTime - sentTime;
    } else {
      currentRoundTripTime = 0;
    }

    interrupts();

    #ifdef CAN_TIME_SYNC_DEBUG_MSGS
    Serial.print("rtt: ");
    Serial.println(currentRoundTripTime);
    #endif

    return false;
  }

  if(msg.id == timeResponseId_rx) {
    auto *timeResponse = (EddaCAN::TimeSyncTimeResponse_DataType*) msg.buf;

    if(timeResponse->get_destination() != lastSource) {
      #ifdef CAN_TIME_SYNC_DEBUG_MSGS
      Serial.println("");
      Serial.print("Skipping request with invalid source ");
      Serial.print(timeResponse->get_destination());
      Serial.print(" - expected ");
      Serial.println(lastSource);
      #endif
      return false;
    }
    if(timeResponse->get_requestIdentifier() != lastRequest) {
      #ifdef CAN_TIME_SYNC_DEBUG_MSGS
      Serial.println("");
      Serial.print("Skipping request with invalid id ");
      Serial.print(timeResponse->get_requestIdentifier());
      Serial.print(" - expected ");
      Serial.println(lastRequest);
      #endif
      return false;
    }

    noInterrupts();
    uint64_t bits0through31 = (uint64_t) timeResponse->get_bits0through31();
    uint64_t bits32through47 = ((uint64_t) timeResponse->get_bits32through47()) << 32;

    uint64_t time = bits0through31 | bits32through47;
    /**
     * The reason for a whole RTT added below is this:
     * 
     * Edda: Write Time Sync Request (to queue)
     * <send Edda -> FC>
     * FC: Process Time Sync Request
     * FC: Write Latency Estimation Response (to queue)
     * FC: Write Current Time Response (to queue)
     * <send FC -> Edda>
     * Edda: Receive Latency Estimation
     * <send FC -> Edda>
     * Edda: Receive Current Time
     * 
     **/
    *remoteTime = time + currentRoundTripTime; // why add one whole RTT??
    interrupts();

    return true;
  }
  return false;
}

void EddaCANTimeSync::sendRequest(int write(const CAN_message_t &)) {
  CAN_message_t msg;
  msg.id = requestId_tx;
  msg.len = 8;
  msg.seq = true;

  auto *syncRequest = (EddaCAN::TimeSyncRequest_DataType*) msg.buf;
  syncRequest->set_source(lastSource);
  syncRequest->set_requestIdentifier(++lastRequest);
  syncRequest->set_currentMicros(micros());
  write(msg);
}

int EddaCANTimeSync::getRTT() {
  return (int)currentRoundTripTime;
}