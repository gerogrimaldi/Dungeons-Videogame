#include "Menu.h"
#include "Partida.h"
#include "Game.h"
#include "Instructions.h"
#include "Selection.h"
using namespace sf;

Menu::Menu() {
	//Creo textos
	m_font.loadFromFile("fonts/FlyingHollander.ttf");
	m_t.setFont(m_font);
	m_font2.loadFromFile("fonts/8bit16.ttf");
	m_t2.setFont(m_font2);
	//texto 1
	m_t.setString("Dungeons");
	m_t.setFillColor({255,215,0});
	m_t.setPosition(125,100);
	m_t.setCharacterSize(100);
	//texto 2
	m_t2.setString("    	Play = ENTER\n How to play = Space");
	m_t2.setFillColor({240,230,140});
	m_t2.setPosition(195,270);
	m_t2.setCharacterSize(35);
	
	//musica
	this->PlayMusic();
}

void Menu::Update(Game &game){
	//jugar
	if (Keyboard::isKeyPressed(Keyboard::Key::Return)){
		game.SetScene ( new Selection());
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Space)){
		game.SetScene ( new Instructions());
	}
}

void Menu::Draw(sf::RenderWindow &w){
	w.clear({0,0,0});
	w.draw(m_t);
	w.draw(m_t2);
	w.display();
}

int Menu::PlayMusic(){
	music = new Music();
	
	if (!music->openFromFile("audio/music/menu_music.wav")){
		return -1; // error
	}
	
	music->stop();
	music->setVolume(10);
	
	music->play();
	
	music->setLoop(true);
	return 0;
}

Menu::~Menu(){
	delete music;
	music = nullptr;
};
