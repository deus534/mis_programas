#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "structs.h"
#include "funciones.h"
int flag = 0;    //para las seniales


//actualiza los archivos cada sierto tiempo
void actualizar_archivos(int num);

//finaliza el programa con control c
void finalizar_programa(int num);

void * escuchar_conexiones(Argumento_t * argumentos);

int main( int argc, char ** argv )
{
        //creo que la razon por la que siempre me sobra un bloque es por el thread de inicio que no termina
	int error;
        Argumento_t arg_inicio;
        pthread_t escucha;

        Nodo_t * lista_usuarios = leer_usuarios(&error);
        Nodo_t * lista_documentos = leer_documentos(&error);
        

	if( argc==2 )
	{
                //para actualizar la lista
                alarm(120);
                signal(SIGALRM, actualizar_archivos);
                
                //para finalizar el programa
                signal(SIGINT, finalizar_programa);

                strcpy(arg_inicio.puerto, argv[1]);
                arg_inicio.lista_usuarios = &lista_usuarios;
                arg_inicio.lista_documentos = &lista_documentos;
                
                //creo un thread que escucha las conexiones
                pthread_create( &escucha, NULL, (void *)escuchar_conexiones, &arg_inicio );
                pthread_detach( escucha );

                while( 1 )
                {
                        if( flag==1 )
                        {
                                flag = 0;
                                printf("Se actualizaron los archivos: %s, %s\n", ARCH_USUARIO, ARCH_DOCUMENTO);
                                cargar_usuarios(lista_usuarios);
                                cargar_documentos(lista_documentos);
                        }
                        
                        if( flag==END )
                        {
                                printf("\nFinalizando el programa\n");
                                liberar(lista_usuarios, liberar_usuario);
                                liberar(lista_documentos, liberar_documento);
                                close(arg_inicio.socket);
                                exit(1);
                        }
                        usleep(5000);
                }
	}
	else
	{
		printf("Introduce el port\n");
	}
	return 0;
}
void * escuchar_conexiones(Argumento_t * argumentos)
{
        int misocket;
        int nuevo_socket;
        pthread_t thread;
        Argumento_t arg_pth;
	struct sockaddr_in sudireccion;
	socklen_t leng = sizeof(sudireccion);

        //modificar
        misocket = iniciar_socket(argumentos->puerto);

        argumentos->socket = misocket;

        if( misocket!=-1 )
        {
                pthread_mutex_init( &(arg_pth.semaforo),NULL );
                while( 1 )
                {              
                        listen(misocket, NBACKLOG);

                        //funciona como lockeo
                        nuevo_socket = accept(misocket, (struct sockaddr *) &sudireccion, &leng);
                        
                        printf("Conexión establecida desde %s\n", inet_ntoa(sudireccion.sin_addr));

                        //lockeo para que no tenga problema con el socket de cada cliente
                        pthread_mutex_lock( &(arg_pth.semaforo) );

                        arg_pth.socket = nuevo_socket;
                        arg_pth.lista_usuarios = argumentos->lista_usuarios;
                        arg_pth.lista_documentos = argumentos->lista_documentos;

                        pthread_create( &thread, NULL, (void *)nuevo_cliente, (void *)&arg_pth );

                        pthread_detach(thread);

                        usleep(5000);
                }
        }
        return NULL;
}
void finalizar_programa(int num)
{
        flag = END;
}
void actualizar_archivos(int num)
{
        flag = 1;
        alarm(120);
}

