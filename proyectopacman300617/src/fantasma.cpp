#include "fantasma.h"
#include <iostream>
#include "constantes.h"
#include "Juego.h"
#include "atributosConsola.h"
using namespace std;


fantasma::fantasma(Juego *const g)
: juego(g){}

// mueve el fantasma basado en el modo actual cada vez que el temporizador de espera alcanza 0
void fantasma::movimiento(int jugadorY , int jugadorX)
{
    if(espera){
        --espera;
    }
    else {
        switch(modo)
        {//Si 'esperando'
         // rebota arriba y abajo
        case 'w':
            esconder();
            if(y==GATE_Y +2)
            {
                ++y;
            }
            else{
                --y;
            }
            presentacion();
            espera=FANTASMA_MAX;
            break;

        // si 'saliendo'
        // hacer un camino para salir de la puerta
        // después de salir de la puerta si el jugador es super pacman, ejecute
        // de lo contrario, perseguir
        case 'e':
            esconder();
            espera= FANTASMA_MAX;
            if(y> GATE_Y+1){
                --y;
            }
            else if(x<GATE_X){
                ++x;
            }
            else if(x>GATE_X){
                --x;
            }
            else if(y!=GATE_Y-1){
                --y;
                SetCursorPosition(GATE_Y,GATE_X+1);
                cout<<juego ->getNivel(GATE_Y,GATE_X+1);
            }
            else{
                _modo=modo;
                if (color==AZUL){
                    modo='r';
                }
                else {
                    modo ='c';

                }
                _dir= 'w';
                espera=0;
            }
            presentacion();
            break;

        // si 'entrar'
        // entra en la casa de fantasmas, luego 'exit'

        case 'n':
            if (y != GATE_Y+1) {
                dir ='s';
                cambioCoords();
                SetCursorPosition(GATE_Y,GATE_X+1);
                cout<< juego ->getNivel(GATE_Y,GATE_X +1);
                espera=DEAD_MAX;
            }
            else {
                color=color_;
                modo= 'e';
                espera=FANTASMA_MAX;
                icono= ICONO_FANTASMA;
            }
            break;
        // si 'dispersión'
        // se mueven en una dirección aleatoria
        case 's':
            getOpuesto();
            if(_modo=='e') {
                _modo = modo;
            }
            if (modo != _modo) {
                dir= dir_;
                cambioCoords();
                _modo=modo;
            }
            else {
                randomDireccion();
            }
            _dir=dir;
            espera=FANTASMA_MAX;
            break;

        // si 'persiguiendo'
        // apuntar al jugador
        case 'c':
            getOpuesto();
            if( _modo == 'e') {
                _modo=modo;

            }
            if( modo != _modo) {
                dir = dir_;
                cambioCoords();
                _modo = modo;
            }
            else {
                bool down =y < jugadorY;
                bool up=y > jugadorY;
                bool right=x < jugadorX;
                bool left =x >jugadorX;
                bool favorableDirs[4]={up,left,down, right };
                objetoObjetivo(favorableDirs);

            }
            _dir=dir;
            espera=FANTASMA_MAX;
            break;
        // si 'corriendo'
        // evitar el jugador
        case 'r':
            getOpuesto();
            if(_modo=='e') {
                _modo = modo;

            }
            if(modo != _modo) {
                dir= dir_;
                cambioCoords();
                _modo=modo;
            }
            else {
                bool down = !(y < jugadorY);
                bool up = !(y > jugadorY);
                bool right = !(x < jugadorX);
                bool left = !(x > jugadorX);
                bool favorableDirs[4] = { up, left, down, right };
                objetoObjetivo(favorableDirs);
            }
            _dir=dir;
            espera= RUN_MAX;
            break;

        // si 'muerto'
        // apuntar a la puerta de la casa del fantasma
        // cuando se alcanza la puerta, 'entrar'
        case 'd':
            getOpuesto();
            if(y!= GATE_Y-1 || x!= GATE_X) {
                bool down = y < GATE_Y - 1;
                bool up = y > GATE_Y - 1;
                bool right = x < GATE_X;
                bool left = x > GATE_X;
                bool favorableDirs[4] = { up, left, down, right };
                objetoObjetivo(favorableDirs);

            }
            else {
                modo ='n';
            }
            _dir=dir;
            espera= DEAD_MAX;
        }
    }
}

void fantasma::objetoObjetivo(bool favorableDirs[4]) {
    int good=0;
    char goodDirs[4]={' ',' ',' ',' '  };
    for(int i=0;i<4;++i) {
        dir = ALL_DIRS[i];
        if(favorableDirs[i] && TestForCollision()==false && dir != dir_) {
            goodDirs[good] = dir;
            ++good;

        }
    }
    if (good==0) {
        randomDireccion();
    }
    else {
        dir= goodDirs[rand() % good];
        cambioCoords();

    }

}
void fantasma::randomDireccion() {
    getOpuesto();
    // selecciona una dirección aleatoria que da como resultado ninguna colisión
    do {
        // selecciona una dirección de randon que no es opuesta a la dirección anterior
        do {
            dir = ALL_DIRS[rand() %4];
        } while(dir== dir_);
    } while(TestForCollision()== true);
    cambioCoords();
}

bool fantasma::TestForCollision() {
// Si el personaje frente al fantasma es un espacio, se mueve en la dirección adecuada
    switch(dir) {
    case 'a':
        //si viaja atraves del tunel
        if(x==0 || strchr(NO_COLLISION_TILES, juego->getNivel(y,x-1))) {
            return false;
        }
        break ;

    case 'd':
        //si viaja atraves del tunel
        if(x==ANCHO_NIVEL-1 || strchr(NO_COLLISION_TILES, juego ->getNivel(y,x+1))) {
            return false;
        }
    case 'w':
        if (strchr(NO_COLLISION_TILES, juego->getNivel(y - 1, x))) {
            return false;
        }
        break;
    case 's':
        if (strchr(NO_COLLISION_TILES, juego->getNivel(y + 1, x))) {
            return false;
        }
        break;
    }
    return true;

}

void fantasma::cambioCoords()
{
    esconder();
    if(dir=='a') {
        if(x==0) {
            x = ANCHO_NIVEL -1;
        }
        else {
            --x;
        }
    }
    if(dir=='d') {
        if (x==ANCHO_NIVEL-1) {
            x=0;
        }
        else {
            ++x;
        }
    }
    if(dir=='w') {
        --y;
    }
    if(dir =='s') {
        ++y;
    }
    presentacion();
}

void fantasma::getOpuesto()
{
    if(_dir=='a') {
        dir_='d';
    }
    if(_dir=='d') {
        dir_='a';
    }
    if(_dir=='w') {
        dir_='s';
    }
    if(_dir=='s') {
        dir_='w';
    }
}
void fantasma::muerte()
{
    color = BLANCO;
    _modo=modo;
    modo = 'd';
    icono= MUERTE_ICONO_FANTASMA;
}

void fantasma::presentacion()
{
    SetTextColor(color);
    SetCursorPosition(y,x);
    cout<<icono;
}

void fantasma::esconder()
{
    SetTextColor(BLANCO);
    if(juego->getNivel(y,x)=='o') {
        SetTextColor(juego->GetBolitaColor());
    }
    SetCursorPosition(y,x);
    cout<< juego->getNivel(y,x);
}
