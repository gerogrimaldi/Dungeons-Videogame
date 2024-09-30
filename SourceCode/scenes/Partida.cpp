#include "all_scenes_headers.h"
//time manager
#ifdef _WIN32
	#include <Windows.h>
#else
	#include <unistd.h>
	#define Sleep(x) usleep((x)*1000)
#endif
//
#include "InputManager.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

///###### MAIN FUNCTIONS #############
Partida::Partida(int player_select, size_t difficulty) {
	//set level
	this->level +=1;
	this->difficulty = difficulty;
	//resources
	this->LoadResources();
	
	//entidades
	this->Initialize_Entities(player_select);

	//music
	this->PlayMusic();
}

Partida::Partida(Player *player, size_t difficulty, int levelx){
	//prev level stats
	this->level = levelx;
	this->level +=1;
	this->difficulty = difficulty;
	//resources
	this->LoadResources();
	
	//entidades
	this->Initialize_Entities(player);
	
	//music
	this->PlayMusic();
}

void Partida::Update(Game &game){
	int key = game.IM.key_pressed;
	
	//volver al menu
	if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
		game.SetScene (new Menu());
	
	//volver al menu
	if (key==sf::Keyboard::Space){
		this->EnableDevTools();
		game.IM.ClearKeyPressed();
	}
	
	//colision con entidad
	this->Check_Entities(game);
	//hud & info
	this->DisplayInfo(game);
	
	if(game.FightEnded){
		music.play(); //reanudo musica al finalizar el combate
	}
	
	//le paso la tecla presionada a player
	p_player->Move(game.IM.key_pressed,game.IM.stop);
	game.IM.stop = false; /*false, para que se mueva una vez y despues 
	impida el movimiento hasta presionar nuevamente la tecla */
}

void Partida::Draw(sf::RenderWindow &w){
	w.clear(Color(255,255,255,255));
	
	// background image
	w.draw(m_s); 
	
	///entities
	//enemies
	for(size_t i=0;i<v_sprites.size();i++) { 
		w.draw(*v_sprites[i]);
	}
	for(size_t i=0;i<v_enemies.size();i++) { 
		v_enemies[i]->Draw(w);
	}
	//door and key
	key->Draw(w);
	door->Draw(w);
	//player
	p_player->Draw(w); 
	///
	
	//Text
	w.draw(m_t);
	
	//display
	w.display();
}

//###########################

///###### RESOURCES #############
void Partida::LoadResources(){
	//cargo imagen fondo
	m_bg.loadFromFile("images/background_x520.png");
	m_s.setTexture(m_bg);
	m_s.setPosition(0,0);
	
	//texturas
	v_textures.resize(4);
	for(size_t i=0;i<v_textures.size();i++) { 
		v_textures[i] = new Texture;
	}
	v_textures[0]->loadFromFile("images/explored_area.png");
	v_textures[1]->loadFromFile("images/death_img/skeleton_corpse.png");
	v_textures[2]->loadFromFile("images/death_img/orc_corpse.png");
	v_textures[3]->loadFromFile("images/death_img/pumpkin_corpse.png");
	
	//Text
	m_font.loadFromFile("fonts/8bit16.ttf");
	m_t.setFont(m_font);
	m_t.setPosition(10,480);
	m_t.setCharacterSize(25);
	m_t.setFillColor({240,230,140});
	
	//musica
	music.stop();
	music.openFromFile("audio/music/game_music.ogg");
	music.setLoop(true);
}

int Partida::PlayMusic(){
	music.setVolume(35);
	music.play();
	return 0;
}
//###########################

///###### SCENE CHANGE #############
void Partida::StartFight(Player *playerx, Enemy *enemyx, Game &game){
	if(!enemyx->Appeared()){ //para q aparezca 1 sola vez la entidad
		enemyx->Appear(); 
		game.Draw(); //para q dibuje al enemigo
		
		game.SetFight(new Fight(playerx, enemyx, game));
		music.pause();
	};
}

void Partida::NextLevel(Game &game){
	if (this->level!=3){ //si el nivel es ya el tercero, termina el juego
		game.SetScene(new Partida(p_player,this->ViewDifficulty()+1,this->ViewLevel()));
	}else{
		//save hp left
		p_player->AddScore(5); 

		//scene change
		game.SetScene(new HighScores(p_player->ViewScore(),this->ViewDifficulty(),this->ViewLevel()));
	}
}
//###########################

///###### ENTITIES MANAGEMENT #############
void Partida::Initialize_Entities(int player_select){ //randomizar enemigos
	//Player	
	switch(player_select){
		case 1: p_player = new Knight();
				break;
		case 2: p_player = new Mage();
				break;
		case 3: p_player = new Rogue();
				break;
	}
	
	//key and door
	door = new Door();
	key = new Key();
	
	//prevenir spawn de llave en puerta
	while(key->CollideWith(door)){
		key->RandomizePosition();
	}
		
	//enemies
	int x;
	v_enemies.resize(this->difficulty);
	
	//creo enemigos
	for(size_t i=0;i<this->difficulty;i++) { 
		x=rand()%20;
		if (x<=12){ // de 1 a 12 spawn un esqueleto
			v_enemies[i] = new Skeleton();
		}
		if (x>12 && x<=17){ //de 12 a 17 un orco
			v_enemies[i] = new Orc();
		}
		if (x>17 && x<=20){ //de 17 a 20 un caballero calabaza
			v_enemies[i] = new Pumpkin_Knight();
		}
	}
	
	//reacomodo enemigos superpuestos
	for(size_t i=0;i<v_enemies.size();i++) { 
		for(size_t i2=0;i2<v_enemies.size();i2++) { 
			if (i2==i) //skip enemigo seleccionado con i
				continue;
			while (v_enemies[i]->CollideWith(v_enemies[i2]) or v_enemies[i]->CollideWith(door))
				v_enemies[i]->RandomizePosition();
		}
	}
}

void Partida::Initialize_Entities(Player *player){ //randomizar enemigos nivel 2 y 3
	//Player	
	this->p_player = player;
	p_player->RemoveKey();
	//key and door
	door = new Door();
	key = new Key();
	
	//prevenir spawn de llave en puerta y/o en jugador
	while(key->CollideWith(door) and key->CollideWith(p_player)){
		key->RandomizePosition();
	}
	while(door->CollideWith(key) and door->CollideWith(p_player)){
		door->RandomizePosition();
	}
	
	//enemies
	int x;
	v_enemies.resize(this->difficulty);
	
	//creo enemigos
	for(size_t i=0;i<this->difficulty;i++) { 
		x=rand()%20;
		if (x<=12){ // de 1 a 12 spawn un esqueleto
			v_enemies[i] = new Skeleton();
		}
		if (x>12 && x<=17){ //de 12 a 17 un orco
			v_enemies[i] = new Orc();
		}
		if (x>17 && x<=20){ //de 17 a 20 un caballero calabaza
			v_enemies[i] = new Pumpkin_Knight();
		}
	}
	
	//reacomodo enemigos superpuestos
	for(size_t i=0;i<v_enemies.size();i++) {
		v_enemies[i]->RandomizePosition(this->p_player->ViewPosition());
		for(size_t i2=0;i2<v_enemies.size();i2++) { 
			if (i2==i) //skip enemigo seleccionado con i
				continue;
			while (v_enemies[i]->CollideWith(v_enemies[i2]) or v_enemies[i]->CollideWith(door))
				v_enemies[i]->RandomizePosition(this->p_player->ViewPosition());
		}
	}
	std::cout << v_enemies.size();
}

void Partida::Check_Entities(Game &game){
		
	//inserto sprite de mapa explorado
	this->Set_Sprite(-1,p_player->ViewPosition());
	
	//check door and key
	//	door
	if(p_player->CollideWith(door)){
		if(!door->ViewStatus())
			this->DisplayInfo(game, door->Appear());
		if(door->Open(game, p_player->HasKey())) //si la puerta se abre avanzo de nivel
			this->NextLevel(game);
	}
	//	key
	if(p_player->CollideWith(key)){
		if(!key->ViewStatus()){
			key->Appear();
			p_player->FoundKey();
		}
	}
	
	//check enemies
	for(size_t i=0;i<v_enemies.size();i++) { 
		//checkeo colisiones
		if(p_player->CollideWith(v_enemies[i])){
			this->StartFight(p_player, v_enemies[i],game);
		}
		//checkeo si estan muertos
		if(!v_enemies[i]->ViewStatus()){ //si esta muerto:
			
			//elimino el sprite de mapa explorado
			auto it2 = v_sprites.end()-1;
			v_sprites.erase(it2);
			
			//dibujo su cadaver
			this->Set_Sprite(v_enemies[i]->ViewType(),v_enemies[i]->ViewPosition());
			
			//elimino la entidad
			delete v_enemies[i];
			auto it = v_enemies.begin()+i;
			v_enemies.erase(it);
			
			i-=1;
			
/*cout comentado: Sirve para ver el tamaño del vector de enemigos y comprobar que 
se eliminan al morir.	*/
//		std::cout << "\nEnemies vector: " << v_enemies.size() << "\n";

		}
	}
	
	if(!p_player->ViewStatus()){ //si el jugador muere muestro puntaje
		game.SetScene(new HighScores(p_player->ViewScore(),this->ViewDifficulty(),this->ViewLevel()));
	}
}
//#########################

///###### SPRITES MANAGEMENT #############
void Partida::Set_Sprite(int type, sf::Vector2f pos){
	bool set = true;
	
	//si ya hay otro sprite en esa posicion, no lo pongo y borro el nuevo
	for(size_t i2=0;i2<v_sprites.size();i2++) { 
		if (pos == v_sprites[i2]->getPosition()){
			set = false;
		}
	}
	
	if (set){
		//añado sprite y creo un indice para esa posicion nueva
		v_sprites.resize(v_sprites.size()+1);
		size_t i= v_sprites.size()-1;
		v_sprites[i] = new Sprite;
		
		switch(type){
			case 2: //skeleton corpse
				v_sprites[i]->setTexture(*this->v_textures[1]);
				break;
			case 3:  //orc corpse
				v_sprites[i]->setTexture(*this->v_textures[2]);
				break;
			case 4: //pumpkin knight corpse
				v_sprites[i]->setTexture(*this->v_textures[3]);
				break;
			default: //tile explored
				v_sprites[i]->setTexture(*this->v_textures[0]);
				break;
		}
		
/*cout comentado: Sirve para ver el tamaño del vector sprites y chequear que no 
se crean en una posicion cuando ya hay otro, es decir, no se superponen.	*/
//		std::cout <<"\nSprites: " << v_sprites.size() << "\n" ;
		v_sprites[i]->setPosition(pos);
	}
	
}

//#########################

///######### TEXT DISPLAY ##########
void Partida::DisplayInfo(Game &game, std::string str){
	ss.clear();
	ss.str("");
	
	ss.str(str);
	
	if (str==""){
		ss << "HP: " << p_player->GetHP() << "  Ap: " << p_player->GetAP()
			<< "			Nivel " << this->ViewLevel();
		m_t.setString(ss.str());
	}else{
		m_t.setString(ss.str()); //set the text
		game.Draw(); //dibujarlo antes del sleep
		Sleep(2500);
	}
	
	if(devTools){
		this->DevDisplay();
	}
}

void Partida::DevDisplay(){
	sf::Vector2f pos;
	
	std::cout << "\n##### Entities positions #####\n";
	std::cout << "\n *ENEMIES";
	for(size_t i=0;i<v_enemies.size();i++) {
		pos = v_enemies[i]->ViewPosition();
		std::cout << "\n 	" << i+1 << 
			"= X:" << 1+pos.x/40 << "  Y:" << 1+pos.y/40; 
	}
	
	pos = door->ViewPosition();
	std::cout << "\n\n *DOOR \n 	X:" << 1+pos.x/40 << " Y:" << 1+pos.y/40; 
	
	pos = key->ViewPosition();
	std::cout << "\n\n *KEY \n 	X:" << 1+pos.x/40 << " Y:" << 1+pos.y/40 << "\n";
	
	this->DisableDevTools(); //para q se muestren solo 1 vez
}
//#########################

///######### GETTERS ##########
int Partida::ViewLevel(){
	return this->level;
}
int Partida::ViewDifficulty(){
	return this->difficulty;
}
//#########################

///######### SETTERS ##########
void Partida::EnableDevTools(){
	devTools = true;
}
void Partida::DisableDevTools(){
	devTools = false;
}
//#########################

Partida::~Partida(){
	//delete enemies vector
	for(size_t i=0;i<v_enemies.size();i++) { 
		delete v_enemies[i];
		v_enemies[i] = nullptr;
	}
	v_enemies.clear();
	v_enemies.shrink_to_fit();
	
	//delete textures vector
	for(size_t i=0;i<v_textures.size();i++) { 
		delete v_textures[i];
		v_textures[i] = nullptr;
	}
	v_textures.clear();
	v_textures.shrink_to_fit();
	
	//delete sprites vector
	for(size_t i=0;i<v_sprites.size();i++) { 
		delete v_sprites[i];
		v_sprites[i] = nullptr;
	}
	v_sprites.clear();
	v_sprites.shrink_to_fit();
	
	//delete other entities
	delete key;
	key = nullptr;
	delete door;
	door = nullptr;
	
	if(this->level==3){
		delete p_player;
		p_player = nullptr;
		std::cout << "\nDeleted Player\n";
	}else{
		p_player = nullptr;
	}
	std::cout << "\nDeleted level " << level << "\n";
};
