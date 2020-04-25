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

	glPushMatrix();
		glTranslatef(0, 0.3, -4.2);
		glScalef(1, 0.65, 1.1);
		modelHelper->draw_model("shelf");
	glPopMatrix();

	forklift->InvokeAction();
	forklift->draw_all_pallets();
#undef _RYSOWANIE
#endif
