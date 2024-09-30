#include "InputManager.h"
#include <iostream>

InputManager::InputManager() {
	
}

void InputManager::Input(int key,bool stopx){
	key_pressed = key; //guardo la tecla para que la use player
	stop = stopx;
	
	//para llevar registro del funcionamiento del input
//	switch(key){
//		case sf::Keyboard::Up:{
//			std::cout<<"UP";
//			break;
//		}
//		case sf::Keyboard::Down:{
//			std::cout<<"Down";
//			break;
//		}
//		case sf::Keyboard::Left:{
//			std::cout<<"left";
//			break;
//		}
//		case sf::Keyboard::Right:{
//			std::cout<<"Right";
//			break;
//		}
//	}
}

void InputManager::Mouse(sf::Vector2i vec){
//	std::cout << "X:" << vec.x << "  Y:"<< vec.y << std::endl;
}

void InputManager::ClearKeyPressed(){
	this->key_pressed = 0;
}

char InputManager::ReturnKeyValue(){
	switch(key_pressed){
///		characters
		case sf::Keyboard::A:{
			return 'A';
			break;
		}
		case sf::Keyboard::B:{
			return 'B';
			break;
		}
		case sf::Keyboard::C:{
			return 'C';
			break;
		}
		case sf::Keyboard::D:{
			return 'D';
			break;
		}
		case sf::Keyboard::E:{
			return 'E';
			break;
		}
		case sf::Keyboard::F:{
			return 'F';
			break;
		}
		case sf::Keyboard::G:{
			return 'G';
			break;
		}
		case sf::Keyboard::H:{
			return 'H';
			break;
		}
		case sf::Keyboard::I:{
			return 'I';
			break;
		}
		case sf::Keyboard::J:{
			return 'J';
			break;
		}
		case sf::Keyboard::K:{
			return 'K';
			break;
		}
		case sf::Keyboard::L:{
			return 'L';
			break;
		}
		case sf::Keyboard::M:{
			return 'M';
			break;
		}
		case sf::Keyboard::N:{
			return 'N';
			break;
		}
		case sf::Keyboard::O:{
			return 'O';
			break;
		}
		case sf::Keyboard::P:{
			return 'P';
			break;
		}
		case sf::Keyboard::Q:{
			return 'Q';
			break;
		}
		case sf::Keyboard::R:{
			return 'R';
			break;
		}
		case sf::Keyboard::S:{
			return 'S';
			break;
		}
		case sf::Keyboard::T:{
			return 'T';
			break;
		}
		case sf::Keyboard::U:{
			return 'U';
			break;
		}
		case sf::Keyboard::V:{
			return 'V';
			break;
		}
		case sf::Keyboard::W:{
			return 'W';
			break;
		}
		case sf::Keyboard::X:{
			return 'X';
			break;
		}
		case sf::Keyboard::Y:{
			return 'Y';
			break;
		}
		case sf::Keyboard::Z:{
			return 'Z';
			break;
		}
		
///		numbers
		case sf::Keyboard::Numpad0:{
			return '0';
			break;
		}
		case sf::Keyboard::Num0:{
			return '0';
			break;
		}
		case sf::Keyboard::Numpad1:{
			return '1';
			break;
		}
		case sf::Keyboard::Num1:{
			return '1';
			break;
		}
		case sf::Keyboard::Numpad2:{
			return '2';
			break;
		}
		case sf::Keyboard::Num2:{
			return '2';
			break;
		}
		case sf::Keyboard::Numpad3:{
			return '3';
			break;
		}
		case sf::Keyboard::Num3:{
			return '3';
			break;
		}
		case sf::Keyboard::Numpad4:{
			return '4';
			break;
		}
		case sf::Keyboard::Num4:{
			return '4';
			break;
		}
		case sf::Keyboard::Numpad5:{
			return '5';
			break;
		}
		case sf::Keyboard::Num5:{
			return '5';
			break;
		}
		case sf::Keyboard::Numpad6:{
			return '6';
			break;
		}
		case sf::Keyboard::Num6:{
			return '6';
			break;
		}
		case sf::Keyboard::Numpad7:{
			return '7';
			break;
		}
		case sf::Keyboard::Num7:{
			return '7';
			break;
		}
		case sf::Keyboard::Numpad8:{
			return '8';
			break;
		}
		case sf::Keyboard::Num8:{
			return '8';
			break;
		}
		case sf::Keyboard::Numpad9:{
			return '9';
			break;
		}
		case sf::Keyboard::Num9:{
			return '9';
			break;
		}
		default:{
			return 0;
			break;
		};
	}
}

