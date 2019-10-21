#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
	const int countWall = 50;// ���������� ����
	const int map_width = 40;// ������ ���� 
	const int map_height = 20;// ������ ����
	const int map_size = 20;// ������ ������ 
	const int quantityFood = 10;
	const int quantityPoison = 10;
	int countFood = 0;
	int countPoison =0;
class Map
{

	
	int points[map_width][map_height];// ������ �����
public:
	void changePoint(int x, int y,int value)
	{
		points[x][y] = value;
	}
	void bePointEmpty(int x,int y)// ������� ������ ������ 
	{
		points[x][y] = 0;
	}
	int isPoint(int x, int y)// �������� ���� ����� ������
	{
		return points[x][y];
	}
	void createMap()// ������� ����� 
	{
		for (int i = 0; i < map_width; i++)
		{
			for (int j = 0; j < map_height; j++)
			{
				points[i][j] = 0;
			}
		}
		int rx = 0, ry = 0;
		for (int i = 0; i < countWall; i++)
		{
			
			do
			{
				rx = rand()%map_width;
				ry = rand() % map_height;
			}
			while (isPoint(rx,ry)!=0);
			points[rx][ry] = 1;
		}
		for (int i = 0; i < quantityFood; i++)
		{
			do
			{
				rx = rand() % map_width;
				ry = rand() % map_height;
			} while (isPoint(rx, ry) != 0);


			points[rx][ry] = 2;
			countFood++;
		}
		for (int i = 0; i < quantityPoison; i++)
		{
			do
			{
				rx = rand() % map_width;
				ry = rand() % map_height;
			} while (isPoint(rx, ry) != 0);


			points[rx][ry] = 3;
			countPoison++;
		}
	}
	void servis()// ����� ���������� ��������
	{
		int rx = 0, ry = 0;
	///	int r = rand() % 100;
		if (countFood<quantityFood)
		{
			do
			{
				rx = rand() % map_width;
				ry = rand() % map_height;
			} while (isPoint(rx, ry) != 0);
			
		
			points[rx][ry] = 2;
			countFood++;
		}
		if (countPoison<quantityPoison)
		{
			do
			{
				rx = rand() % map_width;
				ry = rand() % map_height;
			} while (isPoint(rx, ry) != 0);
			points[rx][ry] = 3;
			countPoison++;
		}

	}
	void Draw(RenderWindow &window)// ���������� �����, ��� � ��
	{
		RectangleShape rectangle(Vector2f(map_size, map_size));
		rectangle.setFillColor(Color(128, 128, 128));
		for (int i = 0; i < map_width; i++)
		{
			for (int j = 0; j < map_height; j++)
			{
				if (points[i][j] == 1)// ���� ����� 
				{
					rectangle.setFillColor(Color(128, 128, 128));
					rectangle.setPosition(i*map_size, j*map_size);
					window.draw(rectangle);
				}
				if (points[i][j] ==2)// ���� ���
				{
					rectangle.setFillColor(Color(0, 255, 0));
					rectangle.setPosition(i*map_size, j*map_size);
					window.draw(rectangle);
				}
				if (points[i][j] == 3)// ���� ��
				{
					rectangle.setFillColor(Color(255, 0, 0));
					rectangle.setPosition(i*map_size, j*map_size);
					window.draw(rectangle);
				}
			}
			DrawLine(window, map_width*map_size , 0,
				map_width*map_size, map_height*map_size, Color(128, 128, 128));
		}
	}
};