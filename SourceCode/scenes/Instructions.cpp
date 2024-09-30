#include "Instructions.h"
#include <SFML/Window/Keyboard.hpp>
#include "Game.h"
#include "Menu.h"
#include <sstream>

Instructions::Instructions() {
	m_font.loadFromFile("fonts/8bit16.ttf");
	m_t.setFont(m_font);
	m_t.setPosition(20,100);
	m_t.setCharacterSize(25);
	m_t.setFillColor({240,230,140});

	//text
	this->SetText();
	
	//music
	this->PlayMusic();
}

void Instructions::Update (Game &game) {
	//volver al menu
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		game.SetScene (new Menu());
}

void Instructions::Draw (sf::RenderWindow & w) {
	w.clear({0,0,0});
	w.draw(m_t);
	w.display();
}

int Instructions::PlayMusic(){
	return 0;
}

void Instructions::SetText(){
	std::stringstream ss("");
	ss << "Estas solo en una mazmorra...\n\n" << 
		"* Usa las flechas de direccion para moverte por el mapa\n\n" << 
		"* Mientras exploras te puedes encontrar a un enemigo.\n" << 
		"Durante el combate pulsa:\n" <<
		"- 1 para atacar (consume AP).\n" <<
		"- 2 para usar tu ataque especial\n" <<
		"- 3 para defenderte (regeneras  HP y AP).\n\n" << 
		"* El danio que haces es calculado dentro de un\n rango de valores segun tu personaje\n\n" << 
		"* Tu vida maxima se reduce con cada ataque recibido\n\n\n" << 
		"* Hay 3 niveles. En cada uno se aniade un enemigo extra\n a los que elijas inicialmente\n\n" <<
		"* Para ganar debes encontrar la llave y usarla \npara abrir la puerta de cada nivel y escapar!!!\n\n" <<
		"* Presionando la barra espaciadora activas \n las herramientas de desarrollador\n\n" <<
		"											 ESC = Volver";
	
	m_t.setString(ss.str());
}

