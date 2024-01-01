#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <winerror.h>

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

//compilar: g++ .\src\main.cpp -o ejec -lwsock32
int main()
{
        int iResult = 0;            // used to return function results
        SOCKET ListenSocket;
        SOCKET nuevo_socket;
        sockaddr_in service;

        ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
        
        if (ListenSocket != INVALID_SOCKET)
        {
                printf("socket abierto\n");
                service.sin_family = AF_INET;
                service.sin_addr.s_addr = inet_addr("127.0.0.1");
                service.sin_port = htons(27015);

                iResult = bind(ListenSocket, (SOCKADDR *) &service, sizeof (service));
                
                if (iResult != SOCKET_ERROR)
                {
                        if ( listen(ListenSocket, SOMAXCONN) != SOCKET_ERROR )
                        {
                                printf("Escuchando conexiones\n");
                                nuevo_socket = accept(ListenSocket, NULL, NULL);
                                if (nuevo_socket != INVALID_SOCKET) {
                                        printf("conexion aceptada\n");
                                        closesocket(nuevo_socket);
                                }
                        }
                        else printf("error de listen\n");
                }
                else printf("error de bind\n");
                closesocket(ListenSocket);
        }
        else printf("No se pudo abrir el socket perrin");

        return 0;
}