#include <SFML/Graphics.hpp>
#include <vector>
#include "function.h"
#include "map.h"
#include "unit.h"
using namespace sf;
using namespace std;
int main()
{
	double time1 = 0, time2 = 0; // переменые для таймера
	srand(2);
	RenderWindow window(VideoMode(map_width * map_size+200, map_height * map_size), "Gens Algorithm ");
	Clock clock;
	Font font;
	font.loadFromFile("times-new-roman.ttf");//передаем нашему шрифту файл шрифта
	Text text("15155", font, 15);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	Map map;
	map.createMap();
	
	vector<Unit> units;
	for (int i = 0; i < 14; i++)// создаем юниты
	{
		Unit oneUnit(map);
		units.push_back(oneUnit);
	}
	while (window.isOpen())
	{
		
		sf::Event event;
		clock.restart();
		time1 = clock.getElapsedTime().asMicroseconds();// присвоим время в начале цикла
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		///////////////////////////////////////////////////////////////// сервисы
		if (Keyboard::isKeyPressed(Keyboard::Space)==false)
		{
			map.servis();
			unitsData.clear();
			for (int i = 0; i < units.size(); i++)
			{
				// заполняем массив данные о юнитах
				OneUnitData oneUnitData;
				oneUnitData.x = units[i].x;
				oneUnitData.y = units[i].y;
				oneUnitData.being = units[i].being;
				unitsData.push_back(oneUnitData);
				units[i].servis( map);// делаем действия для юнитов
			}
		}
		if (PressMouseLeft(event)==true)// если нажата левая кнопка мыши
		{
			for (int i = 0; i < units.size(); i++)
			{
				units[i].selectVisibleGenUnit(window,event);// выбрать номер юнита у которого просмтаривается гены
			}
		}


		////////////////////////отрисовка
		window.clear();
		map.Draw(window);
		for (int i = 0; i < units.size(); i++)
		{
			
			units[i].Draw(window,text);
		}
		//DrawNumTxt(200,200, 20, window, text);
		window.draw(text);
		window.display();

		do ///////////////// таймер
		{
			time2 = clock.getElapsedTime().asMicroseconds();// присвоив время в конце цикла
			//speedGameRegulator.Servis(event);
			//Sleep (1);
		} while (time2 - time1<165000/*speedGameRegulator.gameDelay*/);// пока разница во времени между началом и концом цикла 
		//меньше определенного цисла то считываем время заного 
	}

	return 0;
}