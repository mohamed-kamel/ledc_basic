idf_component_register(SRCS "ledc_basic_example_main.c"
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES esp_driver_ledc esp_driver_gpio
                    )
