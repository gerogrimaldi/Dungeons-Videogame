#include "Mage.h"
#include <iostream>

Mage::Mage() {
	e_texture.loadFromFile("images/wizard.png");
	e_sprite.setTexture(e_texture);
	//posicion de insercion
	e_sprite.setPosition(0,0); 
	//sfx de ataque y defensa
	buffer2.loadFromFile("audio/sfx/mage_attack.ogg");
	attack_SFX.setBuffer(buffer2);
	attack_SFX.setVolume(50.0);
	buffer3.loadFromFile("audio/sfx/mage_defend.ogg");
	defend_SFX.setBuffer(buffer3);
	defend_SFX.setVolume(20.0);
	//stats
	hp=200, ap=25; 
	max_hp=hp, max_ap=ap;
	min_dmg=40, max_dmg=100; 
	attack_ap = 10, special_ap = 15;
	hp_recover = 80, ap_recover = 12;
}

int Mage::SpecialAttack(){ //hace doble de daño y consume 3/2 ap
	attack_SFX.play();
	
	int dmg;
	
	if(ap-special_ap>=0){
		dmg = min_dmg + rand()%max_dmg; 
		dmg = dmg*2.5;
		ap-=special_ap; 
		
		ss << "Atacas por: " << dmg;
		return dmg;
	}else{
		
		ss << "AP insuficiente! Daño reducido";
		dmg = min_dmg + rand()%max_dmg;
		dmg = dmg/3;
		ap-=1;
		
		ss << "Atacas por: " << dmg;
		return dmg; 
	}
}

void Mage::RestartInfo(){
	ss.clear();
	ss.str(""); //limpio stringstream
	
	ss << "Ingresa:\n\n";
	if (ap<attack_ap){
		ss << "1: Atacar (ap insuficiente)\n\n";
		ss << "2: Bomba de fuego (ap insuficiente)\n\n";
	}else{
		if(ap<special_ap){
			ss << "1: Atacar\n\n";
			ss << "2: Bomba de fuego (ap insuficiente)\n\n";
		}else{
			ss << "1: Atacar\n\n";
			ss << "2: Bomba de fuego\n\n";
		}
	}
	
	ss <<"3: Defenderse";
}

void Mage::Die(){
	this->SetDeath();
	e_texture.loadFromFile("images/death_img/wizard_corpse.png");
	e_sprite.setTexture(e_texture);
}
