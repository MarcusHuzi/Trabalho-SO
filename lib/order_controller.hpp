#ifndef _ORDER_CONTROLLER_H_
#define _ORDER_CONTROLLER_H_

///////////////////////////// IMPORTAÇÕES /////////////////////////////////////

using namespace std;

// Bibliotecas-padrão
#include <thread>

// Bibliotecas locais
#include "../lib/order.hpp"
#include "../lib/order_semaphore.hpp"

///////////////////////////////////////////////////////////////////////////////

/// Classe controladora de um pedido.
class OrderController{
private:

    // Referência ao pedido.
    Order *order;

    // Própria thread.
    thread self_thread;

    // Utilitários de sincronização.
    bool removed, active;

    // Função de controle da thread interna.
    void thread_logic(OrderSemaphore *kitchen, OrderSemaphore *tables);

public:

    /// Construtor.
    OrderController(Order *order, OrderSemaphore *kitchen, OrderSemaphore *tables);

    /// Operador de comparação.
    friend bool operator< (const OrderController &left, const OrderController &right);

    /// Retorna se foi ou não logicamente removido.
    bool is_removed();

    /// Retorna se está ou não atualmente ativo.
    bool is_active();

    /// Retorna referência para o pedido.
    Order *get_order();

    /// Inicializa a própria thread.
    void start_thread();
};

///////////////////////////////////////////////////////////////////////////////

#endif