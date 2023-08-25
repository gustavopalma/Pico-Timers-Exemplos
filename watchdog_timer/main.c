#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/watchdog.h"

int main() {
    //inicia as funções de I/O padrão, no caso via Serial-USB
    stdio_init_all();

    sleep_ms(1000);

    //verifica se i WatchDog foi a causa do Reboot
    if (watchdog_caused_reboot()) {
        printf("Rebootado pelo Watchdog!\n");
    } else {
        printf("Boot Limpo\n");
    }

    // Enable the watchdog, requiring the watchdog to be updated every 100ms or the chip will reboot
    // second arg is pause on debug which means the watchdog will pause when stepping through code
    watchdog_enable(1000, 1);

    for (uint i = 0; i < 10; i++) {
        printf("Limpando o Watchdog %d\n", i);
        sleep_ms(500);
        watchdog_update();
    }

    // Wait in an infinite loop and don't update the watchdog so it reboots us
    printf("Esperando o Reboot pelo whatchdog\n");
    while(1);
}