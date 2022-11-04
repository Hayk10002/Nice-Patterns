#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
using namespace sf;
using namespace std;
#define PI 3.14159265359
#define COLORS_CHANGING
Vector2f coords(double angle)
{
	angle = (angle / 180.0) * PI;
	Vector2f coord;
	coord.x = 300.0 * cos(angle);
	coord.y = 300.0 * sin(angle);
	return coord;
}
unsigned char& getCol(Color& col, int i)
{
	while (i < 0)i += 3;
	if (i % 3 == 0) return col.r;
	if (i % 3 == 1) return col.g;
	if (i % 3 == 2) return col.b;
}
void coladd(Color& col)
{
	int i;
	for (i = 2; !(i < 0 || (getCol(col, i) == 0 && getCol(col, i + 1) != 0)); i--);
	if (getCol(col, i + 1) > getCol(col, i + 2)) getCol(col, i + 2)++;
	else getCol(col, i + 1)--;
}
void colminus(Color& col)
{
	int i;
	for (i = 0; !(i >= 3 || (getCol(col, i) == 0 && getCol(col, i - 1) != 0)); i++);
	if (getCol(col, i + 1) < getCol(col, i + 2)) getCol(col, i + 1)++;
	else getCol(col, i + 2)--;
}
VertexArray line(Lines, 2);
#ifdef COLORS_CHANGING
vector<Color> allcolors(1530, Color::Black);
#endif
int main()
{
#ifdef COLORS_CHANGING
	Color c = Color::Red;
	for (int i = 0; i < 1530; i++)
	{
		allcolors[i] = c;
		coladd(c);
	}
	int opacity = 128;
	int colshift = 0;
#endif
	RenderWindow window(VideoMode(700, 700), "SFML works!");
	window.setFramerateLimit(60);
	CircleShape shape(299);
	shape.setFillColor(Color(255, 255, 255, 255));
	shape.setOutlineColor(Color(0, 0, 0, 255));
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
		n += dn * (!pause);
		if (int(n) == nop) n = 0.0;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::P)
					pause = !pause;
			if (event.type = Event::Resized)
			{
				View v(FloatRect(0, 0, window.getSize().x, window.getSize().y));
				window.setView(v);
			}

		}
		if (Keyboard::isKeyPressed(Keyboard::W))
#ifndef COLORS_CHANGING
			col.a += (col.a < 255);
#else
			opacity += (opacity < 255);
#endif
		if (Keyboard::isKeyPressed(Keyboard::S))
#ifndef COLORS_CHANGING
			col.a -= (col.a > 0);
#else
			opacity -= (opacity > 0);
#endif
		if (Keyboard::isKeyPressed(Keyboard::Q))
#ifndef COLORS_CHANGING
			colminus(col);
			colminus(col);
#else
			colshift -= 2;
			colshift += 1530;
			colshift %= 1530;

#endif
		if (Keyboard::isKeyPressed(Keyboard::E))
#ifndef COLORS_CHANGING
			coladd(col);
			coladd(col);
#else
			colshift += 2;
			colshift %= 1530;
#endif
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			if (dn > 0)dn *= 1.01;
			else if (dn < 0)dn /= 1.01;
			if (dn > -0.0001 && dn < 0)dn = 0.0001;
		}
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{
			if (dn > 0)dn /= 1.01;
			else if (dn < 0)dn *= 1.01;
			if (dn < 0.0001 && dn > 0)dn = -0.0001;
		}

		window.clear(Color::White);
		window.draw(shape);
		for (int i = 0; i < nop; i++)
		{
#ifdef COLORS_CHANGING
			Color col = allcolors[((i * 1530 / nop) + colshift) % 1530];
			col.a = opacity;
#endif
			line[0] = Vertex(coords(double(i) * 360.0 / double(nop)) + Vector2f(350, 350), col);
			line[1] = Vertex(coords(n * double(i) * 360.0 / double(nop)) + Vector2f(350, 350), col);
			window.draw(line);
		}
		window.display();
	}

	return 0;
}
