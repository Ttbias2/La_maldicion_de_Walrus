#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "personaje.h"
#include "habilidades.h"
#include "inventario.h"
#include "enemigos.h"
#include "batallas.h"
#include "pueblo.h";

int main()
{
    srand(time(NULL));

    printf("\n\t _    __    __ __  __  _   __  _  ____  __  __  _   __  ___   _   _   __  _   ___ _  _   __  \n");
    printf("\t| |  /  \\  |  V  |/  \\| | | _\\| |/ _/ |/__\\|  \\| | | _\\| __| | | | | /  \\| | | _ \\ || |/' _/\n");
    printf("\t| |_| /\\ | | \\_/ | /\\ | |_| v | | \\_| | \\/ | | ' | | v | _|  | 'V' || /\\ | |_| v / \\/ |`._`.\n");
    printf("\t|___|_||_| |_| |_|_||_|___|__/|_|\\__/_|\\__/|_|\\__| |__/|___| !_/ \\_!|_||_|___|_|_\\\\__/ |___/\n\n");

    int opcion=0;

    printf("\n\n\t\t\t\t\t1: Comenzar una nueva partida"); // menu de inicio
    printf("\n\t\t\t\t\t2: Continuar\n");
    printf("\t\t\t\t\t3: Salir\n");

    do
    {
        scanf("%i",&opcion); // bloquea que se elija opciones inexistentes

    }
    while(opcion<1 || opcion>3);


    system("cls");

    switch(opcion)
    {
    case 1://si se elige el caso se reseteara todo los desbloqueado a 0
    {
        printf("\n\nADVERTENCIA - Este juego posee Autoguardado.\n\n");
        sleep(3);
        system("cls");

        CrearNuevoPersonaje();//retorna el personaje a 0
        devolver_herrero_0();//retorna el herrero a 0

        mochila invent[dim];
        iniciar_mochila(invent);
        traer_mochila(invent);          //para la mochila se carga en una auxiliar se devuelven todas las cantidades a 0 y se guarda de nuevo
        devolver_cantidades_0(invent);  //la funcion de guardado limpia el archivo
        guardar_mochila(invent);

        arbol_habilidades * arbol=inic_arbol();
        arbol=traer_habilidades_de_archivo(arbol);//para el arbol de habilidad funciona de una forma parecida a la mochila pero en este caso
        limpiar_archivo_arbol();                  //la primera habilidad no tiene que ser retornada a 0 y la limpieza del arbol no se hace
        devolver_habilidades_0(arbol->izquierda); //dentro de la funcion guardar
        devolver_habilidades_0(arbol->derecha);
        guardar_habilidades(arbol);

        Pueblo();//se accede al puebl con todo creado de 0
        break;
    }
    case 2:
    {
        Pueblo();//se accede al pueblo sin modificar los archivos
        break;
    }
    case 3:
    {
        break;//no hace nada
    }
    }

    return 0;
}
