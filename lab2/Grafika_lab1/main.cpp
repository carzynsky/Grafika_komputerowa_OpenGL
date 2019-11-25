// Grafika_lab1.cpp : Defines the entry point for the console application.

#include "stdafx.h"

/*************************************************************************************/

// Trochę bardziej skomplikowany program wykorzystujący funkcje biblioteki OpenGL

/*************************************************************************************/

#include <windows.h>

#include <gl/gl.h>

#include <gl/glut.h>

/*************************************************************************************/
float randNoise() {
	float LO = 0.8f;
	float HI = 1.2f;
	return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI -LO))); // LO; HI
	
}
float randColor() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // 0.0 ; 1.0
}

void dywan(int poziomy, float x1, float y1, float x2, float y2)
{
	if (poziomy == 3)
	{
		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(randColor(), randColor(), randColor()); // wierzchołek czerwony
		glVertex2f(x1, y1);
		glColor3f(randColor(), randColor(), randColor()); // wierzchołek zielony
		glVertex2f(x2, y1);
		glColor3f(randColor(), randColor(), randColor());
		glVertex2f(x1, y2);
		glColor3f(randColor(), randColor(), randColor()); // wierzchołek niebieski
		glVertex2f(x2, y2);

		glEnd();
		return;
	}
	float height = (x2 - x1) / 3;
	float width = (y2 - y1) / 3;

	dywan(poziomy + 1, x1 + 0 * height, y1 + 0 * width, x1 + 1 * height, y1 + 1 * width);//1          1 2 3
	dywan(poziomy+ 1, x1 + 1 * height, y1 + 0 * width, x1 + 2 * height, y1 + 1 * width);//2          4 5 6
	dywan(poziomy + 1, x1 + 2 * height, y1 + 0 * width, x1 + 3 * height, y1 + 1 * width);//3          7 8 9
	dywan(poziomy + 1, x1 + 0 * height, y1 + 1 * width, x1 + 1 * height, y1 + 2 * width);//4
	dywan(poziomy + 1, x1 + 2 * height, y1 + 1 * width, x1 + 3 * height, y1 + 2 * width);//6
	dywan(poziomy + 1, x1 + 0 * height, y1 + 2 * width, x1 + 1 * height, y1 + 3 * width);//7
	dywan(poziomy + 1, x1 + 1 * height, y1 + 2 * width, x1 + 2 * height, y1 + 3 * width);//8
	dywan(poziomy + 1, x1 + 2 * height, y1 + 2 * width, x1 + 3 * height, y1 + 3 * width);//9


}
void prostokat(float x, float y, float a, float b) {

	// first triangle
	glBegin(GL_TRIANGLES);
	a *= randNoise();
	b *= randNoise();
	x *= randNoise();
	y *= randNoise();

	glColor3f(randColor(), randColor(), randColor()); // wierzchołek czerwony
	glVertex2f(x, y);
	glColor3f(randColor(), randColor(), randColor()); // wierzchołek zielony
	glVertex2f(x + a, y);
	glColor3f(randColor(), randColor(), randColor()); // wierzchołek niebieski
	glVertex2f(x, y + b);

	glEnd();

	//second triangle
	glBegin(GL_TRIANGLES);

	glColor3f(randColor(), randColor(), randColor()); // wierzchołek czerwony
	glVertex2f(x, y+b);
	glColor3f(randColor(), randColor(), randColor()); // wierzchołek zielony
	glVertex2f(x + a, y);
	glColor3f(randColor(), randColor(), randColor()); // wierzchołek niebieski
	glVertex2f(x+a, y+b);

	glEnd();
}

// Funkcaja określająca, co ma być rysowane
// (zawsze wywoływana, gdy trzeba przerysować scenę)

void RenderScene(void)

{

	glClear(GL_COLOR_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszczącym
	prostokat(-50.0f, 0.0f, 100.0f, 50.0f);
	//dywan(0,-150.0f, -100.0f, 150.0f, 100.0f);
	glFlush();
	// Przekazanie poleceń rysujących do wykonania

}

/*************************************************************************************/

// Funkcja ustalająca stan renderowania



void MyInit(void)

{

	glClearColor(0.2f, 0.0f, 0.4f, 1.0f);

}

/*************************************************************************************/

// Funkcja służąca do kontroli zachowania proporcji rysowanych obiektów
// niezależnie od rozmiarów okna graficznego



void ChangeSize(GLsizei horizontal, GLsizei vertical)

// Parametry horizontal i vertical (szerokość i wysokość okna) są
// przekazywane do funkcji za każdym razem, gdy zmieni się rozmiar okna

{

	GLfloat AspectRatio;

	// Deklaracja zmiennej AspectRatio określającej proporcję wymiarów okna



	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0

		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkościokna okna urządzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)

	glMatrixMode(GL_PROJECTION);
	// Określenie układu współrzędnych obserwatora

	glLoadIdentity();
	// Określenie przestrzeni ograniczającej

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie współczynnika proporcji okna

	// Gdy okno na ekranie nie jest kwadratem wymagane jest
	// określenie okna obserwatora.
	// Pozwala to zachować właściwe proporcje rysowanego obiektu
	// Do określenia okna obserwatora służy funkcja glOrtho(...)



	if (horizontal <= vertical)

		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);

	else

		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Określenie układu współrzędnych     

	glLoadIdentity();

}

/*************************************************************************************/

// Główny punkt wejścia programu. Program działa w trybie konsoli



void main(void)

{

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wyświetlania
	// GLUT_SINGLE - pojedynczy bufor wyświetlania
	// GLUT_RGBA - model kolorów RGB



	glutCreateWindow("Drugi program w OpenGL");
	// Utworzenie okna i określenie treści napisu w nagłówku okna

	glutDisplayFunc(RenderScene);
	// Określenie, że funkcja RenderScene będzie funkcją zwrotną (callback)
	// Biblioteka GLUT będzie wywoływała tą funkcję za każdym razem, gdy
	// trzeba będzie przerysować okno


	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną za
	// zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powyżej) wykonuje wszelkie 
	// inicjalizacje konieczneprzed przystąpieniem do renderowania


	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}

/*************************************************************************************/