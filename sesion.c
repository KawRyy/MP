#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sesion.h"
#include "ficheros.h"

void IniciarSesion(){
    
    printf("Introduce tu usuario: ");
    char usuario[50];
    fgets(usuario, sizeof(usuario), stdin);
    usuario[strcspn(usuario, "\n")] = 0;

    printf("Introduce tu contraseña: ");
    char contrasena[50];

    fgets(contrasena, sizeof(contrasena), stdin);
    contrasena[strcspn(contrasena, "\n")] = 0;

    ComprobarSesion(usuario, contrasena);
}

void ComprobarSesion(char *usuario, char *contrasena){

    FILE *partida = fopen("jugadores.txt", "r");
    char linea[100];
    int encontrado = 0;

    while (fgets(linea, sizeof(linea), partida)) {
        char *token = strtok(linea, ",");
        if (strcmp(token, usuario) == 0) {
            token = strtok(NULL, ",");
            if (strcmp(token, contrasena) == 0) {
                printf("¡Inicio de sesión exitoso!\n");
                encontrado = 1;
                break;
            }
        }
    }

    if (!encontrado) {
        printf("Usuario o contraseña incorrectos.\n");
    }

    fclose(partida);
}