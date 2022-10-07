#ifndef PERSONAJE_H_INCLUDED
#define PERSONAJE_H_INCLUDED
#define ArchPJ "ArchPJ"
#define subida_danio 10
#define subida_agilidad 5
#define subida_danio_magico 1


typedef struct
{
    char nombre[20];
    int vida_max;
    int vida;
    int mana_max;
    int mana;
    int danio;
    int danio_magico;    //estadisticas que usara el personaje
    int agilidad;
    int defensa;
    int oro;
    int xp_sig_lvl;
    int xp_actual;
    int lvl;
    int puntos_de_habilidad;

}personaje;

personaje IniciarPJ();    //funciones para la creacion de un nuevo pj
void CrearNuevoPersonaje();

personaje cargar_personaje();//funciones para el guardado y carga de personaje
void guardar_personaje(personaje pj);

void subir_vida_mana(personaje * pj);
personaje subir_de_nivel(personaje pj);//funciones para la subida de nivel del personaje
void subir_un_atributo(personaje * pj);

void mostrar_personaje(personaje pj);//funcion para mostrar el personaje

#endif // PERSONAJE_H_INCLUDED
