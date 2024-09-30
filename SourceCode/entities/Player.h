#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Game.h"
#include <vector>
#include <sstream>
//using namespace std;

class Player : public Entity {
private:
	int min_pos,max_pos;
	sf::Vector2f position;
	std::vector<int> scores; //enemigos muertos y hp restante
	bool have_key = false;
	bool IsAlive = true;
protected:
	int hp,ap,
		max_dmg, min_dmg, max_hp, max_ap, 
		attack_ap, special_ap, 
		hp_recover, ap_recover;
	Sound move_SFX, attack_SFX, defend_SFX;
	SoundBuffer buffer, buffer2, buffer3;
	std::stringstream ss;
public:
	Player();
	void Move(int key,bool stop);
	//<<combat>>
	int Attack();
	int Defend();
	virtual int SpecialAttack() = 0;
	int Choose(Game *game);
	void ReceiveAttack(int damage);
	//<<position>>
	void Fight_Position();
	void Return_Position();
	//<<score>>
	void AddScore(int type);
	//<<info>>
	std::string ShowInfo(); 
	virtual void RestartInfo() = 0;
	//<<change status>>
	virtual void Die() = 0;
	//<<getters>>
	bool HasKey() const;
	std::vector<int> ViewScore() const;
	sf::Vector2f ViewPosition() const;
	int GetHP() const;
	int GetAP() const;
	bool ViewStatus() const;
	//<<setters>>
	void AddHP(int amount);
	void AddAP(int amount);
	void SetDeath();
	void FoundKey();
	void RemoveKey();
	//<<extra>>
	~Player(){}
};

#endif

