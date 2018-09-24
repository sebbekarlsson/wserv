#ifndef SERVER_H
#define SERVER_H
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>
#include <ResourceManager.h>


class Server {
    public:
        Server();

        std::string get_route(std::string client_message);

        int start();
};
#endif
