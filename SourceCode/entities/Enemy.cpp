#include "Enemy.h"
#include <cstdlib>
#include <ctime>


Enemy::Enemy(){
	this->RandomizePosition();
}

///########### COMBAT ###############
int Enemy::Choose(){ //IA enemigo
	//si no tiene AP, se defiende
	if (ap<attack_ap){
		return this->Defend();
	}else{
		int selection = (rand()%20);
		//17 de 20 probabilidades de atacar
		if(selection < 17){
			return this->Attack();
		}else{//3 de 20 de defender
			return this->Defend();
		}
	}
}
int Enemy::Attack(){
	attack_sfx.stop();
	attack_sfx.play();
	
	int dmg = min_dmg + rand()%(max_dmg-min_dmg); //el daño se mide entre 2 valores
	
	this->AddAP(-attack_ap);
	return dmg;
}
int Enemy::Defend(){
	attack_sfx.stop();
	attack_sfx.play();
	
	this->AddHP(hp_recover);
	this->AddAP(ap_recover);
	
	return 0;
}
//##########################

///########### POSITION ###############
void Enemy::Fight_Position(){
	e_sprite.setPosition(400.0,255.0);
	e_sprite.setScale(2.5,2.5);
}

void Enemy::SetPosition(float x, float y){
	e_sprite.setPosition(x,y);
}

void Enemy::RandomizePosition(sf::Vector2f player_pos){
	int randX = (rand()%16);
	int randY = (rand()%12);
	float x = 40* randX;
	float y = 40* randY;
	
	//prevenir spawn sobre el jugador (nivel 2 y 3)
	while(x==player_pos.x and y==player_pos.y){
		randX = (rand()%16);
		randY = (rand()%12);
		x = 40* randX;
		y = 40* randY;
	}
	
	e_sprite.setPosition(x,y);
	
	position = e_sprite.getPosition(); //guardo posicion y escala para devolver
	scale = e_sprite.getScale();
}
void Enemy::RandomizePosition(){
	int randX = (rand()%16);
	int randY = (rand()%12);
	float x = 40* randX;
	float y = 40* randY;
	
	//prevenir spawn sobre el jugador (nivel 1)
	while(x==0 and y==0){
		randX = (rand()%16);
		randY = (rand()%12);
		x = 40* randX;
		y = 40* randY;
	}
	
	e_sprite.setPosition(x,y);
	
	position = e_sprite.getPosition(); //guardo posicion y escala para devolver
	scale = e_sprite.getScale();
}
//##########################

///########### GETTERS ###############
int Enemy::GetHP()const{
	return this->hp;
}

int Enemy::GetAP()const{
	return this->ap;
}

int Enemy::ViewType()const{
	return this->type;
}

bool Enemy::ViewStatus()const{
	return this->IsAlive;
}

std::string Enemy::ViewName()const{
	return this->name;
}

Vector2f Enemy::ViewPosition()const{
	return this->position;
}
bool Enemy::Appeared()const{
	return this->already_appeared;
}
//##########################

///########### SETTERS ###############
int Enemy::AddHP(int amount){
	this->hp += amount;
}
int Enemy::AddAP(int amount){
	this->ap += amount;
}
void Enemy::SetAppeared(){
	this->already_appeared = true;
}
void Enemy::ReceiveAttack(int damage){
	if(damage>this->GetHP()){
		this->AddHP(-this->GetHP()); //para quedar en 0 al morir
	}else{
		this->AddHP(-damage);
	}
}
//##########################
