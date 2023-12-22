#include <stdio.h>
#include <structs.h>
#include <fcntl.h>
#include <unistd.h>
#include <funciones.h>

int main(int argc, char *argv[])
{
        Nodo_t * lista_equipos = NULL;
        Nodo_t * lista_estadios = NULL;
        Resultado_t dato;
        Equipo_t * eq1;
        Equipo_t * eq2;
        Estadio_t * est;
        int fd;

        fd = open(ARCH_RESULTADOS, O_RDONLY);
        if( fd!=-1 )
        {
                while( read(fd, &dato, sizeof(dato)) ) 
                {
                        //Busco los equipos en la lista de equipos
                        eq1 = buscar_equipo( lista_equipos, dato.idEq1 );               
                        eq2 = buscar_equipo( lista_equipos, dato.idEq2 );               

                        //busco o agrego(si no existe) en la lista de estadios
                        est = buscar_agregar_estadio( lista_estadios, dato.estadio );

                        if( eq1 && eq2 )
                        {
                                est->partidos+=1;
                                if( dato.codRes==0 )  //Empate
                                {
                                        eq1->puntos+=1;
                                        eq2->puntos+=1;
                                        est->empatados+=1;
                                }
                                else if ( dato.codRes<0 )  //gana el equpo 1
                                {
                                        eq1->puntos+=3;
                                }
                                else if ( dato.codRes>0 )  //gana el equpo 2
                                {
                                        eq2->puntos+=3;
                                }
                        }
                }
                actualizar_equipos(lista_equipos);
                close(fd);
        }
        printf("Hola mundo\n");
        return 0;
}
