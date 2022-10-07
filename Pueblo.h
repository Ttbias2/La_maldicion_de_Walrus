#ifndef PUEBLO_H_INCLUDED
#define PUEBLO_H_INCLUDED
#include "personaje.h"
#include "Inventario.h"
#define ArchEspada "ArchEspada"
#define ArchArmadura "ArchArmadura"

void Pueblo();
void TABERNA();
void TIENDA();
int MenuDeCompra(int *CompraTaberna,int *CantidadPota);
int CargaDeCompra(int CompraTaberna,int CantidadPota);
void mago();
void animacion_puerta();
personaje mejorar_arma(personaje pj);
void herrero();
void mostrar_nesesidades_de_objetos();
void mostrar_invent_personaje();

#endif // PUEBLO_H_INCLUDED
