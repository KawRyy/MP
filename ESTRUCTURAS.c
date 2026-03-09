// NO MODULO !!!!!!!

/* ESTRUCTURAS DE DATOS PARA VOLCAR LOS FICHEROS */

typedef struct {
    int id_jugador; // 2 digitos EJ: 99
    char nomb_jugador[20];
    char jugador[10];
    char contraseña[100];
    
    //INVENTARIO DINÁMICO
    char** id_objeto;
    int num_items;
}Jugadores;

typedef struct {
int id_sala; // 2 digitos EJ: 99
char nomb_sala[20];
char descripcion_sala[150];
int tipo_sala; // 1:INICIAL ; 2: NORMAL ; 3: SALIDA
}Salas;
