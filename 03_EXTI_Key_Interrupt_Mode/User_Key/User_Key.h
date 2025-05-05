#ifndef USER_KEY_H
#define USER_KEY_H

#include "gd32f4xx.h"

typedef enum
{
	KEY_WAKEUP = 0,
	KEY_TAMPER = 1,
	KEY_USER = 2
} key_typedef_enum;

typedef enum
{
	KEY_MODE_GPIO = 0,
	KEY_MODE_EXTI = 1
} keymode_typedef_enum;

void key_init(key_typedef_enum key_num, keymode_typedef_enum key_mode);
uint8_t key_state_get(key_typedef_enum key_num);

#endif
