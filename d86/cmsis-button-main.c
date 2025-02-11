#include <cmsis_compiler.h>
#include <bsp_arm_exceptions.h>
#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_UNOR4_MINIMA)
#include <R7FA4M1AB.h>
#elif defined(ARDUINO_PORTENTA_C33)
#include <R7FA6M5BH.h>
#endif

// GPIO 8: P3.04
#define LED_PORT_NUM 3
#define LED_PIN_NUM 4

// GPIO 7: P1.12
#define BUTTON_PORT_NUM 1
#define BUTTON_PIN_NUM 12

int button_mode = 0;

int main() {
    // enable writing to the pin registers
    R_PMISC->PWPR = 0;          // Clear BOWI bit - writing to PFSWE bit enabled
    R_PMISC->PWPR = 1U << 6;    // Set PFSWE bit - writing to PFS register enabled

    // Set GPIO output mode
    R_PFS->PORT[LED_PORT_NUM].PIN[LED_PIN_NUM].PmnPFS_b.PDR = 1;  // "Output"
    R_PFS->PORT[LED_PORT_NUM].PIN[LED_PIN_NUM].PmnPFS_b.DSCR = 1; // "Middle Drive capability"
    R_PFS->PORT[LED_PORT_NUM].PIN[LED_PIN_NUM].PmnPFS_b.PMR = 0;  // "Used as a general I/O pin"

    R_PFS->PORT[BUTTON_PORT_NUM].PIN[BUTTON_PIN_NUM].PmnPFS_b.PDR = 0;  // "Input"
    R_PFS->PORT[BUTTON_PORT_NUM].PIN[BUTTON_PIN_NUM].PmnPFS_b.DSCR = 1; // "Middle Drive capability"
    R_PFS->PORT[BUTTON_PORT_NUM].PIN[BUTTON_PIN_NUM].PmnPFS_b.PMR = 0;  // "Used as a general I/O pin"

    while(1) {
        // read button
        if(R_PFS->PORT[BUTTON_PORT_NUM].PIN[BUTTON_PIN_NUM].PmnPFS_b.PIDR == 0) {
            button_mode = !button_mode;
            while(R_PFS->PORT[BUTTON_PORT_NUM].PIN[BUTTON_PIN_NUM].PmnPFS_b.PIDR == 0) {}
        }
        if(button_mode) {
            // set pin HIGH
            R_PFS->PORT[LED_PORT_NUM].PIN[LED_PIN_NUM].PmnPFS_b.PODR = 1;
            for(volatile int i=0; i < 8*1000*1000/2; i++) {}
        } else {
            // set pin HIGH
            R_PFS->PORT[LED_PORT_NUM].PIN[LED_PIN_NUM].PmnPFS_b.PODR = 1;
            // delay very crudely in a NOP loop, 1s delay at 8MHz reset clock
            for(volatile int i=0; i < 8*1000*1000/2; i++) {}
            // set LOW
            R_PFS->PORT[LED_PORT_NUM].PIN[LED_PIN_NUM].PmnPFS_b.PODR = 0;
            // delay
            for(volatile int i=0; i < 8*1000*1000/2; i++) {}
        }
    }
    return 0;
}

void NMI_Handler (void) { while(1) { }}