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
#include "LLTimeUtil.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Returns the current date time as a string.
 * \param [out] str String where the date time is returned.
 * \param [in]	strLen The length of the arg \a str.
 * \returns 0 on success, -1 on failure.
 * */
int LLGetCurDateTime(char* str, int strLen)
{
	time_t t;
	struct tm *tmp;

	t = time(NULL);
	tmp = localtime(&t);
	if (tmp == NULL) {
		perror("localtime");
		return -1;
	}

	if (strftime(str, strLen, "%Y-%m-%d %H:%M:%S", tmp) == 0) {
		fprintf(stderr, "strftime returned 0");
		return -1;
	}
	return 0;

}
