///////////////////////////// IMPORTAÇÕES /////////////////////////////////////

using namespace std;

// Bibliotecas-padrão
#include <iostream>
#include <string>
#include <thread>

// Bibliotecas locais
#include "../lib/order_controller.hpp"
#include "../lib/order.hpp"

////////////////////////// MÉTODOS PRIVADOS ///////////////////////////////////

// Lógica da thread do controlador do pedido.
void OrderController::thread_logic(OrderSemaphore *kitchen, OrderSemaphore *tables){

    // Espera por uma mesa
    tables->wait();
    OrderController::active = true;

    // Entrada na cozinha
    if(OrderController::order->get_status() == WAITING){

        // Espera pela liberação da cozinha
        kitchen->wait();

        // Verificação de validação
        if(OrderController::order->get_status() == WAITING)
            OrderController::order->set_status(PREPARING);
    }

    // Saída da cozinha
    if(OrderController::order->get_status() == PREPARING){

        // Espera pelo relógio chegar a zero.
        while(OrderController::order->get_clock() > 0);

        // Libera a vaga da cozinha
        kitchen->release();

        // Atualiza para estado de servindo
        OrderController::order->set_status(SERVING);

        // Espera pelo relógio chegar a zero novamente
        while(OrderController::order->get_clock() > 0);
    }

    // Marca como removido e inativo
    OrderController::removed = true;
    OrderController::active = false;

    // Liberação da mesa
    tables->release();
}


////////////////////////// MÉTODOS PÚBLICOS ///////////////////////////////////

// Construtor.
OrderController::OrderController(Order *order, OrderSemaphore *kitchen, OrderSemaphore *tables){
    OrderController::order = order;
    OrderController::self_thread = thread(&OrderController::thread_logic, this, kitchen, tables);
    OrderController::removed = false;
    OrderController::active = false;
}


// Operador comparativo.
bool operator< (const OrderController &left, const OrderController &right){
    return left.order->get_id() < right.order->get_id();
}


// Indica se foi ou não logicamente removido.
bool OrderController::is_removed(){
    return OrderController::removed;
}


// Indica se está ou não ativo.
bool OrderController::is_active(){
    return OrderController::active;
}


// Retorna a referência ao pedido controlado.
Order *OrderController::get_order(){
    return OrderController::order;
}


// Inicializa a thread do controlador.
void OrderController::start_thread(){
    OrderController::self_thread.join();
}