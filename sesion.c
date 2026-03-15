#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sesion.h"
#include "ficheros.h"
#include "interacciones.h"

void Menu(){
    int acciones = 0;
    printf("BIENVENIDO A ESI ESCAPE\n");
    printf("MENÚ:\n 1. Nueva Partida\n 2.Cargar Partida\n 3. Salir\n");
    scanf("%d", &acciones);
    switch(acciones){
        case 1:
            //RegistrarUsuario();
            break;
        case 2:
            IniciarSesion();
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("Opción no válida. Por favor, elige una opción válida.\n");
    }
}

void IniciarSesion(){
    int arranque = 0;
    printf("Introduce tu usuario: ");
    char usuario[50];
    fgets(usuario, sizeof(usuario), stdin);
    usuario[strcspn(usuario, "\n")] = 0;

    printf("Introduce tu contraseña: ");
    char contrasena[50];

    fgets(contrasena, sizeof(contrasena), stdin);
    contrasena[strcspn(contrasena, "\n")] = 0;

    ComprobarSesion(usuario, contrasena, &arranque);
    if(arranque == 1){
        printf("¡Bienvenido, %s!\n", usuario);
        menu_partida(usuario);
    }
}

void ComprobarSesion(char *usuario, char *contrasena, int *arranque){

    FILE *jugadores = fopen("ficheros/jugadores.txt", "r");
    char linea[100];
    int encontrado = 0;

    while (fgets(linea, sizeof(linea), jugadores)) {
        char *token = strtok(linea, "-");
        if (strcmp(token, usuario) == 0) {
            token = strtok(NULL, "-");
            if (strcmp(token, contrasena) == 0) {
                printf("¡Inicio de sesión exitoso!\n");
                encontrado = 1;
                *arranque = 1;
                break;
            }
        }
    }

    if (!encontrado) {
        printf("Usuario o contraseña incorrectos.\n");
    }

    fclose(jugadores);
}

void menu_partida(char *usuario) {
    Partida partida;
    Salas salas[100]; // Asumir máximo 100 salas
    Objetos objetos[100];
    Conexiones conexiones[100];
    Puzles puzles[100];

    // Cargar datos
    if (!leer_partida(&partida)) {
        printf("Error al cargar partida.\n");
        return;
    }
    leer_salas(salas);
    leer_objetos(objetos);
    leer_conexiones(conexiones);
    leer_puzzles(puzles);

    int opcion;
    do {
        // Mostrar nombre de la sala actual
        printf("Sala: %s\n", salas[partida.id_sala_actual - 1].nombre_sala); // Asumir IDs empiezan en 1

        // Menú
        printf("1. Describir sala\n");
        printf("2. Examinar (objetos y salidas)\n");
        printf("3. Entrar en otra sala\n");
        printf("4. Coger objeto\n");
        printf("5. Soltar objeto\n");
        printf("6. Inventario\n");
        printf("7. Usar objeto\n");
        printf("8. Resolver puzle / introducir código\n");
        printf("9. Guardar partida\n");
        printf("10. Volver\n");
        printf("Elige una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                describir_sala(&partida, salas);
                break;
            case 2:
                examinar(&partida, objetos, conexiones);
                break;
            case 3:
                entrar_sala(&partida, conexiones, salas);
                break;
            case 4:
                coger_objeto(&partida, objetos);
                break;
            case 5:
                soltar_objeto(&partida, objetos);
                break;
            case 6:
                inventario(&partida, objetos);
                break;
            case 7:
                usar_objeto(&partida, objetos, conexiones);
                break;
            case 8:
                resolver_puzle(&partida, puzles, conexiones);
                break;
            case 9:
                guardar_partida(&partida);
                printf("Partida guardada.\n");
                break;
            case 10:
                printf("Volviendo al menú principal.\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while (opcion != 10);
}

