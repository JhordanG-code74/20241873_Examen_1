# Pregunta 3(a) – Comparación de microcontroladores


| Característica    | SAMD21                    | ESP32                 | nRF52840                  |
|----------------   |--------                   |-------                |-----------                |
| **Tipo de Core**  | ARM Cortex-M0+ (48 MHz)   | Xtensa LX6 dual-core  | ARM Cortex-M4F (64 MHz)   |
| **Memoria RAM**   | 32 KB                     | 520 KB                | 256 KB                    |
| **Memoria FLASH** | 256 KB                    | 4 MB (externa)        | 1 MB                      |
| **Memoria ROM**   | No tiene ROM programable  | 448 KB                | 256 KB                    |
| **Puertos GPIO**  | 38                        | 34                    | 48                        |
| **Canales ADC**   | 20 canales ADC 12-bit     | 18 canales ADC        | 8 canales ADC             |
| **UART**          | 6 UART SERCOM             | 3 UART                | 2 UART                    |




# Pregunta 3(b) – Punteros a los registros del PUERTO0 (nRF52840)

```c
// Dirección base del PORT0 según la hoja de datos
#define PORT0_BASE 0x50000000UL

// Punteros a los registros del PUERTO0 según la tabla del examen
volatile uint32_t *PORT0_OUT     = (uint32_t *)(PORT0_BASE + 0x504); // Write GPIO port
volatile uint32_t *PORT0_OUTSET  = (uint32_t *)(PORT0_BASE + 0x508); // Set bits in GPIO port
volatile uint32_t *PORT0_OUTCLR  = (uint32_t *)(PORT0_BASE + 0x50C); // Clear bits in GPIO port
volatile uint32_t *PORT0_IN      = (uint32_t *)(PORT0_BASE + 0x510); // Read GPIO port
volatile uint32_t *PORT0_DIR     = (uint32_t *)(PORT0_BASE + 0x514); // Direction of GPIO pins
volatile uint32_t *PORT0_DIRSET  = (uint32_t *)(PORT0_BASE + 0x518); // DIR set register
volatile uint32_t *PORT0_DIRCLR  = (uint32_t *)(PORT0_BASE + 0x51C); // DIR clear register
```