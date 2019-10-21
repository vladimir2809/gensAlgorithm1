#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
int numVisibleGenUnit=-1;// ����� ���� � �������� ��������������� ����
class Unit
{

	int gens[64];// ����
	int numGenReg;// ����� ���� ������� �����������
public:
	int x, y;//����������
	int HP;// �����
	bool being;// �������������
	int num;//����� �����
	int rotate;// ��������
	//int numVisibleGenUnit;
	void fillGens()// ��������� ���� ���������� �������
	{
		for (int i = 0; i < 64; i++)
		{
			gens[i] = rand() % 64;
		}
	}
	Unit(Map &map)// �����������
	{
		static int numSt = 0;
		num = numSt;
		rotate = 0;
		numSt++;
		numGenReg = 0;
		//numVisibleGenUnit = -1;
		for (int i = 0; i < countWall; i++)
		{
			int rx = 0, ry = 0;
			do
			{
				rx = rand() % map_width;
				ry = rand() % map_height;
			} while (map.isPoint(rx, ry) != 0);
			x = rx;
			y = ry;
		}
		HP = 90;
		being = true;
		fillGens();
	}

	void addHP(int value)// �������� ��������
	{
		HP += value;
		if (HP > 90) HP = 90;
	}
	bool isUnitInMap(int x, int y)// ���� ���� � � � �
	{
		
		for (int i = 0; i < unitsData.size(); i++)
		{
			if (unitsData[i].being == true)
			{
			//	cout << unitsData[i].x << "  " << unitsData[i].y << "\n";
				if (x == unitsData[i].x && y == unitsData[i].y)
				{
				//	cout << "yes";
					return true;
				}
			}
		}
		return false;
	}
	Vector2i vectorToDxDy(int vector)// ������ ������������� � dx & dy
	{
		int dx = 0, dy = 0;
		if (vector == 0)
		{
			dx = -1;
			dy = -1;
		}
		if (vector == 1)
		{
			dx = 0;
			dy = -1;
		}
		if (vector == 2)
		{
			dx = 1;
			dy = -1;
		}
		if (vector == 3)
		{
			dx = 1;
			dy = 0;
		}
		if (vector == 4)
		{
			dx = 1;
			dy = 1;
		}
		if (vector == 5)
		{
			dx = 0;
			dy = 1;
		}
		if (vector == 6)
		{
			dx = -1;
			dy = 1;
		}
		if (vector == 7)
		{
			dx = -1;
			dy = 0;
		}
		Vector2i result;
		result.x = dx;
		result.y = dy;
		return result;
	}
	void getRotate(int rot)// �������� �����
	{
		rotate += rot;
		rotate %= 8;
	}
	void move(int vector, Map &map)// ������� �����������
	{
		int dx = 0, dy = 0;
		vector %= 8;
		Vector2i d = vectorToDxDy(vector);
		x += d.x;
		y += d.y;
		if (map.isPoint(x, y) == 1
			|| x > map_width || x <0
			|| y >map_height || y < 0
			|| isUnitInMap(x, y) == true
			)
		{
			x -= d.x;
			y -= d.y;
		}
	}
	void toGrab(int vector, Map &map)// �������� �������� ������
	{
		vector %= 8;
		Vector2i d = vectorToDxDy(vector);
		if (map.isPoint(x + d.x, y + d.y) == 2)
		{
			map.bePointEmpty(x + d.x, y + d.y);
			countFood--;
			addHP(10);
		}
		if (map.isPoint(x + d.x, y + d.y) == 3)
		{
			map.changePoint(x + d.x, y + d.y, 2);
			countPoison--;
			countFood++;
		}
	}
	int gensServis()// ��������� ������� ����� ���������  ������� �� ���������� 
	{
		int result = -1;
		//	do
		//{
		result = gens[numGenReg];
		if (result < 32)
		{
			numGenReg++;
		}
		else
		{
			numGenReg += result;
		}
		numGenReg %= 64;
		//} while (result > 32);
		return result;
	}
	void controllKey(Map &map)// ���������� � ����������
	{
		if (Keyboard::isKeyPressed(Keyboard::Left)) move(7,map);
		if (Keyboard::isKeyPressed(Keyboard::Up)) move(1, map);
		if (Keyboard::isKeyPressed(Keyboard::Right)) move(3, map);
		if (Keyboard::isKeyPressed(Keyboard::Down)) move(5, map);
	}
	void servis(Map &map)// ������� ������������ �������� � �����
	{
		if (being == true)
		{
			if (numVisibleGenUnit == num)// ���� ��� ������
			{
				controllKey(map);// �� �� ����� ���������� ����������
			}
			////////////////////////////�������� ����� 
			int r = gensServis();
			//int r = rand() % 24;
			if (r < 8) move(r + rotate, map);
			if (r >= 8 && r < 16) getRotate(r - 8);
			if (r >= 16 && r < 24) toGrab((r - 16) + rotate, map);
			
			//HP--;
			if (map.isPoint(x, y) == 2)// ���� ������ �� ���
			{
				map.bePointEmpty(x, y);
				addHP(10);
				countFood--;
			}
			if (map.isPoint(x, y) == 3)// ���� ������ �� ��
			{
				map.bePointEmpty(x, y);
				countPoison--;
				being = false;
			}
			if (HP < 1)being = false;// ���� �������� ���


		}
	}
	void selectVisibleGenUnit(RenderWindow &window,Event &event)// ������� ���� 
	{
		//if (PressMouseLeft(event)==true)
		{
			Vector2i mousePos = Mouse::getPosition(window);//�������� ���������� �������
			if (mousePos.x >= x*map_size && mousePos.x < x*map_size + map_size
				&& mousePos.y >= y*map_size && mousePos.y < y*map_size + map_size)
			{
				numVisibleGenUnit = num;
			}
		}
	}
	void drawGens(RenderWindow &window, Text &text)// ���������� ����
	{
		RectangleShape rectangle(Vector2f(map_size, map_size));
		rectangle.setFillColor(Color(255, 128, 0));
		int k = 0;
		
		for (int j = 0; j< 8; j++)
		{
			for (int i = 0; i < 8; i++)
			{
				if (numGenReg == k)
				{
					rectangle.setPosition(i * 20+map_width*map_size+20, j * 20);
					window.draw(rectangle);
				}
				DrawNumTxt(i * 20 + map_width*map_size+20, j * 20, gens[k], window, text);
				k++;
			}
		}
		
	}
	void Draw(RenderWindow &window,Text &text)// ���������� ����
	{
		if (being == true)
		{
			RectangleShape rectangle(Vector2f(map_size, map_size));
			if (numVisibleGenUnit != num)
			{
				rectangle.setFillColor(Color(128, 128, 255));
			}
			else
			{
				rectangle.setFillColor(Color(255, 128, 255));
			}
			rectangle.setPosition(x*map_size, y*map_size);
			window.draw(rectangle);
			DrawNumTxt(x*map_size + 2, y*map_size + 1, HP, window, text);
			if (PressMouseLeft)
			{
				//Vector2i mousePos = Mouse::getPosition(window);//�������� ���������� �������
				if (numVisibleGenUnit==num)
				{
					drawGens(window, text);
				}
			}
		}
	}
	
};