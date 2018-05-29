#include "Small_Cube.h" //������������ ����
class Cube
{
	SmallCube a[3][3][3]; // 27 ������ 
	int rotate[6]; //  ���� �������� ������ �����
	double sizeCube; // ������ �����-������
	unsigned int color[6]; // ����� ������
	int _angle[4];
	bool ok[4][4][4];
	SmallCube tmp[4][4];
public:
	int num; // ������ ����� �����, ������� � ������ ������ ��������������, ��� -1 ���� ������ �� ��������������
	Cube() {} // ����������� �� ���������
	void clear(double size, unsigned int *RGB)
	{
		for (int i = 0; i < 6; i++)
		{
			rotate[i] = 0; // �� ��������� ����� ����� ����
		}
		this->sizeCube = size; // ������ ���� 
		num = -1; // �� ��������� �� ����� ���� �� ��������
		int i, j, k;
		for (i = 0; i < 6; i++)
		{
			this->color[i] = RGB[i]; // ��������� ������ ������
		}
		// ����
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				a[i][j][2].setColor(0, RGB[0]);
			}
		}
		// ���
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				a[i][j][0].setColor(1, RGB[1]);
			}
		}		
		// �������
		for (k = 0; k < 3; k++)
		{
			for (j = 0; j < 3; j++)
			{
				a[j][0][k].setColor(2, RGB[2]);
			}
		}
		// �����
		for (k = 0; k < 3; k++)
		{
			for (j = 0; j < 3; j++)
			{
				a[j][2][k].setColor(3, RGB[3]);
			}
		}
		// �����
		for (i = 0; i < 3; i++)
		{
			for (k = 0; k < 3; k++)
			{
				a[0][k][i].setColor(4, RGB[4]);
			}
		}
		// ������
		for (i = 0; i < 3; i++)
		{
			for (k = 0; k < 3; k++)
			{
				a[2][k][i].setColor(5, RGB[5]);
			}
		}
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				for (k = 0; k < 3; k++)
				{
					a[i][j][k].sizeSmallCube = (size / 3.0) * 0.95;
				}
			}
		}
	}
	void draw()
	{
		for (int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					ok[i][j][k] = true;  //���������  ������ ok[][][] �������� , ���������� �������� ������ ���� ���
				}
			}

		}
		if (num != -1) 
		{
			glPushMatrix();
			int i, j, k;

			if (num == 0 || num == 1) // ����� ��������� ���� ��� �����  
			{
				if ((num % 2) == 0) //��� ����� �� ��� ��������
				{
					k = 0;
				}
				else
				{
					k = 2;
				}
				for (i = 0; i < 3; i++)
				{
					for (j = 0; j < 3; j++)
					{
						ok[i][j][k] = false; //����� � ����� ������
					}
				}
				
				glTranslated(sizeCube / 2, sizeCube / 2, 0);   // ���������� � ������ 
				glRotatef(rotate[num], 0, 0, 1);  // ������
				glTranslated(-sizeCube / 2, -sizeCube / 2, 0);  // ���������� �������
				for (i = 0; i < 3; i++)
				{
					for (j = 0; j < 3; j++)
					{
						a[i][j][k].draw(sizeCube / 3 * i, sizeCube / 3 * j, sizeCube / 3 * k); //������
					}
				}
			}
			//���� ����� ���������� �������
			else if (num == 2 || num == 3)
			{
				if ((num % 2) == 0)
				{
					j = 0;
				}
				else
				{
					j = 2;
				}
				for (i = 0; i < 3; i++)
				{
					for (k = 0; k < 3; k++)
					{
						ok[i][j][k] = false; 
					}
				}
				glTranslated(sizeCube / 2, 0, sizeCube / 2); 
				glRotatef(rotate[num], 0, 1, 0); 
				glTranslated(-sizeCube / 2, 0, -sizeCube / 2); 
				for (i = 0; i < 3; i++)
				{
					for (k = 0; k < 3; k++)
					{
						a[i][j][k].draw(sizeCube / 3 * i, sizeCube / 3 * j, sizeCube / 3 * k); 
					}
				}
			}
			else if (num == 4 || num == 5)
			{
				if ((num % 2) == 0)
				{
					i = 0;
				}
				else
				{
					i = 2;
				}
				for (j = 0; j < 3; j++)
				{
					for (k = 0; k < 3; k++)
					{
						ok[i][j][k] = false;
					}
				}
				glTranslated(0, sizeCube / 2, sizeCube / 2);
				glRotatef(rotate[num], 1, 0, 0);
				glTranslated(0, -sizeCube / 2, -sizeCube / 2);
				for (j = 0; j < 3; j++)
				{
					for (k = 0; k < 3; k++)
					{
						a[i][j][k].draw(sizeCube / 3 * i, sizeCube / 3 * j, sizeCube / 3 * k);
					}
				}
			}
			glPopMatrix();
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					if (ok[i][j][k])
					{
						// ������ �� ������, ������� �� �������������� ����,ok[i][j][k] = true
						a[i][j][k].draw(sizeCube / 3 * i, sizeCube / 3 * j, sizeCube / 3 * k);
					}
				}
			}
		}
	}
	void rot90(int idx, int sign)
	{
		int i, j, k;
		// sign ������� � ����������� �� �����������
		// sign = -1, sign = 1
		// ���� sign = -1, ������ ������ 3 ����
		if (sign == -1)
		{
			sign = 3;
		}
		while (sign--)
		{
			if (idx == 0 || idx == 1)
			{
				// ���/����
				if ((idx % 2) == 0)
				{
					k = 0;
				}
				else
				{
					k = 2;
				}
				// �������� ��������� �� 90 �������� �������/������ �����
				// � ������ tmp, ����� ����� ����������� tmp
				for (i = 0; i < 3; i++)
				{
					for (j = 0; j < 3; j++)
					{
						tmp[j][2 - i] = a[i][j][k];
					}
				}
				for (i = 0; i < 3; i++)
				{
					for (j = 0; j < 3; j++)
					{
						tmp[i][j].rotateZ();
						a[i][j][k] = tmp[i][j];
					}
				}
			}
			//  � ���������� ������� �������
			else if (idx == 2 || idx == 3)
			{
				// ����/�����
				if ((idx % 2) == 0)
				{
					j = 0;
				}
				else
				{
					j = 2;
				}
				for (i = 0; i < 3; i++)
				{
					for (k = 0; k < 3; k++)
					{
						tmp[k][2 - i] = a[i][j][k];
					}
				}
				for (i = 0; i < 3; i++)
				{
					for (k = 0; k < 3; k++)
					{
						tmp[i][k].rotateX();
						a[i][j][k] = tmp[i][k];
					}
				}
			}
			else if (idx == 4 || idx == 5)
			{
				// �������/�����
				if ((idx % 2) == 0)
				{
					i = 0;
				}
				else
				{
					i = 2;
				}
				for (j = 0; j < 3; j++)
					for (k = 0; k < 3; k++)
						tmp[k][2 - j] = a[i][j][k];
				for (j = 0; j < 3; j++)
				{
					for (k = 0; k < 3; k++)
					{
						tmp[j][k].rotateY();
				        a[i][j][k] = tmp[j][k];
			        }
		        }
			}
		}
	}
	void Rotate(int idx, int angle)
	{
		if (num == -1 || num == idx)
		{
			// ��������� �������
			rotate[idx] += angle;

			if (rotate[idx] % 90 != 0)
			{
				num = idx;
			}
			else
			{
				// ���� ���� ���� ������� 90, �� ������������ �� �������
				if ( num == 2 || num == 3)
				{
					rot90(idx, 1);
				}
				else
				{
					rot90(idx, -1);
				}
				rotate[idx] = 0;
				num = -1;
			}
		}
	}
};