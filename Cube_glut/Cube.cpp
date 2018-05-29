#include "Cube.h" //������������ ���� 
#include <time.h> //��� �������
//                        (����,      ���,   �������,   �����,    ����,      �����)
unsigned int RGB[9] = { 0xFFFFFF, 0xFFFF00, 0x0000FF, 0x00FF00, 0xFF0000, 	0xF7850A }; // ���������� �����:
int xRot = 24, yRot = 24, zRot = 0; // �������� ���� �������� �� ���
double translateZ = -10.0; // ���������
Cube cube;
int help1 = 0;
unsigned int textures[5]; // ������ �������
void loadGLTextures() //������� ��� �������� �������
{
	AUX_RGBImageRec *texture1 = auxDIBImageLoad("newgame.bmp"),
		*texture2 = auxDIBImageLoad("inst.bmp"),
		*texture3 = auxDIBImageLoad("inst2.bmp"),
		*texture4 = auxDIBImageLoad("help2.bmp");
	glGenTextures(5, &textures[0]); //���������� ��������(������ �������, ������)
	glBindTexture(GL_TEXTURE_2D, textures[0]);//�������� ������� ��������(������, ��� ��������)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// ��������� (������, ������� ������� ��������, ��������(��������))
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// ��������� (������, ������� ������� ��������, ��������(��������))
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data); //��������(������,0,���-�� ������, ������, ������, �������, ������ �� ������, ��� ������� �������������� �������, ��� ������)

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
	glPushMatrix(); //��������� ������� �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������� ����� � z - �����������
	if (help1 ==1 )
	{
		glTranslatef(0, 0, -35.0);
		glBindTexture(GL_TEXTURE_2D, textures[3]); //����������� ��������
		glBegin(GL_QUADS); //����������
		glColor3f(1, 1, 1);
		glTexCoord3f(1.0, 1.0, 0.0);	glVertex3f(20, 20, 0.0); //������� ������� �������� ����� ������� ��������������
		glTexCoord3f(0.0, 1.0, 0.0);	glVertex3f(-20, 20, 0.0);
		glTexCoord3f(0.0, 0.0, 0.0);	glVertex3f(-20, -20, 0.0);
		glTexCoord3f(1.0, 0.0, 0.0);	glVertex3f(20, -20, 0.0);
		glEnd();
	}
	glTranslatef(0, 0, -35); //��������� ������� ��������, �� �������� ��������� 

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS);//���������
	glColor3f(1, 1, 1);
	glTexCoord3f(1.0, 1.0, 0.0);	glVertex3f(20,20, 0.0);
	glTexCoord3f(0.0, 1.0, 0.0);	glVertex3f(15, 20, 0.0);
	glTexCoord3f(0.0, 0.0, 0.0);	glVertex3f(15, 10, 0.0);
	glTexCoord3f(1.0, 0.0, 0.0);	glVertex3f(20, 10, 0.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[0]);	
	glBegin(GL_QUADS);//����� ����
	glTexCoord3f(0.0, 1.0,0.0);    glVertex3f(-20, 20, 0.0);
	glTexCoord3f(0.0,0.0,0.0);     glVertex3f(-20, 18, 0.0);
	glTexCoord3f(1.0, 0.0, 0.0);   glVertex3f(-11, 18, 0.0);
	glTexCoord3f(1.0,1.0,0.0);     glVertex3f(-11, 20, 0.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);//���������� 
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
	glutSwapBuffers();//����������� �������
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h); //���� ������ ����������� �� ��������� ����������� �� ��� ����
	glMatrixMode(GL_PROJECTION); //��������� ��������� ��������
	glLoadIdentity(); //������� �������
	GLfloat fAspect = w / h;
	gluPerspective(60, fAspect, 1, 1000.0); // ������ �������� ������ ���������(���� ������,��������������� ���������, ��������� �� ����������� �� ������� � ������ ����������)
	glMatrixMode(GL_MODELVIEW); //������������� ��� ������� ��������(��������-�������)
}
void init()
{
	loadGLTextures();//�������� �������
	glEnable(GL_TEXTURE_2D);//�������� ���������� ��������
	glClearColor(0.5, 0.5, 0.5, 0.0); //���
	srand(time(0)); // �������������� ��������� �����
	glEnable(GL_DEPTH_TEST); //���� ������� 
	cube.clear(sizeCube, RGB);// �������������� ���
}
void Keyboard(unsigned char key, int, int)
{
	// ���� ������ ������� �� 0 �� 5 - �������� ������� �� 3 �������
	if (cube.num == -1 && key >= '0' && key < '6')
	{
		cube.Rotate(key - '0', 3);
		display();
	}
}
void sKeyboard(int key, int, int)
{
	// ������� �����/������ ������� �� Y, ������� �����/���� ������� �� X, F1 - ���������� � ��������� ���������
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
			if (cube.num == -1) // ���� ������ ������� ����� �� ��������, �� �������� ������� ���������,
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
		if (((x>2 &&x < 157) && (y>2 && y < 39)) && help1 == 0)//������ ����� ����
		{
			cube.clear(sizeCube, RGB);
			glutPostRedisplay();
			for (int i = 0; i < 900; i++)
			{
				if (cube.num == -1) // ���� ������ ������� ����� �� ��������, �� �������� ������� ���������,
					Keyboard(rand() % 6 + '0', 0, 0);
				else
					cube.Rotate(cube.num, 3); // ���� ������� �������������� �������, � �������
				display();
			}
		}
		else if(((164<x && x<305) &&(y>2 && y< 39)) && help1 == 0)//������ ����������
		{
			help1 = 1;
		}
		else if (((x>2 && x < 101) && (y>2 && y < 39)) && help1 == 1) //������ ����� �� ���� ������
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