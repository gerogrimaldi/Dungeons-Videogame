#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"
#include <SFML/Graphics/Color.hpp>
#include <iostream>

class Enemy : public Entity {
private:
	bool already_appeared = false;
protected:
	SoundBuffer buffer, buffer2;
	Sound sound, attack_sfx;
	Color color;
	int hp,ap, 
		max_dmg, min_dmg,
		attack_ap,
		hp_recover, ap_recover;
	bool IsAlive = true;
	std::string name;
	sf::Vector2f position, scale;
public:
	Enemy();
	//<<combat>>
	int Choose();
	int Attack();
	int Defend();
	void ReceiveAttack(int damage);
	//<<change status>>
	virtual void Appear() = 0;
	virtual void Die() = 0;
	//<<position>>
	void Fight_Position(); //lo acomoda en la escena fight
	void RandomizePosition(sf::Vector2f player_pos); //spawn random nivel 2 y 3
	void RandomizePosition(); //spawn random en nivel 1
	void SetPosition(float x, float y); //para moverlo
	//<<getters>>
	int GetHP()const;
	int GetAP()const;
	int ViewType()const;
	bool ViewStatus()const;
	std::string ViewName()const;
	Vector2f ViewPosition()const;
	bool Appeared()const;
	//<<setters>>
	int AddHP(int amount);
	int AddAP(int amount);
	void SetAppeared();
	//<<extra>>
	~Enemy(){}
};

#endif

