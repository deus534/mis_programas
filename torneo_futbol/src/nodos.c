

int agregar( Nodo_t ** lista, void * dato )
{
        Nodo_t * nuevo = NULL;
        Nodo_t * aux = *lista;
        int error = OK;

        nuevo = (Nodo_t *)malloc( sizeof(Nodo_t) );
        
        if( nuevo )
        {
                nuevo->dato = dato;
                nuevo->next = NULL;
                if( *lista )
                {
                        while( aux ) aux = aux->next;
                        aux->next = nuevo;
                }
                else *lista = nuevo;
        }
        else error = ERRMEM;

        return error;
}

int borrar_primero( Nodo_t ** lista, int (*liberar_dato)(void *) )
{
        Nodo_t * aux = *lista;
        int error = OK;
        
        if( *lista )
        {
                *lista = *lista->next;
                liberar_dato( aux->dato );
                free(aux);
        }

        return error;
}
