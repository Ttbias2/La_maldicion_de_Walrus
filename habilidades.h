#ifndef HABILIDADES_Y_OBJETOS_H_INCLUDED
#define HABILIDADES_Y_OBJETOS_H_INCLUDED
#define ArchArbol "ArchArbol"


typedef struct
{
    char nombre[20];
    char descripcion[50];

    int danio;
    int mas_danio;
    int mas_vida;
    int mas_defensa;
    int coste_mana;

    int coste_desbloqueo;
    int numero;
    int desbloqueado;

}habilidad;

typedef struct
{
    habilidad magia;
    struct arbol_habilidades * izquierda;
    struct arbol_habilidades * derecha;

}arbol_habilidades;

arbol_habilidades * inic_arbol();//crear nondos de habilidad
habilidad crear_habilidad();

void limpiar_archivo_arbol();
void cargar_archivo_arbol(habilidad aux); //funciones relacionadas a la carga y guardado de las habilidades
void guardar_habilidades(arbol_habilidades * arbol);
arbol_habilidades * traer_habilidades_de_archivo(arbol_habilidades * arbol);

void mostrar_habilidad(habilidad aux);
void mostrar_habilidades_desbloqueadas(arbol_habilidades * arbol);//funciones para mostrar las habilidades
void mostrar_arbol(arbol_habilidades * arbol);

arbol_habilidades * cargar_arbol(arbol_habilidades * arbol,habilidad aux);
arbol_habilidades * crear_nodo_arbol(habilidad aux);//crear nodos de habilidad

int mostrar_opciones(arbol_habilidades * arbol,int opciones[],int i);
int esta_en_el_arreglo(int opc[],int eleccion,int i);
void cambiar_bloqueo(arbol_habilidades * arbol,int a_desbloquear,personaje pj);//funciones relacionadas al desbloqueo de habilidades
void desbloquear_habilidades();
void devolver_habilidades_0(arbol_habilidades * arbol);
habilidad traer_habilidad(arbol_habilidades * arbol,int num);

#endif // HABILIDADES_Y_OBJETOS_H_INCLUDED
