#ifndef BOLITA_H
#define BOLITA_H

class Juego;
class bolita
{
private:
    int y,x;
    Juego *juego;

public:
    bolita(Juego *const g);
    void print();
    void setY(int y){this ->y =y;}
    void setX(int x){this ->x =x;}
};

#endif // BOLITA_H
