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
    Order::status = ESPERANDO;
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
    if(status == SATISFEITO)
        Order::clock = 3;
    else if(status == FALHOU)
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

    output.append("Cliente " + std::to_string(Order::id) + " quer um(a) delicioso(a) " + Order::meal->get_meal_name() + ".\n");

    switch(Order::status){
        case ESPERANDO:
            output.append("Este pedido se encontra [ESPERANDO] ");
            output.append("Pedido " + std::to_string(Order::id) + ": ");
            output.append(std::to_string(Order::clock));
            output.append(" segundos restantes para fome intensa.");
            break;
        case PREPARANDO:
            output.append("Este pedido se encontra [PREPARANDO] ");
            output.append("Pedido " + std::to_string(Order::id) + ": ");
            output.append(std::to_string(Order::clock));
            output.append(" segundos restantes para preparo.");
            break;
        case SERVINDO:
            output.append("Este pedido se encontra [SERVINDO] ");
            output.append("Pedido " + std::to_string(Order::id) + ": ");
            output.append(std::to_string(Order::clock));
            output.append(" segundos restantes para satisfazer cliente.");
            break;
        case SATISFEITO:
            output.append("Este pedido se encontra [SATISFEITO] ");
            output.append("Pedido " + std::to_string(Order::id) + ".");
            break;
        default:
            output.append("Este pedido se encontra [FALHOU] ");
            output.append("Pedido " + std::to_string(Order::id) + ".");
            break;
    }
    return output;
}

Meal *Order::get_order_meal(){  return Order::meal; }