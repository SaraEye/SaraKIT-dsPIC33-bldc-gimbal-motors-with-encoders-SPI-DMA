#ifndef LSM6DS3TR_C_H
#define LSM6DS3TR_C_H

#ifdef __cplusplus
extern "C" {
#endif
/* Private variables ---------------------------------------------------------*/

#include <string.h>
#include <stdio.h>
#include <stdint.h> 

void lsm6ds3tr_i2c_init();
void lsm6ds3tr_i2c_check();

#ifdef __cplusplus
}
#endif

#endif /* LSM6DS3TR_C_H */

