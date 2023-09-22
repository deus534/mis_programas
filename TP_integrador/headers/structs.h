
#ifndef STRUCTS_H
	#define STRUCTS_H

	#define MENU_0 0
	#define MENU_1 1
	#define MENU_2 2
	#define MENU_3 3

	#define SALIDA_MENU_1 4
	#define SALIDA_MENU_2 3
	#define SALIDA_MENU_3 6
	
	#define ADM 1
	#define USR 0

	#define OK 0
	#define ERROR 1
	#define ERRPASS 2
	#define ERRUSR 3
	
	typedef struct documento
	{
		char* codigo;
		char* nombre;
		char* autor;
		int anio;
	}Documento_t;

	typedef struct usuario
	{
		char* nombre;
		char* contrasenia;
		int nivel;
	}Usuario_t;

#endif