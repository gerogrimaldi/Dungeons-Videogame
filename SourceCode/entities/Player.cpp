#include "Player.h"
#include <SFML/Window/Event.hpp>

using namespace std;
	
Player::Player(){
	buffer.loadFromFile("audio/sfx/footstep.ogg");
	move_SFX.setBuffer(buffer);
	move_SFX.setVolume(50.0);

//	scores vector
	scores.resize(4);
	for(size_t i=0;i<scores.size();i++) { 
		scores[i] = 0;
	}
}

///########### POSITION ###############
void Player::Fight_Position(){
	position = e_sprite.getPosition();
	e_sprite.setPosition(130.0,255.0);
	e_sprite.setScale(2.5,2.5);
}

void Player::Return_Position(){
	e_sprite.setPosition(position);
	e_sprite.setScale(1.0,1.0);
}
//##########################

///########### MOVEMENT ###############
void Player::Move(int key,bool stop){
	//key binding y bordes
	auto player = e_sprite.getPosition();
	bool move_up = player.y>0;
	bool move_down = player.y+40<480;
	bool move_left = player.x>0;
	bool move_right = player.x+40<640;
	
	if (key==sf::Keyboard::Up and move_up and stop){
		e_sprite.move(0,-40);
		move_SFX.stop();
		move_SFX.play();
	}
	if (key==sf::Keyboard::Down  and move_down and stop){
		e_sprite.move(0,+40);
		move_SFX.stop();
		move_SFX.play();
	}
	if (key==sf::Keyboard::Left  and move_left and stop){
		e_sprite.move(-40,0);
		move_SFX.stop();
		move_SFX.play();
	}
	if (key==sf::Keyboard::Right and move_right and stop){
		e_sprite.move(+40,0);
		move_SFX.stop();
		move_SFX.play();
	}
	position = e_sprite.getPosition();
}
//##########################

///########### COMBAT ###############
int Player::Choose(Game *game){
	bool player_choosed = false;
	ss.str(std::string()); //limpio stringstream
	
	while(!player_choosed){ //mientras no haya seleccionado un ataque, no continua la batalla
		game->ProcessEvents();
		char key = game->IM.ReturnKeyValue();
		int selection = key - '0';
		
		switch(selection){
			case 1:
				game->IM.ClearKeyPressed(); //cambio la tecla guardada para q se pueda volver a elegir
				player_choosed = true;
				return this->Attack();
				break;
			case 2:
				game->IM.ClearKeyPressed();
				player_choosed = true;
				return this->SpecialAttack();
				break;
			case 3:
				game->IM.ClearKeyPressed();
				player_choosed = true;
				return this->Defend();
				break;
		}
	}
	
}

int Player::Attack(){
	ss.clear();
	ss.str(""); //limpio stringstream
	attack_SFX.play();
	
	int dmg;
	if(ap-attack_ap>=0){ //si me queda ap suficiente ataco
		dmg = min_dmg + rand()%(max_dmg-min_dmg); //el daño se mide entre 2 valores
		this->AddAP(-attack_ap); //resto action points
		
		ss << "Atacas por: " << dmg;
	}else{
		ss << "AP insuficiente! Daño reducido\n\n";
		dmg = min_dmg + rand()%(max_dmg-min_dmg);
		dmg = dmg/3;
		this->AddAP(-3);
		
		ss << "Atacas por: " << dmg << "\n";
	}
	
	return dmg; 
}

int Player::Defend(){
	//si la suma de HP es mayor al maximo, se limita a este
	if ( (hp+hp_recover) > max_hp ){
		this->AddHP(max_hp-hp);
	}else{
		this->AddHP(hp_recover); //la defensa se basa en curarse
	}
	//AP
	if ( (ap+ap_recover) > max_ap ){
		this->AddAP(max_ap-ap);
	}else{
		this->AddAP(ap_recover);
	}
	
	defend_SFX.play();
	ss << "Te has defendido";
	return 0;
}

void Player::ReceiveAttack(int damage){
	
	if(damage>this->GetHP()){
		this->AddHP(-this->GetHP()); //para quedar en 0 al morir
	}else{
		this->AddHP(-damage);
	}
	/*reducir la vida maxima con cada ataque recibido
	en base al 10% del daño*/
	this->max_hp -= (damage*0.1); 
}
//##########################

///########### TEXT DISPLAY ###############
std::string Player::ShowInfo(){
	return ss.str();
}
//##########################

///########### SCORE ###############
void Player::AddScore(int type){
	switch(type){
	case 2:  //skeleton killed
		scores[0]+=1;
		break;
	case 3: //orc killed
		scores[1]+=1;
		break;
	case 4: //pumpkin knight killed
		scores[2]+=1;
		break;
	case 5: //hp left
		scores[3] = this->hp;
		break;
	}
}
//##########################

///########### GETTERS ###############
bool Player::HasKey()const{
	return have_key;
}
vector<int> Player::ViewScore()const{
	return this->scores;
}
sf::Vector2f Player::ViewPosition()const{
	return this->position;
}
int Player::GetHP()const{
	return this->hp;
}
int Player::GetAP()const{
	return this->ap;
}
bool Player::ViewStatus() const{
	return this->IsAlive;
}
//##########################

///########### SETTERS ###############
void Player::AddHP(int amount){
	this->hp += amount;
}
void Player::AddAP(int amount){
	this->ap += amount;
}
void Player::SetDeath(){
	this->IsAlive=false;
}
void Player::FoundKey(){
	have_key = true;
}
void Player::RemoveKey(){
	have_key = false;
}
//##########################
