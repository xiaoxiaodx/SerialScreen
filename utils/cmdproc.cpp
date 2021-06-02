/******************************************************************************
 *
 * 				Copyright (c), 2021,
 *
 * *****************************************************************************
 * Filename:cmdproc.c
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

/**---------------------------------------------------------------------------*
**                         Compiler Flag                                     *
**---------------------------------------------------------------------------*/

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
#include <stdlib.h>
#include "cmdproc.h"
#include <QDebug>

#include <utils/resourcesmanager.h>
#include <mywidget/mybutton.h>
#include <mywidget/mygraph.h>
#include <mywidget/mylabel.h>
#include <mywidget/mypage.h>
#include <mywidget/myprogressbar.h>
#include <mywidget/myradio.h>
#include <mywidget/myrolllabel.h>
#include <mywidget/mysilder.h>
#include <mywidget/mypic.h>
#include <mywidget/myhotspot.h>

#include <mywidget/mycheck.h>
#include <mywidget/mydial.h>
#include "util.h"
/******************************************************************************
*	Macros
******************************************************************************/


/******************************************************************************
*	Types
******************************************************************************/
//enum

//Struct
typedef struct  _tagCMDPROCCB_S{
    int32_t cmdid;
    char *cmd;
    int32_t num;
    int (*cmdproc)(char *str,int num, void * data );
}stCMDPROCCB_S;

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
int page_proc(char *str,int num,void *data);
int clean_proc(char *str,int num,void *data);
int point_proc(char *str,int num,void *data);
int line_proc(char *str,int num,void *data);
int rect_proc(char *str,int num,void *data);
int frect_proc(char *str,int num,void *data);

int pie_proc(char *str,int num,void *data);
int arc_proc(char *str,int num,void *data);
int cir_proc(char *str,int num,void *data);
int fcir_proc(char *str,int num,void *data);

int pic_proc(char *str,int num,void *data);
int picc_proc(char *str,int num,void *data);
int str_proc(char *str,int num,void *data);
int ref_proc(char *str,int num,void *data);
int click_proc(char *str,int num,void *data);


int ecoh_proc(char *str,int num,void *data);
int ecohn_proc(char *str,int num,void *data);
int hide_proc(char *str,int num,void *data);
int show_proc(char *str,int num,void *data);
int re_proc(char *str,int num,void *data);


int addn_proc(char *str,int num,void *data);


int add_proc(char *str,int num,void *data);
int del_proc(char *str,int num,void *data);
int cal_proc(char *str,int num,void *data);
int reset_proc(char *str,int num,void *data);
int baud_proc(char *str,int num,void *data);
int dim_proc(char *str,int num,void *data);
int rand_proc(char *str,int num,void *data);
int slen_proc(char *str,int num,void *data);
int scopy_proc(char *str,int num,void *data);
int sncopy_proc(char *str,int num,void *data);
int sleep_proc(char *str,int num,void *data);

serialParam_T serParam = {0};

//extern Functions Prototypes
stCMDPROCCB_S cmdProcTbl[]={
    {1,"page",1,page_proc},
    {2,"clean",1,clean_proc},
    {3,"point",3,point_proc},
    {4,"line",5,line_proc},
    {5,"rect",5,rect_proc},
    {6,"fillRect",5,frect_proc},

    {7,"pie",6,pie_proc},
    {8,"arc",7,arc_proc},
    {9,"circle",4,cir_proc},
    {10,"fillCircle",4,fcir_proc},
    {11,"picture",3,pic_proc},
    {12,"cutChart",5,picc_proc},

    {13,"str",10,str_proc},
    {14,"refresh",1,ref_proc},
    {15,"click",2,click_proc},

    {16,"echo",1,ecoh_proc},
    {17,"echon",2,ecohn_proc},
    {18,"hide",2,hide_proc},
    {19,"show",2,show_proc},
    {20,"re",1,re_proc},
    
    {0x1000|21,"curveAddData",3,addn_proc},

    {22,"curveAdd",3,add_proc},
    {23,"curveDelete",2,del_proc},
    {24,"calTouch",0,cal_proc},
    {25,"reset",0,reset_proc},
    {26,"baudRate",1,baud_proc},
    {27,"lightAdjust",1,dim_proc},
    {28,"rand",1,rand_proc},
    {29,"strLen",2,slen_proc},
    {30,"strCopy",2,scopy_proc},
    {31,"numCopy",3,sncopy_proc},
    {32,"sleep",1,sleep_proc},
    
    {-1,NULL,1,NULL},
};
/******************************************************************************
*	Functions
******************************************************************************/
int btos(char *buf)
{
    int value = 0;

    value |= 0xFF000000 & (buf[3] << 24);
    value |= 0x00FF0000 & (buf[2] << 16);
    value |= 0x0000FF00 & (buf[1] << 8);
    value |= 0x000000FF & buf[0];

    return value;
}

int ButtonAnalysis(int fd,int num,ButtonParam_T *info)
{
	int j = 0;
	char buf[128] = {0};		
	if(num > 0)
	{
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,28);
			info[j].global = buf[0];
			memcpy(info[j].name,buf+1,6);
			info[j].pageId = buf[7];
			info[j].id = buf[8];
			info[j].x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j].y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j].width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j].height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j].level = buf[17];
			info[j].distype = buf[18];
			if(info[j].distype != 0)
			{
				info[j].fpic = (0x0000FF00 & (buf[20] << 8)) | (0x000000FF & buf[19]);
				info[j].bpic = (0x0000FF00 & (buf[22] << 8)) | (0x000000FF & buf[21]);
			}
			else
			{
				info[j].fpic = (0x0000FF00 & (buf[24] << 8)) | (0x000000FF & buf[23]);
				info[j].bpic = (0x0000FF00 & (buf[26] << 8)) | (0x000000FF & buf[25]);
			}
			
			info[j].txtlen = buf[27];
			if(info[j].txtlen > 0)
			{
				info[j].txt = (char *)malloc(sizeof(char) * info[j].txtlen);
				memset(info[j].txt,0,info[j].txtlen);
				read(fd,info[j].txt,info[j].txtlen);
                qDebug()<<"txt:"<<info[j].txt;
			}
			
			memset(buf,0,sizeof(buf));
			read(fd,buf,6);
			info[j].fontIndex = buf[0];
			info[j].txtColor = (0x0000FF00 & (buf[2] << 8)) | (0x000000FF & buf[1]);
			info[j].swType = buf[3];
			info[j].downlen = (0x0000FF00 & (buf[5] << 8)) | (0x000000FF & buf[4]);
			if(info[j].downlen > 0)
			{
				info[j].downcmd = (char *)malloc(sizeof(char) * info[j].downlen);
				memset(info[j].downcmd,0,info[j].downlen);
				read(fd,info[j].downcmd,info[j].downlen);
                qDebug()<<"downcmd:\n"<<info[j].downcmd;
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			
			info[j].uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j].uplen > 0)
			{
				info[j].upcmd = (char *)malloc(sizeof(char) * info[j].uplen);
				memset(info[j].upcmd,0,info[j].uplen);
				read(fd,info[j].upcmd,info[j].uplen);
                qDebug()<<"upcmd:\n"<<info[j].upcmd;
			}
		}
	}

    return 1;
}

int LabelAnalysis(int fd,int num,LabelParam_T *labelInfo)
{
	int j = 0;
	char buf[128] = {0};

	if(num > 0)
	{		
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,21);			
			labelInfo[j].global = buf[0];	
			memcpy(labelInfo[j].name,buf+1,6);
			labelInfo[j].pageId = buf[7];
			labelInfo[j].id = buf[8];	
			labelInfo[j].x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			labelInfo[j].y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			labelInfo[j].width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			labelInfo[j].height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			labelInfo[j].level = buf[17];
			labelInfo[j].distype = buf[18];
			labelInfo[j].txtlen = (0x0000FF00 & (buf[20] << 8)) | (0x000000FF & buf[19]);			
			if(labelInfo[j].txtlen > 0)
			{
				labelInfo[j].txt = (char *)malloc(sizeof(char) * labelInfo[j].txtlen);
				memset(labelInfo[j].txt,0,labelInfo[j].txtlen);
				read(fd,labelInfo[j].txt,labelInfo[j].txtlen);
				printf("[%s:%d] txt:%s\n",__FUNCTION__,__LINE__,labelInfo[j].txt);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,11);	
			labelInfo[j].fontIndex = buf[0];
			labelInfo[j].fpicorcol = (0x0000FF00 & (buf[2] << 8)) | (0x000000FF & buf[1]);
			if(labelInfo[j].distype != 0)
			{
				labelInfo[j].bpicorcol = (0x0000FF00 & (buf[4] << 8)) | (0x000000FF & buf[3]);
			}
			else
			{
				labelInfo[j].bpicorcol = (0x0000FF00 & (buf[6] << 8)) | (0x000000FF & buf[5]);
			}
			labelInfo[j].txtSpace = buf[7];
            labelInfo[j].align = (ENUM_ALIGNMODE)buf[8];
			labelInfo[j].downlen = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);			
			if(labelInfo[j].downlen > 0)
			{
				labelInfo[j].downcmd = (char *)malloc(sizeof(char) * labelInfo[j].downlen);
				memset(labelInfo[j].downcmd,0,labelInfo[j].downlen);
				read(fd,labelInfo[j].downcmd,labelInfo[j].downlen);
				qDebug()<<"downcmd:\n"<<labelInfo[j].downcmd;
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			labelInfo[j].uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(labelInfo[j].uplen > 0)
			{
				labelInfo[j].upcmd = (char *)malloc(sizeof(char) * labelInfo[j].uplen);
				memset(labelInfo[j].upcmd,0,labelInfo[j].uplen);
				read(fd,labelInfo[j].upcmd,labelInfo[j].uplen);
				qDebug()<<"upcmd:"<<labelInfo[j].upcmd;
			}
		}
	}

    return 1;
}

int ProgressBarAnalysis(int fd,int num,PgbarParam_T *info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,31);
			info[j].global = buf[0];
			memcpy(info[j].name,buf+1,6);
			info[j].pageId = buf[7];
			info[j].id = buf[8];
			info[j].x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j].y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j].width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j].height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j].level = buf[17];
			info[j].distype = buf[18];
			info[j].hov = buf[19];
			if(info[j].distype != 0)
			{
				info[j].fpic = (0x0000FF00 & (buf[21] << 8)) | (0x000000FF & buf[20]);
				info[j].bpic = (0x0000FF00 & (buf[23] << 8)) | (0x000000FF & buf[22]);
			}
			else
			{
				info[j].fpic = (0x0000FF00 & (buf[25] << 8)) | (0x000000FF & buf[24]);
				info[j].bpic = (0x0000FF00 & (buf[27] << 8)) | (0x000000FF & buf[26]);
			}
			
			info[j].percent = buf[28];
			info[j].downlen = (0x0000FF00 & (buf[30] << 8)) | (0x000000FF & buf[29]);
			if(info[j].downlen > 0)
			{
				info[j].downcmd = (char *)malloc(sizeof(char) * info[j].downlen);
				memset(info[j].downcmd,0,info[j].downlen);
				read(fd,info[j].downcmd,info[j].downlen);
				qDebug()<<"downcmd:"<<info[j].downcmd;
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j].uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j].uplen > 0)
			{
				info[j].upcmd = (char *)malloc(sizeof(char) * info[j].uplen);
				memset(info[j].upcmd,0,info[j].uplen);
				read(fd,info[j].upcmd,info[j].uplen);
				qDebug()<<"upcmd:"<<info[j].upcmd;
			}
		}
	}

    return 1;
}

int PanelAnalysis(int fd,int num,PanelParam_T *info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{		
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,30);
			info[j].global = buf[0];
			memcpy(info[j].name,buf+1,6);
			info[j].pageId = buf[7];
			info[j].id = buf[8];
			info[j].x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j].y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j].width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j].height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j].level = buf[17];
			info[j].distype = buf[18];
			info[j].fpicorcol = (0x0000FF00 & (buf[20] << 8)) | (0x000000FF & buf[19]);
			if(info[j].distype != 0)
			{
				info[j].bpicorcol = (0x0000FF00 & (buf[24] << 8)) | (0x000000FF & buf[23]);
			}
			else
			{
				info[j].bpicorcol = (0x0000FF00 & (buf[22] << 8)) | (0x000000FF & buf[21]);
			}
			
			info[j].linewidth = buf[25];
			info[j].angle = (0x0000FF00 & (buf[27] << 8)) | (0x000000FF & buf[26]);			
			info[j].downlen = (0x0000FF00 & (buf[29] << 8)) | (0x000000FF & buf[28]);
			if(info[j].downlen > 0)
			{
				info[j].downcmd = (char *)malloc(sizeof(char) * info[j].downlen);
				memset(info[j].downcmd,0,info[j].downlen);
				read(fd,info[j].downcmd,info[j].downlen);
				qDebug()<<"downcmd:"<<info[j].downcmd;
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j].uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j].uplen > 0)
			{
				info[j].upcmd = (char *)malloc(sizeof(char) * info[j].uplen);
				memset(info[j].upcmd,0,info[j].uplen);
				read(fd,info[j].upcmd,info[j].uplen);
				qDebug()<<"upcmd:"<<info[j].upcmd;
			}
		}
	}

    return 1;
}

int SliderAnalysis(int fd,int num,SlideParam_T *info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,38);
			info[j].global = buf[0];
			memcpy(info[j].name,buf+1,6);
			info[j].pageId = buf[7];
			info[j].id = buf[8];
			info[j].x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j].y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j].width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j].height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j].level = buf[17];
			info[j].hov = buf[18];
			info[j].distype = buf[19];
			if(info[j].distype != 0)
			{
				info[j].fpicorcol = (0x0000FF00 & (buf[25] << 8)) | (0x000000FF & buf[24]);
				info[j].bpicorcol = (0x0000FF00 & (buf[27] << 8)) | (0x000000FF & buf[26]);
			}
			else
			{
				info[j].fpicorcol = (0x0000FF00 & (buf[21] << 8)) | (0x000000FF & buf[20]);
				info[j].bpicorcol = (0x0000FF00 & (buf[23] << 8)) | (0x000000FF & buf[22]);
			}
			
			info[j].min = (0x0000FF00 & (buf[29] << 8)) | (0x000000FF & buf[28]);
			info[j].max = (0x0000FF00 & (buf[31] << 8)) | (0x000000FF & buf[30]);			
			info[j].value = (0x0000FF00 & (buf[33] << 8)) | (0x000000FF & buf[32]);
			info[j].wid = buf[34];
			info[j].hgt = buf[35];
			info[j].downlen = (0x0000FF00 & (buf[37] << 8)) | (0x000000FF & buf[36]);
			if(info[j].downlen > 0)
			{
				info[j].downcmd = (char *)malloc(sizeof(char) * info[j].downlen);
				memset(info[j].downcmd,0,info[j].downlen);
				read(fd,info[j].downcmd,info[j].downlen);
				qDebug()<<"downcmd:"<<info[j].downcmd;
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j].uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j].uplen > 0)
			{
				info[j].upcmd = (char *)malloc(sizeof(char) * info[j].uplen);
				memset(info[j].upcmd,0,info[j].uplen);
				read(fd,info[j].upcmd,info[j].uplen);
				qDebug()<<"upcmd:"<<info[j].upcmd;
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j].mvlen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j].mvlen > 0)
			{
				info[j].mvcmd = (char *)malloc(sizeof(char) * info[j].mvlen);
				memset(info[j].mvcmd,0,info[j].mvlen);
				read(fd,info[j].mvcmd,info[j].mvlen);
				qDebug()<<"mvcmd:"<<info[j].mvcmd;
			}
		}
	}

    return 1;
}

int RollLabelAnalysis(int fd,int num,RolllabelParam_T *info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,35);
			info[j].global = buf[0];
			memcpy(info[j].name,buf+1,6);
			info[j].pageId = buf[7];
			info[j].id = buf[8];
			info[j].x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j].y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j].width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j].height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j].level = buf[17];
			info[j].dir = buf[18];
			info[j].distype = buf[19];
			info[j].fpicorcol = (0x0000FF00 & (buf[21] << 8)) | (0x000000FF & buf[20]);
			if(info[j].distype != 0)
			{
				info[j].bpicorcol = (0x0000FF00 & (buf[25] << 8)) | (0x000000FF & buf[24]);
			}
			else
			{
				info[j].bpicorcol = (0x0000FF00 & (buf[23] << 8)) | (0x000000FF & buf[22]);
			}
			
			info[j].step = buf[26];
			info[j].period = (0x0000FF00 & (buf[28] << 8)) | (0x000000FF & buf[27]);	
			info[j].fontIndex = buf[29];
			info[j].enable = buf[30];
			info[j].align = (ENUM_ALIGNMODE)buf[31];
			info[j].txtSpace = buf[32];
			info[j].txtlen = (0x0000FF00 & (buf[34] << 8)) | (0x000000FF & buf[33]);	
			if(info[j].txtlen > 0)
			{
				info[j].txt = (char *)malloc(sizeof(char) * info[j].txtlen);
				memset(info[j].txt,0,info[j].txtlen);
				read(fd,info[j].txt,info[j].txtlen);
				printf("[%s:%d] txt:%s\n",__FUNCTION__,__LINE__,info[j].txt);
			}
		
			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j].downlen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j].downlen > 0)
			{
				info[j].downcmd = (char *)malloc(sizeof(char) * info[j].downlen);
				memset(info[j].downcmd,0,info[j].downlen);
				read(fd,info[j].downcmd,info[j].downlen);
				printf("[%s:%d] downcmd:%s\n",__FUNCTION__,__LINE__,info[j].downcmd);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j].uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j].uplen > 0)
			{
				info[j].upcmd = (char *)malloc(sizeof(char) * info[j].uplen);
				memset(info[j].upcmd,0,info[j].uplen);
				read(fd,info[j].upcmd,info[j].uplen);	
				printf("[%s:%d] upcmd:%s\n",__FUNCTION__,__LINE__,info[j].upcmd);
			}
		}
	}

	return 1;
}

int GraphAnalysis(int fd,int num,GraphParam_T *info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,39);
			info[j].global = buf[0];
			memcpy(info[j].name,buf+1,6);
			info[j].pageId = buf[7];
			info[j].id = buf[8];
			info[j].x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j].y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j].width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j].height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j].level = buf[17];
			info[j].distype = buf[18];
			if(info[j].distype != 0)
			{
				info[j].bpicorcol = (0x0000FF00 & (buf[22] << 8)) | (0x000000FF & buf[21]);
			}
			else
			{
				info[j].bpicorcol = (0x0000FF00 & (buf[20] << 8)) | (0x000000FF & buf[19]);
			}
			
			info[j].lor = buf[23];;
			info[j].gridcolor = (0x0000FF00 & (buf[25] << 8)) | (0x000000FF & buf[24]);			
			info[j].winterval = buf[26];
			info[j].hinterval = buf[27];
			info[j].channel = buf[28];
			info[j].channelcolor0 = (0x0000FF00 & (buf[30] << 8)) | (0x000000FF & buf[29]);
			info[j].channelcolor1 = (0x0000FF00 & (buf[32] << 8)) | (0x000000FF & buf[31]);
			info[j].channelcolor2 = (0x0000FF00 & (buf[34] << 8)) | (0x000000FF & buf[33]);
			info[j].channelcolor3 = (0x0000FF00 & (buf[36] << 8)) | (0x000000FF & buf[35]);
			info[j].downlen = (0x0000FF00 & (buf[38] << 8)) | (0x000000FF & buf[37]);
			if(info[j].downlen > 0)
			{
				info[j].downcmd = (char *)malloc(sizeof(char) * info[j].downlen);
				memset(info[j].downcmd,0,info[j].downlen);
				read(fd,info[j].downcmd,info[j].downlen);
				printf("[%s:%d] downcmd:%s\n",__FUNCTION__,__LINE__,info[j].downcmd);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j].uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j].uplen > 0)
			{
				info[j].upcmd = (char *)malloc(sizeof(char) * info[j].uplen);
				memset(info[j].upcmd,0,info[j].uplen);
				read(fd,info[j].upcmd,info[j].uplen);
				printf("[%s:%d] upcmd:%s\n",__FUNCTION__,__LINE__,info[j].upcmd);
			}
		}
	}

	return 1;
}

int RadioAnalysis(int fd,int num,RadioParam_T *info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,33);
			info[j].global = buf[0];
			memcpy(info[j].name,buf+1,6);
			info[j].pageId = buf[7];
			info[j].id = buf[8];
			info[j].x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j].y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j].width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j].height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j].level = buf[17];
			info[j].horv = buf[18];
			info[j].distype = buf[19];
			
			if(info[j].distype != 0)
			{
				info[j].fpicorcol = (0x0000FF00 & (buf[25] << 8)) | (0x000000FF & buf[24]);
				info[j].bpicorcol = (0x0000FF00 & (buf[27] << 8)) | (0x000000FF & buf[26]);
			}
			else
			{
				info[j].fpicorcol = (0x0000FF00 & (buf[21] << 8))| (0x000000FF & buf[20]);
				info[j].bpicorcol = (0x0000FF00 & (buf[23] << 8)) | (0x000000FF & buf[22]);
			}
			
			info[j].focusindex = buf[28];
			info[j].numofitem = buf[29];	
			info[j].distance = buf[30];
			info[j].downlen = (0x0000FF00 & (buf[32] << 8)) | (0x000000FF & buf[31]);
			if(info[j].downlen > 0)
			{
				info[j].downcmd = (char *)malloc(sizeof(char) * info[j].downlen);
				memset(info[j].downcmd,0,info[j].downlen);
				read(fd,info[j].downcmd,info[j].downlen);
				printf("[%s:%d] downcmd:%s\n",__FUNCTION__,__LINE__,info[j].downcmd);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j].uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j].uplen > 0)
			{
				info[j].upcmd = (char *)malloc(sizeof(char) * info[j].uplen);
				memset(info[j].upcmd,0,info[j].uplen);
				read(fd,info[j].upcmd,info[j].uplen);
				printf("[%s:%d] upcmd:%s\n",__FUNCTION__,__LINE__,info[j].upcmd);
			}
		}
	}

	return 1;
}

int CheckBoxAnalysis(int fd,int num,CheckBoxParam_T *info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,30);
			info[j].global = buf[0];
			memcpy(info[j].name,buf+1,6);
			info[j].pageId = buf[7];
			info[j].id = buf[8];
			info[j].x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j].y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j].width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j].height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j].level = buf[17];
			info[j].state = buf[18];
			info[j].distype = buf[19];
			
			if(info[j].distype != 0)
			{
				info[j].fpicorcol = (0x0000FF00 & (buf[25] << 8)) | (0x000000FF & buf[24]);
				info[j].bpicorcol = (0x0000FF00 & (buf[27] << 8)) | (0x000000FF & buf[26]);
			}
			else
			{
				info[j].fpicorcol = (0x0000FF00 & (buf[21] << 8)) | (0x000000FF & buf[20]);
				info[j].bpicorcol = (0x0000FF00 & (buf[23] << 8)) | (0x000000FF & buf[22]);
			}
			
			info[j].downlen = (0x0000FF00 & (buf[29] << 8)) | (0x000000FF & buf[28]);
			if(info[j].downlen > 0)
			{
				info[j].downcmd = (char *)malloc(sizeof(char) * info[j].downlen);
				memset(info[j].downcmd,0,info[j].downlen);
				read(fd,info[j].downcmd,info[j].downlen);
				printf("[%s:%d] downcmd:%s\n",__FUNCTION__,__LINE__,info[j].downcmd);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j].uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j].uplen > 0)
			{
				info[j].upcmd = (char *)malloc(sizeof(char) * info[j].uplen);
				memset(info[j].upcmd,0,info[j].uplen);
				read(fd,info[j].upcmd,info[j].uplen);
				printf("[%s:%d] upcmd:%s\n",__FUNCTION__,__LINE__,info[j].upcmd);
			}
		}
	}

	return 1;
}

int HotSpotAnalysis(int fd,int num,HotSpotParam_T *info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,20);
			info[j].global = buf[0];
			memcpy(info[j].name,buf+1,6);
			info[j].pageId = buf[7];
			info[j].id = buf[8];
			info[j].x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j].y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j].width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j].height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j].level = buf[17];
		
			info[j].downlen = (0x0000FF00 & (buf[19] << 8)) | (0x000000FF & buf[18]);
			if(info[j].downlen > 0)
			{
				info[j].downcmd = (char *)malloc(sizeof(char) * info[j].downlen);
				memset(info[j].downcmd,0,info[j].downlen);
				read(fd,info[j].downcmd,info[j].downlen);
				printf("[%s:%d] downcmd:%s\n",__FUNCTION__,__LINE__,info[j].downcmd);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j].uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j].uplen > 0)
			{
				info[j].upcmd = (char *)malloc(sizeof(char) * info[j].uplen);
				memset(info[j].upcmd,0,info[j].uplen);
				read(fd,info[j].upcmd,info[j].uplen);
				printf("[%s:%d] upcmd:%s\n",__FUNCTION__,__LINE__,info[j].upcmd);
			}
		}
	}

	return 1;
}

int TimerAnalysis(int fd,int num,TimerParam_T *info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,15);
			info[j].global = buf[0];
			memcpy(info[j].name,buf+1,6);
			info[j].pageId = buf[7];
			info[j].id = buf[8];			
			info[j].level = buf[9];
			info[j].period = (0x0000FF00 & (buf[11] << 8)) | (0x000000FF & buf[10]);
			info[j].enable = buf[12];
			info[j].eventlen = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			if(info[j].eventlen > 0)
			{
				info[j].event = (char *)malloc(sizeof(char) * info[j].eventlen);
				memset(info[j].event,0,info[j].eventlen);
				read(fd,info[j].event,info[j].eventlen);
				printf("[%s:%d] event:%s\n",__FUNCTION__,__LINE__,info[j].event);
			}
		}
	}

	return 1;
}

int VariableAnalysis(int fd,int num,VariableParam_T *info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,17);
			info[j].global = buf[0];
			memcpy(info[j].name,buf+1,6);
			info[j].pageId = buf[7];
			info[j].id = buf[8];			
			info[j].level = buf[9];
			info[j].vartype = buf[10];
			if(info[j].vartype != 0)
			{
				info[j].val = btos(buf+11);
				info[j].len = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
				if(info[j].len > 0)
				{
					info[j].text = (char *)malloc(sizeof(char) * info[j].len);
					memset(info[j].text,0,info[j].len);
					read(fd,info[j].text,info[j].len);
					printf("[%s:%d]:text:%s\n",__FUNCTION__,__LINE__,info[j].text);
				}
			}
			else
			{
				info[j].val = btos(buf+11);
				info[j].len = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			}
			
		}
	}

	return 1;
}

int PicAnalysis(int fd,int num,PicParam_T *info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,22);
			info[j].global = buf[0];
			memcpy(info[j].name,buf+1,6);
			info[j].pageId = buf[7];
			info[j].id = buf[8];
			info[j].x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j].y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j].width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j].height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j].level = buf[17];
			info[j].picIndex = (0x0000FF00 & (buf[19] << 8)) | (0x000000FF & buf[18]);
		
			info[j].downlen = (0x0000FF00 & (buf[21] << 8)) | (0x000000FF & buf[20]);
			if(info[j].downlen > 0)
			{
				info[j].downcmd = (char *)malloc(sizeof(char) * info[j].downlen);
				memset(info[j].downcmd,0,info[j].downlen);
				read(fd,info[j].downcmd,info[j].downlen);
				printf("[%s:%d] downcmd:%s\n",__FUNCTION__,__LINE__,info[j].downcmd);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j].uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j].uplen > 0)
			{
				info[j].upcmd = (char *)malloc(sizeof(char) * info[j].uplen);
				memset(info[j].upcmd,0,info[j].uplen);
				read(fd,info[j].upcmd,info[j].uplen);
				printf("[%s:%d] upcmd:%s\n",__FUNCTION__,__LINE__,info[j].upcmd);
			}
		}
	}

	return 1;
}

int CPicAnalysis(int fd,int num,CPicParam_T *info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,22);
			info[j].global = buf[0];
			memcpy(info[j].name,buf+1,6);
			info[j].pageId = buf[7];
			info[j].id = buf[8];
			info[j].x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j].y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j].width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j].height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j].level = buf[17];
			info[j].picIndex = (0x0000FF00 & (buf[19] << 8)) | (0x000000FF & buf[18]);
		
			info[j].downlen = (0x0000FF00 & (buf[21] << 8)) | (0x000000FF & buf[20]);
			if(info[j].downlen > 0)
			{
				info[j].downcmd = (char *)malloc(sizeof(char) * info[j].downlen);
				memset(info[j].downcmd,0,info[j].downlen);
				read(fd,info[j].downcmd,info[j].downlen);
				printf("[%s:%d] downcmd:%s\n",__FUNCTION__,__LINE__,info[j].downcmd);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j].uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j].uplen > 0)
			{
				info[j].upcmd = (char *)malloc(sizeof(char) * info[j].uplen);
				memset(info[j].upcmd,0,info[j].uplen);
				read(fd,info[j].upcmd,info[j].uplen);
				printf("[%s:%d] upcmd:%s\n",__FUNCTION__,__LINE__,info[j].upcmd);
			}
		}
	}

	return 1;
}

int CNumAnalysis(int fd,int num,CNumParam_T *info)
{
	int j = 0;
	char buf[128] = {0};
	
	if(num > 0)
	{
		for(j = 0;j < num;j++)
		{
			memset(buf,0,sizeof(buf));
			read(fd,buf,33);
			info[j].global = buf[0];
			memcpy(info[j].name,buf+1,6);
			info[j].pageId = buf[7];
			info[j].id = buf[8];
			info[j].x = (0x0000FF00 & (buf[10] << 8)) | (0x000000FF & buf[9]);
			info[j].y = (0x0000FF00 & (buf[12] << 8)) | (0x000000FF & buf[11]);
			info[j].width = (0x0000FF00 & (buf[14] << 8)) | (0x000000FF & buf[13]);
			info[j].height = (0x0000FF00 & (buf[16] << 8)) | (0x000000FF & buf[15]);
			info[j].level = buf[17];
			info[j].distype = buf[18];
			info[j].text = btos(buf+19);
			info[j].fontIndex = buf[23];
			info[j].fpicorcol = (0x0000FF00 & (buf[25] << 8)) | (0x000000FF & buf[24]);
			
			if(info[j].distype != 0)
			{				
				info[j].bpicorcol = (0x0000FF00 & (buf[27] << 8)) | (0x000000FF & buf[26]);
			}
			else
			{				
				info[j].bpicorcol = (0x0000FF00 & (buf[29] << 8)) | (0x000000FF & buf[28]);
			}
			info[j].align = (ENUM_ALIGNMODE)buf[30];
			info[j].downlen = (0x0000FF00 & (buf[32] << 8)) | (0x000000FF & buf[31]);
			if(info[j].downlen > 0)
			{
				info[j].downcmd = (char *)malloc(sizeof(char) * info[j].downlen);
				memset(info[j].downcmd,0,info[j].downlen);
				read(fd,info[j].downcmd,info[j].downlen);
				printf("[%s:%d] downcmd:%s\n",__FUNCTION__,__LINE__,info[j].downcmd);
			}

			memset(buf,0,sizeof(buf));
			read(fd,buf,2);
			info[j].uplen = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
			if(info[j].uplen > 0)
			{
				info[j].upcmd = (char *)malloc(sizeof(char) * info[j].uplen);
				memset(info[j].upcmd,0,info[j].uplen);
				read(fd,info[j].upcmd,info[j].uplen);	
				printf("[%s:%d] upcmd:%s\n",__FUNCTION__,__LINE__,info[j].upcmd);
			}
		}
	}

    return 1;
}

void SerialUtils::widget_proc(char *cmd,char *str,int num,void *data)
{

    int ret=-1;

    Shape *shape = nullptr;
    if(strcmp(cmd,"page")==0){

        pageData_S param = {0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d",&(param.id));

        emit signal_switchPage(param.id);

        return ;
    }else if(strcmp(cmd,"clean")==0){
        cleanData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d",&(param.color));

        emit signal_cleanPage(parse565(param.color));

        return ;
    }else if(strcmp(cmd,"point")==0){
        pointData_S param = {0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d,%d,%d",&(param.x),&(param.y),&(param.color));

        shape = new MPoint(param.x,param.y,parse565(param.color));



    }else if(strcmp(cmd,"line")==0){

        lineData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d,%d,%d,%d,%d",&(param.x1),&(param.y1),&(param.x2),&(param.y2),&(param.color));
        shape = new MLine(param.x1,param.y1,param.x2,param.y2,parse565(param.color));



    }else if(strcmp(cmd,"rect")==0){

        rectData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d,%d,%d,%d,%d",&(param.x),&(param.y),&(param.width),&(param.hight),&(param.color));

        shape = new MRect(param.x,param.y,param.x+param.width,param.y+param.hight,false,parse565(param.color));

    }else if(strcmp(cmd,"fillRect")==0){
        frectData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d,%d,%d,%d,%d",&(param.x),&(param.y),&(param.width),&(param.hight),&(param.color));

        shape = new MRect(param.x,param.y,param.x+param.width,param.y+param.hight,true,parse565(param.color));


    }else if(strcmp(cmd,"pie")==0){

        pieData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d,%d,%d,%d,%d,%d",&(param.x),&(param.y),&(param.radius),&(param.a0),&(param.a1),&(param.color));

        shape = new MArc(param.x,param.y,param.radius,param.a0,param.a1,parse565(param.color),true);


    }else if(strcmp(cmd,"arc")==0){
        arcData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d,%d,%d,%d,%d,%d,%d",&(param.x),&(param.y),&(param.radius),&(param.a0),&(param.a1),&(param.pensize),&(param.color));


        shape = new MArc(param.x,param.y,param.radius,param.a0,param.a1,parse565(param.color),false);


    }else if(strcmp(cmd,"circle")==0){
        cirData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d,%d,%d,%d",&(param.x),&(param.y),&(param.radius),&(param.color));

        shape = new MArc(param.x,param.y,param.radius,0,360,parse565(param.color),false);

    }else if(strcmp(cmd,"fillCircle")==0){
        fcirData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d,%d,%d,%d",&(param.x),&(param.y),&(param.radius),&(param.color));
        shape = new MArc(param.x,param.y,param.radius,0,360,parse565(param.color),true);


    }else if(strcmp(cmd,"picture")==0){

        picData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d,%d,%d",&(param.x),&(param.y),&(param.id));

        QImage img(ResourcesManager::getInstance()->getImageAbsolutePath(param.id));
        shape = new MImage(param.x,param.y,img.width(),img.height(),0,img);


    }else if(strcmp(cmd,"cutChart")==0){
        piccData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d,%d,%d,%d,%d",&(param.x),&(param.y),&(param.width),&(param.hight),&(param.id));


    }else if(strcmp(cmd,"str")==0){

        strData_S param={0};
        memset(&param,0,sizeof(param));

        ret=sscanf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%s",\
                   &(param.x),&(param.y),&(param.width),&(param.hight),\
                   &(param.fontindex),&(param.alignment),&(param.Usebackcolor),\
                   &(param.fcolor),&(param.bcolor),\
                   &(param.str));


        QFont font(ResourcesManager::getInstance()->getFontFamily(param.fontindex));
        shape = new MText(param.x,param.y,param.x+param.width,param.y+param.hight,param.str,font,
                          parse565(param.fcolor),
                          parseAlignment(param.alignment),
                          param.Usebackcolor>0,
                          parse565(param.bcolor));

    }/*else if(strcmp(cmd,"refresh")==0){
        refData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%s",&(param.name));


        emit signal_process_cmd(param.name,cmd,str);
        return;
    }else if(strcmp(cmd,"click")==0){
        clickData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%[^,],%d",&(param.name),&(param.event));

        emit signal_process_cmd(param.name,cmd,str);
        return;

    }else if(strcmp(cmd,"echo")==0){
        ecohData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d",&(param.name));

    }else if(strcmp(cmd,"echon")==0){
        ecohnData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d,%d",&(param.name),&(param.n));

    }else if(strcmp(cmd,"hide")==0){
        hideData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%[^,],%d",&(param.name),&(param.state));

    }else if(strcmp(cmd,"show")==0){
        showData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%[^,],%d",&(param.name),&(param.state));

    }else if(strcmp(cmd,"re")==0){
        reData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d",&(param.en));

    }else if(strcmp(cmd,"curveAddData")==0){
        addnData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%[^,],%d,%d",&(param.name),&(param.channel),&(param.num));


    }else if(strcmp(cmd,"curveAdd")==0){

        addData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%[^,],%d,%d",&(param.name),&(param.channel),&(param.data));
    }else if(strcmp(cmd,"curveDelete")==0){

        delData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%[^,],%d",&(param.name),&(param.channel));

    }else if(strcmp(cmd,"calTouch")==0){


    }else if(strcmp(cmd,"reset")==0){


    }else if(strcmp(cmd,"baudRate")==0){
        baudData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d",&(param.baud));

    }else if(strcmp(cmd,"lightAdjust")==0){

        dimData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d",&(param.val)  );
    }else if(strcmp(cmd,"rand")==0){
        randData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d",&(param.val));

    }else if(strcmp(cmd,"strLen")==0){
        slenData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%[^,],%d",&(param.name),&(param.val));

    }else if(strcmp(cmd,"strCopy")==0){
        scopyData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%[^,],%[^,]",&(param.dst),&(param.src));

    }else if(strcmp(cmd,"numCopy")==0){
        sncopyData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%[^,],%[^,],%d",&(param.dst),&(param.src),&(param.num));

    }else if(strcmp(cmd,"sleep")==0){
        sleepData_S param={0};
        memset(&param,0,sizeof(param));
        ret=sscanf(str,"%d",&(param.state)  );

    }*/else{


        emit signal_process_cmd(cmd,str);
        return;
    }


    if(shape != nullptr)
        emit signal_addShape(shape);
}




//页面
int page_proc(char *str,int num,void *data)
{
    int ret=-1;
    pageData_S param = {0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d",&(param.id));
    //printf("[%s:%d]:%d :%d\r\n",__FUNCTION__,__LINE__,ret,(param.id));


    return ret;
}

int clean_proc(char *str,int num,void *data)
{
    int ret=-1;
    cleanData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d",&(param.color));
    printf("[%s:%d]:%d :%d\r\n",__FUNCTION__,__LINE__,ret,(param.color));
    return ret;
}

int point_proc(char *str,int num,void *data)
{
    int ret=-1;
    pointData_S param = {0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d,%d,%d",&(param.x),&(param.y),&(param.color));
    printf("[%s:%d]:%d :%d %d %d\r\n",__FUNCTION__,__LINE__,ret,(param.x),(param.y),(param.color));
    return ret;
}

int line_proc(char *str,int num,void *data)
{
    int ret=-1;
    lineData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d,%d,%d,%d,%d",&(param.x1),&(param.y1),&(param.x2),&(param.y2),&(param.color));
    printf("[%s:%d]:%d :(%d, %d :%d ,%d) %d\r\n",__FUNCTION__,__LINE__,ret,(param.x1),(param.y1),(param.x2),(param.y2),(param.color));
    return ret;
}

int rect_proc(char *str,int num,void *data)
{
    int ret=-1;
    rectData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d,%d,%d,%d,%d",&(param.x),&(param.y),&(param.width),&(param.hight),&(param.color));
    printf("[%s:%d]:%d :(%d, %d :%d ,%d) %d\r\n",__FUNCTION__,__LINE__,ret,(param.x),(param.y),(param.width),(param.hight),(param.color));
    return ret;
}

int frect_proc(char *str,int num,void *data)
{
    int ret=-1;
    frectData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d,%d,%d,%d,%d",&(param.x),&(param.y),&(param.width),&(param.hight),&(param.color));
    printf("[%s:%d]:%d :(%d, %d :%d ,%d) %d\r\n",__FUNCTION__,__LINE__,ret,(param.x),(param.y),(param.width),(param.hight),(param.color));
    return ret;
}

int pie_proc(char *str,int num,void *data)
{
    int ret=-1;
    pieData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d,%d,%d,%d,%d,%d",&(param.x),&(param.y),&(param.radius),&(param.a0),&(param.a1),&(param.color));
    printf("[%s:%d]:%d :(%d, %d ,%d:%d ,%d ,%d)\r\n",__FUNCTION__,__LINE__,ret,(param.x),(param.y),(param.radius),(param.a0),(param.a1),(param.color));
    return ret;
}

int arc_proc(char *str,int num,void *data)
{
    int ret=-1;
    arcData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d,%d,%d,%d,%d,%d,%d",&(param.x),&(param.y),&(param.radius),&(param.a0),&(param.a1),&(param.pensize),&(param.color));
    printf("[%s:%d]:%d :(%d, %d ,%d:%d ,%d ,%d,%d)\r\n",__FUNCTION__,__LINE__,ret,(param.x),(param.y),(param.radius),(param.a0),(param.a1),(param.pensize),(param.color));
    return ret;
}

int cir_proc(char *str,int num,void *data)
{
    int ret=-1;
    cirData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d,%d,%d,%d",&(param.x),&(param.y),&(param.radius),&(param.color));
    printf("[%s:%d]:%d :(%d, %d :%d  %d)\r\n",__FUNCTION__,__LINE__,ret,(param.x),(param.y),(param.radius),(param.color));
    return ret;
}

int fcir_proc(char *str,int num,void *data)
{
    int ret=-1;
    fcirData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d,%d,%d,%d",&(param.x),&(param.y),&(param.radius),&(param.color));
    printf("[%s:%d]:%d :(%d, %d :%d  %d)\r\n",__FUNCTION__,__LINE__,ret,(param.x),(param.y),(param.radius),(param.color));
    return ret;
}

int pic_proc(char *str,int num,void *data)
{
    int ret=-1;
    picData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d,%d,%d",&(param.x),&(param.y),&(param.id));
    printf("[%s:%d]:%d :(%d, %d :%d )\r\n",__FUNCTION__,__LINE__,ret,(param.x),(param.y),(param.id));
    return ret;
}

int picc_proc(char *str,int num,void *data)
{
    int ret=-1;
    piccData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d,%d,%d,%d,%d",&(param.x),&(param.y),&(param.width),&(param.hight),&(param.id));
    printf("[%s:%d]:%d :(%d, %d %d, %d :%d )\r\n",__FUNCTION__,__LINE__,ret,(param.x),(param.y),(param.width),(param.hight),(param.id));
    return ret;
}

int str_proc(char *str,int num,void *data)
{
    int ret=-1;
    strData_S param={0};
    memset(&param,0,sizeof(param));

    ret=sscanf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%s",\
               &(param.x),&(param.y),&(param.width),&(param.hight),\
               &(param.fontindex),&(param.alignment),&(param.Usebackcolor),\
               &(param.fcolor),&(param.bcolor),\
               &(param.str));
    printf("[%s:%d]:%d :%d,%d,%d,%d;%d,%d,%d;%d,%d;%s\r\n",__FUNCTION__,__LINE__,ret,\
           (param.x),(param.y),(param.width),(param.hight),\
           (param.fontindex),(param.alignment),(param.Usebackcolor),\
           (param.fcolor),(param.bcolor),\
           (param.str));
    return ret;
}

int ref_proc(char *str,int num,void *data)
{
    int ret=-1;
    refData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%s",&(param.name));
    printf("[%s:%d]:%d :%s\r\n",__FUNCTION__,__LINE__,ret,(param.name));
    return ret;
}

int click_proc(char *str,int num,void *data)
{
    int ret=-1;
    clickData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%[^,],%d",&(param.name),&(param.event));
    printf("[%s:%d]:%d :%s %d \r\n",__FUNCTION__,__LINE__,ret,(param.name),(param.event));
    return ret;
}

int ecoh_proc(char *str,int num,void *data)
{
    int ret=-1;
    ecohData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d",&(param.name));
    printf("[%s:%d]:%d :(%d )\r\n",__FUNCTION__,__LINE__,ret,(param.name) );
    return ret;
}

int ecohn_proc(char *str,int num,void *data)
{
    int ret=-1;
    ecohnData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d,%d",&(param.name),&(param.n));
    printf("[%s:%d]:%d :(%d ,%d )\r\n",__FUNCTION__,__LINE__,ret,(param.name),(param.n) );
    return ret;
}

int hide_proc(char *str,int num,void *data)
{
    int ret=-1;
    hideData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%[^,],%d",&(param.name),&(param.state));
    printf("[%s:%d]:%d :%s %d \r\n",__FUNCTION__,__LINE__,ret,(param.name),(param.state));
    return ret;
}

int show_proc(char *str,int num,void *data)
{
    int ret=-1;
    showData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%[^,],%d",&(param.name),&(param.state));
    printf("[%s:%d]:%d :%s %d \r\n",__FUNCTION__,__LINE__,ret,(param.name),(param.state));
    return ret;
}

int re_proc(char *str,int num,void *data)
{
    int ret=-1;
    reData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d",&(param.en));
    printf("[%s:%d]:%d :(%d )\r\n",__FUNCTION__,__LINE__,ret,(param.en));
    return ret;
}

int addn_proc(char *str,int num,void *data)
{
    int ret=-1;
    addnData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%[^,],%d,%d",&(param.name),&(param.channel),&(param.num));
    printf("[%s:%d]:%d :%s %d %d\r\n",__FUNCTION__,__LINE__,ret,(param.name),(param.channel),(param.num));

    return ret;
}

int add_proc(char *str,int num,void *data)
{
    int ret=-1;
    addData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%[^,],%d,%d",&(param.name),&(param.channel),&(param.data));
    printf("[%s:%d]:%d :%s %d %d \r\n",__FUNCTION__,__LINE__,ret,(param.name),(param.channel),(param.data));
    return ret;
}

int del_proc(char *str,int num,void *data)
{
    int ret=-1;
    delData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%[^,],%d",&(param.name),&(param.channel));
    printf("[%s:%d]:%d :%s %d \r\n",__FUNCTION__,__LINE__,ret,(param.name),(param.channel));
    return ret;
}

int cal_proc(char *str,int num,void *data)
{
    return 0;
}

int reset_proc(char *str,int num,void *data)
{
    return 0;
}

int baud_proc(char *str,int num,void *data)
{
    int ret=-1;
    baudData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d",&(param.baud));
    printf("[%s:%d]:%d :(%d )\r\n",__FUNCTION__,__LINE__,ret,(param.baud));
    return ret;
}

int dim_proc(char *str,int num,void *data)
{
    int ret=-1;
    dimData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d",&(param.val)  );
    printf("[%s:%d]:%d :(%d )\r\n",__FUNCTION__,__LINE__,ret,(param.val) );
    return ret;
}

int rand_proc(char *str,int num,void *data)
{
    int ret=-1;
    randData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d",&(param.val));
    printf("[%s:%d]:%d :(%d )\r\n",__FUNCTION__,__LINE__,ret,(param.val));
    return ret;
}

int slen_proc(char *str,int num,void *data)
{
    int ret=-1;
    slenData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%[^,],%d",&(param.name),&(param.val));
    printf("[%s:%d]:%d :%s %d \r\n",__FUNCTION__,__LINE__,ret,(param.name),(param.val));
    return ret;
}

int scopy_proc(char *str,int num,void *data)
{
    int ret=-1;
    scopyData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%[^,],%[^,]",&(param.dst),&(param.src));
    printf("[%s:%d]:%d :%s %s  \r\n",__FUNCTION__,__LINE__,ret,(param.dst),(param.src));
    return ret;
}

int sncopy_proc(char *str,int num,void *data)
{
    int ret=-1;
    sncopyData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%[^,],%[^,],%d",&(param.dst),&(param.src),&(param.num));
    printf("[%s:%d]:%d :%s %s %d \r\n",__FUNCTION__,__LINE__,ret,(param.dst),(param.src),(param.num));
    return ret;
}

int sleep_proc(char *str,int num,void *data)
{
    int ret=-1;
    sleepData_S param={0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d",&(param.state)  );
    printf("[%s:%d]:%d :(%d )\r\n",__FUNCTION__,__LINE__,ret,(param.state) );
    return ret;
}

int SerialUtils::cmdproc(char *str)
{
    int i;
    char cmdstr[64]={0};
    int ret=-1;
    char *pParam=NULL;

    memset(cmdstr,0x0,sizeof(cmdstr));
    ret=sscanf(str,"%s ",&cmdstr);
    printf("[%s:%d]:cmdstr=%s,ret = %d,len=%d\r\n",__FUNCTION__,__LINE__,cmdstr,ret,strlen(cmdstr));
    if(ret == 1)
    {
        for(i=0;i<sizeof(cmdProcTbl)/sizeof(cmdProcTbl[0]);i++)
        {
            if(cmdProcTbl[i].cmdid>0)
            {
                if(!strcmp(cmdProcTbl[i].cmd,cmdstr))
                {

                    // printf("[%s:%d]:pParam=%s!cmd = %s,cmdproc = %p\r\n",__FUNCTION__,__LINE__,pParam,cmdProcTbl[i].cmd,cmdProcTbl[i].cmdproc);
                    qDebug()<<"cmd:"<<cmdProcTbl[i].cmd;

                    pParam=str+strlen(cmdProcTbl[i].cmd)+1;
                    ret=cmdProcTbl[i].cmdproc(pParam,cmdProcTbl[i].num,NULL);
                    widget_proc(cmdProcTbl[i].cmd,pParam,cmdProcTbl[i].num,NULL);
                    break;
                }
            }
        }
    }

    return ret;
}	

static int findHead(char *str,int *len)
{
    int i = 0;
    int buflen = *len;
    char buf[128];

    memset(buf,0,sizeof(buf));
    memcpy(buf,str,buflen);
    for(i= 0;i < buflen;i++)
    {
        if(buf[i] == 0x01 || buf[i] == 0x02)
        {
            memcpy(str,buf+i+1,buflen); //去掉头
            *len = buflen - (i + 1);
            return 1;
        }
    }

    return 0;
}

static int findTrail(char *str,int len,int *posit)
{
    int i = 0;

    for(i= 0;i < len;i++)
    {
        if(str[i] == 0x0b)
        {
            *posit = i;
            return 1;
        }
    }

    return 0;
}



SerialUtils::SerialUtils(QObject *parent) : QObject(parent)
{

}

int SerialUtils::ParseSerialInt()
{
    memset(&serParam,0,sizeof(serialParam_T));
    memset(serParam.buf,0,sizeof(serParam.buf));
    return 0;
}

int ParseSerialSend(char *s_buf,int len)
{
    //tty_send(s_buf,len);
    return 0;
}




int SerialUtils::ParseSerialComm(char *str,int len)
{
    int ret = -1;
    int endPosit = 0;
    char sendbuf[512];
    int sendlen;

    if(serParam.headflag == 0 && serParam.loadflag == 0) //不是下载模式
    {
        if(findHead(str,&len) == 1) //find head
        {
            serParam.headflag = 1;
            qDebug()<<"find head";
        }
        else
        {
            return -1;
        }
    }
    else if(serParam.loadflag == 1)
    {
        if(str[0] == 0x80) //80 EF CD 20 1C
        {
            int binlen;
            int speed;

            binlen = btos(str + 1);
            speed = btos(str + 5);

            //printf("[%s:%d]:binlen:0x%x,speed:0x%x!!!",__FUNCTION__,__LINE__,binlen,speed);

            qDebug()<<"111";
            memset(sendbuf,0,sizeof(sendbuf));
            sendbuf[0] = 0x81;
            sendlen = 1;
            ParseSerialSend(sendbuf,sendlen);
        }
    }


    if(len > 0)
    {
        if(findTrail(str,len,&endPosit) == 1) //find trail
        {
            qDebug()<<"find trail";
            serParam.trailflag = 1;
            memcpy(serParam.buf+serParam.posit,str,endPosit);//0xb 结束符不拷贝
            serParam.posit += endPosit;
            //printf("[%s:%d]:serParam.buf:%s!!!\n",__FUNCTION__,__LINE__,serParam.buf);
            if(!strcmp("load",serParam.buf)) //02 6C 6F 61 64 0B
            {
                qDebug()<<("start to load data!!!!\n");
                memset(sendbuf,0,sizeof(sendbuf));
                sprintf(sendbuf,"%s,%s,%s,%s,%s","t1","320*480","h1","f030","64");
                sendlen = strlen(sendbuf);
                ParseSerialSend(sendbuf,sendlen);
                ParseSerialSend("rst",3);
                serParam.loadflag = 1;
            }
            else
            {
                cmdproc(serParam.buf);
                memset(&serParam,0,sizeof(serialParam_T));
                memset(serParam.buf,0,sizeof(serParam.buf));
                if(len - (endPosit + 1) > 0) //0xb 结束符要减去
                {
                    memcpy(serParam.buf+serParam.posit,str+endPosit,len - endPosit);
                    ParseSerialComm(serParam.buf,len-endPosit);
                }
            }
        }
        else
        {
            memcpy(serParam.buf+serParam.posit,str,len);
            serParam.posit += len;
        }
    }

    return 0;
}

int SerialUtils::analysisBin()
{
    int fd = 0;
    fd = open("H:/dmjProgram/qtPro/LKdata.bin", O_RDWR|O_BINARY); //串口接收bin文件到一个固定的位置或者SD卡拷贝到固定路径



    qDebug()<<"fd:"<<fd;
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
    //printf("[%s:%d]:direction:%d,imageNum:%d,fontNum:%d,pageNum:%d\n",__FUNCTION__,__LINE__,direction,imageInfo.imageNum,fontInfo.fontNum,pageInfo.pageNum);


    ResourcesManager *resourcesManager = ResourcesManager::getInstance();
    qDebug()<<"imageNum:"<<imageInfo.imageNum;
    if(imageInfo.imageNum > 0)
    {
        imageInfo.image = (ImageInfo_T *)malloc(sizeof(ImageInfo_T) * imageInfo.imageNum);
        memset(buf,0,sizeof(buf));
        read(fd,buf,4*imageInfo.imageNum); //图片地址

        for(i = 0;i < imageInfo.imageNum;i++)
        {
            imageInfo.image[i].addr = btos(buf+4*i);
            imageInfo.image[i].index = i;
            //printf("[%s:%d]:imageAddr[%d]:0x%x\n",__FUNCTION__,__LINE__,i,imageInfo.image[i].addr);
        }
    }

    qDebug()<<"fontNum:"<<fontInfo.fontNum;
    if(fontInfo.fontNum > 0)
    {
        fontInfo.font = (FontInfo_T *)malloc(sizeof(FontInfo_T) * fontInfo.fontNum);
        memset(buf,0,sizeof(buf));
        read(fd,buf,4*fontInfo.fontNum); //字库地址
        for(i = 0;i < fontInfo.fontNum;i++)
        {
            fontInfo.font[i].addr = btos(buf+4*i);
            //printf("[%s:%d]:fontAddr[%d]:0x%x\n",__FUNCTION__,__LINE__,i,fontInfo.font[i].addr);
        }
    }

    qDebug()<<"pageNum:"<<pageInfo.pageNum;
    if(pageInfo.pageNum > 0)
    {
        pageInfo.page = (PageInfo_T *)malloc(sizeof(PageInfo_T)*pageInfo.pageNum);
        memset(buf,0,sizeof(buf));
        read(fd,buf,4*pageInfo.pageNum); //页面地址
        for(i = 0;i < pageInfo.pageNum;i++)
        {
            pageInfo.page[i].addr = btos(buf+4*i);
            pageInfo.page[i].index = i;
            //printf("[%s:%d]:pageAddr[%d]:0x%x\n",__FUNCTION__,__LINE__,i,pageInfo.page[i].addr);


            emit signal_addPage(pageInfo.page[i].index,"");
        }
    }



    //开始读取图片头数据(8位) + 图片数据
    qDebug()<<"save image file: "<<imageInfo.imageNum;
    for(i = 0;i < imageInfo.imageNum;i++)
    {
        memset(buf,0,sizeof(buf));
        read(fd,buf,3);
        //printf("[%s:%d]:buf:%s\n",__FUNCTION__,__LINE__,buf);
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
                    //					FILE *file = NULL;
                    //					file= fopen("./iamge0", "w+");
                    //					fwrite(imageInfo.image[i].data,1,imageInfo.image[i].width * imageInfo.image[i].height*2,file);
                    //					fclose(file);


                    resourcesManager->saveImage(
                                imageInfo.image[i].index,
                                imageInfo.image[i].width,
                                imageInfo.image[i].height,
                                0,
                                imageInfo.image[i].data
                                );
                    //  emit signal_saveFontFile(imageInfo.image[i].index,imageInfo.image[i].width,imageInfo.image[i].height,0,imageInfo.image[i].data);
                }
            }
        }
    }

    //开始读取字体头数据(8位) + 字体数据

    qDebug()<<"save font file: "<<fontInfo.fontNum;
    int fontsize = 0;
    for(i = 0;i < fontInfo.fontNum;i++)
    {
        memset(buf,0,sizeof(buf));
        read(fd,buf,4);
        fontInfo.font[i].index = btos(buf);
        //printf("[%s:%d]:font[%d].index:0x%x\n",__FUNCTION__,__LINE__,i,fontInfo.font[i].index);

        memset(buf,0,sizeof(buf));
        read(fd,buf,4);

        fontInfo.font[i].width = (0x0000FF00 & (buf[1] << 8)) | (0x000000FF & buf[0]);
        fontInfo.font[i].height = (0x0000FF00 & (buf[3] << 8)) | (0x000000FF & buf[2]);
        //printf("[%s:%d]:width:0x%x,height:0x%x\n",__FUNCTION__,__LINE__,fontInfo.font[i].width,fontInfo.font[i].height);
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

        resourcesManager->saveFont(fontInfo.font[i].index,
                                   fontInfo.font[i].data,
                                   fontsize);
    }


    qDebug()<<"pageNum:"<<pageInfo.pageNum;
    //开始读取页面头数据(8位) + 页面数据
    for(i = 0;i < pageInfo.pageNum;i++)
    {
        memset(pageInfo.page[i].objname,0,sizeof(pageInfo.page[i].objname));
        read(fd,pageInfo.page[i].objname,9);
        // qDebug<("[%s:%d]:objname:%s\n",__FUNCTION__,__LINE__,pageInfo.page[i].objname);
        qDebug()<<"page id:"<<pageInfo.page[i].index;
        memset(buf,0,sizeof(buf));
        read(fd,buf,4);
        QByteArray arr;
        arr.append(buf,4);

        qDebug()<<"buff:"<<arr.toHex();
        if(!strcmp("PAGE",buf))
        {

            memset(buf,0,sizeof(buf));
            read(fd,buf,2);
            pageInfo.page[i].global = buf[0];
            pageInfo.page[i].picornot = buf[1];
            //printf("[%s:%d]:page[%d]:global:%d,picornot:%d\n",__FUNCTION__,__LINE__,i,pageInfo.page[i].global,pageInfo.page[i].picornot);
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
            //printf("[%s:%d]:page[%d]:bcOrpi:0x%x\n",__FUNCTION__,__LINE__,i,pageInfo.page[i].bcOrpi);
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

			pageInfo.page[i].buttonInfo = (ButtonParam_T *)malloc(sizeof(ButtonParam_T) * pageInfo.page[i].buttonNum);
			ButtonAnalysis(fd,pageInfo.page[i].buttonNum,pageInfo.page[i].buttonInfo);

            //qDebug()<<"buttonNum:"<<pageInfo.page[i].buttonNum;

            for(j = 0;j < pageInfo.page[i].buttonNum;j++)
            {
                addButton(i,&pageInfo.page[i].buttonInfo[j]);

            }

			pageInfo.page[i].labelInfo = (LabelParam_T *)malloc(sizeof(LabelParam_T) * pageInfo.page[i].labelNum);
            LabelAnalysis(fd,pageInfo.page[i].labelNum,pageInfo.page[i].labelInfo);
            //qDebug()<<"labelNum:"<<pageInfo.page[i].labelNum;
            for(j = 0;j < pageInfo.page[i].labelNum;j++)
            {

                addLabel(i,&pageInfo.page[i].labelInfo[j]);

            }

			pageInfo.page[i].pgbarInfo = (PgbarParam_T *)malloc(sizeof(PgbarParam_T) * pageInfo.page[i].pgbarNum);
			ProgressBarAnalysis(fd,pageInfo.page[i].pgbarNum,pageInfo.page[i].pgbarInfo);
            //qDebug()<<"pgbarNum:"<<pageInfo.page[i].pgbarNum;
            for(j = 0;j < pageInfo.page[i].pgbarNum;j++)
            {

                addPgbar(i,&pageInfo.page[i].pgbarInfo[j]);

            }

			pageInfo.page[i].panelInfo = (PanelParam_T *)malloc(sizeof(PanelParam_T) * pageInfo.page[i].panelNum);
			PanelAnalysis(fd,pageInfo.page[i].panelNum,pageInfo.page[i].panelInfo);
            //qDebug()<<"panelNum:"<<pageInfo.page[i].panelNum;
            for(j = 0;j < pageInfo.page[i].panelNum;j++)
            {

                addPanel(i,&pageInfo.page[i].panelInfo[j]);
            }

			pageInfo.page[i].slideInfo = (SlideParam_T *)malloc(sizeof(SlideParam_T) * pageInfo.page[i].slideNum);
			SliderAnalysis(fd,pageInfo.page[i].slideNum,pageInfo.page[i].slideInfo);
            //qDebug()<<"slideNum:"<<pageInfo.page[i].slideNum;
            for(j = 0;j < pageInfo.page[i].slideNum;j++)
            {


                addSlide(i,&pageInfo.page[i].slideInfo[j]);

            }
			
			pageInfo.page[i].rolllableInfo = (RolllabelParam_T *)malloc(sizeof(RolllabelParam_T) * pageInfo.page[i].rolllabelNum);
			RollLabelAnalysis(fd,pageInfo.page[i].rolllabelNum,pageInfo.page[i].rolllableInfo);
            qDebug()<<"rolllableInfo:"<<pageInfo.page[i].rolllableInfo;
            for(j = 0;j < pageInfo.page[i].rolllabelNum;j++)
            {

                addRolllabel(i,&pageInfo.page[i].rolllableInfo[j]);

            }

			pageInfo.page[i].graphInfo = (GraphParam_T *)malloc(sizeof(GraphParam_T) * pageInfo.page[i].graphNum);
			GraphAnalysis(fd,pageInfo.page[i].graphNum,pageInfo.page[i].graphInfo);
            //qDebug()<<"graphNum:"<<pageInfo.page[i].graphNum;
            for(j = 0;j < pageInfo.page[i].graphNum;j++)
            {
                addGraph(i,&pageInfo.page[i].graphInfo[j]);
            }

			pageInfo.page[i].radioInfo = (RadioParam_T *)malloc(sizeof(RadioParam_T) * pageInfo.page[i].radioNum);
			RadioAnalysis(fd,pageInfo.page[i].radioNum,pageInfo.page[i].radioInfo);
            //qDebug()<<"radioNum:"<<pageInfo.page[i].radioNum;
            for(j = 0;j < pageInfo.page[i].radioNum;j++)
            {

                addRadio(i,&pageInfo.page[i].radioInfo[j]);
            }

			pageInfo.page[i].checkboxInfo = (CheckBoxParam_T *)malloc(sizeof(CheckBoxParam_T) * pageInfo.page[i].checkboxNum);
			CheckBoxAnalysis(fd,pageInfo.page[i].checkboxNum,pageInfo.page[i].checkboxInfo);
            //qDebug()<<"checkboxNum:"<<pageInfo.page[i].checkboxNum;
            for(j = 0;j < pageInfo.page[i].checkboxNum;j++)
            {

                addCheckBox(i,&pageInfo.page[i].checkboxInfo[j]);
            }

			pageInfo.page[i].hotspotInfo = (HotSpotParam_T *)malloc(sizeof(HotSpotParam_T) * pageInfo.page[i].hotspotNum);
			HotSpotAnalysis(fd,pageInfo.page[i].hotspotNum,pageInfo.page[i].hotspotInfo);
            // qDebug()<<"hotspotNum:"<<pageInfo.page[i].hotspotNum;
            for(j = 0;j < pageInfo.page[i].hotspotNum;j++)
            {
                addHotSpot(i,&pageInfo.page[i].hotspotInfo[j]);
            }

			pageInfo.page[i].timerInfo = (TimerParam_T *)malloc(sizeof(TimerParam_T) * pageInfo.page[i].timerNum);
			TimerAnalysis(fd,pageInfo.page[i].timerNum,pageInfo.page[i].timerInfo);
            //qDebug()<<"timerNum:"<<pageInfo.page[i].timerNum;
            for(j = 0;j < pageInfo.page[i].timerNum;j++)
            {
                addTimer(i,&pageInfo.page[i].timerInfo[j]);
            }

			pageInfo.page[i].variableInfo = (VariableParam_T *)malloc(sizeof(VariableParam_T) * pageInfo.page[i].variableNum);
			VariableAnalysis(fd,pageInfo.page[i].variableNum,pageInfo.page[i].variableInfo);
            //qDebug()<<"variableNum:"<<pageInfo.page[i].variableNum;
            for(j = 0;j < pageInfo.page[i].variableNum;j++)
            {
                addVariable(i,&pageInfo.page[i].variableInfo[j]);
            }

			pageInfo.page[i].picInfo = (PicParam_T *)malloc(sizeof(PicParam_T) * pageInfo.page[i].picNum);
            PicAnalysis(fd,pageInfo.page[i].picNum,pageInfo.page[i].picInfo);
            qDebug()<<"picNum:"<<pageInfo.page[i].picNum;
            for(j = 0;j < pageInfo.page[i].picNum;j++)
            {
                addPic(i,&pageInfo.page[i].picInfo[j]);
            }

			pageInfo.page[i].cpicInfo = (CPicParam_T *)malloc(sizeof(CPicParam_T) * pageInfo.page[i].cpicNum);
            CPicAnalysis(fd,pageInfo.page[i].cpicNum,pageInfo.page[i].cpicInfo);
            qDebug()<<"cpicNum:"<<pageInfo.page[i].cpicNum;
            for(j = 0;j < pageInfo.page[i].cpicNum;j++)
            {
                addCPic(i,&pageInfo.page[i].cpicInfo[j]);
            }

			pageInfo.page[i].numInfo = (CNumParam_T *)malloc(sizeof(CNumParam_T) * pageInfo.page[i].numNum);
			CNumAnalysis(fd,pageInfo.page[i].numNum,pageInfo.page[i].numInfo);
            //qDebug()<<"numNum:"<<pageInfo.page[i].numNum;
            for(j = 0;j < pageInfo.page[i].numNum;j++)
            {
                addCNum(i,&pageInfo.page[i].numInfo[j]);
            }

        }else{

            qDebug()<<" no page flag";
        }

    }

    return 0;

}


void SerialUtils::addButton(int pageid,ButtonParam_T *ppar)
{
    MyButton *mbtn = new MyButton(ppar->id,ppar->name);
    mbtn->setText(ppar->txt);

    if(ppar->distype == 0){

        mbtn->default_bgcolor = parse565(ppar->fpic);
        mbtn->default_bgcolor_press = parse565(ppar->bpic);

    }else{
        mbtn->default_bgimg = ResourcesManager::getInstance()->getImageAbsolutePath(ppar->fpic);
        mbtn->default_bgimg_press = ResourcesManager::getInstance()->getImageAbsolutePath(ppar->bpic);
    }

    if(ppar->level>1)
        mbtn->raise();

    mbtn->btnType = ppar->swType;

    emit signal_addMWidget(pageid,
                           mbtn,
                           ppar->x,
                           ppar->y,
                           ppar->width,
                           ppar->height);
    mbtn->updateStyle();
}
void SerialUtils::addLabel(int pageid,LabelParam_T *ppar)
{
    MyLabel *mlable = new MyLabel(ppar->id,ppar->name);


    if(ppar->distype == 0){
        mlable->setBackgroudColor(parse565(ppar->bpicorcol));
    }else
        mlable->setBackgroudImg(ResourcesManager::getInstance()->getImageAbsolutePath(ppar->bpicorcol));

    mlable->setTextInfo(parse565(ppar->fpicorcol),ppar->txt,ResourcesManager::getInstance()->getFontFamily(ppar->fontIndex),ppar->txtSpace);

    mlable->setAlignment(parseAlignment(ppar->align));
    emit signal_addMWidget(pageid,mlable,ppar->x,
                           ppar->y,
                           ppar->width,
                           ppar->height);


}

void SerialUtils::addPanel(int pageid,PanelParam_T *ppar)
{

    MyDial *mydial = new MyDial(ppar->id,ppar->name);

    if(ppar->distype == 0){
        mydial->isuseimg = false;
        mydial->bgcolor = parse565(ppar->bpicorcol);
        mydial->indicatorcolo = parse565(ppar->fpicorcol);
    }else{
        mydial->isuseimg = true;
        mydial->bgimg = ResourcesManager::getInstance()->getImage(ppar->bpicorcol);
        mydial->indicatorcolo = parse565(ppar->fpicorcol);
    }

    mydial->indicatorW = ppar->linewidth;
    mydial->indicatorAngle = ppar->angle;

    emit signal_addMWidget(pageid,mydial,ppar->x,ppar->y,
                           ppar->width,ppar->height);
}

void SerialUtils::addSlide(int pageid,SlideParam_T *ppar)
{
    MySilder *silder = new MySilder(ppar->id,ppar->name);


    silder->hov = ppar->hov;
    silder->radius = 0;
    silder->silderw = ppar->wid;
    silder->silderh = ppar->hgt;
    silder->setValue(ppar->value);
    silder->setMinimum(ppar->min);
    silder->setMaximum(ppar->max);
    if(ppar->distype == 0){

        silder->backgroud_color = parse565(ppar->bpicorcol);
        silder->hander_color = parse565(ppar->fpicorcol);

    }else{
        silder->isuseimg = true;
        silder->hander_img = ResourcesManager::getInstance()->getImageAbsolutePath(ppar->fpicorcol);
        silder->backgroud_img = ResourcesManager::getInstance()->getImageAbsolutePath(ppar->bpicorcol);

    }

    //silder->setOrientation(Qt::Horizontal);

    emit signal_addMWidget(pageid,silder,ppar->x,ppar->y,
                           ppar->width,ppar->height);
    silder->updateStyle();
}
#include <QScrollBar>
void SerialUtils::addRolllabel(int pageid,RolllabelParam_T *ppar)
{
    MyRollLabel *mrolllable = new MyRollLabel(1,"222");
    //QFont font("16",10);
    //font.setWordSpacing(100);//字间距


    mrolllable->setFont(ResourcesManager::getInstance()->getFontFamily(ppar->fontIndex),ppar->txt,parse565(ppar->fpicorcol),ppar->txtSpace);

    mrolllable->setAlignment(parseAlignment(ppar->align));

    mrolllable->verticalScrollBar()->setVisible(false);
    mrolllable->horizontalScrollBar()->setVisible(false);
    if(ppar->enable){
        if(ppar->dir){//水平

            mrolllable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            mrolllable->horizontalScrollBar()->setVisible(true);
        }else{
            mrolllable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            mrolllable->verticalScrollBar()->setVisible(true);
        }
    }else{
        mrolllable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mrolllable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }
    if(ppar->distype == 0){
        mrolllable->setBackgroudColor(parse565(ppar->bpicorcol));
    }else
        mrolllable->setBackgroudImg(ResourcesManager::getInstance()->getImageAbsolutePath(ppar->bpicorcol));


    emit signal_addMWidget(pageid,mrolllable,ppar->x,ppar->y,ppar->width,ppar->height);

}
void SerialUtils::addGraph(int pageid,GraphParam_T *ppar)
{

    MyGraph *mg = new MyGraph(ppar->id,ppar->name);

    mg->gridh = ppar->hinterval;
    mg->gridw = ppar->winterval;
    mg->gridColor = parse565(ppar->gridcolor);
    mg->color1 = parse565(ppar->channelcolor0);
    mg->color2 = parse565(ppar->channelcolor1);
    mg->color3 = parse565(ppar->channelcolor2);
    mg->color4 = parse565(ppar->channelcolor3);
    if(ppar->distype == 0){
        mg->isuseimg = false;
        mg->bgcolor = parse565(ppar->bpicorcol);

    }else{
        mg->isuseimg = true;


        mg->imgpath = ResourcesManager::getInstance()->getImageAbsolutePath(ppar->bpicorcol);
    }

    emit signal_addMWidget(pageid,mg,ppar->x,ppar->y,ppar->width,ppar->height);

}
void SerialUtils::addRadio(int pageid,RadioParam_T *ppar){

    MyRadio *mradio = new MyRadio(2,"111",4,0);

    mradio->mdistance = ppar->distance;
    mradio->mselectIndex = ppar->focusindex;
    mradio->mradioCount = ppar->numofitem;
    mradio->mhov = ppar->horv;
    if(ppar->distype == 0){
        mradio->misuseimg = false;
        mradio->backgroudColor = parse565(ppar->bpicorcol);
        mradio->foregroudColor = parse565(ppar->fpicorcol);
    }else{
        mradio->misuseimg = true;
        mradio->foregroudImgPath = ResourcesManager::getInstance()->getImageAbsolutePath(ppar->fpicorcol);
        mradio->backgroudImgPath = ResourcesManager::getInstance()->getImageAbsolutePath(ppar->bpicorcol);
    }

    emit signal_addMWidget(pageid,mradio,ppar->x,ppar->y,ppar->width,ppar->height);
    mradio->layout();

}
void SerialUtils::addCheckBox(int pageid,CheckBoxParam_T *ppar){
    qDebug()<<"addCheckBox";

    MyCheck *myCheck = new MyCheck(ppar->id,ppar->name);



    if(ppar->distype == 0){
        myCheck->misuseimg = false;
        myCheck->backgroudColor = parse565(ppar->bpicorcol);
        myCheck->foregroudColor = parse565(ppar->fpicorcol);
    }else{
        myCheck->misuseimg = true;
        myCheck->foregroudImgPath = ResourcesManager::getInstance()->getImageAbsolutePath(ppar->fpicorcol);
        myCheck->backgroudImgPath = ResourcesManager::getInstance()->getImageAbsolutePath(ppar->bpicorcol);
    }

    emit signal_addMWidget(pageid,myCheck,ppar->x,ppar->y,ppar->width,ppar->height);
    myCheck->layout();

}
void SerialUtils::addHotSpot(int pageid,HotSpotParam_T *ppar){
    qDebug()<<"addHotSpot";
    MyHotSpot *mhotspot = new MyHotSpot(ppar->id,ppar->name);

    emit signal_addMWidget(pageid,mhotspot,ppar->x,ppar->y,ppar->width,ppar->height);
}
void SerialUtils::addTimer(int pageid,TimerParam_T *ppar){
    qDebug()<<"addTimer";
}
void SerialUtils::addVariable(int pageid,VariableParam_T *ppar){
    qDebug()<<"addVariable";
}
void SerialUtils::addPic(int pageid,PicParam_T *ppar){
    qDebug()<<"addPic";
    qDebug()<<"addPic:"<<ppar->picIndex;
    qDebug()<<"addPic:"<<ResourcesManager::getInstance()->getImageAbsolutePath(ppar->picIndex);

    MyPic *mypic = new MyPic(ppar->id,ppar->name);

    mypic->img = QImage(ResourcesManager::getInstance()->getImageAbsolutePath(ppar->picIndex));

    emit signal_addMWidget(pageid,mypic,ppar->x,ppar->y,ppar->width,ppar->height);
}
void SerialUtils::addCPic(int pageid,CPicParam_T *ppar){
    qDebug()<<"addCPic";

    MyPic *mypic = new MyPic(ppar->id,ppar->name);

    qDebug()<<"addCPic:"<<ppar->picIndex;
    qDebug()<<"addCPic:"<<ResourcesManager::getInstance()->getImageAbsolutePath(ppar->picIndex);
    QImage img = QImage(ResourcesManager::getInstance()->getImageAbsolutePath(ppar->picIndex));

    mypic->img = img.copy(ppar->x,ppar->y,ppar->width,ppar->height);

    emit signal_addMWidget(pageid,mypic,ppar->x,ppar->y,ppar->width,ppar->height);

}
void SerialUtils::addCNum(int pageid,CNumParam_T *ppar){
    qDebug()<<"addCNum";
    //QLCDNumber lcdnumber;

    MyLabel *mlable = new MyLabel(ppar->id,ppar->name);


    if(ppar->distype == 0){
        mlable->setBackgroudColor(parse565(ppar->bpicorcol));
    }else
        mlable->setBackgroudImg(ResourcesManager::getInstance()->getImageAbsolutePath(ppar->bpicorcol));


    QString txtnumber = QString::number(ppar->text);
    mlable->setTextInfo(parse565(ppar->fpicorcol),txtnumber.toLatin1().data(),ResourcesManager::getInstance()->getFontFamily(ppar->fontIndex),1);

    mlable->setAlignment(parseAlignment(ppar->align));
    emit signal_addMWidget(pageid,mlable,ppar->x,
                           ppar->y,
                           ppar->width,
                           ppar->height);

}
void SerialUtils::addPgbar(int pageid,PgbarParam_T *ppar)
{

    qDebug()<<"addPgbar";
    MyProgressbar *processbar = new MyProgressbar(ppar->id,ppar->name);


    processbar->setValue(ppar->percent);
    processbar->hov = ppar->hov;
    processbar->radius = 0;
    if(ppar->distype == 0){
        processbar->isuseimg = false;
        processbar->setBackgroudColor(parse565(ppar->bpic));
        processbar->setForegroundColor(parse565(ppar->fpic));
    }else{
        processbar->isuseimg = true;

        QString bgimg = ResourcesManager::getInstance()->getImageAbsolutePath(ppar->bpic);
        QString fgimg = ResourcesManager::getInstance()->getImageAbsolutePath(ppar->fpic);
        processbar->setBackgroudImg(bgimg);
        processbar->setForegroundImg(fgimg);
    }

    emit signal_addMWidget(pageid,processbar,ppar->x,ppar->y,
                           ppar->width,ppar->height);

    processbar->updateStyle();
}

