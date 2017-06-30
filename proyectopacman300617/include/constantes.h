#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <windows.h>

const int ALTURA_NIVEL= 31;
const int ANCHO_NIVEL=28;
const char NO_COLLISION_TILES[3] = {' ','o','\xfa'};
const int GATE_X = 13;
const int GATE_Y = 12;




// directiones e iconos
const char ALL_DIRS[4]     = {'w','a','s','d'};
const char ICONOS[4]        = {'v','>','^','<'};
const char ICONO_FANTASMA      = 'M';
const char MUERTE_ICONO_FANTASMA = '"';

// colores
const int BLANCO     = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int ROJO       = FOREGROUND_RED   | FOREGROUND_INTENSITY;
const int AZUL       = FOREGROUND_BLUE  | FOREGROUND_INTENSITY;
const int AZULOSCURO = FOREGROUND_BLUE;
const int CELESTE    = FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY;
const int ROSA       = FOREGROUND_RED   | FOREGROUND_BLUE  | FOREGROUND_INTENSITY;
const int AMARILLO   = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int NEGRO      = 0;

// tiempos
const int SUPER_MAX   = 500;
const int ONE_UP_MAX  = 13;
const int BOLITA_MAX  = 8;
const int PACMAN_MAX  = 8;
const int FANTASMA_MAX   = 10;
const int RUN_MAX     = 16;
const int DEAD_MAX    = 3;
const int MODE_MAX    = 1000;

// fantasmas nombres
const int BLINK = 0;
const int PINK  = 1;
const int INK   = 2;
const int CLY  = 3;
#endif // CONSTANTES_H
