#include <stdlib.h>
#include <structs.h>
#include <funciones.h>

Nodo_t * leer_equipos(int * error)
{
        Nodo_t * lista = NULL;
        Equipo_t datArch;
        Equipo_t * datList = NULL;
        int fd;

        *error = OK;
        fd = open(ARCH_RESULTADOS, O_RDONLY);

        if( fd!=-1 )
        {
                while( read(fd, &datArch, sizeof(Resultado_t)) && (*error)==OK )
                {
                        datList = (Equipo_t *)malloc( sizeof(Equipo_t) );
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

Equipo_t * buscar_equipo( Nodo_t * lista, int idEq )
{
        Equipo_t * resu = NULL;

        while( lista && resu!=NULL )
        {
                if( lista->dato->idEq==idEq )
                {
                        resu = lista->dato;
                }
                lista = lista->next;
        }
        return resu;
}

Estadio_t * buscar_agregar_estadio( Nodo_t * lista, char * est )
{
        Estadio_t * resu = NULL;

        while( lista && resu==NULL )
        {
                if( strcmp(lista->dato->estadio, est)==0 ) resu = lista->dato;
                lista = lista->next;
        }
        if( !resu )
        {
                resu = (Estadio_t *)malloc(sizeof(Estadio_t));
                if( resu ) agregar( lista, (void *)resu );
        }
        return resu;
}
void actualizar_equipos( Nodo_t * lista)
{
        Equipo_t * aux;
        int fd;

        fd = open(ARCH_EQUIPOS, O_WRONLY);
        if( fd!=-1 )
        {
                while( lista )
                {
                        aux = lista->dato;
                        write(fd, aux);                        
                        lista = lista->next;
                }
        }
}
