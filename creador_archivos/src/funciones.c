#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>

#include <errores.h>
#include <funciones.h>

/* Para el compania de aviacion */
void compania_aviacion(int cant_res)
{
        char buffer[LARGO];
        FILE * file;
        int fd_ciu, fd_vue, fd_res, i;
        Ciudad_t ciu;
        Vuelo_t vue;
        Reserva_t res;

        /*configuracion de ciudad*/
        ciu.idCiu = 1;
        /*configuracion de vuelo*/
        vue.idVue = 100;
        vue.cap = 30;
        /*configuracion de reservas*/
        res.idCli = 1;

        file = fopen(ARCH_NOMBRES, "r");
        fd_ciu = open(ARCH_CIUDADES, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP);
        fd_vue = open(ARCH_VUELOS, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP);
        fd_res = open(ARCH_RESERVAS, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP);

        srand( time(NULL) );

        if( file )
        {
                while( fgets(buffer, LARGO, file) && !feof(file) )
                {
                        if( buffer[strlen(buffer)-1]=='\n' ) buffer[strlen(buffer)-1]='\0';
                        ciu.millas = (int)random()%20 + 10;
                        strcpy( ciu.descr, buffer);
                        write(fd_ciu, &ciu, sizeof(Ciudad_t));
                        printf("id: %d, millas: %d, ciudad: %s\n",ciu.idCiu, ciu.millas, buffer);
                        ciu.idCiu++;
                }
                for( i=0; i<ciu.idCiu; i++ )
                {
                        vue.idDes = (int)random()%ciu.idCiu + 1;
                        vue.idOri = vue.idDes;
                        while( vue.idOri==vue.idDes ) vue.idOri = (int)random()%ciu.idCiu + 1;
                        printf("idVue: %d, cap: %d, idOri: %d, idDes: %d\n", vue.idVue, vue.cap, vue.idOri, vue.idDes);
                        write(fd_vue, &vue, sizeof(Vuelo_t));
                        vue.idVue++;
                }
                for( i=0; i<cant_res; i++ )
                {
                        res.idVue = (int)random()%ciu.idCiu + 100;
                        res.cant = (int)random()%4 + 1; 
                        printf("idCli: %d, idVue: %d, cant: %d \n", res.idCli, res.idVue, res.cant);
                        write(fd_res, &res, sizeof(Reserva_t));
                        res.idCli++;
                        usleep(5000);
                }
                close(fd_ciu);
                close(fd_vue);
                close(fd_res);
                fclose(file);
        }
}
