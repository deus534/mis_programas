#ifndef FUNCIONES_H
        
        #define FUNCIONES_H

        Nodo_t * leer_ciudades(int * error);
        Nodo_t * leer_vuelos(int * error);
        void analizar_espacio(Nodo_t * list_RV, Nodo_t * list_RC, Cliente_t * dato_cliente);
        
        void mostrarListaRVuelo(Nodo_t * list_RV);
        void mostrarListaRCiudad(Nodo_t * list_RC);
#endif
