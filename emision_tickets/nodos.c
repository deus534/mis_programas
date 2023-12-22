#include <stdlib.h>
#include <errores.h>

//retorna error
int agregar( Nodo_t ** lista, void * dato )
{
        Nodo_t * aux_lista = *lista;
        Nodo_t * nuevo = NULL;
        int error = ERRMEM;
        
        nuevo = (Nodo_t *)malloc( sizeof(Nodo_t) );
        if( nuevo )
        {
                nuevo->dato = dato;
                nuevo->next = NULL;
                if( aux_lista )
                {
                        while( aux_lista ) aux_lista = aux_lista->next; 
                        aux_lista->dato = nuevo;
                }
                else *lista = nuevo;
        }
        return error;
}
//puede que falte algunas cosas
int eliminar(Nodo_t ** lista, void * dato_elim, int (*fun_cmp)(void *,void *), void (*liberar)(void *) )
{
        Nodo_t * aux_lista = *lista;
        Nodo_t * ant = NULL;
        Nodo_t * aux = NULL;

        if( aux_lista )
        {
                while ( aux_lista && aux )
                {
                        if( fun_cmp(dato_elim, aux_lista->dato)==0 ) aux = aux_lista;
                        ant = aux_lista;
                        aux_lista = aux_lista->next;
                }
                if( aux )
                {
                        ant->next = aux_lista->next;
                        liberar(aux_lista->dato);
                        free(aux_lista);
                }
        }
}
