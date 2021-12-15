#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

///////////////////////////// IMPORTAÇÕES /////////////////////////////////////

using namespace std;

// Bibliotecas-padrão
#include <set>
#include <thread>
#include <semaphore.h>

// Bibliotecas locais
#include "../lib/order.hpp"
#include "../lib/menu.hpp"

///////////////////////////////////////////////////////////////////////////////

/// Classe controladora dos níveis do jogo de restaurante.
class LevelController {
private:

    // Thread do controlador
    thread self_thread;

    // Indica se o nível foi ou não finalizado.
    bool finished;

    // Conjunto de pedidos atuais.
    set<Order *> current_orders;

    // Semáforo da cozinha.
    sem_t kitchen;

    /// Processa um pedido; retorna verdadeiro se o pedido deve ser removido.
    bool process_order(Order *order);

    /// Operador para controle da thread.
    void thread_controller();

    // Menu do restaurante
    Menu *menu;

public:

    // Construtor.
    LevelController(int max_meals);

    /// Retorna se o nível fora ou não finalizado.
    bool has_finished();

    /// Inserção de um novo pedido; inicia uma thread para ele.
    void insert_order(Order *order);

    /// Remove um pedido atual se ele existir.
    void remove_order(Order *order);

    /// Inicializa a thread do controlador.
    void start_thread();
};


///////////////////////////////////////////////////////////////////////////////

#endif