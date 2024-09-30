#ifndef PARTIDA_H
#define PARTIDA_H
#include "Scene.h"
#include "Game.h"
#include "entities_headers.h"
#include <vector>
#include <sstream>
#include <SFML/Audio/Music.hpp>

class Partida : public Scene {
private:
	bool devTools = false;
	int level=0;
	size_t difficulty;
	std::stringstream ss;
	Player *p_player;
	std::vector<Enemy*> v_enemies;
	std::vector<Texture*> v_textures;
	std::vector<Sprite*> v_sprites;
	Door *door;
	Key *key;
	sf::Texture m_bg; //background
	sf::Sprite m_s; //background
	sf::Music music;
public:
	Partida(int Player_select, size_t difficulty); //level 1
	Partida(Player *player, size_t difficulty, int levelx); //next levels
	void Update(Game &game) override;
	void Draw(sf::RenderWindow &w)override;
	int PlayMusic()override;
	void LoadResources();
	void NextLevel(Game &game);
	//<<fight>>
	void StartFight(Player *playerx, Enemy *enemyx, Game &game);
	//<<entities>>
	void Initialize_Entities(int Player_select); //level 1
	void Initialize_Entities(Player *player); //next levels
	void Check_Entities(Game &game);
	//<<sprites>>
	void Set_Sprite(int type, sf::Vector2f pos);
	//<<text display>>
	void DisplayInfo(Game &game, std::string str="");
	void DevDisplay();
	//<<getters>>
	int ViewLevel();
	int ViewDifficulty();
	//<<setters>>
	void EnableDevTools();
	void DisableDevTools();
	//<<extra>>
	~Partida();
};

#endif

