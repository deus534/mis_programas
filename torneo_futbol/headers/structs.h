#ifndef STRUCTS_H
        #define STRUCTS_H

        #define ERROR 0
        #define OK 1
        #define ERRFILE 2
        #define ERRMEM 3

        #define ARCH_EQUIPOS "cfg/EQUPOS.dat"
        #define ARCH_RESULTADOS "cfg/RESULTADOS.dat"

        typedef struct Resultado
        {
                int idEq1;
                int idEq2;
                char estadio[20];
                int codRes;
        }Resultado_t;

        struct MyStruct {
                
        };
        typedef struct Equipo
        {
                int idEq;
                char nombre[20];
                int puntos;
        }Equipo_t;

        typedef struct Estadio
        {
                int partidos;
                char estadio[20];
                int empatados;
        }Estadio_t;
        typedef struct Nodo
        {
                void * dato;
                struct Nodo * next;
        }Nodo_t;
#endif // !STRUCTS_H

