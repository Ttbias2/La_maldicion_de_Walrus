#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Enemigos.h"

stEnemigo CargarStuctEnemigos()
{
    stEnemigo Enemigo;

    printf("\nNombre Enemigo: ");
    fflush(stdin);
    gets(Enemigo.Nombre);

    printf("\nVida: ");
    scanf("%i",&Enemigo.vida);

    printf("\nDanio: ");
    scanf("%i",&Enemigo.danio);

    printf("\nDrop: ");
    fflush(stdin);
    gets(Enemigo.drop);

    printf("\nMoneda: ");
    scanf("%i",&Enemigo.Moneda);

    printf("\nXP: ");
    scanf("%i",&Enemigo.xp);

    printf("\nMundo(1,2,3): ");
    scanf("%i",&Enemigo.Mundo);

    return Enemigo;
}

void mostrar_enemigo(stEnemigo enemigo)
{
    puts(enemigo.Nombre);
    printf("vida: %i",enemigo.vida);
    printf("\n-------------------------\n");
}

void CargarArchivoEnemigos()//se hace separado al del jefe para hacer mas sencilla la carga y busqueda
{
    char Respuesta='s';

    do
    {
        printf("\n\n*********//CARGA DE ENEMIGO//**********\n\n");

        stEnemigo Enemigo = CargarStuctEnemigos();

        if(Enemigo.Mundo==1)
        {
            FILE * Arch = fopen(ArchEnemigos_M1,"ab");

            if(Arch!=NULL)
            {
                fwrite(&Enemigo,sizeof(stEnemigo),1,Arch);

                fclose(Arch);
            }
            else
            {
                printf("\n\nERROR EN EL ARCHIVO.\n\n");
            }
        }
        else
        {
            if(Enemigo.Mundo==2)
            {
                FILE * Arch = fopen(ArchEnemigos_M2,"ab");

                if(Arch!=NULL)
                {
                    fwrite(&Enemigo,sizeof(stEnemigo),1,Arch);

                    fclose(Arch);
                }
                else
                {
                    printf("\n\nERROR EN EL ARCHIVO.\n\n");
                }
            }
            else
            {
                if(Enemigo.Mundo==3)
                {
                    FILE * Arch = fopen(ArchEnemigos_M3,"ab");

                    if(Arch!=NULL)
                    {
                        fwrite(&Enemigo,sizeof(stEnemigo),1,Arch);

                        fclose(Arch);
                    }
                    else
                    {
                        printf("\n\nERROR EN EL ARCHIVO.\n\n");
                    }
                }
            }
        }

        printf("\nDesea agregar otro enemigo? (s/n): ");
        fflush(stdin);
        scanf("%c",&Respuesta);
    }
    while(Respuesta=='s');

}

void CargarArchivoJEFES()
{
    char Respuesta='s';

    do
    {
        printf("\n\n*********//CARGA DE JEFE//**********\n\n");

        stEnemigo Jefe = CargarStuctEnemigos();

        if(Jefe.Mundo==1)
        {
            FILE * Arch = fopen(ArchJEFE_M1,"ab");

            if(Arch!=NULL)
            {
                fwrite(&Jefe,sizeof(stEnemigo),1,Arch);

                fclose(Arch);

            }
            else
            {
                printf("\n\nERROR EN EL ARCHIVO.\n\n");
            }
        }
        else
        {
            if(Jefe.Mundo==2)
            {
                FILE * Arch = fopen(ArchJEFE_M2,"ab");

                if(Arch!=NULL)
                {
                    fwrite(&Jefe,sizeof(stEnemigo),1,Arch);

                    fclose(Arch);

                }
                else
                {
                    printf("\n\nERROR EN EL ARCHIVO.\n\n");
                }
            }
            else
            {
                if(Jefe.Mundo==3)
                {
                    FILE * Arch = fopen(ArchJEFE_M3,"ab");

                    if(Arch!=NULL)
                    {
                        fwrite(&Jefe,sizeof(stEnemigo),1,Arch);

                        fclose(Arch);

                    }
                    else
                    {
                        printf("\n\nERROR EN EL ARCHIVO.\n\n");
                    }
                }
            }
        }
        printf("\nDesea agregar otro JEFE? (s/n): ");
        fflush(stdin);
        scanf("%c",&Respuesta);
    }
    while(Respuesta=='s');
}

stEnemigo BuscarEnemigos(int Mundo)
{
    int num=0;
    stEnemigo Aux; // dependiendo del mundo se eligira uno de los tres enemigos y lo retornara
    num = rand()%3;

    if(Mundo==1)
    {
        FILE * Arch = fopen(ArchEnemigos_M1,"rb");

        if(Arch!=NULL)
        {
            fseek(Arch,sizeof(stEnemigo)*num,SEEK_SET);

            fread(&Aux,sizeof(stEnemigo),1,Arch);

            fclose(Arch);
        }
        else
        {
            printf("\n\nERROR EN EL ARCHIVO.\n\n");
        }
    }
    else
    {
        if(Mundo==2)
        {
            FILE * Archi = fopen(ArchEnemigos_M2,"rb");

            if(Archi!=NULL)
            {
                fseek(Archi,sizeof(stEnemigo)*num,SEEK_SET);

                fread(&Aux,sizeof(stEnemigo),1,Archi);

                fclose(Archi);
            }
            else
            {
                printf("\n\nERROR EN EL ARCHIVO.\n\n");
            }
        }
        else
        {
            if(Mundo==3)
            {
                FILE * Archib = fopen(ArchEnemigos_M3,"rb");

                if(Archib!=NULL)
                {
                    fseek(Archib,sizeof(stEnemigo)*num,SEEK_SET);

                    fread(&Aux,sizeof(stEnemigo),1,Archib);

                    fclose(Archib);
                }
                else
                {
                    printf("\n\nERROR EN EL ARCHIVO.\n\n");
                }
            }
        }
    }
    return Aux;
}

stEnemigo BuscarJefe(int mundo)
{
    stEnemigo aux;

    if(mundo==1)
    {
        FILE * arch=fopen(ArchJEFE_M1,"rb");

        fread(&aux,sizeof(stEnemigo),1,arch);

        fclose(arch);
    }
    else if(mundo==2)
    {
        FILE * arch=fopen(ArchJEFE_M2,"rb");

        fread(&aux,sizeof(stEnemigo),1,arch);

        fclose(arch);
    }
    else
    {
        FILE * arch=fopen(ArchJEFE_M3,"rb");

        fread(&aux,sizeof(stEnemigo),1,arch);

        fclose(arch);
    }

    return aux;
}

void vaciar_archivos_enemigos()
{
    FILE * arch=fopen(ArchEnemigos_M1,"wb");
    fclose(arch);

    FILE * archi=fopen(ArchEnemigos_M2,"wb");
    fclose(archi);

    FILE * archiv=fopen(ArchEnemigos_M3,"wb");
    fclose(archiv);
}

void vaciar_archivos_jefes()
{
    FILE * arch=fopen(ArchJEFE_M1,"wb");
    fclose(arch);

    FILE * archi=fopen(ArchJEFE_M2,"wb");
    fclose(archi);

    FILE * archiv=fopen(ArchJEFE_M3,"wb");
    fclose(archiv);
}














