/*

 C++ przez OpenGL - szablon do æwiczeñ laboratoryjnych
 (C) Micha³ Turek.

*/

#ifdef _RYSOWANIE
	glPushMatrix();
		glTranslatef(0,-1,0);
		modelHelper->draw_model("droga_plyta"); // malowanie pod³o¿a
		modelHelper->draw_model("niebo"); // malowanie nieba
	glPopMatrix();


//	glPushMatrix();
//
//	glTranslatef(0.0f, 0.3f, 10.0f);
//
//	glTranslatef(-15.0f, 0.0f, 0.0f);
//
//	modelHelper->draw_model("forklift2");
//
//	// skret w lewo
//	glTranslatef(0.0f, 0.0f, 10.0f);
//	glRotatef(20, 0, 1, 0);
//	glTranslatef(0.0f, 0.0f, -10.0f);
//
//	modelHelper->draw_model("forklift2");
//
//	glTranslatef(0.0f, 0.0f, 10.0f);
//	glRotatef(20, 0, 1, 0);
//	glTranslatef(0.0f, 0.0f, -10.0f);
//
//	modelHelper->draw_model("forklift2");
//
//	glTranslatef(0.0f, 0.0f, 10.0f);
//	glRotatef(20, 0, 1, 0);
//	glTranslatef(0.0f, 0.0f, -10.0f);
//
//	modelHelper->draw_model("forklift2");
//
//	glTranslatef(0.0f, 0.0f, 10.0f);
//	glRotatef(30, 0, 1, 0);
//	glTranslatef(0.0f, 0.0f, -10.0f);
//
//	modelHelper->draw_model("forklift2");
//// koniec skret w lewo
//
//	glTranslatef(-10.0f, 0.0f, 0.0f);
//	modelHelper->draw_model("forklift2");
//
//
//// skret w prawo
//
//	glTranslatef(0.0f, 0.0f, -10.0f);
//	glRotatef(-20, 0, 1, 0);
//	glTranslatef(0.0f, 0.0f, 10.0f);
//
//	modelHelper->draw_model("forklift2");
//
//	glTranslatef(0.0f, 0.0f, -10.0f);
//	glRotatef(-20, 0, 1, 0);
//	glTranslatef(0.0f, 0.0f, 10.0f);
//
//	modelHelper->draw_model("forklift2");
//
//	glTranslatef(0.0f, 0.0f, -10.0f);
//	glRotatef(-20, 0, 1, 0);
//	glTranslatef(0.0f, 0.0f, 10.0f);
//
//	modelHelper->draw_model("forklift2");
//
//	glTranslatef(0.0f, 0.0f, -10.0f);
//	glRotatef(-30, 0, 1, 0);
//	glTranslatef(0.0f, 0.0f, 10.0f);
//
//	modelHelper->draw_model("forklift2");
//	// koniec skret w prawo
//
//	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 0.3, -4.2);
		glScalef(1, 0.65, 1.1);
		modelHelper->draw_model("shelf");
	glPopMatrix();

	forklift->InvokeAction();
	//forklift->draw_all_pallets();
#undef _RYSOWANIE
#endif
