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
#include "../lib/controller.hpp"

// Limpeza de console dependente do SO
#ifdef __unix__
    #define clear_console() system("clear")
#elif defined(_WIN32) || defined(WIN32)
    #define clear_console() system("CLS")
#endif


////////////////////////// MÉTODOS PRIVADOS ///////////////////////////////////

// Construtores.
LevelController::LevelController(unsigned int tables){
    LevelController::finished = false;
    LevelController::self_thread = thread(&LevelController::thread_controller, this);
    sem_init(&(LevelController::kitchen), 0, 1);
    sem_init(&(LevelController::tables), 0, tables);
}


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
    set<Order *>::iterator order_itr;

    // Usado para computar tempo decorrido
    chrono::steady_clock::time_point start_time;

    // Executa enquanto não finalizar o nível
    while(LevelController::finished == false){

        // Início do contador
        start_time = chrono::steady_clock::now();

        // Limpeza do console
        clear_console();

        // Percorre todos os pedidos atuais e os processa
        for(order_itr = LevelController::current_orders.begin(); order_itr != LevelController::current_orders.end(); ++order_itr){
            LevelController::process_order(*order_itr);
        }

        // Contagem do tempo decorrido
        auto elapsed_time = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start_time).count();

        // Faz com que a thread durma por um segundo
        std::this_thread::sleep_for(chrono::milliseconds(1000 - elapsed_time));
    }
    
    // Destruição dos semáforos
    sem_destroy(&(LevelController::kitchen));
    sem_destroy(&(LevelController::tables));
}


////////////////////////// MÉTODOS PÚBLICOS ///////////////////////////////////

// Retorna se o nível fora ou não finalizado.
bool LevelController::has_finished(){ 
    return LevelController::finished;
}


/// Retorna ponteiro para o semáforo da cozinha.
sem_t *LevelController::get_kitchen_semaphore(){
    return &(LevelController::kitchen);
}


/// Retorna ponteiro para o semáforo das mesas.
sem_t *LevelController::get_tables_semaphore(){
    return &(LevelController::tables);
}


// Inserção de um novo pedido; inicia uma thread para ele.
void LevelController::insert_order(Order *order){
    LevelController::current_orders.insert(order);
}


// Remove um pedido atual se ele existir.
void LevelController::remove_order(Order *order){
    set<Order *>::iterator itr = LevelController::current_orders.find(order);
    if(itr != LevelController::current_orders.end()){
        LevelController::current_orders.erase(itr);
    }
}


// Inicializa a thread do controlador.
void LevelController::start_thread(){
    LevelController::self_thread.join();
}