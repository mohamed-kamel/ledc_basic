
#include <stdio.h>
#include <math.h>

#include "esp_err.h"
#include "esp_log.h"

#include "driver/ledc.h"    // for all LEDC functions
#include "hal/ledc_types.h" // For LEDC Config Enums

#include "soc/clk_tree_defs.h" // Clock Sources, and available clock for each Module
#include "esp_clk_tree.h"      // for esp_clk_tree_src_get_freq_hz() and clock precision enum

#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO (0) // Define the output GPIO
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_FREQUENCY (8000000)

void app_main(void)
{
    // #define SOC_LEDC_CLKS {SOC_MOD_CLK_XTAL, SOC_MOD_CLK_APB, SOC_MOD_CLK_RC_FAST} // LEDC supported Clocks

    soc_module_clk_t selected_clock = SOC_MOD_CLK_XTAL;

    uint32_t freq = 0;
    ESP_ERROR_CHECK(esp_clk_tree_src_get_freq_hz(selected_clock, ESP_CLK_TREE_SRC_FREQ_PRECISION_APPROX, &freq));
    ESP_LOGI("Main", "Chosen Clock Freq %ld", freq);

    uint32_t duty_res = ledc_find_suitable_duty_resolution(freq, LEDC_FREQUENCY);
    ESP_LOGI("Main", "max resolution %ld", duty_res);

    double duty_cycle = 0.5; // 50%
    int duty_bin_value = (int)(pow(2, duty_res) * duty_cycle);

    ESP_LOGI("Main", "duty value for 50 percent %d", duty_bin_value);

    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .duty_resolution = duty_res,
        .timer_num = LEDC_TIMER,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = selected_clock}; // LEDC_AUTO_CLK for auto selection of the best suitable clock
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .timer_sel = LEDC_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LEDC_OUTPUT_IO,
        .duty = 0, // Set duty to 0%
        .hpoint = 0};
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    // Set duty to 50%
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty_bin_value));
    // Update duty to apply the new value
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
}
