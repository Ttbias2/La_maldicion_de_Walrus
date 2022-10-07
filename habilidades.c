#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personaje.h"
#include "habilidades.h"

arbol_habilidades * inic_arbol()
{
    return NULL;
}

habilidad crear_habilidad()
{
    habilidad aux;

    printf("nombre de la habilidad: ");
    fflush(stdin);
    gets(aux.nombre);

    printf("descripcion: ");
    fflush(stdin);
    gets(aux.descripcion);

    printf("danio: ");
    scanf("%i",&aux.danio);

    printf("danio extra: ");
    scanf("%i",&aux.mas_danio);

    printf("mas defensa: ");
    scanf("%i",&aux.mas_defensa);

    printf("curacion: ");
    scanf("%i",&aux.mas_vida);

    printf("coste de mana: ");
    scanf("%i",&aux.coste_mana);

    printf("coste de desbloqueo: ");
    scanf("%i",&aux.coste_desbloqueo);

    printf("numero: ");
    scanf("%i",&aux.numero);

    printf("desbloqueada: ");
    scanf("%i",&aux.desbloqueado);

    return aux;
}

void limpiar_archivo_arbol()
{
    FILE * arch=fopen(ArchArbol,"wb");

    fclose(arch);
}

void cargar_archivo_arbol(habilidad aux)
{
    FILE * arch=fopen(ArchArbol,"ab");

    fwrite(&aux,sizeof(habilidad),1,arch);

    fclose(arch);
}

void guardar_habilidades(arbol_habilidades * arbol)
{
    if(arbol != NULL)
    {
        cargar_archivo_arbol(arbol->magia);
        guardar_habilidades(arbol->izquierda);
        guardar_habilidades(arbol->derecha);
    }
}

arbol_habilidades * traer_habilidades_de_archivo(arbol_habilidades * arbol)
{
    habilidad aux;

    FILE * arch=fopen(ArchArbol,"rb");

    while(fread(&aux,sizeof(habilidad),1,arch))
    {
        arbol=cargar_arbol(arbol,aux);
    }

    fclose(arch);

    return arbol;
}

void mostrar_habilidad(habilidad aux)
{
    printf("\n=======================================\n");
    printf("\n%i\n",aux.numero);

    printf("\nNombre de la habilidad: ");
    puts(aux.nombre);

    printf("Descripcion: ");
    puts(aux.descripcion);

    printf("Danio: %i",aux.danio);

    printf("\nDanio extra: %i",aux.mas_danio);

    printf("\nDefensa extra: %i",aux.mas_defensa);

    printf("\nCuracion: %i",aux.mas_vida);

    printf("\nCoste de mana: %i",aux.coste_mana);

    if(aux.desbloqueado==0)
    {
        printf("\nCoste de desbloqueo: %i",aux.coste_desbloqueo);
    }
    printf("\n\n=======================================\n");
}

void mostrar_habilidades_desbloqueadas(arbol_habilidades * arbol)
{
    if(arbol != NULL)
    {
        mostrar_habilidades_desbloqueadas(arbol->izquierda);
        if(arbol->magia.desbloqueado>=1)
        {
            mostrar_habilidad(arbol->magia);
        }
        mostrar_habilidades_desbloqueadas(arbol->derecha);
    }

}

arbol_habilidades * crear_nodo_arbol(habilidad aux)
{
    arbol_habilidades * nodo=(arbol_habilidades*)malloc(sizeof(arbol_habilidades));

    nodo->magia=aux;
    nodo->izquierda=NULL;
    nodo->derecha=NULL;

    return nodo;
}

arbol_habilidades * cargar_arbol(arbol_habilidades * arbol,habilidad aux)
{
    if(arbol==NULL)
    {
        arbol=crear_nodo_arbol(aux);

    }
    else
    {
        if(aux.numero<arbol->magia.numero)
        {
            arbol->izquierda=cargar_arbol(arbol->izquierda,aux);
        }
        else
        {
            arbol->derecha=cargar_arbol(arbol->derecha,aux);
        }
    }

    return arbol;
}

int mostrar_opciones(arbol_habilidades * arbol,int opciones[],int i)//muestra las opciones para desbloquear, solo pueden ser 2
{
    if(arbol != NULL)
    {
        if(arbol->magia.desbloqueado==0 && i<2)
        {
            mostrar_habilidad(arbol->magia);
            opciones[i]=arbol->magia.numero;
            i++;
        }
        else
        {
            i=mostrar_opciones(arbol->izquierda,opciones,i);
            i=mostrar_opciones(arbol->derecha,opciones,i);
        }
    }


    return i;
}

int esta_en_el_arreglo(int opc[],int eleccion,int i)//se usa para comprobar si un dato el egido es valido
{
    int flag=-1;

    for(int f=0; f<i; f++)
    {
        if(eleccion==opc[f])
        {
            flag=1;
        }
    }

    return flag;
}

void cambiar_bloqueo(arbol_habilidades * arbol,int a_desbloquear,personaje pj)
{
    if(arbol != NULL)
    {
        if(arbol->magia.numero==a_desbloquear)//cuando encruentra la magia se comprueba si es desbloqueable
        {
            if(pj.puntos_de_habilidad>=arbol->magia.coste_desbloqueo)
            {
                pj.puntos_de_habilidad-=arbol->magia.coste_desbloqueo;
                arbol->magia.desbloqueado=1;
                guardar_personaje(pj);
            }
            else
            {
                printf("\n\nno tiene puntos de mana suficientes como para desbloquear esta habilidad\n\n");
                system("pause");
            }
        }
        else
        {
            if(arbol->magia.numero>a_desbloquear)
            {
                cambiar_bloqueo(arbol->izquierda,a_desbloquear,pj);//busca la magia
            }
            else
            {
                cambiar_bloqueo(arbol->derecha,a_desbloquear,pj);
            }
        }
    }
}

void desbloquear_habilidades()
{
    int opciones[2];

    int i=0,es_posible=-1,eleccion=0;

    arbol_habilidades * arbol=inic_arbol();

    arbol=traer_habilidades_de_archivo(arbol);

    i=mostrar_opciones(arbol,opciones,i);

    printf("\n\nQue habilidad desea desbloquear? ");

    do
    {
        scanf("%i",&eleccion);
        es_posible=esta_en_el_arreglo(opciones,eleccion,i);
        if(es_posible==-1)//es igual a -1 ya que 0 se us para salir del arreglo
        {
            printf("\nOpcion no valida, selecione una valida o presione 0 para cancelar: ");
        }

    }
    while(es_posible == -1 && eleccion!=0);

    if(es_posible != 0)//si no se cancelo la subida de nivel, se hace todo el desbloqueo y guardado de pj
    {
        personaje pj;

        pj=cargar_personaje();

        cambiar_bloqueo(arbol,eleccion,pj);

        limpiar_archivo_arbol();
        guardar_habilidades(arbol);
    }

    system("cls");

}

void mostrar_arbol(arbol_habilidades * arbol)
{
    if(arbol != NULL)
    {
        mostrar_arbol(arbol->izquierda);
        mostrar_habilidad(arbol->magia);
        mostrar_arbol(arbol->derecha);
    }
}

void devolver_habilidades_0(arbol_habilidades * arbol)
{
    if(arbol!=NULL)
    {
        arbol->magia.desbloqueado=0;
        devolver_habilidades_0(arbol->izquierda);
        devolver_habilidades_0(arbol->derecha);
    }

}

habilidad traer_habilidad(arbol_habilidades * arbol,int num)
{
    habilidad aux;
    if(arbol!=NULL)
    {
        if(arbol->magia.numero==num)
        {
            aux=arbol->magia;
        }
        else
        {
            if(num>arbol->magia.numero)
            {
                aux=traer_habilidad(arbol->derecha,num);
            }
            else
            {
                aux=traer_habilidad(arbol->izquierda,num);
            }

        }
    }

    return aux;
}




