#ifndef SERVER_H
	#define SERVER_H

	//MENU_1

	//valida(que no exista el usuario) y agrega el usuario al archivo de usuarios y luego inicia sesion
	int alta_de_usuario(Usuario_t* us);

	//valida(que exista el usuario y que este bien la contrasenia) y inicia sesion
	int validar_usuario(Usuario_t* us);

	//valida(que exista el usuario y que este bien la contrasenia), solicita confirmacion y luego borra del arhivo usuarios
	int baja_de_usuario(Usuario_t* us);

	//MENU_2

#define endif