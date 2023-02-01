#include "LSM6DS3TR.h"

#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "mcc_generated_files/i2c1.h"
#include "mcc_generated_files/delay.h"
#include "lsm6ds3tr-c_reg.h"

#define LSM6DS3TR_C_WHO_AM_I    0x0FU
#define LSM6DS3TR_C_CTRL1_XL    0x10U
#define LSM6DS3TR_C_ID          0x6AU

#define PROPERTY_ENABLE                 (1U)

#define ACC_I2C_ADDRESS ((uint8_t)0b1101010)

volatile int16_t I2CgetMode=0;
volatile bool I2Cbusy=0;
volatile uint8_t tempdelay=25;

lsm6ds3tr_c_reg_t reg;
static uint8_t reg_address;
static I2C1_TRANSACTION_REQUEST_BLOCK trb[2];

int16_t data_raw_acceleration[3];
int16_t data_raw_angular_rate[3];
int16_t data_raw_temperature;

int16_t new_data_raw_acceleration[3];
int16_t new_data_raw_angular_rate[3];
int16_t new_data_raw_temperature;

volatile bool LSM6DS3TREnable=false;

const uint8_t CTRL_REG1_ADDRESS = 0x20;

static uint8_t writeBuffer[20];             // Buffer for I2C writing.
volatile I2C1_MESSAGE_STATUS writeStatus;   // Status for I2C writing.
volatile I2C1_MESSAGE_STATUS readStatus;    // Status for I2C reading.

uint8_t I2C1_write_bytes(uint8_t device_address, uint8_t reg_address, uint8_t length, uint8_t *wr_data)
{
    uint8_t i,j=0;
    writeStatus = I2C1_MESSAGE_PENDING;
    
    writeBuffer[0] = reg_address; // Register Adresse
    for(i=1;i<length+1; i++)
        {
            writeBuffer[i] = wr_data[j];
            j++;
        }
    static I2C1_TRANSACTION_REQUEST_BLOCK trb[2];
    I2C1_MasterWriteTRBBuild(&trb[0], (uint8_t*)writeBuffer, length+1, device_address);
    I2C1_MasterTRBInsert(1, &trb[0], &writeStatus);
    if (writeStatus == I2C1_MESSAGE_FAIL)
    {
        //failed to insert transaction (queue full?)
    } else {
        uint32_t br=0;
        while(writeStatus == I2C1_MESSAGE_PENDING && br<100000) {
            br++;
        };
        while(writeStatus == I2C1_MESSAGE_PENDING);
        DELAY_microseconds(30);
        return (writeStatus == I2C1_MESSAGE_COMPLETE);
    }   
} 
 
uint8_t I2C1_read_bytes(uint8_t device_address, uint8_t reg_address, uint8_t length, uint8_t *pData)
{
    I2C1_MasterWriteTRBBuild(&trb[0], &reg_address, 1, device_address);
    I2C1_MasterReadTRBBuild(&trb[1], pData, length, device_address);
    I2C1_MasterTRBInsert(2, &trb[0], &readStatus);
    if (readStatus == I2C1_MESSAGE_FAIL)
    {
        return I2C1_MESSAGE_FAIL;
        //failed to insert transaction (queue full?)
    } else {
        uint32_t br=0;
        while(readStatus == I2C1_MESSAGE_PENDING && br<100000) {
            br++;
        };
        DELAY_microseconds(30);
        return readStatus;
    }   
}

uint8_t I2C1_read_bytes2(uint8_t device_address, uint8_t regaddress, uint8_t length, uint8_t *pData)
{
    reg_address=regaddress;
    I2C1_MasterWriteTRBBuild(&trb[0], &reg_address, 1, device_address);
    I2C1_MasterReadTRBBuild(&trb[1], pData, length, device_address);
    I2C1_MasterTRBInsert(2, &trb[0], &readStatus);
    return 0;
}

static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len)
{  
   I2C1_write_bytes(ACC_I2C_ADDRESS,reg,len,bufp);
   return 0;
}
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
   I2C1_read_bytes(ACC_I2C_ADDRESS,reg,len,bufp);
   return 0;
}

int  _initiated = 0;
int  _deviceAddress = 0;

uint8_t whoamI, rst;
stmdev_ctx_t dev_ctx;      

void lsm6ds3tr_i2c_init() {
    I2C1_Initialize();
    _deviceAddress = 0x6A;
    if (_initiated==0){
        /* Initialize mems driver interface */
        dev_ctx.write_reg = platform_write;
        dev_ctx.read_reg = platform_read;

        /* Init test platform */                       
        /* Wait sensor boot time */
        DELAY_milliseconds(15);
        
        /* Check device ID */        
        whoamI=0;
        lsm6ds3tr_c_device_id_get(&dev_ctx, &whoamI);
        if ( whoamI != LSM6DS3TR_C_ID )
        {
           return;
        }

        /* Restore default configuration */
        lsm6ds3tr_c_reset_set(&dev_ctx, PROPERTY_ENABLE);
        do {
           Delay(5);
           lsm6ds3tr_c_reset_get(&dev_ctx, &rst);
        } while (rst);      
        
        /* Enable Block Data Update */
        lsm6ds3tr_c_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
        lsm6ds3tr_c_fifo_mode_set(&dev_ctx, LSM6DS3TR_C_BYPASS_MODE);
        /* Set Output Data Rate */
        lsm6ds3tr_c_xl_data_rate_set(&dev_ctx, LSM6DS3TR_C_XL_ODR_3k33Hz);
        lsm6ds3tr_c_gy_data_rate_set(&dev_ctx, LSM6DS3TR_C_GY_ODR_3k33Hz);
        /* Set full scale */
        lsm6ds3tr_c_xl_full_scale_set(&dev_ctx, LSM6DS3TR_C_2g);
        lsm6ds3tr_c_gy_full_scale_set(&dev_ctx, LSM6DS3TR_C_1000dps);
        lsm6ds3tr_c_gy_power_mode_set(&dev_ctx, LSM6DS3TR_C_GY_HIGH_PERFORMANCE);
        /* Configure filtering chain(No aux interface) */
        /* Accelerometer - analog filter */
        lsm6ds3tr_c_xl_filter_analog_set(&dev_ctx, LSM6DS3TR_C_XL_ANA_BW_400Hz);
        /* Accelerometer - LPF1 path ( LPF2 not used )*/
        lsm6ds3tr_c_xl_lp1_bandwidth_set(&dev_ctx, LSM6DS3TR_C_XL_LP1_ODR_DIV_4);
        /* Accelerometer - LPF1 + LPF2 path */
        lsm6ds3tr_c_xl_lp2_bandwidth_set(&dev_ctx, LSM6DS3TR_C_XL_LOW_NOISE_LP_ODR_DIV_100);
        /* Accelerometer - High Pass / Slope path */
        //lsm6ds3tr_c_xl_reference_mode_set(&dev_ctx, PROPERTY_DISABLE);
        //lsm6ds3tr_c_xl_hp_bandwidth_set(&dev_ctx, LSM6DS3TR_C_XL_HP_ODR_DIV_100);
        /* Gyroscope - filtering chain */
        //lsm6ds3tr_c_gy_band_pass_set(&dev_ctx, LSM6DS3TR_C_HP_260mHz_LP2);
        lsm6ds3tr_c_gy_band_pass_set(&dev_ctx, LSM6DS3TR_C_LP2_ONLY);
    }
};

void lsm6ds3tr_i2c_check(){
    if (LSM6DS3TREnable==false)
        return; 
    if (I2Cbusy)
        return;
    I2Cbusy=true;
    
    int16_t sw=I2CgetMode;
    switch (sw) {
        case 0:
            I2C1_read_bytes(ACC_I2C_ADDRESS,LSM6DS3TR_C_STATUS_REG,1,&reg.status_reg);
            I2CgetMode=1;
            break;
        case 1:
            //acc?
            if (reg.status_reg.xlda) {
                memset(new_data_raw_acceleration, 0x00, 3 * sizeof(int16_t));
                I2C1_read_bytes2(ACC_I2C_ADDRESS,LSM6DS3TR_C_OUTX_L_XL,6,new_data_raw_acceleration);
            }
            I2CgetMode=2;
            break;
        case 2:   
            if (readStatus == I2C1_MESSAGE_FAIL){
                I2CgetMode=7;
                break;
            }
            if (readStatus == I2C1_MESSAGE_PENDING)
                break;
            if (readStatus == I2C1_MESSAGE_COMPLETE) {
                memcpy(data_raw_acceleration,new_data_raw_acceleration,3 * sizeof(int16_t));
                //gyro?
                if (reg.status_reg.gda) {
                    I2CgetMode=3;
                } else {
                    I2CgetMode=7;
                }
            } else {
                I2CgetMode=7;
            }
            break;
        case 3:
            memset(new_data_raw_angular_rate, 0x00, 3 * sizeof(int16_t));
            I2C1_read_bytes2(ACC_I2C_ADDRESS,LSM6DS3TR_C_OUTX_L_G,6,new_data_raw_angular_rate);
            I2CgetMode=4;
            break;
        case 4:
            if (readStatus == I2C1_MESSAGE_FAIL){
                I2CgetMode=7;
                break;
            }            
            if (readStatus == I2C1_MESSAGE_PENDING)
                break;            
            if (readStatus == I2C1_MESSAGE_COMPLETE) {
                memcpy(data_raw_angular_rate,new_data_raw_angular_rate,3 * sizeof(int16_t));
                //temp?
                if (tempdelay==0 && reg.status_reg.tda) {
                    tempdelay=25;
                    I2CgetMode=5;
                } else {
                    I2CgetMode=7;
                }
                tempdelay--;
            } else {
                I2CgetMode=7;
            }
            break;
        case 5:
            memset(&new_data_raw_temperature, 0x00, sizeof(int16_t));
            I2C1_read_bytes2(ACC_I2C_ADDRESS,LSM6DS3TR_C_OUT_TEMP_L,2,&new_data_raw_temperature);
            I2CgetMode=6;
            break;
        case 6:
            if (readStatus == I2C1_MESSAGE_FAIL){
                I2CgetMode=7;
                break;
            }            
            if (readStatus == I2C1_MESSAGE_PENDING)
                break;            
            if (readStatus == I2C1_MESSAGE_COMPLETE) {
                data_raw_temperature=new_data_raw_temperature;
                I2CgetMode=7;
            } else {
                I2CgetMode=7;
            }
            break;
        case 7:
            I2CgetMode=0;
            break;            
        default:{}
    }
    I2Cbusy=false;
};

