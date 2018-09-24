#include <iostream>
#include <ResourceManager.h>
#include "includes/Server.hpp"


int main(int argc , char *argv[]) {
    Server* server = new Server();
    return server->start();
}
