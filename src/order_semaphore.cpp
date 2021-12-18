#include "../lib/order_semaphore.hpp"

// Construtor padrão (mutex)
OrderSemaphore::OrderSemaphore(){
    OrderSemaphore::max_signal = 1;
    OrderSemaphore::current_signal = 0;
}

// Construtor.
OrderSemaphore::OrderSemaphore(unsigned int max_signal){
    if(max_signal > 0)
        OrderSemaphore::max_signal = max_signal;
    else
        OrderSemaphore::max_signal = 1;
    OrderSemaphore::current_signal = 0;
}

// Espera.
void OrderSemaphore::wait(){
    while(OrderSemaphore::current_signal >= OrderSemaphore::max_signal);
    OrderSemaphore::current_signal += 1;
}

// Libera.
void OrderSemaphore::release(){
    if(OrderSemaphore::current_signal > 0)
        OrderSemaphore::current_signal -= 1;
}