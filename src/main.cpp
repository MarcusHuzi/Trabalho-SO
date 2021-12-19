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
#include "../lib/level_controller.hpp"


////////////////////////// FUNÇÕES AUXILIARES /////////////////////////////////



//////////////////////////////// MAIN() ///////////////////////////////////////

int main(void){

	// Pedidos
	Order order_a = Order(9, 5);
	Order order_b = Order(21, 9);
	Order order_c = Order(37, 7);
    Order order_d = Order(7, 10);
    Order order_e = Order(12, 22);
    Order order_f = Order(91, 14);

	// Controlador
	LevelController controller = LevelController(3, 3);

    // Inserção dos pedidos
    controller.insert_order(&order_a);
    controller.insert_order(&order_b);
    controller.insert_order(&order_c);
    controller.insert_order(&order_d);
    controller.insert_order(&order_e);
    controller.insert_order(&order_f);

	// Inicialização da thread do controlador
	controller.start_thread();

	return EXIT_SUCCESS;
}