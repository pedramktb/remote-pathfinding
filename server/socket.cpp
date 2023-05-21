#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include "utils.cpp"

class Socket{
public:
    static int start(){
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1)
        {
            std::cerr << "Can't create a socket!";
            return -1;
        }
        struct sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(3333);
        inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
        if (bind(sock, (struct sockaddr *)&hint, sizeof(hint)) == -1)
        {
            std::cerr << "Can't bind to IP/port";
            return -2;
        }
        if (listen(sock, SOMAXCONN) == -1)
        {
            std::cerr << "Can't listen !";
            return -3;
        }
        struct sockaddr_in client;
        socklen_t clientSize = sizeof(client);
        int clientSock = accept(sock, (struct sockaddr *)&client, &clientSize);
        if (clientSock == -1)
        {
            std::cerr << "Problem with client connecting!";
            return -4;
        }
        std::cout << "Client address: " << inet_ntoa(client.sin_addr) << " and port: " << client.sin_port << std::endl;
        close(sock);

        char buf[4096];
        while (true) {
            memset(buf, 0, 4096);

            // wait for a message
            int bytesRecv = recv(clientSock, buf, 4096, 0);
            if (bytesRecv == -1)
            {
                std::cerr << "There was a connection issue." << std::endl;
            }
            if (bytesRecv == 0)
            {
                std::cout << "The client disconnected" << std::endl;
            }

            std::string message = std::string(buf, 0, bytesRecv);

            //std::cout << "Received: " << message << std::endl;//debug

            std::string response = Utils::handle(message);

            //std::cout << "Response: " << response << std::endl;//debug

            // return message
            if(send(clientSock, response.c_str(), response.size(), 0)==-1){
                std::cerr << "There was a connection issue." << std::endl;
            }
        }
        // close socket
        close(clientSock);
    }
};