#include <iostream>
#include <ResourceManager.h>
#include "includes/ArgumentParser.hpp"
#include "includes/Server.hpp"


int main(int argc, char *argv[]) {
    ArgumentParser* argparser = new ArgumentParser(argc, argv);
    argparser->add_argument("--port");
    argparser->add_argument("--directory");

    Server* server = new Server(
        std::stoi(argparser->get_argument("--port")),
        argparser->get_argument("--directory")
    );
    return server->start();
}
