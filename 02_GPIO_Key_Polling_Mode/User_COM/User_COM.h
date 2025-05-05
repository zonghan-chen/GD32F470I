#ifndef USER_COM_H
#define USER_COM_H

#include "gd32f4xx.h"

typedef enum
{
	COM0 = 0
} com_typedef_enum;

void com_init(com_typedef_enum com_num);

#endif
