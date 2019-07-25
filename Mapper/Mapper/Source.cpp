#define NOMINMAX
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include<fstream>
#include<SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

using namespace sf;

struct coords {
	int x, y;
};
class tile {
	Sprite s;
	Texture texture;
	coords textureRectPos;
	coords altTextureRectPos;
	short int type = 1;
	tile *linkedTile;
	bool solid;
	//void pUse() {
	//	//що буде виповнятися при використанні цього тайла
	//	case 3:
	//		buffcolor = color;
	//		bufftexture = texture;
	//		color = altcolor;
	//		texture = alttexture;
	//		altcolor = buffcolor;
	//		alttexture = bufftexture;
	//		linkedtile->use;
	//}
public:
	tile() {
		textureRectPos.x = 0, textureRectPos.y = 0;
		texture.loadFromFile("Textures/tileset.png");
		s.setTexture(texture);
		s.setTextureRect(IntRect(textureRectPos.x, textureRectPos.y, 32, 32));
	}
	void use() {
		coords buffTextureRectPos;
		switch (type) {
		case 2://Door
			if (solid)
				solid = 0;
			else
				solid = 1;
			buffTextureRectPos = textureRectPos;
			textureRectPos = altTextureRectPos;
			altTextureRectPos = buffTextureRectPos;
			break;
		case 3://Button
			buffTextureRectPos = textureRectPos;
			textureRectPos = altTextureRectPos;
			altTextureRectPos = buffTextureRectPos;
			linkedTile->use();
			break;
		}
	}
	Sprite setPos(int x, int y) {
		s.setPosition(x*32, y*32);
		return s;
	}
	void setTexture(int x, int y) {
		textureRectPos.x = x, textureRectPos.y = y;
		s.setTextureRect(IntRect(textureRectPos.x, textureRectPos.y, 32, 32));
	}
};
tile **tileMap;
int main() {
	int tileMap_Y = 20, tileMap_X = 20;
	sf::RenderWindow window{ {800, 600}, "Window" };
	tileMap = new tile*[tileMap_Y];
	RectangleShape tileRect;
	for (size_t i = 0; i < tileMap_Y; i++)
	{
		tileMap[i] = new tile[tileMap_X];
	}

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {
			Vector2i mousePos = Mouse::getPosition(window);
			mousePos.x /= 32;
			mousePos.y /= 32;
			tileMap[mousePos.x][mousePos.y].setTexture(32,32);
		}

		for (size_t j = 0; j < tileMap_Y; j++)
		{
			for (size_t i = 0; i < tileMap_X; i++)
			{
				window.draw(tileMap[i][j].setPos(i,j));
			}
		}
		window.display();
		window.clear();
	}

	for (size_t i = 0; i < tileMap_Y; i++)
	{
		delete[]tileMap[i];
	}
	delete[]tileMap;
}