#ifndef FIGHT_H
#define FIGHT_H
#include "Scene.h"
#include "entities/Enemy.h"
#include "entities/Player.h"
#include "Game.h"
#include <SFML/Graphics/Color.hpp>
#include <sstream>
#include <SFML/Audio/Music.hpp>

class Fight : public Scene {
private:
	std::stringstream ss, ss2;
	bool CombatEnded = false;
	bool FirstDraw = true;
	Enemy *enemy;
	Player *player;
	sf::Music *music;
	sf::Texture f_bg;
	sf::Sprite fight_sprite;
	sf::Color color; //para hacer el fade in de la escena
	sf::Text m_t2; //info en pantalla
	Game *gamex;
public:
	Fight(Player *player, Enemy *enemy, Game &game);
	void Update (Game & game)override;
	void Draw (sf::RenderWindow & w)override;
	int PlayMusic()override;
	void FadeIn(sf::RenderWindow &w);
	void Combat();
	void ShowStats();
	void PlayerTurn();
	void EnemyTurn();
	void GameOver();
	void SetText(std::string text, int pos);
	void LoadResources();
	bool CheckEntities();
	~Fight();
};

#endif

