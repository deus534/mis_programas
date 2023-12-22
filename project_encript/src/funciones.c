
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <funciones.h>

int find_rand(int * rand_list, int random,int largo)
{
        int error = ERROR;
        int i;

        for( i=0; i<largo; i++ )
        {
                if( rand_list[i]==random ) error=OK;
        }
        return error;
}

char * encriptar_dato(char * cadena, int * codigo)
{
        char * enc = NULL;
        int lon = strlen(cadena);
        int mascara = 0x80;
        int i;
        int j;

        //trabajo con mascaras la encriptacion de mis datos
        enc = (char *)malloc( lon+1 );
        codigo = (int *)malloc( sizeof(int)*lon );
        if( enc && codigo )
        {
                for(i=0;i<lon;i++)
                {
                        codigo[i] = rand() % (lon);
                        for(j=0;codigo[i]!=codigo[j];j++)
                        {

                        }
                        printf("vuelta nro %d: %c, %d\n",i, cadena[i], codigo[i]);
                }
        }
        else enc=NULL;
        return enc;
}
