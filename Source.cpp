#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
using namespace sf;
using namespace std;
#define PI 3.14159265359
Vector2f coords(double angle)
{
	angle = (angle / 180.0)*PI;
	Vector2f coord;
	coord.x = 300.0*cos(angle);
	coord.y = 300.0*sin(angle);
	return coord;
}
unsigned char& getCol(Color &col, int i)
{
	while (i < 0)i += 3;
	if (i % 3 == 0) return col.r;
	if (i % 3 == 1) return col.g;
	if (i % 3 == 2) return col.b;
}
void coladd(Color &col)
{
	int i;
	for (i = 2; !(i < 0	|| (getCol(col, i) == 0 && getCol(col, i + 1) != 0)); i--);
	if (getCol(col, i + 1) > getCol(col, i + 2)) getCol(col, i + 2)++;
	else getCol(col, i + 1)--;
}
void colminus(Color &col)
{
	int i;
	for (i = 0; !(i >= 3 || (getCol(col, i) == 0 && getCol(col, i - 1) != 0)); i++);
	if (getCol(col, i + 1) < getCol(col, i + 2)) getCol(col, i + 1)++;
	else getCol(col, i + 2)--;
}
VertexArray line(Lines, 2);
int main()
{
	
	RenderWindow window(VideoMode(700, 700), "SFML works!");
	window.setFramerateLimit(60);
	RectangleShape bg(Vector2f(700, 700));
	bg.setFillColor(Color::White);
	CircleShape shape(299);
	shape.setFillColor(Color(255,255,255,255));
	shape.setOutlineColor(Color(0,0,0,255));
	shape.setOutlineThickness(2);
	shape.setPosition(50, 50);
	shape.setPointCount(100);
	Color col = Color(255, 0, 0, 100);
	double n = 0;
	int nop;
	double dn = 0.0002;
	bool pause = 0;
	cin >> nop;
	while (window.isOpen())
	{
		n += dn*(!pause);
		if (int(n) == nop) n = 0.0;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::P)
					pause = !pause;
			
		}
		if (Keyboard::isKeyPressed(Keyboard::W))
			col.a += (col.a < 255);
		if (Keyboard::isKeyPressed(Keyboard::S))
			col.a -= (col.a > 0);
		if (Keyboard::isKeyPressed(Keyboard::Q))
			colminus(col);
		if (Keyboard::isKeyPressed(Keyboard::E))
			coladd(col);
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			if(dn > 0)dn *= 1.01;
			else if(dn < 0)dn /= 1.01;
			if (dn > -0.0001 && dn < 0)dn = 0.0001;
		}
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{
			if (dn > 0)dn /= 1.01;
			else if (dn < 0)dn *= 1.01;
			if (dn < 0.0001 && dn > 0)dn = -0.0001;
		}
		
		window.clear();
		window.draw(bg);
		window.draw(shape);
		for (int i = 0; i < nop; i++)
		{
			line[0] = Vertex(coords(double(i)*360.0/double(nop)) + Vector2f(350,350), col);
			line[1] = Vertex(coords(n*double(i)*360.0 / double(nop)) + Vector2f(350, 350), col);
			window.draw(line);
		}
		window.display();
	}

	return 0;
}
