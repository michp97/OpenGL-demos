#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<math.h>

float y = 10;
int gravity = 5;
float friction = 0.5;
float speed = 5;
bool Start = false;
float dt = 0.2;


void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(0, 0, -30);

		glColor3f(0.0,1.0,0.0);
		glBegin(GL_QUADS);			// "kulka"
			glVertex3f(0.5f, -0.5f + y, -0.5f);
			glVertex3f(-0.5f, -0.5f + y, -0.5f);
			glVertex3f(-0.5f, 0.5f + y, -0.5f);
			glVertex3f(0.5f, 0.5f + y, -0.5f);
		glEnd();

		glColor3f(0.0,1.0,1.0);
        glBegin(GL_QUADS);			// podloga
			glVertex3f(10.5f, -10.5f, -0.5f);
			glVertex3f(-10.5f, -10.5f, -0.5f);
			glVertex3f(-10.5f, -10.0f, -0.5f);
			glVertex3f(10.5f, -10.0f, -0.5f);
		glEnd();

        glColor3f(0.0,1.0,1.0);
        glBegin(GL_QUADS);			// suwak tarcie
			glVertex3f(0.5f - 8, -0.5f -1, -0.5f);
			glVertex3f(-0.5f - 8, -0.5f - 1, -0.5f);
			glVertex3f(-0.5f - 8, 0.5f + friction * 10, -0.5f);
			glVertex3f(0.5f - 8, 0.5f + friction * 10, -0.5f);
		glEnd();

        glColor3f(255,255,255);
        glBegin(GL_QUADS);			// suwak grawitacja
			glVertex3f((0.5f) - 10, (-0.5f + gravity), -0.5f);
			glVertex3f((-0.5f) - 10, (-0.5f + gravity), -0.5f);
			glVertex3f((-0.5f) - 10, (0.5f) - 2, -0.5f);
			glVertex3f((0.5f) - 10, (0.5f) - 2, -0.5f);
		glEnd();


    glPopMatrix();

    if(Start){
        float movement = speed * dt + 0.5 * gravity * dt * dt;
        speed += gravity * dt;
        y -= movement;
        if(y<-9.5){
            speed = -(speed * friction);
            y = -9.5;
        }
    }
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
                if (myevent.key.keysym.sym==SDLK_SPACE){
                    if(!Start){
                        Start = true;
                    }
                    else{
                        Start = false;
                        y = 10;
                    }
                }
                if (myevent.key.keysym.sym==SDLK_UP && friction < 1){
                    friction+=0.1;
                }
                if (myevent.key.keysym.sym==SDLK_DOWN && friction > 0){
                    friction-=0.1;
                }
                if (myevent.key.keysym.sym==SDLK_LEFT && gravity > 0){
                    gravity -= 1;
                }
                if (myevent.key.keysym.sym==SDLK_RIGHT && gravity <= 10){
                    gravity += 1;
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
