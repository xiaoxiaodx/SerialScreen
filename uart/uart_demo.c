/******************************************************************************
 * 
 * 				Copyright (c), 2020,
 * 
 * *****************************************************************************
 * Filename:uart_demo.c
 * 
 *  File Description: 
 * -----------------------
 * 
 * Revision: 
 * Author: fan
 * DataTime: 07-12-2020
 * Modification History:
 * 	--------------------
 *****************************************************************************/
#ifndef _UART_DEMO_C_
#define _UART_DEMO_C_
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
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdlib.h>
#include "cmdproc.h"

/******************************************************************************
*	Macros
******************************************************************************/
#define DEV_TTY  "/dev/ttyS4"


/******************************************************************************
*	Types
******************************************************************************/
//enum

//Struct

/******************************************************************************
*	Constants
******************************************************************************/
typedef struct _ImageInfo_T{
	int index;
	int addr;
	int width;
	int height;
	char *data;
}ImageInfo_T;

typedef struct _ImageParam_T{
	int imageNum;
	ImageInfo_T *image;
}ImageParam_T;

typedef struct _FontInfo_T{
	int index;
	int addr;
	int width;
	int height;
	char *data;
}FontInfo_T;

typedef struct _FontParam_T{
	int fontNum;
	FontInfo_T *font;
}FontParam_T;

typedef struct _ButtonParam_T{
	int global; //(1字节)   全局1，私有0 
	char name[6];//(6字节) 控件名字
	int pageId; //(1字节)
	int id; //控件ID（1字节）
	int x;
	int y;
	int width;
	int height;
	int level; //控件所在层（1字节）：1or2  1在下 2在上
	int distype; //按钮DisType（1字节）：（单色0 or 切图1 or 图片2) 
	int fpic;
	int bpic;
	int txtlen;
	char *txt;
	int fontIndex;
	int txtColor;
	int swType;
	int downlen;
	char *downcmd;
	int uplen;
	char *upcmd;
}ButtonParam_T;

typedef enum _ENUM_ALIGNMODE{
	TopLeft = 0,
    TopCenter = 1,
    TopRight = 2,
    MiddleLeft = 8,
    MiddleCenter = 9,
    MiddleRight = 10,
    BottomLeft = 4,
    BottomCenter = 5,
    BottomRight = 6,
}ENUM_ALIGNMODE;

typedef struct _LabelParam_T{
	int global;
	char name[6];
	int pageId;
	int id;
	int x;
	int y;
	int width;
	int height;
	int level; //控件所在层（1字节）：1or2  1在下 2在上
	int distype; //按钮DisType（1字节）：（单色0 or 切图1 or 图片2) 
	int txtlen;
	char *txt;
	int fontIndex; //（1字节）
	int fpicorcol; //（2字节）
	int bpicorcol; //（2字节）
	int txtSpace; //字间距 1字节
	ENUM_ALIGNMODE align;//对齐方式 1字节
	int downlen; //（2字节）
	char *downcmd;
	int uplen;//（2字节）
	char *upcmd;
}LabelParam_T;

typedef struct _PgbarParam_T{
	int global;
	char name[6];
	int pageId;
	int id;
	int x;
	int y;
	int width;
	int height;
	int level; //控件所在层（1字节）：1or2  1在下 2在上
	int distype; //按钮DisType（1字节）：（单色0 or 切图1 or 图片2) 
	int hov; //（1字节）：0垂直  ，1水平
	int fpic;  //（2字节）前景色/图索引
	int bpic;  //（2字节）背景色/背景图索引
	int percent; //（1字节）进度值
	int downlen; //（2字节）
	char *downcmd;
	int uplen;//（2字节）
	char *upcmd;
}PgbarParam_T;

typedef struct _PanelParam_T{
	int global;
	char name[6];
	int pageId;
	int id;
	int x;
	int y;
	int width;
	int height;
	int level; //控件所在层（1字节）：1or2  1在下 2在上
	int distype; //按钮DisType（1字节）：（单色0 or 切图1 or 图片2) 
	int fpicorcol; //（2字节）
	int bpicorcol; //（2字节）
	int linewidth; //（1字节）线宽度
	int angle;//（2字节）角度
	int downlen; //（2字节）
	char *downcmd;
	int uplen;//（2字节）
	char *upcmd;
}PanelParam_T;

typedef struct _SlideParam_T{
	int global;
	char name[6];
	int pageId;
	int id;
	int x;
	int y;
	int width;
	int height;
	int level; //控件所在层（1字节）：1or2  1在下 2在上
	int distype; //按钮DisType（1字节）：（单色0 or 切图1 or 图片2) 
	int hov; //（1字节）：0垂直  ，1水平
	int fpicorcol; //（2字节）
	int bpicorcol; //（2字节）
	int min; //（2字节） 最小值
	int max; //（2字节）最大值
	int value; //（2字节）当前值
	int wid; //（1字节）滑块宽度
	int hgt; //（1字节）滑块高度
	int downlen; //（2字节）
	char *downcmd;
	int uplen;//（2字节）
	char *upcmd;
	int mvlen;//（2字节）
	char *mvcmd;
}SlideParam_T;

typedef struct _RolllabelParam_T{
	int global;
	char name[6];
	int pageId;
	int id;
	int x;
	int y;
	int width;
	int height;
	int level; //控件所在层（1字节）：1or2  1在下 2在上
	int distype; //按钮DisType（1字节）：（单色0 or 切图1 or 图片2) 
	int dir; //（1字节）滚动方向
	int fpicorcol; //（2字节）
	int bpicorcol; //（2字节）
	int step; //（1字节） 滚动距离
	int period; //（2字节） 间距间隔
	int fontIndex; //（1字节）字体索引
	int enable; //（1字节）滚动开关（0停止，1开启）
	int txtSpace; //字间距 1字节
	ENUM_ALIGNMODE align;//对齐方式 1字节
	int txtlen;
	char *txt;
	int downlen; //（2字节）
	char *downcmd;
	int uplen;//（2字节）
	char *upcmd;
}RolllabelParam_T;

//曲线控件
typedef struct _GraphParam_T{
	int global;
	char name[6];
	int pageId;
	int id;
	int x;
	int y;
	int width;
	int height;
	int level; //控件所在层（1字节）：1or2  1在下 2在上
	int distype; //按钮DisType（1字节）：（单色0 or 切图1 or 图片2) 
	int bpicorcol; //（2字节）
	int lor; //（1字节） 
	int gridcolor; //（2字节） 网格颜色
	int winterval; //（1字节）网格宽
	int hinterval; //（1字节）网格高
	int channel; //（1字节）通道数量
	int channelcolor0; //（2）曲线1颜色
	int channelcolor1; //（2）曲线2颜色
	int channelcolor2; //（2）曲线3颜色
	int channelcolor3; //（2）曲线4颜色
	int downlen; //（2字节）
	char *downcmd;
	int uplen;//（2字节）
	char *upcmd;
}GraphParam_T;

typedef struct _RadioParam_T{
	int global;
	char name[6];
	int pageId;
	int id;
	int x;
	int y;
	int width;
	int height;
	int level; //控件所在层（1字节）：1or2  1在下 2在上
	int distype; //按钮DisType（1字节）：（单色0 or 切图1 or 图片2) 
	int fpicorcol; //（2字节）
	int bpicorcol; //（2字节）
	int horv; //（1）显示方向
	int focusindex; //（1字节）选中索引
	int numofitem; //（1字节）选项数量
	int distance; //（1字节）控件间隔
	int downlen; //（2字节）
	char *downcmd;
	int uplen;//（2字节）
	char *upcmd;
}RadioParam_T;

typedef struct _CheckBoxParam_T{
	int global;
	char name[6];
	int pageId;
	int id;
	int x;
	int y;
	int width;
	int height;
	int level; //控件所在层（1字节）：1or2  1在下 2在上
	int distype; //按钮DisType（1字节）：（单色0 or 切图1 or 图片2) 
	int fpicorcol; //（2字节）
	int bpicorcol; //（2字节）
	int state; //（1字节） 选中状态	
	int downlen; //（2字节）
	char *downcmd;
	int uplen;//（2字节）
	char *upcmd;
}CheckBoxParam_T;

typedef struct _HotSpotParam_T{
	int global;
	char name[6];
	int pageId;
	int id;
	int x;
	int y;
	int width;
	int height;
	int level; //控件所在层（1字节）：1or2  1在下 2在上
	int downlen; //（2字节）
	char *downcmd;
	int uplen;//（2字节）
	char *upcmd;
}HotSpotParam_T;

typedef struct _TimerParam_T{
	int global;
	char name[6];
	int pageId;	
	int id;
	int level; //控件所在层（1字节）：1or2  1在下 2在上
	int period; //（2字节）定时器周期
	int enable; //（1字节）定时器开头
	int eventlen; //（2字节+len）定时器事件长度
	char *event; //事件内容
}TimerParam_T;


typedef struct _VariableParam_T{
	int global;
	char name[6];
	int pageId;	
	int id;
	int level; //控件所在层（1字节）：1or2  1在下 2在上
	int vartype; //（1字节）变量类型
	int val; //（4字节）
	int len; //（2字节）
	char *text;
}VariableParam_T;

typedef struct _PicParam_T{
	int global;
	char name[6];
	int pageId;	
	int id;
	int x;
	int y;
	int width;
	int height;
	int level; //控件所在层（1字节）：1or2  1在下 2在上
	int picIndex; //（2字节）   图片索引
	int downlen; //（2字节）
	char *downcmd;
	int uplen;//（2字节）
	char *upcmd;
}PicParam_T;

typedef struct _CPicParam_T{
	int global;
	char name[6];
	int pageId;	
	int id;
	int x;
	int y;
	int width;
	int height;
	int level; //控件所在层（1字节）：1or2  1在下 2在上
	int picIndex; //（2字节）   图片索引
	int downlen; //（2字节）
	char *downcmd;
	int uplen;//（2字节）
	char *upcmd;
}CPicParam_T;

typedef struct _CNumParam_T{
	int global;
	char name[6];
	int pageId;	
	int id;
	int x;
	int y;
	int width;
	int height;
	int level; //控件所在层（1字节）：1or2  1在下 2在上
	int distype; //按钮DisType（1字节）：（单色0 or 切图1 or 图片2) 
	int fpicorcol; //（2字节）
	int bpicorcol; //（2字节）
	int fontIndex; //（1字节）字体索引
	int text; //（4字节）显示的数字
	ENUM_ALIGNMODE align;//对齐方式 1字节
	int downlen; //（2字节）
	char *downcmd;
	int uplen;//（2字节）
	char *upcmd;
}CNumParam_T;

typedef struct _PageInfo_T{
	int index;
	int addr;
	int global;
	int picornot;
	int bcOrpi; //BackColorOrPicIndex
	char objname[9];
	int buttonNum;
	ButtonParam_T *buttonInfo;
	int labelNum;
	LabelParam_T *labelInfo;
	int pgbarNum;
	PgbarParam_T *pgbarInfo;
	int panelNum;
	PanelParam_T *panelInfo;
	int slideNum;
	SlideParam_T *slideInfo;
	int rolllabelNum;
	RolllabelParam_T *rolllableInfo;
	int graphNum;
	GraphParam_T *graphInfo;
	int radioNum;
	RadioParam_T *radioInfo;
	int checkboxNum;
	CheckBoxParam_T *checkboxInfo;
	int hotspotNum;
	HotSpotParam_T *hotspotInfo;
	int timerNum;
	TimerParam_T *timerInfo;
	int variableNum;
	VariableParam_T *variableInfo;
	int picNum;
	PicParam_T *picInfo;
	int cpicNum;
	CPicParam_T *cpicInfo;
	int numNum;
	CNumParam_T *numInfo;
}PageInfo_T;

typedef struct _PageParam_T{
	int pageNum;
	PageInfo_T *page;
}PageParam_T;

/******************************************************************************
*	Variables
******************************************************************************/
//local variables
static  int tty_fd = -1 ;

//extern variables

/******************************************************************************
*	Functions Prototypes
******************************************************************************/
//local Functions Prototypes


//extern Functions Prototypes
int Bytes2String(unsigned char *pSrc, int nSrcLen, unsigned char *pDst, int nDstMaxLen);

/******************************************************************************
*	Functions
******************************************************************************/
static int tty_send(void *buf ,int len)
{
    int     s32Ret = -1 ;

    s32Ret = write(tty_fd, buf,len) ;
    if(s32Ret < 0)
    {
        printf("Write() error:%s\n",strerror(errno)) ;
    }
    return  s32Ret ;
}

int btos(char *buf)
{
	int value = 0;
	
	value |= 0xFF000000 & (buf[3] << 24);
	value |= 0x00FF0000 & (buf[2] << 16);
	value |= 0x0000FF00 & (buf[1] << 8);
	value |= 0x000000FF & buf[0];

	return value;
}

int ButtonAnalysis(int fd,int num,ButtonParam_T **info)
{
	int j = 0;
	char buf[128] = {0};		
	if(num > 0)
	{
		*info = (ButtonParam_T *)malloc(sizeof(ButtonParam_T) * num);
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,28);
			info[j]->global = buf[0];
			memcpy(info[j]->name,buf+1,6);
			info[j]->pageId = buf[7];
			info[j]->id = buf[8];
			info[j]->x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j]->y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j]->width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j]->height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j]->level = buf[17];
			info[j]->distype = buf[18];
			if(info[j]->distype != 0)
			{
				info[j]->fpic = (0x0000FF00 & (buf[20] << 8)) | (0x000000FF & buf[19]);
				info[j]->bpic = (0x0000FF00 & (buf[22] << 8)) | (0x000000FF & buf[21]);
			}
			else
			{
				info[j]->fpic = (0x0000FF00 & (buf[24] << 8)) | (0x000000FF & buf[23]);
				info[j]->bpic = (0x0000FF00 & (buf[26] << 8)) | (0x000000FF & buf[25]);
			}
			
			info[j]->txtlen = buf[27];
			if(info[j]->txtlen > 0)
			{
				info[j]->txt = (char *)malloc(sizeof(char) * info[j]->txtlen);
				memset(info[j]->txt,0,info[j]->txtlen);
				read(fd,info[j]->txt,info[j]->txtlen);
			}
			
			memset(buf,0,sizeof(buf));
			read(fd,buf,6);
			info[j]->fontIndex = buf[0];
			info[j]->txtColor = (0x0000FF00 & (buf[2] << 8)) | (0x000000FF & buf[1]);
			info[j]->swType = buf[3];
			info[j]->downlen = (0x0000FF00 & (buf[5] << 8)) | (0x000000FF & buf[4]);
			if(info[j]->downlen > 0)
			{
				info[j]->downcmd = (char *)malloc(sizeof(char) * info[j]->downlen);
				memset(info[j]->downcmd,0,info[j]->downlen);
				read(fd,info[j]->downcmd,info[j]->downlen);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			
			info[j]->uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j]->uplen > 0)
			{
				info[j]->upcmd = (char *)malloc(sizeof(char) * info[j]->uplen);
				memset(info[j]->upcmd,0,info[j]->uplen);
				read(fd,info[j]->upcmd,info[j]->uplen);
			}
		}
	}

	return 1;
}

int LabelAnalysis(int fd,int num,LabelParam_T **labelInfo)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		*labelInfo = (LabelParam_T *)malloc(sizeof(LabelParam_T) * num);
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,21);
			labelInfo[j]->global = buf[0];
			memcpy(labelInfo[j]->name,buf+1,6);
			labelInfo[j]->pageId = buf[7];
			labelInfo[j]->id = buf[8];	
			labelInfo[j]->x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			labelInfo[j]->y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			labelInfo[j]->width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			labelInfo[j]->height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			labelInfo[j]->level = buf[17];
			labelInfo[j]->distype = buf[18];
			labelInfo[j]->txtlen = (0x0000FF00 & (buf[20] << 8)) | (0x000000FF & buf[19]);
			if(labelInfo[j]->txtlen > 0)
			{
				labelInfo[j]->txt = (char *)malloc(sizeof(char) * labelInfo[j]->txtlen);
				memset(labelInfo[j]->txt,0,labelInfo[j]->txtlen);
				read(fd,labelInfo[j]->txt,labelInfo[j]->txtlen);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,11);	
			labelInfo[j]->fontIndex = buf[0];
			labelInfo[j]->fpicorcol = (0x0000FF00 & (buf[2] << 8)) | (0x000000FF & buf[1]);
			if(labelInfo[j]->distype != 0)
			{
				labelInfo[j]->bpicorcol = (0x0000FF00 & (buf[4] << 8)) | (0x000000FF & buf[3]);
			}
			else
			{
				labelInfo[j]->bpicorcol = (0x0000FF00 & (buf[6] << 8)) | (0x000000FF & buf[5]);
			}
			labelInfo[j]->txtSpace = buf[7];
			labelInfo[j]->align = buf[8];
			labelInfo[j]->downlen = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			if(labelInfo[j]->downlen > 0)
			{
				labelInfo[j]->downcmd = (char *)malloc(sizeof(char) * labelInfo[j]->downlen);
				memset(labelInfo[j]->downcmd,0,labelInfo[j]->downlen);
				read(fd,labelInfo[j]->downcmd,labelInfo[j]->downlen);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			labelInfo[j]->uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(labelInfo[j]->uplen > 0)
			{
				labelInfo[j]->upcmd = (char *)malloc(sizeof(char) * labelInfo[j]->uplen);
				memset(labelInfo[j]->upcmd,0,labelInfo[j]->uplen);
				read(fd,labelInfo[j]->upcmd,labelInfo[j]->uplen);
			}
		}
	}

	return 1;
}

int ProgressBarAnalysis(int fd,int num,PgbarParam_T **info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		*info = (PgbarParam_T *)malloc(sizeof(PgbarParam_T) * num);
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,31);
			info[j]->global = buf[0];
			memcpy(info[j]->name,buf+1,6);
			info[j]->pageId = buf[7];
			info[j]->id = buf[8];
			info[j]->x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j]->y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j]->width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j]->height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j]->level = buf[17];
			info[j]->distype = buf[18];
			info[j]->hov = buf[19];
			if(info[j]->distype != 0)
			{
				info[j]->fpic = (0x0000FF00 & (buf[21] << 8)) | (0x000000FF & buf[20]);
				info[j]->bpic = (0x0000FF00 & (buf[23] << 8)) | (0x000000FF & buf[22]);
			}
			else
			{
				info[j]->fpic = (0x0000FF00 & (buf[25] << 8)) | (0x000000FF & buf[24]);
				info[j]->bpic = (0x0000FF00 & (buf[27] << 8)) | (0x000000FF & buf[26]);
			}
			
			info[j]->percent = buf[28];
			info[j]->downlen = (0x0000FF00 & (buf[30] << 8)) | (0x000000FF & buf[29]);
			if(info[j]->downlen > 0)
			{
				info[j]->downcmd = (char *)malloc(sizeof(char) * info[j]->downlen);
				memset(info[j]->downcmd,0,info[j]->downlen);
				read(fd,info[j]->downcmd,info[j]->downlen);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j]->uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j]->uplen > 0)
			{
				info[j]->upcmd = (char *)malloc(sizeof(char) * info[j]->uplen);
				memset(info[j]->upcmd,0,info[j]->uplen);
				read(fd,info[j]->upcmd,info[j]->uplen);
			}
		}
	}

	return 1;
}

int PanelAnalysis(int fd,int num,PanelParam_T **info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		*info = (PanelParam_T *)malloc(sizeof(PanelParam_T) * num);
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,30);
			info[j]->global = buf[0];
			memcpy(info[j]->name,buf+1,6);
			info[j]->pageId = buf[7];
			info[j]->id = buf[8];
			info[j]->x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j]->y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j]->width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j]->height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j]->level = buf[17];
			info[j]->distype = buf[18];
			info[j]->fpicorcol = (0x0000FF00 & (buf[20] << 8)) | (0x000000FF & buf[19]);
			if(info[j]->distype != 0)
			{
				info[j]->bpicorcol = (0x0000FF00 & (buf[24] << 8)) | (0x000000FF & buf[23]);
			}
			else
			{
				info[j]->bpicorcol = (0x0000FF00 & (buf[22] << 8)) | (0x000000FF & buf[21]);
			}
			
			info[j]->linewidth = buf[25];
			info[j]->angle = (0x0000FF00 & (buf[27] << 8)) | (0x000000FF & buf[26]);			
			info[j]->downlen = (0x0000FF00 & (buf[29] << 8)) | (0x000000FF & buf[28]);
			if(info[j]->downlen > 0)
			{
				info[j]->downcmd = (char *)malloc(sizeof(char) * info[j]->downlen);
				memset(info[j]->downcmd,0,info[j]->downlen);
				read(fd,info[j]->downcmd,info[j]->downlen);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j]->uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j]->uplen > 0)
			{
				info[j]->upcmd = (char *)malloc(sizeof(char) * info[j]->uplen);
				memset(info[j]->upcmd,0,info[j]->uplen);
				read(fd,info[j]->upcmd,info[j]->uplen);
			}
		}
	}

	return 1;
}

int SliderAnalysis(int fd,int num,SlideParam_T **info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		*info = (SlideParam_T *)malloc(sizeof(SlideParam_T) * num);
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,38);
			info[j]->global = buf[0];
			memcpy(info[j]->name,buf+1,6);
			info[j]->pageId = buf[7];
			info[j]->id = buf[8];
			info[j]->x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j]->y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j]->width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j]->height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j]->level = buf[17];
			info[j]->hov = buf[18];
			info[j]->distype = buf[19];
			if(info[j]->distype != 0)
			{
				info[j]->fpicorcol = (0x0000FF00 & (buf[25] << 8)) | (0x000000FF & buf[24]);
				info[j]->bpicorcol = (0x0000FF00 & (buf[27] << 8)) | (0x000000FF & buf[26]);
			}
			else
			{
				info[j]->fpicorcol = (0x0000FF00 & (buf[21] << 8)) | (0x000000FF & buf[20]);
				info[j]->bpicorcol = (0x0000FF00 & (buf[23] << 8)) | (0x000000FF & buf[22]);
			}
			
			info[j]->min = (0x0000FF00 & (buf[29] << 8)) | (0x000000FF & buf[28]);
			info[j]->max = (0x0000FF00 & (buf[31] << 8)) | (0x000000FF & buf[30]);			
			info[j]->value = (0x0000FF00 & (buf[33] << 8)) | (0x000000FF & buf[32]);
			info[j]->wid = buf[34];
			info[j]->hgt = buf[35];
			info[j]->downlen = (0x0000FF00 & (buf[37] << 8)) | (0x000000FF & buf[36]);
			if(info[j]->downlen > 0)
			{
				info[j]->downcmd = (char *)malloc(sizeof(char) * info[j]->downlen);
				memset(info[j]->downcmd,0,info[j]->downlen);
				read(fd,info[j]->downcmd,info[j]->downlen);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j]->uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j]->uplen > 0)
			{
				info[j]->upcmd = (char *)malloc(sizeof(char) * info[j]->uplen);
				memset(info[j]->upcmd,0,info[j]->uplen);
				read(fd,info[j]->upcmd,info[j]->uplen);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j]->mvlen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j]->mvlen > 0)
			{
				info[j]->mvcmd = (char *)malloc(sizeof(char) * info[j]->mvlen);
				memset(info[j]->mvcmd,0,info[j]->mvlen);
				read(fd,info[j]->mvcmd,info[j]->mvlen);
				printf("[%s:%d]:mvcmd:%s\n",__FUNCTION__,__LINE__,info[j]->mvcmd);
			}
		}
	}

	return 1;
}

int RollLabelAnalysis(int fd,int num,RolllabelParam_T **info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		*info = (RolllabelParam_T *)malloc(sizeof(RolllabelParam_T) * num);
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,35);
			info[j]->global = buf[0];
			memcpy(info[j]->name,buf+1,6);
			info[j]->pageId = buf[7];
			info[j]->id = buf[8];
			info[j]->x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j]->y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j]->width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j]->height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j]->level = buf[17];
			info[j]->dir = buf[18];
			info[j]->distype = buf[19];
			info[j]->fpicorcol = (0x0000FF00 & (buf[21] << 8)) | (0x000000FF & buf[20]);
			if(info[j]->distype != 0)
			{
				info[j]->bpicorcol = (0x0000FF00 & (buf[25] << 8)) | (0x000000FF & buf[24]);
			}
			else
			{
				info[j]->bpicorcol = (0x0000FF00 & (buf[23] << 8)) | (0x000000FF & buf[22]);
			}
			
			info[j]->step = buf[26];
			info[j]->period = (0x0000FF00 & (buf[28] << 8)) | (0x000000FF & buf[27]);	
			info[j]->fontIndex = buf[29];
			info[j]->enable = buf[30];
			info[j]->align = buf[31];
			info[j]->txtSpace = buf[32];
			info[j]->txtlen = (0x0000FF00 & (buf[34] << 8)) | (0x000000FF & buf[33]);	
			if(info[j]->txtlen > 0)
			{
				info[j]->txt = (char *)malloc(sizeof(char) * info[j]->txtlen);
				memset(info[j]->txt,0,info[j]->txtlen);
				read(fd,info[j]->txt,info[j]->txtlen);
			}
		
			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j]->downlen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j]->downlen > 0)
			{
				info[j]->downcmd = (char *)malloc(sizeof(char) * info[j]->downlen);
				memset(info[j]->downcmd,0,info[j]->downlen);
				read(fd,info[j]->downcmd,info[j]->downlen);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j]->uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j]->uplen > 0)
			{
				info[j]->upcmd = (char *)malloc(sizeof(char) * info[j]->uplen);
				memset(info[j]->upcmd,0,info[j]->uplen);
				read(fd,info[j]->upcmd,info[j]->uplen);
			}
		}
	}

	return 1;
}

int GraphAnalysis(int fd,int num,GraphParam_T **info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		*info = (GraphParam_T *)malloc(sizeof(GraphParam_T) * num);
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,39);
			info[j]->global = buf[0];
			memcpy(info[j]->name,buf+1,6);
			info[j]->pageId = buf[7];
			info[j]->id = buf[8];
			info[j]->x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j]->y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j]->width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j]->height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j]->level = buf[17];
			info[j]->distype = buf[18];
			if(info[j]->distype != 0)
			{
				info[j]->bpicorcol = (0x0000FF00 & (buf[22] << 8)) | (0x000000FF & buf[21]);
			}
			else
			{
				info[j]->bpicorcol = (0x0000FF00 & (buf[20] << 8)) | (0x000000FF & buf[19]);
			}
			
			info[j]->lor = buf[23];;
			info[j]->gridcolor = (0x0000FF00 & (buf[25] << 8)) | (0x000000FF & buf[24]);			
			info[j]->winterval = buf[26];
			info[j]->hinterval = buf[27];
			info[j]->channel = buf[28];
			info[j]->channelcolor0 = (0x0000FF00 & (buf[30] << 8)) | (0x000000FF & buf[29]);
			info[j]->channelcolor1 = (0x0000FF00 & (buf[32] << 8)) | (0x000000FF & buf[31]);
			info[j]->channelcolor2 = (0x0000FF00 & (buf[34] << 8)) | (0x000000FF & buf[33]);
			info[j]->channelcolor3 = (0x0000FF00 & (buf[36] << 8)) | (0x000000FF & buf[35]);
			info[j]->downlen = (0x0000FF00 & (buf[38] << 8)) | (0x000000FF & buf[37]);
			if(info[j]->downlen > 0)
			{
				info[j]->downcmd = (char *)malloc(sizeof(char) * info[j]->downlen);
				memset(info[j]->downcmd,0,info[j]->downlen);
				read(fd,info[j]->downcmd,info[j]->downlen);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j]->uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j]->uplen > 0)
			{
				info[j]->upcmd = (char *)malloc(sizeof(char) * info[j]->uplen);
				memset(info[j]->upcmd,0,info[j]->uplen);
				read(fd,info[j]->upcmd,info[j]->uplen);
			}
		}
	}

	return 1;
}

int RadioAnalysis(int fd,int num,RadioParam_T **info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		*info = (RadioParam_T *)malloc(sizeof(RadioParam_T) * num);
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,33);
			info[j]->global = buf[0];
			memcpy(info[j]->name,buf+1,6);
			info[j]->pageId = buf[7];
			info[j]->id = buf[8];
			info[j]->x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j]->y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j]->width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j]->height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j]->level = buf[17];
			info[j]->horv = buf[18];
			info[j]->distype = buf[19];
			
			if(info[j]->distype != 0)
			{
				info[j]->fpicorcol = (0x0000FF00 & (buf[25] << 8)) | (0x000000FF & buf[24]);
				info[j]->bpicorcol = (0x0000FF00 & (buf[27] << 8)) | (0x000000FF & buf[26]);
			}
			else
			{
				info[j]->fpicorcol = (0x0000FF00 & (buf[21] << 8))| (0x000000FF & buf[20]);
				info[j]->bpicorcol = (0x0000FF00 & (buf[23] << 8)) | (0x000000FF & buf[22]);
			}
			
			info[j]->focusindex = buf[28];
			info[j]->numofitem = buf[29];	
			info[j]->distance = buf[30];
			info[j]->downlen = (0x0000FF00 & (buf[32] << 8)) | (0x000000FF & buf[31]);
			if(info[j]->downlen > 0)
			{
				info[j]->downcmd = (char *)malloc(sizeof(char) * info[j]->downlen);
				memset(info[j]->downcmd,0,info[j]->downlen);
				read(fd,info[j]->downcmd,info[j]->downlen);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j]->uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j]->uplen > 0)
			{
				info[j]->upcmd = (char *)malloc(sizeof(char) * info[j]->uplen);
				memset(info[j]->upcmd,0,info[j]->uplen);
				read(fd,info[j]->upcmd,info[j]->uplen);
			}
		}
	}

	return 1;
}

int CheckBoxAnalysis(int fd,int num,CheckBoxParam_T **info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		*info = (CheckBoxParam_T *)malloc(sizeof(CheckBoxParam_T) * num);
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,30);
			info[j]->global = buf[0];
			memcpy(info[j]->name,buf+1,6);
			info[j]->pageId = buf[7];
			info[j]->id = buf[8];
			info[j]->x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j]->y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j]->width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j]->height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j]->level = buf[17];
			info[j]->state = buf[18];
			info[j]->distype = buf[19];
			
			if(info[j]->distype != 0)
			{
				info[j]->fpicorcol = (0x0000FF00 & (buf[25] << 8)) | (0x000000FF & buf[24]);
				info[j]->bpicorcol = (0x0000FF00 & (buf[27] << 8)) | (0x000000FF & buf[26]);
			}
			else
			{
				info[j]->fpicorcol = (0x0000FF00 & (buf[21] << 8)) | (0x000000FF & buf[20]);
				info[j]->bpicorcol = (0x0000FF00 & (buf[23] << 8)) | (0x000000FF & buf[22]);
			}
			
			info[j]->downlen = (0x0000FF00 & (buf[29] << 8)) | (0x000000FF & buf[28]);
			if(info[j]->downlen > 0)
			{
				info[j]->downcmd = (char *)malloc(sizeof(char) * info[j]->downlen);
				memset(info[j]->downcmd,0,info[j]->downlen);
				read(fd,info[j]->downcmd,info[j]->downlen);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j]->uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j]->uplen > 0)
			{
				info[j]->upcmd = (char *)malloc(sizeof(char) * info[j]->uplen);
				memset(info[j]->upcmd,0,info[j]->uplen);
				read(fd,info[j]->upcmd,info[j]->uplen);
			}
		}
	}

	return 1;
}

int HotSpotAnalysis(int fd,int num,HotSpotParam_T **info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		*info = (HotSpotParam_T *)malloc(sizeof(HotSpotParam_T) * num);
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,20);
			info[j]->global = buf[0];
			memcpy(info[j]->name,buf+1,6);
			info[j]->pageId = buf[7];
			info[j]->id = buf[8];
			info[j]->x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j]->y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j]->width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j]->height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j]->level = buf[17];
		
			info[j]->downlen = (0x0000FF00 & (buf[19] << 8)) | (0x000000FF & buf[18]);
			if(info[j]->downlen > 0)
			{
				info[j]->downcmd = (char *)malloc(sizeof(char) * info[j]->downlen);
				memset(info[j]->downcmd,0,info[j]->downlen);
				read(fd,info[j]->downcmd,info[j]->downlen);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j]->uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j]->uplen > 0)
			{
				info[j]->upcmd = (char *)malloc(sizeof(char) * info[j]->uplen);
				memset(info[j]->upcmd,0,info[j]->uplen);
				read(fd,info[j]->upcmd,info[j]->uplen);
			}
		}
	}

	return 1;
}

int TimerAnalysis(int fd,int num,TimerParam_T **info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		*info = (TimerParam_T *)malloc(sizeof(TimerParam_T) * num);
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,15);
			info[j]->global = buf[0];
			memcpy(info[j]->name,buf+1,6);
			info[j]->pageId = buf[7];
			info[j]->id = buf[8];			
			info[j]->level = buf[9];
			info[j]->period = (0x0000FF00 & (buf[11] << 8)) | (0x000000FF & buf[10]);
			info[j]->enable = buf[12];
			info[j]->eventlen = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			if(info[j]->eventlen > 0)
			{
				info[j]->event = (char *)malloc(sizeof(char) * info[j]->eventlen);
				memset(info[j]->event,0,info[j]->eventlen);
				read(fd,info[j]->event,info[j]->eventlen);
			}
		}
	}

	return 1;
}

int VariableAnalysis(int fd,int num,VariableParam_T **info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		*info = (VariableParam_T *)malloc(sizeof(VariableParam_T) * num);
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,17);
			info[j]->global = buf[0];
			memcpy(info[j]->name,buf+1,6);
			info[j]->pageId = buf[7];
			info[j]->id = buf[8];			
			info[j]->level = buf[9];
			info[j]->vartype = buf[10];
			if(info[j]->vartype != 0)
			{
				info[j]->val = btos(buf+11);
				info[j]->len = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
				if(info[j]->len > 0)
				{
					info[j]->text = (char *)malloc(sizeof(char) * info[j]->len);
					memset(info[j]->text,0,info[j]->len);
					read(fd,info[j]->text,info[j]->len);
					printf("[%s:%d]:text:%s\n",__FUNCTION__,__LINE__,info[j]->text);
				}
			}
			else
			{
				info[j]->val = btos(buf+11);
				info[j]->len = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			}
			
		}
	}

	return 1;
}

int PicAnalysis(int fd,int num,PicParam_T **info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		*info = (PicParam_T *)malloc(sizeof(PicParam_T) * num);
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,22);
			info[j]->global = buf[0];
			memcpy(info[j]->name,buf+1,6);
			info[j]->pageId = buf[7];
			info[j]->id = buf[8];
			info[j]->x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j]->y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j]->width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j]->height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j]->level = buf[17];
			info[j]->picIndex = (0x0000FF00 & (buf[19] << 8)) | (0x000000FF & buf[18]);
		
			info[j]->downlen = (0x0000FF00 & (buf[21] << 8)) | (0x000000FF & buf[20]);
			if(info[j]->downlen > 0)
			{
				info[j]->downcmd = (char *)malloc(sizeof(char) * info[j]->downlen);
				memset(info[j]->downcmd,0,info[j]->downlen);
				read(fd,info[j]->downcmd,info[j]->downlen);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j]->uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j]->uplen > 0)
			{
				info[j]->upcmd = (char *)malloc(sizeof(char) * info[j]->uplen);
				memset(info[j]->upcmd,0,info[j]->uplen);
				read(fd,info[j]->upcmd,info[j]->uplen);
			}
		}
	}

	return 1;
}

int CPicAnalysis(int fd,int num,CPicParam_T **info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		*info = (CPicParam_T *)malloc(sizeof(CPicParam_T) * num);
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,22);
			info[j]->global = buf[0];
			memcpy(info[j]->name,buf+1,6);
			info[j]->pageId = buf[7];
			info[j]->id = buf[8];
			info[j]->x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j]->y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j]->width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j]->height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j]->level = buf[17];
			info[j]->picIndex = (0x0000FF00 & (buf[19] << 8)) | (0x000000FF & buf[18]);
		
			info[j]->downlen = (0x0000FF00 & (buf[21] << 8)) | (0x000000FF & buf[20]);
			if(info[j]->downlen > 0)
			{
				info[j]->downcmd = (char *)malloc(sizeof(char) * info[j]->downlen);
				memset(info[j]->downcmd,0,info[j]->downlen);
				read(fd,info[j]->downcmd,info[j]->downlen);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j]->uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j]->uplen > 0)
			{
				info[j]->upcmd = (char *)malloc(sizeof(char) * info[j]->uplen);
				memset(info[j]->upcmd,0,info[j]->uplen);
				read(fd,info[j]->upcmd,info[j]->uplen);
			}
		}
	}

	return 1;
}

int CNumAnalysis(int fd,int num,CNumParam_T **info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		*info = (CNumParam_T *)malloc(sizeof(CNumParam_T) * num);
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,33);
			info[j]->global = buf[0];
			memcpy(info[j]->name,buf+1,6);
			info[j]->pageId = buf[7];
			info[j]->id = buf[8];
			info[j]->x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j]->y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j]->width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j]->height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j]->level = buf[17];
			info[j]->distype = buf[18];
			info[j]->text = btos(buf+19);
			info[j]->fontIndex = buf[23];
			info[j]->fpicorcol = (0x0000FF00 & (buf[25] << 8)) | (0x000000FF & buf[24]);
			
			if(info[j]->distype != 0)
			{				
				info[j]->bpicorcol = (0x0000FF00 & (buf[27] << 8)) | (0x000000FF & buf[26]);
			}
			else
			{				
				info[j]->bpicorcol = (0x0000FF00 & (buf[29] << 8)) | (0x000000FF & buf[28]);
			}
			info[j]->align = buf[30];
			info[j]->downlen = (0x0000FF00 & (buf[32] << 8)) | (0x000000FF & buf[31]);
			if(info[j]->downlen > 0)
			{
				info[j]->downcmd = (char *)malloc(sizeof(char) * info[j]->downlen);
				memset(info[j]->downcmd,0,info[j]->downlen);
				read(fd,info[j]->downcmd,info[j]->downlen);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j]->uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j]->uplen > 0)
			{
				info[j]->upcmd = (char *)malloc(sizeof(char) * info[j]->uplen);
				memset(info[j]->upcmd,0,info[j]->uplen);
				read(fd,info[j]->upcmd,info[j]->uplen);
			}
		}
	}

	return 1;
}

int analysisBin()
{
	int fd = 0;
	fd = open("./LKdata.bin", O_RDWR);

	ImageParam_T imageInfo = {0};
	FontParam_T fontInfo = {0};
	PageParam_T pageInfo = {0};
	int direction; //方向,最开始四个字节	
	char buf[512] = {0};
	int i = 0,j = 0;

	memset(&imageInfo,0,sizeof(ImageParam_T));
	memset(&fontInfo,0,sizeof(FontParam_T));
	memset(&pageInfo,0,sizeof(PageParam_T));
	
	memset(buf,0,sizeof(buf));
    read(fd, buf, 16); // 01 00 00 00
	direction = btos(buf);
	imageInfo.imageNum = btos(buf+4);
	fontInfo.fontNum = btos(buf+8);
	pageInfo.pageNum = btos(buf+12);
	printf("[%s:%d]:direction:%d,imageNum:%d,fontNum:%d,pageNum:%d\n",__FUNCTION__,__LINE__,direction,imageInfo.imageNum,fontInfo.fontNum,pageInfo.pageNum);

	imageInfo.image = (ImageInfo_T *)malloc(sizeof(ImageInfo_T) * imageInfo.imageNum);
	memset(buf,0,sizeof(buf));
	read(fd,buf,4*imageInfo.imageNum); //图片地址
	for(i = 0;i < imageInfo.imageNum;i++)
	{		
		imageInfo.image[i].addr = btos(buf+4*i);
		imageInfo.image[i].index = i;
		printf("[%s:%d]:imageAddr[%d]:0x%x\n",__FUNCTION__,__LINE__,i,imageInfo.image[i].addr);
	}

	fontInfo.font = (FontInfo_T *)malloc(sizeof(FontInfo_T) * fontInfo.fontNum);
	memset(buf,0,sizeof(buf));
	read(fd,buf,4*fontInfo.fontNum); //字库地址
	for(i = 0;i < fontInfo.fontNum;i++)
	{
		fontInfo.font[i].addr = btos(buf+4*i);	
		printf("[%s:%d]:fontAddr[%d]:0x%x\n",__FUNCTION__,__LINE__,i,fontInfo.font[i].addr);
	}

	pageInfo.page = (PageInfo_T *)malloc(sizeof(PageInfo_T)*pageInfo.pageNum);
	memset(buf,0,sizeof(buf));
	read(fd,buf,4*pageInfo.pageNum); //页面地址
	for(i = 0;i < pageInfo.pageNum;i++)
	{
		pageInfo.page[i].addr = btos(buf+4*i);		
		pageInfo.page[i].index = i;
		printf("[%s:%d]:pageAddr[%d]:0x%x\n",__FUNCTION__,__LINE__,i,pageInfo.page[i].addr);
	}

	//开始读取图片头数据(8位) + 图片数据
	for(i = 0;i < imageInfo.imageNum;i++)
	{
		memset(buf,0,sizeof(buf));
		read(fd,buf,3);
		printf("[%s:%d]:buf:%s\n",__FUNCTION__,__LINE__,buf);
		if(!strcmp("BMP",buf))
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,5);
			printf("[%s:%d]:buf:%d\n",__FUNCTION__,__LINE__,buf[0]);
			//if(buf[0] == imageInfo.image[i].index) //实际bin文件中index值不对，都是0，可以不判断
			{
				imageInfo.image[i].width = (0x0000FF00 & (buf[2] << 8)) | (0x000000FF & buf[1]);
				imageInfo.image[i].height = (0x0000FF00 & (buf[4] << 8)) | (0x000000FF & buf[3]);
				printf("[%s:%d]:width:0x%x,height:0x%x\n",__FUNCTION__,__LINE__,imageInfo.image[i].width,imageInfo.image[i].height);
				imageInfo.image[i].data = (char *)malloc(imageInfo.image[i].width * imageInfo.image[i].height*2);
				read(fd,imageInfo.image[i].data,imageInfo.image[i].width * imageInfo.image[i].height*2);
				if(i == 0)
				{
					FILE *file = NULL;
					file= fopen("./iamge0", "w+");			
					fwrite(imageInfo.image[i].data,1,imageInfo.image[i].width * imageInfo.image[i].height*2,file);
					fclose(file);
				}
			}
		}
	}

	//开始读取字体头数据(8位) + 字体数据
	int fontsize = 0;
	for(i = 0;i < fontInfo.fontNum;i++)
	{
		memset(buf,0,sizeof(buf));
		read(fd,buf,4);
		fontInfo.font[i].index = btos(buf);
		printf("[%s:%d]:font[%d].index:0x%x\n",__FUNCTION__,__LINE__,i,fontInfo.font[i].index);

		memset(buf,0,sizeof(buf));
		read(fd,buf,4);
		
		fontInfo.font[i].width = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
		fontInfo.font[i].height = (0x0000FF00 & (buf[3] << 8)) | (0x000000FF & buf[2]);
		printf("[%s:%d]:width:0x%x,height:0x%x\n",__FUNCTION__,__LINE__,fontInfo.font[i].width,fontInfo.font[i].height);
		if((i + 1) < fontInfo.fontNum)
		{
			fontsize = fontInfo.font[i + 1].addr - fontInfo.font[i].addr - 8;
		}
		else
		{
			fontsize = pageInfo.page[0].addr - fontInfo.font[i].addr - 8;
		}
		fontInfo.font[i].data = (char *)malloc(sizeof(char) * fontsize);
		read(fd,fontInfo.font[i].data,fontsize);				

	}

	
	//开始读取页面头数据(8位) + 页面数据
	for(i = 0;i < pageInfo.pageNum;i++)
	{
		memset(pageInfo.page[i].objname,0,sizeof(pageInfo.page[i].objname));
		read(fd,pageInfo.page[i].objname,9);
		printf("[%s:%d]:objname:%s\n",__FUNCTION__,__LINE__,pageInfo.page[i].objname);
		memset(buf,0,sizeof(buf));
		read(fd,buf,4);
		printf("[%s:%d]:buf:%s\n",__FUNCTION__,__LINE__,buf);
		if(!strcmp("PAGE",buf))
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			pageInfo.page[i].global = buf[0];
			pageInfo.page[i].picornot = buf[1];
			printf("[%s:%d]:page[%d]:global:%d,picornot:%d\n",__FUNCTION__,__LINE__,i,pageInfo.page[i].global,pageInfo.page[i].picornot);
			memset(buf,0,sizeof(buf));
			read(fd,buf,4);
			if(pageInfo.page[i].picornot == 0)
			{
				pageInfo.page[i].bcOrpi = (0x0000FF00 & (buf[3] << 8)) | (0x000000FF & buf[2]);
			}
			else
			{
				pageInfo.page[i].bcOrpi = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			}
			printf("[%s:%d]:page[%d]:bcOrpi:0x%x\n",__FUNCTION__,__LINE__,i,pageInfo.page[i].bcOrpi);
			memset(buf,0,sizeof(buf));
			read(fd,buf,8); //这8个字节不懂啥意思Before\After\TouchDown\TouchUp事件

			memset(buf,0,sizeof(buf));
			read(fd,buf,60); //读取15种控件的数量
			pageInfo.page[i].buttonNum = btos(buf);
			pageInfo.page[i].labelNum = btos(buf+4);
			pageInfo.page[i].pgbarNum = btos(buf+8);
			pageInfo.page[i].panelNum = btos(buf+12);
			pageInfo.page[i].slideNum = btos(buf+16);
			pageInfo.page[i].rolllabelNum = btos(buf+20);
			pageInfo.page[i].graphNum = btos(buf+24);
			pageInfo.page[i].radioNum = btos(buf+28);
			pageInfo.page[i].checkboxNum = btos(buf+32);
			pageInfo.page[i].hotspotNum = btos(buf+36);
			pageInfo.page[i].timerNum = btos(buf+40);
			pageInfo.page[i].variableNum = btos(buf+44);
			pageInfo.page[i].picNum = btos(buf+48);
			pageInfo.page[i].cpicNum = btos(buf+52);
			pageInfo.page[i].numNum = btos(buf+56);
			
			printf("[%s:%d]:page[%d]:num:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",__FUNCTION__,__LINE__,
								  i,pageInfo.page[i].buttonNum,pageInfo.page[i].labelNum,pageInfo.page[i].pgbarNum,pageInfo.page[i].panelNum,
								  pageInfo.page[i].slideNum,pageInfo.page[i].rolllabelNum,pageInfo.page[i].graphNum,pageInfo.page[i].radioNum,
								  pageInfo.page[i].checkboxNum,pageInfo.page[i].hotspotNum,pageInfo.page[i].timerNum,pageInfo.page[i].variableNum,
								  pageInfo.page[i].picNum,pageInfo.page[i].cpicNum,pageInfo.page[i].numNum);
			
			ButtonAnalysis(fd,pageInfo.page[i].buttonNum,&(pageInfo.page[i].buttonInfo));
			for(j = 0;j < pageInfo.page[i].buttonNum;j++)
			{
				printf("[%s:%d]:page[%d].button[%d]info:\n",__FUNCTION__,__LINE__,i,j);
				printf("***********************************\n");
				printf(" global:%d,name:%s,pageId;%d,id:%d \n x:%d,y:%d,width:%d,height:%d \n level:%d,distype:%d,fpic:0x%x,bpic:0x%x \n",
					pageInfo.page[i].buttonInfo[j].global,pageInfo.page[i].buttonInfo[j].name,pageInfo.page[i].buttonInfo[j].pageId,
					pageInfo.page[i].buttonInfo[j].id,pageInfo.page[i].buttonInfo[j].x,pageInfo.page[i].buttonInfo[j].y,
					pageInfo.page[i].buttonInfo[j].width,pageInfo.page[i].buttonInfo[j].height,pageInfo.page[i].buttonInfo[j].level,
					pageInfo.page[i].buttonInfo[j].distype,pageInfo.page[i].buttonInfo[j].fpic,pageInfo.page[i].buttonInfo[j].bpic);
				printf(" txtlen:%d,txt:%s,fontIndex;%d,txtColor:%d \n swType:%d,downlen:%d,uplen:%d \n",
					pageInfo.page[i].buttonInfo[j].txtlen,pageInfo.page[i].buttonInfo[j].txt,pageInfo.page[i].buttonInfo[j].fontIndex,
					pageInfo.page[i].buttonInfo[j].txtColor,pageInfo.page[i].buttonInfo[j].swType,pageInfo.page[i].buttonInfo[j].downlen,
					pageInfo.page[i].buttonInfo[j].uplen);
				printf("***********************************\n\n\n");
			}
			//printf("[%s:%d]:page[%d].labelinfo:[%d]\n",__FUNCTION__,__LINE__,i,pageInfo.page[i].labelInfo[0].global);
			LabelAnalysis(fd,pageInfo.page[i].labelNum,&(pageInfo.page[i].labelInfo));
			for(j = 0;j < pageInfo.page[i].labelNum;j++)
			{
				printf("[%s:%d]:page[%d].label[%d]info:\n",__FUNCTION__,__LINE__,i,j);
				printf("***********************************\n");
				printf(" global:%d,name:%s,pageId;%d,id:%d \n x:%d,y:%d,width:%d,height:%d \n level:%d,distype:%d,fpicorcol:0x%x,bpicorcol:0x%x \n",
					pageInfo.page[i].labelInfo[j].global,pageInfo.page[i].labelInfo[j].name,pageInfo.page[i].labelInfo[j].pageId,
					pageInfo.page[i].labelInfo[j].id,pageInfo.page[i].labelInfo[j].x,pageInfo.page[i].labelInfo[j].y,
					pageInfo.page[i].labelInfo[j].width,pageInfo.page[i].labelInfo[j].height,pageInfo.page[i].labelInfo[j].level,
					pageInfo.page[i].labelInfo[j].distype,pageInfo.page[i].labelInfo[j].fpicorcol,pageInfo.page[i].labelInfo[j].bpicorcol);
				printf(" txtlen:%d,txt:%s,fontIndex;%d,txtSpace:%d \n align:%d,downlen:%d,uplen:%d \n",
					pageInfo.page[i].labelInfo[j].txtlen,pageInfo.page[i].labelInfo[j].txt,pageInfo.page[i].labelInfo[j].fontIndex,
					pageInfo.page[i].labelInfo[j].txtSpace,pageInfo.page[i].labelInfo[j].align,pageInfo.page[i].labelInfo[j].downlen,
					pageInfo.page[i].labelInfo[j].uplen);
				printf("***********************************\n\n\n");
			}

			ProgressBarAnalysis(fd,pageInfo.page[i].pgbarNum,&(pageInfo.page[i].pgbarInfo));
			for(j = 0;j < pageInfo.page[i].pgbarNum;j++)
			{
				printf("[%s:%d]:page[%d].pgbar[%d]info:\n",__FUNCTION__,__LINE__,i,j);
				printf("***********************************\n");
				printf(" global:%d,name:%s,pageId;%d,id:%d \n x:%d,y:%d,width:%d,height:%d \n level:%d,distype:%d,fpic:0x%x,bpic:0x%x \n",
					pageInfo.page[i].pgbarInfo[j].global,pageInfo.page[i].pgbarInfo[j].name,pageInfo.page[i].pgbarInfo[j].pageId,
					pageInfo.page[i].pgbarInfo[j].id,pageInfo.page[i].pgbarInfo[j].x,pageInfo.page[i].pgbarInfo[j].y,
					pageInfo.page[i].pgbarInfo[j].width,pageInfo.page[i].pgbarInfo[j].height,pageInfo.page[i].pgbarInfo[j].level,
					pageInfo.page[i].pgbarInfo[j].distype,pageInfo.page[i].pgbarInfo[j].fpic,pageInfo.page[i].pgbarInfo[j].bpic);
				printf(" hov:%d,percent:%d,downlen:%d,uplen:%d \n",
					pageInfo.page[i].pgbarInfo[j].hov,pageInfo.page[i].pgbarInfo[j].percent,pageInfo.page[i].pgbarInfo[j].downlen,
					pageInfo.page[i].pgbarInfo[j].uplen);
				printf("***********************************\n\n\n");
			}

			PanelAnalysis(fd,pageInfo.page[i].panelNum,&(pageInfo.page[i].panelInfo));
			for(j = 0;j < pageInfo.page[i].panelNum;j++)
			{
				printf("[%s:%d]:page[%d].panel[%d]info:\n",__FUNCTION__,__LINE__,i,j);
				printf("***********************************\n");
				printf(" global:%d,name:%s,pageId;%d,id:%d \n x:%d,y:%d,width:%d,height:%d \n level:%d,distype:%d,fpic:0x%x,bpic:0x%x \n",
					pageInfo.page[i].panelInfo[j].global,pageInfo.page[i].panelInfo[j].name,pageInfo.page[i].panelInfo[j].pageId,
					pageInfo.page[i].panelInfo[j].id,pageInfo.page[i].panelInfo[j].x,pageInfo.page[i].panelInfo[j].y,
					pageInfo.page[i].panelInfo[j].width,pageInfo.page[i].panelInfo[j].height,pageInfo.page[i].panelInfo[j].level,
					pageInfo.page[i].panelInfo[j].distype,pageInfo.page[i].panelInfo[j].fpicorcol,pageInfo.page[i].panelInfo[j].bpicorcol);
				printf(" linewidth:%d,angle:%d,downlen:%d,uplen:%d \n",
					pageInfo.page[i].panelInfo[j].linewidth,pageInfo.page[i].panelInfo[j].angle,pageInfo.page[i].panelInfo[j].downlen,
					pageInfo.page[i].panelInfo[j].uplen);
				printf("***********************************\n\n\n");
			}

			SliderAnalysis(fd,pageInfo.page[i].slideNum,&(pageInfo.page[i].slideInfo));
			for(j = 0;j < pageInfo.page[i].slideNum;j++)
			{
				printf("[%s:%d]:page[%d].slide[%d]info:\n",__FUNCTION__,__LINE__,i,j);
				printf("***********************************\n");
				printf(" global:%d,name:%s,pageId;%d,id:%d \n x:%d,y:%d,width:%d,height:%d \n level:%d,distype:%d,fpic:0x%x,bpic:0x%x \n",
					pageInfo.page[i].slideInfo[j].global,pageInfo.page[i].slideInfo[j].name,pageInfo.page[i].slideInfo[j].pageId,
					pageInfo.page[i].slideInfo[j].id,pageInfo.page[i].slideInfo[j].x,pageInfo.page[i].slideInfo[j].y,
					pageInfo.page[i].slideInfo[j].width,pageInfo.page[i].slideInfo[j].height,pageInfo.page[i].slideInfo[j].level,
					pageInfo.page[i].slideInfo[j].distype,pageInfo.page[i].slideInfo[j].fpicorcol,pageInfo.page[i].slideInfo[j].bpicorcol);
				printf(" hov:%d,min:%d,max:%d,value:%d,wid:%d,hgt:%d,downlen:%d,uplen:%d,mvlen:%d \n",
					pageInfo.page[i].slideInfo[j].hov,pageInfo.page[i].slideInfo[j].min,pageInfo.page[i].slideInfo[j].max,
					pageInfo.page[i].slideInfo[j].value,pageInfo.page[i].slideInfo[j].wid,pageInfo.page[i].slideInfo[j].hgt,
					pageInfo.page[i].slideInfo[j].downlen,pageInfo.page[i].slideInfo[j].uplen,pageInfo.page[i].slideInfo[j].mvlen);
				printf("***********************************\n\n\n");
			}

			RollLabelAnalysis(fd,pageInfo.page[i].rolllabelNum,&(pageInfo.page[i].rolllableInfo));
			for(j = 0;j < pageInfo.page[i].rolllabelNum;j++)
			{
				printf("[%s:%d]:page[%d].rolllabel[%d]info:\n",__FUNCTION__,__LINE__,i,j);
				printf("***********************************\n");
				printf(" global:%d,name:%s,pageId;%d,id:%d \n x:%d,y:%d,width:%d,height:%d \n level:%d,distype:%d,fpic:0x%x,bpic:0x%x \n",
					pageInfo.page[i].rolllableInfo[j].global,pageInfo.page[i].rolllableInfo[j].name,pageInfo.page[i].rolllableInfo[j].pageId,
					pageInfo.page[i].rolllableInfo[j].id,pageInfo.page[i].rolllableInfo[j].x,pageInfo.page[i].rolllableInfo[j].y,
					pageInfo.page[i].rolllableInfo[j].width,pageInfo.page[i].rolllableInfo[j].height,pageInfo.page[i].rolllableInfo[j].level,
					pageInfo.page[i].rolllableInfo[j].distype,pageInfo.page[i].rolllableInfo[j].fpicorcol,pageInfo.page[i].rolllableInfo[j].bpicorcol);
				printf(" dir:%d,step:%d,period:%d,fontIndex:%d,enable:%d,txtSpace:%d,align:%d,txtlen:%d,txt:%s,downlen:%d,uplen:%d \n",
					pageInfo.page[i].rolllableInfo[j].dir,pageInfo.page[i].rolllableInfo[j].step,pageInfo.page[i].rolllableInfo[j].period,
					pageInfo.page[i].rolllableInfo[j].fontIndex,pageInfo.page[i].rolllableInfo[j].enable,pageInfo.page[i].rolllableInfo[j].txtSpace,
					pageInfo.page[i].rolllableInfo[j].align,pageInfo.page[i].rolllableInfo[j].txtlen,pageInfo.page[i].rolllableInfo[j].txt,
					pageInfo.page[i].rolllableInfo[j].downlen,pageInfo.page[i].rolllableInfo[j].uplen);
				printf("***********************************\n\n\n");
			}

			GraphAnalysis(fd,pageInfo.page[i].graphNum,&(pageInfo.page[i].graphInfo));
			for(j = 0;j < pageInfo.page[i].graphNum;j++)
			{
				printf("[%s:%d]:page[%d].graph[%d]info:\n",__FUNCTION__,__LINE__,i,j);
				printf("***********************************\n");
				printf(" global:%d,name:%s,pageId;%d,id:%d \n x:%d,y:%d,width:%d,height:%d \n level:%d,distype:%d,lor:0x%x,bpic:0x%x \n",
					pageInfo.page[i].graphInfo[j].global,pageInfo.page[i].graphInfo[j].name,pageInfo.page[i].graphInfo[j].pageId,
					pageInfo.page[i].graphInfo[j].id,pageInfo.page[i].graphInfo[j].x,pageInfo.page[i].graphInfo[j].y,
					pageInfo.page[i].graphInfo[j].width,pageInfo.page[i].graphInfo[j].height,pageInfo.page[i].graphInfo[j].level,
					pageInfo.page[i].graphInfo[j].distype,pageInfo.page[i].graphInfo[j].lor,pageInfo.page[i].graphInfo[j].bpicorcol);
				printf(" gridcolor:0x%x,winterval:0x%x,hinterval:0x%x,channel:0x%x,channelcolor0:0x%x,channelcolor1:0x%x,channelcolor2:0x%x,channelcolor3:0x%x,downlen:%d,uplen:%d \n",
					pageInfo.page[i].graphInfo[j].gridcolor,pageInfo.page[i].graphInfo[j].winterval,pageInfo.page[i].graphInfo[j].hinterval,
					pageInfo.page[i].graphInfo[j].channel,pageInfo.page[i].graphInfo[j].channelcolor0,pageInfo.page[i].graphInfo[j].channelcolor1,
					pageInfo.page[i].graphInfo[j].channelcolor2,pageInfo.page[i].graphInfo[j].channelcolor3,
					pageInfo.page[i].graphInfo[j].downlen,pageInfo.page[i].graphInfo[j].uplen);
				printf("***********************************\n\n\n");
			}

			RadioAnalysis(fd,pageInfo.page[i].radioNum,&(pageInfo.page[i].radioInfo));
			for(j = 0;j < pageInfo.page[i].radioNum;j++)
			{
				printf("[%s:%d]:page[%d].radio[%d]info:\n",__FUNCTION__,__LINE__,i,j);
				printf("***********************************\n");
				printf(" global:%d,name:%s,pageId;%d,id:%d \n x:%d,y:%d,width:%d,height:%d \n level:%d,distype:%d,fpic:0x%x,bpic:0x%x \n",
					pageInfo.page[i].radioInfo[j].global,pageInfo.page[i].radioInfo[j].name,pageInfo.page[i].radioInfo[j].pageId,
					pageInfo.page[i].radioInfo[j].id,pageInfo.page[i].radioInfo[j].x,pageInfo.page[i].radioInfo[j].y,
					pageInfo.page[i].radioInfo[j].width,pageInfo.page[i].radioInfo[j].height,pageInfo.page[i].radioInfo[j].level,
					pageInfo.page[i].radioInfo[j].distype,pageInfo.page[i].radioInfo[j].fpicorcol,pageInfo.page[i].radioInfo[j].bpicorcol);
				printf(" horv:0x%x,focusindex:0x%x,numofitem:0x%x,distance:0x%x,downlen:%d,uplen:%d \n",
					pageInfo.page[i].radioInfo[j].horv,pageInfo.page[i].radioInfo[j].focusindex,pageInfo.page[i].radioInfo[j].numofitem,
					pageInfo.page[i].radioInfo[j].distance,pageInfo.page[i].radioInfo[j].downlen,pageInfo.page[i].radioInfo[j].uplen);
				printf("***********************************\n\n\n");
			}

			CheckBoxAnalysis(fd,pageInfo.page[i].checkboxNum,&(pageInfo.page[i].checkboxInfo));
			for(j = 0;j < pageInfo.page[i].checkboxNum;j++)
			{
				printf("[%s:%d]:page[%d].checkbox[%d]info:\n",__FUNCTION__,__LINE__,i,j);
				printf("***********************************\n");
				printf(" global:%d,name:%s,pageId;%d,id:%d \n x:%d,y:%d,width:%d,height:%d \n level:%d,distype:%d,fpic:0x%x,bpic:0x%x \n",
					pageInfo.page[i].checkboxInfo[j].global,pageInfo.page[i].checkboxInfo[j].name,pageInfo.page[i].checkboxInfo[j].pageId,
					pageInfo.page[i].checkboxInfo[j].id,pageInfo.page[i].checkboxInfo[j].x,pageInfo.page[i].checkboxInfo[j].y,
					pageInfo.page[i].checkboxInfo[j].width,pageInfo.page[i].checkboxInfo[j].height,pageInfo.page[i].checkboxInfo[j].level,
					pageInfo.page[i].checkboxInfo[j].distype,pageInfo.page[i].checkboxInfo[j].fpicorcol,pageInfo.page[i].checkboxInfo[j].bpicorcol);
				printf(" state:0x%x,downlen:%d,uplen:%d \n",
					pageInfo.page[i].checkboxInfo[j].state,pageInfo.page[i].checkboxInfo[j].downlen,pageInfo.page[i].checkboxInfo[j].uplen);
				printf("***********************************\n\n\n");
			}

			HotSpotAnalysis(fd,pageInfo.page[i].hotspotNum,&(pageInfo.page[i].hotspotInfo));
			for(j = 0;j < pageInfo.page[i].hotspotNum;j++)
			{
				printf("[%s:%d]:page[%d].hotspot[%d]info:\n",__FUNCTION__,__LINE__,i,j);
				printf("***********************************\n");
				printf(" global:%d,name:%s,pageId;%d,id:%d \n x:%d,y:%d,width:%d,height:%d,level:%d \n",
					pageInfo.page[i].hotspotInfo[j].global,pageInfo.page[i].hotspotInfo[j].name,pageInfo.page[i].hotspotInfo[j].pageId,
					pageInfo.page[i].hotspotInfo[j].id,pageInfo.page[i].hotspotInfo[j].x,pageInfo.page[i].hotspotInfo[j].y,
					pageInfo.page[i].hotspotInfo[j].width,pageInfo.page[i].hotspotInfo[j].height,pageInfo.page[i].hotspotInfo[j].level);
				printf("downlen:%d,uplen:%d \n",
					pageInfo.page[i].hotspotInfo[j].downlen,pageInfo.page[i].hotspotInfo[j].uplen);
				printf("***********************************\n\n\n");
			}


			TimerAnalysis(fd,pageInfo.page[i].timerNum,&(pageInfo.page[i].timerInfo));
			for(j = 0;j < pageInfo.page[i].timerNum;j++)
			{
				printf("[%s:%d]:page[%d].timer[%d]info:\n",__FUNCTION__,__LINE__,i,j);
				printf("***********************************\n");
				printf(" global:%d,name:%s,pageId;%d,id:%d,level:%d \n",
					pageInfo.page[i].timerInfo[j].global,pageInfo.page[i].timerInfo[j].name,pageInfo.page[i].timerInfo[j].pageId,
					pageInfo.page[i].timerInfo[j].id,pageInfo.page[i].timerInfo[j].level);
				printf("period:0x%x,enable:%d,eventlen:0x%x,event:%s\n",
					pageInfo.page[i].timerInfo[j].period,pageInfo.page[i].timerInfo[j].enable,pageInfo.page[i].timerInfo[j].eventlen,
					pageInfo.page[i].timerInfo[j].event);
				printf("***********************************\n\n\n");
			}

			VariableAnalysis(fd,pageInfo.page[i].variableNum,&(pageInfo.page[i].variableInfo));
			for(j = 0;j < pageInfo.page[i].variableNum;j++)
			{
				printf("[%s:%d]:page[%d].variable[%d]info:\n",__FUNCTION__,__LINE__,i,j);
				printf("***********************************\n");
				printf(" global:%d,name:%s,pageId;%d,id:%d,level:%d \n",
					pageInfo.page[i].variableInfo[j].global,pageInfo.page[i].variableInfo[j].name,pageInfo.page[i].variableInfo[j].pageId,
					pageInfo.page[i].variableInfo[j].id,pageInfo.page[i].variableInfo[j].level);
				printf("vartype:0x%x,val:0x%x,len:0x%x \n",
					pageInfo.page[i].variableInfo[j].vartype,pageInfo.page[i].variableInfo[j].val,pageInfo.page[i].variableInfo[j].len);
				printf("***********************************\n\n\n");
			}

			PicAnalysis(fd,pageInfo.page[i].picNum,&(pageInfo.page[i].picInfo));
			for(j = 0;j < pageInfo.page[i].picNum;j++)
			{
				printf("[%s:%d]:page[%d].pic[%d]info:\n",__FUNCTION__,__LINE__,i,j);
				printf("***********************************\n");
				printf(" global:%d,name:%s,pageId;%d,id:%d \n x:%d,y:%d,width:%d,height:%d,level:%d \n",
					pageInfo.page[i].picInfo[j].global,pageInfo.page[i].picInfo[j].name,pageInfo.page[i].picInfo[j].pageId,
					pageInfo.page[i].picInfo[j].id,pageInfo.page[i].picInfo[j].x,pageInfo.page[i].picInfo[j].y,
					pageInfo.page[i].picInfo[j].width,pageInfo.page[i].picInfo[j].height,pageInfo.page[i].picInfo[j].level);
				printf(" picIndex:0x%x,downlen:0x%x,uplen:0x%x \n",
					pageInfo.page[i].picInfo[j].picIndex,pageInfo.page[i].picInfo[j].downlen,pageInfo.page[i].picInfo[j].uplen);
				printf("***********************************\n\n\n");
			}

			CPicAnalysis(fd,pageInfo.page[i].cpicNum,&(pageInfo.page[i].cpicInfo));
			for(j = 0;j < pageInfo.page[i].cpicNum;j++)
			{
				printf("[%s:%d]:page[%d].cpic[%d]info:\n",__FUNCTION__,__LINE__,i,j);
				printf("***********************************\n");
				printf(" global:%d,name:%s,pageId;%d,id:%d \n x:%d,y:%d,width:%d,height:%d,level:%d \n",
					pageInfo.page[i].cpicInfo[j].global,pageInfo.page[i].cpicInfo[j].name,pageInfo.page[i].cpicInfo[j].pageId,
					pageInfo.page[i].cpicInfo[j].id,pageInfo.page[i].cpicInfo[j].x,pageInfo.page[i].cpicInfo[j].y,
					pageInfo.page[i].cpicInfo[j].width,pageInfo.page[i].cpicInfo[j].height,pageInfo.page[i].cpicInfo[j].level);
				printf(" picIndex:0x%x,downlen:0x%x,uplen:0x%x \n",
					pageInfo.page[i].cpicInfo[j].picIndex,pageInfo.page[i].cpicInfo[j].downlen,pageInfo.page[i].cpicInfo[j].uplen);
				printf("***********************************\n\n\n");
			}

			CNumAnalysis(fd,pageInfo.page[i].numNum,&(pageInfo.page[i].numInfo));
			for(j = 0;j < pageInfo.page[i].numNum;j++)
			{
				printf("[%s:%d]:page[%d].Cnum[%d]info:\n",__FUNCTION__,__LINE__,i,j);
				printf("***********************************\n");
				printf(" global:%d,name:%s,pageId;%d,id:%d \n x:%d,y:%d,width:%d,height:%d \n level:%d,distype:%d,fpic:0x%x,bpic:0x%x \n",
					pageInfo.page[i].numInfo[j].global,pageInfo.page[i].numInfo[j].name,pageInfo.page[i].numInfo[j].pageId,
					pageInfo.page[i].numInfo[j].id,pageInfo.page[i].numInfo[j].x,pageInfo.page[i].numInfo[j].y,
					pageInfo.page[i].numInfo[j].width,pageInfo.page[i].numInfo[j].height,pageInfo.page[i].numInfo[j].level,
					pageInfo.page[i].numInfo[j].distype,pageInfo.page[i].numInfo[j].fpicorcol,pageInfo.page[i].numInfo[j].bpicorcol);
				printf(" fontIndex:0x%x,text:0x%x,align:%d,downlen:%d,uplen:%d \n",
					pageInfo.page[i].numInfo[j].fontIndex,pageInfo.page[i].numInfo[j].text,pageInfo.page[i].numInfo[j].align,
					pageInfo.page[i].numInfo[j].downlen,pageInfo.page[i].numInfo[j].uplen);
				printf("***********************************\n\n\n");
			}
			
		}
			
	}
	
	return 0;
	
}


int recvEnd(char *dataBuf,int size)
{
	char r_buf[512];
	int	s32Ret = -1,i = 0,findend = 0;

	memset(r_buf,0,sizeof(r_buf));
	s32Ret = uartRecv(r_buf,size);
	for(i = 0;i < s32Ret;i++)
	{
		if(r_buf[i] == 0xb)
		{
			memcpy(dataBuf,r_buf,i);
			findend = 1;
			break;
		}
	}
	
	if(findend != 1)
	{
		size = size - s32Ret;
		if(size > 0)
		{
			memcpy(dataBuf,r_buf,s32Ret);
			recvEnd(dataBuf+s32Ret,size);
		}
		else
		{
			return -1;
		}
	}
	return 0;
}
/*
int main(int argc, char **argv)
{
    int	s32Ret = -1,i = 0;
	int sendlen = 0;
    char r_buf[512];
	char s_buf[512];
	char data_buf[512];

    ttyS4Init();
	
	memset(data_buf,0,sizeof(data_buf));
	analysisBin();
	return 0;
    while(1)
    {
		memset(r_buf,0,sizeof(r_buf));
		s32Ret = uartRecv(r_buf,1); //读头
		if(s32Ret > 0)
		{
			if(r_buf[0] == 0x01 || r_buf[0] == 0x02)
			{
				memset(data_buf,0,sizeof(data_buf));
				recvEnd(data_buf,512);
				printf("[%s:%d]:data_buf:%s!!!",__FUNCTION__,__LINE__,data_buf);
				if(!strcmp("load",data_buf))
				{
					printf("start to load data!!!!\n");
					memset(s_buf,0,sizeof(s_buf));
					sprintf(s_buf,"%s,%s,%s,%s,%s","t1","128*64","h1","f030","64");
					sendlen = strlen(s_buf);
					tty_send(s_buf,sendlen);
				}
				else
				{
					cmdproc(data_buf);
				}
			}
			else if(r_buf[i] == 0x80)
			{
				char binlen[32];
				char speed[32];
				
				memset(binlen,0,sizeof(binlen));
				memcpy(binlen,r_buf+i+1,4);
				printf("[%s:%d]:binlen:%s!!!",__FUNCTION__,__LINE__,binlen);
				
				memset(speed,0,sizeof(speed));
				memcpy(speed,r_buf+i+5,4);
				printf("[%s:%d]:speed:%s!!!",__FUNCTION__,__LINE__,speed);
				
				memset(s_buf,0,sizeof(s_buf));
				s_buf[0] = 0x81;
				tty_send(s_buf,1);
				
				//uartRecv(r_buf,binlen);
			}
		}
    }
 
    close(tty_fd) ;
    return 0 ;
}

*/
int Bytes2String(unsigned char *pSrc, int nSrcLen, unsigned char *pDst, int nDstMaxLen)
{
    if (pDst != NULL)
    {
        *pDst = 0;
    }

    if (pSrc == NULL || nSrcLen <= 0 || pDst == NULL || nDstMaxLen <= nSrcLen * 2)
    {
        return 0;
    }

    const char szTable[] = "0123456789ABCDEF";
    int i;
    for (i = 0; i < nSrcLen; i++)
    {
        *pDst++ = szTable[pSrc[i] >> 4];
        *pDst++ = szTable[pSrc[i] & 0x0f];
    }
    *pDst = '\0';
    return  nSrcLen * 2;
}

/**---------------------------------------------------------------------------*
**                         Compiler Flag                                     *
**---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern   "C"
}
#endif

#endif	//_UART_DEMO_C_

