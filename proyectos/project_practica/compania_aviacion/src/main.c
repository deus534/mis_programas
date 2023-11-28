#include <stdio.h>
#include <structs.h>    //archivo de errores y estructuras
#include <nodos.h>      //funciones relacionadas a nodos
#include <funciones.h>  //funciones generales
#include <sys/types.h>  //para abrir archivos
#include <sys/stat.h>   //para abrir archivos
#include <fcntl.h>      //para abrir archivos
#include <unistd.h>     //para leer archivos

int main()
{
        int errorVue, errorCiu, error;
        int fd;
        Reserva_t datArch;
        Cliente_t dato;
        Nodo_t * list_RC = leer_ciudades(&errorVue); //lista de RCIUDADES
        Nodo_t * list_RV = leer_vuelos(&errorCiu);   //lista de RVUELOS
        
        if( list_RV==NULL ) printf("estas siento grosero\n");
        if( list_RC==NULL ) printf("estas siento grosero\n");

        if( errorCiu==OK && errorVue==OK )
        {
                error = OK;
                fd = open(ARCH_RESERVAS, O_RDONLY);

                if( fd!=-1 )
                {
                        while( read(fd, &datArch, sizeof(Reserva_t)) && error==OK )
                        {
                                dato.reserva = datArch;
                                dato.total_millas = 0;

                                //1)busco el vuelo
                                //2)Verifico que el vuelo tenga espacio para esta reserva
                                //2.1)SI hay espacio -> agrego el vuelo y hago 3)
                                //2.2)NO hay espacio -> sumo cantidad de rechazados
                                //3)tomo el abs de la diferncia de millas entre origen y destino y la sumo a sus millas
                                analizar_espacio(list_RV, list_RC, &dato);
                                printf("Procces complete\n");
                                //4)mostrar Datos
                                printf("Cliente: %d millas: %d\n", dato.reserva.idCli, dato.total_millas);
                        }
                        mostrarListaRVuelo(list_RV);
                        mostrarListaRCiudad(list_RC);
                        close(fd);
                }
                else error=ERRFILE;
        }
        else printf("Error\n");
        return 0;
}
