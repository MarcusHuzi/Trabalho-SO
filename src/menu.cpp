#include "../lib/menu.hpp"


// Construtor do menu
Menu::Menu(int max_meals){
    Menu::max_meals = max_meals;
    Menu::meals.reserve(max_meals);
}

// Métodos acessores
void Menu::add_meal(Meal *meal){ Menu::meals.push_back(meal); }
void Menu::remove_meal(Meal *meal){
    vector <Meal *>::iterator it;

    it = find(Menu::meals.begin(), Menu::meals.end(), meal);
    if(it != Menu::meals.end()) Menu::meals.erase(it);
}