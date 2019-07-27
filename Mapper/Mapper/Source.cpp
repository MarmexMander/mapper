#define NOMINMAX
#define TILESET_WIDTH 23
#define TILESET_HEIGHT 21
#define TILE_HEIGHT 32
#define TILE_WIDTH 32
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include<fstream>
#include<SFML/Graphics.hpp>
using namespace sf;
Texture texture;
Font font;
class enterNum {
	Text t;
	RectangleShape box;
	int buffInt;
	bool fokusLost;
public:
	int enter(Event event, Vector2i mouse) {
		Vector2f begin = box.getPosition(), end = box.getPosition();
		end.x += box.getSize().x;
		end.y += box.getSize().x;
		if (((mouse.x >= begin.x) && (mouse.x <= end.x)) && ((mouse.y >= begin.y) && (mouse.y <= end.y))) {
			if (fokusLost)
				buffInt = 0;
			fokusLost = 0;
			switch (event.key.code) {
			case Keyboard::Num0:
				buffInt *= 10;
				break;
			case Keyboard::Numpad0:
				buffInt *= 10;
				break;
			case Keyboard::Num1:
				buffInt *= 10;
				buffInt += 1;
				break;
			case Keyboard::Numpad1:
				buffInt *= 10;
				buffInt += 1;
				break;
			case Keyboard::Num2:
				buffInt *= 10;
				buffInt += 2;
				break;
			case Keyboard::Numpad2:
				buffInt *= 10;
				buffInt += 2;
				break;
			case Keyboard::Num3:
				buffInt *= 10;
				buffInt += 3;
				break;
			case Keyboard::Numpad3:
				buffInt *= 10;
				buffInt += 3;
				break;
			case Keyboard::Num4:
				buffInt *= 10;
				buffInt += 4;
				break;
			case Keyboard::Numpad4:
				buffInt *= 10;
				buffInt += 4;
				break;
			case Keyboard::Num5:
				buffInt *= 10;
				buffInt += 5;
				break;
			case Keyboard::Numpad5:
				buffInt *= 10;
				buffInt += 5;
				break;
			case Keyboard::Num6:
				buffInt *= 10;
				buffInt += 6;
				break;
			case Keyboard::Numpad6:
				buffInt *= 10;
				buffInt += 6;
				break;
			case Keyboard::Num7:
				buffInt *= 10;
				buffInt += 7;
				break;
			case Keyboard::Numpad7:
				buffInt *= 10;
				buffInt += 7;
				break;
			case Keyboard::Num8:
				buffInt *= 10;
				buffInt += 8;
				break;
			case Keyboard::Numpad8:
				buffInt *= 10;
				buffInt += 8;
				break;
			case Keyboard::Num9:
				buffInt *= 10;
				buffInt += 9;
				break;
			case Keyboard::Numpad9:
				buffInt *= 10;
				buffInt += 9;
				break;
			case Keyboard::Enter:
				buffInt = 0;
				break;
			case Keyboard::BackSpace:
				buffInt /= 10;
				break;
			}
		}
		t.setString(std::to_string(buffInt));
		return buffInt;
	}
	enterNum(IntRect _box, Color col = Color::Black, Color fCol = Color::White) {
		Vector2f tmp;
		buffInt = 0;
		tmp.x = _box.left;
		tmp.y = _box.top;
		t.setPosition(tmp);
		box.setPosition(tmp);
		tmp.x = _box.width;
		tmp.y = _box.height;
		box.setSize(tmp);
		box.setFillColor(col);//Макс. число / Дефайн размера тайла
		t.setFillColor(fCol);
		t.setFont(font);
	}
	RectangleShape getBox() {
		return box;
	}
	Text getText() {
		return t;
	}
	void setInt(int val) {
		buffInt = val;
		t.setString(std::to_string(buffInt));
	}
	void checkFocus(Vector2i mouse) {
		Vector2f begin = box.getPosition(), end = box.getPosition();
		end.x += box.getSize().x;
		end.y += box.getSize().x;
		if (fokusLost == 0)
			if (((mouse.x >= begin.x) && (mouse.x <= end.x)) && ((mouse.y >= begin.y) && (mouse.y <= end.y)))
				fokusLost = 0;
			else
				fokusLost = 1;
	}
};
class sButton {
	Sprite s;
public:
	sButton(int TextureX, int TextureY, int x, int y) {
		s.setTexture(texture);
		s.setTextureRect(IntRect(TextureX * 32, TextureY * 32, 32, 32));
		s.setPosition(x, y);
	}
	bool isPresed(Vector2i mouse) {
		Vector2f begin = s.getPosition(), end = s.getPosition();
		end.x += s.getTextureRect().width;
		end.y += s.getTextureRect().height;
		if (Mouse::isButtonPressed(Mouse::Left) && ((mouse.x >= begin.x) && (mouse.x <= end.x)) && ((mouse.y >= begin.y) && (mouse.y <= end.y))) {
			s.setColor(Color::Magenta);
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
class Label {
public:
	std::string text;	//Текст
protected:
	double x;		//Координата x
	double y;		//Координата y

	Text TXT;		//Отображаемый текст

public:
	Label(double _x = 0, double _y = 0, std::string _text = "Текст")
	{

		x = _x;
		y = _y;
		text = _text;								// загружает текст
		TXT.setFont(font);							// загружаем фрифт
		TXT.setCharacterSize(20); 					// в пикселях, а не точках!
		TXT.setFillColor(Color::White);					// устанавливаем цвет выводимого текста
		TXT.setPosition(x, y);						// позиция текста
	}
	Text displayText()
	{
		TXT.setString(text);						// загружаем в выводимый текст загружаемый текст
		return TXT;
	}
};

class Button : public Label {
protected:
	double width;		// Ширина Кнопки
	double height;		// Высота Кнопки
	RectangleShape BOX;	// Создаем прямоугольник с размером width, height
public:
	Button(double _x = 0, double _y = 0, double _width = 150, double _height = 30, std::string _text = "Кнопка")
	{

		x = _x;
		y = _y;
		width = _width;
		height = _height;
		text = _text;								// загружает текст
		TXT.setFont(font);							// загружаем фрифт
		TXT.setCharacterSize(20); 					// в пикселях, а не точках!
		TXT.setFillColor(Color::White);					// устанавливаем цвет выводимого текста
		TXT.setPosition(x, y);						// позиция текста

		BOX.setSize(Vector2f(width, height));		// размер кнопки
		BOX.setPosition(x, y);						// координаты кнопки
		BOX.setFillColor(sf::Color(133, 133, 133));	// цвет кнопки
		BOX.setOutlineThickness(2);					// Контур X пикселей
		BOX.setOutlineColor(Color(66, 66, 66));		// Цвет контура
	}
	//Проверка нажатия на кнопку
	bool select(Vector2i _mouse)
	{
		if ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height)) {
			return  true;
		}
		else {
			return false;
		}
	}
	//Вывод Текста
	Text displayText()
	{
		TXT.setString(text);  // загружаем в выводимый текст загружаемый текст
		return TXT;
	}
	//Вывод кнопки
	RectangleShape displayButton()
	{
		return BOX;
	}


};
class Input : public Button {
protected:
	bool focus;
public:
	Input(double _x = 0, double _y = 0, double _width = 150, double _height = 30, std::string _text = "")
	{
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		text = _text;								// загружает текст
		focus = false;								// фокус поля ввода

		TXT.setFont(font);							// загружаем фрифт
		TXT.setCharacterSize(20); 					// в пикселях, а не точках!
		TXT.setFillColor(Color::Black);					// устанавливаем цвет выводимого текста
		TXT.setPosition(x, y);						// позиция текста

		BOX.setSize(Vector2f(width, height));		// размер поля ввода
		BOX.setPosition(x, y);						// координаты поля ввода
		BOX.setFillColor(Color::White);	// цвет кнопки
	}
	//метод .reText( char ) изменяет текст внутри класса Типа данных Input
	void reText(char _tmp)
	{
		text.erase(text.size() - 1);

		if (_tmp != 8) {
			text += _tmp;
		}
		else {
			if (text.size() > 0) {
				text.erase(text.size() - 1);
			}

		}
		text += "|";
		TXT.setString(text);
	}

	// Проверка Фокуса Input
	bool select()
	{
		return focus;
	}

	// Установка Фокуса Input
	bool select(Vector2i _mouse)
	{
		if ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height)) { 	//Если нажат клаиша над объектом Input...
			focus = true;																	   	// Фокус true
			text += "|";																		// В конец строки добаляем | (что бы понимать что input в фокусе)
		}
		else {																				//...Иначе если нажатие произошло не над объектом, то...
			if (text.size() > 0) {																// проверка последнего символа(иначе вылетает)
				if (text[text.size() - 1] == 124) {													// если символ | ...
					text.erase(text.size() - 1);														// ... то удаляем его
				}
			}
			focus = false;																		// устанавливаем фокус false
		}
		return focus;
	}

	//Вывод Текста
	Text displayText()
	{
		TXT.setString(text);						// загружаем в выводимый текст загружаемый текст
		return TXT;
	}

	//Вывод фона Input
	RectangleShape displayBOX()
	{
		return BOX;
	}

	//Для того, что бы считать текст с поля Ipnut необходимо пременить  readText() который возвращает string
	std::string readText()
	{
		if (text[text.size() - 1] == 124) { 	// удаляем (если есть) символ |
			text.erase(text.size() - 1);
		}
		return text;
	}
};

class boxButton {
	RectangleShape box;
	Text t;
	Color c;
public:
	boxButton(IntRect _box, char* text, Color col = Color::Color(100, 100, 100, 255), Color fCol = Color::White) {
		Vector2f tmp;
		tmp.x = _box.left;
		tmp.y = _box.top;
		t.setPosition(tmp);
		box.setPosition(tmp);
		tmp.x = _box.width;
		tmp.y = _box.height;
		box.setSize(tmp);
		box.setFillColor(col);//Макс. число / Дефайн размера тайла
		t.setFillColor(fCol);
		t.setString(text);
		c = col;
		t.setFont(font);
	}
	bool isPresed(Vector2i mouse) {
		Vector2f begin = box.getPosition(), end = box.getPosition();
		end.x += box.getSize().x;
		end.y += box.getSize().x;
		if (Mouse::isButtonPressed(Mouse::Left) && ((mouse.x >= begin.x) && (mouse.x <= end.x)) && ((mouse.y >= begin.y) && (mouse.y <= end.y))) {
			box.setFillColor(Color::Black);
			return 1;
		}
		else {
			box.setFillColor(c);
			return 0;
		}
	}
	RectangleShape getBox() {
		return box;
	}
	Text getText() {
		return t;
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
	bool getSolid() {
		return solid;
	}
	coords getAltTexture() {
		return altTextureRectPos;
	}
	short int getType() {
		return type;
	}
	tile* getLinkedTile() {
		return linkedTile;
	}
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
		s.setTextureRect(IntRect(textureRectPos.x * 32, textureRectPos.y * 32, 32, 32));
	}
	void setTexture(coords xy) {
		textureRectPos.x = xy.x, textureRectPos.y = xy.y;
		s.setTextureRect(IntRect(textureRectPos.x * 32, textureRectPos.y * 32, 32, 32));
	}
	Sprite getSprite() {
		return s;
	}
	coords getTexture() {
		return textureRectPos;
	}
	void setAltTexture(coords xy) {
		altTextureRectPos.x = xy.x, altTextureRectPos.y = xy.y;
	}

	void setSolid(bool _solid) {
		solid = _solid;
	}

	void setType(short int _type) {
		type = _type;
	}

	void setLinkedTile(tile *_linkedTile) {
		linkedTile = _linkedTile;
	}
};

struct tileInfo {
	coords textureRectPos;
	coords altTextureRectPos;
	short int type = 1;
	tile *linkedTile;
	bool solid;
};

tile **tileMap = NULL;

void saveMap(int x, int y, char* name = (char*)"map") {
	int i;
	tile buffTile;
	coords tempMapSize;
	std::ofstream save;
	tileInfo buff;
	save.open(std::string(name)+".map", std::ofstream::trunc);
	if (save.is_open()) {
		for (size_t j = 0; j < y; j++)
		{
			for (size_t i = 0; i < x; i++)
			{
				buff.textureRectPos = tileMap[j][i].getTexture();
				buff.altTextureRectPos = tileMap[j][i].getAltTexture();
				buff.linkedTile = tileMap[j][i].getLinkedTile();
				buff.type = tileMap[j][i].getType();
				buff.solid = tileMap[j][i].getSolid();
				save.write((char*)&buff, sizeof(tileInfo));
			}
		}
		save.close();
		save.open(std::string(name) + ".size", std::ofstream::trunc);
		if (!save.is_open())
			std::cout << "Err" << std::endl;
		tempMapSize.x = x;
		tempMapSize.y = y;
		save.write((char*)&tempMapSize, sizeof(coords));
	}
	save.close();
}

int main() {
	if (!texture.loadFromFile("textures.png"))
		exit(-12);
	font.loadFromFile("font.ttf");
	int tileMap_Y = 30, tileMap_X = 30, cameraOffset_X = 0, cameraOffset_Y = 0, chosenPalete = 0;
	RenderWindow window{ {1280, 720}, "Window" };
	if (1) {
		Text lable;
		lable.setFont(font);
		lable.setPosition(550, 60);
		lable.setString("Enter card size (tiles) or load from file.");
		enterNum x(IntRect(128, 120, 152, 32), Color::Color(100, 100, 100, 255), Color::White), y(IntRect(128 + 152 + 152, 120, 152, 32), Color::Color(100, 100, 100, 255), Color::White);
		boxButton newMap(IntRect(128, 170, 152, 32), (char*)"Create"), loadMap(IntRect(128 + 152 + 152, 170, 152, 32), (char*)"Load");
		Input mapName(32, 64, 128, 20);
		Event ev;
		bool load;
		while (1) {
			Vector2i mousePos = Mouse::getPosition(window);
			window.pollEvent(ev);
			if (ev.type == Event::KeyPressed) {
				tileMap_X = x.enter(ev, mousePos);
				tileMap_Y = y.enter(ev, mousePos);
			}
			if (newMap.isPresed(mousePos)) {
				load = 0;
				break;
			}
			if (loadMap.isPresed(mousePos)) {
				load = 1;
				break;
			}
			window.clear();
			window.draw(lable);
			window.draw(x.getBox());
			window.draw(x.getText());
			window.draw(y.getBox());
			window.draw(y.getText());
			window.draw(newMap.getBox());
			window.draw(newMap.getText());
			window.draw(loadMap.getBox());
			window.draw(loadMap.getText());
			window.display();
		}
		if (load) {
			Label loadLable(32, 32, "Enter map name:");
			std::string path;
			while (1) {
				if (window.pollEvent(ev)) {
					if (ev.type == sf::Event::TextEntered) {
						if (mapName.select()) {
							mapName.reText(ev.text.unicode);
						}
					}
					if (ev.type == sf::Event::MouseButtonPressed)
					{
						if (ev.mouseButton.button == sf::Mouse::Left)
						{
							Vector2i mouse = Mouse::getPosition(window);
							mapName.select(mouse);	  		//поле ввода

						}
					}
					if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Enter)
						break;
				}

				window.draw(mapName.displayButton());
				window.draw(mapName.displayText());
				window.display();
				window.clear();
			}
			path = mapName.readText();
			int i;
			tile buffTile;
			coords tempMapSize;
			std::ifstream load;
			load.open(path + ".size");
			if (load.is_open()) {

				load.read((char*)&tempMapSize, sizeof(coords));
				tileMap_X = tempMapSize.x;
				tileMap_Y = tempMapSize.y;
				load.close();
				tileInfo buff;
				load.open(path + ".map");
				if (load.is_open()) {
					if (tileMap != NULL) {
						for (size_t i = 0; i < tileMap_Y; i++)
						{
							delete[]tileMap[i];
						}
						delete[]tileMap;
					}
					tileMap = new tile*[tileMap_Y];
					for (size_t i = 0; i < tileMap_Y; i++)
					{
						tileMap[i] = new tile[tileMap_X];
					}
					for (size_t j = 0; j < tileMap_Y; j++)
					{
						for (size_t i = 0; i < tileMap_X; i++)
						{
							load.read((char*)&buff, sizeof(tileInfo));//НЕ ВИКАЧУЄ З ФАЙЛА КАРТИ НІЧОГО(ТІЛЬКИ З ФАЙЛА З РАЗМЕРОМ КАРТИ)
							tileMap[j][i].setTexture(buff.textureRectPos);
							tileMap[j][i].setAltTexture(buff.altTextureRectPos);
							tileMap[j][i].setLinkedTile(buff.linkedTile);
							tileMap[j][i].setType(buff.type);
							tileMap[j][i].setSolid(buff.solid);
						}
					}
				}
			}
			load.close();
		}
		else
		{
			tileMap = new tile*[tileMap_Y];
			for (size_t i = 0; i < tileMap_Y; i++)
			{
				tileMap[i] = new tile[tileMap_X];
			}
		}
	}
	sButton lButton(0, 0, 23 * 32, 32), rButton(0, 0, 25 * 32, 32);
	boxButton save(IntRect(32, 32 * 21, 128, 32), (char*)"SAVE");
	enterNum set(IntRect(27 * 32, 32, 64, 32), Color::Green, Color::Black);
	tile palette;
	palette.setPos(24, 1);
	palette.setTexture(1, 0);
	while (window.isOpen())
	{
		Vector2i mousePos = Mouse::getPosition(window);
		set.checkFocus(mousePos);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed || event.type == Event::MouseButtonReleased) {
				if (save.isPresed(mousePos)) {
						boxButton ok(IntRect(520, 350, 120, 30), (char*)"OK"), cancle(IntRect(660, 350, 120, 30), (char*)"Cancle");
						Input name(520, 310, 260, 30);
						Event saveDialEvent;
						bool ext = 0;
						while (true)
						{
							while (window.pollEvent(saveDialEvent)) {
								Vector2i mouse = Mouse::getPosition(window);
								if (saveDialEvent.type == sf::Event::TextEntered) {
									if (name.select()) {
										name.reText(saveDialEvent.text.unicode);
									}
								}
								if (saveDialEvent.type == sf::Event::MouseButtonPressed)
								{
									if (saveDialEvent.mouseButton.button == sf::Mouse::Left)
									{
										name.select(mouse);
										if (ok.isPresed(mouse)) {
											saveMap(tileMap_X, tileMap_Y, (char*)name.readText().c_str());
											Mouse::setPosition(Mouse::getPosition()+Vector2i(100,0));
											ext = 1;
										}
										if (cancle.isPresed(mouse))
											ext = 1;
									}
								}
							}
							if (ext)
								break;
							window.clear();
							window.draw(ok.getBox());
							window.draw(ok.getText());
							window.draw(cancle.getBox());
							window.draw(cancle.getText());
							window.draw(name.displayButton());
							window.draw(name.displayText());
							window.display();
						}
				}
				if (lButton.isPresed(mousePos)) {
					if (chosenPalete != 0)
						chosenPalete--;
					set.setInt(chosenPalete);
					int x, y;
					y = chosenPalete / TILESET_WIDTH;
					x = chosenPalete - (y * TILESET_WIDTH);
					palette.setTexture(x, y);
				}
				if (rButton.isPresed(mousePos)) {
					if (chosenPalete != TILESET_WIDTH * TILESET_HEIGHT)
						chosenPalete++;
					set.setInt(chosenPalete);
					int x, y;
					y = chosenPalete / TILESET_WIDTH;
					x = chosenPalete - (y * TILESET_WIDTH);
					palette.setTexture(x, y);
				}
			}
			if (event.type == Event::KeyPressed) {
				chosenPalete = set.enter(event, mousePos);
				int x, y;
				y = chosenPalete / TILESET_WIDTH;
				x = chosenPalete - (y * TILESET_WIDTH);
				palette.setTexture(x, y);
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
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			mousePos.x /= 32;
			mousePos.y /= 32;
			mousePos.x += cameraOffset_X;
			mousePos.y += cameraOffset_Y;
			if ((mousePos.x < 20 && mousePos.x > -1) && (mousePos.y < 20 && mousePos.y > -1)) {
				tileMap[mousePos.y][mousePos.x].setTexture(palette.getTexture());
			}
		}

		for (size_t j = cameraOffset_Y, jj = 0; j < ((tileMap_Y < 20) ? tileMap_Y : 20) + cameraOffset_Y; j++, jj++)
		{
			for (size_t i = cameraOffset_X, ii = 0; i < ((tileMap_X < 20) ? tileMap_X : 20) + cameraOffset_X; i++, ii++)
			{
				window.draw(tileMap[j][i].setPos(ii, jj));
			}
		}
		window.draw(save.getBox());
		window.draw(save.getText());
		window.draw(set.getBox());
		window.draw(set.getText());
		window.draw(palette.getSprite());
		window.draw(lButton.getSprite());
		window.draw(rButton.getSprite());
		window.display();
		window.clear();
	}

	for (size_t i = 0; i < tileMap_Y; i++)
	{
		delete[]tileMap[i];
	}
	delete[]tileMap;
}
