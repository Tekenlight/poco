//
// EVAcceptedStreamSocket.cpp
//
// Library: EVNet
// Package: EVTCPServer
// Module:  EVTCPServer
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//

#include <ev.h>
#include <sys/time.h>
#include "Poco/EVNet/EVNet.h"
#include "Poco/EVNet/EVAcceptedStreamSocket.h"

using Poco::Net::StreamSocket;
namespace Poco{ namespace EVNet {

EVAcceptedStreamSocket::EVAcceptedStreamSocket(StreamSocket & streamSocket):
	_sockFd(streamSocket.impl()->sockfd()),
	_socket_read_watcher(0),
	_socket_write_watcher(0),
	_streamSocket(streamSocket),
	_prevPtr(0),
	_nextPtr(0),
	_sockBusy(false),
	_reqProcState(0),
	_req_memory_stream(0),
	_res_memory_stream(0),
	_state(NOT_WAITING),
	_socketInError(0)
{
	struct timeval tv;
	gettimeofday(&tv,0);
	_timeOfLastUse = tv.tv_sec * 1000000 + tv.tv_usec;
	_req_memory_stream = new chunked_memory_stream();
	_res_memory_stream = new chunked_memory_stream();
}

EVAcceptedStreamSocket::~EVAcceptedStreamSocket()
{
	//printf("[%p:%s:%d] Here in distructor of the created socket\n",pthread_self(),__FILE__,__LINE__);
	if (this->_socket_read_watcher) {
		if ((void*)(this->_socket_read_watcher->data))
			free((void*)(this->_socket_read_watcher->data));
		free(this->_socket_read_watcher);
	}
	if (this->_socket_write_watcher) {
		if ((void*)(this->_socket_write_watcher->data))
			free((void*)(this->_socket_write_watcher->data));
		free(this->_socket_write_watcher);
	}
	if (this->_reqProcState) delete this->_reqProcState;
	if (this->_req_memory_stream) delete this->_req_memory_stream;
	if (this->_res_memory_stream) delete this->_res_memory_stream;
}

void EVAcceptedStreamSocket::setSocketReadWatcher(ev_io *socket_watcher_ptr)
{
	this->_socket_read_watcher = socket_watcher_ptr;
}

ev_io * EVAcceptedStreamSocket::getSocketReadWatcher()
{
	return this->_socket_read_watcher;
}

void EVAcceptedStreamSocket::setSocketWriteWatcher(ev_io *socket_watcher_ptr)
{
	this->_socket_write_watcher = socket_watcher_ptr;
}

ev_io * EVAcceptedStreamSocket::getSocketWriteWatcher()
{
	return this->_socket_write_watcher;
}

StreamSocket &  EVAcceptedStreamSocket::getStreamSocket()
{
	return (this->_streamSocket);
}

void EVAcceptedStreamSocket::setSockBusy()
{
	_sockBusy = true;
	return;
}

void EVAcceptedStreamSocket::setSockFree()
{
	_sockBusy = false;
	return;
}

bool EVAcceptedStreamSocket::sockBusy()
{
	return _sockBusy;
}

StreamSocket *  EVAcceptedStreamSocket::getStreamSocketPtr()
{
	return &(this->_streamSocket);
}

poco_socket_t EVAcceptedStreamSocket::getSockfd()
{
	return _sockFd;
}
EVAcceptedStreamSocket *  EVAcceptedStreamSocket::getNextPtr()
{
	return _nextPtr;
}
EVAcceptedStreamSocket *  EVAcceptedStreamSocket::getPrevPtr()
{
	return _prevPtr;
}
void EVAcceptedStreamSocket::setNextPtr(EVAcceptedStreamSocket * ptr)
{
	_nextPtr = ptr;
}
void EVAcceptedStreamSocket::setPrevPtr(EVAcceptedStreamSocket * ptr)
{
	_prevPtr = ptr;
}

void  EVAcceptedStreamSocket::setTimeOfLastUse()
{
	struct timeval tv;
	gettimeofday(&tv,0);
	_timeOfLastUse = tv.tv_sec * 1000000 + tv.tv_usec;
	return ;
}

long long  EVAcceptedStreamSocket::getTimeOfLastUse()
{
	return _timeOfLastUse;
}

void EVAcceptedStreamSocket::setProcState(EVProcessingState* procState)
{
	_reqProcState = procState;
}

EVProcessingState* EVAcceptedStreamSocket::getProcState()
{
	return _reqProcState;
}

void EVAcceptedStreamSocket::deleteState()
{
	delete _reqProcState;
	_reqProcState = NULL;
	return;
}

size_t EVAcceptedStreamSocket::pushResData(void * buffer, size_t size)
{
	return _req_memory_stream->push(buffer, size);
}

size_t EVAcceptedStreamSocket::pushReqData(void * buffer, size_t size)
{
	return _req_memory_stream->push(buffer, size);
}

bool EVAcceptedStreamSocket::resDataAvlbl()
{
	int c = 0;
	return (_res_memory_stream->copy(0, &c, 1) > 0);
}

bool EVAcceptedStreamSocket::reqDataAvlbl()
{
	int c = 0;
	return (_req_memory_stream->copy(0, &c, 1) > 0);
}

chunked_memory_stream * EVAcceptedStreamSocket::getResMemStream()
{
	return _res_memory_stream;
}

chunked_memory_stream * EVAcceptedStreamSocket::getReqMemStream()
{
	return _req_memory_stream;
}

} } // namespace EVNet and Poco end.

