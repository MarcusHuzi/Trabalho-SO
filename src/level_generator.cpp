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
    else if(difficulty == 3)
        LevelGenerator::menu = new Menu(15);
}

// Métodos públicos
Order *LevelGenerator::new_order(){
    Meal *meal = LevelGenerator::menu->rand_meals();
    numberOfOrders++;
    return new Order(numberOfOrders - 1, meal->get_prep_time() + 10, meal);
}