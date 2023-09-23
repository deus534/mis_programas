#include <stdio.h>

#include "../headers/structs.h"
#include "../headers/funciones.h"
#include "../headers/client.h"
#include "../headers/server.h"

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
	}
}
int realizar_menu_1( Usuario_t* us,int peticion )
{
	int nro_menu;
	//defino todas mis funciones de MENU_1 como puntero a funciones
	int ( *paf1[3] )( Usuario_t* ) = {agregar_usuario, iniciar_sesion, borrar_usuario};

	if( peticion==SALIDA_MENU_1 )
	{
		nro_menu = MENU_0;
	}
	else
	{
		nro_menu = paf1[peticion-1]( us );
	}

	return nro_menu;
}
int realizar_menu_2( Documento_t ** lista, int peticion )
{
	int nro_menu = MENU_2;

	if( peticion==SALIDA_MENU_2 )
	{
		nro_menu = MENU_1;
	}
	else if( peticion==1 )
	{
		nro_menu = buscar_documentos(lista);
	}
	else if ( peticion==2 )
	{
		nro_menu = subir_documento();
	}

	return nro_menu;
}

int realizar_menu_3( Documento_t ** lista, int peticion )
{
	int nro_menu = MENU_3;

	switch( peticion )
	{
		case SALIDA_MENU_3:
			nro_menu = MENU_2;
			break;
		case 1:
			nro_menu = mostrar_documentos_nombre(lista);
			break;
		case 2:
			nro_menu = mostrar_documentos_autor(lista);
			break;
		case 3:
			nro_menu = mostrar_un_documento();
			break;
		case 4:
			nro_menu = descargar_un_documento();
			break;
		case 5:
			nro_menu = actualizar_documentos(lista);
			break;
	}

	return nro_menu;
}
void iniciar_menu(int * nro_menu, int peticion, Usuario_t * us, Documento_t ** lista)
{
	if( *nro_menu==MENU_1 )
	{
		if( peticion>0 && peticion<=SALIDA_MENU_1 )
		{
			*nro_menu = realizar_menu_1( us, peticion );
		}
		else
		{
			printf("++++++++INTRODUCE UNA OPCION CORRECTA++++++++\n");
		}
	}
	else 
	{
		if ( *nro_menu==MENU_2 )
		{
			if( peticion>0 && peticion<=SALIDA_MENU_2 )
			{
				*nro_menu = realizar_menu_2( lista, peticion );
			}
			else
			{
				printf("++++++++INTRODUCE UNA OPCION CORRECTA++++++++\n");
			}
		}
		//por descarte entro al MENU_3
		else 
		{	
			if( peticion>0 && peticion <= SALIDA_MENU_3 )
			{
				*nro_menu = realizar_menu_3( lista, peticion );
			}
			else
			{
				printf("++++++++INTRODUCE UNA OPCION CORRECTA++++++++\n");
			}	
		}
	}
}


//MENU_1
int agregar_usuario(Usuario_t* us)
{
	int menu;
	int val;

	val = alta_de_usuario(us);

	if( val==ERRUSR )
	{
		printf("Usuario existente\n");
	}
	else
	{
		printf("Usuario agregado correctamente\n");
		menu = MENU_2;
	}

	return menu;
}

int iniciar_sesion(Usuario_t* us)
{
	int nro_menu = MENU_1;
	int val;

	val = validar_usuario(us);

	if( val== ERRUSR )
	{
		printf("ERROR no existe usuario\n");
	}
	else
	{
		if( val==ERRPASS )
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

int borrar_usuario(Usuario_t* us)
{
	int nro_menu;
	int val;
	int elim;
	
	nro_menu = iniciar_sesion(us);

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
			val = baja_de_usuario(us);
			
			if( val==OK )
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

//MENU_2
//para esto si no me da memoria puedo retornar MENU_0 para finalizar el programa(creo)
int buscar_documentos(Documento_t ** lista)
{
	return MENU_3;
}
int subir_documento()
{
	return MENU_2;
}

//MENU_3

int mostrar_documentos_nombre(Documento_t ** lista)
{
	return MENU_3;
}
int mostrar_documentos_autor(Documento_t ** lista)
{
	return MENU_3;
}
int mostrar_un_documento()
{
	return MENU_3;
}
int descargar_un_documento()
{
	return MENU_3;
}
int actualizar_documentos(Documento_t **lista)
{
	return MENU_3;
}
