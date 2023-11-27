#include <stdlib.h>
#include <sys/types.h>  //para abrir archivos
#include <sys/stat.h>   //para abrir archivos
#include <fcntl.h>      //para abrir archivos
#include <unistd.h>     //para leer archivos
#include <structs.h>
#include <nodos.h>
#include <funciones.h>

Nodo_t * leer_ciudades(int * error)
{
        Nodo_t * lista = NULL;
        Ciudad_t datArch;
        RCiudad_t * datList;
        int fd;

        *error = OK;
        fd = open(ARCH_CIUDADES, O_RDONLY);

        if( fd!=-1 )
        {
                while( read(fd, &datArch, sizeof(Ciudad_t)) && (*error)==OK )
                {
                        datList = (RCiudad_t *)malloc( sizeof(RCiudad_t) );
                        if( datList )
                        {
                                *error = agregar_ordenado(&lista, (void*)datList, cmp_idCiudad);
                        }
                        else *error = ERRMEM;
                }
                close(fd);
        }
        else *error=ERRFILE;
        
        return lista;
}





// --------------------------------------------FUNCIONES DE NODOS_H-----------------------------------
int cmp_idCiudad(void * p1, void * p2)
{
        RCiudad_t * p1_r = (RCiudad_t*)p1;
        RCiudad_t * p2_r = (RCiudad_t*)p2;

        return p1_r->ciudad.idCiu - p2_r->ciudad.idCiu;
}
int agregar(Nodo_t ** lista, void * pdat)
{
	Nodo_t * nuevo;
	Nodo_t * aux = *lista;
	int error = OK;

	nuevo = (Nodo_t*)malloc( sizeof(Nodo_t) );
	if( nuevo )
	{
                nuevo->dato = pdat;
                nuevo->next = NULL;
		if( *lista )
		{
			while( aux->next ) aux = aux->next; //llego al final de la lista
			aux->next = nuevo; //agrego el dato
		}
		else *lista = nuevo; //si lista vacia->agrego primer elemento
	}
        else error = ERRMEM;
        return error;
}
int agregar_ordenado(Nodo_t ** lista, void * dato, int(*crit_ord)(void *, void *) )
{
        int error = OK;
        Nodo_t * aux = *lista;
        Nodo_t * nuevo = NULL;

        nuevo = (Nodo_t *)malloc( sizeof(Nodo_t) );

        if( nuevo )
        {
                nuevo->dato = dato;
                nuevo->next = NULL;
                if( aux==NULL || crit_ord(dato, (*lista)->dato)<0 )  //agrego al principio
                {
                        nuevo->next = aux;
                        *lista = nuevo;
                }
                else
                {
                        while( aux->next && crit_ord(aux->next->dato,dato)<0 ) aux = aux->next;
                        //agrego al medio o final
                        if( aux->next ) nuevo->next = aux->next;

                        aux->next = nuevo;
                }
        }
        else error=ERRMEM;

        return error;
}

