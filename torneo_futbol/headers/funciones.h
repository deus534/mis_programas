#ifndef FUNCIONES_H
        #define FUNCIONES_H
        
        Nodo_t * leer_equipos(int * error);

        Equipo_t * buscar_equipo( Nodo_t * lista, int idEq );

        Estadio_t * buscar_agregar_estadio( Nodo_t * lista, char * est );

        void actualizar_equipos( Nodo_t * lista);
#endif
