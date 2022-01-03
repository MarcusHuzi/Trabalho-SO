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
#include "../lib/order_semaphore.hpp"

// Limpeza de console dependente do SO
#ifdef __unix__
    #define clear_console() system("clear")
#elif defined(_WIN32) || defined(WIN32)
    #define clear_console() system("CLS")
#endif


////////////////////////// MÉTODOS PRIVADOS ///////////////////////////////////

// Operador para controle da thread.
void LevelController::thread_controller(){

    // Iterador dos pedidos
    set<OrderController *>::iterator order_itr;

    // Usado para computar tempo decorrido
    chrono::steady_clock::time_point start_time;

    // Usado para restringir a leitura do menu a 1 vez
    bool read = false;

    // Executa enquanto não finalizar o nível
    while(LevelController::finished == false){

        // Início do contador
        start_time = chrono::steady_clock::now();

        // Limpeza do console
        clear_console();
    
        // Imprime cardápio atual
		LevelController::print_menu();

        // Faz com que a thread durma 1 vez, para a leitura do menu da fase atual
        if(!read)
            std::this_thread::sleep_for(chrono::milliseconds(LevelController::lvl_generator->get_difficulty() * 2000));
        read = true;

        // Percorre todos os pedidos atuais e os processa
        for(order_itr = LevelController::current_orders.begin(); order_itr != LevelController::current_orders.end();){

            // Processamento
            if((*order_itr)->is_active() == true){

                // Captura do pedido
                Order *order = (*order_itr)->get_order();
                
                // Decremento de relógio
                if(LevelController::kitchen->is_free() == false)
                    order->decrement_clock();

                // Imprime o pedido
                cout << order->to_string() << endl;

                // Verificação de falha
                if(order->get_status() == FAILED && order->get_clock() <= 0){
                    if(LevelController::current_life > 0)
                        LevelController::current_life -= 1;
                }
            }

            // Possível remoção
            if((*order_itr)->is_removed() == true){
                LevelController::current_orders.erase(order_itr++);
                delete (*order_itr)->get_order()->get_order_meal();
                delete (*order_itr)->get_order();
                delete *order_itr;
            }else{
                ++order_itr;
            }
        }

        // Verificação de finalização
        if(LevelController::current_orders.size() == 0){
            LevelController::finished = true;
        }

        // Verificação de falha
        if(LevelController::current_life <= 0){
            LevelController::finished = true;
            LevelController::failed = true;
        }

        // Verificação de liberação da cozinha
        if(LevelController::kitchen->is_free()){
            cout << endl << "Escolha o ID do pedido a ser priorizado pela cozinha a seguir: ";
            int id;
            cin >> id;
            LevelController::kitchen->set_preferential_order_id(id);
            std::this_thread::sleep_for(chrono::milliseconds(1000));
        }

        // Contagem do tempo decorrido
        auto elapsed_time = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start_time).count();

        // Faz com que a thread durma por um segundo
        std::this_thread::sleep_for(chrono::milliseconds(1000 - elapsed_time));
    }

    // Limpeza do console.
    clear_console();

    // Mensagem final.
    if(LevelController::failed == false){
        cout << "LEVEL ACCOMPLISHED" << endl;
    }else{
        cout << "LEVEL FAILED" << endl;
    }
    LevelController::lvl_generator->erase_menu();
    delete LevelController::lvl_generator;
}


////////////////////////// MÉTODOS PÚBLICOS ///////////////////////////////////

// Construtor.
LevelController::LevelController(unsigned int tables, int max_life, int difficulty){
    LevelController::finished = false;
    LevelController::failed = false;
    LevelController::self_thread = thread(&LevelController::thread_controller, this);
    LevelController::kitchen = new OrderSemaphore(SEMAPHORE_DISABLE_SELECTION);
    LevelController::tables = new OrderSemaphore(tables, SEMAPHORE_DISABLE_PREFERENCE);
    LevelController::current_life = max_life;
    LevelController::lvl_generator = new LevelGenerator(difficulty);
}


// Retorna se o nível fora ou não finalizado.
bool LevelController::has_finished(){ 
    return LevelController::finished;
}


// Retorna se o jogador falhou ou não.
bool LevelController::has_failed(){
    return LevelController::failed;
}


// Inserção de um novo pedido; inicia uma thread para ele.
void LevelController::insert_order(){
    Order *order = LevelController::lvl_generator->new_order();
    OrderController *order_controller = new OrderController(order, LevelController::kitchen, LevelController::tables, &(LevelController::current_life));
    LevelController::current_orders.insert(order_controller);
}


// Inicializa a thread do controlador.
void LevelController::start_thread(){
    set<OrderController *>::iterator itr;
    for(itr = LevelController::current_orders.begin(); itr != LevelController::current_orders.end(); ++itr)
        (*itr)->start_thread();
    LevelController::self_thread.join();
}

// Inicializa as ordens dos clientes
void LevelController::setup_phase(int limit_order){
    int count = 0;
    while(count++ != limit_order)
        LevelController::insert_order();
}

// Imprime Menu do restaurante
void LevelController::print_menu(){
    cout << endl << endl << "----------------------------CARDÁPIO DE HOJE------------------------------------" << endl;
    LevelController::lvl_generator->plates();
}