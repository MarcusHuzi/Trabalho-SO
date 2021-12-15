//////////////////////////////// INFO /////////////////////////////////////////
/*
*
* Trabalho para finalização da disciplina de Sistemas Operacionais I, 
* SCC0140, para o segundo semestre letivo de 2021.
*
* Autores: 
* :
* João Lucas Rodrigues Constantino, 11795763.
* Tulio Santana Ramos, 11795526.
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



//////////////////////////////// MAIN() ///////////////////////////////////////

int main(void){

	// Pedidos
	Order order_a = Order(9, 5);
	Order order_b = Order(21, 9);
	Order order_c = Order(37, 7);

	// Controlador
	LevelController controller;

	// Inserção dos pedidos
	controller.insert_order(&order_a);
	controller.insert_order(&order_b);
	controller.insert_order(&order_c);

	// Inicialização da thread do controlador
	controller.start_thread();

	return EXIT_SUCCESS;
}