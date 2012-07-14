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
#include "socket_logger_impl.h"
#include "tPLSocket.h"
#include "LLTimeUtil.h"
#include <win32_support.h>
#include <string.h>

/** The maximum size of the log. */
#define BUF_MAX 1024

/** Helper function to print the logs to a buffer and send to a socket or
 * other consumer */
static int sSendToSock(LogWriter *_this,const LogLevel logLevel,
#ifdef VARIADIC_MACROS
		const char* moduleName,
		const char* file,const char* funcName, const int lineNum, 
#endif
		const char* fmt,va_list ap);

int sSockFuncLogEntry(LogWriter *_this,const char* funcName);

int sSockFuncLogExit(LogWriter* _this,const char* funcName,const int lineNumber);

int sSockLoggerDeInit(LogWriter* _this);

/* helper function to get the log prefix */
static const char* sGetLogPrefix(const LogLevel logLevel);

typedef struct SockLogWriter
{
	LogWriter	base;
	tPLSocket	sock;
}SockLogWriter;

static SockLogWriter sSockLogWriter = 
{
	{
		/* .base.logLevel	= */Trace,
		/* .base.moduleName	= */{0},
		/* .base.log 		= */sSendToSock, 
		/* .base.logFuncEntry 	= */sSockFuncLogEntry,
		/* .base.logFuncExit	= */sSockFuncLogExit,
		/* .base.loggerDeInit 	= */sSockLoggerDeInit,	
	},
	/* .sock  = */0
};


int InitSocketLogger(LogWriter** logWriter,tSockLoggerInitParams *initParams)
{
	if(!logWriter || !initParams || !initParams->server)
	{
		fprintf(stderr,"Invalid args to function InitSocketLogger\n");
		return -1;
	}
	*logWriter = 0;

	if (sSockLogWriter.sock)
	{
		sSockLoggerDeInit((LogWriter*)&sSockLogWriter);
	}
	if( -1 == PLCreateConnectedSocket(initParams->server, initParams->port, &sSockLogWriter.sock) )
	{
		fprintf(stderr,"could not connect to log server %s:%d",initParams->server,initParams->port);
		return -1;
	}
	else
	{
		/* socket was opened successfully, emit the current date / time. */
		char curDateTime[32];	
		char tempBuf[128];
		if( !LLGetCurDateTime(curDateTime,sizeof(curDateTime)) )
		{
			int bytes = snprintf(tempBuf,sizeof(tempBuf),"\n----- Logging Started on %s -----\n",curDateTime);
			if( (bytes == -1) || (bytes > sizeof(tempBuf)) )
				bytes = sizeof(tempBuf);
			PLSockSend(sSockLogWriter.sock,tempBuf,bytes);
		}
	}

	/* Set log level */
	sSockLogWriter.base.logLevel = initParams->logLevel;

	/* Set log module name */
	if (initParams->moduleName)
	{
	    strncpy(sSockLogWriter.base.moduleName, initParams->moduleName, sizeof(sSockLogWriter.base.moduleName) - 1);
	    sSockLogWriter.base.moduleName[sizeof(sSockLogWriter.base.moduleName) - 1] = '\0';
	}

	*logWriter = (LogWriter*)&sSockLogWriter;
	return 0; // success!
}

/** Helper function to print the logs to a buffer and send to a socket or
 * other consumer */
static int sSendToSock(LogWriter *_this,const LogLevel logLevel,
#ifdef VARIADIC_MACROS
		const char* moduleName,
		const char* file,const char* funcName, const int lineNum, 
#endif
		const char* fmt,va_list ap)
{
	SockLogWriter *slw = (SockLogWriter*) _this;
	if(!_this || (-1 == slw->sock))
	{
		fprintf(stderr,"invalid args for sSendToSock");
		return -1;
	}
	else
	{
		char buf[BUF_MAX];
		char curDateTime[32];
		int bytes = 0;

		memset(curDateTime, 0, sizeof(curDateTime));
		LLGetCurDateTime(curDateTime, sizeof(curDateTime));
#ifdef VARIADIC_MACROS
		bytes = snprintf(buf,BUF_MAX-1,"\n[%s] %s %s::%s#%d:%s() - ", curDateTime, sGetLogPrefix(logLevel),
				moduleName,file,lineNum,funcName);
#else
		bytes = snprintf(buf,BUF_MAX-1,"\n[%s] %s - ", curDateTime, sGetLogPrefix(logLevel));
#endif
		// to be on safer side, check if required size is available.
		if(bytes < (BUF_MAX -1) )
			bytes += vsnprintf(buf+bytes,BUF_MAX-1-bytes,fmt,ap);
		buf[BUF_MAX-1] = 0;
		if((-1 == bytes ) || (bytes>BUF_MAX-1))
		{
			fprintf(stderr,"WARNING : socket log truncated, increase BUF_MAX\n");
			bytes = BUF_MAX-1;
		}
		return PLSockSend(slw->sock,buf,bytes);
	}
}

int sSockFuncLogEntry(LogWriter *_this,const char* funcName)
{

	SockLogWriter *slw = (SockLogWriter*) _this;
	if(!_this || (-1 == slw->sock))
	{
		fprintf(stderr,"invalid args for sSockFuncLogEntry");
		return -1;
	}
	else
	{
		char buf[BUF_MAX];
		int bytes;
#ifdef WIN32
		bytes = _snprintf(buf,BUF_MAX-1,"\n{ %s ", funcName);
#else
		bytes = snprintf(buf,BUF_MAX-1,"\n{ %s", funcName);
#endif
		buf[BUF_MAX-1] = 0;
		if((-1 == bytes ) || (bytes>BUF_MAX-1))
			bytes = BUF_MAX-1;
		return PLSockSend(slw->sock,buf,bytes);
	}
	
}

int sSockFuncLogExit(LogWriter* _this,const char* funcName,const int lineNumber)
{

	SockLogWriter *slw = (SockLogWriter*) _this;
	if(!_this || (-1 == slw->sock))
	{
		fprintf(stderr,"invalid args for sSockFuncLogExit");
		return -1;
	}
	else
	{
		char buf[BUF_MAX];
		int bytes;
#ifdef WIN32
		bytes = _snprintf(buf,BUF_MAX-1,"\n%s : %d }", funcName,lineNumber);
#else
		bytes = snprintf(buf,BUF_MAX-1,"\n%s : %d }", funcName,lineNumber);
#endif
		buf[BUF_MAX-1] = 0;
		if((-1 == bytes ) || (bytes>BUF_MAX-1))
			bytes = BUF_MAX-1;
		return PLSockSend(slw->sock,buf,bytes);
	}
}

int sSockLoggerDeInit(LogWriter* _this)
{
	SockLogWriter *slw = (SockLogWriter*) _this;
	if(slw)
	{
		PLDestroySocket(&slw->sock);
	}
	slw->base.logLevel = Trace;
	memset(&(slw->base.moduleName), 0, sizeof(slw->base.moduleName));
	return 0;
}

/* helper function to get the log prefix */
static const char* sGetLogPrefix(const LogLevel logLevel)
{
	switch (logLevel)
	{
		case Trace:	return "[T]";
		case Debug: return "[D]";
		case Info:	return "[I]";
		case Warn:	return "[W]";
		case Error:	return "[E]";
		case Fatal:	return "[F]";
		default:	return "";
	}
}
