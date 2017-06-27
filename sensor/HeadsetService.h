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

#ifndef ANDROID_HEADSET_SERVICE_H
#define ANDROID_HEADSET_SERVICE_H

#include <binder/IInterface.h>
#include <cutils/compiler.h>

namespace android {

/*
 * This class defines the Binder IPC interface for GPU-related queries and
 * control.
 */
class IHeadsetService : public IInterface {
public:
    DECLARE_META_INTERFACE(HeadsetService);
protected:
    enum {
        HEADSET_SVR_SETUP = 0x8001,
        HEADSET_SVR_RELEASE ,
        HEADSET_GET_QUAT ,
    };
    typedef struct HeadsetDataPackage{
        float x;
        float y;
        float z;
        float w;
    } HeadsetDataPackage_T;
};

class BnHeadsetService: public BnInterface<IHeadsetService> {
protected:
    virtual status_t onTransact(uint32_t code, const Parcel& data,
            Parcel* reply, uint32_t flags = 0) override;
    virtual bool headsetSvrInit() =0;
    virtual bool headsetSvrRelease() =0;
    virtual bool headsetGetQuat(HeadsetDataPackage_T*) =0;
};

class HeadsetService : public BnHeadsetService
{
public:
    static const char* const SERVICE_NAME ANDROID_API;

    HeadsetService() ANDROID_API;

    virtual bool headsetSvrInit() override;
    virtual bool headsetSvrRelease() override;
    virtual bool headsetGetQuat(HeadsetDataPackage_T*) override;
};

} // namespace android

#endif // ANDROID_GPUSERVICE_H
