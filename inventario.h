#ifndef INVENTARIO_H_INCLUDED
#define INVENTARIO_H_INCLUDED
#define ArchObjetos "ArchObjetos"
#define dim 2

typedef struct
{
    char nombre[20];
    int mas_vida;
    int mas_mana;
    int cantidad;
    int utilizable;

}objeto;

typedef struct
{

    objeto dato;
    struct nodo * siguiente;

}nodo;

typedef struct
{
    nodo * lista_obj;

}mochila;

objeto crear_objeto();//crea un objeto

void mostrar_objeto(objeto aux);
void mostrar_lista_objetos(nodo * lista);//funciones para mostrar objetos
void mostrar_mochila(mochila aux[]);

nodo * inicnodo_obj();
nodo * crear_nodo_obj(objeto dato); //funciones para cargar las listas de objetos
nodo * buscar_ultimo(nodo * lista);
nodo * agregar_al_final(nodo * lista,nodo * nuevonodo);

void iniciar_mochila(mochila aux[]);
void guardar_mochila(mochila aux[]);
void cargar_archivo_objetos(objeto aux);//funciones para guardar/cargar objetos
void traer_mochila(mochila aux[]);
void limpiar_archivo_objetos();

void aumentar_cantidad(int aumento,mochila invent[],char bojeto[]);//funciones para cambiar las cantidades de los objetos
void devolver_cantidades_0(mochila invent[]);

#endif // INVENTARIO_H_INCLUDED
