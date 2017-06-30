#include "Juego.h"
#include <windows.h>
#include "fantasma.h"
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
        fantasmas[i]= new fantasma(this);
        bolitas[i] = new bolita(this);
    }
}
Juego::~Juego()
{
    delete jugador;
    for (int i = 0; i < 4; ++i) {
        delete fantasmas[i];
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
        // Mientras todavía hay puntos en la pantalla,
        while (jugador->GetLeft()!=0)
        {
            jugador->movimiento();
            comprobarMuerte();
            if(!jugador->GetVidas())
            {
                Findeljuego=true;
                break;
            }
            moverFantasma();
            comprobarMuerte();
            if(!jugador->GetVidas()) {
                Findeljuego=true;
                break;
            }

            UpdateTimers();
        }

        if(Findeljuego)
        {
            break;
        }
        siguienteNivel();
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
    cout << "  ";
    SetCursorPosition(-3, 14);
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
            case 'B':
                fantasmas[BLINK]->SetY_(y);
                fantasmas[BLINK]->SetX_(x);
                fantasmas[BLINK]->SetColor_(ROJO);
                fantasmas[BLINK]->SetDir_('s');
                nivelMapa[y][x] = ' ';
                break;
            case 'P':
                fantasmas[PINK]->SetY_(y);
                fantasmas[PINK]->SetX_(x);
                fantasmas[PINK]->SetColor_(ROSA);
                nivelMapa[y][x] = ' ';
                break;
            case 'I':
                fantasmas[INK]->SetY_(y);
                fantasmas[INK]->SetX_(x);
                fantasmas[INK]->SetColor_(CELESTE);
                nivelMapa[y][x] = ' ';
                break;
            case 'C':
                fantasmas[CLY]->SetY_(y);
                fantasmas[CLY]->SetX_(x);
                fantasmas[CLY]->SetColor_(AMARILLO);
                nivelMapa[y][x] = ' ';
                break;



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
void Juego::siguienteNivel() {
    Sleep(1000);
    HideAll();
    SetCursorPosition(12, 13);
    cout << "  ";
    for (int i = 0; i < 4; ++i) {
        SetScreenColor(BLANCO);
        jugador->presentacion();
        Sleep(200);
        SetScreenColor(AZULOSCURO);
        jugador->presentacion();
        Sleep(200);
    }
    SetCursorPosition(0, 0);
    InitAll();
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

void Juego::moverFantasma() {
    // Comprobar si hay cambios en el modo fantasma
    if (jugador->GetSuper() == SUPER_MAX) {
        jugador->SetCont_muertes(0);
        for (int i = 0; i < 4; ++i) {
            if (fantasmas[i]->GetModo() != 'd') {
                fantasmas[i]->SetColor(AZUL);
            }
            if (fantasmas[i]->GetModo() == 's' || fantasmas[i]->GetModo() == 'c') {
                fantasmas[i]->SetModo('r');
            }
        }
        ShowAll();
    }
    if (jugador->GetLeft() == 235 && fantasmas[PINK]->GetModo() == 'w') {
        fantasmas[PINK]->SetModo('e');
    }
    if (jugador->GetLeft() == 200 && fantasmas[INK]->GetModo() == 'w') {
        fantasmas[INK]->SetModo('e');
    }
    if (jugador->GetLeft() == 165 && fantasmas[CLY]->GetModo() == 'w') {
        fantasmas[CLY]->SetModo('e');
    }
    for (int i = 0; i < 4; ++i) {
        fantasmas[i]->movimiento(jugador->GetY(), jugador->GetX());
    }
    ShowAll();
}

void Juego::UpdateTimers() {
    // Manejar super pacman
    if (jugador->GetSuper()) {
        jugador->SetSuper(jugador->GetSuper() - 1);
        if (jugador->GetSuper() <= 112 && jugador->GetSuper() % 28 == 0) {
            for(int i=0;i<4;++i)
            if(fantasmas[i]->GetColor()== AZUL ){
                fantasmas[i]->SetColor(BLANCO);
            }
            ShowAll();
        }
        if (jugador->GetSuper() <= 98 && (jugador->GetSuper() + 14) % 28 == 0) {
            for (int i = 0; i < 4; ++i) {
                if (fantasmas[i]->GetColor() == BLANCO && fantasmas[i]->GetModo() != 'd' && fantasmas[i]->GetModo() != 'n') {
                    fantasmas[i]->SetColor(AZUL);
                }
            }
            ShowAll();
        }
        if (!jugador->GetSuper()) {
            for (int i = 0; i < 4; ++i) {
                if (fantasmas[i]->GetModo() != 'd' && fantasmas[i]->GetModo() != 'n') {
                    fantasmas[i]->SetColor(fantasmas[i]->GetColor_());
                }
                if (fantasmas[i]->GetModo() == 'r') {
                    fantasmas[i]->Set_Modo(fantasmas[i]->GetModo());
                    fantasmas[i]->SetModo('c');
                }
            }

            ShowAll();
        }
    }
// manejar parpadear 1UP
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
   // manejar parpadear  super bolitas

    if (bolitaTiempo) {
        --bolitaTiempo;
    }
    else {
        if (bolitaColor == BLANCO) {
            bolitaColor = NEGRO;
        }
        else {
            bolitaColor = BLANCO;
        }
        SetTextColor(bolitaColor);
        for (int i = 0; i < 4; ++i) {
            bolitas[i]->print();
        }
        ShowAll();
        bolitaTiempo = BOLITA_MAX;
    }
    // handle ghost chase/scatter mode
    if (fantasmaModoTiempo) {
        --fantasmaModoTiempo;
        if (fantasmaModoTiempo == MODE_MAX / 4) {
            for (int i = 0; i < 4; ++i) {
                if (fantasmas[i]->GetModo() == 'c') {
                    fantasmas[i]->SetModo('s');
                }
            }
        }
    }
    else {
        for (int i = 0; i < 4; ++i) {
            if (fantasmas[i]->GetModo() == 's') {
                fantasmas[i]->SetModo('c');
            }
        }
        fantasmaModoTiempo = MODE_MAX;
    }


    Sleep(15);
}

void Juego::comprobarMuerte() {
    for (int i = 0; i < 4; ++i) {
        if (jugador->GetX() == fantasmas[i]->GetX() && jugador->GetY() == fantasmas[i]->GetY() &&
            fantasmas[i]->GetModo() != 'd' && fantasmas[i]->GetModo() != 'n') {
            if (fantasmas[i]->GetModo() != 'r') {
                jugador->muerte();
            }
            else {
                jugador->PrintKillScore();
                fantasmas[i]->muerte();
            }
        }
    }
}




void Juego::ShowAll() {
    jugador->presentacion();
    for(int i=0;i<4; ++i) {
        fantasmas[i]->presentacion();
    }

}

void Juego::HideAll() {
    jugador->esconder();
    for(int i=0;i<4; ++i) {
        fantasmas[i] ->esconder();
    }


}

void Juego::InitAll() {
    jugador->SetY(jugador->GetY_());
    jugador->SetX(jugador->GetX_());
    jugador->SetColor(AMARILLO);
    jugador->SetIcono(ICONOS[1]);
    jugador->Set_dir('a');
    jugador->SetEspera(0);
    jugador->SetSuper(0);
    for (int i = 0; i < 4; ++i) {
        fantasmas[i]->SetY(fantasmas[i]->GetY_());
        fantasmas[i]->SetX(fantasmas[i]->GetX_());
        fantasmas[i]->SetColor(fantasmas[i]->GetColor_() );
        fantasmas[i]->SetModo('w');
        fantasmas[i]->SetEspera(0);
        fantasmas[i]->SetIcono(ICONO_FANTASMA);
    }
    fantasmas[BLINK]->SetModo('c');
    fantasmas[BLINK]->Set_Modo('c');
    if (jugador->GetLeft() <= 235) {
        fantasmas[PINK]->SetModo('e');
    }
    if (jugador->GetLeft() <= 200) {
        fantasmas[INK]->SetModo('e');
    }
    if (jugador->GetLeft() <= 165) {
        fantasmas[CLY]->SetModo('e');
    }

}
