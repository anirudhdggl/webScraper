#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <string>

#pragma comment(lib,"ws2_32.lib")

#define HOST sin_addr.S_un.S_addr

using namespace std;

int main() {
    system("cls");

    WSADATA wd;

    WSAStartup(MAKEWORD(2,0),&wd);

    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    sockaddr_in socket_address;

    char data[1000000];

    hostent *host;

    string query = "GET / HTTP/1.1\r\n\r\n";

    string hostName;

    if(WSAStartup(0x202,&wd)) {
        cout<<"Unable to initialize windows socket";
        return -1;
    }

    cout<<"Enter host name:\t";
    getline(cin,hostName);

    host = gethostbyname(hostName.data());

    socket_address.sin_family = AF_INET;
    socket_address.HOST =*(PULONG)host->h_addr;
    socket_address.sin_port = htons(80);

    if(s!=INVALID_SOCKET) {
        
        connect(s,(sockaddr*)&socket_address,sizeof(socket_address));

        send(s,query.data(),query.size(),0);

        signed int bytes_returned;
        
        bool flag = true;

        recv(s,data,100000,0);
        
        cout<<data;
    }
    
    closesocket(s);
    WSACleanup();
    return 0;
}
