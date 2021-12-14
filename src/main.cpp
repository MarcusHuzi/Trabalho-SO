//////////////////////////////// INFO /////////////////////////////////////////
/*
*
* Trabalho para a disciplina SCC0218 - Algoritmos Avançados e Aplicações, 
* turma A do segundo semestre de 2021.
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

// Bibliotecas locais
#include "../lib/order.hpp"

////////////////////////// FUNÇÕES AUXILIARES /////////////////////////////////

// Função para thread de impressão.
void print_orders(Order *a, Order *b, Order *c){

	// Variáveis locais
	int clock_a, clock_b, clock_c;
	int id_a = a->get_id(), id_b = b->get_id(), id_c = c->get_id();

	// Impressão a cada segundo
	do {

		// Limpeza da janela
		system("clear");

		// Obtenção dos relógios
		clock_a = a->get_clock();
		clock_b = b->get_clock();
		clock_c = c->get_clock();

		// Impressão
		cout << "Thread " << id_a << ": " << clock_a << " seconds remaining." << endl;
		cout << "Thread " << id_b << ": " << clock_b << " seconds remaining." << endl;
		cout << "Thread " << id_c << ": " << clock_c << " seconds remaining." << endl;

		// Espera por um segundo
		std::this_thread::sleep_for(std::chrono::seconds(1));

	// Execução enquanto ainda houver relógios positivos
	} while(clock_a > 0 || clock_b > 0 || clock_c > 0);
}


//////////////////////////////// MAIN() ///////////////////////////////////////

int main(void){

	// Pedidos
	Order order_a = Order(9, 5);
	Order order_b = Order(21, 9);
	Order order_c = Order(37, 7);

	// Threads
	thread order_printer(print_orders, &order_a, &order_b, &order_c);
	thread order_thread_a(order_clock_reducer_thread, &order_a);
	thread order_thread_b(order_clock_reducer_thread, &order_b);
	thread order_thread_c(order_clock_reducer_thread, &order_c);

	// Inicialização das threads
	order_printer.join();
	order_thread_a.join();
	order_thread_b.join();
	order_thread_c.join();

	return EXIT_SUCCESS;
}