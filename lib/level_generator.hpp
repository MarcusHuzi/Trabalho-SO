#ifndef _LEVEL_GENERATOR_H_
#define _LEVEL_GENERATOR_H_

// Bibliotecas locais
#include "../lib/menu.hpp"
#include "../lib/order.hpp"

class LevelGenerator {
private:

    // Nível de dificuldade do nível
    int difficulty;

    // Quantidade de mesas no restaurante;
    int tables;

    // Número de pedidos criados;
    int numberOfOrders;

    // Menu do restaurante
    Menu* menu;

public:

    // Construtor
    LevelGenerator(int difficulty);

    // Cria novos pedidos
    Order *new_order();
};

#endif /* _LEVEL_GENERATOR_H_ */