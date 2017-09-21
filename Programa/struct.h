// Se importan las cosas que ayudaran al funcionamiento del codigo 
#include <stdio.h>
#include <string.h>

// Definimos las estructuras a ocupar dentro de la aplicacion

typedef struct Nodo
{
	int origen;
	int destino;
	int peso;
}Nodo;

typedef struct Lista
{
	int largo;
	Nodo* nodo;
}Lista;

typedef struct Matriz
{
	int numeroDeNodos;
	int** adyacencia;
	Lista* listaNodos;
	int entrada;
	int llave;
	int salida;
}Matriz;

// Definimos las funciones que se van a utilizar dentro del codigo 

Matriz* createBoard(int numeroDeNodos);
Matriz *cargar(char nombre[]);
void print(Matriz *matriz);
Nodo* buscarNodoMinimo(Lista* lista);
Nodo* buscarCamino(Matriz* matriz, int objetivo, int entrada);
Lista* rellenarPendientes(Lista* lista,Lista* pendiente, int origen, Lista* rutaMinima);
void mostrarLista(Lista* lista);
Lista* borrarElemento(Lista* pendiente , Nodo* auxNodo);
int noCerrado(Lista* lista, int numero);
Lista* calcularRutaMinima(Lista* lista , Nodo* aux);
Lista* agregarNodo(Lista* lista , Nodo* aux);
int calcularPeso(Lista* lista, int peso);
void saveTablero (Lista* rutaMinima, int pesoTotal);