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

    /** 
     * Força a thread requisitante a dormir enquanto não zerar o 
     * relógio do pedido e enquanto não zerar a vida do jogador. 
     * @return verdadeiro se foi um final de execução convencional, 
     * falso se fora interrompido pelo final do jogo.
     * */
    bool wait_for_orders_clock(Order *order, int *current_life);

    /// Algoritmo de encerramento da lógica da thread do controlador do pedido.
    void end_thread_logic(OrderSemaphore *kitchen, OrderSemaphore *tables, int *current_life);

    // Função de controle da thread interna.
    void thread_logic(OrderSemaphore *kitchen, OrderSemaphore *tables, int *current_life);

public:

    /// Construtor.
    OrderController(Order *order, OrderSemaphore *kitchen, OrderSemaphore *tables, int *current_life);

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