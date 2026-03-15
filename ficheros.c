#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ficheros.h"

//completar jugadores y partida

int leer_jugadores(Jugadores *jugadores){
    FILE *f;

    if((f=fopen("ficheros/jugadores.txt","r+"))==NULL){
        return 0;
    }

    fclose(f);
    return 1;
}

int leer_partida(Partida *partida){
    FILE *f;

    if((f=fopen("ficheros/partida.txt","r+"))==NULL){
        return 0;
    }

    fclose(f);
    return 1;
}

int leer_salas(Salas *salas){
    FILE *f;
    char line[256];
    int i = 0;

    if((f=fopen("ficheros/salas.txt","r"))==NULL){
        return 0;
    }

    while(fgets(line, sizeof(line), f)){
        if(line[0] == '/' && line[1] == '/')
            continue;

        char id_str[3] = {0};
        char name[21] = {0};
        char type[8] = {0};
        char desc[151] = {0};

        if(sscanf(line, "%2[^-]-%20[^-]-%7[^-]-%150s", id_str, name, type, desc) != 4)
            continue;

        salas[i].id_sala = atoi(id_str);

        strncpy(salas[i].nombre_sala, name, sizeof(salas[i].nombre_sala));
        salas[i].nombre_sala[sizeof(salas[i].nombre_sala)-1] = '\0';

        if(strcmp(type, "INICIAL") == 0)
            salas[i].tipo_sala = 1;
        else if(strcmp(type, "NORMAL") == 0)
            salas[i].tipo_sala = 2;
        else if(strcmp(type, "SALIDA") == 0)
            salas[i].tipo_sala = 3;
        else
            salas[i].tipo_sala = 0;

        strncpy(salas[i].descripcion_sala, desc, sizeof(salas[i].descripcion_sala));
        salas[i].descripcion_sala[sizeof(salas[i].descripcion_sala)-1] = '\0';

        i++;
    }

    fclose(f);
    return 1;
}

int leer_objetos(Objetos *objetos){
    FILE *f;
    char line[256];
    int i = 0;

    if((f=fopen("ficheros/objetos.txt","r"))==NULL){
        return 0;
    }

    while(fgets(line, sizeof(line), f)){
        if(line[0] == '/' && line[1] == '/')
            continue;

        char id[5] = {0};
        char name[16] = {0};
        char desc[51] = {0};
        int loc = 0;

        if(sscanf(line, "%4[^-]-%15[^-]-%50[^-]-%d", id, name, desc, &loc) != 4)
            continue;

        strncpy(objetos[i].id_objeto, id, sizeof(objetos[i].id_objeto));
        objetos[i].id_objeto[sizeof(objetos[i].id_objeto)-1] = '\0';

        strncpy(objetos[i].nombre_objeto, name, sizeof(objetos[i].nombre_objeto));
        objetos[i].nombre_objeto[sizeof(objetos[i].nombre_objeto)-1] = '\0';

        strncpy(objetos[i].descripcion_objeto, desc, sizeof(objetos[i].descripcion_objeto));
        objetos[i].descripcion_objeto[sizeof(objetos[i].descripcion_objeto)-1] = '\0';

        objetos[i].localizacion_objeto = loc;
        i++;
    }

    fclose(f);
    return 1;
}

int leer_conexiones(Conexiones *conexiones){
    FILE *f;
    char line[256];
    int i = 0;

    if((f=fopen("ficheros/conexiones.txt","r+"))==NULL){
        return 0;
    }

    while(fgets(line, sizeof(line), f)){
        if(line[0] == '/' && line[1] == '/')
            continue;

        char id[4] = {0};
        char orig_str[3] = {0};
        char dest_str[3] = {0};
        char state[10] = {0};
        char cond[10] = {0};

        if(sscanf(line, "%3[^-]-%2[^-]-%2[^-]-%9[^-]-%9s", id, orig_str, dest_str, state, cond) != 5)
            continue;

        strncpy(conexiones[i].id_conexion, id, sizeof(conexiones[i].id_conexion));
        conexiones[i].id_conexion[sizeof(conexiones[i].id_conexion)-1] = '\0';

        conexiones[i].id_sala_orig = atoi(orig_str);
        conexiones[i].id_sala_dest = atoi(dest_str);

        if(strcmp(state, "Activa") == 0)
            conexiones[i].estado_conexion = 1;
        else if(strcmp(state, "Bloqueada") == 0)
            conexiones[i].estado_conexion = 0;
        else
            conexiones[i].estado_conexion = 0;

        if(strcmp(cond, "0") == 0)
            conexiones[i].condicion_conexion = 0;
        else if(strncmp(cond, "OB", 2) == 0)
            conexiones[i].condicion_conexion = 1;
        else if(strncmp(cond, "PUZZLE", 6) == 0)
            conexiones[i].condicion_conexion = 2;
        else
            conexiones[i].condicion_conexion = 0;

        i++;
    }

    fclose(f);
    return 1;
}

int leer_puzzles(Puzles *puzzles){
    FILE *f;
    char line[256];
    int i = 0;

    if((f=fopen("ficheros/puzzles.txt","r"))==NULL){
        return 0;
    }

    while(fgets(line, sizeof(line), f)){
        if(line[0] == '/' && line[1] == '/')
            continue;

        char id[4] = {0};
        char name[16] = {0};
        char sala_str[8] = {0};
        char desc[151] = {0};
        char sol[51] = {0};

        if(sscanf(line, "%3[^-]-%15[^-]-%7[^-]-%150[^-]-%50s", id, name, sala_str, desc, sol) != 5)
            continue;

        strncpy(puzzles[i].id_puzle, id, sizeof(puzzles[i].id_puzle));
        puzzles[i].id_puzle[sizeof(puzzles[i].id_puzle)-1] = '\0';

        puzzles[i].id_sala_puzle = atoi(sala_str);

        puzzles[i].tipo_elemento = 1; //MODIFICAR SI ES CODIGO O PALABRA

        strncpy(puzzles[i].descripcion_puzle, desc, sizeof(puzzles[i].descripcion_puzle));
        puzzles[i].descripcion_puzle[sizeof(puzzles[i].descripcion_puzle)-1] = '\0';

        strncpy(puzzles[i].solucion_puzle, sol, sizeof(puzzles[i].solucion_puzle));
        puzzles[i].solucion_puzle[sizeof(puzzles[i].solucion_puzle)-1] = '\0';

        i++;
    }

    fclose(f);
    return 1;
}

int guardar_jugadores(Jugadores *jugadores){
    
    return 1;
}

int guardar_partida(Partida *partida){
    
    return 1;
}

int guardar_conexiones(Conexiones *conexiones, int num_conexiones){
    FILE *f;
    char comments[100][256];
    int num_comments = 0;
    char line[256];
    int cond = 0;

    if((f = fopen("ficheros/conexiones.txt", "r")) == NULL){
        return 0;
    }

    while(fgets(line, sizeof(line), f) && cond == 0){
        if(line[0] == '/' && line[1] == '/'){
            strcpy(comments[num_comments], line);
            num_comments++;
        } else cond = 1;
    }

    if(freopen("ficheros/conexiones.txt", "w", f) == NULL){
        fclose(f);
        return 0;
    }

    for(int i = 0; i < num_conexiones; i++){
        if(conexiones[i].estado_conexion == 0 && conexiones[i].condicion_conexion == 0){
            conexiones[i].estado_conexion = 1;
        }
    }

    for(int i = 0; i < num_comments; i++){
        fputs(comments[i], f);
    }

    for(int i = 0; i < num_conexiones; i++){
        char state[10];
        if(conexiones[i].estado_conexion == 1){
            strcpy(state, "Activa");
        } else {
            strcpy(state, "Bloqueada");
        }

        char cond[10];
        if(conexiones[i].condicion_conexion == 0){
            strcpy(cond, "0");
        } else if(conexiones[i].condicion_conexion == 1){
            strcpy(cond, "OB");
        } else if(conexiones[i].condicion_conexion == 2){
            strcpy(cond, "PUZZLE");
        } else {
            strcpy(cond, "0");
        }

        fprintf(f, "%s-%d-%d-%s-%s\n", conexiones[i].id_conexion, conexiones[i].id_sala_orig, conexiones[i].id_sala_dest, state, cond);
    }
    fclose(f);
    return 1;
}