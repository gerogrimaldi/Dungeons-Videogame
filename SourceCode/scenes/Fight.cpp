#include "all_scenes_headers.h"
//time manager
#ifdef _WIN32
	#include <Windows.h>
#else
	#include <unistd.h>
	#define Sleep(x) usleep((x)*1000)
#endif
//
//#include <iostream>
#include "HighScores.h"

#include <iomanip>

///###### MAIN FUNCTIONS #############
Fight::Fight(Player *playerx, Enemy *enemyx, Game &game) {

	this->LoadResources();
	
	//cargo enemigo y jugador
	enemy=enemyx;
	player=playerx;
	
	//guardo puntero a game
	gamex = &game;
}

void Fight::Update (Game &game) {
	Fight::Combat();
	if (CombatEnded){
		player->Return_Position(); //devuelvo al jugador a su posicion
		CombatEnded = false;
		game.StartFight = false;
		game.FightEnded = true;
	}
}

void Fight::Draw (sf::RenderWindow &w) { 
	
	//en el primer draw dibujo el escenario con fade in
	if(FirstDraw){
		this->FadeIn(w);
	}
	
	w.clear(Color(255,255,255,255));
	// background image
	w.draw(fight_sprite);
	//entidades
	enemy->Fight_Position();
	enemy->Draw(w); 
	
	player->Draw(w);
	
	//texto
	w.draw(m_t);
	this->ShowStats(); //para q vaya actualizando info
	w.draw(m_t2);
	
	//display
	w.display();
}
//###################

///###### SCENE RESOURCES #############
void Fight::LoadResources(){
	//cargo imagen de fondo
	f_bg.loadFromFile("images/fight_backgroundx520.png");
	fight_sprite.setTexture(f_bg);
	fight_sprite.setPosition(0,0);
	
	//guardo el color para asignar trasnparencia
	color = fight_sprite.getColor(); 
	
	//textos
	m_font.loadFromFile("fonts/8bit16.ttf");
	m_t.setFont(m_font);
	m_t.setCharacterSize(25);
	m_t.setFillColor({240,230,140});
	m_t.setOutlineThickness(2.0);
	
	m_t2.setFont(m_font);
	m_t2.setCharacterSize(25);
	m_t2.setFillColor({240,230,140});
	m_t2.setOutlineThickness(2.0);
	
	ss.str("");
}

int Fight::PlayMusic ( ) {
	music = new Music();
	
	music->setVolume(20);
	if (!music->openFromFile("audio/music/fight_music.flac"))
		return -1; // error
	
	music->play();
	return 0;
}
//fade in del escenario de combate
void Fight::FadeIn(sf::RenderWindow &w){
	w.clear(Color(0,0,0,0));
	w.display();
	Sleep(500);
	// background image
	
	//fade-in del escenario de batalla
	color.a=5; 
	for(int i=0;i<5;i++) { 
		color.a+=50; 
		fight_sprite.setColor(color);
		w.draw(fight_sprite); 
		w.display();
		Sleep(500);
	}
	FirstDraw = false;
	
	//esta funcion se la llama aca pq sino da un bug y no se guarda la posicion actual del jugador
	player->Fight_Position(); 
}
//###################

///###### COMBAT LOOP AND TURNS #############
void Fight::Combat(){
	//clear stringstream
	ss.clear();
	ss.str(""); 
	
	int player_dmg, enemy_dmg;
	
	gamex->Draw(); //para que dibuje el escenario de combate
	
	ss << "Ha aparecido un \n\n      "<< enemy->ViewName() << "!";
	this->SetText(ss.str(),3);
	Sleep(1000);
	
	ss.str("");
	ss << "COMIENZA EL COMBATE";
	this->SetText(ss.str(),3);
	Sleep(1000);
	
	this->PlayMusic(); //musica
	
	while(enemy->ViewStatus() and player->ViewStatus()){ //si uno muere se termina la pelea
		this->ShowStats(); //muestro stats	
		
		//ronda de turnos
		///turno jugador
		this->PlayerTurn();
		
		if (this->CheckEntities())
			break;
		
		///turno enemigo
		this->EnemyTurn();
		
		if (this->CheckEntities())
			break;
	}

	CombatEnded = true; //devuelve true al finalizar el combate
	
	//clear stringstream
	ss.clear();
	ss.str(""); 
	ss << "COMBATE TERMINADO\n";
	this->SetText(ss.str(),3);
	
	music->stop();
}

bool Fight::CheckEntities(){
	if (enemy->GetHP()<=0){ //si muere se termina
		player->AddScore(enemy->ViewType());
		enemy->Die();
		
		ss.str("");
		ss << "\n" << enemy->ViewName() <<" ha muerto\n";
		
		this->SetText(ss.str(),3);
		Sleep(1000);
		return true;
	}
	if (player->GetHP()<=0){ //si el jugador muere termina
		this->GameOver();
		return true;
	}
	return false;
}
void Fight::PlayerTurn(){
	//muestro primero los comandos de ataque
	player->RestartInfo();
	this->SetText(player->ShowInfo(), 1);
	
	//eleccion
	int player_dmg = player->Choose(gamex); //guardo el daño para mostrarlo
	enemy->ReceiveAttack(player_dmg);
	
	//luego del choose, la info se cambia por el daño
	this->SetText(player->ShowInfo(), 1);
	Sleep(2000);
}

void Fight::EnemyTurn(){
	//clear stringstream
	ss.clear();
	ss.str(""); 
	int enemy_dmg = enemy->Choose();
	
	player->ReceiveAttack(enemy_dmg);
	
	//text
	if(enemy_dmg!=0){
		ss <<  "Te atacan por: " << enemy_dmg;
		this->SetText(ss.str(),2);
	}else{
		ss << enemy->ViewName() << " se defiende";
		this->SetText(ss.str(),2);
	}
	
	Sleep(2000);
}


//###################

///######### GAME OVER FUNCTION ##########
void Fight::GameOver(){
	player->Die();
	
	music->stop();
	music->openFromFile("audio/music/game_over.ogg");
	music->play();
	this->SetText( "Has muerto!!!" , 3); 
	Sleep(5000);
}
//###################

///######## TEXT DISPLAY ###########
void Fight::SetText(std::string text, int pos){
	m_t.setString(text);
	
	switch(pos){
	case 1: //info jugador
		m_t.setPosition(100.0,370.0);
		break;
	case 2: //info enemigo
		m_t.setPosition(370.0,370.0);
		break;
	case 3: //info batalla
		m_t.setPosition(210.0,370.0);
		break;
	}
	
	//dibujo el texto en pantalla
	this->Draw(gamex->m_w);
}

void Fight::ShowStats(){
	//clear stringstream
	ss2.clear();
	ss2.str(""); 
	
	ss2 << std::setw(16) <<"PLAYER" << std::setw(50) <<enemy->ViewName() << "\n\n" << 
		 "Hp  #" << std::setw(8) << player->GetHP() << std::setw(46) << "#   " << enemy->GetHP() << "\n\n" << 
		 "Ap  #"<< std::setw(8) << player->GetAP() << std::setw(47) << "#   " << enemy->GetAP() << "\n";
	
	m_t2.setString(ss2.str());
	m_t2.setPosition(90.0,160.0);
}
//###################

Fight::~Fight(){
	player = nullptr;
	enemy = nullptr;
	delete music;
	music = nullptr;
	gamex = nullptr;
	
//	std::cout << "Fight Destructor";
}
