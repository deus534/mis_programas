#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define MAX 100

typedef struct usuario
{
	char nombre[20];
	char pass[20];
}us_t;

int crear_pstruct (us_t ** * inicio, FILE * fs);

int main()
{
	printf("Hola mundo \n");
	FILE * f;
	us_t ** lista_usuarios = NULL;
	

	f = fopen( "usuarios.lst", "r" );
	
	crear_pstruct( &lista_usuarios, f );


	return 0;
}
int crear_pstruct (us_t ** * inicio, FILE * fs)
{
	us_t ** recorrer = NULL;
	us_t *aux=NULL;
	int l_usuario = strlen ("Usuario:");
	int l_contrasena = strlen ("contraseña:");
	int cont= 0, salida = OK, i = 0;

		printf("entra aqui\n");
	if (!ferror (fs))
	{
		recorrer = (us_t **) malloc (sizeof (us_t *)); 
		aux = (us_t *) malloc (sizeof (us_t )); 
		

		fseek (fs , l_usuario , SEEK_SET);
		fgets (aux->nombre,MAX,fs);

		while (!feof(fs))
		{

			fseek (fs , l_contrasena , SEEK_CUR);
			fgets (aux->pass , MAX-1 , fs);

			recorrer [cont] = aux;

			cont ++;

			recorrer = (us_t **) realloc (recorrer,sizeof (us_t *) * (cont + 1)); 
			aux = (us_t *) malloc (sizeof (us_t )); 

			fseek (fs , l_usuario , SEEK_CUR);
			fgets (aux->nombre,MAX-1,fs);
			printf ("\n %s %d\n",__FILE__, __LINE__);
		}

		recorrer [cont] = NULL;
		inicio = (&recorrer);
		printf ("\n %s %d\n",__FILE__, __LINE__);
	}


	i=0;
	while (recorrer[i])
	{
		printf ("\nEl puntero %d vale %p \n", i, &*recorrer[i]);
		printf ("\nEl usuario es: %s \n La contraseña es: %s\n",recorrer[i]->nombre , recorrer[i]->pass );
		i++;
	}

	i=0;
	while (*inicio[i])
	{
		printf ("\nEl puntero %d vale %p \n", i, &((*inicio)[i]));
		printf ("\nEl usuario es: %s \n La contraseña es: %s\n",((*inicio)[i])->nombre , ((*inicio)[i])->pass );
		i++;
	}

	return salida;
}
