#pragma once
#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <queue>
#include <vector>
#include "Consola.h"
using namespace std;

const int MAX_LADO = 50; //longitud máxima de los lados de la matriz
const int MAX_LISTA = 500; //longitud máxima de las listas

typedef struct { //sistema de coordenadas
	int alto;
	int ancho;
} tCoor;

typedef struct { //guarda la coordenada y su padre
	tCoor coor;
	tCoor padre;
} tCoorLista;

typedef struct { //lista abierta y cerrada
	tCoorLista casillas[MAX_LISTA];
	int contador;
} tLista;

typedef struct { //guarda el coste y color de una casilla de la matriz
	double coste;
	uint8 color;
} tCasilla;

typedef struct { //almacena todos la información de la matriz
	tCoor limites;
	tCoor casillaFin;
	queue <tCoor> waypoints;
	tCasilla casillas[MAX_LADO][MAX_LADO];
} tMatriz;

int main();
void iniciarMatriz(tMatriz& matriz); //inicializa la matriz
void iniciarElementos(tMatriz& matriz, tLista& abierta); //inicializa los elementos necesarios (casillas inicio, fin y prohibidas)
void mostrar(tMatriz const& matriz); //mostrar la matriz
bool operator == (tCoor c1, tCoor c2); //ver si dos coordenadas son iguales
bool operator != (tCoor c1, tCoor c2); //ver si dos coordenadas son distintas
tCoor operator + (tCoor c1, tCoor c2); //devuelve el resultado de sumar dos coordenadas
void aEstrella(tMatriz& matriz, tLista& abierta, tLista& cerrada, tLista& camino, bool& continuar); //algoritmo a* estrella
tCoorLista casillaMenorCoste(tMatriz const& matriz, tLista& abierta); //devuelve la casilla de menor coste y distancia a la casilla final
bool minimaDistancia(double& distancia, int coste, tCoor inicio, tCoor fin); //calcula la distancia entre dos coordenada
void caminoRegreso(tMatriz& matriz, tLista cerrada, tLista& camino); //busca el camino de regreso a la posicion inicial y lo guarda en camino
int posicionPadre(tCoor coor, tLista cerrada, int& i); //devuelve la posicion de la coordenada que corresponde al padre de la coordenada anterior
void replanificar(tMatriz& matriz, tLista& abierta);

#endif
