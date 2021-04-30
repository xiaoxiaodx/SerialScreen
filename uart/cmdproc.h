/******************************************************************************
 * 
 * 				Copyright (c), 2021,
 * 
 * *****************************************************************************
 * Filename:cmdproc.h
 * 
 *  File Description: 
 * -----------------------
 * 
 * Revision: 
 * Author: fan
 * DataTime: 04-04-2021
 * Modification History:
 * 	--------------------
 *****************************************************************************/
#ifndef _CMDPROC_H_
#define _CMDPROC_H_
/**---------------------------------------------------------------------------*
**                         Compiler Flag                                     *
**---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern   "C"
{
#endif
/******************************************************************************
*	Include Files
 *****************************************************************************/
#include <stdint.h>
/******************************************************************************
*	Macros
******************************************************************************/


/******************************************************************************
*	Types
******************************************************************************/
//enum

//Struct
typedef struct  _tagpageData_S{
    uint8_t id;
}pageData_S;

typedef struct  _tagcleanData_S{
    uint16_t color;
}cleanData_S;

typedef struct  _tagpointData_S{
    uint32_t x;
    uint32_t y;
    uint16_t color;
}pointData_S;

typedef struct  _taglineData_S{
    uint32_t x1;
    uint32_t y1;
    uint32_t x2;
    uint32_t y2;
    uint16_t color;
}lineData_S;

typedef struct  _tagrectData_S{
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t hight;
    uint16_t color;
}rectData_S,frectData_S;

typedef struct  _tagpieData_S{
    uint32_t x;
    uint32_t y;
    uint32_t radius;
    uint32_t a0;
    uint32_t a1;
    uint16_t color;
}pieData_S;

typedef struct  _tagarcData_S{
    uint32_t x;
    uint32_t y;
    uint32_t radius;
    uint32_t a0;
    uint32_t a1;
    uint32_t pensize;
    uint16_t color;
}arcData_S;

typedef struct  _tagcirData_S{
    uint32_t x;
    uint32_t y;
    uint32_t radius;
    uint16_t color;
}cirData_S,fcirData_S;


typedef struct  _tagpicData_S{
    uint32_t x;
    uint32_t y;
    uint16_t id;
}picData_S;
typedef struct  _tagpiccData_S{
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t hight;
    uint16_t id;
}piccData_S;

typedef struct  _tagstrData_S{
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t hight;
    uint16_t id;
    uint32_t    fontindex;

    uint32_t alignment;
    uint32_t Usebackcolor;
    uint32_t fcolor;
    uint32_t bcolor;

    char  str[256];
}strData_S;

typedef struct  _tagrefData_S{
    char  name[256];
}refData_S;
typedef struct  _tagclickData_S{
    char  name[256];
    uint32_t event;
}clickData_S;

typedef struct  _tagecohData_S{
//    char  name[256];
    uint32_t  name;
}ecohData_S;

typedef struct  _tagecohnData_S{
    uint32_t  name;
    uint32_t n;
}ecohnData_S;


typedef struct  _tagedisplayData_S{
    char  name[256];
    uint32_t state;
}hideData_S,showData_S;

typedef struct  _tagreData_S{
    uint32_t  en;
}reData_S;


typedef struct  _tagaddnData_S{
    char name[32];
    uint32_t channel;
    uint32_t num;
    uint8_t *u8data;
}addnData_S;

typedef struct  _tagaddData_S{
    char name[32];
    uint32_t channel;
    uint32_t num;
}addData_S;

typedef struct  _tagdelData_S{
    char name[32];
    uint32_t channel;
}delData_S;
typedef struct  _tagctlData_S{
    uint32_t x;
}calData_S,resetData_S;

typedef struct  _tagbaudData_S{
    uint32_t baud;
}baudData_S ;
typedef struct  _tagdimData_S{
    uint32_t val;
}dimData_S ;
typedef struct  _tagrandData_S{
    uint32_t val;
}randData_S ;

typedef struct  _tagslenData_S{
    char name[32];
    uint32_t val;
}slenData_S;
typedef struct  _tagscopyData_S{
    char dst[256];
    char src[256];
}scopyData_S;
typedef struct  _tagsncopyData_S{
    char dst[256];
    char src[256];
    uint32_t num;
}sncopyData_S;

typedef struct  _tagsleepData_S{
    uint32_t state;
}sleepData_S ;
/******************************************************************************
*	Constants
******************************************************************************/


/******************************************************************************
*	Variables
******************************************************************************/
//local variables

//extern variables

/******************************************************************************
*	Functions Prototypes
******************************************************************************/
//local Functions Prototypes


//extern Functions Prototypes
// 串口 readbuf 操作函数, 操作后,会移动读写指针位置.
int getCmd(uint8_t *str,int num,uint8_t *type,uint8_t *cmdstr,uint32_t *Pcmdsize);
int getRawData(uint8_t *str,int num,uint8_t *cmdstr);

// 命令解析操作 ,

// 获取命令id 
int cmdGet(char *str, uint32_t *cmdid);
int cmdproc(char *str);

// 获取命令参数;
//int cmdproc(char *str, uint32_t cmdid,void *data);


/******************************************************************************
*	Functions
******************************************************************************/


/**---------------------------------------------------------------------------*
**                         Compiler Flag                                     *
**---------------------------------------------------------------------------*/
#ifdef __cplusplus
}

#endif

#endif	//_CMDPROC_H_

