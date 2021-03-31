#include "Consola.h"

void chcp1252() {
	system("chcp 1252");
}

void borrar() {
	system("cls");
}

void pausa() {
	system("pause");
}

uint8 colores[10] = { 0, 12, 10, 9, 14, 13, 3, 15, 8, 11 };
// negro(0), rojo(1), verde(2), azul(3), amarillo(4), magenta(5), cian2(6), blanco(7), gris(8), cian1(9) 

void colorCTA(uint8 color, uint8 fondo) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | (colores[fondo] << 4));
}