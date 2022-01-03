#ifndef _MEAL_H_
#define _MEAL_H_

#include <iostream>
using namespace std;

// Representa uma refeição do restaurante
class Meal{
private:

    // Nome do prato
    string name;

    // Tempo necessário para o preparo do prato
    int prep_time;

public:

    Meal(string name, int prep_time);

    // Retorna nome do prato
    string get_meal_name();

    // Retorna tempo necessário para o preparo da refeição
    int get_prep_time();
};

#endif /*_MEAL_H_*/