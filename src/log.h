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


#ifndef _PEBBLE_LOG_H_
#define _PEBBLE_LOG_H_

#include "platform.h"

/// @brief 日志级别，各级别的基本原则为\n
///     TRACE : 单步调试\n
///     DEBUG : 调试信息、服务处理关键路径\n
///     INFO  : 统计、系统操作信息（如配置重载、控制命令）\n
///     ERROR : 逻辑错误，服务处理失败\n
///     FATAL : 系统错误，无法提供服务\n
namespace pebble {
typedef enum {
    LOG_PRIORITY_TRACE = 0,
    LOG_PRIORITY_DEBUG,
    LOG_PRIORITY_INFO,
    LOG_PRIORITY_ERROR,
    LOG_PRIORITY_FATAL,
} LOG_PRIORITY;
} // namespace pebble

// TODO: 需要用户适配自己的log
#define PLOG_FATAL(fmt, ...) printf("[(%s:%d)(%s)]" fmt "\n", __FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
#define PLOG_ERROR(fmt, ...) printf("[(%s:%d)(%s)]" fmt "\n", __FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
#define PLOG_INFO(fmt,  ...) printf("[(%s:%d)(%s)]" fmt "\n", __FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
#define PLOG_DEBUG(fmt, ...) printf("[(%s:%d)(%s)]" fmt "\n", __FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
#define PLOG_TRACE(fmt, ...) printf("[(%s:%d)(%s)]" fmt "\n", __FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)

// 条件日志
#define PLOG_IF_FATAL(condition, fmt, ...) if (condition) { PLOG_FATAL(fmt, ##__VA_ARGS__); }
#define PLOG_IF_ERROR(condition, fmt, ...) if (condition) { PLOG_ERROR(fmt, ##__VA_ARGS__); }
#define PLOG_IF_INFO(condition, fmt,  ...) if (condition) { PLOG_INFO(fmt,  ##__VA_ARGS__); }
#define PLOG_IF_DEBUG(condition, fmt, ...) if (condition) { PLOG_DEBUG(fmt, ##__VA_ARGS__); }
#define PLOG_IF_TRACE(condition, fmt, ...) if (condition) { PLOG_TRACE(fmt, ##__VA_ARGS__); }

// 记录日志并返回
#define RETURN_IF_FATAL(condition, ret, fmt, ...) if (condition) { PLOG_FATAL(fmt, ##__VA_ARGS__); return (ret); }
#define RETURN_IF_ERROR(condition, ret, fmt, ...) if (condition) { PLOG_ERROR(fmt, ##__VA_ARGS__); return (ret); }
#define RETURN_IF_INFO(condition, ret, fmt,  ...) if (condition) { PLOG_INFO(fmt,  ##__VA_ARGS__); return (ret); }
#define RETURN_IF_DEBUG(condition, ret, fmt, ...) if (condition) { PLOG_DEBUG(fmt, ##__VA_ARGS__); return (ret); }
#define RETURN_IF_TRACE(condition, ret, fmt, ...) if (condition) { PLOG_TRACE(fmt, ##__VA_ARGS__); return (ret); }

// 频率控制(client不做频率控制)
#define PLOG_FATAL_N_EVERY_SECOND(num, fmt, args...) PLOG_FATAL(fmt, ##args)
#define PLOG_ERROR_N_EVERY_SECOND(num, fmt, args...) PLOG_ERROR(fmt, ##args)
#define PLOG_INFO_N_EVERY_SECOND(num, fmt,  args...) PLOG_INFO(fmt, ##args)
#define PLOG_DEBUG_N_EVERY_SECOND(num, fmt, args...) PLOG_DEBUG(fmt, ##args)
#define PLOG_TRACE_N_EVERY_SECOND(num, fmt, args...) PLOG_TRACE(fmt, ##args)

#endif // _PEBBLE_LOG_H_

