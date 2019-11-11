/*
 *  Copyright (c) 2019 Sinric. All rights reserved.
 *  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)
 *
 *  This file is part of the Sinric Pro (https://github.com/sinricpro/)
 */

#ifndef _SINRICFANUS_H_
#define _SINRICFANUS_H_

#include "SinricProDevice.h"

class SinricProFanUS :  public SinricProDevice {
  public:
	  SinricProFanUS(const char* deviceId, unsigned long eventWaitTime=100);
    // callback
    typedef std::function<bool(const String, int&)> RangeValueCallback;
    void onRangeValue(RangeValueCallback cb) { rangeValueCallback = cb; }
    void onAdjustRangeValue(RangeValueCallback cb) { adjustRangeValueCallback = cb; }

    // event
    bool sendRangeValueEvent(int rangeValue, String cause = "PHYSICAL_INTERACTION");

    // handle
    bool handleRequest(const char* deviceId, const char* action, JsonObject &request_value, JsonObject &response_value) override;
  private:
    RangeValueCallback rangeValueCallback; 
    RangeValueCallback adjustRangeValueCallback;
};

SinricProFanUS::SinricProFanUS(const char* deviceId, unsigned long eventWaitTime) : SinricProDevice(deviceId, eventWaitTime),
  rangeValueCallback(nullptr) {}

bool SinricProFanUS::handleRequest(const char* deviceId, const char* action, JsonObject &request_value, JsonObject &response_value) {
  if (strcmp(deviceId, this->deviceId) != 0) return false;
  if (SinricProDevice::handleRequest(deviceId, action, request_value, response_value)) return true;

  bool success = false;
  String actionString = String(action);

  if (actionString == "setRangeValue" && rangeValueCallback) {
    int rangeValue = request_value["rangeValue"] | 0;
    success = rangeValueCallback(String(deviceId), rangeValue);
    response_value["rangeValue"] = rangeValue;
    return success;
  }

  if (actionString == "adjustRangeValue" && adjustRangeValueCallback) {
    int rangeValueDelta = request_value["rangeValueDelta"] | 0;
    success = adjustRangeValueCallback(String(deviceId), rangeValueDelta);
    response_value["rangeValue"] = rangeValueDelta;
    return success;
  }

  return success;
}

bool SinricProFanUS::sendRangeValueEvent(int rangeValue, String cause) {
  DynamicJsonDocument eventMessage = prepareEvent(deviceId, "setRangeValue", cause.c_str());
  JsonObject event_value = eventMessage["payload"]["value"];
  event_value["rangeValue"] = rangeValue;
  return sendEvent(eventMessage);
}

#endif

