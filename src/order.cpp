///////////////////////////// IMPORTAÇÕES /////////////////////////////////////

using namespace std;

// Bibliotecas-padrão
#include <string>
#include <thread>

// Bibliotecas locais
#include "../lib/order.hpp"
#include "../lib/meal.hpp"

///////////////////////////////////////////////////////////////////////////////

// Construtor do pedido.
Order::Order(int id, int max_waiting_time, string meal_name, int prep_time){
    Order::id = id;
    Order::clock = max_waiting_time;
    Order::status = WAITING;
	Order::meal = new Meal(meal_name, prep_time);
}


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
        Order::clock = 1;
}


// Decremento de relógio.
void Order::decrement_clock(){ Order::clock = Order::clock - 1; }


// Conversão para string.
string Order::to_string(){
    string output;
    switch(Order::status){
        case WAITING:
            output.append("[WAITING] ");
            output.append("Order " + std::to_string(Order::id) + ": ");
            output.append(std::to_string(Order::clock));
            output.append(" seconds left for starvation.");
            break;
        case PREPARING:
            output.append("[PREPARING] ");
            output.append("Order " + std::to_string(Order::id) + ": ");
            output.append(std::to_string(Order::clock));
            output.append(" seconds left for preparation.");
            break;
        case SERVING:
            output.append("[SERVING] ");
            output.append("Order " + std::to_string(Order::id) + ": ");
            output.append(std::to_string(Order::clock));
            output.append(" seconds left to fullfill.");
            break;
        case FULLFILLED:
            output.append("[FULLFILLED] ");
            output.append("Order " + std::to_string(Order::id) + ".");
            break;
        default:
            output.append("[FAILED] ");
            output.append("Order " + std::to_string(Order::id) + ".");
            break;
    }
    return output;
}


// Reduz o relógio do pedido a cada segundo.
void order_clock_reducer_thread(Order *order){
	while(order->get_clock() > 0){
		order->decrement_clock();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}