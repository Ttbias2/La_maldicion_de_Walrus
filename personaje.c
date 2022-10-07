#include <stdio.h>
#include <stdlib.h>
#include "personaje.h"
#include <string.h>

personaje IniciarPJ()
{
    personaje pj;

    printf("ingrese el nombre de su pj: ");
    fflush(stdin);
    gets(pj.nombre);

    pj.vida_max=100;
    pj.vida=100;
    pj.mana_max=50;
    pj.mana=50;
    pj.danio=10;                    //valores base del personaje
    pj.danio_magico=0;
    pj.defensa=0;
    pj.agilidad=0;
    pj.oro=0;
    pj.xp_actual=0;
    pj.xp_sig_lvl=100;
    pj.lvl=0;
    pj.puntos_de_habilidad=0;

    system("cls");

    return pj;
}

void guardar_personaje(personaje pj)
{
    FILE * arch=fopen(ArchPJ,"wb");

    if(arch != NULL)
    {
        fwrite(&pj,sizeof(personaje),1,arch);   //se remplaza al persnaje actual con informacion del nuevo

        fclose(arch);
    }
    else
    {
        printf("ERROR");
    }
}

void CrearNuevoPersonaje()
{
    personaje pj=IniciarPJ();   //se le da las estadisticas base y se sobreescribe el anterior pesonaje
    guardar_personaje(pj);

}

personaje cargar_personaje()
{
    personaje pj;

    FILE * arch=fopen(ArchPJ,"rb");

    if(arch != NULL)               //busca el personaje del archivo y lo retorna
    {
        fread(&pj,sizeof(personaje),1,arch);
    }

    fclose(arch);

    return pj;
}

void subir_vida_mana(personaje * pj)
{
    pj->vida_max+=20;   //esto pasara siempre al subir d nivel
    pj->mana_max+=10;

}

void subir_un_atributo(personaje * pj)
{

    int opcion=0,punto_de_subida=1,todo_al_maximo=0;

    if(pj->danio < 100)
    {
        printf("1:danio %i -> %i\n",pj->danio,pj->danio+subida_danio);//se comprueba que habilidades estan al maximo y cuales no
    }
    else
    {
        printf("1: danio max\n");
        todo_al_maximo++;
    }

    if(pj->danio_magico < 5)
    {
        printf("2: danio magico %i -> %i\n",pj->danio_magico,pj->danio_magico+subida_danio_magico);
    }
    else
    {
        printf("2: danio magico max\n");
        todo_al_maximo++;
    }

    if(pj->agilidad<25)
    {
        printf("3: agilidad: %i -> %i\n",pj->agilidad,pj->agilidad+subida_agilidad);
    }
    else
    {
        printf("3: agilidad max\n");
        todo_al_maximo++;
    }

    if(todo_al_maximo==3) //si todas las habilidades estan al maximo no hay nesesidad de subir de nivel
    {
        system("cls");
        printf("todos los atributos al maximo\n\n");
        system("pause");
    }

    while(punto_de_subida == 1 && todo_al_maximo != 3)
    {

     do
     {
      printf("\nque atrivuto desea subir: ");
      scanf("%i",&opcion);
      if(opcion < 1 || opcion > 3)
      {
          printf("opcion no valida\n");
      }
     }while(opcion < 1 || opcion > 3);

     if(opcion == 1 && pj->danio < 100)
     {
         pj->danio+=subida_danio;
         punto_de_subida=0;
     }
     else if(pj->danio > 100)          //se comprueba que la opcion de subida seleccionada no este subida al maximo
     {                                 //en caso de ser asi no se mejora
         printf("danio al maximo");
     }

     if(opcion == 2 && pj->danio_magico<5)
     {
         pj->danio_magico+=subida_danio_magico;
         punto_de_subida=0;
     }
     else if(pj->danio_magico>5)
     {
         printf("danio magico al maximo");
     }

     if(opcion == 3 && pj->agilidad<25)
     {
         pj->agilidad+=subida_agilidad;
         punto_de_subida=0;
     }
     else if(pj->agilidad>25)
     {
         printf("agilidad al maximo");
     }

    }

}

personaje subir_de_nivel(personaje pj)
{
    if(pj.lvl<20)
    {
    subir_vida_mana(&pj);
    subir_un_atributo(&pj); //invoca a las funciones nesesarias de la subida de nivel
    pj.lvl+=1;
    pj.puntos_de_habilidad+=1;//cambia los valores restantes
    pj.xp_actual=0;
    pj.xp_sig_lvl*=1.25;
    pj.vida=pj.vida_max;//devuelve la salud y el mana al maximo
    pj.mana=pj.mana_max;
    guardar_personaje(pj);//lo guarda con la subida de niveles echa
    }
    else
    {
        printf("\n\nlvl maximo\n\n");
        system("pause");
    }

    return pj;
}

void mostrar_personaje(personaje pj)
{
    printf("\n\n");
    puts(pj.nombre);
    printf("LvL: %i\n",pj.lvl);   //datos
    printf("Oro: %i\n\n",pj.oro);

    printf("  0 \n");
    printf(" /|\\\n"); //"sprite del personaje"
    printf(" / \\\n\n");

    printf("Salud: %i / %i\n",pj.vida,pj.vida_max);
    printf("Mana:  %i / %i\n",pj.mana,pj.mana_max);
    printf("Danio: %i\n",pj.danio);
    printf("Danio magico: %i\n",pj.danio_magico);    //estadisticas del personaje
    printf("Defensa: %i\n",pj.defensa);
    printf("Agilidad: %i\n",pj.agilidad);
    printf("Exp: %i / %i\n",pj.xp_actual,pj.xp_sig_lvl);

}









