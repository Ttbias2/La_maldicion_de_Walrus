#ifndef BATALLAS_H_INCLUDED
#define BATALLAS_H_INCLUDED

typedef struct
{
    stEnemigo enemigo;
    struct lista_enemigos * siguiente;

}lista_enemigos;

lista_enemigos * inicilista_enem();
lista_enemigos * crear_nodo_listenem(stEnemigo enemigo);
lista_enemigos * agregar_al_principio_enem(lista_enemigos * lista,lista_enemigos * nuevonodo);
lista_enemigos * cargar_lista_ene(int mundo,int num_pelea,lista_enemigos * lista);
int mostrar_lista_enemigos(lista_enemigos * lista);
void visual_batalla(personaje pj,lista_enemigos * lista);
void salir_del_pueblo();
int ataque_de_personaje(personaje * pj);
int usar_habilidad(personaje * pj);
int usar_objeto(personaje * pj);
lista_enemigos * borrar_enemigos(lista_enemigos * enemigos,int pocicion);
lista_enemigos * hacer_danio(int danio,lista_enemigos * enemigos);
int ataque_de_enemigos(lista_enemigos * enemigos);
int cantidad_xp(lista_enemigos * enemigos);
int cantidad_oro(lista_enemigos * enemigos);
void recompenza_material(int num_pelea,int mundo);
void creditos();

#endif // BATALLAS_H_INCLUDED
