#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

// Bibliotecas-padrão

#include <iostream>
#include <thread>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <semaphore.h>

// Bibliotecas locais
#include "../lib/level_controller.hpp"

using namespace std;

class Environment{

private:
	
	//vida maxima
	int max_life;

	//vida atual do jogador
	int current_life;

	//ajustes de dificuldade
	LevelController level_controller;

public:
	
	//Construtor
	Environment(int max_life, int current_life, LevelController level_controller);
	
	//retorna vida maxima
	int get_max_life();
	
	//define vida maxima
	int set_max_life(int x);
	
	//retorna vida atual
	int get_current_life();

	//decrementa vida atual
	void decrement_current_life();
	
	//retorna se o nivel foi finalizado ou nao
	bool has_finished();

};

#endif /*_ENVIRONMENT_H_*/
