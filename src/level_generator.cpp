// Bibliotecas locais
#include "../lib/level_generator.hpp"

// Construtor
LevelGenerator::LevelGenerator(int difficulty){
    LevelGenerator::difficulty = difficulty;
    LevelGenerator::numberOfOrders = 0;
    if(difficulty == 1)
        LevelGenerator::menu = new Menu(5);
    else if(difficulty == 2)
        LevelGenerator::menu = new Menu(10);
    else
        LevelGenerator::menu = new Menu(15);
}

// Métodos públicos
Order *LevelGenerator::new_order(){
    Meal meal = LevelGenerator::menu->rand_meals();
    LevelGenerator::numberOfOrders++;
    return new Order(LevelGenerator::numberOfOrders - 1, meal.get_prep_time() + 10, &meal);
}

void LevelGenerator::plates(){
    LevelGenerator::menu->list_menu();
    cout << endl;
}

int LevelGenerator::get_difficulty(){ return LevelGenerator::difficulty; }

void LevelGenerator::erase_menu(){
    LevelGenerator::menu->clear_meals();
    delete menu;
}