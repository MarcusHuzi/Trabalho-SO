#ifndef _LEVEL_CONTROLLER_H_
#define _LEVEL_CONTROLLER_H_

///////////////////////////// IMPORTAÇÕES /////////////////////////////////////

using namespace std;

// Bibliotecas-padrão
#include <set>
#include <thread>

// Bibliotecas locais
#include "../lib/order.hpp"
#include "../lib/order_controller.hpp"
#include "../lib/order_semaphore.hpp"

///////////////////////////////////////////////////////////////////////////////

/// Classe controladora dos níveis do jogo de restaurante.
class LevelController {
private:

    // Thread do controlador
    thread self_thread;

    // Indica se o nível foi ou não finalizado.
    bool finished, failed;

    // Conjuntos de pedidos atuais.
    set<OrderController *> current_orders;

    // Semáforo da cozinha.
    OrderSemaphore kitchen;

    // Semáforo das mesas
    OrderSemaphore tables;

    // Vidas atuais do jogador
    int current_life;
    
    /// Operador para controle da thread.
    void thread_controller();

public:

    // Construtor.
    LevelController(unsigned int tables, int max_life);

    /// Retorna se o nível fora ou não finalizado.
    bool has_finished();

    /// Retorna se o jogador falhou ou não.
    bool has_failed();

    /// Inserção de um novo pedido; inicia uma thread para ele.
    void insert_order(Order *order);

    /// Inicializa a thread do controlador.
    void start_thread();
};


///////////////////////////////////////////////////////////////////////////////

#endif