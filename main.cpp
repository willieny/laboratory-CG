#include <GL/glut.h>
#include <math.h>
#include "bibutil.h"
#include "myutil.h"
#include <stdio.h>

using namespace std;

// Variaveis para controle da projecao
GLfloat fAspect;
GLfloat ang_cam = 60;

// Variaveis para controle da porta
#define ANGLE_DOOR_MAX 90
GLfloat x_trans_angle = 0.430,
		angle_door = 0;

// Variaveis para controle da janela
#define ANGLEE_WINDOW_MAX -180
#define ANGLED_WINDOW_MAX 180
GLfloat xE_trans_angle = 0.430,
		xD_trans_angle = -0.430,
		angleE_window = 0,
		angleD_window = 0;

// Variaveis para controle da hélice
GLfloat angulo;
GLfloat sentido = 1;

// Variaveis para controle do mouse
#define SENS_ROT 5.0
#define SENS_OBS 10.0

// Objetos
OBJ *plano,
	*mesa,
	*porta,
	*janela,
	*lamp,
	*monitor,
	*teclado,
	*mouse,
	*cadeira,
	*interruptor,
	*lousa,
	*lixeira,
	*base,
	*helice;

// Define variaveis para navegacao
GLfloat rotX = 0,
		rotY = 0,
		rotX_ini,
		rotY_ini;

GLfloat obsX = 0,
		obsY = 150,
		obsZ = 100,
		obsY_ini;

int x_ini,
	y_ini,
	bot;

// Arquivo de cena e arquivo de camera
// Desenha 4 paredes
void DesenhaParedes(void)
{
	// Insere a matriz de transformação corrente na pilha
	// Parede esquerda
	glPushMatrix();
	glTranslatef(300, 150, 0);
	glRotatef(-90, 0, 1, 0);
	glColor3f(0.92, 0.92, 0.92);
	glScalef(8, 3, 1);
	DesenhaObjeto(plano);
	glPopMatrix();

	// Parede direita
	glPushMatrix();
	glTranslatef(-300, 150, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(8, 3, 1); // 8 m x 3 m
	DesenhaObjeto(plano);
	glPopMatrix();

	// Parede superior dos fundos
	glPushMatrix();
	glTranslatef(0, 274.5, -400);
	glScalef(6, 0.52, 1);
	DesenhaObjeto(plano);
	glPopMatrix();

	// Parede inferior dos fundos
	glPushMatrix();
	glTranslatef(0, 65.5, -400);
	glScalef(6, 1.315, 1);
	DesenhaObjeto(plano);
	glPopMatrix();

	// Parede do meio dos fundos
	glPushMatrix();
	glTranslatef(0, 190, -400);
	glScalef(1.69, 1.2, 1);
	DesenhaObjeto(plano);
	glPopMatrix();

	// Parede direita dos fundos
	glPushMatrix();
	glTranslatef(243, 190, -400);
	glScalef(1.14, 1.2, 1);
	DesenhaObjeto(plano);
	glPopMatrix();

	// Parede esquerda dos fundos
	glPushMatrix();
	glTranslatef(-243, 190, -400);
	glScalef(1.14, 1.2, 1);
	DesenhaObjeto(plano);
	glPopMatrix();

	// Parte superior da frente
	glPushMatrix();
	glTranslatef(0, 250, 400);
	glRotatef(180, 0, 1, 0);
	glScalef(6, 1, 1);
	DesenhaObjeto(plano);
	glPopMatrix();

	// Parte esquerda da frente
	glPushMatrix();
	glTranslatef(87.5, 100, 400);
	glRotatef(180, 0, 1, 0);
	glScalef(4.25, 2, 1);
	DesenhaObjeto(plano);
	glPopMatrix();

	// Parte direita da frente
	glPushMatrix();
	glTranslatef(-257, 100, 400);
	glRotatef(180, 0, 1, 0);
	glScalef(0.86, 2, 1);
	DesenhaObjeto(plano);
	glPopMatrix();
}

void DesenhaChao(void)
{
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(6, 8, 1);
	glColor3f(0.80, 0.80, 0.80);
	DesenhaObjeto(plano);
	glPopMatrix();
}

void DesenhaTeto(void)
{
	glPushMatrix();
	glTranslatef(0, 300, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(6, 8, 1);
	glColor3f(0.90, 0.90, 0.90);
	DesenhaObjeto(plano);
	glPopMatrix();
}

void DesenhaPorta()
{
	// Desenha a porta
	glPushMatrix();

	glTranslatef(-170, 0, 397.5);
	glScalef(100, 100, 100);
	glRotatef(-180, 0, 1, 0);
	glColor3f(0.65, 0.35, 0);
	glTranslatef(x_trans_angle, 0, 0);
	glRotated(angle_door, 0, 1, 0);
	glTranslatef(-x_trans_angle, 0, 0);
	DesenhaObjeto(porta);
	glPopMatrix();
}

void DesenhaJanela()
{
	// Janela Direita
	// JanelaE
	glPushMatrix();
	glTranslatef(109.5, 130, -399);
	glScalef(60, 60, 60);
	glRotatef(-180, 0, 1, 0);
	glColor3f(0.75, 0.75, 0.75);
	glTranslatef(xE_trans_angle, 0, 0);
	glRotated(angleE_window, 0, 1, 0);
	glTranslatef(-xE_trans_angle, 0, 0);
	DesenhaObjeto(janela);
	glPopMatrix();
	// JanelaD
	glPushMatrix();
	glTranslatef(160, 130, -399);
	glScalef(60, 60, 60);
	glRotatef(-180, 0, 1, 0);
	glColor3f(0.75, 0.75, 0.75);
	glTranslatef(xD_trans_angle, 0, 0);
	glRotated(angleD_window, 0, 1, 0);
	glTranslatef(-xD_trans_angle, 0, 0);
	DesenhaObjeto(janela);
	glPopMatrix();

	// Janela Esquerda
	// JanelaE
	glPushMatrix();
	glTranslatef(-160.5, 130, -399);
	glScalef(60, 60, 60);
	glRotatef(-180, 0, 1, 0);
	glColor3f(0.75, 0.75, 0.75);
	glTranslatef(xE_trans_angle, 0, 0);
	glRotated(angleE_window, 0, 1, 0);
	glTranslatef(-xE_trans_angle, 0, 0);
	DesenhaObjeto(janela);
	glPopMatrix();
	// JanelaD
	glPushMatrix();
	glTranslatef(-110, 130, -399);
	glScalef(60, 60, 60);
	glRotatef(-180, 0, 1, 0);
	glColor3f(0.75, 0.75, 0.75);
	glTranslatef(xD_trans_angle, 0, 0);
	glRotated(angleD_window, 0, 1, 0);
	glTranslatef(-xD_trans_angle, 0, 0);
	DesenhaObjeto(janela);
	glPopMatrix();
}

void DesenhaVentiladores()
{

	// Base
	glPushMatrix();
	glTranslatef(0, 252, 180);
	glScalef(40, 40, 40);
	glRotatef(-180, 0, 1, 0);
	glColor3f(0.75, 0.75, 0.75);
	DesenhaObjeto(base);
	glPopMatrix();

	// Hélice
	glPushMatrix();
	glTranslatef(0, 255, 180);
	glScalef(370, 100, 370);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glColor3f(0.85, 0.85, 0.85);
	glRotatef(angulo, 0, 0, 1);
	DesenhaObjeto(helice);
	glPopMatrix();

	// Base
	glPushMatrix();
	glTranslatef(0, 252, -180);
	glScalef(40, 40, 40);
	glRotatef(-180, 0, 1, 0);
	glColor3f(0.75, 0.75, 0.75);
	DesenhaObjeto(base);
	glPopMatrix();

	// Hélice
	glPushMatrix();
	glTranslatef(0, 255, -180);
	glScalef(370, 100, 370);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glColor3f(0.85, 0.85, 0.85);
	glRotatef(angulo, 0, 0, 1);
	DesenhaObjeto(helice);
	glPopMatrix();
}

void DesenhaMesas()
{
	// mesas parede dos fundos
	// mesa
	glPushMatrix();
	glTranslatef(263, 0, 33);
	glRotatef(90, 0, 1, 0);
	glScalef(90, 90, 90);
	glColor3f(1, 1, 1);
	DesenhaObjeto(mesa);
	glPopMatrix();

	// Retira a matriz do topo da pilha e torna esta última a matriz de transformação corrente
	glPopMatrix();

	// mesa
	glPushMatrix();
	glTranslatef(263, 0, -90);
	glRotatef(90, 0, 1, 0);
	glScalef(90, 90, 90);
	glColor3f(1, 1, 1);
	DesenhaObjeto(mesa);
	glPopMatrix();

	// mesa
	glPushMatrix();
	glTranslatef(263, 0, -213);
	glRotatef(90, 0, 1, 0);
	glScalef(90, 90, 90);
	glColor3f(1, 1, 1);
	DesenhaObjeto(mesa);
	glPopMatrix();

	// mesa
	glPushMatrix();
	glTranslatef(263, 0, -336);
	glRotatef(90, 0, 1, 0);
	glScalef(90, 90, 90);
	glColor3f(1, 1, 1);
	DesenhaObjeto(mesa);
	glPopMatrix();

	// mesas da parede esquerda
	// mesa
	glPushMatrix();
	glTranslatef(165, 0, -363);
	glRotatef(-180, 0, 1, 0);
	glScalef(90, 90, 90);
	glColor3f(1, 1, 1);
	DesenhaObjeto(mesa);
	glPopMatrix();

	// mesa
	glPushMatrix();
	glTranslatef(42, 0, -363);
	glRotatef(-180, 0, 1, 0);
	glScalef(90, 90, 90);
	glColor3f(1, 1, 1);
	DesenhaObjeto(mesa);
	glPopMatrix();

	// mesa
	glPushMatrix();
	glTranslatef(-81, 0, -363);
	glRotatef(-180, 0, 1, 0);
	glScalef(90, 90, 90);
	glColor3f(1, 1, 1);
	DesenhaObjeto(mesa);
	glPopMatrix();

	// mesa
	glPushMatrix();
	glTranslatef(-204, 0, -363);
	glRotatef(-180, 0, 1, 0);
	glScalef(90, 90, 90);
	glColor3f(1, 1, 1);
	DesenhaObjeto(mesa);
	glPopMatrix();

	// mesas da parede da frente
	// mesa
	glPushMatrix();
	glTranslatef(-263, 0, 33);
	glRotatef(-90, 0, 1, 0);
	glScalef(90, 90, 90);
	glColor3f(1, 1, 1);
	DesenhaObjeto(mesa);
	glPopMatrix();

	// mesa
	glPushMatrix();
	glTranslatef(-263, 0, -90);
	glRotatef(-90, 0, 1, 0);
	glScalef(90, 90, 90);
	glColor3f(1, 1, 1);
	DesenhaObjeto(mesa);
	glPopMatrix();

	// mesa
	glPushMatrix();
	glTranslatef(-263, 0, -213);
	glRotatef(-90, 0, 1, 0);
	glScalef(90, 90, 90);
	glColor3f(1, 1, 1);
	DesenhaObjeto(mesa);
	glPopMatrix();

	// mesa
	glPushMatrix();
	glTranslatef(-263, 0, -336);
	glRotatef(-90, 0, 1, 0);
	glScalef(90, 90, 90);
	glColor3f(1, 1, 1);
	DesenhaObjeto(mesa);
	glPopMatrix();
}

void DesenhaMonitores()
{
	glColor3f(0.15, 0.15, 0.15);

	desenhaGeral(monitor, 273, 65, 33, -90, 0, 1, 0, 90, 90, 90);
	desenhaGeral(monitor, 273, 65, -90, -90, 0, 1, 0, 90, 90, 90);
	desenhaGeral(monitor, 273, 65, -213, -90, 0, 1, 0, 90, 90, 90);
	desenhaGeral(monitor, 165, 65, -373, 0, 0, 1, 0, 90, 90, 90);
	desenhaGeral(monitor, 42, 65, -373, 0, 0, 1, 0, 90, 90, 90);
	desenhaGeral(monitor, -81, 65, -373, 0, 0, 1, 0, 90, 90, 90);
	desenhaGeral(monitor, -273, 65, 33, 90, 0, 1, 0, 90, 90, 90);
	desenhaGeral(monitor, -273, 65, -90, 90, 0, 1, 0, 90, 90, 90);
	desenhaGeral(monitor, -273, 65, -213, 90, 0, 1, 0, 90, 90, 90);
	desenhaGeral(monitor, -204, 65, -373, 0, 0, 1, 0, 90, 90, 90);
}

void DesenhaTeclados()
{
	// teclados da parede dos fundos
	// teclado
	glPushMatrix();
	glTranslatef(251, 65, 33);
	glRotatef(-90, 0, 1, 0);
	glScalef(90, 90, 90);
	glColor3f(0.15, 0.15, 0.15);
	DesenhaObjeto(teclado);
	glPopMatrix();

	// Retira a matriz do topo da pilha e torna esta última a matriz de transformação corrente
	glPopMatrix();

	// teclado
	glPushMatrix();
	glTranslatef(251, 65, -90);
	glRotatef(-90, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(teclado);
	glPopMatrix();

	// teclado
	glPushMatrix();
	glTranslatef(251, 65, -213);
	glRotatef(-90, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(teclado);
	glPopMatrix();

	// teclados da parede esquerda
	// teclado
	glPushMatrix();
	glTranslatef(165, 65, -351);
	glRotatef(0, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(teclado);
	glPopMatrix();

	// teclado
	glPushMatrix();
	glTranslatef(42, 65, -351);
	glRotatef(0, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(teclado);
	glPopMatrix();

	// teclado
	glPushMatrix();
	glTranslatef(-81, 65, -351);
	glRotatef(0, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(teclado);
	glPopMatrix();

	// teclado
	glPushMatrix();
	glTranslatef(-204, 65, -351);
	glRotatef(0, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(teclado);
	glPopMatrix();

	// teclados da parede da frente
	// teclado
	glPushMatrix();
	glTranslatef(-251, 65, 33);
	glRotatef(90, 0, 1, 0);
	glScalef(90, 90, 90);
	glColor3f(0.15, 0.15, 0.15);
	DesenhaObjeto(teclado);
	glPopMatrix();

	// teclado
	glPushMatrix();
	glTranslatef(-251, 65, -90);
	glRotatef(90, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(teclado);
	glPopMatrix();

	// teclado
	glPushMatrix();
	glTranslatef(-251, 65, -213);
	glRotatef(90, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(teclado);
	glPopMatrix();
}

void DesenhaMouses()
{
	// mouses da parede dos fundos
	// mouse
	glPushMatrix();
	glTranslatef(251, 65, 63);
	glRotatef(-90, 0, 1, 0);
	glScalef(90, 90, 90);
	glColor3f(0.15, 0.15, 0.15);
	DesenhaObjeto(mouse);
	glPopMatrix();

	// Retira a matriz do topo da pilha e torna esta última a matriz de transformação corrente
	glPopMatrix();

	// mouse
	glPushMatrix();
	glTranslatef(251, 65, -60);
	glRotatef(-90, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(mouse);
	glPopMatrix();

	// mouse
	glPushMatrix();
	glTranslatef(251, 65, -183);
	glRotatef(-90, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(mouse);
	glPopMatrix();

	// mouses da parede esquerda
	// mouse
	glPushMatrix();
	glTranslatef(195, 65, -351);
	glRotatef(0, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(mouse);
	glPopMatrix();

	// mouse
	glPushMatrix();
	glTranslatef(72, 65, -351);
	glRotatef(0, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(mouse);
	glPopMatrix();

	// mouse
	glPushMatrix();
	glTranslatef(-51, 65, -351);
	glRotatef(0, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(mouse);
	glPopMatrix();

	// mouse
	glPushMatrix();
	glTranslatef(-174, 65, -351);
	glRotatef(0, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(mouse);
	glPopMatrix();

	// mouses da parede da frente
	// mouse
	glPushMatrix();
	glTranslatef(-251, 65, 3);
	glRotatef(90, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(mouse);
	glPopMatrix();

	// mouse
	glPushMatrix();
	glTranslatef(-251, 65, -120);
	glRotatef(90, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(mouse);
	glPopMatrix();

	// mouse
	glPushMatrix();
	glTranslatef(-251, 65, -243);
	glRotatef(90, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(mouse);
	glPopMatrix();
}

void DesenhaCadeiras()
{
	// cadeiras da parede dos fundos
	// cadeira
	glPushMatrix();
	glTranslatef(221, 0, 33);
	glRotatef(90, 0, 1, 0);
	glScalef(90, 90, 90);
	glColor3f(0, 0, 0.35);
	DesenhaObjeto(cadeira);
	glPopMatrix();

	// Retira a matriz do topo da pilha e torna esta última a matriz de transformação corrente
	glPopMatrix();

	// cadeira
	glPushMatrix();
	glTranslatef(221, 0, -90);
	glRotatef(90, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(cadeira);
	glPopMatrix();

	// cadeira
	glPushMatrix();
	glTranslatef(221, 0, -213);
	glRotatef(90, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(cadeira);
	glPopMatrix();

	// cadeiras da parede esquerda
	// cadeira
	glPushMatrix();
	glTranslatef(165, 0, -321);
	glRotatef(180, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(cadeira);
	glPopMatrix();

	// cadeira
	glPushMatrix();
	glTranslatef(42, 0, -321);
	glRotatef(180, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(cadeira);
	glPopMatrix();

	// cadeira
	glPushMatrix();
	glTranslatef(-81, 0, -321);
	glRotatef(180, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(cadeira);
	glPopMatrix();

	// cadeira
	glPushMatrix();
	glTranslatef(-204, 0, -321);
	glRotatef(180, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(cadeira);
	glPopMatrix();

	// cadeiras da parede da frente
	// cadeira
	glPushMatrix();
	glTranslatef(-221, 0, 33);
	glRotatef(-90, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(cadeira);
	glPopMatrix();

	// cadeira
	glPushMatrix();
	glTranslatef(-221, 0, -90);
	glRotatef(-90, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(cadeira);
	glPopMatrix();

	// cadeira
	glPushMatrix();
	glTranslatef(-221, 0, -213);
	glRotatef(-90, 0, 1, 0);
	glScalef(90, 90, 90);
	DesenhaObjeto(cadeira);
	glPopMatrix();
}

void DesenhaObjExtra()
{
	// lampada (obj1)
	glPushMatrix();
	glTranslatef(0, 297, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glColor3f(0.9, 0.9, 0);
	DesenhaObjeto(lamp);
	glPopMatrix();

	// interruptor
	glPushMatrix();
	glTranslatef(-80, 105, 397.5);
	glRotatef(-180, 0, 1, 0);
	glScalef(120, 120, 120);
	glColor3f(0.90, 0.90, 0.90);
	DesenhaObjeto(interruptor);
	glPopMatrix();

	// lousa
	glPushMatrix();
	glTranslatef(90, 165, 397.5);
	glRotatef(-180, 0, 1, 0);
	glScalef(0.5, 0.65, 0.5);
	glColor3f(1, 1, 1);
	DesenhaObjeto(lousa);
	glPopMatrix();

	// lixeira
	glPushMatrix();
	glTranslatef(-60, 0, 380);
	glRotatef(-180, 0, 1, 0);
	glScalef(120, 120, 120);
	glColor3f(0.15, 0.15, 0.15);
	DesenhaObjeto(lixeira);
	glPopMatrix();
}

// Desenha toda a cena
void Desenha(void)
{
	// Limpa a janela de visualizacao com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Inicializa sistema de coordenadas do modelo
	// antes da execucao de qualquer operacao de manipulacao de matrizes
	glLoadIdentity();

	// Posiciona e orienta observador
	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);
	glTranslatef(-obsX, -obsY, -obsZ);

	glEnable(GL_TEXTURE_2D);

	// Desenha todos os elementos da cena
	DesenhaParedes();
	DesenhaChao();
	DesenhaTeto();
	DesenhaPorta();
	DesenhaJanela();
	DesenhaVentiladores();
	DesenhaMesas();
	DesenhaMonitores();
	DesenhaTeclados();
	DesenhaMouses();
	DesenhaCadeiras();
	DesenhaObjExtra();

	// Faz a troca dos buffers
	glutSwapBuffers();
}

// Gira hélice do ventilador
void AnimacaoHelice(int value)
{
	// Muda o angulo de rotacao, e se chegar a 360, passa para zero
	if (sentido)
	{
		if (--angulo > 360.0f)
			angulo = 0.0f;
	}
	else
	{
		if (++angulo > 360.0f)
			angulo = 0.0f;
	}

	glutPostRedisplay();
	glutTimerFunc(5, AnimacaoHelice, 1);
}

// Funcao usada para especificar o volume de visualizacao
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projecao
	glMatrixMode(GL_PROJECTION);

	// Inicializa sistema de coordenadas de projecao
	glLoadIdentity();

	// Especifica a projecao perspectiva
	// (angulo, aspecto, zMin, zMax)
	gluPerspective(ang_cam, fAspect, 0.1, 1000);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
}

// Funcao callback chamada quando o tamanho da janela e alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisao por zero
	if (h == 0)
		h = 1;

	// Especifica as dimensoes da viewport
	glViewport(0, 0, w, h);

	// Calcula a correcao de aspecto
	fAspect = (GLfloat)w / (GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Funcao callback para eventos de teclas especiais
// de navegacao atraves das setas
void TecladoEspecial(int key, int x, int y)
{
	float sina, cosa, sina_01, cosa_01;

	// Pre-calcula o seno e cosseno do angulo
	// de direcao atual + 90 graus, ou seja,
	// a direcao para deslocamento lateral
	sina = 5 * sin((rotY + 90) * M_PI / 180.0);
	cosa = 5 * cos((rotY + 90) * M_PI / 180.0);

	// Pre-calcula o seno e cosseno do angulo
	// sem os 90 graus
	sina_01 = 5 * sin(rotY * M_PI / 180.0);
	cosa_01 = 5 * cos(rotY * M_PI / 180.0);

	// Trata as teclas especiais
	switch (key)
	{
	// Controles de deslocamento lateral
	case GLUT_KEY_LEFT:
		obsX = obsX - sina;
		obsZ = obsZ + cosa;
		break;
	case GLUT_KEY_RIGHT:
		obsX = obsX + sina;
		obsZ = obsZ - cosa;
		break;
	case GLUT_KEY_UP:
		obsX = obsX + sina_01;
		obsZ = obsZ - cosa_01;
		break;

	case GLUT_KEY_DOWN:
		obsX = obsX - sina_01;
		obsZ = obsZ + cosa_01;
		break;
	}
	glutPostRedisplay();
}

// Funcao callback para eventos de teclado
void Teclado(unsigned char key, int x, int y)
{
	// Trata as diversas teclas
	switch (key)
	{
	case 'n': // abre a porta
		if (angle_door < ANGLE_DOOR_MAX)
		{
			angle_door = angle_door + 1;
		}
		break;
	case 'm': // fecha a porta
		if (angle_door > 0)
		{
			angle_door = angle_door - 1;
		}
		break;
	case 'h': // abre a janela (0 > -180) && (0 < 180)
		if (angleE_window > ANGLEE_WINDOW_MAX && angleD_window < ANGLED_WINDOW_MAX)
		{
			angleE_window = angleE_window - 1;
			angleD_window = angleD_window + 1;
		}
		break;
	case 'j': // fecha a janela (-179 > -360) && (179 > 0)
		if (angleE_window > -360 && angleD_window > 0)
		{
			angleE_window = angleE_window + 1;
			angleD_window = angleD_window - 1;
		}
		break;
	case 'g':
		if (sentido)
		{
			sentido = 0;
		}
		else
		{
			sentido = 1;
		}
	// Sai do programa
	case 27: // Libera todos os objetos carregados...
		LiberaObjeto(NULL);
		exit(1);
		break;
	}
	// Na próxima iteração por meio de glutMainLoop essa janela será exibida novamente
	glutPostRedisplay();
}

// Funcao callback para eventos de botoes do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		// Atualiza as variaveis de navegação com os valores atuais
		x_ini = x;
		y_ini = y;
		obsY_ini = obsY;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else
		bot = -1;
}

// Funcao callback para eventos de movimento do mouse
void GerenciaMovimentoMouse(int x, int y)
{
	// Botao esquerdo ?
	if (bot == GLUT_LEFT_BUTTON)
	{
		// Calcula diferencas
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica angulos
		rotY = rotY_ini - deltax / SENS_ROT;
		rotX = rotX_ini - deltay / SENS_ROT;
	}
	// Botao direito ?
	else if (bot == GLUT_RIGHT_BUTTON)
	{
		// Calcula diferenca
		int deltay = y_ini - y;
		// E modifica altura do observador
		obsY = obsY_ini + deltay / SENS_OBS;
	}
	glutPostRedisplay();
}

// Funcao responsavel por inicializar parametros e variaveis
void Inicializa(void)
{
	// Define a cor de fundo da janela de visualizacao como preto
	glClearColor(0, 0, 0, 1);

	// Habilita Z-Buffer
	// Realiza comparacoes de profundidade
	// e atualiza o buffer de profundidade
	glEnable(GL_DEPTH_TEST);

	// Carrega objetos
	plano = CarregaObjeto("obj/parede.obj", false);
	mesa = CarregaObjeto("obj/mesa.obj", false);
	porta = CarregaObjeto("obj/porta.obj", false);
	janela = CarregaObjeto("obj/janela.obj", false);
	base = CarregaObjeto("obj/base.obj", false);
	helice = CarregaObjeto("obj/helice.obj", false);
	lamp = CarregaObjeto("obj/lampada.obj", false);
	monitor = CarregaObjeto("obj/monitor.obj", false);
	teclado = CarregaObjeto("obj/teclado.obj", false);
	mouse = CarregaObjeto("obj/mouse.obj", false);
	cadeira = CarregaObjeto("obj/cadeira.obj", false);
	interruptor = CarregaObjeto("obj/interruptor.obj", false);
	lousa = CarregaObjeto("obj/lousa.obj", false);
	lixeira = CarregaObjeto("obj/lixeira.obj", false);
}

// Programa Principal
int main(int argc, char **argv)
{
	// Inicilizar a Glut
	glutInit(&argc, argv);

	// Define o modo de operacao da GLUT
	// GLUT_DOUBLE : dois buffers de cor
	// GLUT_RGB : define que as cores do programa serão especificadas por componentes GLUT_RGB
	// GLUT_DEPTH : buffer de profundidade
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Especifica a posicao e o tamanho inicial em pixels da janela GLUT
	glutInitWindowPosition(100, 70);
	glutInitWindowSize(1700, 900);

	// Cria a janela passando como argumento o titulo da mesma
	glutCreateWindow("IC Laboratory");

	// Registra a funcao callback de redesenho da janela de visualizacao
	glutDisplayFunc(Desenha);

	// Registra a funcao callback das teclas de movimentação (especiais)
	glutSpecialFunc(TecladoEspecial);

	// Registra a funcao callback de teclas selecionadas
	glutKeyboardFunc(Teclado);

	// Registra a funcao callback para eventos de botoes do mouse
	glutMouseFunc(GerenciaMouse);

	// Registra a funcao callback para eventos de movimento do mouse
	glutMotionFunc(GerenciaMovimentoMouse);

	// Registra a funcao callback para a hélice do ventilador
	glutTimerFunc(60, AnimacaoHelice, 1);

	// Registra a funcao callback de redimensionamento da janela de visualizacao
	glutReshapeFunc(AlteraTamanhoJanela);

	// Chama a funcao responsavel por fazer as inicializacoes
	Inicializa();

	// Inicia o processamento e aguarda interacoes do usuario
	glutMainLoop();

	return 0;
}