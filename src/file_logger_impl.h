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
#ifndef __FILE_LOGGER_IMPL_H__
#define __FILE_LOGGER_IMPL_H__

#include <liblogger/liblogger.h>
#include <liblogger/logger_object.h>
#include <liblogger/file_logger.h>

/** Factory Function to create the File Logger. 
 * \param [out] logWriter 	The log writer handle.
 * \param [in]	initParams	The log writer initialization parameters.
 * \returns 0 on success , -1 on failure.
 * */
int InitFileLogger(LogWriter** logWriter,tFileLoggerInitParams* initParams );

/** Factory Function to create the Console Logger. 
 * A console logger is a special case of file logging (where the file is stdout or stderr)
 * \param [out] logWriter 	The log writer handle.
 * \param [in]	initParams	The log writer initialization parameters.
 * \returns 0 on success , -1 on failure.
 * */
int InitConsoleLogger(LogWriter** logWriter,tConsoleLoggerInitParams* initParams);

#endif // __FILE_LOGGER_IMPL_H__
