/* A cada fichero se le asigna un identificador, que va a ayudar a lanzar una función u otra. Los identificadores son los siguientes:
 1: jugadores.txt
 2: partida.txt
 3: salas.txt
 4: objetos.txt
 5: conexiones.txt
 6: puzzles.txt
 */
//cosas a realizar: Completar las funciones. Incluir la estructura respectiva como argumento en cada funcion.
#include <stdio.h>
#include <stdlib.h>


int ProcesarArchivo(int id){
    switch(id){
        case 1: jugadores();
                break;
        case 2: partida();
                break;
        case 3: salas();
                break;
        case 4: objetos();
                break;
        case 5: conexiones();
                break;
        case 6: puzzles();
                break;
    }
}

int jugadores(){
    FILE *f;
    char c;
    if((f=fopen("jugadores.txt","r+"))==NULL){
        printf("Error al abrir el archivo jugadores.txt");
        exit(1);
    }
    for(int i=0;i<6;i++){
        c=fgetc(f);
        if(c=='/'){
            while((c=fgetc(f))!='\n');
        }
    }
}

int partida(){
    FILE *f;
    char c;
    if((f=fopen("partida.txt","r+"))==NULL){
        printf("Error al abrir el archivo partida.txt");
        exit(1);
    }
    for(int i=0;i<13;i++){
        c=fgetc(f);
        if(c=='/'){
            while((c=fgetc(f))!='\n');
        }
    }

}

int salas(){
    FILE *f;
    char c;
    if((f=fopen("salas.txt","r"))==NULL){
        printf("Error al abrir el archivo salas.txt");
        exit(1);
    }
    for(int i=0;i<5;i++){
        c=fgetc(f);
        if(c=='/'){
            while((c=fgetc(f))!='\n');
        }
    }

}

int objetos(){
    FILE *f;
    char c;
    if((f=fopen("objetos.txt","r"))==NULL){
        printf("Error al abrir el archivo objetos.txt");
        exit(1);
    }
    for(int i=0;i<5;i++){
        c=fgetc(f);
        if(c=='/'){
            while((c=fgetc(f))!='\n');
        }
    }

}

int conexiones(){
    FILE *f;
    char c;
    if((f=fopen("conexiones.txt","r+"))==NULL){
        printf("Error al abrir el archivo conexiones.txt");
        exit(1);
    }
    for(int i=0;i<6;i++){
        c=fgetc(f);
        if(c=='/'){
            while((c=fgetc(f))!='\n');
        }
    }

}

int puzzles(){
    FILE *f;
    char c;
    if((f=fopen("puzzles.txt","r"))==NULL){
        printf("Error al abrir el archivo puzzles.txt");
        exit(1);
    }
    for(int i=0;i<6;i++){
        c=fgetc(f);
        if(c=='/'){
            while((c=fgetc(f))!='\n');
        }
    }
}