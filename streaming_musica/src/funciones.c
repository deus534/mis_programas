
#include <errores.h>
#include <funciones.h>

void comparar_agregar( RArtista_t * vec, int * largo, RArtista_t dato )
{
        RArtista_t * aux = vec;
        RArtista_t aux_dato;
        int i;

        if( (*largo)==LARGO_RART )
        {
                for( i=(*largo)-1; i>=0; i-- )
                {
                        if( dato.rep75_100 > (aux+i)->rep75_100 )
                        {
                                aux_dato = *(aux+i);
                                aux[i] = dato;
                                if( i!=((*largo)-1) ) aux[i+1] = aux_dato;
                        }
                        else i = -1;
                }        
        }
        else 
        {
                aux[(*largo)] = dato;
                (*largo)++;
        }
        vec = aux;
}

