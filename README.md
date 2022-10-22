# ARM
ARM Cortex-M projects

Simple ARM Cortex-M3/M4 projects and drivers made on TI Tiva-C and STM32F103. For the Tiva-C, I started to include some FreeRTOS examples. These examples are placed in a dedicated directory [FreeRTOS](https://github.com/Mohammed-AhmedAF/ARM/tree/master/tiva-c/examples/FreeRTOS) under Examples.

For [FreeRTOS](https://github.com/Mohammed-AhmedAF/ARM/tree/master/stm32f103/projects/FreeRTOS_SevenSegment) to work on STM32F103 when using KEIL IDE, you should change the value of macro configPRIO_BITS to 4.

The included examples contain driver files only, no IDE-specific files are included. So if you want to use the example code in Keil IDE for instance, you will have to create a new project and add the files of the example to the project. However, it should be stated that the Tiva-C examples were indeed made with Keil IDE.
