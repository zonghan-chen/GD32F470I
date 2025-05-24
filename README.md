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
2. After pressing the Tamper Key, the data receiving area of the serial port debugging tool displays "USART printf example" (repeatable operation).



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

- **Temperature:**
  
  $Temperature(^\circ\text{C})=\frac{V_{25^\circ\text{C}}-V_{SENSE}}{AvgSlope}+25$
  
  |       Parameter        |                         Explanation                          |
  | :--------------------: | :----------------------------------------------------------: |
  | $V_{25^\circ\text{C}}$ | Internal temperature sensor output voltage at $25^\circ\text{C}$ |
  |      $V_{SENSE}$       | Internal temperature sensor output voltage at the current temperature |
  |       $AvgSlope$       |      Average slope of the $Temperature-V_{SENSE}$ curve      |
  
  
  
- **Internal reference voltage ($V_{REFINT}$) / Temperature sensor voltage ($V_{SENSE}$) :**
  
  $V_{REFINT}=\frac{ADC_{value}*V_{reference}}{2^{bits}-1}$
  
  $V_{SENSE}=\frac{ADC_{value}*V_{reference}}{2^{bits}-1}$
  
  |    Parameter    |      Explanation      |
  | :-------------: | :-------------------: |
  |  $ADC_{value}$  | ADC measurement value |
  | $V_{reference}$ | ADC reference voltage |
  |     $bits$      |    ADC bit number     |
  
  
  
- **External battery voltage ($V_{BAT}$) :**
  
  $V_{BAT}=\frac{ADC_{value}*V_{reference}}{2^{bits}-1}*4$
  
  |    Parameter    |      Explanation      |
  | :-------------: | :-------------------: |
  |  $ADC_{value}$  | ADC measurement value |
  | $V_{reference}$ | ADC reference voltage |
  |     $bits$      |    ADC bit number     |
  
  - There is a bridge divider by 4 integrated on the $V_{BAT}$ pin, it connects $V_{BAT}/4$ to the ADC_IN18 input channel. Therefore, the converted digital value of ADC_IN18 input channel is $V_{BAT}/4$.



## 08_ADC0_ADC1_Follow_Up_Mode

1. The data receiving area of the serial port debugging tool displays the regular value of ADC0 and ADC1 by adc_value[0] and adc_value[1].

(Loop execution)



**The working principle of the TIMER Prescaler and Auto-Reload Register:**

- **Prescaler:**
  - **Hardware design logic:** A prescaler is a counter that starts counting from zero to the set prescaler value, then returns to zero and generates a pulse.
  - **Configuration method:** If the frequency division coefficient is required to be $N$, the value of `timer_parameter_struct.prescaler` should be set to $N-1$.
- **Auto-Reload Register (APR) :**
  - **Role:**
    - Determine the overflow period of the timer.
    - The timer starts counting from zero and increments by one for each received clock pulse. When the count reaches the value of ARR, the timer overflows and triggers an interrupt or updates an event, then starts counting from zero again.
  - **Configuration method:** If the timer overflow period is required to be $N$, the value of `timer_parameter_struct.period` should be set to $N-1$.



**PWM output mode:**

|                                      |          PWM MODE 0          |          PWM MODE 1          |
| :----------------------------------: | :--------------------------: | :--------------------------: |
| Condition of output the set polarity | $Value_{CNT}<Value_{preset}$ | $Value_{CNT}>Value_{preset}$ |




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
2. Press the Tamper Key to switch the LED 2 on/off state.

