#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interacciones.h"
#include "ficheros.h"

void describir_sala(Partida *partida, Salas *salas) {
    int id = partida->id_sala_actual;
    printf("Descripción: %s\n", salas[id - 1].descripcion_sala);
    if (salas[id - 1].tipo_sala == 3) {
        printf("¡Has llegado a la SALIDA! ¡Victoria!\n");
        printf("Volviendo al menú principal.\n");
        // Aquí podríamos resetear o algo, pero por ahora solo mensaje
    }
}

void examinar(Partida *partida, Objetos *objetos, Conexiones *conexiones) {
    printf("Objetos en la sala:\n");
    for (int i = 0; i < partida->num_objetos; i++) {
        if (objetos[i].localizacion_objeto == 0) { // En sala
            printf("- %s: %s\n", objetos[i].nombre_objeto, objetos[i].descripcion_objeto);
        }
    }
    printf("Salidas:\n");
    for (int i = 0; i < partida->num_conexiones; i++) {
        if (conexiones[i].id_sala_orig == partida->id_sala_actual) {
            printf("- Hacia sala %d: %s\n", conexiones[i].id_sala_dest, conexiones[i].estado_conexion ? "Abierta" : "Bloqueada");
        }
    }
}

void entrar_sala(Partida *partida, Conexiones *conexiones, Salas *salas) {
    printf("Elige una sala para entrar: ");
    int dest;
    scanf("%d", &dest);
    for (int i = 0; i < partida->num_conexiones; i++) {
        if (conexiones[i].id_sala_orig == partida->id_sala_actual && conexiones[i].id_sala_dest == dest) {
            if (conexiones[i].estado_conexion) {
                partida->id_sala_actual = dest;
                printf("Entrando en %s\n", salas[dest - 1].nombre_sala);
            } else {
                printf("La conexión está bloqueada. Condición: ");
                if (conexiones[i].condicion_conexion == 1) printf("Requiere objeto\n");
                else if (conexiones[i].condicion_conexion == 2) printf("Requiere resolver puzle\n");
            }
            return;
        }
    }
    printf("No hay conexión a esa sala.\n");
}

void coger_objeto(Partida *partida, Objetos *objetos) {
    printf("Elige un objeto para coger: ");
    char nombre[16];
    scanf("%s", nombre);
    for (int i = 0; i < partida->num_objetos; i++) {
        if (strcmp(objetos[i].nombre_objeto, nombre) == 0 && objetos[i].localizacion_objeto == 0) {
            objetos[i].localizacion_objeto = 1; // Al inventario
            printf("Objeto cogido.\n");
            return;
        }
    }
    printf("Objeto no encontrado en la sala.\n");
}

void soltar_objeto(Partida *partida, Objetos *objetos) {
    printf("Elige un objeto para soltar: ");
    char nombre[16];
    scanf("%s", nombre);
    for (int i = 0; i < partida->num_objetos; i++) {
        if (strcmp(objetos[i].nombre_objeto, nombre) == 0 && objetos[i].localizacion_objeto == 1) {
            objetos[i].localizacion_objeto = 0; // A la sala
            printf("Objeto soltado.\n");
            return;
        }
    }
    printf("Objeto no encontrado en el inventario.\n");
}

void inventario(Partida *partida, Objetos *objetos) {
    printf("Inventario:\n");
    for (int i = 0; i < partida->num_objetos; i++) {
        if (objetos[i].localizacion_objeto == 1) {
            printf("- %s: %s\n", objetos[i].nombre_objeto, objetos[i].descripcion_objeto);
        }
    }
}

void usar_objeto(Partida *partida, Objetos *objetos, Conexiones *conexiones) {
    printf("Elige un objeto para usar: ");
    char nombre[16];
    scanf("%s", nombre);
    for (int i = 0; i < partida->num_objetos; i++) {
        if (strcmp(objetos[i].nombre_objeto, nombre) == 0 && objetos[i].localizacion_objeto == 1) {
            // Asumir que usar objeto desbloquea conexiones, pero simplificar
            for (int j = 0; j < partida->num_conexiones; j++) {
                if (conexiones[j].condicion_conexion == 1) { // Requiere objeto
                    conexiones[j].estado_conexion = 1;
                    printf("Conexión desbloqueada.\n");
                    return;
                }
            }
            printf("No se puede usar aquí.\n");
            return;
        }
    }
    printf("Objeto no encontrado en el inventario.\n");
}

void resolver_puzle(Partida *partida, Puzles *puzles, Conexiones *conexiones) {
    for (int i = 0; i < partida->num_puzles; i++) {
        if (puzles[i].id_sala_puzle == partida->id_sala_actual) {
            printf("Puzle: %s\n", puzles[i].descripcion_puzle);
            printf("Solución: ");
            char sol[51];
            scanf("%s", sol);
            if (strcmp(puzles[i].solucion_puzle, sol) == 0) {
                // Desbloquear conexión
                for (int j = 0; j < partida->num_conexiones; j++) {
                    if (conexiones[j].condicion_conexion == 2) {
                        conexiones[j].estado_conexion = 1;
                        printf("Puzle resuelto. Conexión desbloqueada.\n");
                        return;
                    }
                }
            } else {
                printf("Solución incorrecta.\n");
            }
            return;
        }
    }
    printf("No hay puzle en esta sala.\n");
}