#include <stdio.h>

#include "../headers/funciones.h"
#include "../headers/structs.h"
#include "../headers/client.h"

int main(int argc, char* argv[])
{
	int nro_menu = MENU_1;
	int peticion;
	Documento_t** lista;
	Usuario_t * us;

	if( argc>1 )
	{
		us = nuevo_usuario(argv[1], argv[2], USR);

		if( us )
		{
			//menu_0 sera mi condicion de finalizacion del programa
			while( nro_menu!=MENU_0 )
			{
				mostrar_menu(nro_menu);

				peticion = leer_peticion();

				iniciar_menu(&nro_menu, peticion, us, lista);

			}
		}
		else
		{
			printf("ERROR no tengo memoria para crear Usuarios\n");
		}

	}
	else
	{
		printf("no puedo hacer nada\n");
	}
	return 0;
}
