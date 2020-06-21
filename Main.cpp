#include <GL/glut.h>
#include <GL/freeglut.h>
#include <ctime>
#include <iostream>
#include "DrawObjects.h"
#include "LeapFrog.h"
int NN = 100;//number of timesteps per frame 
Config config;
Particle Pelota;
//Particle Pelota2;
int auxiliar = 1;

GLfloat Drotation = 0.05f;
GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };  /* Infinite light location. */

GLfloat rotangv = 0.005; //camera angle rotation frecuency
GLfloat DT = 0.033f / NN;
void Draw(void);
void Initialize();
void idle();
void Timer(int iUnused);
void SetParticleParams(void);

int main(int argc, char** argv)
{

	SetParticleParams();
	FillSphereVertices();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("boucing");
	Initialize();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glutDisplayFunc(Draw);
	glutIdleFunc(idle);

	Timer(0);
	glutMainLoop();

	return 0;
}

void Draw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawSphere(Pelota.R[0], Pelota.R[1], Pelota.R[2], Pelota.rad);
	//DrawSphere(Pelota2.R[0], Pelota2.R[1], Pelota2.R[2], Pelota2.rad);

	DrawGrid(50, 0.1f, -1.0f);
	//glRotatef(Drotation, 0.0, 1.0, 0.0);
	DrawBoxGrid(1.0f, 0.0f, 0.01f, 0.0f);
	glColor3f(0.5f, 0.1f, 0.1f);

	glutSwapBuffers();
}

void Initialize()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 40.0,
		/* aspect ratio */ 8.0 / 6.0,
		/* Z near */ 1.0, /* Z far */ 10.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 4.0,  /* eye is at */
		0.0, 0.0, 0.0,      /* center is at (0,0,0) */
		0.0, 1.0, 0.0);      /* up is in posiBtive Y direction */

	 /* Adjust cube position to be asthetic angle. */
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(0.0, 0.0, 0.0, 0.0);

}

void idle()
{
	if (auxiliar == 1) //timestep leave idle functioning, so auxiliar int makes idle happen only ONCE every 33ms
	{

		for (int mm = 0; mm <= NN; mm++)
		{
			GLfloat RAD = Pelota.rad;

			compute_force(Pelota, config);
			//compute_force(Pelota2, config);


			timestep(DT, Pelota);
			//timestep(DT, Pelota2);

			//BallBallBounce(Pelota2, Pelota);


		}
	}
	auxiliar = 0;
}


void Timer(int iUnused)
{
	auxiliar = 1;
	glutPostRedisplay();
	glutTimerFunc((GLint)(DT * 1000 * NN), Timer, 0);

}

void SetParticleParams(void)
{
	config.read("ConfigParams.txt");
	Pelota.read("ParticleParams.txt");
	//Pelota2.read("Particle2Params.txt");
}