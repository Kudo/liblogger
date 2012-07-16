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
#ifndef __LIBLOGGER_CONFIG_H__
#define __LIBLOGGER_CONFIG_H__

/** Define this macro to prevent checking the variadic macro support of your compiler.
 * By defining this macro, you can also stop the filenames, function name, and the line no
 * from appearing in the logs.
 * */
//#define DISABLE_VARIADIC_CHECK

/** Define this macro to forcefully enable the varadic macro support. This can lead to compile time
 * errors if the compiler doesnot support variadic macros.*/
//#define ASSUME_VARIADIC_SUPPORT

/** Define this macro to prevent filenames from appearing in the logs. This is useful if the filenames are very long
 * and their presence is not desired in the logs.
 * */
//#define DISABLE_FILENAMES

#endif // __LIBLOGGER_CONFIG_H__
