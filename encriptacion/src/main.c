#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <funciones.h>

int main(int argc, char * argv[])
{
        int i;
        char * encriptado;
        int * codigo;
        srand(time(NULL));
        if( argc>1 )
        {
               for(i=1; i<argc;i++)
               {
                       //encripta la cadena que se le pasa por argumento de main
                       encriptado = encriptar_dato(argv[i], codigo);
               }
        }
        else printf("Introduce lo que queres encriptar\n");
        return 0;
}
