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


#ifndef _PEBBLE_ERROR_H_
#define _PEBBLE_ERROR_H_

#include <stdio.h>
#include <string>

#include "platform.h"


/* @brief 格式化输出log信息到buff */
#define LOG_MESSAGE(buff, buff_len, fmt, ...) \
    snprintf((buff), (buff_len), "(%s:%d)(%s)" fmt, \
    __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)


/* @brief 记录最后错误信息，内部使用，要求buff名字为m_last_error */
#define _LOG_LAST_ERROR(fmt, ...) \
    LOG_MESSAGE((m_last_error), (sizeof(m_last_error)), fmt, ##__VA_ARGS__)

namespace pebble {

/* @brief 每个模块错误码BASE定义，模块错误码取值为XXX_BASE - N */
enum ERROR_CODE_BASE {
    // NO_ERROR                    = 0,
    RPC_ERROR_CODE_BASE         = -1000,
    TIMER_ERROR_CODE_BASE       = -6000,
    PROCESSOR_ERROR_CODE_BASE   = -10000
};

/* @brief 获取错误描述 */
const char* GetErrorString(int32_t error_code);

/* @brief 设置错误描述 */
void SetErrorString(int32_t error_code, const char* error_string);

} // namespace pebble

#endif // _PEBBLE_ERROR_H_