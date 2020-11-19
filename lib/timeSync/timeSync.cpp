#include "timesync.h"
#include "printNonNativeTypes.h"

// #define TIME_SYNC_DEBUG_MESSAGES

int64_t diffUint64(uint64_t a, uint64_t b) {
  if(a > b) {
    return (int64_t)( a - b );
  }
  return -(int64_t)( b - a );
}

void TimeSync::updateRemoteTime(uint64_t _remoteTime) {
  noInterrupts();
  uint64_t actualTimeSinceUpdate = getActualTimeSinceUpdate();
  uint64_t correctedTimeSinceUpdate = getCorrectedTimeSinceUpdate();
  uint64_t predictedTime = timeReference + correctedTimeSinceUpdate;
  int64_t remoteTimeDelta = diffUint64(_remoteTime, remoteTime);

  uint64_t now = sixtyFourBitTime.getCurrentMicros();
  remoteTimeUpdateTime = now;
  remoteTime = _remoteTime;
  if(hasUpdated) {
    if(hasRatePrediction) {
      int64_t delta = diffUint64(predictedTime, _remoteTime);

      lastDelta = delta;

      bool nowWithinThreshold = -TIME_SYNC_SYNCED_THRESHOLD_MICROSECONDS <= delta && delta <= TIME_SYNC_SYNCED_THRESHOLD_MICROSECONDS;
      if(!withinThreshold && nowWithinThreshold) {
        withinThresholdSinceTime = now;
      }
      withinThreshold = nowWithinThreshold;

      bool nowWithinMillisecond = -1000 <= delta && delta <= 1000;
      if(!withinMillisecond && nowWithinMillisecond) {
        withinMillisecondSinceTime = now;
      }
      withinMillisecond = nowWithinMillisecond;

      double errorAdjustmentFactor = 1e-1 * (double)delta / (double) actualTimeSinceUpdate;
      double remoteScalingFactor = (double)remoteTimeDelta / (double) actualTimeSinceUpdate;

      double wantedScalingFactor = remoteScalingFactor - errorAdjustmentFactor;

      const double averagingRate = getStatus() == TimeSyncStatus::Synced ? 0.08 : 0.25;
      scalingRate = (1 - averagingRate) * scalingRate + averagingRate * wantedScalingFactor;

      if(scalingRate < 0.5) scalingRate = 0.5;
      if(scalingRate > 2.0) scalingRate = 2.0;

      #ifdef TIME_SYNC_DEBUG_MESSAGES
      Serial.println("");
      Serial.println("");
      Serial.print("remoteTime: "); printUint64(remoteTime); Serial.println("");
      Serial.print("predictedTime: "); printUint64(predictedTime); Serial.println("");
      Serial.print("timeReference: "); printUint64(timeReference); Serial.println("");
      Serial.print("correctedTimeSinceUpdate: "); printUint64(correctedTimeSinceUpdate); Serial.println("");
      Serial.print("actualTimeSinceUpdate: "); printUint64(actualTimeSinceUpdate); Serial.println("");
      Serial.print("delta: "); printInt64(delta); Serial.println("");
      Serial.print("remoteTimeDelta: "); printInt64(remoteTimeDelta); Serial.println("");
      Serial.print("errorAdjustmentFactor: "); Serial.print(errorAdjustmentFactor, 8); Serial.println("");
      Serial.print("remoteScalingFactor: "); Serial.print(remoteScalingFactor, 8); Serial.println("");
      Serial.print("wantedScalingFactor: "); Serial.print(wantedScalingFactor, 8); Serial.println("");
      Serial.print("scalingRate: "); Serial.print(scalingRate, 8); Serial.println("");
      Serial.println("");
      Serial.println("");
      #endif

      if((
        delta >= TIME_SYNC_JUMP_THRESHOLD_MILLISECONDS * 1000
      ) || (
        delta <= -TIME_SYNC_BEHIND_JUMP_THRESHOLD_MILLISECONDS * 1000
      )){
        #ifdef TIME_SYNC_DEBUG_MESSAGES
        Serial.println("<- jumping forward ->");
        #endif
        timeReference = _remoteTime;
        scalingRate = 1.0;
        hasRatePrediction = false;
      } else {
        timeReference = timeReference + correctedTimeSinceUpdate;
      }
    } else {
      scalingRate = (double)remoteTimeDelta / (double) actualTimeSinceUpdate;
      if(scalingRate < 0.5) scalingRate = 0.5;
      if(scalingRate > 2.0) scalingRate = 2.0;
      hasRatePrediction = true;
      timeReference = _remoteTime;
      Serial.println("");
      Serial.println("");
      Serial.println("Setting scalingRate");
      Serial.print("remoteTimeDelta: "); printInt64(remoteTimeDelta); Serial.println("");
      Serial.print("actualTimeSinceUpdate: "); printUint64(actualTimeSinceUpdate); Serial.println("");
      Serial.print("timeReference: "); printUint64(timeReference); Serial.println("");
      Serial.print("scalingRate: "); Serial.print(scalingRate, 8); Serial.println("");
      Serial.println("");
      Serial.println("");
    }
  } else {
    timeReference = _remoteTime;
    hasUpdated = true;
    Serial.println("");
    Serial.println("");
    Serial.println("Setting reference");
    Serial.print("timeReference: "); printUint64(timeReference); Serial.println("");
    Serial.println("");
    Serial.println("");
  }
  interrupts();
}

uint64_t TimeSync::getActualTimeSinceUpdate() {
  if(!hasUpdated) {
    return 1;
  }

  uint64_t timeNow = sixtyFourBitTime.getCurrentMicros();

  if(remoteTimeUpdateTime < timeNow) {
    return 1 + (timeNow - remoteTimeUpdateTime);
  }

  return 1;
}
uint64_t TimeSync::getCorrectedTimeSinceUpdate() {
  if(!(hasUpdated && hasRatePrediction)) {
    return 0;
  }

  return (uint64_t)((double) getActualTimeSinceUpdate() * scalingRate);
}

uint64_t TimeSync::getLocalTime() {
  if(!(hasUpdated && hasRatePrediction)) {
    return 0;
  }

  return timeReference + getCorrectedTimeSinceUpdate();
}

TimeSyncStatus TimeSync::getStatus() {
  if(!(hasUpdated && hasRatePrediction)) {
    return TimeSyncStatus::PendingRemoteTime;
  }

  uint64_t now = sixtyFourBitTime.getCurrentMicros();

  int64_t timeWithinMillisecond = withinMillisecond ? ((int64_t) now - (int64_t) withinMillisecondSinceTime) : 0;
  int64_t timeWithinThreshold = withinThreshold ? ((int64_t) now - (int64_t) withinThresholdSinceTime) : 0;

  if(timeWithinThreshold >= TIME_SYNC_SYNCED_THRESHOLD_MIN_TIME_MILLISECONDS * 1000) {
    return TimeSyncStatus::Synced;
  }

  if(timeWithinMillisecond >= TIME_SYNC_SYNCED_THRESHOLD_MIN_TIME_MILLISECONDS * 1000) {
    return TimeSyncStatus::SyncedWithinMillisecond;
  }

  return TimeSyncStatus::AcquiringSync;
}

double TimeSync::getSeconds() {
  return (double)getMicroseconds() / (double)1e6;
}

uint64_t TimeSync::getMilliseconds() {
  return getMicroseconds() / 1000;
}

uint64_t TimeSync::getMicroseconds() {
  return getLocalTime();
}

int64_t TimeSync::getDeviation() {
  return lastDelta;
}


double TimeSync::getScalingRate() {
  return scalingRate;
}