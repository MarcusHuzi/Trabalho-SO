<<<<<<< HEAD
#include "../lib/meal.hpp"


// Construtor da refeição
Meal::Meal(string name, int prep_time){
    Meal::name = name;
    Meal::prep_time = prep_time;
}


// Métodos acessores
string Meal::get_meal_name(){ return name; }
=======
#include "../lib/meal.hpp"


// Construtor da refeição
Meal::Meal(string name, int prep_time){
    Meal::name = name;
    Meal::prep_time = prep_time;
}


// Métodos acessores
string Meal::get_meal_name(){ return name; }
>>>>>>> b6708f3058613cbb2b91e4c1f7ec700024ba0ad5
int Meal::get_prep_time(){ return prep_time; }