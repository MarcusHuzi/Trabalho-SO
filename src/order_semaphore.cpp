///////////////////////////// IMPORTAÇÕES /////////////////////////////////////

using namespace std;

// Bibliotecas-padrão
#include <thread>
#include <chrono>
#include <semaphore.h>

// Bibliotecas locais
#include "../lib/order.hpp"
#include "../lib/order_semaphore.hpp"

///////////////////////////////////////////////////////////////////////////////

// Construtor padrão (mutex)
OrderSemaphore::OrderSemaphore(int preferential_order_id){
    OrderSemaphore::max_signal = 1;
    OrderSemaphore::current_signal = 0;
    OrderSemaphore::preferential_order_id = preferential_order_id;
    sem_init(&(OrderSemaphore::signal_semaphore), 0, 1);
}


// Construtor alternativo.
OrderSemaphore::OrderSemaphore(unsigned int max_signal, int preferential_order_id){
    if(max_signal > 0)
        OrderSemaphore::max_signal = max_signal;
    else
        OrderSemaphore::max_signal = 1;
    OrderSemaphore::current_signal = 0;
    OrderSemaphore::preferential_order_id = preferential_order_id;
    sem_init(&(OrderSemaphore::signal_semaphore), 0, 1);
}


// Espera.
bool OrderSemaphore::wait(Order *order, int *current_life){

    // Laço de espera (sem preferência)
    if(OrderSemaphore::preferential_order_id == SEMAPHORE_DISABLE_PREFERENCE){
        while (OrderSemaphore::current_signal >= OrderSemaphore::max_signal){

            // Verificação de falha
            if((*current_life) <= 0 || order->get_clock() <= 0) return false;

            // Suspensão temporária
            std::this_thread::sleep_for(std::chrono::milliseconds(900));
        }
    }else{
        int id = order->get_id();
        while (OrderSemaphore::current_signal >= OrderSemaphore::max_signal || OrderSemaphore::preferential_order_id != id){

            // Verificação de falha
            if((*current_life) <= 0 || order->get_clock() <= 0) return false;

            // Suspensão temporária
            std::this_thread::sleep_for(std::chrono::milliseconds(900));
        }
    }

    // Incremento do sinal
    OrderSemaphore::current_signal += 1;

    // Retorno convencional
    return true;
}


// Libera.
void OrderSemaphore::release(){

    // Espera pelo controle do sinal
    sem_wait(&(OrderSemaphore::signal_semaphore));

    // Atualização do sinal
    if(OrderSemaphore::current_signal > 0)
        OrderSemaphore::current_signal -= 1;

    // Liberação do controle do sinal
    sem_post(&(OrderSemaphore::signal_semaphore));
}


// Seleciona preferência.
void OrderSemaphore::set_preferential_order_id(int id){
    OrderSemaphore::preferential_order_id = id;
}


// Retorna se está ou não livre.
bool OrderSemaphore::is_free(){
    return OrderSemaphore::current_signal == 0;
}