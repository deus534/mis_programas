#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define MAX 100

typedef struct usuario
{
	char nombre[100];
	char pass[100];
}us_t;

int crear_pstruct (us_t ** * inicio, FILE * fs);

int main()
{
	FILE * f;
	us_t ** lista_usuarios = NULL;
	

	f = fopen( "usuarios.lst", "r" );
	
	crear_pstruct( &lista_usuarios, f );
        
        for(int i=0;lista_usuarios[i];i++)
        {
		printf ("\nEl usuario es: %s\nLa contraseña es: %s\n",((lista_usuarios)[i])->nombre , ((lista_usuarios)[i])->pass );
        }

	return 0;
}
int crear_pstruct (us_t ** * inicio, FILE * fs)
{
	//us_t ** recorrer = NULL;
	us_t *aux=NULL;
	int l_usuario = strlen ("Usuario:");
	int l_contrasena = strlen ("contraseña:");
	int cont= 0, salida = OK, i = 0;

	if (!ferror (fs))
	{
		*inicio = (us_t **) malloc (sizeof (us_t *)); 
		aux = (us_t *) malloc (sizeof (us_t )); 

		fseek (fs , l_usuario , SEEK_SET);
		fgets (aux->nombre,MAX,fs);

		while (!feof(fs))
		{

			fseek (fs , l_contrasena , SEEK_CUR);
			fgets (aux->pass , MAX-1 , fs);

			(*inicio)[cont] = aux;

			cont ++;

			(*inicio) = (us_t **) realloc ( (*inicio) ,sizeof (us_t *) * (cont + 1)); 
			aux = (us_t *) malloc (sizeof (us_t )); 

			fseek (fs , l_usuario , SEEK_CUR);
			fgets (aux->nombre,MAX-1,fs);
		}

		(*inicio)[cont] = NULL;
	}

	i=0;
	while (*inicio[i])
	{
                if( (*inicio[i])->nombre==NULL ||  (*inicio[i])->pass==NULL || (*inicio[i]) )
                {
                        printf("%d) ",i);
                        printf("ES NULL\n");
                }
		printf ("\nEl puntero %d vale %p \n", i, &((*inicio)[i]));
		printf ("\nEl usuario es: %s \n La contraseña es: %s\n",((*inicio)[i])->nombre , ((*inicio)[i])->pass );
		i++;
	}
	return salida;
}
