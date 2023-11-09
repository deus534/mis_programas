#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include "structs.h"
#include "funciones.h"

int agregar( Nodo_t ** lista, void * dat )
{
	int error = ERRMEM;

	Nodo_t * aux_lista = *lista;
	
	Nodo_t * nuevo;

	nuevo = (Nodo_t *)malloc( sizeof(Nodo_t) );

	if( nuevo )
	{
		error = OK;
		nuevo->dato = dat;
		nuevo->next = NULL;
		if( aux_lista )
		{
			while( aux_lista->next )
			{
				aux_lista = aux_lista->next;
			}
			aux_lista->next = nuevo;
		}
		else
		{
			*lista = nuevo;
		}
	}
	return error;
}
int buscar( Nodo_t ** lista, void * elem, int(*crit_busqueda)(void *, void *) )
{
	int err = ERROR;
	void * dato_aux;
	Nodo_t * aux_list = *lista;
	while( aux_list && err!=OK )
	{
		dato_aux = aux_list->dato;
		err = crit_busqueda(elem, dato_aux);
		aux_list = aux_list->next;
	}
	return err;
}
int eliminar(Nodo_t ** lista, void * elim, int(*cmp_elim)(void*,void*),void(*liberar_dato)(void *) )
{
	int err = ERROR;
	Nodo_t * aux = *lista;
	Nodo_t * ant = NULL;
	while( aux && cmp_elim(aux->dato, elim)!=OK )
	{
		ant = aux;
		aux = aux->next;
	}
	if( aux )
	{
		err = OK;
		if( ant )
		{
			ant->next = aux->next;
		}
		else
		{
			*lista = aux->next;
		}
		liberar_dato(aux->dato);
		free(aux);
	}
	return err;
}
void ordenar(Nodo_t * lista,int(*fun_cmp)(void *,void *))
{
	void * aux = NULL;
	Nodo_t * pdato = lista;
	Nodo_t * actual = NULL;
	if( lista )
	{
		while( pdato->next )
		{
			actual = pdato->next;
			while( actual )
			{
				if( fun_cmp(pdato->dato,actual->dato)>0 )
				{
					aux = pdato->dato;
					pdato->dato = actual->dato;
					actual->dato = aux;
				}
				actual = actual->next;
			}
			pdato = pdato->next;
		}
	}
}
Nodo_t * leer_usuarios(int * error)
{
	FILE * file;
	int LON_LINEA = 50;
	int nivel;
	char linea[LON_LINEA];
	char * nombre;
	char * contra;
	Nodo_t * lista = NULL;
	Usuario_t * nuevo;

	file = fopen(ARCH_USUARIO, "r");

	if( file )
	{
		while( fgets(linea, LON_LINEA, file) && (*error)!=ERRMEM )
		{
			//obtengo los datos leidos
			nombre = strtok(linea, "|");
			
			contra = strtok(NULL, "|");

			nivel = atoi( strtok(NULL,"|") );
			//creo un nuevo usuario con los datos
			nuevo = nuevo_usuario( nombre, contra, nivel );
			
			if( nuevo )
			{
				*error = agregar(&lista, (void *)nuevo);
			}
			else
			{
				*error = ERRMEM;
			}
		}
		fclose(file);
	}
	return lista;
}
Nodo_t * leer_documentos(int * error)
{
	FILE * file;
	int LON_LINEA = 50;
	char linea[LON_LINEA];
	char * cod;
	char * nom;
	char * aut;
	char * anio;
	Nodo_t * lista = NULL;
	Documento_t * nuevo;

	file = fopen(ARCH_DOCUMENTO, "r");

	if( file )
	{
		while( fgets(linea, LON_LINEA, file) && (*error)!=ERRMEM )
		{
			//obtengo los datos leidos
			cod = strtok(linea, "|");
			
			nom = strtok(NULL, "|");
			
			aut = strtok(NULL, "|");
			
			anio = strtok(NULL, "|");

			//creo un nuevo usuario con los datos
			nuevo = nuevo_documento( cod, nom, aut, atoi(anio) );
			
			if( nuevo )
			{
				*error = agregar(&lista, (void *)nuevo);
			}
			else
			{
				*error = ERRMEM;
			}
		}
		fclose(file);
	}
	return lista;
}

int cargar_usuarios(Nodo_t * lista_usuarios)
{
	FILE * file;
	int error = 0;
	Nodo_t * aux_lista = lista_usuarios;
	Usuario_t * usuario;
	
	file = fopen(ARCH_USUARIO,"w+");	
	
	if( file )
	{
		while( aux_lista && error!=-1 )
		{
			usuario = (Usuario_t*)aux_lista->dato;

			error = fprintf(file, "%s|%s|%d\n",usuario->nombre,usuario->contrasenia,usuario->nivel);
			
			aux_lista = aux_lista->next;	
		}
		fclose(file);
	}
	return error;
}
int cargar_documentos(Nodo_t * lista)
{
	FILE* file;
	int error = 0;
	Nodo_t * aux = lista;
	Documento_t * pdato = NULL;

	file = fopen(ARCH_DOCUMENTO, "w+");

	if( file )
	{
		while( aux && error!=-1 )
		{
			pdato = (Documento_t*)aux->dato;

                        //nose si poner la validacion de que pueda o no escribir
			error = fprintf(file, "%s|%s|%s|%d\n",pdato->codigo,pdato->nombre,pdato->autor,pdato->anio);
			
			aux = aux->next;
		}
                fclose(file);
	}
        return error;
}
Usuario_t * nuevo_usuario(char* nom, char* cont, int nivel)
{
	Usuario_t* us;

	//pido memoria
	us = (Usuario_t*)malloc( sizeof(Usuario_t) );

	//valido memoria
	if( us )
	{
		//pido memoria
		us->nombre = (char *)malloc( sizeof(nom) );

		//pido memoria
		us->contrasenia = (char *)malloc( sizeof(cont) );

		//valido la memoria
		if( us->nombre && us->contrasenia )
		{
			strcpy(us->nombre, nom);
			strcpy(us->contrasenia, cont);
			us->nivel = nivel;
		}
		else
		{
			//no me pudieron dar memoria para los char*
			us = NULL;
		}
	}
	return us;
}
Documento_t * nuevo_documento(char * cod, char * nom, char * aut, int an)
{
	Documento_t * nuevo;
	nuevo = (Documento_t*)malloc( sizeof(Documento_t) );
	if( nuevo )
	{
		//pido memoria
		nuevo->nombre = (char*)malloc( strlen(nom)+1 );
		nuevo->autor = (char*)malloc( strlen(aut)+1 );
		//valido los 2 pedidos de memoria
		
		if( nuevo->nombre && nuevo->autor )
		{
			strcpy(nuevo->codigo, cod);
			strcpy(nuevo->nombre, nom);
			strcpy(nuevo->autor, aut);
			nuevo->anio = an;
		}
		else
		{
			nuevo = NULL;
		}
	}
	return nuevo;
}
void liberar_usuario(void * dato)
{
	Usuario_t * pdato = (Usuario_t*)dato;
	free(pdato->nombre);
	free(pdato->contrasenia);
	free(pdato);
}
void liberar_documento(void * dato)
{
	Documento_t * doc = (Documento_t*)dato;
	free(doc->nombre);
	free(doc->autor);
	free(doc);
}
void liberar(Nodo_t * lista, void(*liberar_dato)(void*))
{
	Nodo_t * aux;
	while( lista )
	{
		aux = lista;
		lista = lista->next;	
		liberar_dato(aux->dato);
		free(aux);
	}
}
int iniciar_socket(char * puerto)
{
	int misocket, resu;
	struct sockaddr_in midireccion;
	int on = 1;

	misocket = socket(AF_INET, SOCK_STREAM, 0);
	
        if (misocket != -1)
	{
		printf("Socket abierto\n");
		midireccion.sin_family = AF_INET;
		midireccion.sin_port = htons(atoi(puerto));
		midireccion.sin_addr.s_addr = INADDR_ANY;
		memset(midireccion.sin_zero, 0, 8);
		setsockopt(misocket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

		resu = bind(misocket, (struct sockaddr *) &midireccion, sizeof(midireccion));

                if( resu ==-1 )
                {
                        close(misocket);
                        exit(1);
                }
        }
        return misocket;
}
void * nuevo_cliente(Argumento_t * dato)
{
        int nuevosocket;
        int error;
	char mensaje[LARGO] = "Hola soy el servidor, iniciaste una nueva sesion";
        int peticion;
        int nro_menu;

        nuevosocket = dato->socket;

        pthread_mutex_unlock( &(dato->semaforo) );

        send(nuevosocket, mensaje, LARGO, 0);

        //tengo un error que si digamos lo pongo la condicion de salida en el while no me funciona

        while( 1 )
        {
                //aca recibo un nro de menu
                recv(nuevosocket, &nro_menu, sizeof(int), 0);

                //espero a recibir una peticion
                recv(nuevosocket, &peticion, sizeof(int), 0);
                
                printf("Recibi los datos de %d: \n", nuevosocket);
                switch( nro_menu )
                {
                        case 1:
                                //pthread_mutex_lock( &(dato->semaforo) );
                                printf("Realizando menu 1\n");
                                error = realizar_menu_1(nuevosocket, peticion, dato->lista_usuarios, &(dato->semaforo) );
                                printf("ERROR: %d\n", error);
                                break;
                        case 2:
                                printf("Realizando menu 2\n");
                                error = realizar_menu_2(nuevosocket, peticion, dato->lista_documentos, &(dato->semaforo) );
                                break;
                        case 3:
                                printf("Realizando menu 3\n");
                                break;
                        case 4:
                                printf("Realizando menu root\n");
                                break;
                }
                
                printf("peticion = %d\n", peticion);

                if( nro_menu==1 && peticion==4 )
                {
                        break;
                }
                usleep(5000);
        }
        printf("Finalizo la sesion nro: %d\n", nuevosocket);

        close(nuevosocket);

        return NULL;
}
int cmp_codigo(void * cod, void * pdocumento)
{
        int error = ERROR;
        char * cod_buff = (char *)cod;
        Documento_t * doc = (Documento_t*)pdocumento;

        if( strcpy(cod_buff,doc->codigo)==0 )
        {
                error = OK;
        }
        return error;
}
int realizar_menu_2(int socket, int peticion, Nodo_t ** lista_documentos, pthread_mutex_t * semaforo )
{
        int error = OK;
        int finalizacion_cliente=OK;
        char buffer[LARGO];
        char codigo[LARGO];
        char nombre[LARGO];
        char autor[LARGO];
        int anio;
        Nodo_t * aux_lista = *lista_documentos;
        Documento_t * doc;

        switch( peticion )
        {
                case 1:
                        if( !aux_lista )
                        {
                                printf("ES NULL\n");
                        }
                        //pasar los documentos al usuario
                        while( aux_lista )
                        {
                                //Envio la condicion para que este en el while del cliente 
                                send(socket, &finalizacion_cliente, sizeof(int), 0);

                                doc = (Documento_t*)aux_lista->dato;
                                //empiezo a enviar los datos del documento

                                //envio el codigo
                                strcpy(buffer, doc->codigo);
                                send(socket, buffer, LARGO, 0);
                                
                                //envio el nombre
                                strcpy(buffer, doc->nombre);
                                send(socket, buffer, LARGO, 0);

                                //envio el autor
                                strcpy(buffer, doc->autor);
                                send(socket, buffer, LARGO, 0);

                                //envio el anio
                                send(socket, &(doc->anio), sizeof(int), 0);

                                aux_lista = aux_lista->next;
                        }
                        //envio la finalizacion del while del cliente
                        printf("ENVIO FINALIZACION\n");
                        finalizacion_cliente = ERROR;
                        send(socket, &finalizacion_cliente, sizeof(int), 0);
                        break;
                case 2:
                        //recibo el codigo
                        recv(socket, codigo, LARGO, 0);
                        
                        error = buscar(lista_documentos, codigo, cmp_codigo);
                        send(socket, &error, sizeof(int), 0);

                        if( (error)!=OK )
                        {
                                printf("TODO OK\n");
                                recv(socket, nombre, LARGO, 0);
                                recv(socket, autor, LARGO, 0);
                                recv(socket, &anio, sizeof(int), 0);
                                
                                //omito verificacion
                                doc = nuevo_documento(codigo, nombre, autor, anio);
                                
                                agregar(lista_documentos, (void *)doc);
                        }
                        break;
        }
        return error;
}
int __nombre(void * comp, void * dat_lista)
{
        int error = ERRUSR;
        Usuario_t * u1 = (Usuario_t*)comp;
        Usuario_t * u2 = (Usuario_t*)dat_lista;

        if( !strcmp( u1->nombre, u2->nombre ) )
        {
                error = OK;
        }

        return error;
}
int __nombre_contra(void * comp, void * dat_lista)
{
        int error = ERRUSR;
        Usuario_t * u1 = (Usuario_t*)comp;
        Usuario_t * u2 = (Usuario_t*)dat_lista;

        if( strcmp( u1->nombre, u2->nombre )==0 )
        {
                if( strcmp( u1->contrasenia, u2->contrasenia )==0 )
                {
                        error = OK;
                }
                else
                {
                        error = ERRPASS;
                }
        }
        return error;
}
int realizar_menu_1(int socket, int peticion, Nodo_t ** lista_usuarios, pthread_mutex_t * semaforo)
{
        int error;
        char nombre[LARGO];
        char contra[LARGO];
        Usuario_t * usuario;
        
        if( peticion!=4 )
        {
                switch( peticion )
                {
                        case 1:
                                //recibo el nombre
                                recv(socket, nombre, LARGO, 0);

                                //recibo la contra
                                recv(socket, contra, LARGO, 0);
                                printf("Nombre: %s\nContrasenia: %s\n", nombre, contra);
                                //por ahoro ignoro la confirmacion
                                usuario = nuevo_usuario(nombre, contra, 0);   //agrego a la lista

                                error = buscar(lista_usuarios, (void *)usuario, __nombre);
                                //si es OK significa que encontro el usuario
                                if( error!=OK )
                                {
                                        pthread_mutex_lock( semaforo );
                                        agregar(lista_usuarios, usuario);
                                        cargar_usuarios(*lista_usuarios);
                                        pthread_mutex_unlock( semaforo );
                                }
                                //Envio el error al cliente
                                send(socket, &error, sizeof(int), 0);
                                break;
                        case 2:
                                //recibo el nombre
                                recv(socket, nombre, LARGO, 0);

                                //recibo la contra
                                recv(socket, contra, LARGO, 0);
                                printf("Nombre: %s\nContrasenia: %s\n", nombre, contra);
                                //por ahoro ignoro la confirmacion
                                usuario = nuevo_usuario(nombre, contra, 0);   //agrego a la lista

                                error = buscar(lista_usuarios, (void *)usuario, __nombre_contra);
                                printf("INICION SESION ERROR %d\n", error);
                                //Envio el error al cliente
                                send(socket, &error, sizeof(int), 0);

                                //libero el usuario que cree para hacer la verificacion
                                liberar_usuario(usuario);
                                break;
                        case 3:
                                //inicio sesion
                                //recibo el nombre
                                recv(socket, nombre, LARGO, 0);

                                //recibo la contra
                                recv(socket, contra, LARGO, 0);
                                printf("Nombre: %s\nContrasenia: %s\n", nombre, contra);

                                //por ahoro ignoro la confirmacion
                                usuario = nuevo_usuario(nombre, contra, 0);   //agrego a la lista

                                error = buscar(lista_usuarios, (void *)usuario, __nombre_contra);
                                send(socket, &error, sizeof(int), 0);
        
                                //verifico la sesion
                                if( error==OK )
                                {
                                        //recibo una confirmacion de eliminar
                                        recv(socket, &error, sizeof(int), 0);
                                        if( error==1 )
                                        {
                                                pthread_mutex_lock( semaforo );
                                                error = eliminar(lista_usuarios, (void *)usuario, __nombre, liberar_usuario);
                                                cargar_usuarios(*lista_usuarios);
                                                //envio el error de la funcion eliminar
                                                send(socket, &error, sizeof(int), 0);
                                                pthread_mutex_unlock( semaforo );
                                        }
                                }
                                liberar_usuario(usuario);
                                break;
                }
        }
        return error;        
}
