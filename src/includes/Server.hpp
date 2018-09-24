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
        Server(std::string directory);

        std::string get_route(std::string client_message);
        std::string gen_header(int content_length);

        std::string directory;

        int start();
};
#endif
