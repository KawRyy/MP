#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sesion.h"
#include "ficheros.h"

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
        Partida(usuario);
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

    fclose(partida);
}

