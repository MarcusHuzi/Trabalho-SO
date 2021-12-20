#ifndef _ORDER_SEMAPHORE_H_
#define _ORDER_SEMAPHORE_H_

///////////////////////////////////////////////////////////////////////////////

/// Classe de semáforo para pedidos em um restaurante.
class OrderSemaphore{
private:

    // Sinais de controle.
    unsigned int max_signal;
    unsigned int current_signal;

public:

    /// Construtor padrão; cria um semáforo binário.
    OrderSemaphore();

    /**
     * Construtor do semáforo de um pedido em um restaurante. 
     * @param max_signal maior sinal admissível pelo semáforo. Se 
     * igual a um, por exemplo, tratar-se-á de um semáforo binário.
     */
    OrderSemaphore(unsigned int max_signal);

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
};

///////////////////////////////////////////////////////////////////////////////

#endif