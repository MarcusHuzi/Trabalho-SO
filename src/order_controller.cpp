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


////////////////////////// MÉTODOS PRIVADOS ///////////////////////////////////

// Espera pelo relógio do pedido.
bool OrderController::wait_for_orders_clock(Order *order, int *current_life){

    // Validação
    while(order->get_clock() > 0){
        if((*current_life) <= 0)
            return false;

        // Espera
        std::this_thread::sleep_for(std::chrono::milliseconds(980));
    }

    // Estado crítico
    if(order->get_status() == WAITING){
        order->set_status(FAILED);
        return false;
    }

    // Fim convencional
    return true;
}


// Algoritmo de encerramento da lógica da thread do controlador do pedido.
void OrderController::end_thread_logic(OrderSemaphore *kitchen, OrderSemaphore *tables, int *current_life){

    // Espera
    wait_for_orders_clock(OrderController::order, current_life);

    // Marcação
    OrderController::active = false;
    OrderController::removed = true;

    // Liberação
    if(kitchen != NULL)
        kitchen->release();
    if(tables != NULL)
        tables->release();
}


// Lógica da thread do controlador do pedido.
void OrderController::thread_logic(OrderSemaphore *kitchen, OrderSemaphore *tables, int *current_life){

    // Espera por uma mesa
    if( tables->wait(OrderController::order, current_life) == false )
        return OrderController::end_thread_logic(NULL, NULL, current_life);
    
    // Ativação do pedido
    OrderController::active = true;

    // Espera pela liberação da cozinha
    if( kitchen->wait(OrderController::order, current_life) == false ){
        if(OrderController::order->get_status() == WAITING && (*current_life) > 0)
            OrderController::order->set_status(FAILED);
        return OrderController::end_thread_logic(NULL, tables, current_life);
    }

    // Estado de preparação
    OrderController::order->set_status(PREPARING);

    // Espera pelo relógio chegar a zero.
    if( wait_for_orders_clock(OrderController::order, current_life) == false )
        return OrderController::end_thread_logic(kitchen, tables, current_life);

    // Atualiza para estado de servindo
    OrderController::order->set_status(SERVING);

    // Libera a vaga da cozinha
    kitchen->release();

    // Espera pelo relógio chegar a zero novamente
    if( wait_for_orders_clock(OrderController::order, current_life) == false )
        return OrderController::end_thread_logic(NULL, tables, current_life);

    // Estado de término
    OrderController::order->set_status(FULLFILLED);

    // Finalização
    return OrderController::end_thread_logic(NULL, tables, current_life);
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
    return left.order < right.order;
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