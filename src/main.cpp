//////////////////////////////// INFO /////////////////////////////////////////
/*
*
* Trabalho para finalização da disciplina de Sistemas Operacionais I, 
* SCC0140, para o segundo semestre letivo de 2021.
*
* Autores: 
* :
* Tulio Santana Ramos, 11795526.
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

// Função para imprimir o menu do jogo com todas as operações
void print_options(){
	cout << "------------------------Menu----------------------" << endl;
	cout << "Selecione uma das opções abaixo:" << endl;
	cout << "1 - Iniciar novo jogo - Dificuldade Fácil" << endl;
	cout << "2 - Iniciar novo jogo - Dificuldade Média" << endl;
	cout << "3 - Iniciar novo jogo - Dificuldade Difícil" << endl;
	cout << "4 - Sair do jogo" << endl << endl;
	cout << "Sua escolha:";
}

// Função para inserções de operações inválidas
void print_invalid(){
	cout << "Você inseriu uma operação inválida..." << endl << endl;
	print_options();
}

// Função para saída do jogo
void print_exit(){
	cout << "Você escolheu sair do jogo" << endl;
	cout << "Obrigado por jogar!!!" << endl;
}

//////////////////////////////// MAIN() ///////////////////////////////////////

int main(void){

	// Operação selecionada pelo usuário
	int option;

	// Máximo de pedidos
	int limit_order;

	// Pedidos
	// Order order_a = Order(9, 5);
	// Order order_b = Order(21, 9);
	// Order order_c = Order(37, 7);
    // Order order_d = Order(7, 10);
    // Order order_e = Order(12, 22);
    // Order order_f = Order(91, 14);

	// Controlador
	//LevelController controller = LevelController(3, 3);

	while(option != 4){

		// Recebendo uma operação válida
		print_options();
		cin >> option;
		while(option <= 0 || option > 4){
			print_invalid();
			cin >> option;
		}

		if(option == 4){
			print_exit();
			break;
		}

		// Criando Controlador apropriado
		LevelController controller = LevelController(5 * option, 3, option);

		// Determinando limite de pedidos da fase atual
		limit_order = (option * 5) + 10;

		// Cria pedidos da fase atual
		controller.setup_phase(limit_order);

		// Inicialização da thread do controlador
		controller.start_thread();
	}

    // Inserção dos pedidos
    // controller.insert_order(&order_a);
    // controller.insert_order(&order_b);
    // controller.insert_order(&order_c);
    // controller.insert_order(&order_d);
    // controller.insert_order(&order_e);
    // controller.insert_order(&order_f);


	return EXIT_SUCCESS;
}