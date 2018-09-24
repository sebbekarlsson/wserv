#include "includes/Server.hpp"

Server::Server() {};


size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}


std::string Server::get_route(std::string client_message) {
    std::string route = "";
    std::istringstream iss(client_message);

    for (std::string line; std::getline(iss, line); ) {
        if (line.find("GET") != std::string::npos && line.find("HTTP") != std::string::npos) {
            std::vector<std::string> parts;
            split(line, parts, ' ');
            route = parts[1];

            if (route.find("/") != std::string::npos)
                route.erase(0, 1);

            return route;
        }
    }

    return route;
};

int Server::start() {
    ResourceManager::load("response.txt");
    std::string msg = ResourceManager::get("response.txt");

    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];

    // Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 2000 );

    // Bind
    if (bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0) {
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    // Listen
    listen(socket_desc , 3);

    // Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    while (true) {
        // accept connection from an incoming client
        client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
        if (client_sock < 0) {
            perror("accept failed");
            return 1;
        }
        puts("Connection accepted");

        // Receive a message from client
        while ((read_size = read(client_sock , client_message , sizeof(client_message))) > 0) {
            //Send the message back to client
            std::string route = this->get_route(std::string(client_message));
            ResourceManager::load(route);

            write(client_sock , ResourceManager::get(route).c_str(), strlen(msg.c_str()));
            memset( &client_message, 0, sizeof(client_message));
        }

        if(read_size == 0) {
            puts("Client disconnected");
            fflush(stdout);
        }
        else if(read_size == -1) {
            perror("recv failed");
        }
    }

    return 0;
};
