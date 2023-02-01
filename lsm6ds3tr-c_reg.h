/**
  ******************************************************************************
  * @file    lsm6ds3tr_c_reg.h
  * @author  Sensors Software Solution Team
  * @brief   This file contains all the functions prototypes for the
  *          lsm6ds3tr_c_reg.c driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LSM6DS3TR_C_DRIVER_H
#define LSM6DS3TR_C_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include <math.h>

/** @addtogroup LSM6DS3TR_C
  * @{
  *
  */

/** @defgroup  Endianness definitions
  * @{
  *
  */

#ifndef DRV_BYTE_ORDER
#ifndef __BYTE_ORDER__

#define DRV_LITTLE_ENDIAN 1234
#define DRV_BIG_ENDIAN    4321

/** if _BYTE_ORDER is not defined, choose the endianness of your architecture
  * by uncommenting the define which fits your platform endianness
  */
//#define DRV_BYTE_ORDER    DRV_BIG_ENDIAN
#define DRV_BYTE_ORDER    DRV_LITTLE_ENDIAN

#else /* defined __BYTE_ORDER__ */

#define DRV_LITTLE_ENDIAN  __ORDER_LITTLE_ENDIAN__
#define DRV_BIG_ENDIAN     __ORDER_BIG_ENDIAN__
#define DRV_BYTE_ORDER     __BYTE_ORDER__

#endif /* __BYTE_ORDER__*/
#endif /* DRV_BYTE_ORDER */

/**
  * @}
  *
  */

/** @defgroup STMicroelectronics sensors common types
  * @{
  *
  */

#ifndef MEMS_SHARED_TYPES
#define MEMS_SHARED_TYPES

typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t bit0       : 1;
  uint8_t bit1       : 1;
  uint8_t bit2       : 1;
  uint8_t bit3       : 1;
  uint8_t bit4       : 1;
  uint8_t bit5       : 1;
  uint8_t bit6       : 1;
  uint8_t bit7       : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t bit7       : 1;
  uint8_t bit6       : 1;
  uint8_t bit5       : 1;
  uint8_t bit4       : 1;
  uint8_t bit3       : 1;
  uint8_t bit2       : 1;
  uint8_t bit1       : 1;
  uint8_t bit0       : 1;
#endif /* DRV_BYTE_ORDER */
} bitwise_t;

#define PROPERTY_DISABLE                (0U)
#define PROPERTY_ENABLE                 (1U)

/** @addtogroup  Interfaces_Functions
  * @brief       This section provide a set of functions used to read and
  *              write a generic register of the device.
  *              MANDATORY: return 0 -> no Error.
  * @{
  *
  */

typedef int32_t (*stmdev_write_ptr)(void *, uint8_t, const uint8_t *, uint16_t);
typedef int32_t (*stmdev_read_ptr)(void *, uint8_t, uint8_t *, uint16_t);
typedef void (*stmdev_mdelay_ptr)(uint32_t millisec);

typedef struct
{
  /** Component mandatory fields **/
  stmdev_write_ptr  write_reg;
  stmdev_read_ptr   read_reg;
  /** Component optional fields **/
  stmdev_mdelay_ptr   mdelay;
  /** Customizable optional pointer **/
  void *handle;
} stmdev_ctx_t;

/**
  * @}
  *
  */

#endif /* MEMS_SHARED_TYPES */

#ifndef MEMS_UCF_SHARED_TYPES
#define MEMS_UCF_SHARED_TYPES

/** @defgroup    Generic address-data structure definition
  * @brief       This structure is useful to load a predefined configuration
  *              of a sensor.
  *              You can create a sensor configuration by your own or using
  *              Unico / Unicleo tools available on STMicroelectronics
  *              web site.
  *
  * @{
  *
  */

typedef struct
{
  uint8_t address;
  uint8_t data;
} ucf_line_t;

/**
  * @}
  *
  */

#endif /* MEMS_UCF_SHARED_TYPES */

/**
  * @}
  *
  */

/** @defgroup LSM6DS3TR_C_Infos
  * @{
  *
  */

/** I2C Device Address 8 bit format  if SA0=0 -> D5 if SA0=1 -> D7 **/
#define LSM6DS3TR_C_I2C_ADD_L     0xD5U
#define LSM6DS3TR_C_I2C_ADD_H     0xD7U

/** Device Identification (Who am I) **/
#define LSM6DS3TR_C_ID            0x6AU

/**
  * @}
  *
  */

#define LSM6DS3TR_C_FUNC_CFG_ACCESS              0x01U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 5;
uint8_t func_cfg_en              :
  3;  /* func_cfg_en + func_cfg_en_b */
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
uint8_t func_cfg_en              :
  3;  /* func_cfg_en + func_cfg_en_b */
  uint8_t not_used_01              : 5;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_func_cfg_access_t;

#define LSM6DS3TR_C_SENSOR_SYNC_TIME_FRAME       0x04U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tph                      : 4;
  uint8_t not_used_01              : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 4;
  uint8_t tph                      : 4;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_sensor_sync_time_frame_t;

#define LSM6DS3TR_C_SENSOR_SYNC_RES_RATIO        0x05U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t rr                       : 2;
  uint8_t not_used_01              : 6;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 6;
  uint8_t rr                       : 2;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_sensor_sync_res_ratio_t;

#define LSM6DS3TR_C_FIFO_CTRL1                   0x06U
typedef struct
{
  uint8_t fth                      : 8;  /* + FIFO_CTRL2(fth) */
} lsm6ds3tr_c_fifo_ctrl1_t;

#define LSM6DS3TR_C_FIFO_CTRL2                   0x07U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t fth                      : 3;  /* + FIFO_CTRL1(fth) */
  uint8_t fifo_temp_en             : 1;
  uint8_t not_used_01              : 2;
  uint8_t timer_pedo_fifo_drdy     : 1;
  uint8_t timer_pedo_fifo_en       : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t timer_pedo_fifo_en       : 1;
  uint8_t timer_pedo_fifo_drdy     : 1;
  uint8_t not_used_01              : 2;
  uint8_t fifo_temp_en             : 1;
  uint8_t fth                      : 3;  /* + FIFO_CTRL1(fth) */
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_fifo_ctrl2_t;

#define LSM6DS3TR_C_FIFO_CTRL3                   0x08U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t dec_fifo_xl              : 3;
  uint8_t dec_fifo_gyro            : 3;
  uint8_t not_used_01              : 2;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 2;
  uint8_t dec_fifo_gyro            : 3;
  uint8_t dec_fifo_xl              : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_fifo_ctrl3_t;

#define LSM6DS3TR_C_FIFO_CTRL4                   0x09U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t dec_ds3_fifo             : 3;
  uint8_t dec_ds4_fifo             : 3;
  uint8_t only_high_data           : 1;
  uint8_t stop_on_fth              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t stop_on_fth              : 1;
  uint8_t only_high_data           : 1;
  uint8_t dec_ds4_fifo             : 3;
  uint8_t dec_ds3_fifo             : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_fifo_ctrl4_t;

#define LSM6DS3TR_C_FIFO_CTRL5                   0x0AU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t fifo_mode                : 3;
  uint8_t odr_fifo                 : 4;
  uint8_t not_used_01              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t odr_fifo                 : 4;
  uint8_t fifo_mode                : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_fifo_ctrl5_t;

#define LSM6DS3TR_C_DRDY_PULSE_CFG_G             0x0BU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t int2_wrist_tilt          : 1;
  uint8_t not_used_01              : 6;
  uint8_t drdy_pulsed              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t drdy_pulsed              : 1;
  uint8_t not_used_01              : 6;
  uint8_t int2_wrist_tilt          : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_drdy_pulse_cfg_g_t;

#define LSM6DS3TR_C_INT1_CTRL                    0x0DU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t int1_drdy_xl             : 1;
  uint8_t int1_drdy_g              : 1;
  uint8_t int1_boot                : 1;
  uint8_t int1_fth                 : 1;
  uint8_t int1_fifo_ovr            : 1;
  uint8_t int1_full_flag           : 1;
  uint8_t int1_sign_mot            : 1;
  uint8_t int1_step_detector       : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t int1_step_detector       : 1;
  uint8_t int1_sign_mot            : 1;
  uint8_t int1_full_flag           : 1;
  uint8_t int1_fifo_ovr            : 1;
  uint8_t int1_fth                 : 1;
  uint8_t int1_boot                : 1;
  uint8_t int1_drdy_g              : 1;
  uint8_t int1_drdy_xl             : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_int1_ctrl_t;

#define LSM6DS3TR_C_INT2_CTRL                    0x0EU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t int2_drdy_xl             : 1;
  uint8_t int2_drdy_g              : 1;
  uint8_t int2_drdy_temp           : 1;
  uint8_t int2_fth                 : 1;
  uint8_t int2_fifo_ovr            : 1;
  uint8_t int2_full_flag           : 1;
  uint8_t int2_step_count_ov       : 1;
  uint8_t int2_step_delta          : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t int2_step_delta          : 1;
  uint8_t int2_step_count_ov       : 1;
  uint8_t int2_full_flag           : 1;
  uint8_t int2_fifo_ovr            : 1;
  uint8_t int2_fth                 : 1;
  uint8_t int2_drdy_temp           : 1;
  uint8_t int2_drdy_g              : 1;
  uint8_t int2_drdy_xl             : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_int2_ctrl_t;

#define LSM6DS3TR_C_WHO_AM_I                     0x0FU
#define LSM6DS3TR_C_CTRL1_XL                     0x10U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t bw0_xl                   : 1;
  uint8_t lpf1_bw_sel              : 1;
  uint8_t fs_xl                    : 2;
  uint8_t odr_xl                   : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t odr_xl                   : 4;
  uint8_t fs_xl                    : 2;
  uint8_t lpf1_bw_sel              : 1;
  uint8_t bw0_xl                   : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_ctrl1_xl_t;

#define LSM6DS3TR_C_CTRL2_G                      0x11U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t fs_g                     : 3;  /* fs_g + fs_125 */
  uint8_t odr_g                    : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t odr_g                    : 4;
  uint8_t fs_g                     : 3;  /* fs_g + fs_125 */
  uint8_t not_used_01              : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_ctrl2_g_t;

#define LSM6DS3TR_C_CTRL3_C                      0x12U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t sw_reset                 : 1;
  uint8_t ble                      : 1;
  uint8_t if_inc                   : 1;
  uint8_t sim                      : 1;
  uint8_t pp_od                    : 1;
  uint8_t h_lactive                : 1;
  uint8_t bdu                      : 1;
  uint8_t boot                     : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t boot                     : 1;
  uint8_t bdu                      : 1;
  uint8_t h_lactive                : 1;
  uint8_t pp_od                    : 1;
  uint8_t sim                      : 1;
  uint8_t if_inc                   : 1;
  uint8_t ble                      : 1;
  uint8_t sw_reset                 : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_ctrl3_c_t;

#define LSM6DS3TR_C_CTRL4_C                      0x13U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t lpf1_sel_g               : 1;
  uint8_t i2c_disable              : 1;
  uint8_t drdy_mask                : 1;
  uint8_t den_drdy_int1            : 1;
  uint8_t int2_on_int1             : 1;
  uint8_t sleep                    : 1;
  uint8_t den_xl_en                : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t den_xl_en                : 1;
  uint8_t sleep                    : 1;
  uint8_t int2_on_int1             : 1;
  uint8_t den_drdy_int1            : 1;
  uint8_t drdy_mask                : 1;
  uint8_t i2c_disable              : 1;
  uint8_t lpf1_sel_g               : 1;
  uint8_t not_used_01              : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_ctrl4_c_t;

#define LSM6DS3TR_C_CTRL5_C                      0x14U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t st_xl                    : 2;
  uint8_t st_g                     : 2;
  uint8_t den_lh                   : 1;
  uint8_t rounding                 : 3;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t rounding                 : 3;
  uint8_t den_lh                   : 1;
  uint8_t st_g                     : 2;
  uint8_t st_xl                    : 2;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_ctrl5_c_t;

#define LSM6DS3TR_C_CTRL6_C                      0x15U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t ftype                    : 2;
  uint8_t not_used_01              : 1;
  uint8_t usr_off_w                : 1;
  uint8_t xl_hm_mode               : 1;
uint8_t den_mode                 :
  3;  /* trig_en + lvl_en + lvl2_en */
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
uint8_t den_mode                 :
  3;  /* trig_en + lvl_en + lvl2_en */
  uint8_t xl_hm_mode               : 1;
  uint8_t usr_off_w                : 1;
  uint8_t not_used_01              : 1;
  uint8_t ftype                    : 2;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_ctrl6_c_t;

#define LSM6DS3TR_C_CTRL7_G                      0x16U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 2;
  uint8_t rounding_status          : 1;
  uint8_t not_used_02              : 1;
  uint8_t hpm_g                    : 2;
  uint8_t hp_en_g                  : 1;
  uint8_t g_hm_mode                : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t g_hm_mode                : 1;
  uint8_t hp_en_g                  : 1;
  uint8_t hpm_g                    : 2;
  uint8_t not_used_02              : 1;
  uint8_t rounding_status          : 1;
  uint8_t not_used_01              : 2;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_ctrl7_g_t;

#define LSM6DS3TR_C_CTRL8_XL                     0x17U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t low_pass_on_6d           : 1;
  uint8_t not_used_01              : 1;
  uint8_t hp_slope_xl_en           : 1;
  uint8_t input_composite          : 1;
  uint8_t hp_ref_mode              : 1;
  uint8_t hpcf_xl                  : 2;
  uint8_t lpf2_xl_en               : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t lpf2_xl_en               : 1;
  uint8_t hpcf_xl                  : 2;
  uint8_t hp_ref_mode              : 1;
  uint8_t input_composite          : 1;
  uint8_t hp_slope_xl_en           : 1;
  uint8_t not_used_01              : 1;
  uint8_t low_pass_on_6d           : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_ctrl8_xl_t;

#define LSM6DS3TR_C_CTRL9_XL                     0x18U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 2;
  uint8_t soft_en                  : 1;
  uint8_t not_used_02              : 1;
  uint8_t den_xl_g                 : 1;
  uint8_t den_z                    : 1;
  uint8_t den_y                    : 1;
  uint8_t den_x                    : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t den_x                    : 1;
  uint8_t den_y                    : 1;
  uint8_t den_z                    : 1;
  uint8_t den_xl_g                 : 1;
  uint8_t not_used_02              : 1;
  uint8_t soft_en                  : 1;
  uint8_t not_used_01              : 2;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_ctrl9_xl_t;

#define LSM6DS3TR_C_CTRL10_C                     0x19U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t sign_motion_en           : 1;
  uint8_t pedo_rst_step            : 1;
  uint8_t func_en                  : 1;
  uint8_t tilt_en                  : 1;
  uint8_t pedo_en                  : 1;
  uint8_t timer_en                 : 1;
  uint8_t not_used_01              : 1;
  uint8_t wrist_tilt_en            : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t wrist_tilt_en            : 1;
  uint8_t not_used_01              : 1;
  uint8_t timer_en                 : 1;
  uint8_t pedo_en                  : 1;
  uint8_t tilt_en                  : 1;
  uint8_t func_en                  : 1;
  uint8_t pedo_rst_step            : 1;
  uint8_t sign_motion_en           : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_ctrl10_c_t;

#define LSM6DS3TR_C_MASTER_CONFIG                0x1AU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t master_on                : 1;
  uint8_t iron_en                  : 1;
  uint8_t pass_through_mode        : 1;
  uint8_t pull_up_en               : 1;
  uint8_t start_config             : 1;
  uint8_t not_used_01              : 1;
  uint8_t data_valid_sel_fifo      : 1;
  uint8_t drdy_on_int1             : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t drdy_on_int1             : 1;
  uint8_t data_valid_sel_fifo      : 1;
  uint8_t not_used_01              : 1;
  uint8_t start_config             : 1;
  uint8_t pull_up_en               : 1;
  uint8_t pass_through_mode        : 1;
  uint8_t iron_en                  : 1;
  uint8_t master_on                : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_master_config_t;


#define LSM6DS3TR_C_STATUS_REG                   0x1EU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t xlda                     : 1;
  uint8_t gda                      : 1;
  uint8_t tda                      : 1;
  uint8_t not_used_01              : 5;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 5;
  uint8_t tda                      : 1;
  uint8_t gda                      : 1;
  uint8_t xlda                     : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_status_reg_t;

#define LSM6DS3TR_C_OUT_TEMP_L                   0x20U
#define LSM6DS3TR_C_OUT_TEMP_H                   0x21U
#define LSM6DS3TR_C_OUTX_L_G                     0x22U
#define LSM6DS3TR_C_OUTX_H_G                     0x23U
#define LSM6DS3TR_C_OUTY_L_G                     0x24U
#define LSM6DS3TR_C_OUTY_H_G                     0x25U
#define LSM6DS3TR_C_OUTZ_L_G                     0x26U
#define LSM6DS3TR_C_OUTZ_H_G                     0x27U
#define LSM6DS3TR_C_OUTX_L_XL                    0x28U
#define LSM6DS3TR_C_OUTX_H_XL                    0x29U
#define LSM6DS3TR_C_OUTY_L_XL                    0x2AU
#define LSM6DS3TR_C_OUTY_H_XL                    0x2BU
#define LSM6DS3TR_C_OUTZ_L_XL                    0x2CU
#define LSM6DS3TR_C_OUTZ_H_XL                    0x2DU

#define LSM6DS3TR_C_FIFO_DATA_OUT_L              0x3EU
#define LSM6DS3TR_C_FIFO_DATA_OUT_H              0x3FU
#define LSM6DS3TR_C_TIMESTAMP0_REG               0x40U
#define LSM6DS3TR_C_TIMESTAMP1_REG               0x41U
#define LSM6DS3TR_C_TIMESTAMP2_REG               0x42U
#define LSM6DS3TR_C_STEP_TIMESTAMP_L             0x49U
#define LSM6DS3TR_C_STEP_TIMESTAMP_H             0x4AU
#define LSM6DS3TR_C_STEP_COUNTER_L               0x4BU
#define LSM6DS3TR_C_STEP_COUNTER_H               0x4CU

#define LSM6DS3TR_C_WRIST_TILT_IA                0x55U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 2;
  uint8_t wrist_tilt_ia_zneg       : 1;
  uint8_t wrist_tilt_ia_zpos       : 1;
  uint8_t wrist_tilt_ia_yneg       : 1;
  uint8_t wrist_tilt_ia_ypos       : 1;
  uint8_t wrist_tilt_ia_xneg       : 1;
  uint8_t wrist_tilt_ia_xpos       : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t wrist_tilt_ia_xpos       : 1;
  uint8_t wrist_tilt_ia_xneg       : 1;
  uint8_t wrist_tilt_ia_ypos       : 1;
  uint8_t wrist_tilt_ia_yneg       : 1;
  uint8_t wrist_tilt_ia_zpos       : 1;
  uint8_t wrist_tilt_ia_zneg       : 1;
  uint8_t not_used_01              : 2;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_wrist_tilt_ia_t;

#define LSM6DS3TR_C_TAP_CFG                      0x58U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t lir                      : 1;
  uint8_t tap_z_en                 : 1;
  uint8_t tap_y_en                 : 1;
  uint8_t tap_x_en                 : 1;
  uint8_t slope_fds                : 1;
  uint8_t inact_en                 : 2;
  uint8_t interrupts_enable        : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t interrupts_enable        : 1;
  uint8_t inact_en                 : 2;
  uint8_t slope_fds                : 1;
  uint8_t tap_x_en                 : 1;
  uint8_t tap_y_en                 : 1;
  uint8_t tap_z_en                 : 1;
  uint8_t lir                      : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_tap_cfg_t;

#define LSM6DS3TR_C_TAP_THS_6D                   0x59U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tap_ths                  : 5;
  uint8_t sixd_ths                 : 2;
  uint8_t d4d_en                   : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t d4d_en                   : 1;
  uint8_t sixd_ths                 : 2;
  uint8_t tap_ths                  : 5;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_tap_ths_6d_t;

#define LSM6DS3TR_C_INT_DUR2                     0x5AU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t shock                    : 2;
  uint8_t quiet                    : 2;
  uint8_t dur                      : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t dur                      : 4;
  uint8_t quiet                    : 2;
  uint8_t shock                    : 2;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_int_dur2_t;

#define LSM6DS3TR_C_WAKE_UP_THS                  0x5BU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t wk_ths                   : 6;
  uint8_t not_used_01              : 1;
  uint8_t single_double_tap        : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t single_double_tap        : 1;
  uint8_t not_used_01              : 1;
  uint8_t wk_ths                   : 6;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_wake_up_ths_t;

#define LSM6DS3TR_C_WAKE_UP_DUR                  0x5CU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t sleep_dur                : 4;
  uint8_t timer_hr                 : 1;
  uint8_t wake_dur                 : 2;
  uint8_t ff_dur                   : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t ff_dur                   : 1;
  uint8_t wake_dur                 : 2;
  uint8_t timer_hr                 : 1;
  uint8_t sleep_dur                : 4;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_wake_up_dur_t;

#define LSM6DS3TR_C_FREE_FALL                    0x5DU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t ff_ths                   : 3;
  uint8_t ff_dur                   : 5;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t ff_dur                   : 5;
  uint8_t ff_ths                   : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_free_fall_t;

#define LSM6DS3TR_C_MD1_CFG                      0x5EU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t int1_timer               : 1;
  uint8_t int1_tilt                : 1;
  uint8_t int1_6d                  : 1;
  uint8_t int1_double_tap          : 1;
  uint8_t int1_ff                  : 1;
  uint8_t int1_wu                  : 1;
  uint8_t int1_single_tap          : 1;
  uint8_t int1_inact_state         : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t int1_inact_state         : 1;
  uint8_t int1_single_tap          : 1;
  uint8_t int1_wu                  : 1;
  uint8_t int1_ff                  : 1;
  uint8_t int1_double_tap          : 1;
  uint8_t int1_6d                  : 1;
  uint8_t int1_tilt                : 1;
  uint8_t int1_timer               : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_md1_cfg_t;

#define LSM6DS3TR_C_MD2_CFG                      0x5FU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t int2_iron                : 1;
  uint8_t int2_tilt                : 1;
  uint8_t int2_6d                  : 1;
  uint8_t int2_double_tap          : 1;
  uint8_t int2_ff                  : 1;
  uint8_t int2_wu                  : 1;
  uint8_t int2_single_tap          : 1;
  uint8_t int2_inact_state         : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t int2_inact_state         : 1;
  uint8_t int2_single_tap          : 1;
  uint8_t int2_wu                  : 1;
  uint8_t int2_ff                  : 1;
  uint8_t int2_double_tap          : 1;
  uint8_t int2_6d                  : 1;
  uint8_t int2_tilt                : 1;
  uint8_t int2_iron                : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_md2_cfg_t;

#define LSM6DS3TR_C_MASTER_CMD_CODE              0x60U
typedef struct
{
  uint8_t master_cmd_code          : 8;
} lsm6ds3tr_c_master_cmd_code_t;

#define LSM6DS3TR_C_SENS_SYNC_SPI_ERROR_CODE     0x61U
typedef struct
{
  uint8_t error_code               : 8;
} lsm6ds3tr_c_sens_sync_spi_error_code_t;

#define LSM6DS3TR_C_OUT_MAG_RAW_X_L              0x66U
#define LSM6DS3TR_C_OUT_MAG_RAW_X_H              0x67U
#define LSM6DS3TR_C_OUT_MAG_RAW_Y_L              0x68U
#define LSM6DS3TR_C_OUT_MAG_RAW_Y_H              0x69U
#define LSM6DS3TR_C_OUT_MAG_RAW_Z_L              0x6AU
#define LSM6DS3TR_C_OUT_MAG_RAW_Z_H              0x6BU
#define LSM6DS3TR_C_X_OFS_USR                    0x73U
#define LSM6DS3TR_C_Y_OFS_USR                    0x74U
#define LSM6DS3TR_C_Z_OFS_USR                    0x75U
#define LSM6DS3TR_C_SLV0_ADD                     0x02U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t rw_0                     : 1;
  uint8_t slave0_add               : 7;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t slave0_add               : 7;
  uint8_t rw_0                     : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_slv0_add_t;

#define LSM6DS3TR_C_DATAWRITE_SRC_MODE_SUB_SLV0  0x0EU
typedef struct
{
  uint8_t slave_dataw              : 8;
} lsm6ds3tr_c_datawrite_src_mode_sub_slv0_t;

#define LSM6DS3TR_C_CONFIG_PEDO_THS_MIN          0x0FU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t ths_min                  : 5;
  uint8_t not_used_01              : 2;
  uint8_t pedo_fs                  : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t pedo_fs                  : 1;
  uint8_t not_used_01              : 2;
  uint8_t ths_min                  : 5;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_config_pedo_ths_min_t;

#define LSM6DS3TR_C_SM_THS                       0x13U
#define LSM6DS3TR_C_PEDO_DEB_REG                 0x14U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t deb_step      : 3;
  uint8_t deb_time      : 5;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t deb_time      : 5;
  uint8_t deb_step      : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6ds3tr_c_pedo_deb_reg_t;

#define LSM6DS3TR_C_STEP_COUNT_DELTA             0x15U
#define LSM6DS3TR_C_MAG_SI_XX                    0x24U
#define LSM6DS3TR_C_MAG_SI_XY                    0x25U
#define LSM6DS3TR_C_MAG_SI_XZ                    0x26U
#define LSM6DS3TR_C_MAG_SI_YX                    0x27U
#define LSM6DS3TR_C_MAG_SI_YY                    0x28U
#define LSM6DS3TR_C_MAG_SI_YZ                    0x29U
#define LSM6DS3TR_C_MAG_SI_ZX                    0x2AU
#define LSM6DS3TR_C_MAG_SI_ZY                    0x2BU
#define LSM6DS3TR_C_MAG_SI_ZZ                    0x2CU
#define LSM6DS3TR_C_MAG_OFFX_L                   0x2DU
#define LSM6DS3TR_C_MAG_OFFX_H                   0x2EU
#define LSM6DS3TR_C_MAG_OFFY_L                   0x2FU
#define LSM6DS3TR_C_MAG_OFFY_H                   0x30U
#define LSM6DS3TR_C_MAG_OFFZ_L                   0x31U
#define LSM6DS3TR_C_MAG_OFFZ_H                   0x32U

/**
  * @defgroup LSM6DS3TR_C_Register_Union
  * @brief    This union group all the registers having a bit-field
  *           description.
  *           This union is useful but it's not needed by the driver.
  *
  *           REMOVING this union you are compliant with:
  *           MISRA-C 2012 [Rule 19.2] -> " Union are not allowed "
  *
  * @{
  *
  */
typedef union
{
  lsm6ds3tr_c_func_cfg_access_t                  func_cfg_access;
  lsm6ds3tr_c_sensor_sync_time_frame_t           sensor_sync_time_frame;
  lsm6ds3tr_c_sensor_sync_res_ratio_t            sensor_sync_res_ratio;
  lsm6ds3tr_c_fifo_ctrl1_t                       fifo_ctrl1;
  lsm6ds3tr_c_fifo_ctrl2_t                       fifo_ctrl2;
  lsm6ds3tr_c_fifo_ctrl3_t                       fifo_ctrl3;
  lsm6ds3tr_c_fifo_ctrl4_t                       fifo_ctrl4;
  lsm6ds3tr_c_fifo_ctrl5_t                       fifo_ctrl5;
  lsm6ds3tr_c_drdy_pulse_cfg_g_t                 drdy_pulse_cfg_g;
  lsm6ds3tr_c_int1_ctrl_t                        int1_ctrl;
  lsm6ds3tr_c_int2_ctrl_t                        int2_ctrl;
  lsm6ds3tr_c_master_config_t                    master_config;
  lsm6ds3tr_c_status_reg_t                       status_reg;
  lsm6ds3tr_c_md1_cfg_t                          md1_cfg;
  lsm6ds3tr_c_md2_cfg_t                          md2_cfg;
  lsm6ds3tr_c_master_cmd_code_t                  master_cmd_code;
  lsm6ds3tr_c_sens_sync_spi_error_code_t
  sens_sync_spi_error_code;
  lsm6ds3tr_c_config_pedo_ths_min_t              config_pedo_ths_min;
  lsm6ds3tr_c_pedo_deb_reg_t                     pedo_deb_reg;
  bitwise_t                                  bitwise;
  uint8_t                                    byte;
} lsm6ds3tr_c_reg_t;

/**
  * @}
  *
  */

int32_t lsm6ds3tr_c_read_reg(stmdev_ctx_t *ctx, uint8_t reg,
                             uint8_t *data,
                             uint16_t len);
int32_t lsm6ds3tr_c_write_reg(stmdev_ctx_t *ctx, uint8_t reg,
                              uint8_t *data,
                              uint16_t len);

typedef enum
{
  LSM6DS3TR_C_2g       = 0,
  LSM6DS3TR_C_16g      = 1,
  LSM6DS3TR_C_4g       = 2,
  LSM6DS3TR_C_8g       = 3,
  LSM6DS3TR_C_XL_FS_ND = 4,  /* ERROR CODE */
} lsm6ds3tr_c_fs_xl_t;
int32_t lsm6ds3tr_c_xl_full_scale_set(stmdev_ctx_t *ctx,
                                      lsm6ds3tr_c_fs_xl_t val);
int32_t lsm6ds3tr_c_xl_full_scale_get(stmdev_ctx_t *ctx,
                                      lsm6ds3tr_c_fs_xl_t *val);

typedef enum
{
  LSM6DS3TR_C_XL_ODR_OFF      =  0,
  LSM6DS3TR_C_XL_ODR_12Hz5    =  1,
  LSM6DS3TR_C_XL_ODR_26Hz     =  2,
  LSM6DS3TR_C_XL_ODR_52Hz     =  3,
  LSM6DS3TR_C_XL_ODR_104Hz    =  4,
  LSM6DS3TR_C_XL_ODR_208Hz    =  5,
  LSM6DS3TR_C_XL_ODR_416Hz    =  6,
  LSM6DS3TR_C_XL_ODR_833Hz    =  7,
  LSM6DS3TR_C_XL_ODR_1k66Hz   =  8,
  LSM6DS3TR_C_XL_ODR_3k33Hz   =  9,
  LSM6DS3TR_C_XL_ODR_6k66Hz   = 10,
  LSM6DS3TR_C_XL_ODR_1Hz6     = 11,
  LSM6DS3TR_C_XL_ODR_ND       = 12,  /* ERROR CODE */
} lsm6ds3tr_c_odr_xl_t;
int32_t lsm6ds3tr_c_xl_data_rate_set(stmdev_ctx_t *ctx,
                                     lsm6ds3tr_c_odr_xl_t val);
int32_t lsm6ds3tr_c_xl_data_rate_get(stmdev_ctx_t *ctx,
                                     lsm6ds3tr_c_odr_xl_t *val);

typedef enum
{
  LSM6DS3TR_C_250dps     = 0,
  LSM6DS3TR_C_125dps     = 1,
  LSM6DS3TR_C_500dps     = 2,
  LSM6DS3TR_C_1000dps    = 4,
  LSM6DS3TR_C_2000dps    = 6,
  LSM6DS3TR_C_GY_FS_ND   = 7,    /* ERROR CODE */
} lsm6ds3tr_c_fs_g_t;
int32_t lsm6ds3tr_c_gy_full_scale_set(stmdev_ctx_t *ctx,
                                      lsm6ds3tr_c_fs_g_t val);
int32_t lsm6ds3tr_c_gy_full_scale_get(stmdev_ctx_t *ctx,
                                      lsm6ds3tr_c_fs_g_t *val);

typedef enum
{
  LSM6DS3TR_C_GY_ODR_OFF    =  0,
  LSM6DS3TR_C_GY_ODR_12Hz5  =  1,
  LSM6DS3TR_C_GY_ODR_26Hz   =  2,
  LSM6DS3TR_C_GY_ODR_52Hz   =  3,
  LSM6DS3TR_C_GY_ODR_104Hz  =  4,
  LSM6DS3TR_C_GY_ODR_208Hz  =  5,
  LSM6DS3TR_C_GY_ODR_416Hz  =  6,
  LSM6DS3TR_C_GY_ODR_833Hz  =  7,
  LSM6DS3TR_C_GY_ODR_1k66Hz =  8,
  LSM6DS3TR_C_GY_ODR_3k33Hz =  9,
  LSM6DS3TR_C_GY_ODR_6k66Hz = 10,
  LSM6DS3TR_C_GY_ODR_ND     = 11,    /* ERROR CODE */
} lsm6ds3tr_c_odr_g_t;
int32_t lsm6ds3tr_c_gy_data_rate_set(stmdev_ctx_t *ctx,
                                     lsm6ds3tr_c_odr_g_t val);
int32_t lsm6ds3tr_c_gy_data_rate_get(stmdev_ctx_t *ctx,
                                     lsm6ds3tr_c_odr_g_t *val);

int32_t lsm6ds3tr_c_block_data_update_set(stmdev_ctx_t *ctx,
                                          uint8_t val);
int32_t lsm6ds3tr_c_block_data_update_get(stmdev_ctx_t *ctx,
                                          uint8_t *val);

typedef enum
{
  LSM6DS3TR_C_LSb_1mg   = 0,
  LSM6DS3TR_C_LSb_16mg  = 1,
  LSM6DS3TR_C_WEIGHT_ND = 2,
} lsm6ds3tr_c_usr_off_w_t;
int32_t lsm6ds3tr_c_xl_offset_weight_set(stmdev_ctx_t *ctx,
                                         lsm6ds3tr_c_usr_off_w_t val);
int32_t lsm6ds3tr_c_xl_offset_weight_get(stmdev_ctx_t *ctx,
                                         lsm6ds3tr_c_usr_off_w_t *val);

typedef enum
{
  LSM6DS3TR_C_XL_HIGH_PERFORMANCE  = 0,
  LSM6DS3TR_C_XL_NORMAL            = 1,
  LSM6DS3TR_C_XL_PW_MODE_ND        = 2,    /* ERROR CODE */
} lsm6ds3tr_c_xl_hm_mode_t;
int32_t lsm6ds3tr_c_xl_power_mode_set(stmdev_ctx_t *ctx,
                                      lsm6ds3tr_c_xl_hm_mode_t val);
int32_t lsm6ds3tr_c_xl_power_mode_get(stmdev_ctx_t *ctx,
                                      lsm6ds3tr_c_xl_hm_mode_t *val);

typedef enum
{
  LSM6DS3TR_C_GY_HIGH_PERFORMANCE  = 0,
  LSM6DS3TR_C_GY_NORMAL            = 1,
  LSM6DS3TR_C_GY_PW_MODE_ND        = 2,    /* ERROR CODE */
} lsm6ds3tr_c_g_hm_mode_t;

typedef enum
{
  LSM6DS3TR_C_BYPASS_MODE           = 0,
  LSM6DS3TR_C_FIFO_MODE             = 1,
  LSM6DS3TR_C_STREAM_TO_FIFO_MODE   = 3,
  LSM6DS3TR_C_BYPASS_TO_STREAM_MODE = 4,
  LSM6DS3TR_C_STREAM_MODE           = 6,
  LSM6DS3TR_C_FIFO_MODE_ND          = 8,    /* ERROR CODE */
} lsm6ds3tr_c_fifo_mode_t;

typedef enum
{
  LSM6DS3TR_C_XL_ANA_BW_1k5Hz = 0,
  LSM6DS3TR_C_XL_ANA_BW_400Hz = 1,
  LSM6DS3TR_C_XL_ANA_BW_ND    = 2,    /* ERROR CODE */
} lsm6ds3tr_c_bw0_xl_t;
int32_t lsm6ds3tr_c_xl_filter_analog_set(stmdev_ctx_t *ctx,
                                         lsm6ds3tr_c_bw0_xl_t val);
typedef enum
{
  LSM6DS3TR_C_XL_LP1_ODR_DIV_2 = 0,
  LSM6DS3TR_C_XL_LP1_ODR_DIV_4 = 1,
  LSM6DS3TR_C_XL_LP1_NA        = 2,  /* ERROR CODE */
} lsm6ds3tr_c_lpf1_bw_sel_t;
int32_t lsm6ds3tr_c_xl_lp1_bandwidth_set(stmdev_ctx_t *ctx,lsm6ds3tr_c_lpf1_bw_sel_t val);

int32_t lsm6ds3tr_c_device_id_get(stmdev_ctx_t *ctx, uint8_t *buff);
int32_t lsm6ds3tr_c_reset_set(stmdev_ctx_t *ctx, uint8_t val);
int32_t lsm6ds3tr_c_reset_get(stmdev_ctx_t *ctx, uint8_t *val);
int32_t lsm6ds3tr_c_fifo_mode_set(stmdev_ctx_t *ctx,
                                  lsm6ds3tr_c_fifo_mode_t val);

typedef enum
{
  LSM6DS3TR_C_XL_LOW_LAT_LP_ODR_DIV_50     = 0x00,
  LSM6DS3TR_C_XL_LOW_LAT_LP_ODR_DIV_100    = 0x01,
  LSM6DS3TR_C_XL_LOW_LAT_LP_ODR_DIV_9      = 0x02,
  LSM6DS3TR_C_XL_LOW_LAT_LP_ODR_DIV_400    = 0x03,
  LSM6DS3TR_C_XL_LOW_NOISE_LP_ODR_DIV_50   = 0x10,
  LSM6DS3TR_C_XL_LOW_NOISE_LP_ODR_DIV_100  = 0x11,
  LSM6DS3TR_C_XL_LOW_NOISE_LP_ODR_DIV_9    = 0x12,
  LSM6DS3TR_C_XL_LOW_NOISE_LP_ODR_DIV_400  = 0x13,
  LSM6DS3TR_C_XL_LP_NA                     = 0x20, /* ERROR CODE */
} lsm6ds3tr_c_input_composite_t;
int32_t lsm6ds3tr_c_xl_lp2_bandwidth_set(stmdev_ctx_t *ctx,
                                         lsm6ds3tr_c_input_composite_t val);

typedef enum
{
  LSM6DS3TR_C_LP2_ONLY                    = 0x00,

  LSM6DS3TR_C_HP_16mHz_LP2                = 0x80,
  LSM6DS3TR_C_HP_65mHz_LP2                = 0x90,
  LSM6DS3TR_C_HP_260mHz_LP2               = 0xA0,
  LSM6DS3TR_C_HP_1Hz04_LP2                = 0xB0,

  LSM6DS3TR_C_HP_DISABLE_LP1_LIGHT        = 0x0A,
  LSM6DS3TR_C_HP_DISABLE_LP1_NORMAL       = 0x09,
  LSM6DS3TR_C_HP_DISABLE_LP_STRONG        = 0x08,
  LSM6DS3TR_C_HP_DISABLE_LP1_AGGRESSIVE   = 0x0B,

  LSM6DS3TR_C_HP_16mHz_LP1_LIGHT          = 0x8A,
  LSM6DS3TR_C_HP_65mHz_LP1_NORMAL         = 0x99,
  LSM6DS3TR_C_HP_260mHz_LP1_STRONG        = 0xA8,
  LSM6DS3TR_C_HP_1Hz04_LP1_AGGRESSIVE     = 0xBB,

  LSM6DS3TR_C_HP_GY_BAND_NA               = 0xFF,    /* ERROR CODE */
} lsm6ds3tr_c_lpf1_sel_g_t;
int32_t lsm6ds3tr_c_gy_band_pass_set(stmdev_ctx_t *ctx,
                                     lsm6ds3tr_c_lpf1_sel_g_t val);
int32_t lsm6ds3tr_c_status_reg_get(stmdev_ctx_t *ctx,
                                   lsm6ds3tr_c_status_reg_t *val);
int32_t lsm6ds3tr_c_temperature_raw_get(stmdev_ctx_t *ctx,
                                        int16_t *val);
int32_t lsm6ds3tr_c_angular_rate_raw_get(stmdev_ctx_t *ctx,
                                         int16_t *val);
int32_t lsm6ds3tr_c_acceleration_raw_get(stmdev_ctx_t *ctx,
                                         int16_t *val);


#ifdef __cplusplus
}
#endif

#endif /* LSM6DS3TR_C_DRIVER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
