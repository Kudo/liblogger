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
/**
 * \file Implementation of the Mutex Abstraction API for Win32 platform.
 * */
#include "tPLMutex.h"
#include <windows.h>
#include <stdio.h>

/** Create the mutex. */
int PLCreateMutex(tPLMutex* mutex)
{
	if(!mutex)
		return -1;
	else
	{
		HANDLE _mutex = CreateMutex( 
				NULL,              // default security attributes
				FALSE,             // initially not owned
				NULL);             // unnamed mutex
		if ( !_mutex)
		{
			fprintf(stderr,"Mutex creation failed.");
			return -1;
		}
		*mutex = _mutex;
		return 0; // success.
	}
}
/** Lock the mutex. */
int PLLockMutex(tPLMutex mutex)
{
	if(!mutex)
		return -1;
	if( WaitForSingleObject(mutex,INFINITE) != WAIT_OBJECT_0 )
	{
		// locking failed.
		return -1;
	}
	return 0;
	
}
/** Unlock the mutex. */
int PLUnLockMutex(tPLMutex mutex)
{
	if(!mutex)
		return -1;
	if( ReleaseMutex (mutex) == 0  )
	{
		//If the function succeeds, the return value is nonzero.
		// unlocking failed.
		return -1;
	}
	return 0;
}

/** Destroy the mutex. */
int PLDestroyMutex(tPLMutex* mutex)
{
	if( !mutex || !(*mutex) )
		return -1;
	if( CloseHandle( (HANDLE)*mutex ) != 0 )
	{
		// destroy failed.
		return -1;
	}
	*mutex = 0;
	return 0;

}
