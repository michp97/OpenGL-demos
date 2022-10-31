#include <SDL/SDL.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <iostream>
#include <random>
#include <time.h>



int plansza[6][3]; //plansza na karty z kolorami, zostanie ona wype³niona numerami od 1 od 9 podczas inicjalizacji gry
int overlay[6][3]; //plansza zas³aniaj¹ca kolory, 0 = zas³ania kolor, 1 = odslania kolor
int px = 1, py = 1; //pozycja wksaźnika
int unmatchCounter = 1; //licznik wykonanych odsłonięć kart

//pozycje dwóch ostatnich odsłoniętych kart
int guessX1 = -1, guessY1 = -1;
int guessX2 = -1, guessY2 = -1;

bool wygrana = false; //koniec gry
bool fail = false; //złe zgadnięcie
bool cheat = false;
int stopTimer = 0;
int winCounter = 0; //ilość poprawnie odgadniętych kart

void createNewGame(){

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            plansza[i][j] = 0;
            overlay[i][j] = 0;
        }
    }

    px = 1, py = 1;
    unmatchCounter = 1;

    guessX1 = -1; guessY1 = -1;
    guessX2 = -1; guessY2 = -1;

    wygrana = false;
    fail = false;
    stopTimer = 0;
    winCounter = 0;

    //generowanie nowych kolorów
    for (int i = 1; i < 10; i++) {
        int counter = 0;
        while (counter < 2) {
            int randx = rand() % 6, randy = rand() % 3;
            if (plansza[randx][randy] == 0) {
                counter++;
                plansza[randx][randy] = i;
            }
        }
    }
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 640.0 / 480.0, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    srand(time(nullptr));

    createNewGame();

}

void DrawColor(int x, int y)
{
    glBegin(GL_QUADS);
    glVertex3f(0.0 + x + (0.1 * x), 1.0 + y + (0.1 * y), 0.5);
    glVertex3f(1.0 + x + (0.1 * x), 1.0 + y + (0.1 * y), 0.5);
    glVertex3f(1.0 + x + (0.1 * x), 0.0 + y + (0.1 * y), 0.5);
    glVertex3f(0.0 + x + (0.1 * x), 0.0 + y + (0.1 * y), 0.5);
    glEnd();
}

void DrawOverlay(int x, int y)
{
    glBegin(GL_QUADS);
    glVertex3f(0.0 + x + (0.1 * x), 1.0 + y + (0.1 * y), 0.5001);
    glVertex3f(1.0 + x + (0.1 * x), 1.0 + y + (0.1 * y), 0.5001);
    glVertex3f(1.0 + x + (0.1 * x), 0.0 + y + (0.1 * y), 0.5001);
    glVertex3f(0.0 + x + (0.1 * x), 0.0 + y + (0.1 * y), 0.5001);
    glEnd();
}


void DrawCursor(int x, int y)
{
    glBegin(GL_QUADS);
    glVertex3f(0.0 + x + (0.1 * x), 1.0 + y + (0.1 * y), 0.501);
    glVertex3f(1.0 + x + (0.1 * x), 1.0 + y + (0.1 * y), 0.501);
    glVertex3f(1.0 + x + (0.1 * x), 0.0 + y + (0.1 * y), 0.501);
    glVertex3f(0.0 + x + (0.1 * x), 0.0 + y + (0.1 * y), 0.501);
    glEnd();
}

void DrawCounter(int x, int y)
{
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex3f(0.00 + ((x * 0.2) -0.5) + (0.1 * x), 0.25 + ((y * 0.2) + 4) + (0.1 * y), 0.5);
    glVertex3f(0.25 + ((x * 0.2) -0.5) + (0.1 * x), 0.25 + ((y * 0.2) + 4) + (0.1 * y), 0.5);
    glVertex3f(0.25 + ((x * 0.2) -0.5) + (0.1 * x), 0.00 + ((y * 0.2) + 4) + (0.1 * y), 0.5);
    glVertex3f(0.00 + ((x * 0.2) -0.5) + (0.1 * x), 0.00 + ((y * 0.2) + 4) + (0.1 * y), 0.5);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-3.3, -1.5, -8);
    glColor3f(0.8, 0.8, 0.8);

    // rysowanie kolorów //
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            if (plansza[i][j] == 0) {
                glColor3f(1, 1, 1); //biały
            }
            else if (plansza[i][j] == 1) {
                glColor3f(1, 0, 0); //czerwony
            }
            else if (plansza[i][j] == 2) {
                glColor3f(0, 1, 0); //zielony
            }
            else if (plansza[i][j] == 3) {
                glColor3f(0, 0, 1); //niebieski
            }
            else if (plansza[i][j] == 4) {
                glColor3f(0, 1, 1); //cyan
            }
            else if (plansza[i][j] == 5) {
                glColor3f(1, 0, 1); //różowy
            }
            else if (plansza[i][j] == 6) {
                glColor3f(1, 1, 0); //żółty
            }
            else if (plansza[i][j] == 7) {
                glColor3f(0.5, 0.5, 1); //jasny niebieski
            }
            else if (plansza[i][j] == 8) {
                glColor3f(1, 0.5, 0.5); //flamingo
            }
            else if (plansza[i][j] == 9) {
                glColor3f(0.5, 0.5, 0.5); //szary
            }

            DrawColor(i, j);


            // ukrywanie kolorów //
            if (overlay[i][j] == 0) { //ignorowanie ods³oniêtych kart
                if(!cheat){
                    glColor3f(1, 1, 1);
                    DrawOverlay(i, j);
                }

            }
        }
    }

    // rysowanie licznika //
    int loop = (unmatchCounter-1)/2;
    for(int i = 0, j = 0; i < loop; i++){
        if(i > 24){
            i = 0;
            loop-=25;
            j--;
        }
        DrawCounter(i,j);
    }

    // rysowanie kursora //
    if (!wygrana) {
        if(!fail){
            glColor3f(0.2, 0.1, 0.4);
            DrawCursor(px, py);
        }
    }
    else{
        stopTimer++;
        if(stopTimer>200){
            stopTimer = 0;
            createNewGame();
        }
    }

    // chwilowe zatrzymanie gry podczas błędnego zgadnięcia //
    if(fail){
        stopTimer++;
        if(stopTimer>60){
            fail = false;
            stopTimer = 0;
            overlay[guessX1][guessY1] = 0;
            overlay[guessX2][guessY2] = 0;
            guessX1 =guessY1 = guessX2 = guessY2 = -1;
        }
    }
    glPopMatrix();
}


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_OPENGL);

    int loop = 1;
    SDL_Event myevent;
    init();
    while (loop == 1)
    {
        while (SDL_PollEvent(&myevent))
        {
            switch (myevent.type)
            {
            case SDL_QUIT:
                loop = 0;
                break;

            case SDL_KEYDOWN:
                // movement //
                if (myevent.key.keysym.sym == SDLK_LEFT && px > 0 && !fail) px--;
                if (myevent.key.keysym.sym == SDLK_RIGHT && px < 5 && !fail) px++;
                if (myevent.key.keysym.sym == SDLK_UP && py < 2 && !fail) py++;
                if (myevent.key.keysym.sym == SDLK_DOWN && py > 0 && !fail) py--;
                if (myevent.key.keysym.sym == SDLK_r) createNewGame();
                if (myevent.key.keysym.sym == SDLK_q) cheat = !cheat;
                // akcja //
                if (myevent.key.keysym.sym == SDLK_SPACE && overlay[px][py] == 0 && !wygrana) {
                    unmatchCounter++;
                    overlay[px][py] = 1;
                    if (unmatchCounter % 2) {
                        guessX2 = px;
                        guessY2 = py;
                        if (plansza[guessX1][guessY1] != plansza[guessX2][guessY2]) {
                            fail = true;
                        }
                        else{
                            winCounter++;
                            if(winCounter==9){
                                wygrana = true;
                            }
                        }
                    }
                    else {
                        guessX1 = px;
                        guessY1 = py;
                    }
                }
                break;
            }
        }
        display();
        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
    return 0;
}
