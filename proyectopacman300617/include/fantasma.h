#ifndef FANTASMA_H
#define FANTASMA_H

class Juego;
class fantasma
{
private:
    int y,x;
    int y_ ,x_ ;
    int espera;
    int color;
    int color_;
    char dir;
    char _dir;
    char dir_;
    char modo;
    char _modo;
    char icono;

    Juego *juego;

public:
    fantasma(Juego * const g);
    void movimiento(int, int);
    void objetoObjetivo(bool[4] );
    void randomDireccion();
    bool TestForCollision();
    void cambioCoords();
    void getOpuesto();
    void muerte();
    void presentacion();
    void esconder();

    int GetY(){return y;}
    int GetX(){return x;}
    int GetY_() { return y_; }
    int GetX_() { return x_; }
    int GetColor()  { return color;  }
    int GetColor_() { return color_; }
    int GetModo() { return modo; }

    void SetY(int y)  { this->y = y; }
    void SetX(int x)  { this->x = x; }
    void SetY_(int y)  { y_ = y;  }
    void SetX_(int x)  { x_ = x;  }
    void SetEspera(int w)  { espera = w;  }
    void SetColor(int c)  { color = c;  }
    void SetColor_(int c) { color_ = c;  }
    void SetDir_(char d) {dir_ =d;}
    void SetModo(char m) {modo=m;}
    void Set_Modo(char m) {_modo=m;}
    void SetIcono(char i)   { icono = i; }

};

#endif // FANTASMA_H
