
#ifndef NODOS_H
        #define NODOS_H
        
        //criterio de agregado_ordenado para la lista de ciudades
        int cmp_idCiudad(void * p1, void * p2);

        //----------------------------------PARA AGREGADO ELIMINADO Y DEMAS DE LA LISTA--------------------
        //agrega a la lista de nodos
        int agregar(Nodo_t ** lista, void * pdat);

        //agrega ordenado a la lista de nodos
        int agregar_ordenado(Nodo_t ** lista, void * dato, int(*crit_ord)(void *, void *) );
#endif
