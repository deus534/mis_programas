#include <stdlib.h>
#include <sys/types.h>  //para abrir archivos
#include <sys/stat.h>   //para abrir archivos
#include <fcntl.h>      //para abrir archivos
#include <unistd.h>     //para leer archivos
#include <math.h>       //para el abs
#include <string.h>
#include <stdio.h>                        
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
                                datList->cant = 0;
                                datList->ciudad = datArch;
                                *error = agregar_ordenado(&lista, (void*)datList, cmp_idCiudad);
                        }
                        else *error = ERRMEM;
                }
                close(fd);
        }
        else *error=ERRFILE;
        
        return lista;
}
Nodo_t * leer_vuelos(int * error)
{
        Nodo_t * lista = NULL;
        Vuelo_t datArch;
        RVuelo_t * datList;
        int fd;

        *error = OK;
        fd = open(ARCH_VUELOS, O_RDONLY);

        if( fd!=-1 )
        {
                while( read(fd, &datArch, sizeof(Vuelo_t)) && (*error)==OK )
                {
                        datList = (RVuelo_t *)malloc( sizeof(RVuelo_t) );
                        if( datList )
                        {
                                datList->vuelo = datArch;
                                datList->rechazados = 0;
                                datList->aceptados = 0;
                                *error = agregar_ordenado(&lista, (void*)datList, cmp_idVuelo);
                        }
                        else *error = ERRMEM;
                }
                close(fd);
        }
        else *error=ERRFILE;
        
        return lista;
}
void analizar_espacio(Nodo_t * list_RV, Nodo_t * list_RC, Cliente_t * dato_cliente)
{
        RVuelo_t * r_vue;
        RCiudad_t * r_c1;
        RCiudad_t * r_c2;

        //busco el vuelo y obtengo la direccion de memoria del vuelo
        r_vue = (RVuelo_t *)buscar(list_RV, (void *)&dato_cliente->reserva.idVue, busq_idVuelo);

        if( r_vue )
        {
                //verifico el espacio disponible
                if( (r_vue->aceptados+dato_cliente->reserva.cant)<=r_vue->vuelo.cap )
                {
                        //acepto la reserva en el vuelo
                        r_vue->aceptados+=dato_cliente->reserva.cant;
                        //busco las ciudades(Aca no puede fallar el buscar ya seria problema del que escribe el archivo)
                        r_c1 = (RCiudad_t *)buscar(list_RC, (void *)&r_vue->vuelo.idOrg, busq_idCiudad);
                        r_c2 = (RCiudad_t *)buscar(list_RC, (void *)&r_vue->vuelo.idDest, busq_idCiudad);
                        //sumo las millas al cliente
                        dato_cliente->total_millas += abs(r_c1->ciudad.millas-r_c2->ciudad.millas)*dato_cliente->reserva.cant;
                        //sumo cantidad que eligieron de destino a ciudad de orien
                        r_c2->cant+=1;
                }
                else //rechazo la reserva
                {
                        //rechazo por cantidad de familias y no por unidad
                        r_vue->rechazados+=1;
                }
        }
}

void mostrarListaRVuelo(Nodo_t * list_RV)
{
        RVuelo_t * ptr;
        char msg[20];
        while (list_RV) 
        {
                ptr = (RVuelo_t *)list_RV->dato;
                if( ptr->vuelo.cap <= ptr->aceptados ) strcpy(msg, "INCOMPLETO");
                else strcpy(msg, "COMPLETO");
 
                printf("vuelo: %d tiene: %d rechazados y sale %s\n",ptr->vuelo.idVue, ptr->rechazados, msg);
                list_RV = list_RV->next;
        }
}
void mostrarListaRCiudad(Nodo_t * list_RC)
{
        RCiudad_t * ptr;
        while (list_RC)
        {
                ptr = (RCiudad_t *)list_RC->dato;
                printf("Ciudad: %s\tdestinados: %d\n",ptr->ciudad.descr,ptr->cant);
                list_RC = list_RC->next;
        }
}



// --------------------------------------------FUNCIONES DE NODOS_H-----------------------------------
int busq_idCiudad(void * idCiu, void * dato_lista)
{
        int * c_ic = (int *)idCiu;
        RCiudad_t * c_dl = (RCiudad_t *)dato_lista;
        return (*c_ic)-c_dl->ciudad.idCiu;
}
int busq_idVuelo(void * idVue, void * dato_lista)
{
        int * c_iv = (int *)idVue;
        RVuelo_t * c_dl = (RVuelo_t *)dato_lista;
        return (*c_iv)-c_dl->vuelo.idVue;
}
int cmp_idVuelo(void *dat1, void * dat2)
{
        RVuelo_t * rdat1 = (RVuelo_t *)dat1;
        RVuelo_t * rdat2 = (RVuelo_t *)dat2;
        return rdat1->vuelo.idVue - rdat2->vuelo.idVue;
}
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

void * buscar(Nodo_t * lista, void * busqueda, int(*crit_busq)(void *,void *))
{
        void * ret = NULL;

        while ( lista && !ret )
        {
                if( crit_busq(busqueda,lista->dato)==0 )
                {
                        ret = lista->dato;
                }
                lista = lista->next;
        }
        return ret;
}
