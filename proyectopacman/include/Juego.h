#ifndef JUEGO_H
#define JUEGO_H
#include "constantes.h"
#include "pacman.h"
#include "bolita.h"

class pacman;
class bolita;

class Juego

{
private:
    char nivelMapa[ALTURA_NIVEL][ANCHO_NIVEL];
    int oneUpTimer = ONE_UP_MAX;
    int oneUpColor = BLANCO;

    pacman* jugador;

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

    char getNivel(int y, int x)
    {
        return nivelMapa[y][x];
    }



    void UpdateTimers();
    void ShowAll();
    void HideAll();
    void InitAll();

    void SetNivel(int y, int x, char c) { nivelMapa[y][x] = c;    }



};

#endif // JUEGO_H
