#ifndef _ORDER_SEMAPHORE_H_
#define _ORDER_SEMAPHORE_H_

#include <semaphore.h>

//////////////////////////////// CONSTANTES ///////////////////////////////////

#define SEMAPHORE_DISABLE_PREFERENCE -1
#define SEMAPHORE_DISABLE_SELECTION -2

///////////////////////////////////////////////////////////////////////////////

/// Classe de semáforo para pedidos em um restaurante.
class OrderSemaphore{
private:

    // Sinais de controle.
    unsigned int max_signal;
    unsigned int current_signal;
    int preferential_order_id;

    // Semáforo auxiliar para sincronização.
    sem_t signal_semaphore;

public:

    /**
     * @brief Construtor padrão; cria um semáforo binário.
     * @param preferential_order_id número de identificação do pedido 
     * a ser priorizado pelo semáforo. Admite valores especiais dados 
     * pelas constantes definidas neste cabeçalho.
     */
    OrderSemaphore(int preferential_order_id);

    /**
     * @brief semáforo de um pedido em um restaurante. 
     * @param max_signal maior sinal admissível pelo semáforo. Se 
     * igual a um, por exemplo, tratar-se-á de um semáforo binário.
     * @param preferential_order_id número de identificação do pedido 
     * a ser priorizado pelo semáforo. Admite valores especiais dados 
     * pelas constantes definidas neste cabeçalho.
     */
    OrderSemaphore(unsigned int max_signal, int preferential_order_id);

    /** 
     * Espera pela liberação de um sinal do semáforo. 
     * @param order referência ao pedido ao qual se está aguardando.
     * @param current_life referência à vida atual do jogador.
     * @return verdadeiro se a espera terminara de forma convencional, 
     * ou falso, caso a espera tenha sido encerrada devido a um sinal 
     * do pedido.
     * */
    bool wait(Order *order, int *current_life);

    /// Libera um sinal do semáforo.
    void release();

    /**
     * @brief Define um ID de pedido como preferencial. Se igual a -1, como 
     * por padrão, priorizará o primeiro pedido a realizar uma solicitação e, 
     * em caso contrário, priorizará o pedido cujo ID equivale ao apontado.
     * @param id Número de identificação a ser priorizado.
     */
    void set_preferential_order_id(int id);

    /**
     * @brief Retorna se o semáforo está ou não livre.
     */
    bool is_free();
};

///////////////////////////////////////////////////////////////////////////////

#endif