#include "../headers/funciones.h"
#include "../headers/structs.h"
#include "../headers/client.h"


//pensarlo como hacer todo esto y ver si funciona o se va todo
int leer_peticion()
{
	int num;

	fgets()

	return num;
}

int leer_baja_usuario();

//encripta un caracter con root13
char root5(char c)
{
	char ret;

	if( c>='5' )
	{
		ret = c-5;
	}
	else
	{
		ret = c+5;
	}
	return ret;
}
char root13(char c)
{
	char ret;

	if( c>='N' || c>='n' )
	{
		ret = c - 13;
	}
	else
	{
		ret = c + 13;
	}
	return ret;
}

void encriptar_contrasenia(char* cont,char* encriptado)
{
	int lon = strlen(cont);
	int i;
	char aux;

	for (i = 0; i < lon; ++i)
	{
		aux = *(cont+i);
		if( (aux>='A' && aux<='Z') || (aux>='a' && aux<='z') )
		{
			*(encriptado+i) = root13(aux);
		}
		else
		{
			if( aux>= '0' && aux<='9' )
			{
				*(encriptado+i) = root5(aux);
			}
			else
			{
				*(encriptado+i) = aux;
			}
		}
	}
	*(encriptado+i) = '\0';
}

//el nom puede ser un valor por teclado.... x lo cual no pedi memoria en ninguna parte para el
Usuario_t* nuevo_usuario(char* nom, char* cont, int nivel)
{
	Usuario_t* us;
	char* encrip;

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
			encriptar_contrasenia(cont, us->contrasenia );
			us->nivel = nivel;
		}
		else
		{
			//no me pudieron dar memoria para los char*
			us == NULL;
		}
	}
	return us;
}


