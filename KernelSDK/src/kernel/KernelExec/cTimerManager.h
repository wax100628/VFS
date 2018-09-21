// Copyright 2018 Grass Valley, A Belden Brand

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once
/*
**  
*/

// --- Headers ---------------------------------------------------------------------------

#include "cCmdConsoleHandler.h"
#pragma warning(push)
#pragma warning(disable: 4201)  // Ignore "nonstandard extension used : nameless struct/union"
#include <mmsystem.h>
#pragma warning(pop)

// --- Namespace -------------------------------------------------------------------------

using namespace std;
using namespace vfs;



// =======================================================================================
// === cTimerManager =====================================================================
// =======================================================================================

class cTimerManager : public iTimerManager, public iGuardCreator, public cRefCount
{
  public :

    QDEFINE_SINGLETON_IMPL(cTimerManager, L"{5042B43F-A604-46a3-8EC9-1E8D32E2A6A3} // cTimerManager", iTimerManager);

    // iTimerManager
    virtual cGuard::ConstPtr QAPI addOneSecondTimerCallback(const iOneSecondTimerCallback::Ptr & newCallback);
    virtual void QAPI waitNextSecondTick();

    // cTimerManager
    cTimerManager();
    ~cTimerManager();
    void serviceOneSecondTimerCallbacks();

  private :

    mutable cLock                 m_OneSecondTimerCallbacksThreadSafety;
    typedef list<iOneSecondTimerCallback::Ptr> OneSecondTimerCallbackList;
    OneSecondTimerCallbackList    m_OneSecondTimerCallbacks;
    iBasicThread::Ptr             m_OneSecondTimerKernelThread;
    cLogIndentGuard *             m_OneSecondTimerThreadTopLevelLogging;

    cPulse                        m_OneSecondPulse;
    unsigned int                  m_EventQueueServiceTimeoutMillisecs;
    MMRESULT                      m_OneSecondTimerId;
    UINT                          m_TimerRes;

    // iGuardCreator
    void QAPI onGuardDestroyed(iGuarded::Ptr Guarded);
};
