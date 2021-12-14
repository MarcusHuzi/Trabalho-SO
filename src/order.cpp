#include <thread>
#include "../lib/order.hpp"


// Construtor do pedido.
Order::Order(int id, int max_waiting_time){
    Order::id = id;
    Order::clock = max_waiting_time;
    Order::status = WAITING;
}


// Métodos acessores.
int Order::get_id(){ return Order::id; }
int Order::get_clock(){ return Order::clock; }
OrderStatus Order::get_status(){ return Order::status; }
void Order::set_status(OrderStatus status){ Order::status = status; }


// Decremento de relógio.
void Order::decrement_clock(){ Order::clock = Order::clock - 1; }


// Reduz o relógio do pedido a cada segundo.
void order_clock_reducer_thread(Order *order){
	while(order->get_clock() > 0){
		order->decrement_clock();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}