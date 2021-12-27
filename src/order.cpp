///////////////////////////// IMPORTAÇÕES /////////////////////////////////////

using namespace std;

// Bibliotecas-padrão
#include <string>
#include <thread>
#include <semaphore.h>

// Bibliotecas locais
#include "../lib/order.hpp"

////////////////////////// MÉTODOS PRIVADOS ///////////////////////////////////

// Construtor do pedido.
Order::Order(int id, int max_waiting_time, Meal *meal){
    Order::id = id;
    Order::clock = max_waiting_time;
    Order::status = WAITING;
    Order::meal = new Meal(meal->get_meal_name(), meal->get_prep_time());
}


////////////////////////// MÉTODOS PÚBLICOS ///////////////////////////////////

// Operador de comparação.
bool operator< (const Order &left, const Order &right) {
    return left.id < right.id;
}


// Métodos acessores de leitura.
int Order::get_id(){ return Order::id; }
int Order::get_clock(){ return Order::clock; }
OrderStatus Order::get_status(){ return Order::status; }


// Atualização do estado.
void Order::set_status(OrderStatus status){ 

    // Atribuição
    Order::status = status; 

    // Atualização de relógio
    if(status == FULLFILLED)
        Order::clock = 3;
    else if(status == FAILED)
        Order::clock = 3;
    else
        Order::clock = 8;
}


// Decremento de relógio.
void Order::decrement_clock(){ Order::clock = Order::clock - 1; }


// Conversão para string.
string Order::to_string(){
    string output;
    //Meal *meal = Order::meal;

    output.append("Client " + std::to_string(Order::id) + " wants a tasty " + Order::meal->get_meal_name() + ".\n");

    switch(Order::status){
        case WAITING:
            output.append("This order is currently [WAITING] ");
            output.append("Order " + std::to_string(Order::id) + ": ");
            output.append(std::to_string(Order::clock));
            output.append(" seconds left for starvation.");
            break;
        case PREPARING:
            output.append("This order is currently [PREPARING] ");
            output.append("Order " + std::to_string(Order::id) + ": ");
            output.append(std::to_string(Order::clock));
            output.append(" seconds left for preparation.");
            break;
        case SERVING:
            output.append("This order is currently [SERVING] ");
            output.append("Order " + std::to_string(Order::id) + ": ");
            output.append(std::to_string(Order::clock));
            output.append(" seconds left to fullfill.");
            break;
        case FULLFILLED:
            output.append("This order is currently [FULLFILLED] ");
            output.append("Order " + std::to_string(Order::id) + ".");
            break;
        default:
            output.append("This order is currently [FAILED] ");
            output.append("Order " + std::to_string(Order::id) + ".");
            break;
    }
    return output;
}

Meal *Order::get_order_meal(){  return Order::meal; }