/*
 * Copyright (C) 2010 The Android Open Source Project
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
 */

#include <sys/resource.h>

#include <cutils/sched_policy.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include "HeadsetService.h"

using namespace android;

int main(int, char**) {
/*
    signal(SIGPIPE, SIG_IGN);
    ProcessState::self()->setThreadPoolMaxThreadCount(4);

    // start the thread pool
    sp<ProcessState> ps(ProcessState::self());
    ps->startThreadPool();


    setpriority(PRIO_PROCESS, 0, PRIORITY_URGENT_DISPLAY);

    set_sched_policy(0, SP_FOREGROUND);

#ifdef ENABLE_CPUSETS
    // Put most SurfaceFlinger threads in the system-background cpuset
    // Keeps us from unnecessarily using big cores
    // Do this after the binder thread pool init
    set_cpuset_policy(0, SP_SYSTEM);
#endif
*/
    // publish surface flinger
    sp<IServiceManager> sm(defaultServiceManager());

    // publish HeadsetService
    sp<HeadsetService> headsetservice = new HeadsetService();
    sm->addService(String16(HeadsetService::SERVICE_NAME), headsetservice, false);

    return 0;
}
