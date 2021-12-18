///////////////////////////// IMPORTAÇÕES /////////////////////////////////////

using namespace std;

// Bibliotecas-padrão
#include <iostream>
#include <string>
#include <thread>
#include <set>
#include <chrono>
#include <stdlib.h>

// Bibliotecas locais
#include "../lib/order.hpp"
#include "../lib/level_controller.hpp"
#include "../lib/order_controller.hpp"

// Limpeza de console dependente do SO
#ifdef __unix__
    #define clear_console() system("clear")
#elif defined(_WIN32) || defined(WIN32)
    #define clear_console() system("CLS")
#endif


////////////////////////// MÉTODOS PRIVADOS ///////////////////////////////////

// Realiza operações de processamento de um pedido corrente.
void LevelController::process_order(Order *order){

    // Decremento de relógio
    order->decrement_clock();

    // Imprime o pedido
    cout << order->to_string() << endl << flush;

    // Verificação de relógio nulo
    if(order->get_clock() <= 0){

        // Modificação de estado
        switch(order->get_status()){
            
            // De espera para falha
            case WAITING:
                order->set_status(FAILED);
                break;
            
            // De preparação para servindo
            case PREPARING:
                order->set_status(SERVING);
                break;
            
            // De servindo para finalizado
            case SERVING:
                order->set_status(FULLFILLED);
                break;
            
            // Se falhou, avisar o controlador
            case FAILED:
                // LevelController::finished = true;
                break;
            
            // Se finalizado
            default:
                break;
        }
    }
}


// Operador para controle da thread.
void LevelController::thread_controller(){

    // Iterador dos pedidos
    set<OrderController *>::iterator order_itr;

    // Usado para computar tempo decorrido
    chrono::steady_clock::time_point start_time;

    // Executa enquanto não finalizar o nível
    while(LevelController::finished == false){

        // Início do contador
        start_time = chrono::steady_clock::now();

        // Limpeza do console
        clear_console();

        // Percorre todos os pedidos atuais e os processa
        for(order_itr = LevelController::current_orders.begin(); order_itr != LevelController::current_orders.end();){

            // Processamento
            LevelController::process_order((*order_itr)->get_order());

            // Possível remoção
            if((*order_itr)->is_removed() == true)
                LevelController::current_orders.erase(order_itr++);
            else
                ++order_itr;
        }

        // Contagem do tempo decorrido
        auto elapsed_time = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start_time).count();

        // Faz com que a thread durma por um segundo
        std::this_thread::sleep_for(chrono::milliseconds(1000 - elapsed_time));
    }
    
    // Destruição dos semáforos
    // sem_destroy(&(LevelController::kitchen));
    // sem_destroy(&(LevelController::tables));
}


////////////////////////// MÉTODOS PÚBLICOS ///////////////////////////////////

// Construtor.
LevelController::LevelController(unsigned int tables){
    LevelController::finished = false;
    LevelController::self_thread = thread(&LevelController::thread_controller, this);
    sem_init(&(LevelController::kitchen), 0, 1);
    sem_init(&(LevelController::tables), 0, tables);
}


// Retorna se o nível fora ou não finalizado.
bool LevelController::has_finished(){ 
    return LevelController::finished;
}


// Inserção de um novo pedido; inicia uma thread para ele.
void LevelController::insert_order(Order *order){
    OrderController *order_controller = new OrderController(order, &(LevelController::kitchen), &(LevelController::tables));
    LevelController::current_orders.insert(order_controller);
}


// Inicializa a thread do controlador.
void LevelController::start_thread(){
    set<OrderController *>::iterator itr;
    for(itr = LevelController::current_orders.begin(); itr != LevelController::current_orders.end(); ++itr)
        (*itr)->start_thread();
    LevelController::self_thread.join();
}