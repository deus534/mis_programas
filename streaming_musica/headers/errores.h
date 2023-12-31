#ifndef ERRORES_H
        #define ERRORES_H
        
        /* DEFINICION DE CONSTANTES - ERRORES*/
        #define ARCH_REPRODUCCIONES "cfg/REPRODUCIONES.dat"
        #define ARCH_ARTISTAS "cfg/ARTISTAS.dat"
        #define ARCH_ALBUMES "cfg/ALBUMES.dat"
       
        #define ERR_FILE 0
        #define ERR_MEM 1
        #define OK 2

        #define LARGO_RART 10
        

        /* ESTRUCTURAS DE LA DOCUMENTACION */
        typedef struct Reproduccion
        {
                int idUser;
                int idAlbum;  //ordenado
                int date;
                int minutos;
        }Reproduccion_t;

        typedef struct Album
        {
                int idAlbum;  //ordenado
                int idArtista;
                char titulo[50];
                int duracion;  //minutos
        }Album_t;
        
        typedef struct Artista
        {
                int idArtista; //ordenado
                char nombre[50];
        }Artista_t;

        /* ESTRUCTURAS DEFINIDAS */
        
        typedef struct RAlbum 
        {
                Album_t album;
                unsigned int rep_comp;
                unsigned int rep75_100;
                unsigned int rep50_75;
                unsigned int rep25_50;
                unsigned int rep0_25;
        }RAlbum_t;

        typedef struct RArtista
        {
                Artista_t artista;
                unsigned int rep75_100;
        }RArtista_t;
#endif // !ERRORES_H

