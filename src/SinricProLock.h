/*
 *  Copyright (c) 2019 Sinric. All rights reserved.
 *  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)
 *
 *  This file is part of the Sinric Pro (https://github.com/sinricpro/)
 */

#ifndef _SINRICLOCK_H_
#define _SINRICLOCK_H_

#include "SinricProDevice.h"
#include "./Controller/LockController.h"

/**
 * @class SinricProLock
 * @brief Device to control a smart lock
 * 
 * Supporting 
 * * on / off
 * * lock / unlock
 **/
class SinricProLock :  public SinricProDevice,
                       public LockController {
  public:
	  SinricProLock(const DeviceId &deviceId);
    String getProductType() { return SinricProDevice::getProductType() + String("SMARTLOCK"); }

    bool handleRequest(const DeviceId &deviceId, const char* action, JsonObject &request_value, JsonObject &response_value) override;
};

SinricProLock::SinricProLock(const DeviceId &deviceId) : SinricProDevice(deviceId),
                                                         LockController(this) {}

bool SinricProLock::handleRequest(const DeviceId &deviceId, const char* action, JsonObject &request_value, JsonObject &response_value) {
  if (deviceId != this->deviceId) return false;
  bool success = false;

  if (!success) LockController::handleRequest(action, request_value, response_value);
  return success;
}

#endif

