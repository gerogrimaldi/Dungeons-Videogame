#include <SFML/Graphics.hpp>
#include "Game.h"
#include "scenes/Menu.h"
using namespace sf;

Game::Game() 
	: m_w(VideoMode(640,520),"Dungeons")
{
	m_w.setFramerateLimit(60);
	m_scene = new Menu();
	m_w.setKeyRepeatEnabled(false); //para moverse de a uno
}

void Game::Run(){
	//game loop
	while(m_w.isOpen()) {
		ProcessEvents();
		Update();
		Draw();
		//cambio de escenas
		if(m_next_scene){
			delete m_scene;
			m_scene = m_next_scene;
			m_next_scene = nullptr;
		}
		//cuando termina la pelea borro la escena
		if (FightEnded){ 
			FightEnded = false;
			delete fight_scene;
			fight_scene = nullptr;
			m_scene->PlayMusic();
		}
	}
}


void Game::Update(){
	m_scene->Update(*this);
	
	if (StartFight){ //si hay pelea pasa al update de fight
		fight_scene->Update(*this);
	}
}


void Game::Draw(){
	m_scene->Draw(m_w);
	if (StartFight){
		fight_scene->Draw(m_w);
	}
}

void Game::ProcessEvents(){

	//para rastrear los input por consola //testeo
	while(m_w.pollEvent(e)) {
		if(e.type == Event::Closed)
			m_w.close();	
		if (e.type == Event::KeyPressed){ //cuando apreto uan tecla se la paso al input manager
			IM.Input(e.key.code,true);
		}
		if (e.type == Event::MouseMoved){
			Vector2i vec = Mouse::getPosition(m_w);
			IM.Mouse(vec);
		}
	}
	
}

void Game::SetScene(Scene *next_scene){
	m_next_scene = next_scene;
}

void Game::SetFight(Scene *next_fight){
	StartFight = true;
	fight_scene = next_fight;
}

Game::~Game(){
	delete m_scene;
	m_scene = nullptr;
	delete fight_scene;
	fight_scene = nullptr;
	delete m_next_scene;
	m_next_scene = nullptr;
}
