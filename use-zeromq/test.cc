#include "gtest/gtest.h"

#include "test_util.h" 
#include <zmq.hpp>

#include <chrono>
#include <thread>

using namespace zmq;
using std::cout;
using std::endl;
using namespace util;

/*
on exception, we need to set_linger=0 and close() all sockets BEFORE calling context_close()
*/
TEST(some, test_socket_cleanup) {

    auto factory = SocketFactory::create();
    auto serverSocket = factory->createRepSocket(9095);
    auto clientSocket = factory->createReqSocket(9095);

    try {

        cout << "errno=" << errno << endl;
        zmq::message_t msg(1024);
    
        auto ret = clientSocket->send(msg, zmq::send_flags::dontwait);
        cout << "ret.hasValue()=" << ret.has_value() << endl;
        ret = clientSocket->send(msg, zmq::send_flags::dontwait);
        cout << "ret.hasValue()=" << ret.has_value() << endl;
    }
    catch (std::exception& e) {
        cout << "err: " << e.what() << endl;

        //clientSocket->setsockopt(ZMQ_LINGER, 0);
        //clientSocket->close();
        //serverSocket->setsockopt(ZMQ_LINGER, 0);
        //serverSocket->close();
    }
}

TEST(some, DISABLED_init_message) {
    zmq_msg_t* msg = new zmq_msg_t();
    zmq_msg_init(msg);

    zmq::context_t context(1);
    zmq::socket_t serverSocket(context, ZMQ_REP);
    serverSocket.bind("tcp://*:5555");

    zmq::socket_t clientSocket(context, ZMQ_REQ);

    cout << "Connecting to hello world server..." << endl;
    clientSocket.connect("tcp://localhost:5555");

    zmq::message_t request(5);
    memcpy(request.data(), "agh\0", 4);
    cout << "data=" << request.data() << endl;
    printf("data=%s\n", (char*)request.data());

    clientSocket.send(request);

    zmq::message_t serverMsg(500);
    serverSocket.recv(&serverMsg);

    printf("server: data=%s\n", (char*)request.data());
    //  Send reply back to client

    zmq::message_t reply(30);
    memcpy(reply.data(), "server: agh\0", 12);
    serverSocket.send(reply);

    zmq::message_t resp(30);
    clientSocket.recv(&resp);
    printf("client: resp data=%s\n", (char*)resp.data());

}

TEST(some, DISABLED_test) {

    
    //  Socket to talk to clients
    // void* context = zmq_ctx_new();
    // void* repSocket = zmq_socket(context, ZMQ_REP);

    zmq::context_t context(1);
    zmq::socket_t serverSocket(context, ZMQ_REP);
    serverSocket.bind("tcp://*:5555");

    zmq::socket_t clientSocket(context, ZMQ_REQ);
    clientSocket.connect("tcp://localhost:5555");

    for (int i=0;i<10;i++) {
        zmq::message_t request(5);
        memcpy(request.data(), "Hello", 5);
        
        std::cout << "client: sending num=" << i << std::endl;
        clientSocket.send(request);

        //  Get the reply.
        zmq::message_t reply;
        serverSocket.recv(&reply);
        std::cout << "server: msg=" << reply.data() << std::endl;

        zmq::message_t reply1;
        memcpy(reply1.data(), "agh", 5);
        serverSocket.send(reply1);

        //  Wait for next request from client
        clientSocket.recv(&request);
        std::cout << "client: recv=" << request.data() << std::endl;
    }

  ASSERT_TRUE(false);
}
