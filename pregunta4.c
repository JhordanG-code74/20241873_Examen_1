#include <stdio.h>
#include <stdint.h>


void delay_ms(int ms) {
    for (volatile int i = 0; i < ms * 30000; i++) {
        // bucle vacío
    }
}


// DIRECCIONES DE LOS REGISTROS ADC (ESP32)

#define SENS_SAR_ATTEN1_REG_ADDR        0x3FF48834
#define SENS_SAR_READ_CTRL_REG_ADDR     0x3FF4888C
#define SENS_SAR_START_FORCE_REG_ADDR   0x3FF4882C
#define SENS_SAR_MEAS_START1_REG_ADDR   0x3FF48854

volatile uint32_t *SENS_SAR_ATTEN1_REG      = (uint32_t *)SENS_SAR_ATTEN1_REG_ADDR;
volatile uint32_t *SENS_SAR_READ_CTRL_REG   = (uint32_t *)SENS_SAR_READ_CTRL_REG_ADDR;
volatile uint32_t *SENS_SAR_START_FORCE_REG = (uint32_t *)SENS_SAR_START_FORCE_REG_ADDR;
volatile uint32_t *SENS_SAR_MEAS_START1_REG = (uint32_t *)SENS_SAR_MEAS_START1_REG_ADDR;


// GPIO

#define LED_R 27
#define LED_G 26
#define LED_B 25
#define BTN_INC 5
#define BTN_DEC 4

void set_led(int r, int g, int b) {
    // funciones simples
    gpio_set_level(LED_R, r);
    gpio_set_level(LED_G, g);
    gpio_set_level(LED_B, b);
}


void configurar_adc() {
    *SENS_SAR_ATTEN1_REG |= (1 << 12) | (1 << 13);
    *SENS_SAR_READ_CTRL_REG |= (1 << 27) | (1 << 16) | (1 << 17);
    *SENS_SAR_START_FORCE_REG |= (1 << 0) | (1 << 1);
}


uint16_t leer_adc_ch6() {
    *SENS_SAR_MEAS_START1_REG |= (1 << 31) | (1 << 18) | (1 << 17);
    *SENS_SAR_MEAS_START1_REG |= (1 << 25);  // habilitar canal 6

    while (((*SENS_SAR_MEAS_START1_REG >> 16) & 1) == 0) {
        // esperar mrp = 1
    }

    return (uint16_t)(*SENS_SAR_MEAS_START1_REG & 0xFFFF);
}

// PROGRAMA PRINCIPAL
void app_main() {

    int tiempo = 2;    // valor inicial
    configurar_adc();

    while (1) {

        // AJUSTAR TIEMPO
        if (gpio_get_level(BTN_INC) == 0 && tiempo < 20) tiempo += 2;
        if (gpio_get_level(BTN_DEC) == 0 && tiempo > 2)  tiempo -= 2;

        delay_ms(200);

        // LED SEGÚN RANGO
        if (tiempo <= 10)      set_led(1,0,0); // rojo
        else if (tiempo <=16)  set_led(0,0,1); // azul
        else                   set_led(0,1,0); // verde

        int suma = 0;

        // TOMAR 10 MUESTRAS
        for (int i = 0; i < 10; i++) {
            int val = leer_adc_ch6();
            suma += val;
            delay_ms(50);
        }

        int promedio = suma / 10;

        // APAGAR LED
        set_led(0,0,0);

        // MOSTRAR RESULTADOS
        printf("Promedio ADC: %d\n", promedio);
        printf("Tiempo de muestreo: %d s\n\n", tiempo);

        // ESPERAR EL TIEMPO CONFIGURADO
        delay_ms(tiempo * 1000);
    }
}
