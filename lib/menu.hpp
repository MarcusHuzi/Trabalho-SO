#ifndef _MENU_H_
#define _MENU_H_

#include <bits/stdc++.h>
#include "../lib/meal.hpp"
using namespace std;

// Representa o menu de um restaurante
class Menu{
private:

    // Representa a quantidade de refeições no menu
    int max_meals;

    // Representa as refeições do menu
    vector <Meal *> meals;

public:

    Menu(int max_meals);

    // Adiciona refeição ao menu do restaurante
    void add_meal(Meal *meal);

    // Remove refeição do menu do restaurante
    void remove_meal(Meal *meal);
};

#endif /*_MENU_H_*/