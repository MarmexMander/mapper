#define NOMINMAX
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include<fstream>
#include<SFML/Graphics.hpp>
using namespace sf;
Texture texture;
class sButton {
	Sprite s;
public:
	sButton(int TextureX, int TextureY, int x, int y) {
		s.setTexture(texture);
		s.setTextureRect(IntRect(TextureX * 32, TextureY * 32, 32, 32));
		s.setPosition(x, y);
	}
	bool isPresed() {
		Vector2i mouse = Mouse::getPosition();
		Vector2f begin = s.getPosition(), end = s.getPosition() + s.getScale();
		if (Mouse::isButtonPressed(Mouse::Left) && ((mouse.x >= begin.x) && (mouse.x <= end.x)) && ((mouse.y >= begin.y) && (mouse.y <= end.y))) {
			s.setColor(Color::Black);
			return 1;
		}
		else {
			s.setColor(Color::White);
			return 0;
		}
	}
	Sprite getSprite() {
		return s;
	}
};

struct coords {
	int x, y;
};
class tile {
	Sprite s;
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
		s.setPosition(x * 32, y * 32);
		return s;
	}
	void setTexture(int x, int y) {
		textureRectPos.x = x, textureRectPos.y = y;
		s.setTextureRect(IntRect(textureRectPos.x, textureRectPos.y, 32, 32));
	}
};
tile **tileMap;
int main() {
	if (!texture.loadFromFile("textures.png"))
		exit(-12);
	int tileMap_Y = 30, tileMap_X = 30, cameraOffset_X = 0, cameraOffset_Y = 0;
	sButton lButton(0, 2, 23*32, 1);
	sf::RenderWindow window{ {1280, 720}, "Window" };
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
			if (event.type == Event::KeyPressed) {
				switch (event.key.code) {
				case Keyboard::Left:
					if (cameraOffset_X != 0)
						cameraOffset_X--;
					break;
				case Keyboard::Right:
					if (cameraOffset_X != tileMap_X - ((tileMap_X < 20) ? tileMap_X : 20))
						cameraOffset_X++;
					break;
				case Keyboard::Up:
					if (cameraOffset_Y != 0)
						cameraOffset_Y--;
					break;
				case Keyboard::Down:
					if (cameraOffset_Y != tileMap_Y - ((tileMap_Y < 20) ? tileMap_Y : 20))
						cameraOffset_Y++;
					break;
				}

			}
			if (lButton.isPresed()) {

			}
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {
			Vector2i mousePos = Mouse::getPosition(window);
			mousePos.x /= 32;
			mousePos.y /= 32;
			mousePos.x += cameraOffset_X;
			mousePos.y += cameraOffset_Y;
			if ((mousePos.x < tileMap_X && mousePos.x > -1) && (mousePos.y < tileMap_Y && mousePos.y > -1))
				tileMap[mousePos.y][mousePos.x].setTexture(32, 32);
		}

		for (size_t j = cameraOffset_Y, jj = 0; j < ((tileMap_Y < 20) ? tileMap_Y : 20)+cameraOffset_Y; j++, jj++)
		{
			for (size_t i = cameraOffset_X, ii = 0; i < ((tileMap_X < 20) ? tileMap_X : 20)+cameraOffset_X; i++, ii++)
			{
				window.draw(tileMap[j][i].setPos(ii, jj));
			}
		}
		window.display();
		window.draw(lButton.getSprite());
		window.clear();
	}

	for (size_t i = 0; i < tileMap_Y; i++)
	{
		delete[]tileMap[i];
	}
	delete[]tileMap;
}