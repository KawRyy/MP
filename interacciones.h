#ifndef INTERACCIONES_H
#define INTERACCIONES_H

#include "ficheros.h"

void describir_sala(Partida *partida, Salas *salas);
void examinar(Partida *partida, Objetos *objetos, Conexiones *conexiones);
void entrar_sala(Partida *partida, Conexiones *conexiones, Salas *salas);
void coger_objeto(Partida *partida, Objetos *objetos);
void soltar_objeto(Partida *partida, Objetos *objetos);
void inventario(Partida *partida, Objetos *objetos);
void usar_objeto(Partida *partida, Objetos *objetos, Conexiones *conexiones);
void resolver_puzle(Partida *partida, Puzles *puzles, Conexiones *conexiones);

#endif /* INTERACCIONES_H */