#ifndef STRUCTS_H
        #define STRUCTS_H

        #define ERROR 0
        #define OK 1
        #define ERRFILE 2
        #define ERRMEM 3

        #define ARCH_EQUIPOS "cfg/equipos.dat"
        #define ARCH_RESULTADOS "cfg/resultados.dat"

        typedef struct Resultado
        {
                int idEq1;
                int idEq2;
                int codRes;
                char estadio[20];
        }Resultado_t;

        typedef struct Equipo
        {
                int idEq;
                char nombre[20];
                int puntos;
        }Equipo_t;

        typedef struct Estadio
        {
                int partidos;
                int empatados;
                char estadio[20]: 
        }Estadio_t;
        typedef struct Nodo
        {
                void * dato;
                struct Nodo * next;
        }Nodo_t;
#endif // !STRUCTS_H

