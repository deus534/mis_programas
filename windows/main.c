#include <stdio.h>
#include <stdlib.h>

int main()
{
	int * lista = (int *)malloc( sizeof(int)*3 );

	lista[0] = 21;
	lista[1] = 23;
	lista[2] = 53;

	for(int i=0; i<3; i++)
	{
		printf("%d\n",lista[i]);
	}
	free(lista);

	return 0;
}
