#ifndef ERRORES_H
        #define ERRORES_H
        
        #define ARCH_NOMBRES "cfg/ciudades.txt"
        #define ARCH_CIUDADES "cfg/CIUDADES.dat"
        #define ARCH_VUELOS "cfg/VUELOS.dat"
        #define ARCH_RESERVAS "cfg/RESERVAS.dat"
        #define LARGO 100
        
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
                int idOri;
                int idDes;
        }Vuelo_t;
        
        typedef struct Reserva
        {
                int idCli;
                int idVue;
                int cant;
        }Reserva_t;

#endif
