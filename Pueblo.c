#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "Pueblo.h"
#define precioVidaMenor 15
#define precioVidaMedia 30
#define precioVidaMayor 50
#define precioManaMenor 15
#define precioManaMedia 30
#define precioManaMayor 50
#define precioElixirMenor 30
#define precioElixirMedia 50
#define precioElixirMayor 75

void devolver_herrero_0()
{
    int i=0;

    FILE * arch=fopen(ArchArmadura,"wb");
    fwrite(&i,sizeof(int),1,arch);
    fclose(arch);                 //hace que el archivo de armas y armadura quede en 0

    FILE * archi=fopen(ArchEspada,"wb");
    fwrite(&i,sizeof(int),1,archi);
    fclose(arch);
}

personaje mejorar_armadura(personaje pj)
{
    mochila invent[dim];
    iniciar_mochila(invent);//trae la mochila para verificar que tienes los objetos nesesario para subir
    traer_mochila(invent);
    int lvl=0,cantidad=0;

    nodo * seg=invent[1].lista_obj;

    FILE * arch=fopen(ArchArmadura,"rb");//se trae el nivel actual del arma

    fread(&lvl,sizeof(int),1,arch);

    fclose(arch);

    if(lvl<5)//dependiendo de que nivel sea el arma la lista de objetos se movera hasta ese punto y verificara si tienes los materiales suficientes
    {
        if(lvl==0)
        {
         cantidad=lvl+1;
        }
        else
        {
         cantidad=lvl;
        }

        if(seg->dato.cantidad>cantidad)
        {
            seg->dato.cantidad-=cantidad;
            lvl++;
            pj.defensa+=1;
            printf("\nArmadura mejorada\n");
        }
        else
        {
            printf("\nNo tiene suficientes materiales\n");
        }

    }
    else if(lvl>=5 && lvl<10)
    {
        cantidad=lvl-5;
        seg=seg->siguiente;

        if(seg->dato.cantidad>cantidad)
        {
            seg->dato.cantidad-=cantidad;
            lvl++;
            pj.defensa+=1;
            printf("\nArmadura mejorada\n");
        }
        else
        {
            printf("\nNo tiene suficientes materiales\n");
        }
    }
    else if(lvl>=10 && lvl<15)
    {
        cantidad=lvl-10;
        for (int i=0; i<2; i++)
        {
            seg=seg->siguiente;
        }

        if(seg->dato.cantidad>cantidad)
        {
            seg->dato.cantidad-=cantidad;
            lvl++;
            pj.defensa+=2;
            printf("\nArmadura mejorada\n");
        }
        else
        {
            printf("\nNo tiene suficientes materiales\n");
        }

    }
    else
    {
        cantidad=lvl-15;
        for (int i=0; i<3; i++)
        {
            seg=seg->siguiente;
        }

        if(seg->dato.cantidad>cantidad)
        {
            seg->dato.cantidad-=cantidad;
            lvl++;
            pj.defensa+=4;
            printf("\nArmadura mejorada\n");
        }
        else
        {
            printf("\nNo tiene suficientes materiales\n");
        }
    }

    FILE * archi=fopen(ArchArmadura,"wb");

    fwrite(&lvl,sizeof(int),1,archi); //guarda el archivo actualizado(si se subio de nivel)

    fclose(archi);

    system("pause");

    guardar_mochila(invent); //la guarda con los materiales restados

    system("cls");

    return pj;//retorna el pj actualizado
}

personaje mejorar_arma(personaje pj)//funciona exactamente como la funcion mejorar_armadura pero con el archivo de arma
{
    mochila invent[dim];
    iniciar_mochila(invent);
    traer_mochila(invent);
    int lvl=0,cantidad=0;

    nodo * seg=invent[1].lista_obj;

    FILE * arch=fopen(ArchEspada,"rb");

    fread(&lvl,sizeof(int),1,arch);

    fclose(arch);

    if(lvl<5)
    {
        if(lvl==0)
        {
         cantidad=lvl+1;
        }
        else
        {
         cantidad=lvl;
        }

        if(seg->dato.cantidad>cantidad)
        {
            seg->dato.cantidad-=cantidad;
            lvl++;
            pj.danio+=5;
            printf("\nArma mejorada\n");
        }
        else
        {
            printf("\nNo tiene suficientes materiales\n");
        }

    }
    else if(lvl>=5 && lvl<10)
    {
        cantidad=lvl-5;
        seg=seg->siguiente;

        if(seg->dato.cantidad>cantidad)
        {
            seg->dato.cantidad-=cantidad;
            lvl++;
            pj.danio+=5;
            printf("\nArma mejorada\n");
        }
        else
        {
            printf("\nNo tiene suficientes materiales\n");
        }
    }
    else if(lvl>=10 && lvl<15)
    {
        cantidad=lvl-10;
        for (int i=0; i<2; i++)
        {
            seg=seg->siguiente;
        }

        if(seg->dato.cantidad>cantidad)
        {
            seg->dato.cantidad-=cantidad;
            lvl++;
            pj.danio+=5;
            printf("\nArma mejorada\n");
        }
        else
        {
            printf("\nNo tiene suficientes materiales\n");
        }

    }
    else
    {
        cantidad=lvl-15;
        for (int i=0; i<3; i++)
        {
            seg=seg->siguiente;
        }

        if(seg->dato.cantidad>cantidad)
        {
            seg->dato.cantidad-=cantidad;
            lvl++;
            pj.danio+=5;
            printf("\nArma mejorada\n");
        }
        else
        {
            printf("\nNo tiene suficientes materiales\n");
        }
    }

    FILE * archi=fopen(ArchEspada,"wb");

    fwrite(&lvl,sizeof(int),1,archi);

    fclose(archi);

    guardar_mochila(invent);

    return pj;
}

void mostrar_nesesidades_de_objetos()//abre ambos archivos y dependiendo del nivel de el arma o de la armadura muestra lo nesesario para mejorar
{
    int nesesita_arma=0,nesesita_armadura=0;

    FILE * arch=fopen(ArchArmadura,"rb");
    fread(&nesesita_armadura,sizeof(int),1,arch);
    fclose(arch);

    FILE * archi=fopen(ArchEspada,"rb");
    fread(&nesesita_arma,sizeof(int),1,archi);
    fclose(archi);

    if(nesesita_arma==0)
    {
        nesesita_arma++;
    }

    if(nesesita_armadura==0)
    {
        nesesita_armadura++;
    }

    printf("1: arma nesesita %i de ",nesesita_arma);
    if(nesesita_arma<5)
    {
        printf("cuero\n");
    }
    else if(nesesita_arma>=5 && nesesita_arma<10)
    {
        printf("hierro\n");
    }
    else if(nesesita_arma>=10 && nesesita_arma<15)
    {
        printf("oro\n");
    }
    else
    {
        printf("diamante\n");
    }

    printf("2: armadura nesesita %i de ",nesesita_armadura);
    if(nesesita_arma<5)
    {
        printf("cuero\n");
    }
    else if(nesesita_armadura>=5 && nesesita_armadura<10)
    {
        printf("hierro\n");
    }
    else if(nesesita_armadura>=10 && nesesita_armadura<15)
    {
        printf("oro\n");
    }
    else
    {
        printf("diamante\n");
    }

}

void herrero()
{
    animacion_puerta();
    personaje pj;
    pj=cargar_personaje();
    int opcion=0;

    mostrar_nesesidades_de_objetos();
    printf("3: salir\n");

    do
    {
        scanf("%i",&opcion); //comprueba que la opcion sea valida
    }
    while(opcion<1 || opcion>3);

    switch (opcion)//dependiendo de la opcion se hara lo elegido
    {
    case 1:
    {
        if(pj.danio>=100)
        {
            pj=mejorar_arma(pj); //para mejorar el personaje la fuerza debe estar al maximo, si no dara error, mejorar en futuras versiones
        }
        else
        {
            printf("\nTodavia no puedes mejorar el arma, primero sube el danio al maximo\n\n");
            system("pause");
            system("cls");
        }
        break;
    }
    case 2:
    {
        pj=mejorar_armadura(pj);
        break;
    }
    case 3:
    {
        system("cls");
        animacion_puerta();
        break;
    }
    }

    guardar_personaje(pj);

}

void animacion_puerta()// pequeño "sprite"
{
    printf(" -----------\n");
    printf("|           |\n");
    printf("|           |\n");
    printf("|           |\n");
    printf("|           |\n");
    printf("|           |\n");
    printf("|         ()|\n");
    printf("|           |\n");
    printf("|           |\n");
    printf("|           |\n");
    printf("|           |\n");
    printf(" -----------\n");

    sleep(1);
    system("cls");

    printf(" -----------\n");
    printf("||          |\n");
    printf("||          |\n");
    printf("||          |\n");
    printf("||          |\n");
    printf("||          |\n");
    printf("||]         |\n");
    printf("||          |\n");
    printf("||          |\n");
    printf("||          |\n");
    printf("||          |\n");
    printf(" -----------\n");

    sleep(1);
    system("cls");
}

void mago()//funcion para subir habilidades
{
    animacion_puerta();
    personaje Aux = cargar_personaje();

    printf("\nBuen dia joven, que habilidad desea aprender?(0 para salir)");

    printf("\n\n*************************\n");
    printf("* PUNTOS DISPONIBLES: %d *\n",Aux.puntos_de_habilidad);
    printf("*************************\n");
    desbloquear_habilidades();
    system("cls");
    animacion_puerta();

}

void mostrar_invent_personaje()//muetra el personaje y el inventario
{
    personaje pj;
    pj=cargar_personaje();
    mostrar_personaje(pj);
    printf("\n");
    mochila invent[dim];
    iniciar_mochila(invent);
    traer_mochila(invent);
    mostrar_mochila(invent);
    system("pause");
    system("cls");
}

void Pueblo()//funcion principal de este archivo
{
    int opcion=0,flag=0;

    system("cls");

    printf("\n\n\t\t\t ___    ___    ___                       ___    ___    ___ \n");
    printf("\t\t\t|   |  |   |  |   |                     |   |  |   |  |   |\n");
    printf("\t\t\t|   |__|   |__|   |                     |   |__|   |__|   |\n");
    printf("\t\t\t|                 |                     |                 |\n");
    printf("\t\t\t|       ___       |_____________________|       ___       |\n");
    printf("\t\t\t|      (   )                                   (   )      |\n");
    printf("\t\t\t|     (     )           BIENVENIDO A          (     )     |\n");
    printf("\t\t\t|    |       |           ' WALRUS '          |       |    |\n");
    printf("\t\t\t|    |_______|        _______________        |_______|    |\n");
    printf("\t\t\t|                   (        |        )                   |\n");
    printf("\t\t\t|                  (         |         )                  |\n");
    printf("\t\t\t|                 (          |          )                 |\n");
    printf("\t\t\t|                 |          |          |                 |\n");
    printf("\t\t\t|                 |      U   |   U      |                 |\n");
    printf("\t\t\t|                 |          |          |                 |\n");
    printf("\t\t\t|_________________|__________|__________|_________________|\n");

    sleep(1);
    system("cls");

    printf("\n\n\t\t\t ___    ___    ___                       ___    ___    ___ \n");
    printf("\t\t\t|   |  |   |  |   |                     |   |  |   |  |   |\n");
    printf("\t\t\t|   |__|   |__|   |                     |   |__|   |__|   |\n");
    printf("\t\t\t|                 |                     |                 |\n");
    printf("\t\t\t|       ___       |_____________________|       ___       |\n");
    printf("\t\t\t|      (   )                                   (   )      |\n");
    printf("\t\t\t|     (     )           BIENVENIDO A          (     )     |\n");
    printf("\t\t\t|    |       |           ' WALRUS '          |       |    |\n");
    printf("\t\t\t|    |_______|        _______________        |_______|    |\n");
    printf("\t\t\t|                   (   |         |   )                   |\n");
    printf("\t\t\t|                  (    |         |    )                  |\n");
    printf("\t\t\t|                 (     |         |     )                 |\n");
    printf("\t\t\t|                 |     |         |     |                 |\n");
    printf("\t\t\t|                 |   u |         | u   |                 |\n");
    printf("\t\t\t|                 |     |         |     |                 |\n");
    printf("\t\t\t|_________________|_____|_________|_____|_________________|\n");

    sleep(1);
    system("cls");



    do
    {
        printf("  ______________________\n");
        printf(" |   _____   _        _ | \n");
        printf(" |  |__H__| |_|   _  |_|| \n");
        printf(" |  |_____|    _ |M|    | \n");
        printf(" |    _    _  |_| |     |__ \n");
        printf(" |   |_|  |_|   __|__  S __ \n");
        printf(" |      _   _   |   |   | \n");
        printf(" |     |_| |_|  |___|   | \n");
        printf(" |  _____   _  _  _   _ | \n");
        printf(" | |__T__| |_||_||_| |_|| \n");
        printf(" |______________________| \n");

        printf("\nDonde quiere dirigirse?\n");

        printf("\n 1 - TABERNA");
        printf("\n 2 - HERRERO");
        printf("\n 3 - DUMBLEDORE");
        printf("\n 4 - Ir a pelear");
        printf("\n 5 - ver inventario");
        printf("\n 0 - Guardar y salir\n\n");

         scanf("%d",&opcion);

        system("cls");

        switch(opcion)
        {
        case 1:
        {
            animacion_puerta();
            TABERNA();
            break;
        }
        case 2:
        {
            herrero();
            break;
        }
        case 3:
        {
            mago();
            break;
        }
        case 4:
        {
            system("cls");

            printf("\n\n\t\t\t ___    ___    ___                       ___    ___    ___ \n");
            printf("\t\t\t|   |  |   |  |   |                     |   |  |   |  |   |\n");
            printf("\t\t\t|   |__|   |__|   |                     |   |__|   |__|   |\n");
            printf("\t\t\t|                 |                     |                 |\n");
            printf("\t\t\t|       ___       |_____________________|       ___       |\n");
            printf("\t\t\t|      (   )                                   (   )      |\n");
            printf("\t\t\t|     (     )           SALIENDO DE           (     )     |\n");
            printf("\t\t\t|    |       |           ' WALRUS '          |       |    |\n");
            printf("\t\t\t|    |_______|        _______________        |_______|    |\n");
            printf("\t\t\t|                   (   |         |   )                   |\n");
            printf("\t\t\t|                  (    |         |    )                  |\n");
            printf("\t\t\t|                 (     |         |     )                 |\n");
            printf("\t\t\t|                 |     |         |     |                 |\n");
            printf("\t\t\t|                 |   u |         | u   |                 |\n");
            printf("\t\t\t|                 |     |         |     |                 |\n");
            printf("\t\t\t|_________________|_____|_________|_____|_________________|\n");

            sleep(1);
            system("cls");

            printf("\n\n\t\t\t ___    ___    ___                       ___    ___    ___ \n");
            printf("\t\t\t|   |  |   |  |   |                     |   |  |   |  |   |\n");
            printf("\t\t\t|   |__|   |__|   |                     |   |__|   |__|   |\n");
            printf("\t\t\t|                 |                     |                 |\n");
            printf("\t\t\t|       ___       |_____________________|       ___       |\n");
            printf("\t\t\t|      (   )                                   (   )      |\n");
            printf("\t\t\t|     (     )           SALIENDO DE           (     )     |\n");
            printf("\t\t\t|    |       |           ' WALRUS '          |       |    |\n");
            printf("\t\t\t|    |_______|        _______________        |_______|    |\n");
            printf("\t\t\t|                   (        |        )                   |\n");
            printf("\t\t\t|                  (         |         )                  |\n");
            printf("\t\t\t|                 (          |          )                 |\n");
            printf("\t\t\t|                 |          |          |                 |\n");
            printf("\t\t\t|                 |      U   |   U      |                 |\n");
            printf("\t\t\t|                 |          |          |                 |\n");
            printf("\t\t\t|_________________|__________|__________|_________________|\n");

            sleep(1);
            system("cls");

            salir_del_pueblo();

            break;
        }
        case 5:
            {
                mostrar_invent_personaje();
                break;
            }
        case 0:
        {
            flag=1;
            break;
        }
        }
    }
    while(flag==0);
}

void TABERNA()//funcion para obtener pociones
{
    int opcion=0,flag=0;

    printf("\n\n*****************************\n");
    printf("********** TABERNA **********\n");
    printf("*****************************\n\n");

    sleep(1);

    printf("Bienvenido a la Taberna, aqui podra descansar y comprar objetos para el combate.\n\n");

    sleep(3);

    do
    {
        system("cls");

        printf("Que desea hacer?\n\n");

        printf(" 1 - Comprar Objetos.\n");
        printf(" 0 - Salir\n\n");

        printf("\n... ");
        scanf("%d",&opcion);

        system("cls");

        switch(opcion)
        {
        case 1:
        {
            TIENDA();
            break;
        }
        case 0:
        {
            flag=1;
        }
        }
    }
    while(flag==0);
}

void TIENDA()//donde se compran
{
    int CompraTaberna=0,CantidadPota=0,flag=0,flag2=0;
    char Respuesta='s';

    do
    {
        do
        {
            flag2 = MenuDeCompra(&CompraTaberna,&CantidadPota);

            if(flag2==0)
            {
                flag = CargaDeCompra(CompraTaberna,CantidadPota);
                flag2=1;
                if(flag==0)
                {
                    printf("\nNo tienes las monedas suficientes para tu compra, prueba a comprar menos cantidad o conseguir mas monedas...\n\n");
                    sleep(4);
                }
            }
        }
        while((flag==0)&&(flag2==0));

        if(flag==1)
        {
            printf("\nDesea realizar otra compra?(s/n): ");
            fflush(stdin);
            scanf("%c",&Respuesta);

            flag2=0;

            system("cls");
        }
    }
    while((Respuesta=='s')&&(flag2==0));
}

int MenuDeCompra(int *CompraTaberna,int *CantidadPota)
{
    personaje pj=cargar_personaje();
    int flag=0,oro=pj.oro;

    printf("\nQue desea comprar?");

    do
    {
        printf("\n\n************************************\n");
        printf(" 1 - Pocion de Vida Menor.\t$15 \t\tMONEDERO: %d\n",oro);
        printf(" 2 - Pocion de Vida Media.\t$30\n");
        printf(" 3 - Pocion de Vida Mayor.\t$50\n");
        printf("************************************\n");
        printf(" 4 - Pocion de Mana Menor.\t$15\n");
        printf(" 5 - Pocion de Mana Media.\t$30\n");
        printf(" 6 - Pocion de Mana Mayor.\t$50\n");
        printf("************************************\n");
        printf(" 7 - Elixir Menor.\t\t$30\n");
        printf(" 8 - Elixir Media.\t\t$50\n");
        printf(" 9 - Elixir Mayor.\t\t$75\n");
        printf("************************************\n");
        printf(" 0 - Salir de la tienda\n");

        printf("\n... ");
        scanf("%d",&(*CompraTaberna));

        if(((*CompraTaberna)<0)||((*CompraTaberna)>9))
        {
            printf("\nOye... No puedo venderte algo que no existe.\n");
            sleep(3);

            system("cls");
        }

        if((*CompraTaberna)==0)
        {
            flag=1;
        }
    }
    while(((*CompraTaberna)<0)||((*CompraTaberna)>9));

    if(*CompraTaberna!=0)
    {
        printf("\nCantidad a comprar: ");
        scanf("%d",&(*CantidadPota));

        system("cls");
    }

    return flag;
}

int CargaDeCompra(int CompraTaberna,int CantidadPota)
{
    mochila MochilaAux[dim];
    iniciar_mochila(MochilaAux);
    traer_mochila(MochilaAux);
    personaje PJ=cargar_personaje();

    char VidaMenor[20];
    char VidaMedia[20];
    char VidaMayor[20];
    char ManaMenor[20];
    char ManaMedio[20];
    char ManaMayor[20];
    char ElixirMenor[20];
    char ElixirMedio[20];
    char ElixirMayor[20];
    int Calculo=0,flag=0;

    if(CompraTaberna==1)
    {
        strcpy(VidaMenor,"pocion pequenia");
        Calculo=CantidadPota * precioVidaMenor;

        if(Calculo<=PJ.oro)
        {
            aumentar_cantidad(CantidadPota,MochilaAux,VidaMenor);
            flag=1;
        }
        else
        {
            flag=0;
        }
    }
    else
    {
        if(CompraTaberna==2)
        {
            strcpy(VidaMedia,"pocion mediana");
            Calculo=CantidadPota*precioVidaMedia;

            if(Calculo<=PJ.oro)
            {
                aumentar_cantidad(CantidadPota,MochilaAux,VidaMedia);
                flag=1;
            }
            else
            {
                flag=0;
            }
        }
        else
        {
            if(CompraTaberna==3)
            {
                strcpy(VidaMayor,"pocion grande");
                Calculo=CantidadPota*precioVidaMayor;

                if(Calculo<=PJ.oro)
                {

                    aumentar_cantidad(CantidadPota,MochilaAux,VidaMayor);
                    flag=1;
                }
                else
                {
                    flag=0;
                }
            }
            else
            {
                if(CompraTaberna==4)
                {
                    strcpy(ManaMenor,"mana pequenio");
                    Calculo=CantidadPota*precioManaMenor;

                    if(Calculo<=PJ.oro)
                    {
                        aumentar_cantidad(CantidadPota,MochilaAux,ManaMenor);
                        flag=1;
                    }
                    else
                    {
                        flag=0;
                    }
                }
                else
                {
                    if(CompraTaberna==5)
                    {
                        strcpy(ManaMedio,"mana mediano");
                        Calculo=CantidadPota*precioManaMedia;

                        if(Calculo<=PJ.oro)
                        {
                            aumentar_cantidad(CantidadPota,MochilaAux,ManaMedio);
                            flag=1;
                        }
                        else
                        {
                            flag=0;
                        }
                    }
                    else
                    {
                        if(CompraTaberna==6)
                        {
                            strcpy(ManaMayor,"mana grande");
                            Calculo=CantidadPota*precioManaMayor;

                            if(Calculo<=PJ.oro)
                            {
                                aumentar_cantidad(CantidadPota,MochilaAux,ManaMayor);
                                flag=1;
                            }
                            else
                            {
                                flag=0;
                            }
                        }
                        else
                        {
                            if(CompraTaberna==7)
                            {
                                strcpy(ElixirMenor,"elixir pequenio");
                                Calculo=CantidadPota*precioElixirMenor;

                                if(Calculo<=PJ.oro)
                                {
                                    aumentar_cantidad(CantidadPota,MochilaAux,ElixirMenor);
                                    flag=1;
                                }
                                else
                                {
                                    flag=0;
                                }
                            }
                            else
                            {
                                if(CompraTaberna==8)
                                {
                                    strcpy(ElixirMedio,"elixir mediano");
                                    Calculo=CantidadPota*precioElixirMedia;

                                    if(Calculo<=PJ.oro)
                                    {
                                        aumentar_cantidad(CantidadPota,MochilaAux,ElixirMedio);
                                        flag=1;
                                    }
                                    else
                                    {
                                        flag=0;
                                    }
                                }
                                else
                                {
                                    strcpy(ElixirMayor,"elixir grande");
                                    Calculo=CantidadPota*precioElixirMayor;

                                    if(Calculo<=PJ.oro)
                                    {
                                        aumentar_cantidad(CantidadPota,MochilaAux,ElixirMayor);
                                        flag=1;
                                    }
                                    else
                                    {
                                        flag=0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if(Calculo<=PJ.oro)
    {
        PJ.oro-=Calculo;
    }

    guardar_mochila(MochilaAux);
    guardar_personaje(PJ);

    return flag;
}
