#include "bolita.h"
#include<iostream>
#include "Juego.h"
#include "atributosConsola.h"
using namespace std;


bolita::bolita(Juego *const g)
: juego(g){}

void bolita::print()
{
    SetCursorPosition(y,x);
    cout<< juego->getNivel(y,x);
}

