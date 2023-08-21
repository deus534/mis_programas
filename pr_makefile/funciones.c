#define OK 1
#define ERROR 0

void to_binary(char c,char* bin)
{
	int i;
	int mascara = 0x80;
	
	for( i=0; i<8; i++ )
	{
		if( c&mascara )
		{
			*(bin+i) = '1';
		}
		else
		{	
			*(bin+i) = '0';
		}
		mascara = mascara >> 1;
	}
	*(bin+i) = '\0';
}

int bin_toInt(char* bin)
{
	int i, ret = 0;
	int masc = 0x80;

	for( i=0; i<8; i++ )
	{
		if( bin[i]=='1' )
		{
			ret += masc;
			masc = masc>>1;
		}
	}
	return ret;
}
void stringToBinary(char* s)
{
	int len, i;
	char bin[9];
	len = strlen(s);

	for( i=0; i<len; i++ )
	{
		to_binary( *(s+i), bin );
		printf("en binario: %c: %s: %d \n",*(s+i), bin, *(s+i) );
	}
}

double mi_atoi(char* s)
{
	double ret, aux, ent, dec;
	int i, val, cont_dec;

	i = 0;
	val = 0;
	cont_dec = 0;

	ent = 0.0;
	dec = 0.0;

	if( s[0]=='-' )
	{
		i++;
	}

	while( s[i] && ((s[i]>='0' && s[i]<='9') || s[i]=='.') )
	{
		if( s[i]=='.' )
		{
			val = 1;
			i++;
		}
		if( val )
		{
			//la parte decimal
			aux = s[i]-'0';
			dec = dec*10 + aux;
			cont_dec++;
		}
		else
		{
			//la parte entera
			aux = s[i]-'0';
			ent = ent*10 + aux;
		}
		i++;
	}
	ret = ent + (dec/mi_pow(10,cont_dec));
	
	if( s[0]=='-' )
	{
		i++;
	}

	return s[0]=='-'?ret*(-1):ret;
}
double sumar(double n1,double n2)
{
	return n1+n2;
}
double restar(double n1,double n2)
{
	return n1-n2;
}
double multiplicar(double n1,double n2)
{
	return n1*n2;
}
int dividir(double divisor,double dividendo, double* resu)
{
	int ret = ERROR;
	if( dividendo!=0 )
	{
		*(resu) = divisor/dividendo;
		ret = OK;
	}
	return ret;
}
int realizarOperacion(double n1,double n2,char op,double* resu)
{
	int ret = OK;
	switch( op )
	{
		case '+':
			*(resu) = sumar(n1,n2);
			break;
		case '-':
			*(resu) = restar(n1,n2);
			break;
		case 'x':
			*(resu) = multiplicar(n1,n2);
			break;
		case '/':
			ret = dividir(n1,n2,resu);
			break;
	}
	return ret;
}
//devuelve 0 si NO pudo realizarlo
int implementar_rot_13(char carOrg,char* carCod)
{
	int ret = ERROR;
	if( ( carOrg>'M' && carOrg<='Z' ) || ( carOrg>'m' && carOrg<='z' ) )
	{
		*carCod = carOrg-13;
		ret = OK;
	}
	else
	{
		if( ( carOrg>='A' && carOrg<='M') || ( carOrg>='a' && carOrg<='m' ) )
		{
			*carCod = carOrg+13;
			ret =  OK;
		}
	}
	return ret;
}

int rot_13(char* ptr, char* ptrCodificado)
{
	int ret, i, lon, num;
	char aux;
	
	lon = strlen(ptr);
	ret = 0;
	
	for( i=0; i<lon && ret >= 0; i++)
	{
		aux = *(ptr+i);
		
		if( aux == ' ' )
		{
			*(ptrCodificado+i) = aux;
		}
		else
		{
			num = implementar_rot_13(aux, (ptrCodificado+i));
			
			if( num )
			{
				ret++;
			}
			else
			{
				ret = -1;
			}
		}
	}
	return ret;
}
char *genero(char gen,char* palabra)
{
	int lon, i;
	i = 1;
	lon = strlen(palabra);

	if( *(palabra+lon-i)=='s' )
	{
		i++;
	}
	
	if( gen=='F' || gen=='f' )
	{
		if( *(palabra+lon-i)=='o' )
		{
			*(palabra+lon-i) = 'a';
		}
	}
	else
	{
		if( *(palabra+lon-i)=='a' )
		{
			*(palabra+lon-i) = 'o';
		}
	}

	return "";
}




int analizar(unsigned char estado,int* resultado)
{
	int ret, mascara;
	
	ret = ERROR;
	mascara = 0x40;

	if( estado<0x80 )
	{
		ret = OK;
		if( estado & mascara )
		{
			*resultado = 10;
		}
		else
		{
			mascara = mascara >> 2;
			if( estado & mascara )
			{
				*resultado = 40 + (estado&0x03);
			}		
			else
			{
				mascara = mascara >> 2;
				if( estado & mascara )
				{
					*resultado = 30;
				}
				else
				{
					*resultado = 20;
				}
			}
		}
	}
	

	return ret;
}
int mi_strlen(const char* cadena)
{
	int cont = 0;
	while( *(cadena+cont) ) 
	{
		cont++;
	}
	return cont;
}

int leerCadena(char* s,int lon)
{
	int ret = strlen(s)-1;	
	
	fgets(s,lon,stdin);
	s[ ret ] = '\0';
	
	return ret;
}

int compararCadenas(const char* palabra_1,const char* palabra_2)
{
	int lon_1;
	int lon_2;
	int i, ret = 0;

	lon_1 = mi_strlen(palabra_1);
	lon_2 = mi_strlen(palabra_2);
	if( (lon_1-lon_2) >=0 )
	{
		for( i=0; palabra_1[i] && ret==0; i++ )
		{
			ret = palabra_1[i] - palabra_2[i];
		}
	}
	else
	{
		
		for( i=0; palabra_2[i] && ret==0; i++ )
		{
			ret = palabra_1[i] - palabra_2[i];
		}
	}
		
	return ret;
}
int copiarCadena(char* destino, const char* origen)
{
	int ret, lon, i;

	lon = mi_strlen(origen);

	for(i=0; i<lon; i++)
	{
		*(destino+i) = *(origen+i);
		ret++;
	}
	return ret;
}

int unirCadenas(char* destino,const char* origen)
{
		
	int ret, i, lon1, lon2;
	
	lon1 = mi_strlen(destino);
	lon2 = mi_strlen(origen);
	ret = lon1+lon2;
	
	for( i=0; i<lon2; i++)
	{
		*(destino+lon1+i) = *(origen+i);
	}

	*(destino+ret) = '\0';
	
	return ret;

}
double diferenciaPorcentual( double num1, int num2 )
{
	double ret;
	double promedio;
	double diferencia;
	
	promedio = (num1+num2)/2;
	diferencia = (num1>num2)?num1-num2:num2-num1;
	
	ret = (diferencia/promedio)*100;
	
	return ret;
}
int cantDigitos(int num)
{
	int cant = 0;
	while( num>0 )
	{
		num = num/10;
		cant++;
	}
	return cant;
}

double pote( double base, int exp )
{
	double ret = 1;
	int i;
	if( exp>0 )
	{
		for( i=0; i<exp; i++ )
		{
			ret = ret*base;
		}
	}
	else
	{
		base = 1/base;
		exp = exp*(-1);
		for( i=0; i<exp; i++ )
		{
			ret = ret*base;
		}
	}
	return ret;
	
}
void mostrar(int *p,int cant, int num)
{
	int i;
	for( i=0; i<cant; i++)
	{
		printf("%d*10^%d",p[i],cant-(i+1));
		if( i==(cant-1) )
		{
			printf(" = %d\n",num);
		}
		else
		{
			printf(" + ");
		}
	}
}
int descomponerYMostrar(int num, int* p)
{
	int cant,i, numAux;

	numAux = num;
	cant = cantDigitos( num );

	if( num>0 )
	{
		for( i=0; i<cant; i++ )
		{
			p[i] = numAux/pote(10,cant-i-1);

			numAux = numAux - p[i]*pote(10,cant-i-1);

		}
		mostrar(p,cant,num);
	}

	return num>0? OK: ERROR;
}

// <<EJERCICIO DE PRIMER PARCIAL>>
// ejercicio 1.....
int mul2uni(char* codigo,float* valor)
{
	int ret, len;
	char sub, *aux;
	
	ret = ERROR;

	len = strlen(codigo);
	aux = (char *)malloc( sizeof(char)*(len+1) );
	
	strcpy(aux,codigo);

	*(aux+len-1) = '\0';
	
	sub = *(codigo+len-1);
	
	switch ( sub )
	{
		case 'M':
			*valor = atof( aux )*pow(10,6);
			ret = OK;
			break;
		case 'K':
			*valor = atof( aux )*pow(10,3);
			ret = OK;
			break;
		case 'n':
			*valor = atof( aux )*pow(10,-3);
			ret = OK;
			break;
		case 'u':
			*valor = atof( aux )*pow(10,-6);
			ret = OK;
			break;
	}
	free(aux);	
	return ret;
}

//ejercicio 2
void mostrar_listado(float* list, int lon)
{
	int i;

	for( i=0; i<lon; i++ )
	{
		printf("%.7f ", *(list+i) );
	}
	printf("\n");
}
void mostrar(char tipo,float* listado,int largo)
{
	switch( tipo )
	{
		case 'C':
			printf("listado de capacitores\n\t");
			mostrar_listado(listado,largo);
			break;
		case 'I':
			printf("listado de inductores\n\t");
			mostrar_listado(listado,largo);
			break;
		case 'R':
			printf("listado de resistencias\n\t");
			mostrar_listado(listado,largo);
			break;
		default:
			printf("no se que tipo me espeficaste\n");
	}
}


//ejercicio 4
unsigned char componer(unsigned char dato1, unsigned char dato2)
{
	int mascara, aux_1, aux_2, i;
	unsigned char ret;

	ret = 0;

	mascara = 0x40;

	aux_1 = 0x80;
	aux_2 = 0x08;

	for( i=0;i<5;i++ )
	{
		if( i!=2 )
		{
			if( mascara & dato1 )
			{
				ret += aux_1;
			}
			if( mascara & dato2 )
			{
				ret += aux_2;
			}
			mascara = mascara >> 1;
			aux_1 = aux_1 >> 1;
			aux_2 = aux_2>>1;
		}
		else
		{
			mascara = mascara >> 2;
		}
	}
	return ret;
}
// <<EJERCICIO DE PRIMER PARCIAL>>
