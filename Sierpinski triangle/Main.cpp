#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;


void drawFractal(Vector2f top, Vector2f left, Vector2f right, int  depth);
Color randomColor();
vector<VertexArray> triangles;
unsigned int maxIterator = 5;
int main()
{
	srand(time(NULL));

	const unsigned width = 740;
	const unsigned height = 640;
	int depth = 0;

	sf::RenderWindow window(sf::VideoMode(width, height), "Sierpinski Triangle");

	drawFractal(Vector2f(0, height), Vector2f(width / 2, 5), Vector2f(width, height), depth);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		for (int i = 0; i < triangles.size();i++)
		{
			window.draw(triangles[i]);
		}

		window.display();
	}

	return 0;
}

void drawFractal(Vector2f left, Vector2f center, Vector2f right, int depth)
{

	if (depth < maxIterator)
	{
		VertexArray tTri(LinesStrip, 4);
		tTri[0].position = Vector2f(((left.x + center.x) / 2), (left.y + center.y) / 2);
		tTri[1].position = Vector2f((left.x + right.x) / 2, (center.y));
		tTri[2].position = Vector2f(((right.x + center.x) / 2), (right.y + center.y) / 2);
		tTri[3].position = Vector2f(center.x - 12, (right.y + center.y) / 2);

		tTri[0].color = Color::Red;
		tTri[1].color = Color::Green;
		tTri[2].color = Color::Blue;
		tTri[3].color = Color::Blue;


		triangles.push_back(tTri);

		VertexArray lTri(LineStrip, 4);
		lTri[0].position = Vector2f(left.x, (left.y + right.y) / 2);
		lTri[1].position = Vector2f((left.x + center.x) / 2, (center.y + left.y) / 2);
		lTri[2].position = Vector2f((right.x + left.x) / 2, (left.y + right.y) / 2);
		lTri[3].position = Vector2f(right.x, (left.y + right.y) / 2);

		lTri[0].color = Color::Red;
		lTri[1].color = Color::Green;
		lTri[2].color = Color::Blue;
		lTri[3].color = Color::Green;
		triangles.push_back(lTri);
	
		VertexArray rTri(LineStrip, 4);
		rTri[0].position = Vector2f(((left.x + right.x) / 2), (left.y + right.y) / 2);
		rTri[1].position = Vector2f((right.x + center.x) / 2, (center.y + right.y) / 2);
		rTri[2].position = Vector2f(right.x , (right.y + left.y) / 2);
		rTri[3].position = Vector2f(left.x, (right.y + left.y) / 2);

		rTri[0].color = Color::Red;
		rTri[1].color = Color::Green;
		rTri[2].color = Color::Blue;
		rTri[3].color = Color::Red;
		triangles.push_back(rTri);

		drawFractal(tTri[0].position, tTri[1].position, tTri[2].position, depth + 1);
		drawFractal(lTri[0].position, lTri[1].position, lTri[2].position, depth + 1);
	    drawFractal(rTri[0].position, rTri[1].position, rTri[2].position, depth + 1);
	}

}

Color randomColor()
{
	Color color(rand() % 255, rand() % 255, rand() % 255, 255);
	return color;
}
