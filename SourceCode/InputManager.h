#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

class Player;

class InputManager {
public:
	int key_pressed;
	bool stop; //variable publica para que pueda modificarse
	InputManager();
	void Input(int key,bool stopx);
	void Mouse(sf::Vector2i vec); //tracking del mouse
	void ClearKeyPressed();
	char ReturnKeyValue();
};

#endif

