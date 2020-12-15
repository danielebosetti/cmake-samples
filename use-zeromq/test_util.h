#ifndef USE_ZEROMQ_TEST_UTIL_H
#define USE_ZEROMQ_TEST_UTIL_H

#include <zmq.hpp>

#include <chrono>
#include <thread>

#include <memory>

namespace util {

	class SocketFactory {
	private:
		zmq::context_t context;

	public:
		SocketFactory() : context{ 1 } {
		}

		static std::shared_ptr<SocketFactory> create() {
			return std::make_shared<SocketFactory>();
		}
		/*
		 * creates a REP socket, listening on the given tcp port
		*/
		std::shared_ptr<zmq::socket_t> createRepSocket(int port) {
			auto res = std::make_shared<zmq::socket_t>(context, ZMQ_REP);
			char* tcpAddr = new char[1000];
			sprintf(tcpAddr, "tcp://*:%d", port);
			fprintf(stdout, "bind: tcpAddr=[%s]\n", tcpAddr);
			res->bind(tcpAddr);
			return res;
		}
		/*
		 * creates a new REQ socket, connects to localhost on the the given port
		 */
		std::shared_ptr<zmq::socket_t> createReqSocket(int port) {
			auto res = std::make_shared<zmq::socket_t>(context, ZMQ_REQ);
			char* tcpAddr = new char[1000];
			sprintf(tcpAddr, "tcp://localhost:%d", port);
			fprintf(stdout, "connect: tcpAddr=[%s]\n", tcpAddr);
			res->connect(tcpAddr);
			return res;
		}

	};
}
#endif