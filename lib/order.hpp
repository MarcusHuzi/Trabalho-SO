#ifndef _ORDER_H_
#define _ORDER_H_

///////////////////////////// IMPORTAÇÕES /////////////////////////////////////

using namespace std;

// Bibliotecas-padrão
#include <string>

// Bibliotecas locais
#include "../lib/meal.hpp"

//////////////////////////// ENUMERAÇÕES //////////////////////////////////////

// Estado de um pedido em um restaurante.
enum OrderStatus {
    WAITING, 
    PREPARING, 
    SERVING, 
    FULLFILLED, 
    FAILED
};


////////////////////////////// CLASSES ////////////////////////////////////////

/// Representa um pedido em um restaurante.
class Order {
private:

    // Número de identificação do pedido.
    int id;
    
    // Relógio do pedido; contabiliza tempos restantes.
    int clock;

    // Estado do pedido.
    OrderStatus status;

    // Refeição desejada
    Meal *meal;

public:

    /**  
     * @param id Número de identificação do pedido.
     * @param max_waiting_time Tempo máximo, em segundos, que o pedido pode 
     * ficar em estado de espera, que se trata de seu estado inicial. Desse 
     * modo, o relógio do pedido é inicializado nesse tempo.
    */
    Order(int id, int max_waiting_time, Meal *meal);

    /// Compara dois pedidos com base em seu número de identificação.
    friend bool operator< (const Order &left, const Order &right);

    /// Retorna o número identificador do pedido.
    int get_id();

    /// Retorna o valor atual do relógio armazenado pelo pedido.
    int get_clock();

    /// Retorna o estado atual do pedido.
    OrderStatus get_status();

    /** 
     * Atualiza o estado do pedido. 
     * @param status Estado ao qual atualizar o pedido.
    */
    void set_status(OrderStatus status);

    /// Decrementa o relógio atual da classe em uma unidade.
    void decrement_clock();

    /// Retorna uma visualização do pedido.
    string to_string();

    // Retorna refeição associada
    Meal *get_order_meal();
};


///////////////////////////////////////////////////////////////////////////////

#endif