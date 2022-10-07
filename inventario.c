#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"

objeto crear_objeto()
{
    objeto aux;

    printf("nombre: ");
    fflush(stdin);
    gets(aux.nombre);

    printf("recuperacion de vida: ");
    scanf("%i",&aux.mas_vida);

    printf("recuperacion de mana: ");
    scanf("%i",&aux.mas_mana);

    aux.cantidad=0;

    printf("1 utilizable, 2 no utilizable: ");
    scanf("%i",&aux.utilizable);

    return aux;
}

void mostrar_objeto(objeto aux)
{
    puts(aux.nombre);

    if(aux.utilizable==1)
    {
      printf("vida +%i",aux.mas_vida);
      printf("\nmana +%i\n",aux.mas_mana);
    }
    printf("cantidad %i\n",aux.cantidad);
    printf("-------------------------------------------------------------\n");
}

void mostrar_lista_objetos(nodo * lista)
{
    int i=0;
    nodo * seg=lista;

    while(seg != NULL)
    {
        printf("%i\n",i);//para identificar los objetos a un numero
        mostrar_objeto(seg->dato);
        seg=seg->siguiente;
        i++;
    }

}

void mostrar_mochila(mochila aux[])
{
    for(int i=0;i<dim;i++)
    {
        mostrar_lista_objetos(aux[i].lista_obj);
    }
}

nodo * inicnodo_obj()
{
    return NULL;
}

nodo * crear_nodo_obj(objeto dato)
{
    nodo * aux=(nodo*)malloc(sizeof(nodo));

    aux->dato=dato;
    aux->siguiente=NULL;

    return aux;
}

nodo * buscar_ultimo(nodo * lista)
{
    nodo * seg=lista;

    while(seg->siguiente != NULL)
    {
        seg=seg->siguiente;
    }

    return seg;
}

nodo * agregar_al_final(nodo * lista,nodo * nuevonodo)
{
    if(lista==NULL)
    {
        lista=nuevonodo;
    }
    else
    {
        nodo * ultimo=buscar_ultimo(lista);
        ultimo->siguiente=nuevonodo;
    }

    return lista;
}

void iniciar_mochila(mochila aux[])//inicia las dos listas dentro de la mochila
{
    aux[0].lista_obj=inicnodo_obj();
    aux[1].lista_obj=inicnodo_obj();
}

void guardar_mochila(mochila aux[])
{
    limpiar_archivo_objetos();//limpia el archivo, pq si no abria todo repetido y daria errores

    for (int i=0;i<dim;i++)
    {
        while(aux[i].lista_obj != NULL)
        {
           cargar_archivo_objetos(aux[i].lista_obj->dato);
           aux[i].lista_obj=aux[i].lista_obj->siguiente;
        }
    }
}

void cargar_archivo_objetos(objeto aux)
{
    FILE * arch=fopen(ArchObjetos,"ab");

    fwrite(&aux,sizeof(objeto),1,arch);

    fclose(arch);
}

void traer_mochila(mochila aux[])
{
    objeto obj;
    nodo * nuevonodo;

    FILE * arch=fopen(ArchObjetos,"rb");

    while(fread(&obj,sizeof(objeto),1,arch)>0)
    {
        nuevonodo=crear_nodo_obj(obj);

       if(obj.utilizable==1)//dependiendo si el objeto es utilisable o no se guardara en una lista u otra
       {
           aux[0].lista_obj=agregar_al_final(aux[0].lista_obj,nuevonodo);
       }
       else
       {
           aux[1].lista_obj=agregar_al_final(aux[1].lista_obj,nuevonodo);
       }

    }

    fclose(arch);
}

void limpiar_archivo_objetos()
{
    FILE * arch=fopen(ArchObjetos,"wb");

    fclose(arch);
}

void aumentar_cantidad(int aumento,mochila invent[],char bojeto[])
{
    nodo * seg=inicnodo_obj();
    int i=0,flag=0;

    while (i<dim && flag==0)
    {
        seg=invent[i].lista_obj;

        while(strcmpi(seg->dato.nombre,bojeto)!=0 && seg != NULL)
        {
            seg=seg->siguiente;
        }


        if(seg != NULL)
        {
            flag=1;
            seg->dato.cantidad+=aumento;
        }
        else
        {
            i++;
        }

    }

}

void devolver_cantidades_0(mochila invent[])
{
    nodo * seg=NULL;

    for(int i=0;i<dim;i++)
    {
        seg=invent[i].lista_obj;
        while(seg != NULL)
        {
            seg->dato.cantidad=0;
            seg=seg->siguiente;
        }
    }
}





