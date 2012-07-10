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
#ifndef __FILE_LOGGER_H__
#define __FILE_LOGGER_H__

#include <stdio.h>

/* The rollback feature has been disabled, due to limitations 
 * in open modes of fopen(), will be enabled after further study.
 * */
#undef _ENABLE_LL_ROLLBACK_

/** File open mode.
 * */
typedef enum tFileOpenMode
{
	/** Indicates that the log file should be opened in append mode. */
	AppendMode = 0x2,
#ifdef _ENABLE_LL_ROLLBACK_
	/** Rollback Mode : The log file will be opened in append mode and will
	 * roll back when the size indicated 
	 * by \ref tFileLoggerInitParams::rollbackSize is reached.
	 * */
	RollbackMode
#endif // _ENABLE_LL_ROLLBACK_
} tFileOpenMode;

/** File Logger Initialization parameters. */
typedef struct tFileLoggerInitParams
{
	/** The filename of the log. */
	char* 			fileName;
	/** The file open mode. */
	tFileOpenMode 	fileOpenMode;
#ifdef _ENABLE_LL_ROLLBACK_
	/** The rollback size in \b bytes to use, when \ref tFileLoggerInitParams::fileOpenMode "fileOpenMode"
	 * is equal \ref tFileOpenMode::RollbackMode "RollbackMode"
	 * */
	unsigned long	rollbackSize;
#endif // _ENABLE_LL_ROLLBACK_
}tFileLoggerInitParams;

#endif // __FILE_LOGGER_H__
