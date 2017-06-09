#include "pacman.h"
#include<iostream>
#include <windows.h>
#include "constantes.h"
#include "Juego.h"
#include "pacman.h"
#include "atributosConsola.h"
#include<conio.h>
#include <iomanip>
using namespace std;


pacman::pacman(Juego *const g)
: juego(g){
    puntajeAlto=0;
}

void pacman::movimiento()
{
    if (espera)
    {
        --espera;
    }
    else{
        getDireccion();
        if (TestForCollision() == false) {
            //
            SetCursorPosition(_y, _x);
            cout << juego->getNivel(_y, _x);
            //
            if (juego->getNivel(y, x) != ' ') {
                int puntajeInc;
                if (juego->getNivel(y, x) == 'o') {
                    puntajeInc = 50;
                    super = SUPER_MAX;
                }
                else {
                    puntajeInc = 10;
                }
                mostrarPuntaje(puntajeInc);
                juego->SetNivel(y, x, ' ');
                --left;
            }
            presentacion();
            _dir = dir;
            espera = PACMAN_MAX;
        }

    }
}
void pacman::getDireccion()
{
    dir='x';
    if(_kbhit()) //me permite retornar un valor distinto de 0 si presiono alguna tecla
    {
        dir = tolower(_getch());
    }
    if(!strchr(ALL_DIRS,dir))
    {
        dir=_dir;
    }

}
bool pacman::TestForCollision() {
    // coordenadas
    _x = x;
    _y = y;
    // movimiento

    switch (dir) {
    case 'a':
        // atravesando tuneles
        if (x == 0) {
            x = ANCHO_NIVEL - 1; //portal izquierda
            icono = ICONOS[1];
        }
        else if (strchr(NO_COLLISION_TILES, juego->getNivel(y, x - 1))) {
            --x;
            icono = ICONOS[1];
        }
        break;
    case 'd':
        //
        if (x == ANCHO_NIVEL - 1) {
            x = 0;                    //portal derecha
            icono = ICONOS[3];
        }
        else if (strchr(NO_COLLISION_TILES, juego->getNivel(y, x + 1))) {
            ++x;
            icono = ICONOS[3];
        }
        break;
    case 'w':
        if (strchr(NO_COLLISION_TILES, juego->getNivel(y - 1, x))) {
            --y;
            icono = ICONOS[0];
        }
        break;
    case 's':
        if (strchr(NO_COLLISION_TILES, juego->getNivel(y + 1, x))) {
            ++y;
            icono = ICONOS[2];
        }
    }
    //
    if (x == _x && y == _y) {
        return true;
    }
    return false;
}
void pacman::mostrarPuntaje(int puntajeInc)
{
    if (puntaje/1000<(puntaje+puntajeInc)/1000)
    {
        ++vidas;
        mostrarVidas();

    }
    puntaje+=puntajeInc;
    SetTextColor(BLANCO);
    SetCursorPosition(-2,0);
    if(puntaje==0)
    {
        cout<<setw(7)<<"00";
    }
    else{
        cout<<setw(7)<<puntaje;

    }
    if(puntaje>puntajeAlto)
    {
        puntajeAlto=puntaje;
        cout<<setw(11)<<puntajeAlto;
    }
}
void pacman::mostrarVidas()
{


    SetTextColor(color);
    SetCursorPosition(ALTURA_NIVEL, 2);
    for (int i = 1; i < vidas; ++i) {
        cout << ICONOS[1] << " ";
    }
    cout << " ";
}





void pacman::muerte() {
    Sleep(1000);
    juego->HideAll();
    for (int i = 0; i < 8; ++i) {
        icono = ICONOS[i % 4];
        esconder();
        Sleep(100);
    }
    esconder();
    Sleep(500);
    --vidas;
    if (vidas != 0) {
        juego->InitAll();
        juego->ShowAll();
        mostrarVidas();
        juego->PrintReady();
    }
    else {
        juego->PrintGameOver();
    }
}

void pacman::presentacion() {
    SetTextColor(color);
    SetCursorPosition(y, x);
    cout << icono;
}

void pacman::esconder() {
    SetCursorPosition(y, x);
    cout << juego->getNivel(y, x);
}
