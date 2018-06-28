// ----------------------------------------------------------------------------
// Copyright 2016-2017 ARM Ltd.
//
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------------------------------------------------------

#include "ns_event_loop.h"

//#include "pal.h"
//#include "ns_trace.h"

#include "eventOS_scheduler.h"

#include <assert.h>

#include <mutex.h>
#include <sema.h>
#include <thread.h>
#include <kernel_types.h>



static void *event_loop_thread(void *arg);

char thread_stack[THREAD_STACKSIZE_DEFAULT];

static kernel_pid_t event_thread_id ;


//static palMutexID_t event_mutex_id = 0;
static mutex_t event_mutex_id;

//static palSemaphoreID_t event_start_sema_id = 0;
static sema_t event_start_sema_id;

//static palSemaphoreID_t event_signal_sema_id = 0;
static sema_t event_signal_sema_id;

//static palSemaphoreID_t event_stop_sema_id = 0;
static sema_t event_stop_sema_id;

static volatile bool event_stop_loop;

void eventOS_scheduler_mutex_wait(void)
{
    mutex_lock(&event_mutex_id);
}

void eventOS_scheduler_mutex_release(void)
{
    mutex_unlock(&event_mutex_id);
}

void eventOS_scheduler_signal(void)
{

    //status = pal_osSemaphoreRelease(event_signal_sema_id);
	sema_post(&event_signal_sema_id);
}

void eventOS_scheduler_idle(void)
{
    //int32_t counters = 0;

    eventOS_scheduler_mutex_release();

    //status = pal_osSemaphoreWait(event_signal_sema_id, UINT32_MAX, &counters);
    sema_wait(&event_signal_sema_id);

    eventOS_scheduler_mutex_wait();
}

static void *event_loop_thread(void *arg)
{

    event_stop_loop = false;

    sema_wait(&event_start_sema_id);


    // TODO: Delete start semaphore?
    eventOS_scheduler_mutex_wait();

    // A stoppable version of eventOS_scheduler_run(void)
    while (event_stop_loop == false) {
        if (!eventOS_scheduler_dispatch_event()) {
            eventOS_scheduler_idle();
        }
    }


    // cleanup the scheduler timer resources which are not needed anymore
    eventOS_scheduler_timer_stop();

    // signal the ns_event_loop_thread_stop() that it can continue 
    sema_post(&event_stop_sema_id);

    void* p;

    return p;
}

void ns_event_loop_thread_create(void)
{

    sema_create(&event_start_sema_id,1);


    sema_wait(&event_start_sema_id);


    sema_create(&event_stop_sema_id,0);


    sema_create(&event_signal_sema_id,1);


    mutex_init(&event_mutex_id);

    //thread_task_func_t
    //pal_osThreadCreateWithAlloc(event_loop_thread, NULL, PAL_osPriorityNormal, MBED_CONF_NS_HAL_PAL_EVENT_LOOP_THREAD_STACK_SIZE, NULL, &event_thread_id);
    event_thread_id = thread_create(thread_stack,sizeof(thread_stack),3,THREAD_CREATE_STACKTEST,event_loop_thread,NULL,"M2M_Evtq");
}

void ns_event_loop_thread_start(void)
{
    sema_post(&event_start_sema_id);
}

void ns_event_loop_thread_stop(void)
{

    // request loop to stop
    event_stop_loop = true;

    // Ping the even loop at least once more so it will notice the flag and
    // hopefully end the loop soon.
    eventOS_scheduler_signal();

    // wait until the event loop has been stopped and the thread is shutting down.
    // Note: the PAL API does not have any better means to join with a thread termination. 
    sema_wait(&event_stop_sema_id);

    sema_destroy(&event_start_sema_id);
    sema_destroy(&event_stop_sema_id);
}
