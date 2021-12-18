#ifndef _LEVEL_CONTROLLER_H_
#define _LEVEL_CONTROLLER_H_

///////////////////////////// IMPORTAÇÕES /////////////////////////////////////

using namespace std;

// Bibliotecas-padrão
#include <set>
#include <thread>
#include <semaphore.h>

// Bibliotecas locais
#include "../lib/order.hpp"
#include "../lib/order_controller.hpp"

///////////////////////////////////////////////////////////////////////////////

/// Classe controladora dos níveis do jogo de restaurante.
class LevelController {
private:

    // Thread do controlador
    thread self_thread;

    // Indica se o nível foi ou não finalizado.
    bool finished;

    // Conjuntos de pedidos atuais.
    set<OrderController *> current_orders;

    // Semáforo da cozinha.
    sem_t kitchen;

    // Semáforo das mesas
    sem_t tables;

    /// Realiza operações de processamento de um pedido corrente.
    void process_order(Order *order);

    /// Operador para controle da thread.
    void thread_controller();

public:

    // Construtores.
    LevelController(unsigned int tables);

    /// Retorna se o nível fora ou não finalizado.
    bool has_finished();

    /// Inserção de um novo pedido; inicia uma thread para ele.
    void insert_order(Order *order);

    /// Inicializa a thread do controlador.
    void start_thread();
};


///////////////////////////////////////////////////////////////////////////////

#endif