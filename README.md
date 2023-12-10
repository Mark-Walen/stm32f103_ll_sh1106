# OLED SH1106 SPI Driver for STM32F103

## Overview

This repository hosts an OLED SH1106 SPI driver designed for STM32 microcontrollers, specifically targeting the STM32F103 series. The driver is implemented using the STM32 Low-Level (LL) library and supports SPI communication. Additionally, for enhanced performance and faster frame refresh rates, the driver includes an optional SPI with DMA feature, which can be enabled or disabled using the `DMA_ENABLE` macro.

## Background

This project was inspired by the work of [BaudDance](https://github.com/BaudDance), particularly the [LEDDrive](https://github.com/BaudDance/LEDDrive/tree/main/library/stm32_hal_ch1116) project. The LEDDrive project utilizes the STM32 HAL library and I2C to implement the SH1106. Our implementation builds upon this inspiration, adapting it for SPI communication with the STM32F103 microcontroller and incorporating the STM32 Low-Level (LL) library for optimized performance.

## Features

- **Hardware Compatibility:** Developed and tested for STM32F103 microcontrollers.
- **SPI Communication:** Utilizes SPI for communication with the SH1106 OLED display.
- **DMA Support:** Optionally enables SPI with DMA for faster frame refresh rates (Enabled by defining `DMA_ENABLE` macro).

## Getting Started

### Prerequisites

- STM32F103 microcontroller
- MDK IDE

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/Mark-Walen/stm32f103_ll_sh1106/tree/master
    ```

2. Include the necessary files in your MDK project.

3. Configure the SPI and DMA settings in the driver according to your hardware setup.

4. Build and flash your STM32F103 microcontroller.

### Usage

Include the driver files in your STM32 project and initialize the OLED display in your code. Optionally, define the `DMA_ENABLE` macro to enable SPI with DMA.

```c
// Sample code snippet with DMA support
#include "oled_sh1106.h"

int main() {
    // Optionally enable SPI with DMA
    #define DMA_ENABLE
    // Initialize OLED display
    OLED_SH1106_Init();

    // Your application code here

    return 0;
}
```
## Contributing
If you'd like to contribute to this project, please follow the contribution guidelines.

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments
Thanks to BaudDance for the inspiration from the LEDDrive project.
Thanks to STM32 Community for support and inspiration.

## Contact
For questions or feedback, please contact [Mark Walen] at [walen.mark2509758@gmail.com].
