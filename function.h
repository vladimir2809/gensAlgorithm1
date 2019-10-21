#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
using namespace sf;
struct OneUnitData{
	int x, y;
	bool being;
};

vector<OneUnitData> unitsData;
void DrawNumTxt(int x, int y, int mesNum, RenderWindow &window, Text &text)// функци€ вывода цифр в тексте 
{
	text.setColor(Color(255, 255, 255));//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	std::ostringstream numStr;    // объ€вили переменную
	numStr << trunc(mesNum);
	text.setString(numStr.str());
	text.setPosition(x, y);
	window.draw(text);
}
bool PressMouseLeft(Event event)// процедура обработки событи€ нажатие левой кнопки мыщи
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		//if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
		//			if (event.key.code == Mouse::Left)//а именно лева€
	{
		//std::cout<<"ckick mouse"<<"\n";
		return true;

	}
	return false;
}
void DrawLine(RenderWindow &window,int x, int y, int x1, int y1, Color color)// процедура рисовани€ линии
{
	//создаем массив точек, по которым будут рисоватьс€ линии:
	sf::VertexArray lines(sf::Lines, 16 /*количество точек*/);

	//далее дл€ каждой из точек задаем свою позицию:
	lines[0].position = sf::Vector2f(x, y);
	lines[1].position = sf::Vector2f(x1, y1);
	//и т.д.

	//далее дл€ каждой точки указываем цвет(так можно создавать градиенты):
	lines[0].color = color;
	lines[1].color = color;
	//и т.д.

	//и в конце выводим все на экран:
	window.draw(lines);
}