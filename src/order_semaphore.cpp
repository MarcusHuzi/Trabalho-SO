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
OrderSemaphore::OrderSemaphore(){
    OrderSemaphore::max_signal = 1;
    OrderSemaphore::current_signal = 0;
    sem_init(&(OrderSemaphore::signal_semaphore), 0, 1);
}


// Construtor alternativo.
OrderSemaphore::OrderSemaphore(unsigned int max_signal){
    if(max_signal > 0)
        OrderSemaphore::max_signal = max_signal;
    else
        OrderSemaphore::max_signal = 1;
    OrderSemaphore::current_signal = 0;
    sem_init(&(OrderSemaphore::signal_semaphore), 0, 1);
}


// Espera.
bool OrderSemaphore::wait(Order *order, int *current_life){

    // Laço de espera
    while(OrderSemaphore::current_signal >= OrderSemaphore::max_signal){

        // Verificação de falha
        if((*current_life) <= 0 || order->get_clock() <= 0) return false;

        // Suspensão temporária
        std::this_thread::sleep_for(std::chrono::milliseconds(900));
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