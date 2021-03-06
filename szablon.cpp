/*

 OpenGL - Szablon 3D do cwiczen laboratoryjnych
 (C) Micha� Turek.

*/

#include <regex>
#include <windows.h>
#include "glut.h"
#include "model3DS.h"
#include <time.h>
#include <direct.h>
#include <GL/glu.h>
#include <fstream>
#include "ModelHelper.h"
#include "Forklift.h"
#include "JobList.h"
#include "LeavePalletOperation.h"
#include "LowerMastOperation.h"
#include "MoveOperation.h"
#include "PickUpPalletOperation.h"
#include "RaiseMastOperation.h"
#include "TurnOperation.h"
#include "Configuration.h"

//#include <GL/glaux.h>
//#define GLUTCHECKLOOP

ModelHelper* modelHelper = new ModelHelper();
Forklift* forklift;
int numberOfShelves = 1;
	
// Wymiary okna
int oknoSzerkosc=800;
int oknoWysokosc=600;
bool oknoFullScreen = false;
GLint oknoLewe = 1, oknoPrawe = 2;      // id okien stereo 

// Opcje projekcji stereo
int stereoTryb = 0;
int stereoRozstawOczu = 5;				// dystans mi�dzy oczami
int stereoPunktPatrzenia = 150;			// odleg�o�� do punktu, na kt�ry patrz� oczy
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
bool kameraPrzemieszczanie;		// przemieszczanie lub rozgl�danie
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
	glEnable(GL_LIGHT0);  // �wiatlo sceny

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
		oknoSzerkosc=width;   // przy stereo nie mo�na zmienia� rozmiaru
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

void Draw();

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


	// #define _RYSOWANIE
	// #include "rysowanie.cpp"	// rysowanie
	//
	Draw();

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

	// test json deserialization
	std::string jsonString;
	if (argc > 1) {
		std::ifstream json_file;

		// open json from arg
		json_file.open(argv[1]);
		// if fail
		if (json_file.fail()) {
			std::cout << "Fail to open JSON file\n";
			jsonString = R"(
				{
					"jobs":
					[
						{
							"shelf_index":1,
							"shelf_level":1,
							"pallet_position":1
						}
					]
				}
			)";
		}
		else
		{
			std::stringstream buffer;
			buffer << json_file.rdbuf();
			jsonString = buffer.str();

			// check if indexes are corect
			std::smatch result1, result2;
			std::regex pattern1("\"shelf_level\":\s*(([3-9][0-9]*)|([0-9][0-9]+))");
			std::regex pattern2("\"pallet_position\":\s*(([4-9][0-9]*)|([0-9][0-9]+)|0)");
			if (std::regex_search(jsonString, result1, pattern1) || std::regex_search(jsonString, result2, pattern2)) {
				std::cout << "Wrong JSON indexes\n";
				jsonString = R"(
					{
						"jobs":
						[
							{
								"shelf_index":1,
								"shelf_level":1,
								"pallet_position":2
							}
						]
					}
				)";
			}
		}
	}
	else
	{
		std::cout << "No JSON file specified\n";
		jsonString = R"(
			{
				"jobs":
				[
					{
						"shelf_index":1,
						"shelf_level":1,
						"pallet_position":3
					}
				]
			}
		)";
	}
	

	JobList* jobList = JobList::CreateJobListFromJsonString(jsonString);
	numberOfShelves = jobList->get_number_of_shelves();
	std::vector<Operation*> generatedOperations = jobList->GenerateOperations();

	const std::queue<Operation*> operations(std::deque<Operation*>(generatedOperations.begin(), generatedOperations.end()));
	
	forklift = new Forklift(modelHelper, operations, jobList->get_shelf_index_list());
	
	if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 's') 	// poprawki w konfiguracji na podstawie parametr� (te maj� pierwsze�stwo)
	{
		stereoTryb = 2;
		oknoSzerkosc=800;
		oknoWysokosc=600;
	}
	glutInit(&argc, argv);    	// INIT - wszystkie funkcje obs�ugi okna i przetwzrzania zdarze� realizuje GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	if (stereoTryb == 2) {
		glutInitWindowSize(oknoSzerkosc-8,oknoWysokosc);
		glutInitWindowPosition(0,0);
		oknoLewe = glutCreateWindow("Lewe");  // ==1
		HWND hwnd = FindWindow(NULL, "Lewe");
		SetWindowLong(hwnd, GWL_STYLE, WS_BORDER | WS_MAXIMIZE);
		glutSetWindow(oknoLewe);
		windowInit();
		glutReshapeFunc (rozmiarLewe);						// def. obs�ugi zdarzenia resize (GLUT)
		glutKeyboardFunc (KlawiszKlawiaturyWcisniety);		// def. obs�ugi klawiatury
		glutSpecialFunc (KlawiszSpecjalnyWcisniety);		// def. obs�ugi klawiatury (klawisze specjalne)
		glutMouseFunc (PrzyciskMyszyWcisniety); 			// def. obs�ugi zdarzenia przycisku myszy (GLUT)
		glutMotionFunc (RuchKursoraMyszy);					// def. obs�ugi zdarzenia ruchu myszy (GLUT)
		glutDisplayFunc(rysuj);								// def. funkcji rysuj�cej
		glutInitWindowSize(oknoSzerkosc-8,oknoWysokosc);
		glutInitWindowPosition(oknoSzerkosc+4,0);
		oknoPrawe = glutCreateWindow("Prawe"); // ==2
		glutSetWindow(oknoPrawe);
		windowInit();
		hwnd = FindWindow(NULL, "Prawe");
		SetWindowLong(hwnd, GWL_STYLE, WS_BORDER | WS_MAXIMIZE);
		glutReshapeFunc (rozmiarPrawe);						// def. obs�ugi zdarzenia resize (GLUT)
		glutKeyboardFunc (KlawiszKlawiaturyWcisniety);		// def. obs�ugi klawiatury
		glutSpecialFunc (KlawiszSpecjalnyWcisniety);		// def. obs�ugi klawiatury (klawisze specjalne)
		glutMouseFunc (PrzyciskMyszyWcisniety); 			// def. obs�ugi zdarzenia przycisku myszy (GLUT)
		glutMotionFunc (RuchKursoraMyszy);					// def. obs�ugi zdarzenia ruchu myszy (GLUT)
		glutDisplayFunc(rysuj);								// def. funkcji rysuj�cej
	} else {  // jedno okno
		glutInitWindowSize(oknoSzerkosc,oknoWysokosc);
		glutInitWindowPosition(0,0);
		oknoLewe = glutCreateWindow("Szablon");  
		windowInit();
		glutReshapeFunc (rozmiar);						// def. obs�ugi zdarzenia resize (GLUT)
		glutKeyboardFunc (KlawiszKlawiaturyWcisniety);		// def. obs�ugi klawiatury
		glutSpecialFunc (KlawiszSpecjalnyWcisniety);		// def. obs�ugi klawiatury (klawisze specjalne)
		glutMouseFunc (PrzyciskMyszyWcisniety); 			// def. obs�ugi zdarzenia przycisku myszy (GLUT)
		glutMotionFunc (RuchKursoraMyszy);					// def. obs�ugi zdarzenia ruchu myszy (GLUT)
		glutDisplayFunc(rysuj);								// def. funkcji rysuj�cej
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

void Draw()
{
	glPushMatrix();
	glTranslatef(0, -1, 0);
	modelHelper->draw_model("droga_plyta"); // malowanie pod�o�a
	modelHelper->draw_model("niebo"); // malowanie nieba
	glPopMatrix();


	glPushMatrix();
		glTranslatef(0, 0.3, -4.2);
		for(int i = 0; i < numberOfShelves; i++)
		{
			glPushMatrix();
				glScalef(1, 0.65, 1.1);
				modelHelper->draw_model("shelf");
			glPopMatrix();
			glTranslatef(0, 0, -SPACE_BETWEEN_SHELVES);
		}
	glPopMatrix();

	forklift->InvokeAction();
}