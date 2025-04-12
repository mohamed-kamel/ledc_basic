# ESP32 LEDC Example (Source Code Description)

This project demonstrates the basic usage of the LED Control (LEDC) functionality on the ESP32 family, based on the provided C source code.

## Overview

The C code initializes and configures the LEDC module on an ESP32 to generate a Pulse Width Modulation (PWM) signal. It sets up a specific timer, mode, output GPIO, channel, and frequency for the PWM output. The code then calculates the appropriate duty cycle value for 50% and applies it to the configured LEDC channel.

## Code Functionality

The `app_main` function in the provided source code performs the following steps:

1.  **Includes Headers:** Includes necessary header files for standard input/output (`stdio.h`), math functions (`math.h`), ESP-IDF error handling (`esp_err.h`), logging (`esp_log.h`), LEDC driver (`driver/ledc.h`), LEDC types (`hal/ledc_types.h`), clock tree definitions (`soc/clk_tree_defs.h`), and ESP clock tree functions (`esp_clk_tree.h`).

2.  **Defines Constants:** Defines several constants for LEDC configuration:
    * `LEDC_TIMER`: Set to `LEDC_TIMER_0`.
    * `LEDC_MODE`: Set to `LEDC_LOW_SPEED_MODE`.
    * `LEDC_OUTPUT_IO`: Set to `0`, defining GPIO0 as the output pin.
    * `LEDC_CHANNEL`: Set to `LEDC_CHANNEL_0`.
    * `LEDC_FREQUENCY`: Set to `8000000` (8 MHz)

3.  **Selects Clock Source:** Selects the XTAL clock (`SOC_MOD_CLK_XTAL`) as the clock source for the LEDC module.

4.  **Gets Clock Frequency:** Retrieves the frequency of the selected XTAL clock using `esp_clk_tree_src_get_freq_hz`.

5.  **Calculates Duty Resolution:** Determines the appropriate duty resolution based on the selected clock frequency and the desired LEDC frequency using `ledc_find_suitable_duty_resolution`.

6.  **Calculates Duty Value for 50%:** Sets a `duty_cycle` of 0.5 (50%) and calculates the corresponding binary duty value based on the determined duty resolution.

7.  **Configures LEDC Timer:** Initializes a `ledc_timer_config_t` structure with the defined speed mode, duty resolution, timer number, frequency, and selected clock source. This configuration is then applied using `ledc_timer_config`.

8.  **Configures LEDC Channel:** Initializes a `ledc_channel_config_t` structure with the defined speed mode, channel number, timer selection, interrupt disable setting, output GPIO, initial duty set to 0, and hpoint set to 0. This configuration is applied using `ledc_channel_config`.

9.  **Sets Duty Cycle to 50%:** Sets the duty cycle of the configured LEDC channel to the calculated `duty_bin_value` (representing 50%) using `ledc_set_duty`.

10. **Updates Duty Cycle:** Applies the new duty cycle value to the LEDC channel using `ledc_update_duty`.

In summary, this code configures an LEDC channel on GPIO0 to output a PWM signal with a frequency of 8 MHz (as defined by `LEDC_FREQUENCY`) and a duty cycle of 50%. The LEDC module uses the ESP32's XTAL clock as its source.