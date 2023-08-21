// aqui estaran todas las funciones que realize...

//reazliza la conversion de todas los caracteres a binario y los escribe
void stringToBinary(char*);

int bin_toInt(char* bin);
//transforma un caracter a binario
void to_binary(char,char *);

//realiza algo
int realizarOperacion(double n1,double n2,char op,double* resu);

//va de string a int
double mi_atoi(char* s);

//realiza un encriptado rot13...
int rot_13(char* ptr, char* ptrCodificado);

//cambia el genero a la palabra
char* genero(char,char*);

//ejercicio realizado en clase...(de donde tengo que analizar bits y devolver algo dependiendo que si hay 1 o 0 en el bit
int analizar(unsigned char estado,int* resultado);

//lee una cadena y devuelve la longitud de la cadena leida...
int leerCadena(char* s,int lon);

//devuelve la longitud de una cadena
int mi_strlen(const char* cadena);

//copia origen en destino
int copiarCadena(char* destino, const char* origen);

//compara cadenas, y devuele 0 si son iguales >0 si p1 tiene mayor denominacion y viceversa
int compararCadenas(const char* palabra_1,const char* palabra_2);

// Une origen al final de destino
int unirCadenas(char* destino,const char* origen);

// Realiza una diferencia porcentual para ejercicio de numero e...
double diferenciaPorcentual(double num1, int num2);

// Realiza la funcion potenciacion...
double pote( double base, int exp );

// Devuelve la cantidad de digitos que tiene num...
int cantDigitos(int num);

// Creo que muestra al numero como suma de bases de 10 123 = 1*10² .... etc
void mostrar(int *p,int cant, int num);

// Descompone y muestra como la anterior funcion
int descomponerYMostrar(int num, int* p);

// <<EJERCICIO DE PRIMER PARCIAL>>...
int mul2uni(char* codigo,float* valor);
void mostrar(char tipo,float* listado,int largo);
unsigned char componer(unsigned char dato1, unsigned char dato2);
// <<EJERCICIO DE PRIMER PARCIAL>>...
//
