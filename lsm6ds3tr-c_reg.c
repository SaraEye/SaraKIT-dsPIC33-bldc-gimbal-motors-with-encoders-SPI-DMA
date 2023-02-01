/**
  ******************************************************************************
  * @file    lsm6ds3tr_c_reg.c
  * @author  Sensors Software Solution Team
  * @brief   LSM6DS3TR_C driver file
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

#include "lsm6ds3tr-c_reg.h"

/**
  * @defgroup    LSM6DS3TR_C
  * @brief       This file provides a set of functions needed to drive the
  *              lsm6ds3tr_c enanced inertial module.
  * @{
  *
  */

/**
  * @defgroup    LSM6DS3TR_C_interfaces_functions
  * @brief       This section provide a set of functions used to read and
  *              write a generic register of the device.
  *              MANDATORY: return 0 -> no Error.
  * @{
  *
  */

/**
  * @brief  Read generic device register
  *
  * @param  ctx   read / write interface definitions(ptr)
  * @param  reg   register to read
  * @param  data  pointer to buffer that store the data read(ptr)
  * @param  len   number of consecutive register to read
  * @retval       interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6ds3tr_c_read_reg(stmdev_ctx_t *ctx, uint8_t reg,
                             uint8_t *data,
                             uint16_t len)
{
  int32_t ret;

  ret = ctx->read_reg(ctx->handle, reg, data, len);

  return ret;
}

/**
  * @brief  Write generic device register
  *
  * @param  ctx   read / write interface definitions(ptr)
  * @param  reg   register to write
  * @param  data  pointer to data to write in register reg(ptr)
  * @param  len   number of consecutive register to write
  * @retval       interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6ds3tr_c_write_reg(stmdev_ctx_t *ctx, uint8_t reg,
                              uint8_t *data,
                              uint16_t len)
{
  int32_t ret;

  ret = ctx->write_reg(ctx->handle, reg, data, len);

  return ret;
}

/**
  * @brief  Accelerometer full-scale selection.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of fs_xl in reg CTRL1_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6ds3tr_c_xl_full_scale_set(stmdev_ctx_t *ctx,
                                      lsm6ds3tr_c_fs_xl_t val)
{
  lsm6ds3tr_c_ctrl1_xl_t ctrl1_xl;
  int32_t ret;

  ret = lsm6ds3tr_c_read_reg(ctx, LSM6DS3TR_C_CTRL1_XL,
                             (uint8_t *)&ctrl1_xl, 1);

  if (ret == 0)
  {
    ctrl1_xl.fs_xl = (uint8_t) val;
    ret = lsm6ds3tr_c_write_reg(ctx, LSM6DS3TR_C_CTRL1_XL,
                                (uint8_t *)&ctrl1_xl, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer data rate selection.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of odr_xl in reg CTRL1_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6ds3tr_c_xl_data_rate_set(stmdev_ctx_t *ctx,
                                     lsm6ds3tr_c_odr_xl_t val)
{
  lsm6ds3tr_c_ctrl1_xl_t ctrl1_xl;
  int32_t ret;

  ret = lsm6ds3tr_c_read_reg(ctx, LSM6DS3TR_C_CTRL1_XL,
                             (uint8_t *)&ctrl1_xl, 1);

  if (ret == 0)
  {
    ctrl1_xl.odr_xl = (uint8_t) val;
    ret = lsm6ds3tr_c_write_reg(ctx, LSM6DS3TR_C_CTRL1_XL,
                                (uint8_t *)&ctrl1_xl, 1);
  }

  return ret;
}


/**
  * @brief  Gyroscope chain full-scale selection.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of fs_g in reg CTRL2_G
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6ds3tr_c_gy_full_scale_set(stmdev_ctx_t *ctx,
                                      lsm6ds3tr_c_fs_g_t val)
{
  lsm6ds3tr_c_ctrl2_g_t ctrl2_g;
  int32_t ret;

  ret = lsm6ds3tr_c_read_reg(ctx, LSM6DS3TR_C_CTRL2_G,
                             (uint8_t *)&ctrl2_g, 1);

  if (ret == 0)
  {
    ctrl2_g.fs_g = (uint8_t) val;
    ret = lsm6ds3tr_c_write_reg(ctx, LSM6DS3TR_C_CTRL2_G,
                                (uint8_t *)&ctrl2_g, 1);
  }

  return ret;
}


/**
  * @brief  Gyroscope data rate selection.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of odr_g in reg CTRL2_G
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6ds3tr_c_gy_data_rate_set(stmdev_ctx_t *ctx,
                                     lsm6ds3tr_c_odr_g_t val)
{
  lsm6ds3tr_c_ctrl2_g_t ctrl2_g;
  int32_t ret;

  ret = lsm6ds3tr_c_read_reg(ctx, LSM6DS3TR_C_CTRL2_G,
                             (uint8_t *)&ctrl2_g, 1);

  if (ret == 0)
  {
    ctrl2_g.odr_g = (uint8_t) val;
    ret = lsm6ds3tr_c_write_reg(ctx, LSM6DS3TR_C_CTRL2_G,
                                (uint8_t *)&ctrl2_g, 1);
  }

  return ret;
}

/**
  * @brief  Block data update.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of bdu in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6ds3tr_c_block_data_update_set(stmdev_ctx_t *ctx,
                                          uint8_t val)
{
  lsm6ds3tr_c_ctrl3_c_t ctrl3_c;
  int32_t ret;

  ret = lsm6ds3tr_c_read_reg(ctx, LSM6DS3TR_C_CTRL3_C,
                             (uint8_t *)&ctrl3_c, 1);

  if (ret == 0)
  {
    ctrl3_c.bdu = val;
    ret = lsm6ds3tr_c_write_reg(ctx, LSM6DS3TR_C_CTRL3_C,
                                (uint8_t *)&ctrl3_c, 1);
  }

  return ret;
}


/**
  * @brief  High-performance operating mode disable for gyroscope.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of g_hm_mode in reg CTRL7_G
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6ds3tr_c_gy_power_mode_set(stmdev_ctx_t *ctx,
                                      lsm6ds3tr_c_g_hm_mode_t val)
{
  lsm6ds3tr_c_ctrl7_g_t ctrl7_g;
  int32_t ret;

  ret = lsm6ds3tr_c_read_reg(ctx, LSM6DS3TR_C_CTRL7_G,
                             (uint8_t *)&ctrl7_g, 1);

  if (ret == 0)
  {
    ctrl7_g.g_hm_mode = (uint8_t) val;
    ret = lsm6ds3tr_c_write_reg(ctx, LSM6DS3TR_C_CTRL7_G,
                                (uint8_t *)&ctrl7_g, 1);
  }

  return ret;
}

int32_t lsm6ds3tr_c_device_id_get(stmdev_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lsm6ds3tr_c_read_reg(ctx, LSM6DS3TR_C_WHO_AM_I, buff, 1);

  return ret;
}

int32_t lsm6ds3tr_c_reset_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6ds3tr_c_ctrl3_c_t ctrl3_c;
  int32_t ret;

  ret = lsm6ds3tr_c_read_reg(ctx, LSM6DS3TR_C_CTRL3_C,
                             (uint8_t *)&ctrl3_c, 1);

  if (ret == 0)
  {
    ctrl3_c.sw_reset = val;
    ret = lsm6ds3tr_c_write_reg(ctx, LSM6DS3TR_C_CTRL3_C,
                                (uint8_t *)&ctrl3_c, 1);
  }

  return ret;
}

int32_t lsm6ds3tr_c_reset_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6ds3tr_c_ctrl3_c_t ctrl3_c;
  int32_t ret;

  ret = lsm6ds3tr_c_read_reg(ctx, LSM6DS3TR_C_CTRL3_C,
                             (uint8_t *)&ctrl3_c, 1);
  *val = ctrl3_c.sw_reset;

  return ret;
}

int32_t lsm6ds3tr_c_fifo_mode_set(stmdev_ctx_t *ctx,
                                  lsm6ds3tr_c_fifo_mode_t val)
{
  lsm6ds3tr_c_fifo_ctrl5_t fifo_ctrl5;
  int32_t ret;

  ret = lsm6ds3tr_c_read_reg(ctx, LSM6DS3TR_C_FIFO_CTRL5,
                             (uint8_t *)&fifo_ctrl5, 1);

  if (ret == 0)
  {
    fifo_ctrl5.fifo_mode = (uint8_t)val;
    ret = lsm6ds3tr_c_write_reg(ctx, LSM6DS3TR_C_FIFO_CTRL5,
                                (uint8_t *)&fifo_ctrl5, 1);
  }

  return ret;
}

int32_t lsm6ds3tr_c_xl_filter_analog_set(stmdev_ctx_t *ctx,
                                         lsm6ds3tr_c_bw0_xl_t val)
{
  lsm6ds3tr_c_ctrl1_xl_t ctrl1_xl;
  int32_t ret;

  ret = lsm6ds3tr_c_read_reg(ctx, LSM6DS3TR_C_CTRL1_XL,
                             (uint8_t *)&ctrl1_xl, 1);

  if (ret == 0)
  {
    ctrl1_xl.bw0_xl = (uint8_t) val;
    ret = lsm6ds3tr_c_write_reg(ctx, LSM6DS3TR_C_CTRL1_XL,
                                (uint8_t *)&ctrl1_xl, 1);
  }

  return ret;
}

int32_t lsm6ds3tr_c_xl_lp1_bandwidth_set(stmdev_ctx_t *ctx,
                                         lsm6ds3tr_c_lpf1_bw_sel_t val)
{
  lsm6ds3tr_c_ctrl1_xl_t ctrl1_xl;
  lsm6ds3tr_c_ctrl8_xl_t ctrl8_xl;
  int32_t ret;

  ret = lsm6ds3tr_c_read_reg(ctx, LSM6DS3TR_C_CTRL1_XL,
                             (uint8_t *)&ctrl1_xl, 1);

  if (ret == 0)
  {
    ctrl1_xl.lpf1_bw_sel = (uint8_t) val;
    ret = lsm6ds3tr_c_write_reg(ctx, LSM6DS3TR_C_CTRL1_XL,
                                (uint8_t *)&ctrl1_xl, 1);

    if (ret == 0)
    {
      ret = lsm6ds3tr_c_read_reg(ctx, LSM6DS3TR_C_CTRL8_XL,
                                 (uint8_t *)&ctrl8_xl, 1);

      if (ret == 0)
      {
        ctrl8_xl.lpf2_xl_en = 0;
        ctrl8_xl.hp_slope_xl_en = 0;
        ret = lsm6ds3tr_c_write_reg(ctx, LSM6DS3TR_C_CTRL8_XL,
                                    (uint8_t *)&ctrl8_xl, 1);
      }
    }
  }

  return ret;
}

int32_t lsm6ds3tr_c_xl_lp2_bandwidth_set(stmdev_ctx_t *ctx,
                                         lsm6ds3tr_c_input_composite_t val)
{
  lsm6ds3tr_c_ctrl8_xl_t ctrl8_xl;
  int32_t ret;

  ret = lsm6ds3tr_c_read_reg(ctx, LSM6DS3TR_C_CTRL8_XL,
                             (uint8_t *)&ctrl8_xl, 1);

  if (ret == 0)
  {
    ctrl8_xl.input_composite = ((uint8_t) val & 0x10U) >> 4;
    ctrl8_xl.hpcf_xl = (uint8_t) val & 0x03U;
    ctrl8_xl.lpf2_xl_en = 1;
    ctrl8_xl.hp_slope_xl_en = 0;
    ret = lsm6ds3tr_c_write_reg(ctx, LSM6DS3TR_C_CTRL8_XL,
                                (uint8_t *)&ctrl8_xl, 1);
  }

  return ret;
}

int32_t lsm6ds3tr_c_gy_band_pass_set(stmdev_ctx_t *ctx,
                                     lsm6ds3tr_c_lpf1_sel_g_t val)
{
  lsm6ds3tr_c_ctrl4_c_t ctrl4_c;
  lsm6ds3tr_c_ctrl6_c_t ctrl6_c;
  lsm6ds3tr_c_ctrl7_g_t ctrl7_g;
  int32_t ret;

  ret = lsm6ds3tr_c_read_reg(ctx, LSM6DS3TR_C_CTRL7_G,
                             (uint8_t *)&ctrl7_g, 1);

  if (ret == 0)
  {
    ctrl7_g.hpm_g  = ((uint8_t)val & 0x30U) >> 4;
    ctrl7_g.hp_en_g = ((uint8_t)val & 0x80U) >> 7;
    ret = lsm6ds3tr_c_write_reg(ctx, LSM6DS3TR_C_CTRL7_G,
                                (uint8_t *)&ctrl7_g, 1);

    if (ret == 0)
    {
      ret = lsm6ds3tr_c_read_reg(ctx, LSM6DS3TR_C_CTRL6_C,
                                 (uint8_t *)&ctrl6_c, 1);

      if (ret == 0)
      {
        ctrl6_c.ftype = (uint8_t)val & 0x03U;
        ret = lsm6ds3tr_c_write_reg(ctx, LSM6DS3TR_C_CTRL6_C,
                                    (uint8_t *)&ctrl6_c, 1);

        if (ret == 0)
        {
          ret = lsm6ds3tr_c_read_reg(ctx, LSM6DS3TR_C_CTRL4_C,
                                     (uint8_t *)&ctrl4_c, 1);

          if (ret == 0)
          {
            ctrl4_c.lpf1_sel_g = ((uint8_t)val & 0x08U) >> 3;
            ret = lsm6ds3tr_c_write_reg(ctx, LSM6DS3TR_C_CTRL4_C,
                                        (uint8_t *)&ctrl4_c, 1);
          }
        }
      }
    }
  }

  return ret;
}
