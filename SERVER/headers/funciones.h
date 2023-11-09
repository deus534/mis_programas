#ifndef FUNCIONES_H
	#define FUNCIONES_H
	
	//FUNCIONES REALACIONADAS CON NODOS

	//agrega a la lista el Usuario_t * dato y retorna ERRMEM(falta de memoria) o OK
	int agregar( Nodo_t ** lista, void * dato );
	
	//buscar en la lista con el criterio de busqueda OK si lo encuetra, ERRUSR o ERRPSW si no lo pudo encontrar
	int buscar(Nodo_t ** lista, void * dat, int(*crit_busqueda)(void *, void *));
	
	//borra de la lista a us, cuando se encuentra su nombre OK si pudo borrar ERROR sino
	int eliminar(Nodo_t ** lista, void * elim, int(*cmp_elim)(void*,void*),void(*liberar)(void *) );

	//ordena la lista de documentos respecto de la funcion fun_cmp
	void ordenar(Nodo_t * lista,int(*fun_cmp)(void *,void *));
	
	//lee los datos de un archivo y retorna una lista con los datos
	Nodo_t * leer_usuarios( int * error);

	//lee los datos del archivo documentos.lst y retorna la lista
	Nodo_t * leer_documentos( int * error);

	//sobreescribe el archivo usuarios.lst con los datos de lista_usuarios
	int cargar_usuarios(Nodo_t * lista);
	
	//carga al archivo documentos.lst los datos de lista
	int cargar_documentos(Nodo_t * lista);


        
        //FUNCIONES RELACIONADAS CCON EL SOCKET

       
        //Inicia el socket retorna el nro de socket
        int iniciar_socket(char * puerto);

        //Inicia un nuevo thread de cliente
        void * nuevo_cliente(Argumento_t* dato);

        int __nombre(void * nom, void * us);
        int cmp_codigo(void * cod, void * pdocumento);

        int realizar_menu_1(int socket, int peticion, Nodo_t ** lista_usuarios, pthread_mutex_t * semaforo);

        int realizar_menu_2(int socket, int peticion, Nodo_t ** lista_documentos, pthread_mutex_t * semaforo );

	//FUNCIONES RELACIONADAS CON ESTRUCTURAS
	
	//Crea un Usuario_t * con los datos y lo retorna, si no pudo NULL
	Usuario_t * nuevo_usuario(char* nom, char* cont, int nivel);
	
	//Pide memoria y copia los datos en la memoria pedida
	Documento_t * nuevo_documento(char * cod, char * nom, char * aut, int anio);
	
	//libera el bloque de codigo Usuario_t*
	void liberar_usuario(void * dato);
	
	//libera el bloque de codigo Documento_t *
	void liberar_documento(void * dato);
	
	//libera la lista
	void liberar(Nodo_t * lista, void(*liberar_dato)(void*));        
#endif
