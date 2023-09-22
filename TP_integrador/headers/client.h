#ifndef CLIENT_H
	#define CLIENT_H
	
	void mostrar_menu();

	void iniciar_menu(int * nro_menu, int peticion, Usuario_t * us, Documento_t ** lista);
	
	int realizar_menu_1( Usuario_t* us,int peticion );
	int realizar_menu_2( Documento_t ** lista, int peticion );
	int realizar_menu_3( Documento_t ** lista, int peticion );
	
	//MENU_1
	int agregar_usuario(Usuario_t* us);

	int iniciar_sesion(Usuario_t* us);

	int borrar_usuario(Usuario_t* us);

	//MENU_2

	int buscar_documentos(Documento_t ** lista);

	int subir_documento();

	//MENU_3

	//aca muestra los datos de los documentos
	int mostrar_documentos_nombre(Documento_t ** lista);

	int mostrar_documentos_autor(Documento_t ** lista);

	//muestra o descarga el documento en si, pido el nro de documento dentro de la funcion
	int mostrar_un_documento();

	int descargar_un_documento();

	int actualizar_documentos(Documento_t ** lista);

#endif