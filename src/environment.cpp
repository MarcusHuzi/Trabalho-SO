#include <iostream>
#include <thread>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <semaphore.h>

#include "../lib/environment.hpp"
#include "../lib/level_controller.hpp"

using namespace std;

//contrutor
Environment::Environment(int max_life, int current_life, LevelController level_controller){
	Environment::max_life = max_life;
	Environment::current_life = current_life;
	Environment::level_controller = level_controller;

}

//métodos públicos
int Environment::get_max_life(){
	return Environment::max_life;
}

int Environment::set_max_life(int x){
	Environment::max_life = x;
	return Environment::max_life;
}

int Environment::get_current_life(){
	return Environment::current_life;
}

void Environment::decrement_current_life(){
	Environment::current_life -= 1;
}

bool Environment::has_finished(){ 
    return Environment::level_controller.finished;
}
