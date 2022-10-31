#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>


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
		glBegin(GL_QUADS);			// top face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
		glEnd();
		glBegin(GL_QUADS);			// front face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
		glEnd();
		glBegin(GL_QUADS);			// right face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();
		glBegin(GL_QUADS);			// left face
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
		glEnd();
		glBegin(GL_QUADS);			// bottom face
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
		glEnd();
		glBegin(GL_QUADS);			// back face
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();
}

    int a, b = 0;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
//
//    glTranslatef(10.0, 0.0, -15.0);
//    glRotatef(90,0.0,1.0,0.0);

    glTranslatef(1.0, -4.0, -5.0);
    glRotatef(30, 1.0, 1.0, 0.0);

    glPushMatrix(); //kokpit
    glColor3f(0.8,0.8,0.8);
    glTranslatef(1.0,1.0,-10.0);
    glScalef(1.5,1.0,1.0);
    DrawCube();
    glPopMatrix();

    glPushMatrix(); //ogon
    glColor3f(0.5,0.5,0.5);
    glTranslatef(2.5,1.0,-10.0);
    glScalef(3,0.3,0.3);
    DrawCube();
    glPopMatrix();

    glPushMatrix(); //noga 1
    glColor3f(0.3,0.3,0.3);
    glTranslatef(1.0,0.3,-9.5);
    glScalef(3.0,0.3,0.3);
    DrawCube();
    glPopMatrix();

    glPushMatrix(); //noga 2
    glColor3f(0.3,0.3,0.3);
    glTranslatef(1.0,0.3,-10.5);
    glScalef(3.0,0.3,0.3);
    DrawCube();
    glPopMatrix();

    glPushMatrix(); //smiglo duze
    glColor3f(0.7,0.3,0.5);
    glTranslatef(1.1,1.6,-10);
    glRotatef(b,0,b,0);
    glScalef(4.0,0.1,0.4);
    DrawCube();
    glPopMatrix();

    glPushMatrix(); //smiglo male
    glColor3f(0.7,0.3,0.5);
    glTranslatef(3.3,0.9,-9.5);
    glRotatef(a,0,0,1);
    glScalef(0.2,0.8,0.1);
    DrawCube();
    glPopMatrix();

    a += 8;
    b += 4;
}



int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    int petla=1;
//    Uint32 start;
    SDL_Event zdarzenie;
    init();
    while (petla==1)
    {
//        start=SDL_GetTicks();
        while (SDL_PollEvent(&zdarzenie))
        {
            switch(zdarzenie.type)
            {
                case SDL_QUIT:
                petla=0;
                break;
            }
        }
        display();
        SDL_GL_SwapBuffers();
//        if (1000/30>(SDL_GetTicks()-start)) SDL_Delay(SDL_GetTicks()-start);
    }
    SDL_Quit();
    return 0;
}
