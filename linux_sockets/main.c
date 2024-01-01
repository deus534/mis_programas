#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PUERTO 15002
#define LON_MAX 100

int main()
{
        int mi_socket;
        int on;
        int resu;
        int nuevo_socket;
        char msj[LON_MAX];
        struct sockaddr_in su_direccion;
        struct sockaddr_in midireccion;
        socklen_t leng = sizeof(su_direccion);

        mi_socket = socket( AF_INET, SOCK_STREAM, 0 );

        if( mi_socket!=-1 )
        {
                printf("SOCKET ABIERto\n");
                midireccion.sin_family = AF_INET;
                midireccion.sin_port = htons(PUERTO);
                midireccion.sin_addr.s_addr = INADDR_ANY;
                memset(midireccion.sin_zero, 0, 8);
                setsockopt(mi_socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

                resu = bind( mi_socket, (struct sockaddr *)&midireccion, sizeof(midireccion) );

                if( resu!=-1 )
                {
                        printf("Socket conectado\n");

                        listen( mi_socket, 10 );
                        nuevo_socket = accept( mi_socket, (struct sockaddr *)&su_direccion, &leng );
                        printf("Conexion establecida desde: %s\n", inet_ntoa(su_direccion.sin_addr) );

                        // envio un mensaje de bienvenida
                        strcpy( msj, "hola soy el servidor" );
                        send( nuevo_socket, msj, strlen(msj), 0 );

                        close(nuevo_socket);
                }
                close(mi_socket);
        }
        else printf("ERROR NO PUDE ABRIR EL SOCKET\n");


        return 0;
}
