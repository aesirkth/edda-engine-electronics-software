#ifndef CANTimeSync_H
#define CANTimeSync_H

#include <stdint.h>
#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "codegen.h"
#include "timeSync.h"

class EddaCANTimeSync {
  private:
    uint8_t requestId_tx;
    uint8_t requestId_rx;
    uint8_t latencyResponseId_tx;
    uint8_t latencyResponseId_rx;
    uint8_t timeResponseId_tx;
    uint8_t timeResponseId_rx;

    uint8_t lastSource;
    uint8_t lastRequest;

    uint32_t currentRoundTripTime;

    void sendLatencyResponse(int write(const CAN_message_t &msg));
    void sendTimeResponse(int write(const CAN_message_t &msg));

  public:
    EddaCANTimeSync(
      uint8_t requestId_tx,
      uint8_t requestId_rx,
      uint8_t latencyResponseId_tx,
      uint8_t latencyResponseId_rx,
      uint8_t timeResponseId_tx,
      uint8_t timeResponseId_rx
    );

    bool processFrame(uint64_t *remoteTime, const TimeSync &timeSync, const CAN_message_t &msg, int write(const CAN_message_t &msg));

    void sendRequest(int write(const CAN_message_t &msg));

    int getRTT();
};

#endif