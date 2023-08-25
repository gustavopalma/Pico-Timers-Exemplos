#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

//flag que controla se o timer foi disparado ou não
volatile bool timer_disparado = false;

// função de callback chamada na interrupção do timer
int64_t timer_callback(alarm_id_t id, void *user_data) {
    printf("Timer %d disparado!\n", (int) id);
    timer_disparado = true;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    return 0;
}

int main() {
    //inicia as funções de I/O padrão, no caso via Serial-USB
    stdio_init_all();
    cyw43_arch_init();

    while(true) {

        printf("Hello Timer!\n");
        
        int tempo = 0;
        do {
            printf("Insira o Tempo para o timer em Milissegundos: ");
        } while (scanf("%d",&tempo) < 0 && tempo == 0);

        timer_disparado = false;
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);

        /*
        * função do SDK para a criação de um timer em Milissegundos
        */
        int timer_id = add_alarm_in_ms(tempo, timer_callback, NULL, false);

        printf("Timer programado para %d segundos, com o id: %d\n",tempo, timer_id);

         // aguarda o timer ser disparado
        while (!timer_disparado) {
            /*função de NoP, de acordo com o Datasheet, é recomandável utiliza-la 
              quando temos loops vazios
            */
            tight_loop_contents();
        }
    }
    
    return 0;
}