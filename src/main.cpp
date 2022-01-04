//////////////////////////////// INFO /////////////////////////////////////////
/*
*
* Trabalho para finalização da disciplina de Sistemas Operacionais I, 
* SCC0140, para o segundo semestre letivo de 2021.
*
* Autores: 
* João Lucas Rodrigues Constantino, 11795763.
* Marcus Vinícius Teixeira Huziwara, 11834432.
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
#include "../lib/level_controller.hpp"

// Limpeza de console dependente do SO
#ifdef __unix__
    #define clear_console() system("clear")
#elif defined(_WIN32) || defined(WIN32)
    #define clear_console() system("CLS")
#endif

////////////////////////// FUNÇÕES AUXILIARES /////////////////////////////////

// Função para imprimir o menu do jogo com todas as operações
void print_options(){
	cout << "------------------------Menu----------------------" << endl;
	cout << "Selecione uma das opções abaixo:" << endl;
	cout << "1 - Iniciar novo jogo - Dificuldade Fácil" << endl;
	cout << "2 - Iniciar novo jogo - Dificuldade Média" << endl;
	cout << "3 - Iniciar novo jogo - Dificuldade Difícil" << endl;
	cout << "4 - Instruções do jogo" << endl;
	cout << "5 - Sair do jogo" << endl << endl;
	cout << "Sua escolha: ";
}

// Função para inserções de operações inválidas
void print_invalid(){
	cout << "Você inseriu uma operação inválida..." << endl << endl;
	print_options();
}

// Função para saída do jogo
void print_exit(int sucess_levels, int failed_levels){
	cout << endl << "Você escolheu sair do jogo." << endl;
	cout << "Enquanto jogava, você venceu " << sucess_levels << " vez(es) e perdeu " << failed_levels << endl;
	cout << endl << "Obrigado por jogar!!!" << endl;
}

// Função para instruções do jogo
void print_instructions(){
	cout << endl << endl;
	cout << "------------------------Termos de Serviço do Restaurante------------------------" << endl;
	cout << "Seguem abaixo os procedimentos que você, novo(a) gerente, deverá seguir diariamente para satifazer nossos clientes." << endl;
	cout << "1 - Deve selecionar uma dificuldade (fácil, média ou difícil). A dificuldade do serviço define a quantidade de mesas a serem servidas" << endl;
	cout << "    assim como a quantidade de refeições disponíveis para os clientes escolherem. Para todas as dificuldades, você poderá cometer até 3 erros antes de ser demitido." << endl;
	cout << "2 - Devido à pandemia da COVID-19, foi necessária uma redução no número de cozinheiros. Você deverá coordenar o atendimento junto com o único cozinheiro" << endl;
	cout << "    presente no restaurante; ele já foi instruído a seguir suas ordens e priorizar os pedidos que você escolher." << endl;
	cout << "3 - É sua responsabilidade analisar quanto tempo cada cliente está esperando e quanto tempo é necessário para o preparo da refeição solicitada por ele." << endl;
	cout << "4 - Após finalizar o serviço do dia, você pode escolher entre coordenar o restaurante por mais turnos ou se demitir e procurar outras oportunidades." << endl;
	cout << endl << "Mais uma vez, seja bem vindo(a) ao nosso restaurante" << endl << endl;
}

//////////////////////////////// MAIN() ///////////////////////////////////////

int main(void){

	// Operação selecionada pelo usuário
	int option;

	// Máximo de pedidos
	int limit_order;

	// Quantidade de níveis vencidos
	int sucess_levels = 0;

	// Quantidade de níveis perdidos
	int failed_levels = 0;

	while(option != 5){
		clear_console();

		// Recebendo uma operação válida
		print_options();
		cin >> option;
		while(option <= 0 || option > 5){
			print_invalid();
			cin >> option;
		}

		// Imprimindo instruções até seleção da dificuldade
		while(option == 4){
			print_instructions();
			cout << endl << endl;
			print_options();
			cin >> option;
		}

		// Caso usuário queira parar de jogar
		if(option == 5){
			print_exit(sucess_levels, failed_levels);
			break;
		}

		// Criando Controlador apropriado
		LevelController controller = LevelController(5 * option, 3, option);

		// Determinando limite de pedidos da fase atual
		limit_order = (option + 1) * 5;

		// Cria pedidos da fase atual
		controller.setup_phase(limit_order);

		// Inicialização da thread do controlador
		controller.start_thread();

		// Atualizar contagem de níveis vencidos e perdidos
		if(!controller.has_failed())	sucess_levels++;
		else	failed_levels++;
	}

	return EXIT_SUCCESS;
}