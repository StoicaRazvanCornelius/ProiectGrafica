#include "..\GLOS.H"
#include <GL/glu.h>
#include <GL/glaux.h>
#include <GL/glut.h>
#include<math.h>
#include<time.h>
#include <stdio.h>


#define M_PI 3.14
GLuint  IDtextura;
void init();
void CALLBACK display(void);
void desenareObiect();

int main(int argc, char** argv);

int zoom = 0;
int x = 90;
int y = 0;
int z = 0;
int spin = 0;

int xM = 0;
int yM = 0;
int zM = 0;

int camera = 0;

float smoke_x = 0;
float smoke_y = 0;
float smoke_z = 0;
//functii

GLfloat sgenparams[] = { 1.0, 1.0, 1.0, 0.0 };//coeficientii planului fata
// de care se calculeazã directia texturii


#define ImageWidth 51
GLubyte Image[3 * ImageWidth];

void makeStripeImage(void)
{ //construieste o textura 1D cu 3 octeti pentru fiecare texel
	//din 32 texeli 5 sunt rosii si 27 sunt verzi
	int j;

	for (j = 0; j < ImageWidth; j++) {
		Image[3 * j] = 215; //rosu
		Image[3 * j + 1] = 255; //verde
		Image[3 * j + 2] = 255; //albastru
		
	}
}
void init()
{

	LPCWSTR nume = L"iglu.png";
	AUX_RGBImageRec* pImagineTextura = auxDIBImageLoad(nume);

	glClearColor(1, 1, 1, 0.0);
	GLfloat mat_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };
	/*  reflexia speculara si exponentul de reflexie speculara
	nu sunt la valorile implicite (0.0)   */
	GLfloat mat_specular[] = { 0.0, .0, .0, 1.0 };
	GLfloat mat_shininess[] = { 20 };
	//set�ri pentru sursa de lumin�
	GLfloat light_ambient[] = { 0.08, 0.09, .1, .1 };//intensitatea
	//componentei ambientale din sursa 0 este nula
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };//intensitatea
	//componentei difuze din sursa 0 este maxima pentru fiecrae compopnenta de
	//culoare
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 0 };//intensitatea lumina galbena
	//componentei speculare din sursa 0 este maxima pentru fiecrae compopnenta de
	//culoare
	GLfloat light_position[] = { 10, -100.0, -100, 10.0 };


	GLfloat global_ambient[] = { 20.0, 20.0, 20.0, 0.5 };

	GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	
	makeStripeImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//incercati si parametrul GL_DECAL. Veti constata ca nu se tine seama 
	//de iluminare
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//incercati si cu GL_CLAMP. Nu se repeta texturarea. Se prelungec aceeiasi
	//texel-i
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glTexImage1D(GL_TEXTURE_1D, 0, 3, ImageWidth, 0,
		GL_RGB, GL_UNSIGNED_BYTE, Image); //specificare texturii

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);//incercati si GL_OBJECT_PLANE
	glTexGenfv(GL_S, GL_OBJECT_PLANE, sgenparams);	//incercati si parametrul 
	//GL_EYE_PLANE
	//ascunderea suprafeþelor
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_TEXTURE_GEN_S);//se genereaza automat coordonatele texturii pe s
	glEnable(GL_TEXTURE_1D);//texturare 1D
	//tãierea feþelor spate
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_BACK);
	glCullFace(GL_CW);
	//iluminarea
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//calcularea automata a normalelor pentru coordonate generate cu GL_MAP1_VERTEX
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE); //normalizarea normalelor

	

}
void deseneazaPatrat(
	GLfloat x1, GLfloat y1, GLfloat z1,
	GLfloat x2, GLfloat y2, GLfloat z2,
	GLfloat x3, GLfloat y3, GLfloat z3,
	GLfloat x4, GLfloat y4, GLfloat z4) {

	glBegin(GL_QUAD_STRIP);

	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glVertex3f(x3, y3, z3);
	glVertex3f(x4, y4, z4);

	glEnd();

}

void deseneazaBlockIglu(
	GLfloat x1, GLfloat  y1, GLfloat  z1,
	GLfloat  x2, GLfloat  y2, GLfloat  z2,
	GLfloat  x3, GLfloat  y3, GLfloat  z3,
	GLfloat  x4, GLfloat  y4, GLfloat  z4,
	GLfloat  x5, GLfloat  y5, GLfloat  z5,
	GLfloat  x6, GLfloat  y6, GLfloat  z6,
	GLfloat  x7, GLfloat  y7, GLfloat  z7,
	GLfloat  x8, GLfloat  y8, GLfloat  z8) {

	deseneazaPatrat(x1, y1, z1, x2, y2, z2, x4, y4, z4, x3, y3, z3);
	deseneazaPatrat(x1, y1, z1, x2, y2, z2, x5, y5, z5, x6, y6, z6);
	deseneazaPatrat(x1, y1, z1, x4, y4, z4, x5, y5, z5, x8, y8, z8);
	deseneazaPatrat(x3, y3, z3, x2, y2, z2, x7, y7, z7, x6, y6, z6);
	deseneazaPatrat(x3, y3, z3, x4, y4, z4, x7, y7, z7, x8, y8, z8);
	deseneazaPatrat(x5, y5, z5, x6, y6, z6, x8, y8, z8, x7, y7, z7);
}
void CALLBACK display(void)
{	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat position[] = { -300, -0, -0,1.0 };

	glLoadIdentity();
	gluLookAt(-300, -100, 200,-100, -100.0, 100.0, 0, -100.0, -1.0);
	glTranslatef(0, 20, 0);

	glPushMatrix();
	glRotated((GLdouble)spin, 0.0, 0.0, 1.0);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glPopMatrix();

	glPushMatrix();


	glRotatef(x, 1, 0, 0);
	glRotatef(y, 0, 0, 1);
	glRotatef(z, 0, 1, 0);

	glTranslatef(xM, 0, 0);
	glTranslatef( 0, 0, yM);
	glTranslatef(0, zM, 0);

	desenareObiect();

	glPopMatrix();



	glFlush();
}
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
void deseneazaCub(GLfloat h, GLfloat x1, GLfloat y1, GLfloat z1,
	GLfloat x2, GLfloat y2, GLfloat z2,
	GLfloat x3, GLfloat y3, GLfloat z3,
	GLfloat x4, GLfloat y4, GLfloat z4
) {
	deseneazaPatrat(x1, y1, z1, x2, y2, z2, x4, y4, z4, x3, y3, z3);
	deseneazaPatrat(x1, y1, z1, x2, y2, z2, x1, y1, z1 + h, x2, y2, z2 + h);
	deseneazaPatrat(x1, y1, z1, x4, y4, z4, x1, y1, z1 + h, x4, y4, z4 + h);
	deseneazaPatrat(x3, y3, z3, x4, y4, z4, x3, y3, z3 + h, x4, y4, z4 + h);
	deseneazaPatrat(x3, y3, z3, x2, y2, z2, x3, y3, z3 + h, x2, y2, z2 + h);
	deseneazaPatrat(x1, y1, z1 + h, x2, y2, z2 + h, x4, y4, z4 + h, x3, y3, z3 + h);
}
float randomNrFum(int lowerBound, int upperBound) {
	return (rand() % (upperBound - lowerBound + 1) + lowerBound);

}

void desenareObiect()
{

	GLfloat mat_sphere_transp[] = { 0.0, 0.0, 0.0, 1.0 };
	GLUquadric* obj;
	obj = gluNewQuadric();
	/*
	//inceput iglu facut procedural
	float pivotx = 0;
	float pivoty = 0;
	float pivotz = 0;
	float r = 200;
	float alfa = M_PI / 2;
	float beta = 0;
	float width = 10;
	float factorCresterealfa = 10;
	float factorCresterebeta = 10;

	glPushMatrix();
	for (int i = 1; i < 10; i++)
	{
		alfa = alfa + M_PI / factorCresterealfa;

		for (int j = 1; j < 10; j++)
		{
			deseneazaBlockIglu(pivotx + r * sin(alfa) * cos(beta), pivoty + r * sin(beta) * sin(alfa), pivotz + r * cos(alfa),
				pivotx + r * sin(alfa) * cos(beta + (2 * M_PI) / 7), pivoty + r * sin(beta + (2 * M_PI) / 7) * sin(alfa), pivotz + r * cos(alfa),
				pivotx + (r - width) * sin(alfa) * cos(beta + (2 * M_PI) / 7), pivoty + (r - width) * sin(beta + (2 * M_PI) / 7) * sin(alfa), pivotz + r * cos(alfa),
				pivotx + (r - width) * sin(alfa) * cos(beta), pivoty + (r - width) * sin(beta) * sin(alfa), pivotz + r * cos(alfa),

				pivotx + r * sin(alfa + M_PI / 12) * cos(beta), pivoty + r * sin(beta) * sin(alfa + M_PI / 12), pivotz + r * cos(alfa + M_PI / 12),
				pivotx + r * sin(alfa + M_PI / 12) * cos(beta + (2 * M_PI) / 7), pivoty + r * sin(beta + (2 * M_PI) / 7) * sin(alfa + M_PI / 12), pivotz + r * cos(alfa + M_PI / 12),
				pivotx + (r - width) * sin(alfa + M_PI / 12) * cos(beta + (2 * M_PI) / 7), pivoty + (r - width) * sin(beta + (2 * M_PI) / 7) * sin(alfa + M_PI / 12), pivotz + r * cos(alfa + M_PI / 12),
				pivotx + (r - width) * sin(alfa + M_PI / 12) * cos(beta), pivoty + (r - width) * sin(beta) * sin(alfa + M_PI / 12), pivotz + r * cos(alfa + M_PI / 12));
			beta = beta + (2 * M_PI) / factorCresterebeta;
			;

		}

	}
	*/
	
	//glColor3f(1,1,1);
	glBegin(GL_POINTS);
	for (int i = 0; i < 100; i++)
		glVertex3f(randomNrFum(-500, 500) , randomNrFum(-500, 500), randomNrFum(-500, 500));
	glEnd();
	gluCylinder(obj, 100, 100, 100, 20, 10);
	
	/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glColor3f(0, 0, 0);
	
	gluCylinder(obj, 101, 101, 101, 20, 10);
	*/
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glColor3f(1, 1, 1);

	glTranslatef(-5, 100, 10);
	auxSolidBox(10, 10, 20);
	glTranslatef(0, 0, 20);
	auxSolidBox(10, 10, 20);
	glTranslatef(0, 0, 20);
	auxSolidBox(10, 10, 20);
	glTranslatef(0, 0, 20);
	auxSolidBox(10, 10, 20);
	glTranslatef(0, 0, 20);
	auxSolidBox(10, 10, 20);
	



	glRotatef(90, 0, 0, 1);
	glTranslatef(-15, 50, -80);

	glRotatef(20, 0, 0, 1);

	auxSolidBox(10, 10, 20);
	glTranslatef(0, 0, 20);
	auxSolidBox(10, 10, 20);
	glTranslatef(0, 0, 20);
	auxSolidBox(10, 10, 20);
	glTranslatef(0, 0, 20);
	auxSolidBox(10, 10, 20);
	glTranslatef(0, 0, 20);
	auxSolidBox(10, 10, 20);


	
	
	glRotatef(-20, 0, 0, 1);
	glTranslatef(15, -50, 0);
	glRotatef(-90, 0, 0, 1);
	glTranslatef(5, -100, 0);
	gluSphere(obj, 99, 20, 20);
	/*
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glColor3f(0, 0, 0);
	gluSphere(obj, 100, 20, 20);
	*/
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	
	//glColor3f(1, 1, 1);

	glTranslatef(0, 0, 98);
	
	gluCylinder(obj, 10, 10, 10, 20, 1);
	glTranslatef(0, 0, 10);

	auxSolidBox(25, 25, 5);
	glPointSize(5); // dimensiunea pixelului 5
	//glColor3f(0.0, 0, 0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 100; i++)
		glVertex3f(smoke_x+ randomNrFum(0,10)+i*(-1* randomNrFum(-1, 1)), smoke_y + randomNrFum(0, 30), smoke_z + randomNrFum(0, 50)+ i);	
	glEnd();
	
	glTranslatef(0, 0,-105);
	//glColor3f(1, 1, 1);

	glTranslatef(-5, 95, 10);
	glTranslatef(-25, 0, 0);
	glRotatef(15, 0, 0, 1);

	auxSolidBox(60, 10, 10);
	
	glPopMatrix();
	
}



void CALLBACK stanga() //-- rotire totala stanga
{
	y -= 10;
}

void CALLBACK dreapta()//-- rotire totala dreapta
{
	y += 10;
}

void CALLBACK sus() //-- rotire inainte
{
	x += 10;

}

void CALLBACK jos()//--rotire inapoi
{
	x -= 10;
}



void CALLBACK stangaM() //-- rotire totala stanga
{
	zM += 10;
}

void CALLBACK dreaptaM()//-- rotire totala dreapta
{
	zM -= 10;
}

void CALLBACK fataM() //-- rotire inainte
{
	xM += 10;

}

void CALLBACK spateM()//--rotire inapoi
{
	xM -= 10;
}
void CALLBACK susM() //-- rotire inainte
{
	yM += 10;

}

void CALLBACK josM()//--rotire inapoi
{
	yM -= 10;
}

void CALLBACK animatieFum() {
	Sleep(75);
	display();

}
void CALLBACK moveLight() {
	spin = (spin + 30) % 360;
}
int main(int argc, char** argv)
{
	srand(time(0));
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB | AUX_DEPTH16);
	auxInitPosition(0, 0, 1024, 600);
	auxInitWindowA("Iglu");
	init();
	auxKeyFunc(AUX_4, stanga);
	auxKeyFunc(AUX_6, dreapta);
	auxKeyFunc(AUX_2, sus);
	auxKeyFunc(AUX_8, jos);
	auxKeyFunc(AUX_w, fataM);
	auxKeyFunc(AUX_s, spateM);
	auxKeyFunc(AUX_d, dreaptaM);
	auxKeyFunc(AUX_a, stangaM);
	auxKeyFunc(AUX_i, susM);
	auxKeyFunc(AUX_k, josM);
	auxKeyFunc(AUX_g, moveLight);

	auxReshapeFunc(myReshape);
	auxIdleFunc(animatieFum);
	auxMainLoop(display);
	return(0);
}
