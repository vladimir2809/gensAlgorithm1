#include <SFML/Graphics.hpp>
#include <vector>
#include "function.h"
#include "map.h"
#include "unit.h"
using namespace sf;
using namespace std;
int main()
{
	double time1 = 0, time2 = 0; // ��������� ��� �������
	srand(2);
	RenderWindow window(VideoMode(map_width * map_size+200, map_height * map_size), "Gens Algorithm ");
	Clock clock;
	Font font;
	font.loadFromFile("times-new-roman.ttf");//�������� ������ ������ ���� ������
	Text text("15155", font, 15);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	Map map;
	map.createMap();
	
	vector<Unit> units;
	for (int i = 0; i < 14; i++)// ������� �����
	{
		Unit oneUnit(map);
		units.push_back(oneUnit);
	}
	while (window.isOpen())
	{
		
		sf::Event event;
		clock.restart();
		time1 = clock.getElapsedTime().asMicroseconds();// �������� ����� � ������ �����
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		///////////////////////////////////////////////////////////////// �������
		if (Keyboard::isKeyPressed(Keyboard::Space)==false)
		{
			map.servis();
			unitsData.clear();
			for (int i = 0; i < units.size(); i++)
			{
				// ��������� ������ ������ � ������
				OneUnitData oneUnitData;
				oneUnitData.x = units[i].x;
				oneUnitData.y = units[i].y;
				oneUnitData.being = units[i].being;
				unitsData.push_back(oneUnitData);
				units[i].servis( map);// ������ �������� ��� ������
			}
		}
		if (PressMouseLeft(event)==true)// ���� ������ ����� ������ ����
		{
			for (int i = 0; i < units.size(); i++)
			{
				units[i].selectVisibleGenUnit(window,event);// ������� ����� ����� � �������� ��������������� ����
			}
		}


		////////////////////////���������
		window.clear();
		map.Draw(window);
		for (int i = 0; i < units.size(); i++)
		{
			
			units[i].Draw(window,text);
		}
		//DrawNumTxt(200,200, 20, window, text);
		window.draw(text);
		window.display();

		do ///////////////// ������
		{
			time2 = clock.getElapsedTime().asMicroseconds();// �������� ����� � ����� �����
			//speedGameRegulator.Servis(event);
			//Sleep (1);
		} while (time2 - time1<165000/*speedGameRegulator.gameDelay*/);// ���� ������� �� ������� ����� ������� � ������ ����� 
		//������ ������������� ����� �� ��������� ����� ������ 
	}

	return 0;
}