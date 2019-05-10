//Semestre 2019 - 2
//*************************************************************//
//*************************************************************//
//************* Alumno (s): Cedillo N�jera Eric Rodrigo *******//
//*************				Calva Lorenzo Ivan Eduardo *******//
//*************	Proyecto Final **********//
//*************	Visual Studio 2017 ******//
//*************	Feria de Pueblo *********//
//*************************************************************//

//Teclas Especiales para activar la animacion
//K,k =>Para guardar la animacion
//L,l =>Para correr la animacion

#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "cmodel/CModel.h"	//PERMITE TEXTURAS EN 3D
#include "iostream"
#include "cstdlib"
#include <cstring>


using namespace std;
static GLuint ciudad_display_list;

float angVoodoo = 0.0;
float angCanoa = 0.0;

//keyframe

float movhombro = 0.0;
float anghom = 0.0;
float movpie = 0.0;

#define MAX_FRAMES 20  // Cuantos cuadros capturamos por segundo
int i_max_steps = 90;
int i_curr_steps = 0;

typedef struct _frame  // Debemos declarar la variable y otra que es su incremento
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ

	float transZ = -5.0f;
	float transX = 0.0f;
	float angleX = 0.0f;
	float angleY = 0.0f;
	int screenW = 0.0;
	int screenH = 0.0;
	float movhombro = 0.0;
	float movcodo = 0.0;
	float inchom = 0.0;
	float movpie = 0.0;
	float incpie = 0.0;


}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 20;			//introducir datos
bool play = false;  //Play en falso
int playIndex = 0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame = 0, time, timebase = 0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font = (int)GLUT_BITMAP_HELVETICA_18;



GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

CTexture text1;
CTexture t_pasto;
CTexture t_nubes;
CTexture t_pav;
CTexture t_ladrillo;
CTexture t_ct;
CTexture t_pelota;
CTexture t_madera;
CTexture t_metal;
CTexture t_carrito;
CTexture t_yeso;
CTexture t_entba;


CFiguras cubo;
CFiguras sky;

//END NEW//////////////////////////////////////////


CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;

CFiguras voodoo;
CFiguras medusa;

CModel asiento;
CModel arbol;
CModel kiosko;


GLuint createDL()
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL, GL_COMPILE);
	// call the function that contains 
	// the rendering commands

	// endList
	glEndList();

	return(ciudadDL);
}

void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	//Para construir la figura comentar esto
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	text1.LoadBMP("cielo.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	t_pasto.LoadTGA("pasto.tga");
	t_pasto.BuildGLTexture();
	t_pasto.ReleaseImage();

	t_nubes.LoadTGA("nube.tga");
	t_nubes.BuildGLTexture();
	t_nubes.ReleaseImage();

	t_pav.LoadTGA("pavimento.tga");
	t_pav.BuildGLTexture();
	t_pav.ReleaseImage();

	t_ladrillo.LoadTGA("tabique.tga");
	t_ladrillo.BuildGLTexture();
	t_ladrillo.ReleaseImage();

	t_ct.LoadTGA("ct.tga");
	t_ct.BuildGLTexture();
	t_ct.ReleaseImage();

	t_pelota.LoadTGA("pel.tga");
	t_pelota.BuildGLTexture();
	t_pelota.ReleaseImage();

	t_madera.LoadTGA("TEXTURAS/llama.tga");
	t_madera.BuildGLTexture();
	t_madera.ReleaseImage();

	t_metal.LoadTGA("metal.tga");
	t_metal.BuildGLTexture();
	t_metal.ReleaseImage();

	t_carrito.LoadTGA("frenteCarritoMedusa.tga");
	t_carrito.BuildGLTexture();
	t_carrito.ReleaseImage();

	t_yeso.LoadTGA("texba.tga");
	t_yeso.BuildGLTexture();
	t_yeso.ReleaseImage();

	t_entba.LoadTGA("banio.tga");
	t_entba.BuildGLTexture();
	t_entba.ReleaseImage();


	//3ds carga
	arbol._3dsLoad("3ds/firtree3.3ds");
	asiento._3dsLoad("3ds/gardenB.3ds");

	//END NEW//////////////////////////////

	objCamera.Position_Camera(0, 2.5f, 3, 0, 2.5f, 0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	//ciudad_display_list = createDL();

	///
	KeyFrame[0].movhombro = 0;
	KeyFrame[1].movhombro = -55;
	KeyFrame[2].movhombro = -55;
	KeyFrame[3].movhombro = -100;
	KeyFrame[4].movhombro = -55;

	KeyFrame[5].movpie = 0;
	KeyFrame[6].movpie = -25;
	KeyFrame[7].movpie = -40;
	KeyFrame[8].movpie = -25;
	//KeyFrame[].movhombro = -55;

}

void soporteMedusa(void) {
	glPushMatrix();

	//----------------1

	glPushMatrix();
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(0, 1.75, 0);
	glRotatef(45, 0, 0, 1);
	medusa.prisma(4.5, 0.5, 0.5, t_metal.GLindex);
	glRotatef(90, 0, 0, 1);
	medusa.prisma(4.5, 0.5, 0.5, t_metal.GLindex);
	glPopMatrix();

	medusa.prisma(4, 0.5, 0.5, t_metal.GLindex);
	glTranslatef(0, 3.5, 0);
	medusa.prisma(4, 0.5, 0.5, t_metal.GLindex);

	glTranslatef(1.75, -1.75, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	medusa.prisma(4, 0.5, 0.5, t_metal.GLindex);
	glPopMatrix();

	glTranslatef(-3.5, 0, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	medusa.prisma(4, 0.5, 0.5, t_metal.GLindex);
	glPopMatrix();

	glPopMatrix();

	//----------------2

	glPushMatrix();
	glTranslatef(0, 0, -3.5);
	glPushMatrix();
	glTranslatef(0, 1.75, 0);
	glRotatef(45, 0, 0, 1);
	medusa.prisma(4.5, 0.5, 0.5, t_metal.GLindex);
	glRotatef(90, 0, 0, 1);
	medusa.prisma(4.5, 0.5, 0.5, t_metal.GLindex);
	glPopMatrix();

	medusa.prisma(4, 0.5, 0.5, t_metal.GLindex);
	glTranslatef(0, 3.5, 0);
	medusa.prisma(4, 0.5, 0.5, t_metal.GLindex);

	glTranslatef(1.75, -1.75, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	medusa.prisma(4, 0.5, 0.5, t_metal.GLindex);
	glPopMatrix();

	glTranslatef(-3.5, 0, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	medusa.prisma(4, 0.5, 0.5, t_metal.GLindex);
	glPopMatrix();

	glPopMatrix();

	//-----------------3


	glPushMatrix();
	glTranslatef(-1.75, 0, -1.75);
	glRotatef(90, 0, 1, 0);

	glPushMatrix();
	glTranslatef(0, 1.75, 0);
	glRotatef(45, 0, 0, 1);
	medusa.prisma(4.5, 0.5, 0.5, t_metal.GLindex);
	glRotatef(90, 0, 0, 1);
	medusa.prisma(4.5, 0.5, 0.5, t_metal.GLindex);
	glPopMatrix();

	medusa.prisma(4, 0.5, 0.5, t_metal.GLindex);
	glTranslatef(0, 3.5, 0);
	medusa.prisma(4, 0.5, 0.5, t_metal.GLindex);

	glTranslatef(1.75, -1.75, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	medusa.prisma(4, 0.5, 0.5, t_metal.GLindex);
	glPopMatrix();

	glTranslatef(-3.5, 0, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	medusa.prisma(4, 0.5, 0.5, t_metal.GLindex);
	glPopMatrix();

	glPopMatrix();

	//-------------4

	glPushMatrix();

	glTranslatef(1.75, 0, -1.75);
	glRotatef(90, 0, 1, 0);

	glPushMatrix();
	glTranslatef(0, 1.75, 0);
	glRotatef(45, 0, 0, 1);
	medusa.prisma(4.5, 0.5, 0.5, t_metal.GLindex);
	glRotatef(90, 0, 0, 1);
	medusa.prisma(4.5, 0.5, 0.5, t_metal.GLindex);
	glPopMatrix();

	medusa.prisma(4, 0.5, 0.5, t_metal.GLindex);
	glTranslatef(0, 3.5, 0);
	medusa.prisma(4, 0.5, 0.5, t_metal.GLindex);

	glTranslatef(1.75, -1.75, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	medusa.prisma(4, 0.5, 0.5, t_metal.GLindex);
	glPopMatrix();

	glTranslatef(-3.5, 0, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	medusa.prisma(4, 0.5, 0.5, t_metal.GLindex);
	glPopMatrix();

	glPopMatrix();



	glPopMatrix();
}

void translateMedusa(float x, float y, float z) {
	glTranslatef(x*4, y*4, z*4);
}

void columnasMedusa(int length) {

	glPushMatrix();
	soporteMedusa();
	for (size_t i = 0; i < length; i++)
	{
		glPushMatrix();
		glTranslated(0, i*4, 0);
		soporteMedusa();
		glPopMatrix();
	
	}

	glPopMatrix();
}

void estructuraMedusaTotal(void) {
	
	//Push General de la funci�n
	glPushMatrix();
	
	columnasMedusa(5);
	translateMedusa(1, 0, 0);
	columnasMedusa(5);
	translateMedusa(2, 0, 0);
	columnasMedusa(5);
	translateMedusa(2, 0, 0);
	columnasMedusa(6);

	//Primera curva

	translateMedusa(1, 0, -1);
	columnasMedusa(7);
	translateMedusa(1, 0, -1);
	columnasMedusa(8);

	translateMedusa(0, 0, -2);
	columnasMedusa(9);
	translateMedusa(0, 0, -2);
	columnasMedusa(10);
	translateMedusa(0, 0, -2);
	columnasMedusa(11);
	translateMedusa(0, 0, -2);
	columnasMedusa(12);
	translateMedusa(0, 0, -2);
	columnasMedusa(13);
	translateMedusa(0, 0, -2);
	columnasMedusa(14);
	translateMedusa(0, 0, -2);
	columnasMedusa(15);
	translateMedusa(0, 0, -2);
	columnasMedusa(16);

	//Segunda Curva

	translateMedusa(-1, 0, -1);
	columnasMedusa(17);
	translateMedusa(-1, 0, -1);
	columnasMedusa(17);
	translateMedusa(-1, 0, 0);
	columnasMedusa(17);
	translateMedusa(-1, 0, 0);
	columnasMedusa(17);
	translateMedusa(-1, 0, 1);
	columnasMedusa(17);

	translateMedusa(0, 0, 2);
	columnasMedusa(16);
	translateMedusa(0, 0, 2);
	columnasMedusa(14);
	translateMedusa(0, 0, 2);
	columnasMedusa(13);
	translateMedusa(0, 0, 2);
	columnasMedusa(12);
	translateMedusa(0, 0, 2);
	columnasMedusa(10);
	translateMedusa(0, 0, 2);
	columnasMedusa(9);

	//Tercera Curva
	translateMedusa(-1, 0, 1);
	columnasMedusa(7);
	translateMedusa(-1, 0, 1);
	columnasMedusa(7);
	translateMedusa(-1, 0, 0);
	columnasMedusa(7);
	translateMedusa(-1, 0, 0);
	columnasMedusa(7);//
	translateMedusa(-1, 0, -1);
	columnasMedusa(7);
	translateMedusa(-1, 0, -1);
	columnasMedusa(7);

	translateMedusa(0, 0, -2);
	columnasMedusa(6);
	translateMedusa(0, 0, -2);
	columnasMedusa(5);
	translateMedusa(0, 0, -2);
	columnasMedusa(4);
	translateMedusa(0, 0, -2);
	columnasMedusa(3);
	translateMedusa(0, 0, -2);
	columnasMedusa(3);
	translateMedusa(0, 0, -2);
	columnasMedusa(3);
	translateMedusa(0, 0, -2);
	columnasMedusa(3);

	//Cuarta Curva
	translateMedusa(-1, 0, -1);
	columnasMedusa(4);
	translateMedusa(-1, 0, -1);
	columnasMedusa(5);
	translateMedusa(-1, 0, 0);
	columnasMedusa(7);
	translateMedusa(-1, 0, 0);
	columnasMedusa(9);
	translateMedusa(-1, 0, 1);
	columnasMedusa(11);
	translateMedusa(-1, 0, 1);
	columnasMedusa(13);

	translateMedusa(0, 0, 2);
	columnasMedusa(15);
	translateMedusa(0, 0, 2);
	columnasMedusa(17);
	translateMedusa(0, 0, 2);
	columnasMedusa(19);
	translateMedusa(0, 0, 2);
	columnasMedusa(19);
	translateMedusa(0, 0, 2);
	columnasMedusa(17);
	translateMedusa(0, 0, 2);
	columnasMedusa(15);
	translateMedusa(0, 0, 2);
	columnasMedusa(13);
	translateMedusa(0, 0, 2);
	columnasMedusa(11);
	translateMedusa(0, 0, 2);
	columnasMedusa(9);

	//Quinta curva
	translateMedusa(-1, 0, 1);
	columnasMedusa(7);
	translateMedusa(-1, 0, 1);
	columnasMedusa(7);
	translateMedusa(-1, 0, 0);
	columnasMedusa(6);
	translateMedusa(-1, 0, -1);
	columnasMedusa(5);
	translateMedusa(-1, 0, -1);
	columnasMedusa(4);

	translateMedusa(0, 0, -2);
	columnasMedusa(4);
	translateMedusa(0, 0, -2);
	columnasMedusa(5);
	translateMedusa(0, 0, -2);
	columnasMedusa(6);
	translateMedusa(0, 0, -2);
	columnasMedusa(7);
	translateMedusa(0, 0, -2);
	columnasMedusa(8);
	translateMedusa(0, 0, -2);
	columnasMedusa(9);
	translateMedusa(0, 0, -2);
	columnasMedusa(10);
	translateMedusa(0, 0, -2);
	columnasMedusa(11);
	translateMedusa(0, 0, -2);
	columnasMedusa(12);

	//SextaCurva
	translateMedusa(-1, 0, -2);
	columnasMedusa(13);
	translateMedusa(-2, 0, -2);
	columnasMedusa(13);
	translateMedusa(-2, 0, 0);
	columnasMedusa(13);
	translateMedusa(-2, 0, 0);
	columnasMedusa(13);
	translateMedusa(-2, 0, 2);
	columnasMedusa(13);
	translateMedusa(-1, 0, 2);
	columnasMedusa(13);

	translateMedusa(0, 0, 2);
	columnasMedusa(12);
	translateMedusa(0, 0, 2);
	columnasMedusa(10);
	translateMedusa(0, 0, 2);
	columnasMedusa(9);
	translateMedusa(0, 0, 2);
	columnasMedusa(8);
	translateMedusa(0, 0, 2);
	columnasMedusa(7);
	translateMedusa(0, 0, 2);
	columnasMedusa(6);
	translateMedusa(0, 0, 2);
	columnasMedusa(5);
	translateMedusa(0, 0, 2);
	columnasMedusa(5);
	translateMedusa(0, 0, 2);
	columnasMedusa(5);
	translateMedusa(0, 0, 2);
	columnasMedusa(5);

	//Septima Curva
	translateMedusa(1, 0, 2);
	columnasMedusa(5);
	translateMedusa(2, 0, 1);
	columnasMedusa(5);
	translateMedusa(2, 0, 1);
	columnasMedusa(5);
	translateMedusa(2, 0, 1);
	columnasMedusa(5);
	translateMedusa(2, 0, 1);
	columnasMedusa(5);
	translateMedusa(2, 0, 0);
	columnasMedusa(5);
	translateMedusa(2, 0, -1);
	columnasMedusa(5);
	translateMedusa(1, 0, -1);
	columnasMedusa(5);
	translateMedusa(1, 0, -1);
	columnasMedusa(5);
	translateMedusa(1, 0, -1);
	columnasMedusa(5);
	translateMedusa(1, 0, -1);
	columnasMedusa(5);

	translateMedusa(2, 0, 0);
	columnasMedusa(5);
	translateMedusa(2, 0, 0);
	columnasMedusa(5);
	translateMedusa(2, 0, 0);
	columnasMedusa(5);

	//Fin del circuito Medusa

	//Pop General de la funci�n
	glPopMatrix();
}


void carroMedusa(void) {
	glPushMatrix();
	//Carro Medusa
	glColor3f(1, 1, 1);
	medusa.prisma(4, 0.5, 3, t_metal.GLindex);
	glTranslatef(1.25, 1.25, 0);
	medusa.prisma(1.5, 2, 3, t_madera.GLindex);
	glTranslatef(-1, -0.25, 0);
	glColor3f(1, 0, 0);
	medusa.prisma(0.5, 1.5, 2, NULL);
	glTranslatef(-0.625, -0.5, 0);
	medusa.prisma(0.75, 0.5, 2, NULL);
	glColor3f(1, 1, 1);
	glTranslatef(-1.375, 0, 0);
	medusa.prisma(0.5, 1.5, 3, t_carrito.GLindex);

	glPopMatrix();

}

void arregloCarrosMedusa(void) {
	for (size_t i = 0; i < 8; i++)
	{	
		carroMedusa();
		glPushMatrix();
		glTranslatef(i * 4, 0, 0);
		carroMedusa();
		glPopMatrix();

	}
}

void Voodoo(void) {
	//Push de la estructrura
	glPushMatrix();

	//Base Voodoo
	//Izquierda
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(-2.25, -2, 0);
	glDisable(GL_LIGHTING);
	voodoo.prisma(2, 13, 5, t_madera.GLindex);
	glTranslatef(1.5, 6.5, 0);
	glEnable(GL_LIGHTING);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	voodoo.cilindro(2.5, 3, 20, t_metal.GLindex);
	glPopMatrix();
	glPopMatrix();

	//Derecha
	glPushMatrix();
	glTranslatef(28.75, -2, 0);
	voodoo.prisma(2, 13, 5, t_madera.GLindex);
	glTranslatef(1.5, 6.5, 0);
	
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	voodoo.cilindro(2.5, 3, 20, t_madera.GLindex);
	glPopMatrix();
	glPopMatrix();

	//Barra Movimiento Principal Voodoo
	
	glTranslatef(0, 4.5, 0);
	glRotatef(-angVoodoo, 1, 0, 0);//Rotate de animaci�n del juego
	glPushMatrix();
	glTranslated(25.75, -1, 0);
	glRotatef(90, 0, 0, 1);
	voodoo.cilindro(1, 25, 20, t_metal.GLindex);
	glPopMatrix();


	//Brazo Izquierdo del Voodoo
	glTranslated(0, -5, 0);
	glPushMatrix();
	voodoo.prisma(1.5, 10, 4, t_madera.GLindex);
	glTranslated(0.75, -5, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	voodoo.cilindro(2, 1.5, 20, t_madera.GLindex);
	glPopMatrix();
	glTranslatef(-0.75, 15, 0);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	voodoo.prismaTriangular(10, 4, 1.5, t_madera.GLindex);
	glPopMatrix();
	glTranslatef(0.75, 5, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	voodoo.cilindro(2.5, 1.5, 20, t_madera.GLindex);
	glPopMatrix();

	glPopMatrix();
	glTranslatef(13.25, -6, 0);


	//Canoa del Voodoo.
	glPushMatrix();
	glRotatef(angCanoa, 1, 0, 0);//Rotate de animaci�n del juego
	voodoo.prisma(23, 1, 5, NULL);
	
	voodoo.prisma(23, 1, 5, t_madera.GLindex);
	glTranslatef(0, -1, 0);

	voodoo.prisma(21, 1, 3, t_madera.GLindex);
	glTranslatef(12.5, 1, 0);

	//cilindro canoa
	glColor3f(1, 0, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	voodoo.cilindro(0.5, 1, 20, t_metal.GLindex);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-24, 0, 0);
	glRotatef(90, 0, 0, 1);
	voodoo.cilindro(0.5, 1, 20, t_metal.GLindex);
	glPopMatrix();
	glPopMatrix();

	glTranslatef(13.25, 6, 0);
	glColor3f(1, 1, 1);
	//Brazo Derecho del Voodoo
	glPushMatrix();
	voodoo.prisma(1.5, 10, 4, t_madera.GLindex);
	glTranslated(0.75, -5, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	voodoo.cilindro(2, 1.5, 20, t_madera.GLindex);
	glPopMatrix();
	glTranslatef(-0.75, 15, 0);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	voodoo.prismaTriangular(10, 4, 1.5, t_madera.GLindex);
	glPopMatrix();
	glTranslatef(0.75, 5, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	voodoo.cilindro(2.5, 1.5, 20, t_madera.GLindex);
	glPopMatrix();

	glPopMatrix();

	glColor3f(1, 1, 1);

	glPopMatrix();
}

void humanide(void) {

	//cabeza
	glPushMatrix();
	glScalef(4, 4, 4);
	glColor3f(1, 1, 1);
	fig4.esfera(0.6, 20, 20, 0);
	glPopMatrix();

	//ojos
	glPushMatrix();
	glTranslatef(-0.5, 0, 2.5);
	glScalef(.52, .52, .1);
	glColor3f(0, .1, 1);
	fig3.prisma3(0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0, 2.5);
	glScalef(.52, .52, .1);
	glColor3f(0, .1, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -3, 0);

	//cuello
	glPushMatrix();
	glScalef(3, 2, 3);
	glColor3f(1, 0, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -6, 0);
	//torso
	glPushMatrix();
	glScalef(10, 10, 3);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//pierna izquierda
	//muslo
	glTranslatef(2.5, -7.5, 0);

	glPushMatrix();
	glScalef(2, 5, 3);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -3, 0);
	//rodilla
	glPushMatrix();
	glScalef(2, 1, 3);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -3, 0);

	//espinilla
	glPushMatrix();
	glScalef(2, 5, 3);
	glColor3f(1, 0.5, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -2.75, 0);

	//tobillo
	glPushMatrix();
	glScalef(2, 0.5, 3);
	glColor3f(1, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -1.25, 0);
	//pie
	glPushMatrix();
	glScalef(2, 2, 3);
	glColor3f(0.5, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glPopMatrix();

	glTranslatef(3, 21.5, 0);

	//brazo izquierdo
	//Hombro1
	glPushMatrix();
	/*glPushMatrix();
	glScalef(1, 2, 2);
	glColor3f(1, 1, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();
	*/
	//hombro2
	glPushMatrix();
	glRotatef(movhombro, 0, 0, 1);
	glPushMatrix();
	glScalef(1, 2, 2);
	glColor3f(1, 1, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();


	//Bicep
	glPushMatrix();
	glTranslatef(2, 0, 0);
	glScalef(3, 2, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Codo
	//glRotatef(angCodo, 0, 1, 0);
	glPushMatrix();
	glTranslatef(3.75, 0, 0);
	glScalef(0.5, 2, 2);
	glColor3f(1, 0, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Antebrazo
	glPushMatrix();
	glTranslatef(6, 0, 0);
	glScalef(4, 2, 2);
	glColor3f(0, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Mu�eca
	//glRotatef(angMuni, 0, 1, 0);
	glPushMatrix();
	glTranslatef(8.25, 0, 0);
	glScalef(0.5, 2, 2);
	glColor3f(1, 1, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Mano
	glPushMatrix();
	glTranslatef(9.5, 0, 0);
	glScalef(2, 2, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo pulgar
	glPushMatrix();
	//glRotatef(angDedP, 1, 0, 0);
	glTranslatef(9.75, 1.25, 0);
	glScalef(.3, .5, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angDedP, 1, 0, 0);
	glTranslatef(9.75, 1.75, 0);
	glScalef(.3, .5, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo indice
	glPushMatrix();
	//glRotatef(angDedI, 0, 1, 0);
	glTranslatef(10.75, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angDedI, 0, 1, 0);
	glTranslatef(11.25, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angDedI, 0, 1, 0);
	glTranslatef(11.75, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo medio

	glPushMatrix();
	//glRotatef(angMed, 0, 1, 0);
	glTranslatef(10.75, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angMed, 0, 1, 0);
	glTranslatef(11.25, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angMed, 0, 1, 0);
	glTranslatef(11.75, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo anular
	glPushMatrix();
	//glRotatef(angAn, 0, 1, 0);
	glTranslatef(10.75, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angAn, 0, 1, 0);
	glTranslatef(11.25, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angAn, 0, 1, 0);
	glTranslatef(11.75, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();
	//me�ique
	glPushMatrix();
	//glRotatef(angMe, 0, 1, 0);
	glTranslatef(10.75, -.75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angMe, 0, 1, 0);
	glTranslatef(11.25, -.75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPopMatrix();


	//Brazo derecha
	//Hombro
	glPushMatrix();
	glTranslatef(-11, 0, 0);
	glRotatef(-movhombro, 0, 0, 1);
	glPushMatrix();
	glScalef(1, 2, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Bicep
	glPushMatrix();
	glTranslatef(-2, 0, 0);
	glScalef(3, 2, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Codo
	//glRotatef(-angCodo, 0, 1, 0);
	glPushMatrix();
	glTranslatef(-3.75, 0, 0);
	glScalef(0.5, 2, 2);
	glColor3f(1, 0, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Antebrazo
	glPushMatrix();
	glTranslatef(-6, 0, 0);
	glScalef(4, 2, 2);
	glColor3f(0, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Mu�eca
	//glRotatef(-angMuni, 0, 1, 0);
	glPushMatrix();
	glTranslatef(-8.25, 0, 0);
	glScalef(0.5, 2, 2);
	glColor3f(1, 1, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Mano
	glPushMatrix();
	glTranslatef(-9.5, 0, 0);
	glScalef(2, 2, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo pulgar
	glPushMatrix();
	//glRotatef(-angDedP, 1, 0, 0);
	glTranslatef(-9.75, 1.25, 0);
	glScalef(.3, .5, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angDedP, 1, 0, 0);
	glTranslatef(-9.75, 1.75, 0);
	glScalef(.3, .5, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo indice
	glPushMatrix();
	//glRotatef(-angDedI, 0, 1, 0);
	glTranslatef(-10.75, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angDedI, 0, 1, 0);
	glTranslatef(-11.25, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angDedI, 0, 1, 0);
	glTranslatef(-11.75, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo medio

	glPushMatrix();
	//glRotatef(-angMed, 0, 1, 0);
	glTranslatef(-10.75, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angMed, 0, 1, 0);
	glTranslatef(-11.25, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angMed, 0, 1, 0);
	glTranslatef(-11.75, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo anular
	glPushMatrix();
	//glRotatef(-angAn, 0, 1, 0);
	glTranslatef(-10.75, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angAn, 0, 1, 0);
	glTranslatef(-11.25, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angAn, 0, 1, 0);
	glTranslatef(-11.75, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();
	//me�ique
	glPushMatrix();
	//glRotatef(-angMe, 0, 1, 0);
	glTranslatef(-10.75, -.75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angMe, 0, 1, 0);
	glTranslatef(-11.25, -.75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPopMatrix();


	//pie derecho
	//muslo

	glTranslatef(-7.5, -11.5, 0);
	glPushMatrix();
	glScalef(2, 5, 3);
	glColor3f(0.6, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();
	glTranslatef(0, -3, 0);
	//rodilla
	glPushMatrix();
	glScalef(2, 1, 3);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -3, 0);

	//espinilla
	glPushMatrix();
	glScalef(2, 5, 3);
	glColor3f(1, 0.5, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -2.75, 0);

	//tobillo
	glPushMatrix();
	glScalef(2, 0.5, 3);
	glColor3f(1, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -1.25, 0);
	//pie
	glPushMatrix();
	glScalef(2, 2, 3);
	glColor3f(0.5, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();



}

void ninio(void) {

	//cabeza
	glPushMatrix();
	glScalef(4, 4, 4);
	glColor3f(1, 1, 1);
	fig4.esfera(0.6, 20, 20, 0);
	glPopMatrix();

	//ojos
	glPushMatrix();
	glTranslatef(-0.5, 0, 2.5);
	glScalef(.52, .52, .1);
	glColor3f(0, .1, 1);
	fig3.prisma3(0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0, 2.5);
	glScalef(.52, .52, .1);
	glColor3f(0, .1, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -3, 0);

	//cuello
	glPushMatrix();
	glScalef(3, 2, 3);
	glColor3f(1, 0, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();


	//pasto
	glTranslatef(0, -6, 0);
	//torso
	glPushMatrix();
	glScalef(10, 10, 3);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//pierna izquierda
	//muslo
	glTranslatef(2.5, -7.5, 0);

	glPushMatrix();

	glScalef(2, 5, 3);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -3, 0);
	//rodilla
	glPushMatrix();
	glScalef(2, 1, 3);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -3, 0);

	//espinilla
	glPushMatrix();
	glScalef(2, 5, 3);
	glColor3f(1, 0.5, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -2.75, 0);

	//tobillo
	glPushMatrix();
	glScalef(2, 0.5, 3);
	glColor3f(1, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -1.25, 0);
	//pie
	glPushMatrix();
	glScalef(2, 2, 3);
	glColor3f(0.5, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glPopMatrix();

	glTranslatef(3, 21.5, 0);

	//brazo izquierdo
	//Hombro1

	glPushMatrix();
	glRotatef(-75, 0, 0, 1);
	glPushMatrix();
	//glRotatef(75,0,1,0);
	glScalef(1, 2, 2);
	glColor3f(1, 1, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();


	//Bicep
	glPushMatrix();
	glTranslatef(2, 0, 0);
	glScalef(3, 2, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Codo
	//glRotatef(angCodo, 0, 1, 0);
	glPushMatrix();
	glTranslatef(3.75, 0, 0);
	glScalef(0.5, 2, 2);
	glColor3f(1, 0, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Antebrazo
	glPushMatrix();
	glTranslatef(6, 0, 0);
	glScalef(4, 2, 2);
	glColor3f(0, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Mu�eca
	//glRotatef(angMuni, 0, 1, 0);
	glPushMatrix();
	glTranslatef(8.25, 0, 0);
	glScalef(0.5, 2, 2);
	glColor3f(1, 1, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Mano
	glPushMatrix();
	glTranslatef(9.5, 0, 0);
	glScalef(2, 2, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo pulgar
	glPushMatrix();
	//glRotatef(angDedP, 1, 0, 0);
	glTranslatef(9.75, 1.25, 0);
	glScalef(.3, .5, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angDedP, 1, 0, 0);
	glTranslatef(9.75, 1.75, 0);
	glScalef(.3, .5, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo indice
	glPushMatrix();
	//glRotatef(angDedI, 0, 1, 0);
	glTranslatef(10.75, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angDedI, 0, 1, 0);
	glTranslatef(11.25, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angDedI, 0, 1, 0);
	glTranslatef(11.75, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo medio

	glPushMatrix();
	//glRotatef(angMed, 0, 1, 0);
	glTranslatef(10.75, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angMed, 0, 1, 0);
	glTranslatef(11.25, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angMed, 0, 1, 0);
	glTranslatef(11.75, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo anular
	glPushMatrix();
	//glRotatef(angAn, 0, 1, 0);
	glTranslatef(10.75, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angAn, 0, 1, 0);
	glTranslatef(11.25, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angAn, 0, 1, 0);
	glTranslatef(11.75, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();
	//me�ique
	glPushMatrix();
	//glRotatef(angMe, 0, 1, 0);
	glTranslatef(10.75, -.75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angMe, 0, 1, 0);
	glTranslatef(11.25, -.75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPopMatrix();


	//Brazo derecha
	//Hombro
	glPushMatrix();
	glTranslatef(-11, 0, 0);
	glRotatef(-75, 0, 0, 1);
	glPushMatrix();
	glScalef(1, 2, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Bicep
	glPushMatrix();
	glTranslatef(-2, 0, 0);
	glScalef(3, 2, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Codo
	//glRotatef(-angCodo, 0, 1, 0);
	glPushMatrix();
	glTranslatef(-3.75, 0, 0);
	glScalef(0.5, 2, 2);
	glColor3f(1, 0, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Antebrazo
	glPushMatrix();
	glTranslatef(-6, 0, 0);
	glScalef(4, 2, 2);
	glColor3f(0, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Mu�eca
	//glRotatef(-angMuni, 0, 1, 0);
	glPushMatrix();
	glTranslatef(-8.25, 0, 0);
	glScalef(0.5, 2, 2);
	glColor3f(1, 1, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Mano
	glPushMatrix();
	glTranslatef(-9.5, 0, 0);
	glScalef(2, 2, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo pulgar
	glPushMatrix();
	//glRotatef(-angDedP, 1, 0, 0);
	glTranslatef(-9.75, 1.25, 0);
	glScalef(.3, .5, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angDedP, 1, 0, 0);
	glTranslatef(-9.75, 1.75, 0);
	glScalef(.3, .5, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo indice
	glPushMatrix();
	//glRotatef(-angDedI, 0, 1, 0);
	glTranslatef(-10.75, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angDedI, 0, 1, 0);
	glTranslatef(-11.25, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angDedI, 0, 1, 0);
	glTranslatef(-11.75, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo medio

	glPushMatrix();
	//glRotatef(-angMed, 0, 1, 0);
	glTranslatef(-10.75, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angMed, 0, 1, 0);
	glTranslatef(-11.25, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angMed, 0, 1, 0);
	glTranslatef(-11.75, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo anular
	glPushMatrix();
	//glRotatef(-angAn, 0, 1, 0);
	glTranslatef(-10.75, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angAn, 0, 1, 0);
	glTranslatef(-11.25, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angAn, 0, 1, 0);
	glTranslatef(-11.75, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();
	//me�ique
	glPushMatrix();
	//glRotatef(-angMe, 0, 1, 0);
	glTranslatef(-10.75, -.75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angMe, 0, 1, 0);
	glTranslatef(-11.25, -.75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPopMatrix();


	//pie derecho
	//muslo 
	glPushMatrix();
	glPushMatrix();
	glTranslatef(-7.5, -11.5, 0);
	glRotatef(movpie, 1, 0, 0);
	glPushMatrix();
	glScalef(2, 5, 3);
	glColor3f(0.6, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();
	glTranslatef(0, -3, 0);
	//rodilla
	glPushMatrix();
	glScalef(2, 1, 3);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -3, 0);

	//espinilla
	glPushMatrix();
	glScalef(2, 5, 3);
	glColor3f(1, 0.5, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -2.75, 0);

	//tobillo
	glPushMatrix();
	glScalef(2, 0.5, 3);
	glColor3f(1, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -1.25, 0);
	//pie
	glPushMatrix();
	glScalef(2, 2, 3);
	glColor3f(0.5, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}

void banio(void) {

	glPushMatrix();
	//glTranslatef(23, -30, 45);
	glColor3f(1, 1, 1);
	glScalef(5, 5, 5);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glScalef(5, 5, 5);
	fig3.prisma2(t_yeso.GLindex, t_yeso.GLindex);
	glPopMatrix();
	//
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-2.5, 0, 0);
	glScalef(.1, 5, 5);
	fig3.prisma3(t_entba.GLindex, t_entba.GLindex);
	glPopMatrix();
	glPopMatrix();


}

void pelota(void) {
	glColor3f(1,1,1);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	fig6.esfera(2, 10, 10, t_pelota.GLindex);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);


}



void pintaTexto(float x, float y, float z, void *font, char *string)
{

	char *c;     //Almacena los caracteres a escribir
	glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
							//glWindowPos2i(150,100);
	for (c = string; *c != '\0'; c++) //Condicion de fin de cadena
	{
		glutBitmapCharacter(font, *c); //imprime
	}
}

void display(void)   // Creamos la funcion donde se dibuja
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	

	glPushMatrix();
	glRotatef(g_lookupdown, 1.0f, 0, 0);

	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);


	glPushMatrix();
	glPushMatrix(); //Creamos cielo
	glDisable(GL_LIGHTING);
	glTranslatef(0, 60, 0);
	fig1.skybox(200.0, 200.0, 200.0, text1.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//pasto
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(0, -40, 0.0);
	glScalef(200, .1, 200);
	fig3.prisma2(t_pasto.GLindex, t_pasto.GLindex);
	glPopMatrix();

	//nubes

	glPushMatrix();
	glTranslatef(0, 160, 0.0);
	glScalef(200, .1, 200);
	fig3.prisma2(t_nubes.GLindex, t_nubes.GLindex);
	glPopMatrix();

	//tienda
	glPushMatrix();
	glTranslatef(23, -30, 45);
	glScalef(5, 5, 5);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glScalef(5, 5, 5);
	fig3.prisma2(t_ladrillo.GLindex, t_ladrillo.GLindex);
	glPopMatrix();

	//cara de tienda
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-2.5, 0, 0);
	glScalef(.1, 5, 5);
	fig3.prisma3(t_ct.GLindex, t_ct.GLindex);
	glPopMatrix();
	glPopMatrix();
	// ba�o
	glPushMatrix();
	glTranslatef(-15,-30,45);
	glRotatef(180, 0, 1, 0);
	glScalef(0.5,0.5,0.5);
	banio();
	glPopMatrix();

	//piso
	glPushMatrix();
	glTranslatef(0, -39.9, 0.0);
	glScalef(20, .1, 200);
	fig5.prisma3(t_pav.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	
	//3ds
	//arboles
	glColor3f(0, 1, 1);
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-20, -39.9, 10);
	glScalef(5, 5, 5);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(45, -39.9, 15);
	glScalef(5, 5, 5);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -39.9, -75);
	glScalef(5, 5, 5);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glColor3f(1, 1, 1);

	//bancos
	glPushMatrix();
	glTranslatef(20, -39.9, -60);
	glRotatef(270, 0, 1, 0);
	glScalef(.03, .03, .03);
	asiento.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20, -39.9, 68);
	glRotatef(90, 0, 1, 0);
	glScalef(.03, .03, .03);
	asiento.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glEnable(GL_COLOR_MATERIAL);

	//humanoide
	glPushMatrix();
	glTranslatef(0, -28, 0);
	glScalef(.4, .4, .4);
	humanide();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3, -20, 5);
	//fig5.esfera(2,12,12,0);
	pelota();
	glPopMatrix();
	//ni�o
	glPushMatrix();
	glTranslatef(0, -10, 45);
	glRotatef(180, 0, 1, 0);
	glScalef(.6, .6, .6);
	ninio();
	glPopMatrix();

	glEnable(GL_LIGHTING);
	//medusa
	glPushMatrix();
	glTranslatef(-90, -20, -50);
	//glRotatef(90, 0, 1, 0);
	glScalef(1.5,1.5,1.5);
	glPushMatrix();
	glTranslatef(4, 20, -1.75);
	glRotatef(180,0,1,0);
	arregloCarrosMedusa();
	glPopMatrix();
	estructuraMedusaTotal();
	glPopMatrix();
	//voodoo
	glPushMatrix();
	glTranslatef(35,-26.5,-45);
	glRotatef(270, 0, 1, 0);
	glScalef(1.5,1.5,1.5);
	Voodoo();
	glPopMatrix();





	glColor3f(1.0, 1.0, 1.0);

	glPopMatrix();
	
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 0.0, 0.0);
	pintaTexto(-11, 12.0, -14.0, (void *)font, "Proyecto Final");
	pintaTexto(-11, 10.0, -14.0, (void *)font, "Feria de Pueblo");
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	
	glutSwapBuffers();

}

void animacion()
{
	angCanoa = 0;
	angVoodoo++;
	

	fig3.text_izq -= 0.01;
	fig3.text_der -= 0.01;
	if (fig3.text_izq<-1)
		fig3.text_izq = 0;
	if (fig3.text_der<0)
		fig3.text_der = 1;

	//Movimiento del monito
	if (play)
	{

		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex>FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation

								  //Interpolaciones incremento.
								  //el incremento es la distancia entre dos cuadros, el 2 - 1 y se divide entre el 90(i_max_steps)   Se hace la interpolacion


				KeyFrame[playIndex].inchom = (KeyFrame[playIndex + 1].movhombro - KeyFrame[playIndex].movhombro) / i_max_steps;
				KeyFrame[playIndex].incpie = (KeyFrame[playIndex + 1].movpie - KeyFrame[playIndex].movpie) / i_max_steps;

			}
		}
		else
		{	//Draw information


			movhombro += KeyFrame[playIndex].inchom;
			movpie += KeyFrame[playIndex].incpie;


			i_curr_steps++;
		}

	}

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(s, "FPS:%4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}

	glutPostRedisplay();
}

void animacion2()
{
fig3.text_izq -= 0.01;
fig3.text_der -= 0.01;
if (fig3.text_izq<-1)
fig3.text_izq = 0;
if (fig3.text_der<0)
fig3.text_der = 1;

//Movimiento del monito
if (play)
{

if (i_curr_steps >= i_max_steps) //end of animation between frames?
{
playIndex++;
if (playIndex>FrameIndex - 2)	//end of total animation?
{
printf("termina anim\n");
playIndex = 0;
play = false;
}
else //Next frame interpolations
{
i_curr_steps = 0; //Reset counter
//Interpolation

//Interpolaciones incremento.
//el incremento es la distancia entre dos cuadros, el 2 - 1 y se divide entre el 90(i_max_steps)   Se hace la interpolacion



KeyFrame[playIndex].incpie = (KeyFrame[playIndex + 1].movpie - KeyFrame[playIndex].movpie) / i_max_steps;

}
}
else
{	//Draw information



movpie += KeyFrame[playIndex].incpie;


i_curr_steps++;
}

}

frame++;
time = glutGet(GLUT_ELAPSED_TIME);
if (time - timebase > 1000) {
sprintf(s, "FPS:%4.2f", frame*1000.0 / (time - timebase));
timebase = time;
frame = 0;
}

glutPostRedisplay();
}


void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 300.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {

	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.2);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.2));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
		break;

	case 'M':
	case 'm':
		if (play == false && (FrameIndex>1))
		{

			movhombro = KeyFrame[0].movhombro;


			//First Interpolation


			KeyFrame[playIndex].inchom = (KeyFrame[playIndex + 1].movhombro - KeyFrame[playIndex].movhombro) / i_max_steps;


			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;
	case 'N':
	case 'n':
		if (play == false && (FrameIndex>1))
		{

			movpie = KeyFrame[4].movpie;


			//First Interpolation


			KeyFrame[playIndex].incpie = (KeyFrame[playIndex + 4].movpie - KeyFrame[playIndex].movpie) / i_max_steps;


			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;


		//break;

	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}

	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(CAMERASPEED);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)   // Main Function
{
	PlaySound(TEXT("WAV/MusicaDeFondo.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(500, 500);	// Tama�o de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Proyecto Final - Lab CG"); // Nombre de la Ventana
							   //glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut funci�n de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut funci�n en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut funci�n de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);


	glutMainLoop();          // 

	return 0;
}