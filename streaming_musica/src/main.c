#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <errores.h>
#include <funciones.h>

/*
 - cosas por terminar
 1) falta lo del nombre del artista
 2) falta lo de agregar a una lista los de RAlbum
 3) falta los archivos para probar todo

*/

int main()
{
        int fd_rep, fd_alb, fd_art;
        int error_alb, error_rep, error_art;
        int largo = 0;
//        off_t size_alb, size_art;

        Reproduccion_t repro;
        Album_t alb;
        Artista_t art;
        RAlbum_t rAlb;
        RArtista_t rArt;
        RArtista_t vec_rArt[LARGO_RART];

        fd_rep = open(ARCH_REPRODUCCIONES, O_RDONLY);
        fd_alb = open(ARCH_ALBUMES, O_RDONLY);
        fd_art = open(ARCH_ARTISTAS, O_RDONLY);

        if( fd_rep!=-1 && fd_alb!=-1 && fd_rep!=-1 )
        {
                /* leo una vez para una verificacion de idAlbum */
                error_alb = read( fd_alb, &alb, sizeof(Album_t) );
                error_rep = read( fd_rep, &repro, sizeof(Reproduccion_t) );
                error_art = read( fd_art, &art, sizeof(Artista_t) );

                /*
                analizo si ARCH_ARTISTAS es un archivo mas grande que ARCH_ALBUMES 

                size_alb = lseek( fd_alb, SEEK_END, 0 );
                size_art = lseek( fd_art, SEEK_END, 0 );
                
                lseek( fd_alb, SEEK_SET, 0 );
                lseek( fd_art, SEEK_SET, 0 );
                */
                /* comienzo leyendo el archivo de ARCH_ALBUMES */
                while( error_alb>0 )
                {
                        /* inicializo la estructura RAlbum para ponerla en una lista */
                        rAlb.album = alb;
                        rAlb.rep_comp = 0;
                        rAlb.rep75_100 = 0;
                        rAlb.rep50_75 = 0;
                        rAlb.rep25_50 = 0;
                        rAlb.rep0_25 = 0;
                        
                        /* inicializo la estructura RArtista_t para ponerla en un vector */
                        rArt.artista.idArtista = alb.idArtista; 
                        rArt.rep75_100 = 0;
                        if( alb.idArtista == art.idArtista ) strcpy( rArt.artista.nombre, art.nombre );

                        /* sigo leyendo reproducciones mientras sea tengan el mismo idAlbum y no llegue al final */
                        while( error_rep>0 && repro.idAlbum==alb.idAlbum )
                        {
                                /* analizo la duracion de cada reproduccion y veo para los 10 artistas mas destacados*/ 
                                if( alb.duracion == repro.minutos ) rAlb.rep_comp+=1; 
                                else if( repro.minutos > (0.75*alb.duracion) ) rAlb.rep75_100+=1;
                                else if( repro.minutos > (0.50*alb.duracion) ) rAlb.rep50_75+=1;
                                else if( repro.minutos > (0.25*alb.duracion) ) rAlb.rep25_50+=1;
                                else rAlb.rep0_25+=1;

                                error_rep = read( fd_rep, &repro, sizeof(Reproduccion_t) );
                        }
                        if( error_art>0 && repro.minutos > (0.75*alb.duracion) ) comparar_agregar( vec_rArt, &largo, rArt );

                        error_alb = read( fd_alb, &alb, sizeof(Album_t) );
                        error_art = read( fd_art, &art, sizeof(Artista_t) );
                        // agrego a una lista el rAlb 
                }
                close(fd_alb);
                close(fd_rep);
                close(fd_art);
        }
        else perror("archivo"); 


        return 0;
}
