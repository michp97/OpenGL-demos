#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<math.h>
#include<iostream>

#define M_PI 3.14159265358979323846

float angle = 90.0;
float x = 0.0;
float y = 0.0;

float dx = 0.2;
float dy = 0.2;
float r = 0.5;
float counter = 1;

bool bStart = false;
int xBorder = 3;
int yBorder = 3;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void DrawCube()
{
        glColor3f(0.0,1.0,1.0);
		glBegin(GL_QUADS);			// front face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
		glEnd();
}

void DrawCircle(int n){
    for (int k=0; k<=n-1; k++){
        glColor3f(255,255,255);
        glBegin(GL_TRIANGLES);
        glVertex3f( 0.0, 0.0, -0.499);
        glVertex3f( 0.4 * cos( ( (2*M_PI) / n ) * k ), 0.4 * sin ( ( (2*M_PI) / n ) * k ), -0.499);
        glVertex3f( 0.4 * cos( ( (2*M_PI) / n ) * (k+1) ), 0.4 * sin ( ( (2*M_PI) / n ) * (k+1) ), -0.499);
        glEnd();
    }
}

void DrawCircle2(int n){
    for (int k=0; k<=n-1; k++){
        glColor3f(0,255,255);
        glBegin(GL_TRIANGLES);
        glVertex3f( 0.0, 0.0, -0.499);
        glVertex3f( 0.4 * cos( ( (2*M_PI) / n ) * k ), 0.4 * sin ( ( (2*M_PI) / n ) * k ), -0.499);
        glVertex3f( 0.4 * cos( ( (2*M_PI) / n ) * (k+1) ), 0.4 * sin ( ( (2*M_PI) / n ) * (k+1) ), -0.499);
        glEnd();
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
        glTranslatef(0.0, 0.0, -15.0);
        glColor3f(0.2,1.0,0.3);
		glBegin(GL_QUADS);
			glVertex3f(5.0f, -5.0f, -0.5f);
			glVertex3f(5.0f, 5.0f, -0.5f);
			glVertex3f(-5.0f, 5.0f, -0.5f);
			glVertex3f(-5.0f, -5.0f, -0.5f);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(x, y, -8);
        glRotatef(angle,0.0,0.0,1.0);
        glTranslatef(0, 0, -5);

        if(!bStart){
            glColor3f(0.0,0.0,0.0); //wskazówka
            glBegin(GL_LINES);
            glVertex2f(y,x);
            glVertex2f(y+2,x);
            glEnd();
        }
        DrawCircle(20);
}


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    int loop=1;
    SDL_Event myevent;
    init();
    while (loop==1)
    {
        while (SDL_PollEvent(&myevent))
        {
            switch(myevent.type)
            {
                case SDL_QUIT:
                loop=0;
                break;

                case SDL_KEYDOWN:
                if (myevent.key.keysym.sym==SDLK_LEFT && !bStart) angle+=5;
                if (myevent.key.keysym.sym==SDLK_RIGHT && !bStart) angle-=5;
                if (myevent.key.keysym.sym==SDLK_SPACE) bStart = true;
                break;
            }
        }

        if(bStart){
            x += dx * counter * cos((angle*M_PI)/180);
            if(x >= 4 || x <= -4) dx = -dx;
            y += dy * counter * sin((angle*M_PI)/180);
            if(y >= 4 || y <= -4) dy = -dy;
            counter *= 0.994;
        }
        display();
        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
    return 0;
}
