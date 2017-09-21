#include <stdio.h>
#include "funciones.c"
#include <string.h>

int main()
{    
	// Se declaran las variables que se van a utilizar
    char nombre[25];
    int opcion;
    Matriz* matriz;
    matriz = NULL; // Se inicializa la matriz como nula
 
    do
    {
        printf( "\n   1. Cargar Nodos");
        printf( "\n   2. Mostrar relaciones de nodos");
        printf( "\n   3. Buscar camino minimo hacia la llave");
        printf( "\n   4. Buscar camino minimo hacia la salida");
        printf( "\n   5. Creditos" );
        printf( "\n   6. Salir" );
        printf( "\n\n   Introduzca opcion (1-6): ");

        scanf( "%d", &opcion );

        /* Inicio del anidamiento */

        switch ( opcion )
        {
            case 1: printf("Ingrese nombre del archivo a leer\n");
                    scanf("%s",nombre); // Se carga el nombre del archivo
                    matriz = cargar(nombre); // Se lee el archivo y se almacena en momoria el grafo
                    break;

            case 2: if (matriz != NULL)
            		{
            			print(matriz); // Se muestra la matriz
                    	break;
                    }
                    printf("Primero debe cargar alguna matriz, elegir opcion 1 \n");
                    break;                    

            case 3: if (matriz != NULL)
            		{
            			buscarCamino(matriz,matriz->llave,matriz->entrada); // Se busca el camino hacia la llave
            			printf("Camino minimo hacia la Llave encontrado , archivo generado\n");
                   	 	break;
                   	}
                    printf("Primero debe cargar alguna matriz, elegir opcion 1 \n");
                    break;                   	

            case 4: if (matriz != NULL)
            		{
            			buscarCamino(matriz,matriz->salida,matriz->llave); // Se busca el camino hacia la salida
            			printf("Camino minimo hacia la Salida encontrado , archivo generado\n");
                    	break;
                    }
                    printf("Primero debe cargar alguna matriz, elegir opcion 1 \n");
                    break;

            case 5: printf(" * Autor: CRISTIAN EDUARDO ESPINOZA SILVA \n ");
                    printf(" * Universidad santiago de chile \n");
                    break;
        }

    }while(opcion!=6);

    return 0;
}