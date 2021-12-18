#ifndef _ORDER_CONTROLLER_H_
#define _ORDER_CONTROLLER_H_

///////////////////////////// IMPORTAÇÕES /////////////////////////////////////

using namespace std;

// Bibliotecas-padrão
#include <thread>
#include <semaphore.h>

// Bibliotecas locais
#include "../lib/order.hpp"

///////////////////////////////////////////////////////////////////////////////

/// Classe controladora de um pedido.
class OrderController{
private:

    // Referência ao pedido.
    Order *order;

    // Própria thread.
    thread self_thread;

    // Indica se foi ou não removido (para sincronização).
    bool removed;

    // Função de controle da thread interna.
    void thread_logic(sem_t *kitchen, sem_t *tables);

public:

    /// Construtor.
    OrderController(Order *order, sem_t *kitchen, sem_t *tables);

    /// Operador de comparação.
    friend bool operator< (const OrderController &left, const OrderController &right);

    /// Retorna se foi ou não logicamente removido.
    bool is_removed();

    /// Retorna referência para o pedido.
    Order *get_order();

    /// Inicializa a própria thread.
    void start_thread();
};

///////////////////////////////////////////////////////////////////////////////

#endif