#ifndef EVNet_EVServer_INCLUDED
#define EVNet_EVServer_INCLUDED

#include "Poco/Net/Net.h"
#include "Poco/EVNet/EVNet.h"
#include "Poco/Net/StreamSocket.h"

namespace Poco {
namespace EVNet {

class Net_API EVServer {
public:
	EVServer();
	~EVServer();
	virtual void receivedDataConsumed(int fd) = 0;
	virtual void errorInReceivedData(poco_socket_t fd, bool connInErr) = 0;
	virtual void dataReadyForSend(int fd) = 0;
};

/*
typedef void (EVServer::*reqComplMthd)(Net::StreamSocket &);
typedef void (EVServer::*dataReadyMthd)(Net::StreamSocket &);
typedef void (EVServer::*reqExcpMthd)(Net::StreamSocket & streamSocket,poco_socket_t fd, bool);
typedef struct {
	EVServer *objPtr;
	reqComplMthd reqComMthd;
	reqExcpMthd reqExcMthd;
	dataReadyMthd dataSendMthd;
} reqComplEvntHandler , *reqComplEvntHandlerPtr;
*/

}
}

#endif
