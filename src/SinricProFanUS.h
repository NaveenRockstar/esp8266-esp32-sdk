/*
 *  Copyright (c) 2019 Sinric. All rights reserved.
 *  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)
 *
 *  This file is part of the Sinric Pro (https://github.com/sinricpro/)
 */

#ifndef _SINRICFANUS_H_
#define _SINRICFANUS_H_

#include "SinricProDevice.h"
#include "./Controller/PowerStateController.h"
#include "./Controller/RangeController.h"

/**
 * @class SinricProFanUS
 * @brief Device to control a fan with on / off commands and its speed by a range value
 */
class SinricProFanUS :  public SinricProDevice,
                        public PowerStateController,
                        public RangeController {
  public:
	  SinricProFanUS(const DeviceId &deviceId);
    bool handleRequest(const DeviceId &deviceId, const char* action, JsonObject &request_value, JsonObject &response_value) override;
};

SinricProFanUS::SinricProFanUS(const DeviceId &deviceId) : SinricProDevice(deviceId, "FAN"),
                                                           PowerStateController(this),
                                                           RangeController(this) {}

bool SinricProFanUS::handleRequest(const DeviceId &deviceId, const char* action, JsonObject &request_value, JsonObject &response_value) {
  bool success = false;

  if (!success) success = PowerStateController::handleRequest(action, request_value, response_value);
  if (!success) success = RangeController::handleRequest(action, request_value, response_value);

  return success;
}


#endif

