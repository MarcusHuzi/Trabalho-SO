// Bibliotecas padrão
#include <experimental/random>

// Biblioteca local
#include "../lib/menu.hpp"

// Lista base de possíveis refeições a serem selecionadas
const string plates[15] = {"Feijoada", "Pernil", "Frango à Passarinho", "Espaguete", "Bolo de Chocolate",
                            "Lasanha", "Torta de Limão", "Milkshake", "Cuscuz", "Batata Recheada", "Pizza",
                            "X-Bacon", "Pudim de Leite", "Estrogonofe de Carne", "Nhoque de Mandioquinha"};

// Lista do tempo de preparo de cada refeição
const int prepare[15] = {15, 35, 20, 15, 25, 25, 20, 15, 25, 30, 30, 10, 25, 20, 30};

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

    while(count++ != Menu::max_meals){
        index = experimental::randint(0, 15);
        if(!used[index]){
            Menu::add_meal(new Meal(plates[index], prepare[index]));
            used[index] = 1;
        }
    }
}

// Métodos acessores
void Menu::add_meal(Meal *meal){ Menu::meals.push_back(meal); }

void Menu::remove_meal(Meal *meal){
    vector <Meal *>::iterator it;

    it = find(Menu::meals.begin(), Menu::meals.end(), meal);
    if(it != Menu::meals.end()) Menu::meals.erase(it);
}

Meal *Menu::rand_meals(){
    int index = experimental::randint(0, max_meals);
    return Menu::meals[index];
}