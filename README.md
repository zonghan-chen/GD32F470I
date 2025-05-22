# GD32F470I

## 01_GPIO_Running_LED

1. Light up LED 1 and turn off LED 3 (hold for 1 second).
2. Light up LED 2 and turn off LED 1 (hold for 1 second).
3. Light up LED 3 and turn off LED 2 (hold for 1 second).

(Loop execution)



## 02_GPIO_Key_Polling_Mode

1. Press the Tamper Key to switch the LED 2 on/off state.



## 03_EXTI_Key_Interrupt_Mode

1. LED 2 flashes once for test.
2. Press the Tamper Key to switch the LED 2 on/off state.



## 04_USART_Printf

1. The data receiving area of the serial port debugging tool displays "USART printf example: please press the Tamper key".
1. After pressing the Tamper Key, the data receiving area of the serial port debugging tool displays "USART printf example" (repeatable operation).



## 05_USART_Echo_Interrupt_Mode

1. LED 1, LED 2 and LED 3 flash three times for test.
2. The data receiving area of the serial port debugging tool displays the data in the tx_buffer array.
3. Send the data in data.txt to the rx_buffer array through the data sending area of the serial port debugging tool.
4. If the data in tx_buffer array and rx_buffer array are the same, all the LEDs will light up successively and then turn off simultaneously (loop execution).
5. Else if the data in tx_buffer array and rx_buffer array are different, all the LEDs will flash three times (loop execution).



## 06_USART_DMA

1. LED 1, LED 2 and LED 3 flash three times for test.
2. The data receiving area of the serial port debugging tool displays the data in the tx_buffer array.
3. Send the data in data.txt to the rx_buffer array through the data sending area of the serial port debugging tool.
4. If the data in tx_buffer array and rx_buffer array are the same, all the LEDs will light up successively and then turn off simultaneously (loop execution).
5. Else if the data in tx_buffer array and rx_buffer array are different, all the LEDs will flash three times (loop execution).



## 07_ADC_Temperature_Vrefint

1. The data receiving area of the serial port debugging tool displays the temperature, internal reference voltage and external battery voltage values every two seconds.

(Loop execution)



**Formula:**

- Temperature:
  $$
  Temperature(^\circ\text{C})=\frac{V_{25^\circ\text{C}}-V_{sensor}}{AvgSlope}+25
  $$

  |       Parameter        |                         Explanation                          |
  | :--------------------: | :----------------------------------------------------------: |
  | $V_{25^\circ\text{C}}$ | Voltage value corresponding to the temperature sensor at $25^\circ\text{C}$ |
  |      $V_{sensor}$      |    Voltage value corresponding to the temperature sensor     |
  |       $AvgSlope$       |     Average slope of the $Temperature-V_{sensor}$ curve      |

  

- Internal reference voltage:
  $$
  V=\frac{ADC_{value}*V_{reference}}{2^{bits}-1}
  $$

  |    Parameter    |      Explanation      |
  | :-------------: | :-------------------: |
  |  $ADC_{value}$  | ADC measurement value |
  | $V_{reference}$ | ADC reference voltage |
  |     $bits$      |    ADC bit number     |

  

- External battery voltage:
  $$
  V=\frac{ADC_{value}*V_{reference}}{2^{bits}-1}*ClkDiv
  $$

  |    Parameter    |       Explanation        |
  | :-------------: | :----------------------: |
  |  $ADC_{value}$  |  ADC measurement value   |
  | $V_{reference}$ |  ADC reference voltage   |
  |     $bits$      |      ADC bit number      |
  |    $ClkDiv$     | Clock frequency division |




## 24_TLI_IPA

1. The LCD displays a running leopard with the logo of GigaDevice as the background.



## old_01_Starting_LED_Master

1. LED 1 lights up for one second and turns off for one second.
2. LED 2 lights up for one second and turns off for one second.
3. LED 3 lights up for one second and turns off for one second.

(Loop execution)



## old_02_Keyboard_Polling_Mode

1. Press the Tamper Key to switch the LED 1 on/off state.



## old_03_Key_External_Interrupt_Mode

1. Light up LED 1.
1. Press the Tamper Key to switch the LED 2 on/off state.

