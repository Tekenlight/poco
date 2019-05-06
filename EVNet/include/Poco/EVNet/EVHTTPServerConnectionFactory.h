//
// EVHTTPServerConnectionFactory.h
//
// Library: EVNet
// Package: EVHTTPServer
// Module:  EVHTTPServerConnectionFactory
//
// Definition of the EVHTTPServerConnectionFactory class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef EVNet_EVHTTPServerConnectionFactory_INCLUDED
#define EVNet_EVHTTPServerConnectionFactory_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/EVNet/EVTCPServerConnectionFactory.h"
#include "Poco/EVNet/EVHTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/EVNet/EVHTTPProcessingState.h"

using Poco::Net::HTTPServerParams;
using Poco::Net::StreamSocket;

namespace Poco {
namespace EVNet {


class Net_API EVHTTPServerConnectionFactory: public EVTCPServerConnectionFactory
	/// This implementation of a EVTCPServerConnectionFactory
	/// is used by HTTPServer to create HTTPServerConnection objects.
{
public:
	EVHTTPServerConnectionFactory(HTTPServerParams::Ptr pParams, EVHTTPRequestHandlerFactory::Ptr pFactory);
		/// Creates the EVHTTPServerConnectionFactory.

	~EVHTTPServerConnectionFactory();
		/// Destroys the EVHTTPServerConnectionFactory.

	EVTCPServerConnection* createConnection(StreamSocket& socket);
		/// Creates an instance of HTTPServerConnection
		/// using the given StreamSocket.
	
	EVTCPServerConnection* createConnection(StreamSocket& socket, EVProcessingState * reqProcState);
		/// Creates an instance of HTTPServerConnection
		/// using the given StreamSocket.
	
	EVProcessingState* createReaProcState();
		/// Creates an instance of EVHTTPProcessingState

private:
	HTTPServerParams::Ptr          _pParams;
	EVHTTPRequestHandlerFactory::Ptr _pFactory;
};


} } // namespace Poco::EVNet


#endif // EVNet_EVHTTPServerConnectionFactory_INCLUDED
