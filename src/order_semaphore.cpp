///////////////////////////// IMPORTAÇÕES /////////////////////////////////////

using namespace std;

// Bibliotecas-padrão
#include <thread>
#include <chrono>

// Bibliotecas locais
#include "../lib/order.hpp"
#include "../lib/order_semaphore.hpp"

///////////////////////////////////////////////////////////////////////////////

// Construtor padrão (mutex)
OrderSemaphore::OrderSemaphore(){
    OrderSemaphore::max_signal = 1;
    OrderSemaphore::current_signal = 0;
}


// Construtor alternativo.
OrderSemaphore::OrderSemaphore(unsigned int max_signal){
    if(max_signal > 0)
        OrderSemaphore::max_signal = max_signal;
    else
        OrderSemaphore::max_signal = 1;
    OrderSemaphore::current_signal = 0;
}


// Espera.
bool OrderSemaphore::wait(Order *order, int *current_life){

    // Laço de espera
    while(OrderSemaphore::current_signal >= OrderSemaphore::max_signal){

        // Verificação de falha
        OrderStatus status = order->get_status();
        if(status == FAILED || status == FULLFILLED || (*current_life) <= 0) return false;

        // Suspensão temporária
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }

    // Incremento do sinal
    OrderSemaphore::current_signal += 1;

    // Retorno convencional
    return true;
}


// Libera.
void OrderSemaphore::release(){
    if(OrderSemaphore::current_signal > 0){
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        OrderSemaphore::current_signal -= 1;
    }
}