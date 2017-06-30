#ifndef JUEGO_H
#define JUEGO_H
#include "constantes.h"
#include "pacman.h"
#include "bolita.h"
#include "fantasma.h"
class pacman;
class bolita;
class fantasma;
class Juego

{
private:
    char nivelMapa[ALTURA_NIVEL][ANCHO_NIVEL];
    int oneUpTimer = ONE_UP_MAX;
    int oneUpColor = BLANCO;
    int bolitaTiempo= BOLITA_MAX;
    int bolitaColor= BLANCO;
    int fantasmaModoTiempo= MODE_MAX;

    pacman* jugador;
    fantasma* fantasmas[4];
    bolita* bolitas[4];

    void mainloop();

public:
    Juego();
    ~Juego();

    void inicio();
    void CargarNivel();
    void siguienteNivel();
    void PrintReady();
    void PrintGameOver();

    void moverFantasma();
    void UpdateTimers();
    void comprobarMuerte();
    void ShowAll();
    void HideAll();
    void InitAll();

    char getNivel(int y, int x) {return nivelMapa[y][x];}
    int GetOneUpTimer()         { return oneUpTimer;     }
    int GetOneUpColor()         { return oneUpColor;     }
    int GetBolitaTiempo()        { return bolitaTiempo;    }
    int GetBolitaColor()        { return bolitaColor;    }
    int GetFantasmaModoTiempo()     { return fantasmaModoTiempo; }

    void SetNivel(int y, int x, char c) { nivelMapa[y][x] = c;    }
    void SetOneUpTimer(int t)           { oneUpTimer = t;     }
    void SetOneUpColor(int c)           { oneUpColor = c;     }
    void SetBolitaTiempo(int t)          { bolitaTiempo = t;    }
    void SetBolitaColor(int c)          { bolitaColor = c;    }
    void SetFantasmaModoTiempo(int t)       { fantasmaModoTiempo = t; }


};

#endif // JUEGO_H
