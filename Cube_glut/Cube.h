#include "Small_Cube.h" //заголовычный файл
class Cube
{
	SmallCube a[3][3][3]; // 27 частей 
	int rotate[6]; //  угол поворота каждой грани
	double sizeCube; // размер кубик-рубика
	unsigned int color[6]; // цвета граней
	int _angle[4];
	bool ok[4][4][4];
	SmallCube tmp[4][4];
public:
	int num; // храним номер грани, которая в данный момент поварачивается, или -1 если ничего не поварачивается
	Cube() {} // конструктор по умолчанию
	void clear(double size, unsigned int *RGB)
	{
		for (int i = 0; i < 6; i++)
		{
			rotate[i] = 0; // по умолчанию будет равно нолю
		}
		this->sizeCube = size; // размер куба 
		num = -1; // по умолчанию не какая гран не крутится
		int i, j, k;
		for (i = 0; i < 6; i++)
		{
			this->color[i] = RGB[i]; // заполняет массив цветов
		}
		// верх
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				a[i][j][2].setColor(0, RGB[0]);
			}
		}
		// низ
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				a[i][j][0].setColor(1, RGB[1]);
			}
		}		
		// спереди
		for (k = 0; k < 3; k++)
		{
			for (j = 0; j < 3; j++)
			{
				a[j][0][k].setColor(2, RGB[2]);
			}
		}
		// сзади
		for (k = 0; k < 3; k++)
		{
			for (j = 0; j < 3; j++)
			{
				a[j][2][k].setColor(3, RGB[3]);
			}
		}
		// слева
		for (i = 0; i < 3; i++)
		{
			for (k = 0; k < 3; k++)
			{
				a[0][k][i].setColor(4, RGB[4]);
			}
		}
		// справа
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
					ok[i][j][k] = true;  //заполняем  массив ok[][][] значение , показывает крутится обьект илил нет
				}
			}

		}
		if (num != -1) 
		{
			glPushMatrix();
			int i, j, k;

			if (num == 0 || num == 1) // одной плоскости есть два грани  
			{
				if ((num % 2) == 0) //опр какой из них крутится
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
						ok[i][j][k] = false; //грань к можно крутит
					}
				}
				
				glTranslated(sizeCube / 2, sizeCube / 2, 0);   // сдвигаемся к центру 
				glRotatef(rotate[num], 0, 0, 1);  // крутим
				glTranslated(-sizeCube / 2, -sizeCube / 2, 0);  // сдвигаемся обратно
				for (i = 0; i < 3; i++)
				{
					for (j = 0; j < 3; j++)
					{
						a[i][j][k].draw(sizeCube / 3 * i, sizeCube / 3 * j, sizeCube / 3 * k); //рисуем
					}
				}
			}
			//тоже самое остальными гранами
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
						// рисуем те детали, которые не поварачивались выше,ok[i][j][k] = true
						a[i][j][k].draw(sizeCube / 3 * i, sizeCube / 3 * j, sizeCube / 3 * k);
					}
				}
			}
		}
	}
	void rot90(int idx, int sign)
	{
		int i, j, k;
		// sign задаётся в зависимости он направления
		// sign = -1, sign = 1
		// если sign = -1, значит крутим 3 раза
		if (sign == -1)
		{
			sign = 3;
		}
		while (sign--)
		{
			if (idx == 0 || idx == 1)
			{
				// низ/верх
				if ((idx % 2) == 0)
				{
					k = 0;
				}
				else
				{
					k = 2;
				}
				// копируем повёрнутую на 90 градусов верхнюю/нижнюю грань
				// в массив tmp, затем грани присваиваем tmp
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
			//  с остальными четырмя гранями
			else if (idx == 2 || idx == 3)
			{
				// лево/право
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
				// впереди/сзади
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
			// обновляем поворот
			rotate[idx] += angle;

			if (rotate[idx] % 90 != 0)
			{
				num = idx;
			}
			else
			{
				// если угол стал кратным 90, то поварачиваем на массиве
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