#ifndef FUNCIONES_H
	#define FUNCIONES_H
        
        //++++++++++++++        MENU_1        ++++++++++++
        
        int realizar_menu_1( int peticion, int * nro_menu, int socket, int * nivel);

        int agregar_usuario( int socket, int * nivel);

        int iniciar_sesion( int socket, int * nivel );

        int borrar_usuario( int socket, int * nivel );

        //++++++++++++++        MENU_2        ++++++++++++
        
        int agregar( Nodo_t ** lista, void * dat );
        int realizar_menu_2( Nodo_t ** lista_documentos, int peticion, int * nro_menu, int socket );

        Documento_t * nuevo_documento(char * cod, char * nom, char * aut, int an);

        int buscar_documentos(Nodo_t ** lista, int * error, int socket);

        void subir_documento(Nodo_t ** lista, int * error, int socket);

        //++++++++++++++        MENU_3        ++++++++++++
        
        int realizar_menu_3( Nodo_t ** lista_documentos, int peticion, int * nro_menu, int socket );

        //criterio de ordenamiento
        int cmp_nombre( void * dat1, void * dat2 );
        
        //criterio de ordenamiento
        int cmp_autor( void * dat1, void * dat2 );
        
        void mostrar_documentos(Nodo_t * lista, int criterio);
         
        void mostrar_descargar_documento(Nodo_t * lista,char * cod, int val);

        //++++++++++++++        FUNCIONES CONEXION        ++++++++++++

        //establece la conexion con el servidor, retorna socket
        int establecer_conexion();


	//++++++++++++++++ FUNCIONES GENERALES ++++++++++++++++++++
	
        //muestra el nro de menu
        void mostrar_menu(int nro_menu);

        //lee por consola un numero entre (0, 9), si no retorna -1
	int leer_peticion();
	
	//lee una cadena de texto por consola
	int leer_cadena(char* cad,int lon_max);
	
	//encripta con root13 y root5 cont en enc
	void encriptar_contrasenia(char* cont,char* enc);

	//algoritmo de encriptacion	
	char root13(char c);
#endif
