#ifndef _ORDER_SEMAPHORE_H_
#define _ORDER_SEMAPHORE_H_

///////////////////////////////////////////////////////////////////////////////

/// Classe de semáforo para pedidos em um restaurante.
class OrderSemaphore{
private:

    // Sinais de controle
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

    /// Espera pela liberação de um sinal do semáforo.
    void wait();

    /// Libera um sinal do semáforo.
    void release();
};

///////////////////////////////////////////////////////////////////////////////

#endif