#ifndef TimeSync_H
#define TimeSync_H

#include <stdint.h>
#include <Arduino.h>
#include "64bittime.h"

// The acceptable time latency in milliseconds before the time makes a jump to the current remote time,
// to avoid large scaling ratios
#define TIME_SYNC_JUMP_THRESHOLD_MILLISECONDS 1000

// The acceptable time latency in milliseconds before the time makes a jump to the current remote time,
// to avoid large scaling ratios
#define TIME_SYNC_BEHIND_JUMP_THRESHOLD_MILLISECONDS 50

// The threshold for how much the predicted time can differ from the remote time before considering it to be synced
#define TIME_SYNC_SYNCED_THRESHOLD_MICROSECONDS 250

// The amount of time that we must be within the above threshold to consider the time to be synced
#define TIME_SYNC_SYNCED_THRESHOLD_MIN_TIME_MILLISECONDS 10000

enum struct TimeSyncStatus {
  PendingRemoteTime,
  AcquiringSync,
  SyncedWithinMillisecond,
  Synced
};

class TimeSync {
  private:
    SixtyFourBitTime sixtyFourBitTime;
    uint64_t remoteTimeUpdateTime = 0;
    uint64_t remoteTime = 0;
    uint64_t timeReference = 0;
    int64_t lastDelta = 0;

    uint64_t withinThresholdSinceTime = 0;
    bool withinThreshold = false;

    uint64_t withinMillisecondSinceTime = 0;
    bool withinMillisecond = false;

    bool hasUpdated = false;
    bool hasRatePrediction = false;

    double scalingRate = 1.0;
    
    uint64_t getActualTimeSinceUpdate();
    uint64_t getCorrectedTimeSinceUpdate();
    
  public:
    void updateRemoteTime(uint64_t remoteTime);
    uint64_t getLocalTime();
    TimeSyncStatus getStatus();

    double getScalingRate();
    double getSeconds();
    uint64_t getMilliseconds();
    uint64_t getMicroseconds();
    
    int64_t getDeviation();
};


#endif