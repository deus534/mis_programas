#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <signal.h>

#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "structs.h"
#include "funciones.h"

int establecer_conexion()
{
        FILE * file;
        char buffer[LON_MAX];

        //Variables para la conexion
	int misocket, resu;
	struct sockaddr_in tudireccion;
	struct hostent * direccion;
       
        file = fopen(ARCH_CLIENTE, "r");
        if( file )
        {
                fgets(buffer, LON_MAX, file);

                misocket = socket(AF_INET, SOCK_STREAM, 0);
                if (misocket != -1)
                {
                        printf("Socket abierto\n");

                        direccion = gethostbyname(strtok(buffer,"|"));

                        tudireccion.sin_family = AF_INET;
                        tudireccion.sin_port = htons(atoi( strtok(NULL,"|") ));
                        memcpy(&(tudireccion.sin_addr), direccion->h_addr, 4);
                        memset(tudireccion.sin_zero, 0, 8);

                        resu = connect(misocket, (struct sockaddr *) &tudireccion, sizeof(tudireccion));
                        if(resu)
                        {
	                        misocket = -1;
                        }
                }
                fclose(file);
        }
        return misocket;
}
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

void mostrar_menu(int nro_menu)
{
	switch( nro_menu )
	{
		case MENU_1:
			printf("1) Agregar usuario\n");
			printf("2) Iniciar sesion\n");
			printf("3) Borrar usuario\n");
			printf("4) Salir\n");
			break;
		case MENU_2:
			printf("1) Buscar documento\n");
			printf("2) Subir documento\n");
			printf("3) Volver\n");
			break;
		case MENU_3:
			printf("1) Mostrar documentos ordenados por nombre\n");
			printf("2) Mostrar documentos ordenados por autor\n");
			printf("3) Mostrar un documento\n");
			printf("4) Descargar un documento\n");
			printf("5) Actualizar lista de documentos\n");
			printf("6) Volver\n");
			break;
		case MENU_ROOT:
			printf("1) Buscar documento\n");
			printf("2) Subir documento\n");
			printf("3) Eliminar documento\n");
			printf("4) Volver\n");
			break;
	}
}

int leer_cadena(char* cad,int lon_max  )
{
	fgets(cad, lon_max, stdin);
	if( cad[strlen(cad)-1]=='\n' )
	{
		cad[strlen(cad)-1] = '\0';
	}
	else
	{
		//si leo demas, limpio mi buffer de teclado
		__fpurge(stdin);
	}
	return strlen(cad);
}
int leer_peticion()
{
	char cad[10];
	int peticion = -1;
	int lon;

	lon = leer_cadena(cad, 10);	
	
	if( cad[0]>='0' && cad[0]<='9' && lon==1 )
	{
		peticion = cad[0] - '0' ;
	}
	return peticion;
}
char root13(char c)
{
	char ret;

	if( c>='A' && c>='N')
	{
		ret = c - 13;
	}
	else
	{
		ret = c + 13;
	}
	if( c>='a' && c>='n' )
	{
		ret = c - 13;
	}
	else
	{
		ret = c + 13;
	}
	return ret;
}
void encriptar_contrasenia(char* org,char* encriptado)
{
	int lon = strlen(org);
	int i;
	char aux;

	for (i = 0; i < lon; ++i)
	{
		aux = *(org+i);
		if( (aux>='A' && aux<='Z') || (aux>='a' && aux<='z') )
		{
			*(encriptado+i) = root13(aux);
		}
		else
		{
			if( aux>='5' )
			{
				*(encriptado+i) = aux-5;
			}
			else
			{
				if( aux<='9' )
				{
					*(encriptado+i) = aux+5;
				}
				else
				{
					*(encriptado+i) = aux;
				}
			}
		}
	}
	*(encriptado+i) = '\0';
}
int agregar_usuario( int socket, int * nivel)
{
	int menu = MENU_1;
	int error = OK;
        
        //recibo del servidor si pudo o no agregar al usuario
        recv(socket, &error, sizeof(int), 0);

	if( error!=OK )
	{
                printf("Usuario agregado correctamente\n");
                menu = MENU_2;
	}
	else
	{
		printf("Usuario existente\n");
	}	
	return menu;
}
int iniciar_sesion( int socket, int *nivel )
{
	int nro_menu = MENU_1;
	int error;

        //recibo del servidor si pudo o no confirmar la existencia del usuario
        recv(socket, &error, sizeof(int), 0);

	if( error==ERRUSR || error==ERROR )
	{
		printf("ERROR no existe usuario\n");
	}
	else
	{
		if( error==ERRPASS )
		{
			printf("ERROR contrasenia incorrecta\n");
		}
		else
		{
                        nro_menu = MENU_2;
		}
	}
	return nro_menu;
}
int borrar_usuario( int socket, int * nivel )
{
	int nro_menu;
	int error = OK;
	int elim;
	
	nro_menu = iniciar_sesion( socket, nivel );

	//pudo validar y inicio sesion
	if( nro_menu == MENU_2 )
	{
		printf("Confirma que deseas eliminar tu usuario\n");
		printf("1) SI\n");
		printf("2) NO\n");
		//lee por consola la baja de usuario
		elim = leer_peticion();

		if( elim == 1 )
		{
                        //SERVIDOR: envio al servidor la baja de usuario
                        send(socket, &elim, sizeof(int), 0);

                        //SERVIDOR: recibo la confirmacion de la eliminacion
                        recv(socket, &error, sizeof(int), 0);

                        if( error==OK )
			{
				printf("Usuario borrado\n");
			}
			else
			{
				printf("ERROR no se pudo borrar el usuario\n");
			}
			nro_menu = MENU_1;
		}
		else
		{
			if( elim==-1 )
			{
				printf("Introduce una opcion correcta\n");
			}
		}
	}
	return nro_menu;
}
int realizar_menu_1( int peticion, int * nro_menu, int socket, int * nivel)
{
        int error = OK;
        char usuario[LON_MAX];
        char contrasenia[LON_MAX];
        char encriptado[LON_MAX];
        
        *nro_menu = MENU_0;
        
        if( peticion!= 4)
        {
                printf("Introduce tu usuario: ");
                leer_cadena(usuario, LON_MAX);

                printf("Introduce tu contrasenia: ");
                leer_cadena(contrasenia, LON_MAX);
                
                encriptar_contrasenia( contrasenia, encriptado );

                //envio el usuario
                send(socket, usuario, LON_MAX, 0);
                
                //envio la contrasenia
                send(socket, encriptado, LON_MAX, 0);
                
                switch( peticion )
                {
                        //en todas las funciones recibo el nivel del usuario,( el servidor la envia)
                        case 1:
                                *nro_menu = agregar_usuario( socket, nivel );
                                break;
                        case 2:
                                *nro_menu = iniciar_sesion( socket, nivel );
                                break;
                        case 3:
                                *nro_menu = borrar_usuario( socket, nivel );
                                break;
                }
        }
	return error;
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
		//valido los 3 pedidos de memoria
		
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

int buscar_documentos(Nodo_t ** lista, int * error, int socket)
{
	char cod[LON_MAX] ;
	char nom[LON_MAX] ; 
	char aut[LON_MAX] ;
	int anio ;
        int condicion = OK;

	Documento_t * nuevo;
        
        //recibo condicion de while
        while( condicion==OK )
        {
                //recibo la condicion de salida
                printf("RECIBO LA CONDICION\n");
                recv(socket, &condicion, sizeof(int), 0);

                if( condicion==OK )
                {
                        //empiezo a recibir los datos
                        //recivo el codigo
                        recv(socket, cod, LON_MAX, 0);
                        //recibo el nombre
                        recv(socket, nom, LON_MAX, 0);
                        //recibo el autor
                        recv(socket, aut, LON_MAX, 0);
                        //recibo el anio
                        recv(socket, &anio, sizeof(int), 0);

                        nuevo = nuevo_documento(cod, nom, aut, anio);
                        if( nuevo )
                        {
                                *error = agregar(lista, (void*)nuevo);
                        }
                        else
                        {
                                *error = ERRMEM;
                        }
                }
        }
	return MENU_3;
}
void subir_documento(Nodo_t ** lista, int * error, int socket)
{
	char codigo[LON_MAX];
	char nombre[LON_MAX];
	char autor[LON_MAX];
	char anio[10];
        int an;
	Documento_t * nuevo;

	printf("Introduce el codigo: ");
	leer_cadena(codigo, LON_MAX);
	printf("Introduce el nombre: ");
        leer_cadena(nombre, LON_MAX);
        printf("Introduce el autor: ");
        leer_cadena(autor, LON_MAX);
        printf("Introduce el anio: ");
        leer_cadena(anio, 10);
        
        //envio el codigo al servidor y este lo valida
        send(socket, codigo, LON_MAX, 0);
        
        //recibo la validacion del codigo
        recv(socket, error, sizeof(int), 0);

        if( *error == OK )
        {
                an = atoi(anio);
                nuevo = nuevo_documento(codigo,nombre,autor,an);
                //OMITO VERIFICACION DEMEMORIA
                *error = agregar(lista,(void*)nuevo);
                
                //SERVIDOR: solicito el nombre del archivo local para subir el documento
                //POR AHORA OMITO ESTO

                //envio el nombre
                send(socket, nombre, LON_MAX, 0);
                //envio el autor
                send(socket, autor, LON_MAX, 0);
                //envio el anio
                send(socket, &an, sizeof(int), 0);
        }
}

int realizar_menu_2( Nodo_t ** lista_documentos, int peticion, int * nro_menu, int socket )
{
	int error = OK;
	*nro_menu = MENU_1;
	
	switch( peticion )
	{
		case 1:
			*nro_menu = buscar_documentos(lista_documentos, &error, socket);
			break;
		case 2:
			subir_documento(lista_documentos,&error, socket);
                        *nro_menu = MENU_2;
			break;
	}
	return error;
}
int cmp_nombre( void * dat1, void * dat2 )
{
	int err = ERROR;
	Documento_t * d_dat1 = (Documento_t*)dat1;
	Documento_t * d_dat2 = (Documento_t*)dat2;
	if( strcmp(d_dat1->nombre,d_dat2->nombre)==0 )
	{
		err = OK;
	}
	return err;
}
int cmp_autor( void * dat1, void * dat2 )
{
	int err = ERROR;
	Documento_t * d_dat1 = (Documento_t*)dat1;
	Documento_t * d_dat2 = (Documento_t*)dat2;
	if( strcmp(d_dat1->autor, d_dat2->autor)==0 )
	{
		err = OK;
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

void mostrar_documentos(Nodo_t * lista, int criterio)
{
	int i;
	int (*fun_cmp)(void *,void *);
	char msg[30];
	Nodo_t * aux_lista = lista;
	Documento_t * dato_aux;
	//veo que criterio para ordenar
	if( criterio==NOMBRE )
	{
		fun_cmp = cmp_nombre;
		strcpy(msg,"ORDENADO POR NOMBRE");
	}
	else
	{
		fun_cmp = cmp_autor;
		strcpy(msg,"ORDENADO POR AUTOR");
	}
	//ordeno el documento
	ordenar(lista,fun_cmp);
	
	//muestro los documentos
	printf("+++++++++++++++++++++++++++\n\n");
	printf("%s\n",msg);
	printf("\t\t%-13s\t%s\t%13s\t\t%s\n","NOMBRE","CODIGO", "AUTOR","ANIO");
	for(i=1; aux_lista;i++ )
	{
		dato_aux = (Documento_t *)aux_lista->dato;

		printf("\t%d) %-20s\t",i, dato_aux->nombre);
		
		printf("(%s)\t", dato_aux->codigo);

		printf("%-10s\t", dato_aux->autor);

		printf("%d\n", dato_aux->anio);

		aux_lista = aux_lista->next;
	}
	printf("\n\n+++++++++++++++++++++++++++\n");
}
void mostrar_descargar_documento(Nodo_t * lista,char* cod, int val)
{
	int err;
        
        //SERVIDOR: Pido al servidor si tiene el documento
	err = OK;

	if( err==ERROR )
	{
		printf("ERROR no existe el codigo\n");
	}
	else
	{
		//codigo encontrado y se hara lo de mostrar
		//SERVIDOR: comienza el envio del documento
                if( val==MOSTRAR )
		{
			printf("+++++++++AQUI SE MUESTRA EL DOCUMENTO++++++\n");	
		}
		else
		{
			printf("+++++++++AQUI SE DESCARGA EL DOCUMENTO++++++\n");	
		}
	}
	return;
}

int realizar_menu_3( Nodo_t ** lista_documentos, int peticion, int * nro_menu,int socket )
{
	int error = OK;
	char buffer_cod[9];

	*nro_menu = MENU_3;
	
	switch( peticion )
	{
		case 1:
			mostrar_documentos(*lista_documentos, NOMBRE);
			break;
		case 2:
			mostrar_documentos(*lista_documentos, AUTOR);
			break;
		case 3:
                        printf("Introduce el codigo: ");
                        leer_cadena(buffer_cod, 9);
			mostrar_descargar_documento(*lista_documentos,buffer_cod, MOSTRAR);
			break;
		case 4:
                        printf("Introduce el codigo: ");
                        leer_cadena(buffer_cod, 9);
			mostrar_descargar_documento(*lista_documentos,buffer_cod, DESCARGAR);
			break;
		case 5:
			buscar_documentos(lista_documentos,&error, socket);
			break;
		case 6:
                        *nro_menu = MENU_2;
			break;
	}
	return error;
}
