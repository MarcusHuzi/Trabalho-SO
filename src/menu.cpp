// Bibliotecas padrão
#include <experimental/random>

// Biblioteca local
#include "../lib/menu.hpp"

// Lista base de possíveis refeições a serem selecionadas
string plates[20] = {"Feijoada", "Pernil", "Frango a Passarinho", "Espaguete", "Bolo de Chocolate",
                    "Lasanha", "Torta de Limao", "Milkshake", "Cuscuz", "Batata Recheada", "Pizza",
                    "X-Bacon", "Pudim de Leite", "Estrogonofe de Carne", "Nhoque de Mandioquinha",
                    "Bife de Chorizo", "Bife Ancho", "Costela Premium", "Lagosta", "Ratatouille"};

// Lista do tempo de preparo de cada refeição
int prepare[20] = {15, 35, 20, 15, 25, 25, 20, 15, 25, 30, 30, 10, 25, 20, 30, 15, 15, 25, 20, 20};

// Construtor do menu
Menu::Menu(int max_meals){
    Menu::max_meals = max_meals;
    Menu::meals.reserve(max_meals);
    Menu::generate_menu();
}

// Métodos privados
void Menu::generate_menu(){
    int count = 0, index = 0, used[20] = {0};

    while(count != Menu::max_meals){
        index = experimental::randint(0, 19);
        if(used[index] == 0){
            Meal meal = Meal(plates[index], prepare[index]);
            Menu::add_meal(meal);
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
    int index = experimental::randint(0, Menu::max_meals - 1);

    Meal meal = Meal(Menu::meals[index].get_meal_name(), Menu::meals[index].get_prep_time());
    return meal;
}

void Menu::list_menu(){
    int count = 1;
    vector <Meal>::iterator it;

    for(it = Menu::meals.begin(); it != Menu::meals.end(); it++, count++){
        cout << count << " - Nome: " << it->get_meal_name();
        if(it->get_meal_name().length() <= 5 && count < 10)  cout << "\t\t\t\t\t\tTempo de preparo: ";
        else if(it->get_meal_name().length() <= 12)  cout << "\t\t\t\t\tTempo de preparo: ";
        else if(it->get_meal_name().length() <= 20)  cout << "\t\t\t\tTempo de preparo: ";
        else    cout << "\t\t\tTempo de preparo: ";
        cout << it->get_prep_time() << endl;
    }
}

void Menu::clear_meals(){   Menu::meals.clear(); }