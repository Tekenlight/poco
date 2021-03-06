//
// EVProcessingState.h
//
// Library: EVProcessingState
// Package: EVNet
// Module:  EVProcessingState
//
// Basic definitions for the Poco EVNet library.
// This file must be the first file included by every other EVNet
// header file.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include <chunked_memory_stream.h>
#include "Poco/Net/Net.h"
#include "Poco/EVNet/EVNet.h"
#include "Poco/EVNet/EVServer.h"

#ifndef EVNet_EVProcessingState_INCLUDED
#define EVNet_EVProcessingState_INCLUDED

namespace Poco {
namespace EVNet {

class Net_API EVProcessingState
	// This class is used as a marker to hold state data of processing of a request in a connection.
	// In case of event driven model of processing, the processing of a request may have to be
	// suspended mulptiple times, while data is being fetched from sources (e.g. client)
	//
	// The processing of the request is coded in such a way, that all the intermediate data is held within
	// a derivation of this base class and the state is destroyed at the end of processing of the request.
{
public:

	EVProcessingState(EVServer * server);
	virtual int getState() = 0;
	virtual ~EVProcessingState();
	virtual void setReqMemStream(chunked_memory_stream *memory_stream) = 0;
	virtual void setResMemStream(chunked_memory_stream *memory_stream) = 0;
	EVServer* getServer();

private:
	EVServer* _server;

};

inline EVProcessingState::EVProcessingState(EVServer * server):_server(server) { }
inline EVProcessingState::~EVProcessingState() { }
inline EVServer* EVProcessingState::getServer() { return _server; }

}
} // End namespace Poco::EVNet





#endif
