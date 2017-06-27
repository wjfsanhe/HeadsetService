/*
 * Copyright 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Qiyi-framework
 */
#define ATRACE_TAG "HEADSET"

#include "HeadsetService.h"

#include <binder/Parcel.h>
#include <utils/String8.h>

namespace android {

// ----------------------------------------------------------------------------

class BpHeadsetService : public BpInterface<IHeadsetService>
{
public:
    BpHeadsetService(const sp<IBinder>& impl) : BpInterface<IHeadsetService>(impl) {}
    virtual int32_t headsetSvrInit()
    {   
        Parcel data,reply;
        data.writeInterfaceToken(IHeadsetService::getInterfaceDescriptor());
        remote()->transact(HEADSET_SVR_SETUP, data, &reply);
        return reply.readInt32();
    }
    virtual int32_t headsetSvrRelease()
    {
        Parcel data,reply;
        data.writeInterfaceToken(IHeadsetService::getInterfaceDescriptor());
        remote()->transact(HEADSET_SVR_RELEASE, data, &reply);
        return reply.readInt32();
    }
    virtual int32_t headsetGetQuat(HeadsetDataPackage_T* package)
    {
        Parcel data,reply;
        if (NULL == package) return -1;
        
        data.writeInterfaceToken(IHeadsetService::getInterfaceDescriptor());
        remote()->transact(HEADSET_GET_QUAT, data, &reply);
        package->x = reply.readFloat();
        package->y = reply.readFloat();
        package->z = reply.readFloat();
        package->w = reply.readFloat();
        ALOGD("got headset data:[%4f %4f %4f %4f]",package->x,
                                                    package->y,
                                                    package->z,
                                                    package->w);
        return 0;
    }
};

IMPLEMENT_META_INTERFACE(HeadsetService, "android.ui.IHeadsetService");

status_t BnHeadsetService::onTransact(uint32_t code, const Parcel& data,
        Parcel* reply, uint32_t flags)
{
    
    switch (code) {
    case HEADSET_SVR_SETUP:
    reply->writeInt32(headsetSvrInit());
    break;
    case HEADSET_SVR_RELEASE:
    reply->writeInt32(headsetSvrRelease());
    break;
    case HEADSET_GET_QUAT:
    HeadsetDataPackage_T package;
    headsetGetQuat(&package);
    reply->writeFloat(package.x);
    reply->writeFloat(package.y);
    reply->writeFloat(package.z);
    reply->writeFloat(package.w);
    break;
    default:
        return BBinder::onTransact(code, data, reply, flags);
    }
    return NO_ERROR;
}

// ----------------------------------------------------------------------------
const char* const HeadsetService::SERVICE_NAME = "Headset";

HeadsetService::HeadsetService() {}

bool HeadsetService::headsetSvrInit() {
    ALOGD("Headset svr init be called");
    return true;
}
bool HeadsetService::headsetSvrRelease() {
    ALOGD("Headset svr release be called");
    return true;
}
bool HeadsetService::headsetGetQuat(HeadsetDataPackage_T *data) {
    ALOGD("Headset svr get Quat be called");
    if(NULL == data ) return false;

    //for test case
    data->x = 0.5;    
    data->y = 0.5;    
    data->z = 0.5;
    
    return true;
}


// ----------------------------------------------------------------------------

} // namespace android
