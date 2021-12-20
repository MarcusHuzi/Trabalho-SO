// Bibliotecas padrão
#include <experimental/random>

// Biblioteca local
#include "../lib/menu.hpp"

// Lista base de possíveis refeições a serem selecionadas
string plates[15] = {"Feijoada", "Pernil", "Frango à Passarinho", "Espaguete", "Bolo de Chocolate",
                            "Lasanha", "Torta de Limão", "Milkshake", "Cuscuz", "Batata Recheada", "Pizza",
                            "X-Bacon", "Pudim de Leite", "Estrogonofe de Carne", "Nhoque de Mandioquinha"};

// Lista do tempo de preparo de cada refeição
int prepare[15] = {15, 35, 20, 15, 25, 25, 20, 15, 25, 30, 30, 10, 25, 20, 30};

// Lista auxiliar para controlar refeições utilizadas
int used[15] = {0};

// Construtor do menu
Menu::Menu(int max_meals){
    Menu::max_meals = max_meals;
    Menu::meals.reserve(max_meals);
    memset(used, 0, sizeof(used));
    Menu::generate_menu();
}

// Métodos privados
void Menu::generate_menu(){
    int count = 0, index;

    while(count != Menu::max_meals){
        index = experimental::randint(0, 15);
        if(used[index] == 0){
            Menu::add_meal(Meal(plates[index], prepare[index]));
            used[index] = 1;
            count++;
        }
    }
}

// Métodos acessores
void Menu::add_meal(Meal meal){ Menu::meals.push_back(meal); }

void Menu::remove_meal(Meal meal){
    vector <Meal>::iterator it;

    for(it = Menu::meals.begin(); it != Menu::meals.end(); it++){
        if(it->get_meal_name() == meal.get_meal_name()){
            Menu::meals.erase(it);
        }
    }
}

Meal Menu::rand_meals(){
    int index = experimental::randint(0, Menu::max_meals);
    Meal meal = Meal(Menu::meals[index].get_meal_name(), Menu::meals[index].get_prep_time());
    return meal;
}