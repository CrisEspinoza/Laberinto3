#include <stdio.h>
#include "struct.h"
#include <string.h>
#include <stdlib.h>

int VUELTA = 0;

Matriz* createBoard(int numeroDeNodos)
{
    int i,j;
    // Procedemos a crear una variable de tipo Tablero y a solicitar memoria para dicha variable
    Matriz *matriz;
    matriz = (Matriz*)malloc(sizeof(Matriz));

    matriz->adyacencia = (int**)malloc(numeroDeNodos*sizeof(int*)); // Inicializamos una de variables que contiene nuestra estructura con tantas filas diga el archivo
    matriz->numeroDeNodos = numeroDeNodos;

    for (i = 0 ; i < numeroDeNodos ;i++)
    {
        matriz->adyacencia[i] = (int*)malloc(numeroDeNodos*sizeof(int)); // Aca inicializamos las columnas que rescatamos desde el archivo

        for (j = 0;  j < numeroDeNodos ;j++)
        {
            matriz->adyacencia[i][j] = 0; // Asignamos un elemento neutro que demostrara que el tablero esta creado pero no utilizado 
        }
    }
    return matriz; // retornamos el tablero inicilizado (con elemento que representa estar vacio)
}

Lista* crearLista() // Creamos la lista nueva 
{
    Lista* lista = (Lista*)malloc(sizeof(Lista)); // Pedimos memoria para la nueva lista 
    lista->nodo = NULL;
    lista->largo = 0 ; // El largo de la lista es igual a "0".
    return lista; // Se retorna la lista creada
}

Nodo* crearNodo(int peso, int origen, int destino)
{
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo)); // Pedimos memoria para el nuevo nodo declarado
    if (nuevoNodo != NULL)
    {
        nuevoNodo->peso = peso; // Asignamos lo que recibe la funcion a la variable direccion
        nuevoNodo->origen = origen; // Asignamo el valor de file que recibe a lo que pertenece a la estructura
        nuevoNodo->destino = destino; // Asignamos el valor de columna que recibe a lo que pertenece a ala estructura
    }
    return nuevoNodo; // Se retorna el nuevo nodo creado
}

Lista* agregarNodo(Lista* lista , Nodo* aux)
{
    if(lista->largo == 0)
    {
    	lista->nodo = (Nodo*)malloc(sizeof(Nodo));
    	lista->nodo[0] = *aux;
    }
    else
    {
        lista->nodo = (Nodo*)realloc(lista->nodo, (lista->largo + 1) * sizeof (Nodo)); // Pedimos mas memoria para el arreglo creado
        lista->nodo[lista->largo] = *aux; // Agregamos el nodo que se desea agregar, luego de haber solicitado memoria
    }
    lista->largo++; // aumnetamos el largo de la lista de arreglos
    return lista;
}

Matriz *cargar(char nombre[])
{
    FILE *archivo; // Declaramos un puntero File para poder leer el archivo de entrada.

    archivo = fopen (nombre, "r"); // Estamos abriendo el archivo en modo lectura
    Matriz* matriz; // Se declara una variable de tipo matriz
    
    Nodo* auxNodo;// Se declara una variable de tipo nodo
    int caracter;

    //Verificamos si el archivo se encuentra nulo
    if( archivo == NULL)
    {
        printf("Error al abrir archivo \n");
        return 0;
    }
    
    int numeroDeNodos,entrada,llave,salida,destino,origen,peso; // Se declaran las variables que vana a ser utilizadas
    char camino;
    // Leemos las primeras lineas del archivo para un mejor manejo de este
    fscanf(archivo, "%d", &numeroDeNodos);
    while(getc(archivo) != '\n');
    matriz = createBoard(numeroDeNodos);
    fscanf(archivo, "%c %d" ,&camino,&entrada);
    while(getc(archivo) != '\n');
    fscanf(archivo, "%c %d" ,&camino,&llave);
    while(getc(archivo) != '\n');
    fscanf(archivo, "%c %d" ,&camino,&salida); 
    // Creamos el ablero para luego colocar lo extraido desde el archivo
    matriz = createBoard(numeroDeNodos); //Creamos un tablero con las dimensiones que tendra el tablero
    //Guardamos las posiciones mas importantes del laberinto
    matriz->entrada = entrada;
    matriz->llave = llave;
    matriz->salida = salida;
    matriz->listaNodos = crearLista(); //Creamos la lista de nodos 
    while(getc(archivo) != '\n'); // Que lea el archivo siempre y cuando no sea un salto de linea

    int i,j;

     while (!feof(archivo)) 
    {
        fscanf(archivo, "%d %d %d",&origen, &destino ,&peso);
        matriz->adyacencia[origen-1][destino-1] = peso; // Cada caracter que lea sera almacenado en la variable de tipo (struct Tablero)
        matriz->adyacencia[destino-1][origen-1] = peso;
        auxNodo = crearNodo(peso,origen,destino); // Creamos un nuevo nodo con lo caputrado desde el archivo
        agregarNodo(matriz->listaNodos,auxNodo); // Agregamos el nodo creado a la lista
        auxNodo = crearNodo(peso,destino,origen); // Agregamos el reciproco de lo leido en la lista
        agregarNodo(matriz->listaNodos,auxNodo); // Lo agregamos a la lista el nuevo nodo creado
    }
    // Agregamos las cosas importantes a la variable matriz
    matriz->entrada = entrada;
    matriz->llave = llave;
    matriz->salida = salida;
    
    fclose(archivo); // Cerramos el archivo
 
    return matriz; //Retornamo la variable matriz, con el tablero contenido, el cual se leyó desde el archivo ingresado
}

void print(Matriz *matriz)
{
    Nodo* aux;
    //aux = matriz->listaDeAdy->primero;

    for (int i = 0; i < matriz->numeroDeNodos; i++)
    {
        for (int j = 0; j < matriz->numeroDeNodos; j++)
        {
            printf("%d  ", matriz->adyacencia[i][j]); //Imprimos por pantalla cada una de las caracteristicas que guarda dentro de si el tablero
        }
        printf("\n");
    }

    for (int j = 0; j < matriz->listaNodos->largo; j++)
    {
        // Mostramos por pantalla detalladamente cada uno de los valores que contiene la lista
    	printf("Entrada es: %d , la llave es: %d y la salida es: %d \n",matriz->listaNodos->nodo[j].origen,matriz->listaNodos->nodo[j].destino,matriz->listaNodos->nodo[j].peso);
    }   
}

void mostrarLista(Lista* lista)
{
	for (int j = 0; j < lista->largo; j++)
    {
        // Funcion que se encarga de mostrar cada uno de los valores que contiene la lista a mostrar por pantalla
    	printf("origen es: %d , la destino es: %d y el peso es: %d \n",lista->nodo[j].origen,lista->nodo[j].destino,lista->nodo[j].peso);
    }
}

Lista* rellenarPendientes(Lista* lista,Lista* pendiente, int origen, Lista* rutaMinima)
{
    //Declaramos las varaibles que se van a utlizar
	int contador = 0;
	Nodo* aux;

	while(lista->largo > contador)
	{
		if (origen == lista->nodo[contador].origen && (noCerrado(rutaMinima,lista->nodo[contador].destino) == 1 ))
		{
			aux = crearNodo(lista->nodo[contador].peso,lista->nodo[contador].origen,lista->nodo[contador].destino); // Creamos el nodo agregar a la lista
			agregarNodo(pendiente,aux); // agregamos el nodo creado a la lista de pendientes
		}
		contador++; // aumentamos el contador
	}
	return pendiente;
}

int noCerrado(Lista* lista, int numero)
{
	for (int i = 0; i < lista->largo; i++)
	{
		if (lista->nodo[i].destino == numero) // Verificamos si esta dentro de la lista el numero que se esta analizando
		{
			return 0; // Retorna 0 si el elemento ya se encuentra dentro de la lista 
		}
	}
	return 1 ; // Retorna 1 si el elemento no esta contenido dentro de la lista
}

Nodo* buscarCamino(Matriz* matriz, int objetivo, int entrada)
{    
    //Declaramos las varuables que se van a utilizar dentro de la funcion
    Lista* rutaMinima = crearLista();
    Lista* pendientes = crearLista();
    Nodo* aux;
    int pesoTotal = 0;

    aux = crearNodo(0,0,entrada); // Creamos el nodo inicial que se obtiene desde el archivo
    rutaMinima = agregarNodo(rutaMinima,aux); //Agregamos la entrada del laberinto
    pendientes = rellenarPendientes(matriz->listaNodos, pendientes,rutaMinima->nodo[rutaMinima->largo - 1].destino,rutaMinima); // Actualizamos la lsta de pendientes
    int contador = 0;

    while(aux->destino != objetivo)
    {
    	aux = buscarNodoMinimo(pendientes); // Buscamos el nodo minimo que se tiene actualmente
        rutaMinima = agregarNodo(rutaMinima, aux); // Agregamos el nodo minimo a la lista de ruta minima 
        pendientes = borrarElemento(pendientes,aux); // Borramos ese elemento de la lista de pendientes
        pendientes = rellenarPendientes(matriz->listaNodos, pendientes ,aux->destino,rutaMinima); // Actualizamos nuevamente la lista de pendientes
        contador++; // aumentamos el contador
    }
    rutaMinima = calcularRutaMinima(rutaMinima,aux); // Se verifica la ruta minima que se obtiene
    mostrarLista(rutaMinima); // Se muestra po pantalla
    pesoTotal = calcularPeso(rutaMinima, pesoTotal); // Se calcula el peso total que se tiene al hacer el recorrido
    saveTablero(rutaMinima,pesoTotal); // Se pasan los parametros a la funcion que se encarga de crear el archivo
    printf("El peso total recorrido fue de: %d\n",pesoTotal );
    return aux;
}

int calcularPeso(Lista* lista, int peso)
{
	for (int i = 0; i < lista->largo; i++)
	{
		peso = peso + lista->nodo[i].peso; // Suma la cantidad total de pesos que se tiene en la tuta minima encontrada dentro del grafo
	}
	return peso; // Retorna el peso final del camino minimo
}

Lista* calcularRutaMinima(Lista* lista , Nodo* objetivo)
{
    // Decaramos las variables que se van a utilizar
	Nodo* aux = (Nodo*)malloc(sizeof(Nodo));
	Lista* ruta = crearLista();

	aux = objetivo;
	agregarNodo(ruta,aux); // Agregamos a la ruta la variable creada (pasada por paramentro)

	while(aux->origen != 0)
	{
		for (int i = 0; i < lista->largo; i++)
		{
			if(aux->origen == lista->nodo[i].destino) // Verificamos si estps valores son iguales 
			{
				*aux = lista->nodo[i]; // Se cambia el valor de aux
				agregarNodo(ruta,aux);	// Se agrega a la lista el nuevo aux encontrado				 
			}
		}
	}
	return ruta; // Se devuelve la ruta final del grafo 
}

Nodo* buscarNodoMinimo(Lista* lista)
{
    // Se declaran las variables qwue se van a utilizar dentro de la funcion
    Nodo* aux = (Nodo*)malloc(sizeof(Nodo));
    *aux = lista->nodo[0];
    int contador = 1;

    while (lista->largo > contador)
    {
        if (lista->largo == 1) // Se verifica si el largo de la lista es uno 
        {
            return aux; // S devuelve el aux
        }
        else
        {     
            if (aux->peso > lista->nodo[contador].peso) // Se hace la comparacion para verificar si se cambia el aux 
            {
                *aux = lista->nodo[contador]; // Se actualiza el valor de aux
            }
        }  
        contador++;  // Se aumenta el contado
    }
    return aux; // Se retorna en nuevo nodo minimo
}

Lista* borrarElemento(Lista* lista , Nodo* auxNodo)
{
    // Se declaran variables que se van a utilizar dentro de la funcion
    Lista* auxLista = crearLista();
    Nodo* aux = (Nodo*)malloc(sizeof(Nodo));
    // Se inicializa el aux
    *aux = lista->nodo[0];
    int contador = 1;

    while(contador <= lista->largo)
    {
        if (aux->origen == auxNodo->origen && aux->destino == auxNodo->destino && aux->peso == auxNodo->peso) // Se verifica si es el mismo nodo
        {
            *aux = lista->nodo[contador]; // Se actualiza el valor de aux
        }
        else
        {
            auxLista = agregarNodo(auxLista,aux); // Se agrega el nuevo aux a la lista aux
            *aux = lista->nodo[contador]; // Se cambia el valor de aux, luego de haberlo agregado a al lista
        }
        contador++; // Se auemnta el contador
    }    
    free(aux); // Se libera memeria de la variable solicitada
    return auxLista; // Se retona la nueva lita creada
}

void saveTablero (Lista* rutaMinima, int pesoTotal)
{
    FILE *txt;  // Incialzamos una variable de tipo FILE para poder trabajar con los archivos

    // Hacemos una comparacion para verificar si es el primero o segundo camino que se esta recibiendo 
    if (VUELTA == 0) 
    {
        txt = fopen("Salida.out", "wt"); // Abrimos le archivo en modo escritura y que se cree si no exite el archivo nombrado
        VUELTA = 1;
    }

    else
    {
        txt = fopen("Salida.out", "a"); // Abrimos el archivo en modo sobreescritura, para no perder el camino anterior que esta en el archivo
        fprintf(txt,"\n");
        fprintf(txt,"\n");
        VUELTA = 0;
    }

    for (int i = rutaMinima->largo-1 ; i >= 0 ; i--)
    {
    	if (i == 0)
    	{
    		fprintf(txt,"%d ",rutaMinima->nodo[i].destino); // Se escribe la ruta minima en el archivo
    	}
    	else
    	{
    		fprintf(txt,"%d - ",rutaMinima->nodo[i].destino); // Se escribe la ruta minima en el archivo
    	}
        
    }
    fprintf(txt, "\n"); // S ehace un salto de linea en ele archio
    fprintf(txt,"La distancia recorrida es: %d",pesoTotal); // Se coloca el peso total ocupado en la ruta minima obtenida y se pone en el archivo

    fclose(txt); // Cerramos el archivo
}