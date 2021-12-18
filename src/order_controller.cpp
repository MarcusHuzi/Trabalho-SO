///////////////////////////// IMPORTAÇÕES /////////////////////////////////////

using namespace std;

// Bibliotecas-padrão
#include <iostream>
#include <string>
#include <thread>
#include <semaphore.h>

// Bibliotecas locais
#include "../lib/order_controller.hpp"
#include "../lib/order.hpp"

////////////////////////// MÉTODOS PRIVADOS ///////////////////////////////////

// Lógica da thread do controlador do pedido.
void OrderController::thread_logic(sem_t *kitchen, sem_t *tables){

    // Espera por uma mesa
    sem_wait(tables);

    // Entrada na cozinha
    if(OrderController::order->get_status() == WAITING){

        // Espera pela liberação da cozinha
        sem_wait(kitchen);

        // Verificação de validação
        if(OrderController::order->get_status() == WAITING)
            OrderController::order->set_status(PREPARING);
    }

    // Saída da cozinha
    if(OrderController::order->get_status() == PREPARING){

        // Espera pelo relógio chegar a zero.
        while(OrderController::order->get_clock() > 0);

        // Libera a vaga da cozinha
        sem_post(kitchen);

        // Atualiza para estado de servindo
        OrderController::order->set_status(SERVING);

        // Espera pelo relógio chegar a zero novamente
        while(OrderController::order->get_clock() > 0);
    }

    // Marca como removido
    OrderController::removed = true;

    // Liberação da mesa
    sem_post(tables);
}


////////////////////////// MÉTODOS PÚBLICOS ///////////////////////////////////

// Construtor.
OrderController::OrderController(Order *order, sem_t *kitchen, sem_t *tables){
    OrderController::order = order;
    OrderController::self_thread = thread(&OrderController::thread_logic, this, kitchen, tables);
    OrderController::removed = false;
}


// Operador comparativo.
bool operator< (const OrderController &left, const OrderController &right){
    return left.order->get_id() < right.order->get_id();
}


// Indica se foi ou não logicamente removido.
bool OrderController::is_removed(){
    return OrderController::removed;
}


// Retorna a referência ao pedido controlado.
Order *OrderController::get_order(){
    return OrderController::order;
}


// Inicializa a thread do controlador.
void OrderController::start_thread(){
    OrderController::self_thread.join();
}