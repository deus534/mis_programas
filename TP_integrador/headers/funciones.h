#ifndef FUNCIONES_H
	#define FUNCIONES_H
	
	Usuario_t* nuevo_usuario(char* nom, char* cont, int nivel);

	//solicita por teclado lo que quiere hacer ya sea 1,2,3,etc.. validando cada error que se pueda tener
	
	int leer_peticion();
	int leer_baja_usuario();
	char* encriptar_contrasenia(char* cont);


#endif