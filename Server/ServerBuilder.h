//
// Created by gaojian on 2019/12/24.
//

#ifndef QRPC_SERVERBUILDER_H
#define QRPC_SERVERBUILDER_H


class ServerBuilder {
public:
	template<typename Request, typename Response>
	void registerPairedMsg();
};

class Services {
public:
};
#endif //QRPC_SERVERBUILDER_H
