#include <stdio.h>
#include <structs.h>
#include <nodos.h>
#include <funciones.h>

int main()
{
        int error;
        Nodo_t * list_ciudades = leer_ciudades(&error);

        if( list_ciudades )
        {
                printf("No esta vacia\n");
        }
        else
        {
                printf("Dale flaco esta en null perrin\n");
        }
        return 0;
}
