///////////////////////////// IMPORTAÇÕES /////////////////////////////////////

using namespace std;

// Bibliotecas-padrão
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

// Bibliotecas locais
#include "../lib/order_controller.hpp"
#include "../lib/order.hpp"

/////////////////////////// FUNÇÃO AUXILIAR ///////////////////////////////////

// Força a thread requisitante a dormir enquanto não zerar o relógio do pedido.
void wait_for_orders_clock(Order *order){
    while(order->get_clock() > 0)
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
}


////////////////////////// MÉTODOS PRIVADOS ///////////////////////////////////

// Lógica da thread do controlador do pedido.
void OrderController::thread_logic(OrderSemaphore *kitchen, OrderSemaphore *tables, int *current_life){

    // Espera por uma mesa
    if(tables->wait(OrderController::order, current_life) == false) {
        wait_for_orders_clock(OrderController::order);
        OrderController::active = false;
        OrderController::removed = true;
        return;
    }
    OrderController::active = true;

    // Espera pela liberação da cozinha
    if(kitchen->wait(OrderController::order, current_life) == false){
        wait_for_orders_clock(OrderController::order);
        OrderController::active = false;
        OrderController::removed = true;
        return;
    }

    // Estado de preparação
    OrderController::order->set_status(PREPARING);

    // Espera pelo relógio chegar a zero.
    wait_for_orders_clock(OrderController::order);

    // Libera a vaga da cozinha
    kitchen->release();

    // Atualiza para estado de servindo
    OrderController::order->set_status(SERVING);

    // Espera pelo relógio chegar a zero novamente
    wait_for_orders_clock(OrderController::order);

    // Marca como removido e inativo
    OrderController::removed = true;
    OrderController::active = false;

    // Liberação da mesa
    tables->release();
}


////////////////////////// MÉTODOS PÚBLICOS ///////////////////////////////////

// Construtor.
OrderController::OrderController(Order *order, OrderSemaphore *kitchen, OrderSemaphore *tables, int *current_life){
    OrderController::order = order;
    OrderController::self_thread = thread(&OrderController::thread_logic, this, kitchen, tables, current_life);
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