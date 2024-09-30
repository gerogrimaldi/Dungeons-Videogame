#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "scenes/Scene.h"
#include "InputManager.h"
#include <SFML/Window/Event.hpp>

class Game {
private:
	Scene *m_scene, *fight_scene = nullptr;
	Scene *m_next_scene = nullptr;
	sf::RenderWindow m_w;
	sf::Event e;
public:
	Game();
	void Run();
	void Update();
	void Draw();
	void ProcessEvents();
	void SetScene(Scene *next_scene);
	void SetFight(Scene *next_fight);
	bool StartFight = false;
	bool FightEnded = false;
	InputManager IM;
	/*fight es friend para acceder a window,
	ya que la pelea se da durante un loop interno,
	por lo que no se pasa 
	por el update que lleva al draw*/
	friend class Fight; 
	~Game();
};

#endif

