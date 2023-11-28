
#ifndef NODOS_H
        #define NODOS_H
        
        //criterio de agregado_ordenado para la lista de Rciudades
        int cmp_idCiudad(void * p1, void * p2);
        
        //criterio de agregado_ordenado para la lista de RVuelos
        int cmp_idVuelo(void *dat1, void * dat2);

        //criterio de busqueda para lista de RVuelos
        int busq_idVuelo(void * idVue, void * dato_lista);

        //criterio de busqueda para lista de ciudades
        int busq_idCiudad(void * idCiu, void * dato_lista);
        //----------------------------------PARA AGREGADO ELIMINADO Y DEMAS DE LA LISTA--------------------
        //agrega a la lista de nodos
        int agregar(Nodo_t ** lista, void * pdat);

        //agrega ordenado a la lista de nodos
        int agregar_ordenado(Nodo_t ** lista, void * dato, int(*crit_ord)(void *, void *) );

        //busca en la lista de nodos
        void * buscar(Nodo_t * lista, void * busqueda, int(*crit_busq)(void *,void *));
#endif
