#include <iostream>
#include <ResourceManager.h>
#include "includes/Server.hpp"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Specify a directory to serve" << std::endl;
        return 1;
    }

    Server* server = new Server(std::string(argv[1]));
    return server->start();
}
