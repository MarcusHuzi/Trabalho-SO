//////////////////////////////// INFO /////////////////////////////////////////
/*
*
* Trabalho para finalização da disciplina de Sistemas Operacionais I, 
* SCC0140, para o segundo semestre letivo de 2021.
*
* Autores: 
* :
* :
* João Lucas Rodrigues Constantino, 11795763.
*
*/
///////////////////////////// IMPORTAÇÕES /////////////////////////////////////

using namespace std;

// Bibliotecas-padrão
#include <cstdio>
#include <iostream>
#include <thread>
#include <stdlib.h>
#include <semaphore.h>
#include <set>

// Bibliotecas locais
#include "../lib/order.hpp"
#include "../lib/controller.hpp"


////////////////////////// FUNÇÕES AUXILIARES /////////////////////////////////

/**
 * Thread controladora de um pedido; utiliza semáforos para 
 * determinar se deve ou não executar em determinado instante.
 * 
 * @param controller Controlador do nível atual.
 * @param order Pedido a ser monitorado.
 */
void order_thread_controller(LevelController *controller, Order *order){

	// Espera por uma mesa
    sem_wait(controller->get_tables_semaphore());

    // Adição ao controlador
    controller->insert_order(order);

    // Entrada na cozinha
    if(order->get_status() == WAITING){

        // Espera pela liberação da cozinha
        sem_wait(controller->get_kitchen_semaphore());

        // Verificação de validação
        if(order->get_status() == WAITING)
            order->set_status(PREPARING);
    }

    // Saída da cozinha
    if(order->get_status() == PREPARING){
        while(order->get_clock() > 0);
        sem_post(controller->get_kitchen_semaphore());
        order->set_status(SERVING);
        while(order->get_clock() > 0);
    }

    // Liberação da mesa
    sem_post(controller->get_tables_semaphore());
}


//////////////////////////////// MAIN() ///////////////////////////////////////

int main(void){

	// Pedidos
	Order order_a = Order(9, 5);
	Order order_b = Order(21, 9);
	Order order_c = Order(37, 7);

	// Controlador
	LevelController controller(5);

	// Declaração das threads
	thread ta = thread(order_thread_controller, &controller, &order_a);
	thread tb = thread(order_thread_controller, &controller, &order_b);
	thread tc = thread(order_thread_controller, &controller, &order_c);

	// Inicialização das threads
	ta.join();
	tb.join();
	tc.join();

	// Inicialização da thread do controlador
	controller.start_thread();

	return EXIT_SUCCESS;
}