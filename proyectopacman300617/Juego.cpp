#include "Juego.h"
#include <windows.h>

#include "constantes.h"
#include <iostream>
#include "atributosConsola.h"
#include "pacman.h"
#include "bolita.h"
using namespace std;

Juego::Juego()
{
    SetWindowTitle("PACMAN");
    SetWindowSize(ALTURA_NIVEL+4,ANCHO_NIVEL);
    SetCursorVisibility(false);
    jugador=new pacman(this);
    for (int i = 0; i < 4; ++i) {

        bolitas[i] = new bolita(this);
    }
}
Juego::~Juego()
{
    delete jugador;
    for (int i = 0; i < 4; ++i) {

        delete bolitas[i];
    }
}

void Juego::inicio()
{
    while(true)
    {
        mainloop();
    }
}

void Juego::mainloop()
{
    jugador->SetPuntaje(0);
    jugador->SetVidas(3);
    bool Findeljuego = false;
    for(int nivelNum=1; nivelNum<=255; ++nivelNum)
    {
        CargarNivel();
        while (jugador->GetLeft()!=0)
        {
            jugador->movimiento();

            if(!jugador->GetVidas())
            {
                Findeljuego=true;
                break;
            }

            UpdateTimers();
        }

        if(Findeljuego)
        {
            break;
        }


    }

}

void Juego::CargarNivel()
{
    char nivel[ALTURA_NIVEL][ANCHO_NIVEL +1]=
    {

        "1555555555555555555555555552",
        "6............^^............6",
        "6.!%%@.!%%%@.^^.!%%%@.!%%@.6",
        "67^  ^.^   ^.^^.^   ^.^  ^86",
        "6.#%%$.#%%%$.#$.#%%%$.#%%$.6",
        "6..........................6",
        "6.!%%@.!@.!%%%%%%@.!@.!%%@.6",
        "6.#%%$.^^.#%%@!%%$.^^.#%%$.6",
        "6......^^....^^....^^......6",
        "355552.^#%%@ ^^ !%%$^.155554",
        "     6.^!%%$ #$ #%%@^.6     ",
        "     6.^^    B     ^^.6     ",
        "     6.^^ 155&&552 ^^.6     ",
        "555554.#$ 6      6 #$.355555",
        "      .   6I   C 6   .      ",
        "555552.!@ 6  P   6 !@.155555",
        "     6.^^ 35555554 ^^.6     ",
        "     6.^^          ^^.6     ",
        "     6.^^ !%%%%%%@ ^^.6     ",
        "155554.#$ #%%@!%%$ #$.355552",
        "6............^^............6",
        "6.!%%@.!%%%@.^^.!%%%@.!%%@.6",
        "6.#%@^.#%%%$.#$.#%%%$.^!%$.6",
        "69..^^.......X .......^^..06",
        "6%@.^^.!@.!%%%%%%@.!@.^^.!%6",
        "6%$.#$.^^.#%%@!%%$.^^.#$.#%6",
        "6......^^....^^....^^......6",
        "6.!%%%%$#%%@.^^.!%%$#%%%%@.6",
        "6.#%%%%%%%%$.#$.#%%%%%%%%$.6",
        "6..........................6",
        "3555555555555555555555555554"
    };
    char curChar;
    SetTextColor(BLANCO);
    SetCursorPosition(-3,0);
    cout << "1UP";
    SetCursorPosition(-3, 5);
    cout << "HIGH SCORE";
    jugador->mostrarPuntaje(0);
    SetCursorPosition(0, 0);
    jugador->SetLeft(0);

    for (int y=0;y < ALTURA_NIVEL; ++y)
    {
        for(int x=0;x<ANCHO_NIVEL;++x){

            curChar= nivel[y][x];
            SetTextColor(AZULOSCURO);

            switch (curChar) {
            case 'X':
                jugador->SetY_(y);
                jugador->SetX_(x);
                nivelMapa[y][x] = ' ';
                break;
            /*case 'B':
                ghosts[BLINKY]->SetYInit(y);
                ghosts[BLINKY]->SetXInit(x);
                ghosts[BLINKY]->SetColorInit(RED);
                ghosts[BLINKY]->SetDirOpp('s');
                nivelMapa[y][x] = ' ';
                break;
            case 'P':
                ghosts[PINKY]->SetYInit(y);
                ghosts[PINKY]->SetXInit(x);
                ghosts[PINKY]->SetColorInit(MAGENTA);
                nivelMapa[y][x] = ' ';
                break;
            case 'I':
                ghosts[INKY]->SetYInit(y);
                ghosts[INKY]->SetXInit(x);
                ghosts[INKY]->SetColorInit(CYAN);
                nivelMapa[y][x] = ' ';
                break;
            case 'C':
                ghosts[CLYDE]->SetYInit(y);
                ghosts[CLYDE]->SetXInit(x);
                ghosts[CLYDE]->SetColorInit(YELLOW);
                nivelMapa[y][x] = ' ';
                break;

                */

            case '7':
                bolitas[0]->setY(y);
                bolitas[0]->setX(x);
                SetTextColor(BLANCO);
                nivelMapa[y][x] = 'o';
                jugador->SetLeft(jugador->GetLeft() + 1);
                break;
            case '8':
                bolitas[1]->setY(y);
                bolitas[1]->setX(x);
                SetTextColor(BLANCO);
                nivelMapa[y][x] = 'o';
                jugador->SetLeft(jugador->GetLeft() + 1);
                break;
            case '9':
                bolitas[2]->setY(y);
                bolitas[2]->setX(x);
                SetTextColor(BLANCO);
                nivelMapa[y][x] = 'o';
                jugador->SetLeft(jugador->GetLeft() + 1);
                break;
            case '0':
                bolitas[3]->setY(y);
                bolitas[3]->setX(x);
                SetTextColor(BLANCO);
                nivelMapa[y][x] = 'o';
                jugador->SetLeft(jugador->GetLeft() + 1);
                break;
            case '.':
                SetTextColor(BLANCO);
                nivelMapa[y][x] = char(250);
                jugador->SetLeft(jugador->GetLeft() + 1);
                break;
            case ' ':
                nivelMapa[y][x] = curChar;
                break;
            case '&':
                SetTextColor(BLANCO);
                curChar = '%';
            }


            if (curChar == '1') {
                nivelMapa[y][x] = char(201);
            }
            else if (curChar == '2') {
                nivelMapa[y][x] = char(187);
            }
            else if (curChar == '3') {
                nivelMapa[y][x] = char(200);
            }
            else if (curChar == '4') {
                nivelMapa[y][x] = char(188);
            }
            else if (curChar == '5') {
                nivelMapa[y][x] = char(205);
            }
            else if (curChar == '6') {
                nivelMapa[y][x] = char(186);
            }
            else if (curChar == '!') {
                nivelMapa[y][x] = char(218);
            }
            else if (curChar == '@') {
                nivelMapa[y][x] = char(191);
            }
            else if (curChar == '#') {
                nivelMapa[y][x] = char(192);
            }
            else if (curChar == '$') {
                nivelMapa[y][x] = char(217);
            }
            else if (curChar == '%') {
                nivelMapa[y][x] = char(196);
            }
            else if (curChar == '^') {
                nivelMapa[y][x] = char(179);
            }
            cout << nivelMapa[y][x];
        }
        SetCursorPosition(y+1,0);

    }
    InitAll();
    ShowAll();
    jugador->mostrarVidas();
    PrintReady();

}



void Juego::PrintReady() {
    SetTextColor(AMARILLO);
    SetCursorPosition(17, 11);
    cout << "READY!";
    Sleep(2000);
    SetCursorPosition(17, 11);
    cout << "      ";
}

void Juego::PrintGameOver() {
    SetCursorPosition(17, 9);
    SetTextColor(ROJO);
    cout << "GAME  OVER";
    Sleep(1000);
}



void Juego::UpdateTimers() {
    // handle super pacman
    if (jugador->GetSuper()) {
        jugador->SetSuper(jugador->GetSuper() - 1);
        if (jugador->GetSuper() <= 112 && jugador->GetSuper() % 28 == 0) {

            ShowAll();
        }
        if (jugador->GetSuper() <= 98 && (jugador->GetSuper() + 14) % 28 == 0) {

            ShowAll();
        }
        if (!jugador->GetSuper()) {

            ShowAll();
        }
    }
    // handle flashing 1UP
    if (oneUpTimer) {
        --oneUpTimer;
    }
    else {
        if (oneUpColor == BLANCO) {
            oneUpColor = NEGRO;
        }
        else {
            oneUpColor = BLANCO;
        }
        SetTextColor(oneUpColor);
        SetCursorPosition(-3, 3);
        cout << "1UP";
        oneUpTimer = ONE_UP_MAX;
    }
    // handle flashing super pellets

    Sleep(15);
}





void Juego::ShowAll() {
    jugador->presentacion();

}

void Juego::HideAll() {
    jugador->esconder();


}

void Juego::InitAll() {
    jugador->SetY(jugador->GetY_());
    jugador->SetX(jugador->GetX_());
    jugador->SetColor(AMARILLO);
    jugador->SetIcono(ICONOS[1]);
    jugador->Set_dir('a');
    jugador->SetEspera(0);
    jugador->SetSuper(0);

}
