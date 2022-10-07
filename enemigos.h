#ifndef ENEMIGOS_H_INCLUDED
#define ENEMIGOS_H_INCLUDED
#define ArchEnemigos_M1 "ArchEnemigos_M1"
#define ArchEnemigos_M2 "ArchEnemigos_M2"
#define ArchEnemigos_M3 "ArchEnemigos_M3"
#define ArchJEFE_M1 "ArchJEFE_M1"
#define ArchJEFE_M2 "ArchJEFE_M2"
#define ArchJEFE_M3 "ArchJEFE_M3"

typedef struct
{
    char Nombre[20];
    int vida;
    int danio;
    char drop[20];
    int Moneda;
    int xp;
    int Mundo;

}stEnemigo;

void mostrar_enemigo(stEnemigo enemigo);
stEnemigo CargarStuctEnemigos();
void CargarArchivoEnemigos();
void CargarArchivoJEFES();
stEnemigo BuscarEnemigos(int Mundo);
stEnemigo BuscarJefe(int mundo);
void vaciar_archivos_enemigos();
void vaciar_archivos_jefes();

#endif // ENEMIGOS_H_INCLUDED
