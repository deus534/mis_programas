
#include <errores.h>
#include <funciones.h>

Nodo_t * leer_rubros()
{
        FILE * f;
        char buffer[LARGO];

        f = fopen(ARCH_RUBROS, "r");

        if( fd!=-1 )
        {
                while( !feof(f) )
                {
                        fgets(buffer, LARGO, f);

                }
        }
}
