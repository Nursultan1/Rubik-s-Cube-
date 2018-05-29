#include "Cube.h" //заголовочный файл 
#include <time.h> //для рандома
//                        (верх,      низ,   впереди,   сзади,    лево,      право)
unsigned int RGB[9] = { 0xFFFFFF, 0xFFFF00, 0x0000FF, 0x00FF00, 0xFF0000, 	0xF7850A }; // обозначаем цвета:
int xRot = 24, yRot = 24, zRot = 0; // проекции угла поворота на оси
double translateZ = -10.0; // отдаление
Cube cube;
int help1 = 0;
unsigned int textures[5]; // массив текстур
void loadGLTextures() //функция для загрузки текстур
{
	AUX_RGBImageRec *texture1 = auxDIBImageLoad("newgame.bmp"),
		*texture2 = auxDIBImageLoad("inst.bmp"),
		*texture3 = auxDIBImageLoad("inst2.bmp"),
		*texture4 = auxDIBImageLoad("help2.bmp");
	glGenTextures(5, &textures[0]); //генирирует текстуру(чистло текстур, начало)
	glBindTexture(GL_TEXTURE_2D, textures[0]);//текстура который работаем(формат, сам текстура)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// параметры (фармат, свойтва который изменяем, параметр(линейный))
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// параметры (фармат, свойтва который изменяем, параметр(линейный))
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data); //построит(формат,0,кол-во цветов, ширина, высота, граница, фотмат по цветам, тип который представляется тестура, сам ресурс)

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2->sizeX, texture2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2->data);
	
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture3->sizeX, texture3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture3->data);

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture4->sizeX, texture4->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture4->data);
}
void display()
{
	glPushMatrix(); //сохраняем текушую матрицу
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очищаем экран и z - буферизацию
	if (help1 ==1 )
	{
		glTranslatef(0, 0, -35.0);
		glBindTexture(GL_TEXTURE_2D, textures[3]); //накладываем текстуру
		glBegin(GL_QUADS); //инструкция
		glColor3f(1, 1, 1);
		glTexCoord3f(1.0, 1.0, 0.0);	glVertex3f(20, 20, 0.0); //сначало верширы текстуры потом вершины четырёхуголника
		glTexCoord3f(0.0, 1.0, 0.0);	glVertex3f(-20, 20, 0.0);
		glTexCoord3f(0.0, 0.0, 0.0);	glVertex3f(-20, -20, 0.0);
		glTexCoord3f(1.0, 0.0, 0.0);	glVertex3f(20, -20, 0.0);
		glEnd();
	}
	glTranslatef(0, 0, -35); //пермещает системы кординат, от такущего положения 

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS);//подсказка
	glColor3f(1, 1, 1);
	glTexCoord3f(1.0, 1.0, 0.0);	glVertex3f(20,20, 0.0);
	glTexCoord3f(0.0, 1.0, 0.0);	glVertex3f(15, 20, 0.0);
	glTexCoord3f(0.0, 0.0, 0.0);	glVertex3f(15, 10, 0.0);
	glTexCoord3f(1.0, 0.0, 0.0);	glVertex3f(20, 10, 0.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[0]);	
	glBegin(GL_QUADS);//новая игра
	glTexCoord3f(0.0, 1.0,0.0);    glVertex3f(-20, 20, 0.0);
	glTexCoord3f(0.0,0.0,0.0);     glVertex3f(-20, 18, 0.0);
	glTexCoord3f(1.0, 0.0, 0.0);   glVertex3f(-11, 18, 0.0);
	glTexCoord3f(1.0,1.0,0.0);     glVertex3f(-11, 20, 0.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);//инструкция 
	glTexCoord3f(0.0, 1.0, 0.0);	glVertex3f(-10.8, 20, 0.0);
	glTexCoord3f(0.0, 0.0, 0.0);	glVertex3f(-10.8, 18, 0.0);
	glTexCoord3f(1.0, 0.0, 0.0);	glVertex3f(-2.5, 18, 0.0);
	glTexCoord3f(1.0, 1.0, 0.0); 	glVertex3f(-2.5, 20, 0.0);
	glEnd();

	glTranslatef(0, 0, translateZ); 
	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);
	glTranslatef(sizeCube / -2.0, sizeCube / -2.0, sizeCube / -2.0);
	cube.draw();
	glPopMatrix();
	glutSwapBuffers();//освобождает ресурсы
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h); //порт вывода изображения по умолчанию растягивает на все окна
	glMatrixMode(GL_PROJECTION); //загружаем матричную проекцию
	glLoadIdentity(); //очищаем матрицу
	GLfloat fAspect = w / h;
	gluPerspective(60, fAspect, 1, 1000.0); // строит пирамиду охвата видимости(угол обзора,характерическое отношение, растояния от наблюдателя до ближней и далней плоскостей)
	glMatrixMode(GL_MODELVIEW); //устанавливаем тип текушей проекции(обьектно-видовая)
}
void init()
{
	loadGLTextures();//загрузка текстур
	glEnable(GL_TEXTURE_2D);//разрешит накладыват текстуру
	glClearColor(0.5, 0.5, 0.5, 0.0); //фон
	srand(time(0)); // инициализируем случайные числа
	glEnable(GL_DEPTH_TEST); //тест глубины 
	cube.clear(sizeCube, RGB);// инициализируем куб
}
void Keyboard(unsigned char key, int, int)
{
	// если нажали клавишу от 0 до 5 - начинаем поворот на 3 градуса
	if (cube.num == -1 && key >= '0' && key < '6')
	{
		cube.Rotate(key - '0', 3);
		display();
	}
}
void sKeyboard(int key, int, int)
{
	// клавиши влево/вправо вращают по Y, клавиши вверх/вниз вращают по X, F1 - возвращает в начальное положение
	if (key == GLUT_KEY_DOWN)
	{
		xRot += 3;
		if (xRot >= 360)
		{
			xRot -= 360;
		glutPostRedisplay();
		}
	}

	if (key == GLUT_KEY_UP)
	{
		xRot -= 3;
		if (xRot < 0)
			xRot += 360;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_RIGHT)
	{
		yRot += 3;
		if (yRot >= 360)
			yRot -= 360;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_LEFT)
	{
		yRot -= 3;
		if (yRot < 0)
			yRot += 360;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_F2)
	{
		cube.clear(sizeCube, RGB);
		glutPostRedisplay();
		for (int i = 0; i < 900; i++)
		{
			if (cube.num == -1) // если сейчас никакая грань не крутится, то начинаем крутить случайную,
				Keyboard(rand() % 6 + '0', 0, 0);
			else
				cube.Rotate(cube.num, 3); 
			display();
		}
	}
}
void mouse(int button, int state, int x, int y)
{
	if (button == 3)
	{
		translateZ += 5;
		glutPostRedisplay();
	}
	else if (button == 4)
	{
		translateZ -= 5;
		glutPostRedisplay();
	}
	else if (button == GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		if (((x>2 &&x < 157) && (y>2 && y < 39)) && help1 == 0)//кнопка новая игра
		{
			cube.clear(sizeCube, RGB);
			glutPostRedisplay();
			for (int i = 0; i < 900; i++)
			{
				if (cube.num == -1) // если сейчас никакая грань не крутится, то начинаем крутить случайную,
					Keyboard(rand() % 6 + '0', 0, 0);
				else
					cube.Rotate(cube.num, 3); // если включен автоматический поворот, и смотрим
				display();
			}
		}
		else if(((164<x && x<305) &&(y>2 && y< 39)) && help1 == 0)//кнопка инструкция
		{
			help1 = 1;
		}
		else if (((x>2 && x < 101) && (y>2 && y < 39)) && help1 == 1) //кнопка назад из окна помощь
		{
			help1 = 0;
		}
	}
	
}
void timer(int)
{
	glutTimerFunc(timeRot, timer, 0);
	cube.Rotate(cube.num, 3);
	display();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(300, 0);
	glutCreateWindow("Cube");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(timeRot, timer, 0);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(mouse);
	glutSpecialFunc(sKeyboard);
	glutMainLoop();
	return 0;
}