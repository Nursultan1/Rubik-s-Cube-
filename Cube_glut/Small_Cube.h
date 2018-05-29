#include "FGL/Freeglut.h" //�������� ���������� (��������� ������� ��� opengl � ������������ ������� ����. ����)
#include "GL/glaux.h" // ���������� ��� �������� ��������
const int sizeCube = 15; // ������ ���� 
const int timeRot = 20; //�������� �������� �����
class SmallCube 
{
public:
	unsigned int colorSmallCube[6]; //����� ������ ���� - ����� ������  (����, ���, �������, �����, ����, �����)						  
	double sizeSmallCube;   // ������ �����
	unsigned char _color[3]; // ��� ���������� ��� ����� �� ���
	SmallCube() //����������� �� ���������
	{
		for (int i = 0; i < 6; i++)
		{
			colorSmallCube[i] = 0; 
		}
		sizeSmallCube = 0.0; 
	}
	void rotateZ() // ������� �� ��������� X0Y
	{
		unsigned int tmp;
		tmp = colorSmallCube[5]; 
		colorSmallCube[5] = colorSmallCube[3];
		colorSmallCube[3] = colorSmallCube[4];
		colorSmallCube[4] = colorSmallCube[2];
		colorSmallCube[2] = tmp;
	}
	void rotateY()// ������� �� ��������� X0Z
	{
		unsigned int tmp;
		tmp = colorSmallCube[2];
		colorSmallCube[2] = colorSmallCube[1];
		colorSmallCube[1] = colorSmallCube[3];
		colorSmallCube[3] = colorSmallCube[0];
		colorSmallCube[0] = tmp;
	}
	void rotateX()// ������� �� ��������� Y0Z
	{
		unsigned int tmp;
		tmp = colorSmallCube[0];
		colorSmallCube[0] = colorSmallCube[4];
		colorSmallCube[4] = colorSmallCube[1];
		colorSmallCube[1] = colorSmallCube[5];
		colorSmallCube[5] = tmp;
	}
	void setColor(int i, int color) //�������� ������ ������ 
	{
		colorSmallCube[i] = color;
	}
	unsigned char *at(int i) // ��������� colorSmallCube[i] �� 3 ������������ (0xFF0000 RGB(FF, 00, 00))
	{
		_color[0] = colorSmallCube[i] >> 16;
		_color[1] = colorSmallCube[i] >> 8;
		_color[2] = colorSmallCube[i];
		return _color;
	}
	void draw(double x, double y, double z)	// ��������� ���� �� ��������� (x, y, z)
	{
		glPushMatrix();
		glTranslated(x, y, z);
		glBegin(GL_QUADS);
		// ����
		glColor3ubv(at(0));
		glVertex3f(sizeSmallCube, sizeSmallCube, sizeSmallCube);
		glVertex3f(0, sizeSmallCube, sizeSmallCube);
		glVertex3f(0, 0, sizeSmallCube);
		glVertex3f(sizeSmallCube, 0, sizeSmallCube);
		// ���
		glColor3ubv(at(1));
		glVertex3f(sizeSmallCube, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, sizeSmallCube, 0);
		glVertex3f(sizeSmallCube, sizeSmallCube, 0);
		// �������
		glColor3ubv(at(2));
		glVertex3f(sizeSmallCube, 0, sizeSmallCube);
		glVertex3f(0, 0, sizeSmallCube);
		glVertex3f(0, 0, 0);
		glVertex3f(sizeSmallCube, 0, 0);
		// �����
		glColor3ubv(at(3));
		glVertex3f(sizeSmallCube, sizeSmallCube, 0);
		glVertex3f(0, sizeSmallCube, 0);
		glVertex3f(0, sizeSmallCube, sizeSmallCube);
		glVertex3f(sizeSmallCube, sizeSmallCube, sizeSmallCube);
		// �����
		glColor3ubv(at(4));
		glVertex3f(0, sizeSmallCube, sizeSmallCube);
		glVertex3f(0, sizeSmallCube, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, sizeSmallCube);
		// ������
		glColor3ubv(at(5));
		glVertex3f(sizeSmallCube, sizeSmallCube, 0);
		glVertex3f(sizeSmallCube, sizeSmallCube, sizeSmallCube);
		glVertex3f(sizeSmallCube, 0, sizeSmallCube);
		glVertex3f(sizeSmallCube, 0, 0);
		glEnd();
		glPopMatrix();
	}
};
