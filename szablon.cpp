/*

 OpenGL - Szablon 3D do cwiczen laboratoryjnych
 (C) Micha³ Turek.

*/

#include <windows.h>
#include "glut.h"
#include "model3DS.h"
#include <time.h>
#include <direct.h>
#include <GL/glu.h>
#include "ModelHelper.h"
#include "Forklift.h"
#include "LeavePalletOperation.h"
#include "LowerMastOperation.h"
#include "MoveOperation.h"
#include "PickUpPalletOperation.h"
#include "RaiseMastOperation.h"
#include "TurnOperation.h"

//#include <GL/glaux.h>
//#define GLUTCHECKLOOP

ModelHelper* modelHelper = new ModelHelper();
Forklift* forklift;// = new Forklift(modelHelper);
	
// Wymiary okna
int oknoSzerkosc=800;
int oknoWysokosc=600;
bool oknoFullScreen = false;
GLint oknoLewe = 1, oknoPrawe = 2;      // id okien stereo 

// Opcje projekcji stereo
int stereoTryb = 0;
int stereoRozstawOczu = 5;				// dystans miêdzy oczami
int stereoPunktPatrzenia = 150;			// odleg³oœæ do punktu, na który patrz¹ oczy
bool stereoIDRamki = false;	
bool timing100FPS = true;				// flaga polecenia odmierzania czasu

// Kamera
int pozycjaMyszyX;						// na ekranie
int pozycjaMyszyY;
double kameraX;
double kameraY;
double kameraZ;
double kameraPunktY;
double kameraPredkoscPunktY;
double kameraPredkosc;
bool kameraPrzemieszczanie;		// przemieszczanie lub rozgl¹danie
double kameraKat;				// kat patrzenia
double kameraPredkoscObrotu;	
#define MIN_DYSTANS 0.5			// minimalny dystans od brzegu obszaru ograniczenia kamery
double obszarKamery = 0;

#define _DEFINICJE
#include "definicje.cpp"


		/** REJESTRATOR PRZESZKOD **/

struct przeszkoda{
	przeszkoda *next;
	double posX1;
	double posZ1;
	double posX2;
	double posZ2;
};
przeszkoda *obszarPrzeszkody = NULL;

void resetKamery(){
	kameraX = 0;
	kameraY = 4;
	kameraZ = 40;
	kameraKat = -0.4;
	kameraPunktY = -15;
	kameraPredkoscPunktY = 0;
	kameraPredkosc = 0;
	kameraPredkoscObrotu = 0;
	kameraPrzemieszczanie = true;
}

void ustalObszar (double X){
	obszarKamery = X;	
}

bool wObszarze(double posX, double posZ){ 
	if ( posX*posX + posZ*posZ > (obszarKamery-MIN_DYSTANS*2)*(obszarKamery-MIN_DYSTANS*2) ) return false;
	przeszkoda * pom = obszarPrzeszkody;
	while (pom){
		if (pom->posX1 < posX && 
			pom->posX2 > posX && 
			pom->posZ1 < posZ && 
			pom->posZ2 > posZ ) return false;
		pom = pom -> next;
	}
	return true;
}

void rejestrujPrzeszkode(double X1, double Z1, double X2, double Z2){
	przeszkoda * pom = new przeszkoda;
	if (X1 > X2) {double tmp = X1; X1 = X2; X2 = tmp;}
	if (Z1 > Z2) {double tmp = Z1; Z1 = Z2 ;Z2 = tmp;}
	pom -> posX1 = X1;
	pom -> posZ1 = Z1;
	pom -> posX2 = X2;
	pom -> posZ2 = Z2;
	pom -> next = obszarPrzeszkody;
	obszarPrzeszkody = pom;
}

		/** OBSLUGA INTERAKCJI Z UZYTKOWNIKIEM **/

void SzablonPrzyciskMyszyWcisniety (int button, int state, int x, int y)
{
	switch (state)
	{
		case GLUT_UP:
			kameraPredkosc = 0;
			kameraPredkoscObrotu = 0;
			kameraPredkoscPunktY = 0;
		break;
		case GLUT_DOWN:
				pozycjaMyszyX = x;
				pozycjaMyszyY = y;
			if (button == GLUT_LEFT_BUTTON)
				kameraPrzemieszczanie = true;
			else 
				kameraPrzemieszczanie = false;
		break;
	}
}

void SzablonRuchKursoraMyszy (int x, int y)
{
	kameraPredkoscObrotu = -(pozycjaMyszyX - x) * 0.001;
	if (kameraPrzemieszczanie)
	{
		kameraPredkosc = (pozycjaMyszyY - y) * 0.02;
		kameraPredkoscPunktY = 0;
	} else {
		kameraPredkoscPunktY = (pozycjaMyszyY - y) * 0.06;
		kameraPredkosc = 0;
	}
}

void SzablonKlawiszKlawiaturyWcisniety (GLubyte key, int x, int y)
{
   switch (key) {
   case 27:    
      exit(1);
   break;
   case ' ':    
      if (stereoTryb != 2) glutFullScreen();
      break;

   }

}

		/** INICJALIZACJA **/

#define _INTERAKCJA
#include "interakcja.cpp"

void windowInit()
{
	glClearColor(0.2, 0.2, 1.0, 0.0);			
    glShadeModel(GL_SMOOTH);					
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST); 
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); 
	glEnable(GL_LIGHTING);
	GLfloat  ambient[4] = {0.3,0.3,0.3,1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient); 

	GLfloat  diffuse[4] = {0.9,0.9,0.9,1};
	GLfloat  specular[4] = {0.9,0.9,0.9,1};
	GLfloat	 position[4] = {30,30,-30,1};
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	glLightfv(GL_LIGHT0,GL_POSITION,position);
	glEnable(GL_LIGHT0);  // œwiatlo sceny

	/*******************MGLA**************************/

	//float fogColor[4]= {0.8f, 0.8f, 0.8f, 0.1f};
	//glFogi(GL_FOG_MODE,GL_EXP2); // [GL_EXP, GL_EXP2, GL_LINEAR ]
	//glFogfv(GL_FOG_COLOR, fogColor); 
	//glFogf(GL_FOG_DENSITY, 0.01f); 
	//glFogf(GL_FOG_START, 0.0f); 
	//glFogf(GL_FOG_END, 200.0f); 
	//glEnable(GL_FOG);  


}

void rozmiar (int width, int height)
{
	if (width==0) width++;
	if (width==0) width++;
	if (stereoTryb != 2) {
		oknoSzerkosc=width;   // przy stereo nie mo¿na zmieniaæ rozmiaru
		oknoWysokosc=height; 
	}
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glViewport(0,0,oknoSzerkosc,oknoWysokosc+24); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluPerspective(45.0f,(GLfloat)oknoSzerkosc/(GLfloat)oknoWysokosc,1.0f,10000.0f);
	glMatrixMode(GL_MODELVIEW);

}

void rozmiarLewe (int width, int height)
{
	glutSetWindow(oknoLewe);
	rozmiar (width, height);
}

void rozmiarPrawe (int width, int height)
{
	glutSetWindow(oknoPrawe);
	rozmiar (width, height);
}

/**********************************************************
 		RYSOWANIE TRESCI RAMKI
 *********************************************************/

void rysujRamke(bool prawa)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Kasowanie ekranu
	glLoadIdentity();
	switch (stereoTryb){
		case 0: // zwykle mono
			 gluLookAt (kameraX,kameraY,kameraZ,kameraX + 100*sin(kameraKat),3 + kameraPunktY	,kameraZ - 100*cos(kameraKat),0,1,0); // kamera
		break;
		case 1: // 3D-ready
		case 2: // pelne stereo 
		case 3: // anaglyph
			if (prawa){			//  klatka prawa
				float newKameraX = kameraX - stereoRozstawOczu/2*cos(kameraKat);
				float newKameraZ = kameraZ - stereoRozstawOczu/2*sin(kameraKat);
				gluLookAt (newKameraX,kameraY,newKameraZ,kameraX+0.2 + stereoPunktPatrzenia*sin(kameraKat),3 + kameraPunktY	,kameraZ - stereoPunktPatrzenia*cos(kameraKat),0,1,0); // kamera
			}
			else {				// klatka lewa
				float newKameraX = kameraX + stereoRozstawOczu/2*cos(kameraKat);
				float newKameraZ = kameraZ + stereoRozstawOczu/2*sin(kameraKat);
				gluLookAt (newKameraX,kameraY,newKameraZ,kameraX+0.2 + stereoPunktPatrzenia*sin(kameraKat),3 + kameraPunktY	,kameraZ - stereoPunktPatrzenia*cos(kameraKat),0,1,0); // kamera
			}
		break;
	} //case


	#define _RYSOWANIE
	#include "rysowanie.cpp"	// rysowanie 

	glFlush(); 
    glPopMatrix();
}

void rysuj()
{
	switch (stereoTryb){
		case 0: // mono
			 rysujRamke (false);
			 glutSwapBuffers(); 
		break;
		case 1: // 3D-ready
			 stereoIDRamki = !stereoIDRamki;
			 rysujRamke (stereoIDRamki);
			 glutSwapBuffers(); 
		break;
		case 2: // pelne stereo
			glutSetWindow(oknoLewe);
			rysujRamke (false);
			glutSetWindow(oknoPrawe);
			rysujRamke  (true);
			glutSetWindow(oknoLewe);
	 		glutSwapBuffers();			// Wyslanie na ekran (L+P) synchronizowane
			glutSetWindow(oknoPrawe);
	 		glutSwapBuffers(); 
		break;
		case 3: // anaglyph
			glColorMask(true, false, false, false);
			rysujRamke (true);
			glClear(GL_DEPTH_BUFFER_BIT);
			glColorMask(false, true, true, false);
			rysujRamke (false);
			glColorMask(true, true, true, true);
			glutSwapBuffers(); 
	}
}

void timer()
{
	double kameraXTmp = kameraX+kameraPredkosc*sin(kameraKat);
    double kameraZTmp = kameraZ-kameraPredkosc*cos(kameraKat);
	kameraKat = kameraKat + kameraPredkoscObrotu;
	kameraPunktY = kameraPunktY + kameraPredkoscPunktY;
	if (wObszarze(kameraXTmp,kameraZTmp))
	{
		kameraX = kameraXTmp;
		kameraZ = kameraZTmp;
	} else 
		kameraPredkosc = 0;
	rysuj();		
}

void syncTimer (int ID)
{
	timer();
	glutTimerFunc(1,syncTimer,10);
}

int main(int argc, char **argv)
{
	#define _KONFIGURACJA
	#include "konfiguracja.cpp"

	// initialize forklift here
	std::queue<Operation*> operations;
	
	operations.push(new MoveOperation(Operation::MoveDirection::Forward, 10));	
	operations.push(new TurnOperation(Operation::TurnDirection::Left, Operation::MoveDirection::Forward, 90));
	operations.push(new MoveOperation(Operation::MoveDirection::Backward, 15));
	operations.push(new TurnOperation(Operation::TurnDirection::Right, Operation::MoveDirection::Forward, 90));
	operations.push(new MoveOperation(Operation::MoveDirection::Backward, 20));
	operations.push(new TurnOperation(Operation::TurnDirection::Left, Operation::MoveDirection::Backward, 90));	
	operations.push(new MoveOperation(Operation::MoveDirection::Forward, 10));


	operations.push(new RaiseMastOperation(Operation::ShelfLevel::Level2));
	operations.push(new MoveOperation(Operation::MoveDirection::Forward, 5));
	operations.push(new LeavePalletOperation());
	operations.push(new MoveOperation(Operation::MoveDirection::Backward, 5));
	operations.push(new LowerMastOperation());
	
	operations.push(new PickUpPalletOperation());
	operations.push(new RaiseMastOperation(Operation::ShelfLevel::Level0));
	operations.push(new MoveOperation(Operation::MoveDirection::Forward, 5));
	operations.push(new LeavePalletOperation());
	operations.push(new MoveOperation(Operation::MoveDirection::Backward, 5));
	operations.push(new LowerMastOperation());
	
	operations.push(new PickUpPalletOperation());
	operations.push(new RaiseMastOperation(Operation::ShelfLevel::Level1));
	operations.push(new MoveOperation(Operation::MoveDirection::Forward, 5));
	operations.push(new LeavePalletOperation());
	operations.push(new MoveOperation(Operation::MoveDirection::Backward, 5));
	operations.push(new LowerMastOperation());
	
	operations.push(new PickUpPalletOperation());

	forklift = new Forklift(modelHelper, operations);
	
	if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 's') 	// poprawki w konfiguracji na podstawie parametró (te maj¹ pierwszeñstwo)
	{
		stereoTryb = 2;
		oknoSzerkosc=800;
		oknoWysokosc=600;
	}
	glutInit(&argc, argv);    	// INIT - wszystkie funkcje obs³ugi okna i przetwzrzania zdarzeñ realizuje GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	if (stereoTryb == 2) {
		glutInitWindowSize(oknoSzerkosc-8,oknoWysokosc);
		glutInitWindowPosition(0,0);
		oknoLewe = glutCreateWindow("Lewe");  // ==1
		HWND hwnd = FindWindow(NULL, "Lewe");
		SetWindowLong(hwnd, GWL_STYLE, WS_BORDER | WS_MAXIMIZE);
		glutSetWindow(oknoLewe);
		windowInit();
		glutReshapeFunc (rozmiarLewe);						// def. obs³ugi zdarzenia resize (GLUT)
		glutKeyboardFunc (KlawiszKlawiaturyWcisniety);		// def. obs³ugi klawiatury
		glutSpecialFunc (KlawiszSpecjalnyWcisniety);		// def. obs³ugi klawiatury (klawisze specjalne)
		glutMouseFunc (PrzyciskMyszyWcisniety); 			// def. obs³ugi zdarzenia przycisku myszy (GLUT)
		glutMotionFunc (RuchKursoraMyszy);					// def. obs³ugi zdarzenia ruchu myszy (GLUT)
		glutDisplayFunc(rysuj);								// def. funkcji rysuj¹cej
		glutInitWindowSize(oknoSzerkosc-8,oknoWysokosc);
		glutInitWindowPosition(oknoSzerkosc+4,0);
		oknoPrawe = glutCreateWindow("Prawe"); // ==2
		glutSetWindow(oknoPrawe);
		windowInit();
		hwnd = FindWindow(NULL, "Prawe");
		SetWindowLong(hwnd, GWL_STYLE, WS_BORDER | WS_MAXIMIZE);
		glutReshapeFunc (rozmiarPrawe);						// def. obs³ugi zdarzenia resize (GLUT)
		glutKeyboardFunc (KlawiszKlawiaturyWcisniety);		// def. obs³ugi klawiatury
		glutSpecialFunc (KlawiszSpecjalnyWcisniety);		// def. obs³ugi klawiatury (klawisze specjalne)
		glutMouseFunc (PrzyciskMyszyWcisniety); 			// def. obs³ugi zdarzenia przycisku myszy (GLUT)
		glutMotionFunc (RuchKursoraMyszy);					// def. obs³ugi zdarzenia ruchu myszy (GLUT)
		glutDisplayFunc(rysuj);								// def. funkcji rysuj¹cej
	} else {  // jedno okno
		glutInitWindowSize(oknoSzerkosc,oknoWysokosc);
		glutInitWindowPosition(0,0);
		oknoLewe = glutCreateWindow("Szablon");  
		windowInit();
		glutReshapeFunc (rozmiar);						// def. obs³ugi zdarzenia resize (GLUT)
		glutKeyboardFunc (KlawiszKlawiaturyWcisniety);		// def. obs³ugi klawiatury
		glutSpecialFunc (KlawiszSpecjalnyWcisniety);		// def. obs³ugi klawiatury (klawisze specjalne)
		glutMouseFunc (PrzyciskMyszyWcisniety); 			// def. obs³ugi zdarzenia przycisku myszy (GLUT)
		glutMotionFunc (RuchKursoraMyszy);					// def. obs³ugi zdarzenia ruchu myszy (GLUT)
		glutDisplayFunc(rysuj);								// def. funkcji rysuj¹cej
	}
		if (stereoTryb == 1 || !timing100FPS)
			glutIdleFunc(timer);				
		else 
			glutTimerFunc(10,syncTimer,10);
		resetKamery();
		//srand( (unsigned)time( NULL ) ); // generator liczb losowych
	    modelHelper->load_models();
		modelHelper->activate_special_model_rendering("woda",1);
		modelHelper->activate_special_model_rendering("most",2);
		if (oknoFullScreen && stereoTryb != 2) glutFullScreen();
		glutMainLoop();        
	return(0);    
}