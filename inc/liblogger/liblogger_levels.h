/*
       Licensed to the Apache Software Foundation (ASF) under one
       or more contributor license agreements.  See the NOTICE file
       distributed with this work for additional information
       regarding copyright ownership.  The ASF licenses this file
       to you under the Apache License, Version 2.0 (the
       "License"); you may not use this file except in compliance
       with the License.  You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

       Unless required by applicable law or agreed to in writing,
       software distributed under the License is distributed on an
       "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
       KIND, either express or implied.  See the License for the
       specific language governing permissions and limitations
       under the License.
 */
#ifndef __EXP_LOGGER_CONFIG_H__
#define __EXP_LOGGER_CONFIG_H__

/** \defgroup GRP_LOG_LEVELS Log Levels
 * The following macros indicate the log levels
 * @{
 * */
/** The Trace log level */
#define LOG_LEVEL_TRACE	1
/** The Debug log level */
#define LOG_LEVEL_DEBUG 2
/** The Info log level */
#define LOG_LEVEL_INFO	3
/** The Warning log level */
#define LOG_LEVEL_WARN	4
/** The Error log level */
#define LOG_LEVEL_ERROR	5
/** The Fatal log level */
#define LOG_LEVEL_FATAL	6

/** The disable log level */
#define LOG_LEVEL_DISABLED 0xff

/** Indicates the log level */
typedef enum LogLevel
{
	Trace = LOG_LEVEL_TRACE,	/**< The trace log level */
	Debug = LOG_LEVEL_DEBUG,	/**< The debug log level */
	Info = LOG_LEVEL_INFO,		/**< The info log level */
	Warn = LOG_LEVEL_WARN,		/**< The warn log level */
	Error = LOG_LEVEL_ERROR,	/**< The error log level */
	Fatal = LOG_LEVEL_FATAL,	/**< The fatal log level */
	Disable = LOG_LEVEL_DISABLED	/**< the disabled log level */
}LogLevel;

/** @} */

#endif // __EXP_LOGGER_CONFIG_H__

