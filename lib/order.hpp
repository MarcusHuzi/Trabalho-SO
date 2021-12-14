#ifndef _ORDER_H_
#define _ORDER_H_

///////////////////////////////////////////////////////////////////////////////

// Estado de um pedido em um restaurante.
enum OrderStatus {
    WAITING, 
    PREPARING, 
    SERVED, 
    FULLFILLED
};


// Representa um pedido em um restaurante.
class Order {
private:

    // Número de identificação do pedido.
    int id;
    
    // Relógio do pedido; contabiliza tempos restantes.
    int clock;

    // Estado do pedido.
    OrderStatus status;

public:

    /**  
     * @param id Número de identificação do pedido.
     * @param max_waiting_time Tempo máximo, em segundos, que o pedido pode 
     * ficar em estado de espera, que se trata de seu estado inicial. Desse 
     * modo, o relógio do pedido é inicializado nesse tempo.
    */
    Order(int id, int max_waiting_time);

    /// Retorna o número identificador do pedido.
    int get_id();

    /// Retorna o valor atual do relógio armazenado pelo pedido.
    int get_clock();

    /// Retorna o estado atual do pedido.
    OrderStatus get_status();

    /** 
     * Atualiza o estado do pedido. 
     * @param status Estado ao qual atualizar o pedido.
    */
    void set_status(OrderStatus status);

    /// Decrementa o relógio atual da classe em uma unidade.
    void decrement_clock();
};


/// Função para thread que reduz o relógio do pedido em uma unidade a cada segundo.
void order_clock_reducer_thread(Order *order);

///////////////////////////////////////////////////////////////////////////////

#endif