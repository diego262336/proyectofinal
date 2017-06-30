#ifndef PACMAN_H
#define PACMAN_H
#include "Juego.h"
class Juego;

class pacman
{
private:
    int y,x;
    int _y ,_x ;
    int y_ , x_ ;
    int espera;
    int puntaje;
    int puntajeAlto;
    int color;
    int vidas;
    int left;
    int super;
    int cont_muertes;

    char dir;
    char _dir;
    char icono;

    Juego *juego;

public:
    pacman(Juego * const g);
    void movimiento();
    void getDireccion();
    bool TestForCollision();

    void PrintKillScore();
    void muerte();
    void presentacion();
    void esconder();

    void mostrarPuntaje(int);
    void mostrarVidas();

    int GetY(){return y;}
    int GetX(){return x;}
    int GetY_() { return y_; }
    int GetX_() { return x_; }
    int GetLeft()  { return left;  }
    int GetVidas() { return vidas; }
    int GetSuper() { return super; }

    void SetY(int y)  { this->y = y; }
    void SetX(int x)  { this->x = x; }
    void SetY_(int y)  { y_ = y;  }
    void SetX_(int x)  { x_ = x;  }
    void SetEspera(int w)  { espera = w;  }
    void SetLeft(int l)  { left = l;  }
    void SetPuntaje(int s) { puntaje = s;  }
    void SetVidas(int l) { vidas = l;  }
    void SetSuper(int s) { super = s;  }
    void SetCont_muertes(int k) { cont_muertes = k; }
    void SetColor(int c) { color = c; }
    void Set_dir(char d)  { _dir = d;  }
    void SetIcono(char i)   { icono = i; }






};

#endif // PACMAN_H
