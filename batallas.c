#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "personaje.h"
#include "habilidades.h"
#include "inventario.h"
#include "enemigos.h"
#include "batallas.h"

void creditos()
{
    system("cls");
    printf("FELICITACIONES, HAS CONSEGUIDO ACABAR CON LA MALDICION DEL PUEBLO");
    printf("PERO NO TE CONFIES, TODAVIA HAY MONSTRUOS AHI AFUERA Y ES TU DEBER");
    printf("ACABAR CON ELLOS");

}

lista_enemigos * inicilista_enem()
{
    return NULL;
}

lista_enemigos * crear_nodo_listenem(stEnemigo enemigo)
{
    lista_enemigos * aux=(lista_enemigos*)malloc(sizeof(lista_enemigos));

    aux->enemigo=enemigo;
    aux->siguiente=NULL;
}

lista_enemigos * agregar_al_principio_enem(lista_enemigos * lista,lista_enemigos * nuevonodo)
{
    if(lista == NULL)
    {
        lista=nuevonodo;
    }
    else
    {
        nuevonodo->siguiente=lista;
        lista=nuevonodo;
    }

    return lista;
}

lista_enemigos * cargar_lista_ene(int mundo,int num_pelea,lista_enemigos * lista)
{
    stEnemigo enemigo;
    lista_enemigos * nuevonodo;

    if(num_pelea != 4)
    {
        if(num_pelea==0 && mundo==1)
        {
          FILE * arch=fopen(ArchEnemigos_M1,"rb");

          fread(&enemigo,sizeof(enemigo),1,arch);

          fclose(arch);

          for (int i=0;i<3;i++)
          {
              nuevonodo=crear_nodo_listenem(enemigo);
              lista=agregar_al_principio_enem(lista,nuevonodo);
          }

        }
        else
        {
          for (int i=0; i<3; i++)
         {
            enemigo=BuscarEnemigos(mundo);
            nuevonodo=crear_nodo_listenem(enemigo);
            lista=agregar_al_principio_enem(lista,nuevonodo);
         }
        }

    }
    else
    {
        enemigo=BuscarJefe(mundo);
        nuevonodo=crear_nodo_listenem(enemigo);
        lista=agregar_al_principio_enem(lista,nuevonodo);
    }

    return lista;
}

int mostrar_lista_enemigos(lista_enemigos * lista)
{
    lista_enemigos * seg=lista;
    int i=0;

    while(seg != NULL)
    {
        printf("-------------------------\n");
        printf("%i\n",i);
        mostrar_enemigo(seg->enemigo);
        seg=seg->siguiente;
        i++;
    }

    return i;
}

void visual_batalla(personaje pj,lista_enemigos * lista)
{
    mostrar_personaje(pj);

    printf("\n---------------\n");
    printf("|  enemigos   |\n");
    printf("---------------\n");

    mostrar_lista_enemigos(lista);
}

int usar_habilidad(personaje * pj)
{
    int danio=0,cual_usar=0,esta=0,puerta_1=0,puerta_2=0;
    habilidad a_usar;
    arbol_habilidades * arbol=inic_arbol();
    arbol=traer_habilidades_de_archivo(arbol);

    system("cls");

    mostrar_habilidades_desbloqueadas(arbol);

    do
    {
        printf("\nQue habilidad desea usar(0 para salir): ");
        scanf("%i",&cual_usar);

        if(cual_usar != 0)
        {
            if(cual_usar>=0 && cual_usar<=9)
            {
                puerta_1=1;
            }
            else
            {
                printf("\nEsa habilidad no existe\n");
            }

            if(puerta_1==1)
            {
                a_usar=traer_habilidad(arbol,cual_usar);


                if(a_usar.desbloqueado==0)
                {
                    printf("\nLa habilidad no esta desbloqueada aun, ");
                    puerta_1=0;
                }
                else
                {
                    puerta_2=1;
                    if(a_usar.coste_mana>pj->mana)
                    {
                        printf("\nNo tiene suficiente mana\n\n");
                        cual_usar=0;
                    }
                }
            }

        }
        else
        {
            puerta_1=1;
            puerta_2=1;
        }



    }
    while(puerta_1==0 || puerta_2==0);

    if(cual_usar == 0)
    {
        danio=-1;
    }
    else
    {
        danio=a_usar.danio*pj->danio_magico;

        pj->vida+=a_usar.mas_vida;

        if(pj->vida>pj->vida_max)
        {
            pj->vida=pj->vida_max;
        }

        pj->danio+=a_usar.mas_danio;
        pj->defensa+=a_usar.mas_defensa;
        pj->mana-=a_usar.coste_mana;
    }

    return danio;
}

int usar_objeto(personaje * pj)
{
    system("cls");

    int cual_usar=0,danio=-1;
    mochila invent[dim];
    iniciar_mochila(invent);
    traer_mochila(invent);

    mostrar_mochila(invent);

    do
    {
     printf("cual objeto quieres usar: ");
     scanf("%i",&cual_usar);

     if(cual_usar<0 || cual_usar>8)
     {
         printf("ese objeto no existe, ");
     }

    }while(cual_usar<0 || cual_usar>8);

    nodo * seg=invent[0].lista_obj;

    for(int i=0;i<cual_usar;i++)
    {
        seg=seg->siguiente;
    }

    if(seg->dato.cantidad==0)
    {
        printf("no tiene ese objeto\n\n");
    }
    else
    {
        seg->dato.cantidad--;

        pj->vida+=seg->dato.mas_vida;
        if(pj->vida>pj->vida_max)
        {
            pj->vida=pj->vida_max;
        }

        pj->mana+=seg->dato.mas_mana;
        if(pj->mana>pj->mana_max)
        {
            pj->mana=pj->mana_max;
        }
        danio=0;

        guardar_mochila(invent);
    }

    system("pause");
    system("cls");

    return danio;
}

int ataque_de_personaje(personaje * pj)
{
    int opcion=0,danio=-1;

    while(danio<0)
    {


            printf("1: ataque fisico\n");
            printf("2: habilidad\n");
            printf("3: objetos\n");

            do
            {
                scanf("%i",&opcion);
            }
            while(opcion<1 || opcion > 3);

            switch(opcion)
            {
            case 1:
            {
                danio=pj->danio;
                break;
            }
            case 2:
            {
                danio=usar_habilidad(pj);
                break;
            }
            case 3:
                {
                 danio=usar_objeto(pj);
                 break;
                }

            }

    }

    return danio;
}

lista_enemigos * borrar_enemigos(lista_enemigos * enemigos,int pocicion)
{
    lista_enemigos * seg=enemigos;
    lista_enemigos * anterior=inicilista_enem();
    lista_enemigos * aborrar=inicilista_enem();

    for(int i=0;i<pocicion;i++)
    {
        anterior=seg;
        seg=seg->siguiente;
    }

    if(seg==enemigos)
    {
        aborrar=enemigos;
        enemigos=enemigos->siguiente;
        free(aborrar);
    }
    else
    {
        anterior->siguiente=seg->siguiente;
        free(seg);
    }

    return enemigos;
}

lista_enemigos * hacer_danio(int danio,lista_enemigos * enemigos)
{
   int i=0,a_atacar=0;

   i=mostrar_lista_enemigos(enemigos);

   printf("que enemigo desea atacar: ");

   do
   {
       scanf("%i",&a_atacar);
   }while(a_atacar<0 || a_atacar>=i);

   lista_enemigos * seg=enemigos;

   for (int f=0;f<a_atacar;f++)
   {
       seg=seg->siguiente;
   }

   seg->enemigo.vida-=danio;

   if(seg->enemigo.vida<=0)
   {
       enemigos=borrar_enemigos(enemigos,a_atacar);
   }

   return enemigos;

}

int ataque_de_enemigos(lista_enemigos * enemigos)
{
   int danio_enemig=0,i=0;

   lista_enemigos * seg=enemigos;

   while(seg != NULL)
   {
       puts(seg->enemigo.Nombre);
       printf("ataca haciendo %i de danio\n",seg->enemigo.danio);
       sleep(1);
       danio_enemig+=seg->enemigo.danio;
       seg=seg->siguiente;
   }

    system("cls");

   return danio_enemig;
}

int cantidad_xp(lista_enemigos * enemigos)
{
    int xp=0;
    lista_enemigos * seg=enemigos;

    while(seg != NULL)
    {
        xp+=seg->enemigo.xp;
        seg=seg->siguiente;
    }

    return xp;
}

int cantidad_oro(lista_enemigos * enemigos)
{
    int oro=0;
    lista_enemigos * seg=enemigos;

    while(seg != NULL)
    {
        oro+=seg->enemigo.Moneda;
        seg=seg->siguiente;
    }

    return oro;
}

void recompenza_material(int num_pelea,int mundo)
{
    mochila invent[dim];
    iniciar_mochila(invent);
    traer_mochila(invent);

    if(num_pelea==4)
    {
        aumentar_cantidad(1,invent,"diamante");
    }
    else if(mundo==1)
    {
        aumentar_cantidad(1,invent,"cuero");
    }
    else if(mundo==2)
    {
        aumentar_cantidad(1,invent,"hierro");
    }
    else
    {
        aumentar_cantidad(1,invent,"oro");
    }

    guardar_mochila(invent);

}

void salir_del_pueblo()
{
    int mundo=1,num_pelea=0,danio=0,danio_enemigo=0,premio_xp=0,premio_oro=0,agilidad=0;
    char continuar='s';
    personaje pj=cargar_personaje();
    personaje Aux;
    lista_enemigos * enemigos=inicilista_enem();

    pj.vida=pj.vida_max;
    pj.mana=pj.mana_max;

    while(continuar=='s' && mundo<=3)
    {
        if(mundo==1)
        {
            system("color 20");
        }
        else if(mundo==2)
        {
            system("color f0");
        }
        else
        {
            system("color 40");
        }

        enemigos=cargar_lista_ene(mundo,num_pelea,enemigos);
        premio_oro=cantidad_oro(enemigos);
        premio_xp=cantidad_xp(enemigos);

        while(pj.vida>0 && enemigos != NULL)
        {
            visual_batalla(pj,enemigos);
            danio=ataque_de_personaje(&pj);

            system("cls");

            if(danio>0)
            {
             enemigos=hacer_danio(danio,enemigos);
            }

            system("cls");

            agilidad=rand()%100+1;

            danio_enemigo=ataque_de_enemigos(enemigos);
            danio_enemigo-=pj.defensa;

            if(agilidad<pj.agilidad)
            {
                danio_enemigo=0;
                puts(pj.nombre);
                printf("pudo esquivar los ataques");
                sleep(2);
                system("cls");
            }

            if(danio_enemigo>0)
            {
             pj.vida-=danio_enemigo;
            }
        }

        if(pj.vida<=0)
        {
            puts(pj.nombre);
            printf("\nSufrio eridas graves y tuvo que ir al hospital(la salud es privada por lo que le sacaron 50%% de las monedas)\n\n");
            sleep(3);
            pj.vida=pj.vida_max;
            pj.mana=pj.mana_max;
            pj.oro=pj.oro/2;
            continuar='n';
        }
        else
        {
            Aux=cargar_personaje();
            pj.danio=Aux.danio;
            pj.defensa=Aux.defensa;
            printf("\nTu recompenza de oro es: %i",premio_oro);
            printf("\nTu recompenza de xp es: %i",premio_xp);
            pj.xp_actual+=premio_xp;
            pj.oro+=premio_oro;
            mostrar_personaje(pj);

            if(pj.xp_actual>=pj.xp_sig_lvl)
            {
                pj=subir_de_nivel(pj);
            }

            recompenza_material(num_pelea,mundo);

            printf("\nDesea continuar?(s/n): ");
            fflush(stdin);
            scanf("%c",&continuar);

            system("cls");

            num_pelea++;
            if(num_pelea>4)
            {
                num_pelea=0;
                mundo++;
            }

        }

        guardar_personaje(pj);

    }

    pj.vida=pj.vida_max;
    pj.mana=pj.mana_max;

    guardar_personaje(pj);

    system("color 0f");
    if(mundo>3)
    {
        creditos();
    }
    system("cls");


}









