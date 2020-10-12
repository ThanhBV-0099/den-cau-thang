/****************************************Copyright (c)*************************
**                            All rights reserved (C), 2015-2020, Tuya
**
**                                 http://www.tuya.com
**
**--------------File information-------------------------------------------------------
**File name   : protocol.c
**Description : Deliver/report data processing function
**Instructions for use :

                  *******Very important, be sure to watch！！！********

** 1、The user implements the data delivery/reporting function in this file.
** 2、DP ID / TYPE and data processing functions require the user to implement according to the actual definition
** 3、There are #err hints inside the function that needs the user to implement the code after starting some macro definitions. 
**    Please delete the #err after completing the function.
**
**--------------Current revision---------------------------------------------------
** Version : v2.5.1
** Date    : 2018.10.27.
** Description: 1:Turn off streaming service by default
                2:Increase 03 protocol wifi status macro definition
		        3:Update and modify some function comments
		   
** Version : v2.5.0
** Date    : 2018.4.18
** Description: 1:The protocol version is changed to 0x03
                2:Increase WIFI module heartbeat off function
                3:Increase weather function

** Version : v2.3.8
** Date    : 2018.1.17
** Description: 1:Variables added volatile to prevent compiler optimization
                2:Add #error hint

** Version : v2.3.7
** Date    : 2017.4.18
** Description: 1:Optimize serial queue reception processing
		   
** Version : v2.3.6
** Date    : 2016.7.21
** Description: 1:Fix getting local time error
                2:Add hex_to_bcd conversion function
		   
** Version : v2.3.5
** Date    : 2016.6.3
** Description: 1:Modify the return protocol version to 0x01
                2:Firmware upgrade data offset is modified to 4 bytes

** Version : v2.3.4
** Date    : 2016.5.26
** Description: 1:Optimize serial port parsing function
                2:Optimize compiler compatibility, cancel enum type definitions

** Version : v2.3.3
** Date    : 2016.5.24
** Description: 1:Modify mcu to get local time function
                2:Add wifi function test

** Version : v2.3.2
** Date    : 2016.4.23
** Description: 1:Optimize serial port data analysis
                2:Optimize the MCU firmware upgrade process
                3:Optimize the reporting process

** Version : v2.3.1
** Date    : 2016.4.15
** Description: 1:Optimize serial port data analysis

** Version : v2.3
** Date    : 2016.4.14
** Description: 1:Support MCU firmware online upgrade

** Version : v2.2
** Date    : 2016.4.11
** Description: 1:Modify the serial port data receiving mode

** Version : v2.1
** Date    : 2016.4.8
** Description: 1:Adding some compilers does not support function pointer compatibility options

** Version : v2.0
** Data    : 2016.3.29
** Description: 1:Optimize code structure
                2:Save RAM space
**
**-----------------------------------------------------------------------------

******************************************************************************/

#include "wifi.h"

#ifdef WEATHER_ENABLE
/******************************************************************************
                        Weather data parameter selection array
          **Users can customize the required parameters, comments or uncomment,
            pay attention to the changes**         
******************************************************************************/
const char weather_choose[WEATHER_CHOOSE_CNT][10] = {
    "temp",
    "humidity",
    "condition",
    "pm25",
    /*"pressure",
    "realFeel",
    "uvi",
    "tips",
    "windDir",
    "windLevel",
    "windSpeed",
    "sunRise",
    "sunSet",
    "aqi",
    "so2 ",
    "rank",
    "pm10",
    "o3",
    "no2",
    "co",*/
 };
#endif

/******************************************************************************
                            Transplant instructions:
1:The MCU must directly call the wifi_uart_service() function in mcu_api.c in the while.
2:After the normal initialization of the program is completed, 
  it is recommended not to turn off the serial port interrupt. 
  If the interrupt must be turned off, the off interrupt time must be short, 
  and the interrupt will cause the serial port packet to be lost.
3:Do not call the escalation function in the interrupt/timer interrupt
******************************************************************************/

         
/******************************************************************************
                          The first step: initialization
1:Include "wifi.h" in files that need to use wifi related files
2:Call the wifi_protocol_init() function in the mcu_api.c file in the MCU initialization
3:Fill the MCU serial single-byte send function into the uart_transmit_output 
   function in the protocol.c file, and delete #error
4:Call the uart_receive_input function in the mcu_api.c file in the MCU serial receive 
   function and pass the received byte as a parameter.
5:The wifi_uart_service() function in the mcu_api.c file is called after the MCU enters the while loop.
******************************************************************************/

/******************************************************************************
                    1:dp data point sequence type comparison table
          **This is the automatic generation of code, such as the relevant changes in
              the development platform, please re-download MCU_SDK**         
******************************************************************************/
const DOWNLOAD_CMD_S download_cmd[] =
{
  {DPID_SWITCH_1, DP_TYPE_BOOL},
  {DPID_COUNTDOWN_1, DP_TYPE_VALUE},
  {DPID_ADD_ELE, DP_TYPE_VALUE},
  {DPID_CUR_CURRENT, DP_TYPE_VALUE},
  {DPID_CUR_POWER, DP_TYPE_VALUE},
  {DPID_CUR_VOLTAGE, DP_TYPE_VALUE},
};


/******************************************************************************
                    2:Serial single-byte send function
Please fill in the MCU serial port send function into the function,
and pass the received data as a parameter to the serial port send function.

******************************************************************************/

/*****************************************************************************
Function name          : uart_transmit_output
Functional description : Send data processing
Input parameters       : value:Serial port receives byte data
Return parameter       : Null
Instructions for use   : Please fill in the MCU serial port send function into the function, 
                         and pass the received data as a parameter to the serial port send function.
*****************************************************************************/
void uart_transmit_output(unsigned char value)
{
  //#error "Please fill in the MCU serial port send function and delete the line."

  //Example:
  extern void Uart_PutChar(unsigned char value);
  Uart_PutChar(value);	                                //Serial port send function

}
/******************************************************************************
                        Step 2: Implement a specific user function
1:APP send data processing
2:Data upload processing
******************************************************************************/

/******************************************************************************
                        1:All data upload processing
The current function handles all data upload (including deliverable/reportable and report only)

  Users need to implement according to the actual situation:
  1:Need to implement the reportable/reportable data point report
  2:Need to report only reported data points
This function must be called internally by the MCU.
Users can also call this function to achieve all data upload.

******************************************************************************/

//Automated generation of data reporting functions

/*****************************************************************************
Function name          : all_data_update
Functional description : All dp point information of the system is uploaded to realize APP and muc data synchronization.
Input parameters       : Null
Return parameter       : Null
Instructions for use   : This function SDK needs to be called internally;
           The MCU must implement the data upload function in the function; including only reporting and reportable hair style data.
*****************************************************************************/
extern volatile unsigned char State_switch_1;
extern volatile unsigned char State_switch_2;
extern volatile unsigned char State_switch_3;
extern volatile unsigned char State_switch_4;
extern unsigned long State_countdown_1;
extern unsigned long State_countdown_2;
extern unsigned long State_countdown_3;
extern unsigned long State_countdown_4;
extern unsigned long State_thong_so1; // thong so dong dien
extern unsigned long State_thong_so2; // thong so cong suat
extern unsigned long State_thong_so3; // kha nang thong so tong cong suat
extern unsigned long State_thong_so4; // thong so dien ap
void all_data_update(void)
{
//  #error "Please process the reportable data and report only the data. After the processing is completed, delete the line."
  
  //This code is automatically generated by the platform. 
  //Please modify each reportable and reportable function according to the actual data.
  mcu_dp_bool_update(DPID_SWITCH_1,State_switch_1); //BOOL型数据上报;
  mcu_dp_value_update(DPID_COUNTDOWN_1,State_countdown_1); //VALUE型数据上报;
  mcu_dp_value_update(DPID_ADD_ELE,State_thong_so1); //VALUE型数据上报;
  mcu_dp_value_update(DPID_CUR_CURRENT,State_thong_so2); //VALUE型数据上报;
  mcu_dp_value_update(DPID_CUR_POWER,State_thong_so3); //VALUE型数据上报;
  mcu_dp_value_update(DPID_CUR_VOLTAGE,State_thong_so4); //VALUE型数据上报;

 
}


/******************************************************************************
                                WARNING!!!    
                            2:All data upload processing
Automate code template functions, please implement data processing by yourself
******************************************************************************/


/*****************************************************************************
Function name : dp_download_switch_1_handle
Function description : on DPID_SWITCH_1 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_switch_1_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isBOOL
  unsigned char ret;
  //0:关/1:开
  unsigned char switch_1;
  
  switch_1 = mcu_get_dp_download_bool(value,length);
	State_switch_1 = switch_1;
  if(switch_1 == 0)
  {
    //开关关
  }
  else
  {
    //开关开
  }
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_bool_update(DPID_SWITCH_1,switch_1);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_countdown_1_handle
Function description : on DPID_COUNTDOWN_1 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_countdown_1_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isVALUE
  unsigned char ret;
  unsigned long countdown_1;
  
  countdown_1 = mcu_get_dp_download_value(value,length);
	State_countdown_1 = countdown_1;
  /*
  //VALUE类型数据处理
  
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_value_update(DPID_COUNTDOWN_1,countdown_1);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}


/******************************************************************************
                                WARNING!!!                     
This code is called internally by the SDK. 
Please implement the internal data of the function according to the actual dp data.
******************************************************************************/
#ifdef SUPPORT_MCU_RTC_CHECK
/*****************************************************************************
Function name          : mcu_write_rtctime
Functional description : MCU proofreads local RTC clock
Input parameters       : Null
Return parameter       : Null
Instructions for use   : MCU needs to implement this function by itself
*****************************************************************************/
void mcu_write_rtctime(unsigned char time[])
{
  #error "Please complete the RTC clock write code yourself and delete the line."
  /*
     Time[0] is the time success flag, 0 is a failure, and 1 is a success.
     Time[1] is the year and 0x00 is the year 2000.
     Time[2] is the month, starting from 1 to ending at 12
     Time[3] is the date, starting from 1 to 31
     Time[4] is the clock, starting from 0 to ending at 23
     Time[5] is minutes, starting from 0 to ending at 59
     Time[6] is seconds, starting from 0 to ending at 59
     Time[7] is the week, starting from 1 to 7 and 1 is Monday.

 */
  if(time[0] == 1)
  {
    //Correctly receive the local clock data returned by the wifi module
	 
  }
  else
  {
  	//Error getting local clock data, it may be that the current wifi module is not connected
  }
}
#endif

#ifdef WIFI_TEST_ENABLE
/*****************************************************************************
Function name          : wifi_test_result
Functional description : Wifi function test feedback
Input parameters       : Result:wifi function test » fruit; 0: failure / 1: success
           rssi: test success indicates wifi signal strength / test failure indicates error type
Return parameter       : Null
Instructions for use   : MCU needs to implement this function by itself
*****************************************************************************/
void wifi_test_result(unsigned char result,unsigned char rssi)
{
  //#error "Please implement the wifi function test success/failure code by yourself. Please delete the line after completion."
  if(result == 0)
  {
    //Test failed
    if(rssi == 0x00)
    {
      //Can't scan to the router named tuya_mdev_test, please check
    }
    else if(rssi == 0x01)
    {
      //Module not authorized
    }
  }
  else
  {
    //Test success
    //rssiis the signal strength (0-100, 0 signal is the worst, 100 signal is the strongest)
  }
  
}
#endif

#ifdef SUPPORT_MCU_FIRM_UPDATE
/*****************************************************************************
Function name          : mcu_firm_update_handle
Functional description : MCU enters firmware upgrade mode
Input parameters       : value:Firmware buffer
                         position:The current data packet is in the firmware location
                         length:Current firmware package length (when the firmware package length is 0,
                                it indicates that the firmware package is sent)
Return parameter       : Null
Instructions for use   : MCU needs to implement this function by itself
*****************************************************************************/
unsigned char mcu_firm_update_handle(const unsigned char value[],unsigned long position,unsigned short length)
{
  #error "Please complete the MCU firmware upgrade code yourself. Please delete the line after completion."
  if(length == 0)
  {
    //Firmware data transmission completed
    
  }
  else
  {
    //Firmware data processing
  }
  
  return SUCCESS;
}
#endif
/******************************************************************************
                                WARNING!!!                     
The following function users do not modify!!
******************************************************************************/

/*****************************************************************************
Function name          : dp_download_handle
Functional description : dp delivery processing function
Input parameters       : dpid:DP number
                         value:dp data buffer address
                         length:dp data length
Return parameter       : successful return: SUCCESS / failed return: ERRO
Instructions for use   : The function user cannot modify
*****************************************************************************/
unsigned char dp_download_handle(unsigned char dpid,const unsigned char value[], unsigned short length)
{
  /*********************************
  Current function processing can issue/report data calls                    
  Need to implement the data processing in the specific function
  The result of the processing needs to be fed back to the APP, otherwise the APP will consider the delivery failure.
  ***********************************/
  unsigned char ret;
  switch(dpid)
  {
    case DPID_SWITCH_1:
      //开关processing function
      ret = dp_download_switch_1_handle(value,length);
      break;
    case DPID_COUNTDOWN_1:
      //开关1倒计时processing function
      ret = dp_download_countdown_1_handle(value,length);
      break;

  default:
    break;
  }
  return ret;
}
/*****************************************************************************
Function name          : get_download_cmd_total
Functional description : Get the sum of all dp commands
Input parameters       : Null
Return parameter       : Sent the sum of the commands
Instructions for use   : The function user cannot modify
*****************************************************************************/
unsigned char get_download_cmd_total(void)
{
  return(sizeof(download_cmd) / sizeof(download_cmd[0]));
}

#ifdef WEATHER_ENABLE

/*****************************************************************************
Function name          : weather_open_return
Functional description : Turn on the weather function to return the user self-processing function
Input parameters       : 1:res:turn on the weather function to return the result, 1: success; 0: failure

Return parameter       : Null
*****************************************************************************/
void weather_open_return_handle(unsigned char res, unsigned char err)
{
  #error "Please complete the M open weather function to return the data processing code. Please delete the line after completion."
  unsigned char err_num = 0;
  
  if(res == 1)
  {
    //Open the weather and return successfully
  }
  else if(res == 0)
  {
    //Open weather return failed
    err_num = err;//Get the error code
  }
}

/*****************************************************************************
Function name          : weather_data_user_handle
Functional description : Weather data user self-processing function
Input parameters       : name:parameter name
                         type:parameter type，0：int ；1：string 
                         data:the address of the parameter value
Return parameter       : Null
*****************************************************************************/
void weather_data_user_handle(char *name, unsigned char type, char *data)
{
  #error "Here is just an example. Please correct the weather data processing code yourself. Please delete the line after you finish."
  int value_int;
  char value_string[50];//Since there are many parameters, the default is 50. 
                        //You can reduce this value appropriately based on the defined parameters.
  
  my_memset(value_string, '/0', 50);
  
  //First get the data type
  if(type == 0)//The parameter is INT type
  {
    value_int = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];Here is just an example. Please correct the weather data processing code yourself. Please delete the line after you finish.
  }
  else if(type == 1)
  {
    my_strcpy(value_string, data);
  }
  
  //Note that the parameter value is obtained according to the selected parameter type! ! !
  if(my_strcmp(name, "temp") == 0)
  {
    //printf("temp value is:%d", value_int);            //int type
  }
  else if(my_strcmp(name, "humidity") == 0)
  {
    //printf("humidity value is:%d", value_int);        //int type
  }
  else if(my_strcmp(name, "pm25") == 0)
  {
    //printf("pm25 value is:%d", value_int);            //int type
  }
  else if(my_strcmp(name, "condition") == 0)
  {
    //printf("condition value is:%s", value_string);    //string type
  }
}
#endif

#ifdef WIFI_STREAM_ENABLE
/*****************************************************************************
Function name          : stream_file_trans
Functional description : Stream service file sending
Input parameters       : id:ID number
                         buffer:Send the address of the package
                         buf_len:Send packet length
Return parameter       : Null
*****************************************************************************/
unsigned char stream_file_trans(unsigned int id, unsigned char *buffer, unsigned long buf_len)
{
  #error "Here is just an example, please improve the stream service processing code yourself, please delete the line after completion"
  unsigned short length = 0;
  unsigned long map_offset = 0;
  unsigned int pack_num = 0;
  unsigned int rest_length = 0;

  if(stop_update_flag == ENABLE)
    return SUCCESS;

  pack_num = buf_len / STREM_PACK_LEN;
  rest_length = buf_len - pack_num * STREM_PACK_LEN;
  if (rest_length > 0)
  {
    pack_num++;
  }

  int this_len = STREM_PACK_LEN;
  for (int cnt = 0; cnt < pack_num; cnt++)
  {
    if (cnt == pack_num - 1 && rest_length > 0)
    {
      this_len = rest_length;
    }
    else
    {
      this_len = STREM_PACK_LEN;
    }

    stream_trans(id, map_offset, buffer + map_offset, this_len);

    //while(stream_status == 0xff);//Received back
    
    if(stream_status != 0)
    {
      return ERROR;
    }
  }
  
  return SUCCESS;
}

#endif
