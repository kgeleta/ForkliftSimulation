/*

 C++ przez OpenGL - szablon do æwiczeñ laboratoryjnych
 (C) Micha³ Turek.

*/

#ifdef _RYSOWANIE

const int ROAD_LENGTH = 24;
const int CROSSROAD_LENGTH = 7;


	/******************* SZABLON **************************/
	static int time = 0;
	static int forklift1Position = 50;
	static int forklift2Position = 0;

	// ###################################
	static float topPartPosition = -4.5f;
	static float forkPosition = -4.5f;

	time = (time++) % 100;

	// TEREN	
	// Tekstura podloza jest zapisana w pliku "data/podloze.bmp", definiowana bezpoœrednio w 3ds. 
	// Wymagany format pliku: bmp, 24 bity na pixel.

	//glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();
		glTranslatef(0,-1,0);
		modelHelper->draw_model("desert_terrain"); // malowanie pod³o¿a
		modelHelper->draw_model("niebo"); // malowanie nieba
	glPopMatrix();
	

	// MODELE 3ds:
	// Modele 3ds znajdujace sie w katalogu /data s¹ autoamtycznie ladowane i rejestrowane pod nazwami zbieznymi z nazwami plikow
	// Aby narysowaæ model nalezy wywo³aæ funkcjê: modelHelper->draw_model ("nazwa_modelu");
	// Nazwa_modelu mo¿e byæ podana literemi du¿ymi lub ma³ymi, z rozszerzeniem pliku lub bez.
		
	// przyklad:	

	glPushMatrix();
		glTranslatef(-20, 0.3, -50);
		modelHelper->draw_model("wiatrak");
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, 0.3, 45);
	modelHelper->draw_model("Semaphore");
	glPopMatrix();

	// pallet
	glPushMatrix();
	glTranslatef(0, 0.3, -4.2);
	glScalef(1, 0.65, 1.1);
	modelHelper->draw_model("shelf");
	glPopMatrix();
	
	// forklift1 animation
	forklift->InvokeAction();
	forklift->draw_all_pallets();
	//glPushMatrix();
	//	if (time % 5 == 0)
	//	{
	//		if (forkPosition <= -0.001f)
	//		{
	//			forkPosition += 0.1f;
	//		}
	//		else if (topPartPosition <= -0.001f)
	//		{
	//			topPartPosition += 0.1f;
	//		}
	//	}

	//	glTranslatef(0, 0.3, 0);

	//	glRotatef(-90,0,1,0);

	//	modelHelper->draw_model("forklift2");

	//	glTranslatef(0, topPartPosition, 0);
	//	modelHelper->draw_model("topPart");

	//	glTranslatef(0, forkPosition, 0);
	//	modelHelper->draw_model("fork");

	//	glTranslatef(-3.8, 10.1, 1.1);
	//	modelHelper->draw_model("pallet");

	//glPopMatrix();



	// slupy
	glPushMatrix();
		glTranslatef(-67, 0.3, -57);
		modelHelper->draw_model("linia_slup");

		for (int i = 0; i < 9; i++)
		{
			glTranslatef(0, 0, 10.5);
			modelHelper->draw_model("linia");
		}
		
	glPopMatrix();

	// tory
	glPushMatrix();
		glTranslatef(40, 0.3, -57);
		modelHelper->draw_model("tor");

		for (int i = 0; i < 6; i++)
		{
			glTranslatef(0, 0, 13.5);
			modelHelper->draw_model("tor");
		}

		modelHelper->draw_model("tor_zakret");

		glRotatef(-30, 0, 1, 0);
		glTranslatef(3.42, 0, 14);

		modelHelper->draw_model("tor_zakret");

		glRotatef(-30, 0, 1, 0);
		glTranslatef(3.42, 0, 14);

		modelHelper->draw_model("tor_zakret");

		glRotatef(-30, 0, 1, 0);
		glTranslatef(3.42, 0, 14.2);

		for (int i = 0; i < 10; i++)
		{
			glTranslatef(0, 0, 13.5);
			modelHelper->draw_model("tor");
		}
		
	glPopMatrix();

	// droga
	glPushMatrix();
		glTranslatef(0, 0.3, -57);
		modelHelper->draw_model("droga_prosta");			

		glTranslatef(0, 0, 7);
		modelHelper->draw_model("droga_przejscie");
		
		glTranslatef(0, 0, ROAD_LENGTH);
		modelHelper->draw_model("droga_prosta");

		glTranslatef(0, 0, CROSSROAD_LENGTH);
		modelHelper->draw_model("droga_skrzyzowanie");

		glPushMatrix();
			glTranslatef(0, 0, ROAD_LENGTH + CROSSROAD_LENGTH);
			modelHelper->draw_model("droga_prosta");

			glTranslatef(0, 0, ROAD_LENGTH);
			modelHelper->draw_model("droga_prosta");

			glTranslatef(0, 0, ROAD_LENGTH);
			modelHelper->draw_model("droga_prosta");

			glTranslatef(0, 0, CROSSROAD_LENGTH);
			glRotatef(90, 0, 1, 0);
			modelHelper->draw_model("droga_zakret");

			glTranslatef(0, 0, 10);
			glRotatef(90, 0, 1, 0);
			modelHelper->draw_model("droga_koniec");
		glPopMatrix();

		// back to crossroad
		glRotatef(90, 0, 1, 0);

		glTranslatef(0, 0, -CROSSROAD_LENGTH);
		modelHelper->draw_model("droga_prosta");

		glTranslatef(0, 0, -ROAD_LENGTH);
		modelHelper->draw_model("droga_prosta");

		glRotatef(-270, 0, 1, 0);
		glTranslatef(ROAD_LENGTH + 7, 0, 0);
		modelHelper->draw_model("droga_skrzyzowanie");

		glPushMatrix();
			glTranslatef(0, 0, -7);
			modelHelper->draw_model("droga_prosta");

			glTranslatef(0, 0, -ROAD_LENGTH);
			modelHelper->draw_model("droga_przejscie");

			glTranslatef(0, 0, -7);
			modelHelper->draw_model("droga_prosta");


			glTranslatef(0, 0, -ROAD_LENGTH);
			glRotatef(-90, 0, 1, 0);

			modelHelper->draw_model("droga_koniec");
		glPopMatrix();

		// back to crossroad
		glTranslatef(0, 0, ROAD_LENGTH + CROSSROAD_LENGTH);
		modelHelper->draw_model("droga_prosta");

		glTranslatef(0, 0, ROAD_LENGTH);
		modelHelper->draw_model("droga_prosta");
	glPopMatrix();

	

#undef _RYSOWANIE
#endif
