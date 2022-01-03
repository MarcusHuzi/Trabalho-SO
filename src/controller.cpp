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


///////////////////////////////////////////////////////////////////////////////

// Construtor.
LevelController::LevelController(int max_meals){
    LevelController::finished = false;
    LevelController::self_thread = thread(&LevelController::thread_controller, this);
    LevelController::menu = new Menu(max_meals);
}


// Processa um pedido; retorna verdadeiro se o pedido deve ser removido.
bool LevelController::process_order(Order *order){

    // Decremento de relógio
    order->decrement_clock();

    // Imprime o pedido
    cout << order->to_string() << endl;

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
                LevelController::finished = true;
                return true;
            
            // Se finalizado
            default:
                return true;
        }
    }
    return false;
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
        for(order_itr = LevelController::current_orders.begin(); order_itr != LevelController::current_orders.end(); ){
            
            // Processo o pedido e verifica se deve ser removido
            if( LevelController::process_order(*order_itr) == true ){
                LevelController::current_orders.erase(order_itr++);
            }else{
                ++order_itr;
            }
        }

        // Contagem do tempo decorrido
        auto elapsed_time = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start_time).count();

        // Faz com que a thread durma por um segundo
        std::this_thread::sleep_for(chrono::milliseconds(1000 - elapsed_time));
    }
}


/*
// Realiza operações relativas a um avanço no nível.
void LevelController::step(){

    return;
    // Iteração ao longo dos pedidos
    set<Order *>::iterator itr;
    for(itr = LevelController::current_orders.begin(); itr != LevelController::current_orders.end(); ){

        // Verificação de relógio
        if((*itr)->get_clock() <= 0){
            
            // Modificação de estado
            switch((*itr)->get_status()){
                
                // De espera para falha
                case WAITING:
                    cout << "finished";
                    LevelController::finished = true;
                    (*itr)->set_status(FAILED);
                    ++itr;
                    break;
                
                // De preparação para servindo
                case PREPARING:
                    (*itr)->set_status(SERVING);
                    ++itr;
                    break;
                
                // De servindo para finalizado
                case SERVING:
                    (*itr)->set_status(FULLFILLED);
                    ++itr;
                    break;
                
                // Se finalizado, é removido
                case FULLFILLED:
                    LevelController::current_orders.erase(itr++);
                    break;
                
                // Nada acontece
                default:
                    ++itr;
                    break;
            }
        }else{
            ++itr;
        }
    }
}
*/


// Retorna se o nível fora ou não finalizado.
bool LevelController::has_finished(){ 
    return LevelController::finished;
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