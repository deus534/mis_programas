#ifndef STRUCTS_H
        #define STRUCTS_H

        //definicion de constantes de error y demas
        #define OK 0
        #define ERROR 1
        #define ERRMEM 2
        #define ERRFILE 3

        #define ARCH_VUELOS "cfg/vuelos.dat"
        #define ARCH_CIUDADES "cfg/ciudades.dat"
        #define ARCH_RESERVAS "cfg/reservas.dat"
        
        //estrucutras para la obtencion de datos de los archivos
        typedef struct Ciudad
        {
                int idCiu;
                char descr[20];
                int millas;
        }Ciudad_t;

        typedef struct Vuelo 
        {
                int idVue;
                int cap;
                int idOrg;  //idCiu origen
                int idDest;  //idCiu destino
        }Vuelo_t;

        typedef struct Reserva
        {
                int idCli;
                int idVue;
                int cant;
        }Reserva_t;

        //structuras para la definicion del programa
        typedef struct RCiudad
        {
                Ciudad_t ciudad;
                int cant;  //cantidad de que la eligieron de destino
        }RCiudad_t;
        typedef struct RVuelo
        {
                Vuelo_t vuelo;
                int rechazados;
                int aceptados;
        }RVuelo_t;
        typedef struct Cliente
        {
                Reserva_t reserva;
                int total_millas;
        }Cliente_t;
        
        typedef struct Nodo
        {
                void * dato;
                struct Nodo * next;
        }Nodo_t;
#endif
