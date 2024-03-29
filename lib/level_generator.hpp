#ifndef _LEVEL_GENERATOR_H_
#define _LEVEL_GENERATOR_H_

// Bibliotecas locais
#include "../lib/menu.hpp"
#include "../lib/order.hpp"

class LevelGenerator {
private:

    // Nível de dificuldade do nível
    int difficulty;

    // Número de pedidos criados;
    int numberOfOrders;

    // Menu do restaurante
    Menu* menu;

public:

    // Construtor
    LevelGenerator(int difficulty);

    // Cria novos pedidos
    Order *new_order();

    // Imprime Refeições do Menu
    void plates();

    // Retorna dificuldade
    int get_difficulty();

    // Deleta menu
    void erase_menu();
};

#endif /* _LEVEL_GENERATOR_H_ */