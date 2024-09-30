#include "HighScores.h"
#include "Menu.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <iterator>
#include <iomanip>
using namespace std;

///###### MAIN FUNCTIONS ##########
HighScores::HighScores( std::vector<int> scores, int dif, int levelx) {
	//cargo imagen fondo
	m_bg.loadFromFile("images/scroll_background.png");
	m_s.setTexture(m_bg);
	m_s.setPosition(0,0);
	
	//guardo scores
	player_scores = scores; //actual player score
	level=levelx;
	difficulty= dif-(level-1); //(level-1) son los enemigos extra añadidos en c/nivel
	//text	
	m_font.loadFromFile("fonts/8bit16.ttf");
	m_t.setFont(m_font);
	m_t.setPosition(140,80);
	m_t.setCharacterSize(25);
	m_t.setFillColor({0,0,0});
	
	//data
	file_name = "scenes/highscores.dat";

	//scores
	this->CalculateScore();
	//next step
	this->ReadFile();
	//first show player scores
	this->SetText();
	
	std::cout << "\nPresiona 'espacio' para resetear los puntajes\n";
}

void HighScores::Update (Game &game) {
	//volver al menu
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		game.SetScene (new Menu());
	
	//resetear high scores
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		this->ResetHighScores();
	
	//texto 2
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) and compare){
		compare = false; //comparar solo 1 vez
		this->CompareScore(game);
	}
}

void HighScores::Draw (sf::RenderWindow & w) {
	w.clear({0,0,0});
	w.draw(m_s);//Sprite
	w.draw(m_t);//text
	w.display();
}

int HighScores::PlayMusic(){
	return 0;
}
//############################

///###### TEXT DISPLAY ##########
void HighScores::SetText(std::string str){
	//clear stringstream
	ss.clear();
	ss.str(""); 
	//clear text
	m_t.setString("");
	
	//si esta vacio inserto score del jugador
	if(str==""){
		ss << setw(18) << "#### TU PUNTAJE ####\n\n" << 
			"#Enemigos eliminados:" << setw(12) << "\n\n" <<
			"	Esqueletos:"  << setw(9) << player_scores[0] <<" * 10 pts\n\n" << 
			"	Orcos:"  << setw(9) << player_scores[1] << " * 20 pts\n\n" << 
			"	Caballero calabaza:" << setw(6) << player_scores[2] << " * 30 pts\n\n" << 
			"#HP restante:"  << setw(12) << player_scores[3] << "\n\n\n" <<
			"#Nivel:"  << setw(12) << level << "\n\n\n" <<
			"#Dificultad:"  << setw(12) << difficulty << "\n\n\n" <<
			"TOTAL:" << setw(12) << total_score << " puntos\n\n" << 
			setw(18) << "Continuar: Enter";
	}else{
		ss.str(str);
	}
	
	m_t.setString(ss.str());
}

void HighScores::ShowBestScores(std::string str){
	//clear stringstream
	ss.clear();
	ss.str(""); 
	//clear text
	m_t.setString("");
	
	//si esta vacio inserto texto 2
	if(str==""){
		ss << setw(18) << "#### MEJORES PUNTAJES ####\n\n"; 
		
		for(size_t i=0;i<high_scores.size();i++) { 
				ss << setw(14) << i+1 << "°		" << high_scores[i].name << setw(8) << high_scores[i].score << "\n\n";
		}	
		ss << setw(18) << "Volver al menu: ESC";
	}else{
		ss.str(str);
	}
	
	this->SetText(ss.str());
	//next step
	this->WriteFile();
}
//############################

///###### FILE MANAGEMENT ##########
void HighScores::ReadFile(){
	//load file
	std::ifstream file_in;
	
	file_in.open(file_name,ios::binary|ios::ate);
	if (!file_in.is_open()){
		std::cerr << "No se pudo abrir el archivo\n"; 
	}
	
	//read file
	int tamanio = file_in.tellg();
	int n = tamanio/sizeof(Score);
	Score x;
	
	file_in.seekg(0);
	for(int i=0;i<n;i++) { 
		file_in.read(reinterpret_cast<char*>(&x),sizeof(Score));
		high_scores.push_back (x); //cargo struct
	}

	file_in.close();
}

void HighScores::WriteFile(){
	//open file and clear ir
	std::ofstream file_out;
	file_out.open(file_name, ios::binary|ios::trunc);
	if(!file_out.is_open()){
		std::cerr << "No se pudo escribir el archivo\n"; 
	}
	
	//write file
	file_out.seekp(0);	
	for(Score s : high_scores) { 
		file_out.write(reinterpret_cast<char*>(&s),sizeof(Score));
	}
	file_out.close();
}
//############################

///###### SCORE CALCULATIONS ##########
void HighScores::CalculateScore(){
	//	Each enemy gives different values
	//	skeleton: 10 Points each
	total_score += player_scores[0]*10;
	//	orcs: 20 Points each
	total_score += player_scores[1]*20;
	//	pumpkin knight: 30 Points each
	total_score += player_scores[2]*30;
	//	HP left
	total_score += player_scores[3];
	
	//level bonus
	total_score*=level;
	//difficulty bonus
	total_score*=(difficulty/3);
}

void HighScores::CompareScore(Game &game){
	bool NewRecord = false;
	int posNewScore;
	
	for(size_t i=0;i<high_scores.size();i++) { 
		if (total_score >= high_scores[i].score){
			NewRecord = true;
			posNewScore = i;
			break;
		}
	}
	
	NewRecord ? this->SaveNewScore(posNewScore,game) : this->ShowBestScores();
}

void HighScores::SaveNewScore(int i, Game &game){
	//clear stringstream
	ss.clear();
	ss.str(""); 
	//clear text
	m_t.setString("");
	
	//create new high score
	Score new_score;
	std::string str;
	std::string c = "";
	while (str.length() < 3){
		game.IM.key_pressed = 0; //clear previous saved key
		
		//display text
		ss << "Ingresa tu nombre (AAA format): \n\n" << setw(18) << str;
		this->SetText(ss.str());
		game.Draw();
		
		while(game.IM.key_pressed == 0){
			game.ProcessEvents(); //to read keyboard inputs
			c = game.IM.ReturnKeyValue();
		}
		
		str += c;
		
//		cout de testing
//		std::cout << c << "\n length" << str.length();
	}
	
	strcpy(new_score.name,str.c_str());
	new_score.score = total_score;
	
	//insert new score
	auto it = high_scores.begin()+i;
	
	high_scores.insert(it,new_score);
	high_scores.resize(high_scores.size()-1); //delete last one
	
	this->ShowBestScores();
}
//############################
void HighScores::ResetHighScores(){
	std::string str = "AAA";
	Score s;
	high_scores.clear();
	
	for(int i=5;i>0;i--) { 
		strcpy(s.name , str.c_str() );
		s.score = 200*i;
		high_scores.push_back(s);
	}
}
