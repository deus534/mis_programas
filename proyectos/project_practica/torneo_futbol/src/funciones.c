#include <stdlib.h>
#include <structs.h>
#include <funciones.h>

Nodo_t * leer_equipos(int * error)
{
        Nodo_t * lista = NULL;
        Resultado_t datArch;
        Resultado_t * datList = NULL;
        int fd;

        *error = OK;
        fd = open(ARCH_RESULTADOS, O_RDONLY);

        if( fd!=-1 )
        {
                while( read(fd, &datArch, sizeof(Resultado_t)) && (*error)==OK )
                {
                        datList = (Resultado_t *)malloc( sizeof(Resultado_t) );
                        if( datList )
                        {
                                *datList = datArch;
                                *error = agregar(&lista, (void*)datList);
                        }
                        else *error = ERRMEM;
                }
                close(fd);
        }
        else *error=ERRFILE;
        
        return lista;
}

