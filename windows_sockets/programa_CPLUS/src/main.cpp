#include <stdio.h>
#include <iostream>

//encabezados para sockets
#include <winsock2.h>
#include <arpa/inet.h>
//definicion de constantes
#define PORT 15001

int main()
{
        SOCKET mi_socket = INVALID_SOCKET;
        sockaddr_int service;
        int id_result;



        mi_socket = socket(AF_INET, SOCK_STREAM, 0);

        if( mi_socket!=INVALID_SOCKET )
        {
                printf("Creacion correcta\n");
                service.sin_family = AF_INET;
                service.sin_addr.s_addr = inet_addr("127.0.0.1");
                service.sin_port() = htons(PORT);
                
                id_result = bind(mi_socket, (SOCK_ADDR *)&service, sizeof(service) );

                if( id_result!=SOCKET_ERROR )
                {
                        printf("CREACION CORRECTA\n");
                        if( listen(mi_socket,SOMAXCONN)!=SOCKET_ERROR )
                        {
                                printf("LISTEN CORRECTO\n");

                        }
                        else 
                        {
                                printf("ERROR DE LISTEN\n");
                        }
                }
                else 
                {
                        printf("ERROR DE BIND\n");
                }
                closesocket(mi_socket);
        }
        else
        {
                printf("ERROR de socket\n");        
        }

        /*
        int num;
        scanf("%d", &num);
        printf("el numero es: %d\n", num);
        std::cout << "hola mundo\n";
        printf("hola mundo\n");
        */
        return 0;
}
