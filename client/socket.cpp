#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include "utils.cpp"

class SocketClient {
public:
    static int conncet() {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1)
        {
            std::cerr << "Can't create a socket!" << std::endl;
            return -1;
        }
        struct sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(3333);
        inet_pton(AF_INET, "localhost", &hint.sin_addr);
        if (connect(sock, (sockaddr*)&hint, sizeof(hint)) == -1)
        {
            std::cerr << "Connection failed" << std::endl;
            return -2;
        }

        std::string userInput;
        char buf[4096];
        while(true) {
            memset(buf, 0, 4096);
            std::cout << "> ";
            getline(std::cin, userInput);
            if (send(sock, userInput.c_str(), userInput.size(), 0) == -1) {
                std::cerr << "There was a connection issue." << std::endl;
                continue;
            }
            memset(buf, 0, 4096);
            int bytesRecv = recv(sock, buf, 4096, 0);
            if (bytesRecv == -1) {
                std::cerr << "There was an error getting the response." << std::endl;
            }
            else {
                std::string response = std::string(buf, 0, bytesRecv);
                std::cout << "Server> " << response << std::endl;
                Utils::handle(userInput, response);
            }

        }

        close(sock);

        return 0;
    }
};