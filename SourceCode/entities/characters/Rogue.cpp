#include "Rogue.h"
#include <iostream>


Rogue::Rogue() {
	e_texture.loadFromFile("images/rogue.png");
	e_sprite.setTexture(e_texture);
	//posicion de insercion
	e_sprite.setPosition(0,0); 
	//sfx de ataque y defensa
	buffer2.loadFromFile("audio/sfx/rogue_attack.ogg");
	attack_SFX.setBuffer(buffer2);
	attack_SFX.setVolume(40.0);
	buffer3.loadFromFile("audio/sfx/rogue_defend.ogg");
	defend_SFX.setBuffer(buffer3);
	defend_SFX.setVolume(50.0);
	//stats
	hp=250, ap=35; 
	max_hp=hp, max_ap=ap;
	min_dmg=40, max_dmg=70;
	attack_ap = 5, special_ap = 9;
	hp_recover = 75, ap_recover = 10;
}

int Rogue::SpecialAttack(){
	ss.clear();
	ss.str(""); //limpio stringstream
	attack_SFX.play();
	
	int dmg;
	int dmg2;
	
	if(ap-special_ap>=0){ //consume 4/3 ap
		dmg = min_dmg + rand()%max_dmg; //el daño se mide entre 2 valores
		dmg2 = min_dmg + rand()%max_dmg; 
		ap-=special_ap; //resto action points
		
		ss << "Atacas por: " << dmg << " y " << dmg2;
		return dmg+dmg2;
	}else{
		ss << "AP insuficiente! Daño reducido";
		dmg = min_dmg + rand()%max_dmg;
		dmg2 = min_dmg + rand()%max_dmg;
		dmg = dmg/3;
		dmg2 = dmg2/3;
		ap-=3;
		
		ss << "Atacas por: " << dmg << "y " << dmg2;
		return dmg+dmg2; 
	}
}

void Rogue::RestartInfo(){
	ss.clear();
	ss.str(""); //limpio stringstream
	
	ss << "Ingresa:\n\n";
	if (ap<attack_ap){
		ss << "1: Atacar (ap insuficiente)\n\n";
		ss << "2: Ataque doble (ap insuficiente)\n\n";
	}else{
		if(ap<special_ap){
			ss << "1: Atacar\n\n";
			ss << "2: Ataque doble (ap insuficiente)\n\n";
		}else{
			ss << "1: Atacar\n\n";
			ss << "2: Ataque doble\n\n";
		}
	}
	
	ss <<"3: Defenderse";
}

void Rogue::Die(){
	this->SetDeath();
	e_texture.loadFromFile("images/death_img/rogue_corpse.png");
	e_sprite.setTexture(e_texture);
}
