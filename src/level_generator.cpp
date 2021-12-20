// Bibliotecas locais
#include "../lib/level_generator.hpp"

// Construtor
LevelGenerator::LevelGenerator(int difficulty){
    LevelGenerator::difficulty = difficulty;
    LevelGenerator::numberOfOrders = 0;
    if(difficulty == 0){
        LevelGenerator::menu = new Menu(5);
        LevelGenerator::tables = 8;
    }
    else if(difficulty == 1){
        LevelGenerator::menu = new Menu(10);
        LevelGenerator::tables = 10;
    }
    else if(difficulty == 2){
        LevelGenerator::menu = new Menu(15);
        LevelGenerator::tables = 12;
    }
}

// Métodos públicos
Order *LevelGenerator::new_order(){
    Meal *meal = LevelGenerator::menu->rand_meals();
    return new Order(numberOfOrders, meal->get_prep_time() + 10, meal);
}