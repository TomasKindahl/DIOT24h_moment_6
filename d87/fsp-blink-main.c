#include "hal_data.h"
void R_BSP_WarmStart(bsp_warm_start_event_t event);

/* Change LED as needed here */
#define LED    BSP_IO_PORT_03_PIN_04 // D8 på Arduino Uno R4 WiFi

void hal_entry(void)
{
    R_BSP_PinAccessEnable();
    R_IOPORT_PinCfg(&g_ioport_ctrl, LED, IOPORT_CFG_PORT_DIRECTION_OUTPUT);
    while(true) 
    {
        R_IOPORT_PinWrite(&g_ioport_ctrl, LED, BSP_IO_LEVEL_HIGH);
        R_BSP_SoftwareDelay(200, BSP_DELAY_UNITS_MILLISECONDS);
        R_IOPORT_PinWrite(&g_ioport_ctrl, LED, BSP_IO_LEVEL_LOW);
        R_BSP_SoftwareDelay(200, BSP_DELAY_UNITS_MILLISECONDS);
    }
}

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart(bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
#if BSP_FEATURE_FLASH_LP_VERSION != 0
        /* Enable reading from data flash. */
        R_FACI_LP->DFLCTL = 1U;
        /* Would normally have to wait tDSTOP(6us) for data flash recovery. Placing the enable here, before clock and
         * C runtime initialization, should negate the need for a delay since the initialization will typically take more than 6us. */
#endif
    }
    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */
        /* E.g., you can configure pins here. */
    }
}
