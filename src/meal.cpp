#include "../lib/meal.hpp"


// Construtor da refeição
Meal::Meal(string name, int prep_time){
    Meal::name = name;
    Meal::prep_time = prep_time;
}


// Métodos acessores
string Meal::get_meal_name(){ return Meal::name; }
int Meal::get_prep_time(){ return Meal::prep_time; }