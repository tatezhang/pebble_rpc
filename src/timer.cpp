/*
 * Tencent is pleased to support the open source community by making Pebble available.
 * Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.
 * Licensed under the MIT License (the "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT
 * Unless required by applicable law or agreed to in writing, software distributed under the License
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the License for the specific language governing permissions and limitations under
 * the License.
 *
 */

//#include <algorithm>
#include <string.h>

#include "time_utility.h"
#include "timer.h"


namespace pebble {


SequenceTimer::SequenceTimer() {
    m_timer_seqid   = 0;
    m_last_error[0] = 0;
}

SequenceTimer::~SequenceTimer() {
}

int64_t SequenceTimer::StartTimer(uint32_t timeout_ms, const TimeoutCallback& cb) {
    if (!cb || 0 == timeout_ms) {
        // _LOG_LAST_ERROR("param is invalid: timeout_ms = %u, cb = %d", timeout_ms, (cb ? true : false));
        return kTIMER_INVALID_PARAM;
    }

    cxx::shared_ptr<TimerItem> item(new TimerItem);
    item->stoped   = false;
    item->id       = m_timer_seqid;
    item->timeout  = TimeUtility::GetCurrentMS() + timeout_ms;
    item->cb       = cb;

    m_timers[timeout_ms].push_back(item);
    m_id_2_timer[m_timer_seqid] = item;

    return m_timer_seqid++;
}

int32_t SequenceTimer::StopTimer(int64_t timer_id) {
    cxx::unordered_map<int64_t, cxx::shared_ptr<TimerItem> >::iterator it =
        m_id_2_timer.find(timer_id);
    if (m_id_2_timer.end() == it) {
        // _LOG_LAST_ERROR("timer id %ld not exist", timer_id);
        return kTIMER_UNEXISTED;
    }

    it->second->stoped = true;
    m_id_2_timer.erase(it);

    return 0;
}

int32_t SequenceTimer::Update() {
    int32_t num = 0;
    int64_t now = TimeUtility::GetCurrentMS();
    int32_t ret = 0;
    uint32_t old_timeout = 0;
    uint32_t timer_map_size = m_timers.size();

    cxx::unordered_map<uint32_t, std::list<cxx::shared_ptr<TimerItem> > >::iterator mit =
        m_timers.begin();
    std::list<cxx::shared_ptr<TimerItem> >::iterator lit;
    while (mit != m_timers.end()) {
        /* 暂不考虑主动清理，顺序定时器即使不清理，也不会占用太多内存，频繁清理反而会影响性能 */

        std::list<cxx::shared_ptr<TimerItem> >& timer_list = mit->second;
        while (!timer_list.empty()) {
            lit = timer_list.begin();
            if ((*lit)->stoped) {
                timer_list.erase(lit);
                continue;
            }

            if ((*lit)->timeout > now) {
                /* 此队列后面的都未超时 */
                break;
            }

            old_timeout = mit->first;
            ret = (*lit)->cb();

            /* 返回 <0 删除定时器，=0 继续，>0按新的超时时间重启定时器 */
            if (ret < 0) {
                m_id_2_timer.erase((*lit)->id);
                timer_list.erase(lit);
            } else {
                cxx::shared_ptr<TimerItem> back_item = *lit;
                timer_list.erase(lit);
                if (ret > 0) {
                    back_item->timeout = now + ret;
                    m_timers[ret].push_back(back_item);
                } else {
                    back_item->timeout = now + old_timeout;
                    timer_list.push_back(back_item);
                }
            }

            ++num;
        }

        if (timer_map_size != m_timers.size()) {
            /* 暂时用此方法防止迭代器失效，m_timers目前实现只会增加不会减少 */
            break;
        }
        ++mit;
    }

    return num;
}

}  // namespace pebble

