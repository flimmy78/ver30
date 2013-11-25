/**********
This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version. (See <http://www.gnu.org/copyleft/lesser.html>.)

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
**********/
// Copyright (c) 1996-2010 Live Networks, Inc.  All rights reserved.
// Basic Usage Environment: for a simple, non-scripted, console application
// Implementation


#include "BasicUsageEnvironment.hh"
#include "HandlerSet.hh"
#include <stdio.h>
#if defined(_QNX4)
#include <sys/select.h>
#include <unix.h>
#endif

////////// BasicTaskScheduler //////////

BasicTaskScheduler* BasicTaskScheduler::createNew() {
	return new BasicTaskScheduler();
}

BasicTaskScheduler::BasicTaskScheduler()
	: fMaxNumSockets(0) {
  FD_ZERO(&fReadSet);
}

BasicTaskScheduler::~BasicTaskScheduler() {
}

#ifndef MILLION
#define MILLION 1000000
#endif

//struct timeval timeNow, timeNow2;
void BasicTaskScheduler::SingleStep(unsigned maxDelayTime) {
	int selectResult;
	HandlerDescriptor* handler;
	HandlerIterator iter(*fReadHandlers);
	fd_set readSet = fReadSet; // make a copy for this select() call

//	printf("env %p, fNoDelayFunc %p\n", this, fNoDelayFunc);
	if (fNoDelayFunc != NULL) {
		(*fNoDelayFunc)(fNoDelayClientData);
		return;
	}

	DelayInterval const& timeToDelay = fDelayQueue.timeToNextAlarm();
	struct timeval tv_timeToDelay;
	tv_timeToDelay.tv_sec = timeToDelay.seconds();
	tv_timeToDelay.tv_usec = timeToDelay.useconds();
	// Very large "tv_sec" values cause select() to fail.
	// Don't make it any larger than 1 million seconds (11.5 days)
	const long MAX_TV_SEC = MILLION;
	if (tv_timeToDelay.tv_sec > MAX_TV_SEC) {
		tv_timeToDelay.tv_sec = MAX_TV_SEC;
	}
	// Also check our "maxDelayTime" parameter (if it's > 0):
	if (maxDelayTime > 0 &&
		(tv_timeToDelay.tv_sec > (long)maxDelayTime/MILLION ||
		(tv_timeToDelay.tv_sec == (long)maxDelayTime/MILLION &&
		tv_timeToDelay.tv_usec > (long)maxDelayTime%MILLION))) {
		tv_timeToDelay.tv_sec = maxDelayTime/MILLION;
		tv_timeToDelay.tv_usec = maxDelayTime%MILLION;
	}
	
//	printf("select: this %p, maxSock %d, timeout %d : %d\n", this, fMaxNumSockets, tv_timeToDelay.tv_sec, tv_timeToDelay.tv_usec);	//jay
	//  gettimeofday(&timeNow, NULL);		//jay
	if (fMaxNumSockets == 0 && tv_timeToDelay.tv_sec == 0 && tv_timeToDelay.tv_usec == 0)
		goto delayTask;

	selectResult = select(fMaxNumSockets, &readSet, NULL, NULL, &tv_timeToDelay);

#if defined(__WIN32__) || defined(_WIN32)
	if (selectResult < 0) {
		int err = WSAGetLastError();
		// For some unknown reason, select() in Windoze sometimes fails with WSAEINVAL if
		// it was called with no entries set in "readSet".  If this happens, ignore it:
		if (err == WSAEINVAL && readSet.fd_count == 0) {
			err = MY_EINTR; //yzhu
			// To stop this from happening again, create a dummy readable socket:
#if 0
			int dummySocketNum = socket(AF_INET, SOCK_DGRAM, 0);
			FD_SET((unsigned)dummySocketNum, &fReadSet);
#else
			SOCKET dummySocketNum = socket(AF_INET, SOCK_DGRAM, 0);
			FD_SET(dummySocketNum, &fReadSet);
#endif
		}
		if (err != MY_EINTR) { //yzhu
			abort();
	}
}
#else
	if (selectResult < 0) {
//		printf("select errno %d\n", errno);		//jay
		// Unexpected error - treat this as fatal:
		if (errno != MY_EINTR && errno != MY_EAGAIN) { //yzhu
			abort();
		} else {
			goto delayTask;
		}
	}
#endif	

	// Call the handler function for one readable socket:

	// To ensure forward progress through the handlers, begin past the last
	// socket number that we handled:
  if (fLastHandledSocketNum >= 0) {
	  while ((handler = iter.next()) != NULL) {
		  if (handler->socketNum == fLastHandledSocketNum) break;
		}
	  if (handler == NULL) {
		  fLastHandledSocketNum = -1;
		  iter.reset(); // start from the beginning instead
		}
	}
	while ((handler = iter.next()) != NULL) {
		if (FD_ISSET(handler->socketNum, &readSet) &&
			FD_ISSET(handler->socketNum, &fReadSet) /* sanity check */ &&
			handler->handlerProc != NULL) {
	//		printf("SingleStep %p, sock %d\n", this, handler->socketNum);		//jay
			fLastHandledSocketNum = handler->socketNum;
				// Note: we set "fLastHandledSocketNum" before calling the handler,
				// in case the handler calls "doEventLoop()" reentrantly.
			(*handler->handlerProc)(handler->clientData, SOCKET_READABLE);
			break;
		}
	}
	if (handler == NULL && fLastHandledSocketNum >= 0) {
		// We didn't call a handler, but we didn't get to check all of them,
		// so try again from the beginning:
		iter.reset();
		while ((handler = iter.next()) != NULL) {
			if (FD_ISSET(handler->socketNum, &readSet) &&
				FD_ISSET(handler->socketNum, &fReadSet) /* sanity check */ &&
				handler->handlerProc != NULL) {
	//			printf("SingleStep2 %p, sock %d\n", this, handler->socketNum);		//jay
				fLastHandledSocketNum = handler->socketNum;
			// Note: we set "fLastHandledSocketNum" before calling the handler,
			// in case the handler calls "doEventLoop()" reentrantly.
				(*handler->handlerProc)(handler->clientData, SOCKET_READABLE);
				break;
			}
		}
		if (handler == NULL) fLastHandledSocketNum = -1;//because we didn't call a handler
	}

	// Also handle any delayed event that may have come due.	(Note that we do this *after* calling a socket
	// handler, in case the delayed event handler modifies the set of readable socket.)
	//  gettimeofday(&timeNow2, NULL);	//jay

delayTask:
	 fDelayQueue.handleAlarm();
//	printf("single return, this %p\n", this);
}

void BasicTaskScheduler::turnOnBackgroundReadHandling(int socketNum,
				BackgroundHandlerProc* handlerProc,
				void* clientData) {
//printf("turnOn: this %p, sock %d, handle %p, fReadSet %p\n", this, socketNum, handlerProc, &fReadSet);	//jay
  if (socketNum < 0) return;
  fReadHandlers->assignHandler(socketNum, handlerProc, clientData);
  FD_SET((unsigned)socketNum, &fReadSet);

  if (socketNum+1 > fMaxNumSockets) {
	  fMaxNumSockets = socketNum+1;
	}
}

void BasicTaskScheduler::turnOffBackgroundReadHandling(int socketNum) {
  if (socketNum < 0) return;
  FD_CLR((unsigned)socketNum, &fReadSet);
  fReadHandlers->removeHandler(socketNum);

  if (socketNum+1 == fMaxNumSockets) {
		--fMaxNumSockets;
	}
}

void BasicTaskScheduler::moveSocketHandling(int oldSocketNum, int newSocketNum) {
  if (oldSocketNum < 0 || newSocketNum < 0) return; // sanity check
  FD_CLR((unsigned)oldSocketNum, &fReadSet);
  fReadHandlers->moveHandler(oldSocketNum, newSocketNum);
  FD_SET((unsigned)newSocketNum, &fReadSet);

  if (oldSocketNum+1 == fMaxNumSockets) {
		--fMaxNumSockets;
	}
  if (newSocketNum+1 > fMaxNumSockets) {
	  fMaxNumSockets = newSocketNum+1;
	}
}
