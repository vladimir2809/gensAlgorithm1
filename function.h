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
void DrawNumTxt(int x, int y, int mesNum, RenderWindow &window, Text &text)// ������� ������ ���� � ������ 
{
	text.setColor(Color(255, 255, 255));//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
	std::ostringstream numStr;    // �������� ����������
	numStr << trunc(mesNum);
	text.setString(numStr.str());
	text.setPosition(x, y);
	window.draw(text);
}
bool PressMouseLeft(Event event)// ��������� ��������� ������� ������� ����� ������ ����
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		//if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
		//			if (event.key.code == Mouse::Left)//� ������ �����
	{
		//std::cout<<"ckick mouse"<<"\n";
		return true;

	}
	return false;
}
void DrawLine(RenderWindow &window,int x, int y, int x1, int y1, Color color)// ��������� ��������� �����
{
	//������� ������ �����, �� ������� ����� ���������� �����:
	sf::VertexArray lines(sf::Lines, 16 /*���������� �����*/);

	//����� ��� ������ �� ����� ������ ���� �������:
	lines[0].position = sf::Vector2f(x, y);
	lines[1].position = sf::Vector2f(x1, y1);
	//� �.�.

	//����� ��� ������ ����� ��������� ����(��� ����� ��������� ���������):
	lines[0].color = color;
	lines[1].color = color;
	//� �.�.

	//� � ����� ������� ��� �� �����:
	window.draw(lines);
}