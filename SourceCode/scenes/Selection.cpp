#include "Selection.h"
#include "Game.h"
#include "Menu.h"
#include "Partida.h"

///###### MAIN FUNCTIONS #############
Selection::Selection() {
	m_font.loadFromFile("fonts/8bit16.ttf");
	m_t.setFont(m_font);
	m_t.setPosition(30,40);
	m_t.setCharacterSize(25);
	m_t.setFillColor({240,230,140});
	
}

void Selection::Update (Game &game) {
	this->Player_Selection(game);
}

void Selection::Draw (sf::RenderWindow & w) {
	w.clear({0,0,0});
	w.draw(m_t);
	w.display();
}

int Selection::PlayMusic(){
	return 0;
}
//###################

///###### PLAYER AND DIFFICULTY #############
void Selection::Player_Selection(Game &game){
	this->SetText();
	
	bool player_choosed = false;
	bool player_exited = false;
	char selection;
	
	game.Draw();
	game.IM.ClearKeyPressed();
	
	//seleccion de jugador
	//mientras no haya seleccionado un personaje, no empieza el juego
	while(!player_choosed){ 
		game.ProcessEvents();
		
		selection = game.IM.ReturnKeyValue(); //save key

		switch(selection){
			case '1':{ 		//caballero
				player_choosed=true;
				break;
			}
			case '2':{ 		//mago
				player_choosed=true;
				break;
			}
			case '3':{ 		//arquero
				player_choosed=true;
				break;
			}
		}
		
		//back to menu	
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)){
			player_choosed=true;
			player_exited = true;
		}
	}
	
	if (player_exited){
		game.SetScene (new Menu());
	}else{
		int selection_int = selection - 48; //convert char to int
		this->Difficulty_Selection(selection_int,game);
	}
}

void Selection::Difficulty_Selection(int player, Game &game){
	this->SetText2();
	
	bool player_choosed = false;
	bool player_exited = false;
	char selection;
	
	game.Draw();
	game.IM.ClearKeyPressed();
	
	//seleccion de jugador
	while(!player_choosed){ 
		game.ProcessEvents();
		
		selection = game.IM.ReturnKeyValue(); //save key
		
		switch(selection){
			case '3':{ 		//facil
				player_choosed=true;
				break;
			}
			case '5':{ 		//normal
				player_choosed=true;
				break;
			}
			case '7':{ 		//dificil
				player_choosed=true;
				break;
			}
		}
		
		//back to menu
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)){
			player_choosed=true;
			player_exited = true;
		}
	}
	
	if (player_exited){
		game.SetScene (new Menu());
	}else{
		int selection_int = selection - 48; //convert char to int
		game.SetScene(new Partida(player, selection_int));
	}
}
//###################

///###### TEXT DISPLAY #############
void Selection::SetText(){
	//clear stringstream
	ss.clear();
	ss.str(""); 
	
	ss << "Escoge tu personaje (presiona la tecla):\n\n" << 
		"1. Caballero:\n" << "  HP=300,  AP=25,  DMG=30-60\n"<<
		"  Costo de ataque=8\n" <<  "  Ataque especial -> Golpe con escudo (coste AP*1/2)\n\n" << 
		
		"2. Mago:\n" << "  HP=200,  AP=25,  DMG=40-100\n"<<
		"  Costo de ataque=10\n" <<  "  Ataque especial -> Bomba de fuego (coste AP*3/2)\n\n" << 
		
		"3. Arquero:\n" << "  HP=250,  AP=35,  DMG=40-70\n"<<
		"  Costo de ataque=5\n" << "  Ataque especial -> Ataque doble (coste AP*4/3)\n";
	
	m_t.setString(ss.str());
}

void Selection::SetText2(){
	//clear stringstream
	ss.clear();
	ss.str(""); 
	
	ss << "Escoge la dificultad (cantidad de enemigos):\n\n" << 
		"3 - Facil: 3 enemigos\n\n" << 
		"5 - Normal: 5 enemigos\n\n" << 
		"7 - Dificil: 7 enemigos";
	
	m_t.setString(ss.str());
}
//###################
