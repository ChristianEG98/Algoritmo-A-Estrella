#pragma once
#ifndef CONSOLA_H
#define CONSOLA_H
#include <Windows.h>
using namespace std;

typedef unsigned char uint8; //Byte

void chcp1252(); //codificación para usar los colores en la consola
void borrar(); //hacer un clear de la consola
void pausa(); //pausar la ejecución en un punto concreto
void colorCTA(uint8 color, uint8 fondo); //asignación de colores a caracteres en la consola (color de letras, color de fondo)

#endif