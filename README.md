# OLED SH1106 SPI Driver for STM32F103

## Overview

This repository hosts an OLED SH1106 SPI driver designed for STM32 microcontrollers, specifically targeting the STM32F103 series. The driver is implemented using the STM32 Low-Level (LL) library and is intended for use within the MDK IDE.

## Features

- **Hardware Compatibility:** Developed and tested for STM32F103 microcontrollers.
- **SPI Communication:** Utilizes SPI for communication with the SH1106 OLED display.
- **Low-Level (LL) Library:** Leverages the STM32 Low-Level library for optimized performance.

## Getting Started

### Prerequisites

- STM32F103 microcontroller
- MDK IDE

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/your-username/your-repository.git
    ```

2. Include the necessary files in your MDK project.

3. Configure the SPI settings in the driver according to your hardware setup.

4. Build and flash your STM32F103 microcontroller.

### Usage

Include the driver files in your STM32 project and initialize the OLED display in your code. Refer to the provided examples for guidance.

```c
// Sample code snippet
#include "oled_sh1106.h"

int main() {
    // Initialize OLED display
    OLED_SH1106_Init();

    // Your application code here

    return 0;
}
```

