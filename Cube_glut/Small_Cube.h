#include "FGL/Freeglut.h" //подклчаю библиотеку (открывает контекс для opengl и обрабатывает события клав. мышь)
#include "GL/glaux.h" // библиотека для загрузки текстуры
const int sizeCube = 15; // размер куба 
const int timeRot = 20; //быстрата вращения грани
class SmallCube 
{
public:
	unsigned int colorSmallCube[6]; //шесть граней куба - шесть цветов  (верх, низ, впереди, сзади, лево, право)						  
	double sizeSmallCube;   // размер ребра
	unsigned char _color[3]; // для разделения код цвета на три
	SmallCube() //конструктор по умолчанию
	{
		for (int i = 0; i < 6; i++)
		{
			colorSmallCube[i] = 0; 
		}
		sizeSmallCube = 0.0; 
	}
	void rotateZ() // поворот на плоскости X0Y
	{
		unsigned int tmp;
		tmp = colorSmallCube[5]; 
		colorSmallCube[5] = colorSmallCube[3];
		colorSmallCube[3] = colorSmallCube[4];
		colorSmallCube[4] = colorSmallCube[2];
		colorSmallCube[2] = tmp;
	}
	void rotateY()// поворот на плоскости X0Z
	{
		unsigned int tmp;
		tmp = colorSmallCube[2];
		colorSmallCube[2] = colorSmallCube[1];
		colorSmallCube[1] = colorSmallCube[3];
		colorSmallCube[3] = colorSmallCube[0];
		colorSmallCube[0] = tmp;
	}
	void rotateX()// поворот на плоскости Y0Z
	{
		unsigned int tmp;
		tmp = colorSmallCube[0];
		colorSmallCube[0] = colorSmallCube[4];
		colorSmallCube[4] = colorSmallCube[1];
		colorSmallCube[1] = colorSmallCube[5];
		colorSmallCube[5] = tmp;
	}
	void setColor(int i, int color) //запоняет массив цветов 
	{
		colorSmallCube[i] = color;
	}
	unsigned char *at(int i) // разбиваем colorSmallCube[i] на 3 составляющих (0xFF0000 RGB(FF, 00, 00))
	{
		_color[0] = colorSmallCube[i] >> 16;
		_color[1] = colorSmallCube[i] >> 8;
		_color[2] = colorSmallCube[i];
		return _color;
	}
	void draw(double x, double y, double z)	// отрисовка куба со смещением (x, y, z)
	{
		glPushMatrix();
		glTranslated(x, y, z);
		glBegin(GL_QUADS);
		// верх
		glColor3ubv(at(0));
		glVertex3f(sizeSmallCube, sizeSmallCube, sizeSmallCube);
		glVertex3f(0, sizeSmallCube, sizeSmallCube);
		glVertex3f(0, 0, sizeSmallCube);
		glVertex3f(sizeSmallCube, 0, sizeSmallCube);
		// низ
		glColor3ubv(at(1));
		glVertex3f(sizeSmallCube, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, sizeSmallCube, 0);
		glVertex3f(sizeSmallCube, sizeSmallCube, 0);
		// спереди
		glColor3ubv(at(2));
		glVertex3f(sizeSmallCube, 0, sizeSmallCube);
		glVertex3f(0, 0, sizeSmallCube);
		glVertex3f(0, 0, 0);
		glVertex3f(sizeSmallCube, 0, 0);
		// сзади
		glColor3ubv(at(3));
		glVertex3f(sizeSmallCube, sizeSmallCube, 0);
		glVertex3f(0, sizeSmallCube, 0);
		glVertex3f(0, sizeSmallCube, sizeSmallCube);
		glVertex3f(sizeSmallCube, sizeSmallCube, sizeSmallCube);
		// слева
		glColor3ubv(at(4));
		glVertex3f(0, sizeSmallCube, sizeSmallCube);
		glVertex3f(0, sizeSmallCube, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, sizeSmallCube);
		// справа
		glColor3ubv(at(5));
		glVertex3f(sizeSmallCube, sizeSmallCube, 0);
		glVertex3f(sizeSmallCube, sizeSmallCube, sizeSmallCube);
		glVertex3f(sizeSmallCube, 0, sizeSmallCube);
		glVertex3f(sizeSmallCube, 0, 0);
		glEnd();
		glPopMatrix();
	}
};
