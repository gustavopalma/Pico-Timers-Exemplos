#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"

//flag que controla se o timer foi disparado ou não
volatile bool timer_disparado = false;
bool led_status = false;

// cria uma constante com o pino padrão do led
const uint LED_PIN = PICO_DEFAULT_LED_PIN;


// função de callback chamada na interrupção do timer
bool per_timer_callback(struct repeating_timer *t) {
    printf("Repetição do timer em %lld\n", time_us_64());
    led_status = !led_status;
    gpio_put(LED_PIN, led_status);
    return true;
}


int main() {
    //inicia as funções de I/O padrão, no caso via Serial-USB
    stdio_init_all();
   /*
    * Inicia o Pino de GPIO e o configura como saída
    */
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    struct repeating_timer timer;
    while(true) {

        printf("Hello Timer!\n");
        gpio_put(LED_PIN, false);
        int tempo = 0;
        do {
            printf("Insira o Tempo para o timer em Milissegundos, para cancelar digite -1: ");
        } while (scanf("%d",&tempo) < 0 && tempo == 0);

        if ( tempo == -1) {
            //desabilita o timer na repetição
            cancel_repeating_timer(&timer);
            continue;
        }
        //adicionando o timer com repetição periódica
        add_repeating_timer_ms(tempo, per_timer_callback, NULL, &timer);
    }
    
    return 0;
}