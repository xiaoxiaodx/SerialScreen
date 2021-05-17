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
#ifndef _CMDPROC_C_
#define _CMDPROC_C_
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

#include "cmdproc.h"


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

//页面
int page_proc(char *str,int num,void *data)
{
    int ret=-1;
    pageData_S param = {0};
    memset(&param,0,sizeof(param));
    ret=sscanf(str,"%d",&(param.id));
    printf("[%s:%d]:%d :%d\r\n",__FUNCTION__,__LINE__,ret,(param.id));

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

int cmdproc(char *str)
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
					pParam=str+strlen(cmdProcTbl[i].cmd)+1;
				    printf("[%s:%d]:pParam=%s!cmd = %s,cmdproc = %p\r\n",__FUNCTION__,__LINE__,pParam,cmdProcTbl[i].cmd,cmdProcTbl[i].cmdproc);
					ret=cmdProcTbl[i].cmdproc(pParam,cmdProcTbl[i].num,NULL);
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

int ParseSerialInt()
{
	memset(&serParam,0,sizeof(serialParam_T));
	memset(serParam.buf,0,sizeof(serParam.buf)); 
	return 0;
}

int ParseSerialSend(char *s_buf,int len)
{
	tty_send(s_buf,len);
	return 0;
}

int ParseSerialComm(char *str,int len)
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
			
			printf("[%s:%d]:binlen:0x%x,speed:0x%x!!!",__FUNCTION__,__LINE__,binlen,speed);
			
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
			serParam.trailflag = 1;
			memcpy(serParam.buf+serParam.posit,str,endPosit);//0xb 结束符不拷贝
			serParam.posit += endPosit;
			printf("[%s:%d]:serParam.buf:%s!!!\n",__FUNCTION__,__LINE__,serParam.buf);
			if(!strcmp("load",serParam.buf)) //02 6C 6F 61 64 0B
			{
				printf("start to load data!!!!\n");
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

int analysisBin()
{
	int fd = 0;
	fd = open("./LKdata.bin", O_RDWR); //串口接收bin文件到一个固定的位置或者SD卡拷贝到固定路径

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

	if(imageInfo.imageNum > 0)
	{
		imageInfo.image = (ImageInfo_T *)malloc(sizeof(ImageInfo_T) * imageInfo.imageNum);
		memset(buf,0,sizeof(buf));
		read(fd,buf,4*imageInfo.imageNum); //图片地址
		for(i = 0;i < imageInfo.imageNum;i++)
		{		
			imageInfo.image[i].addr = btos(buf+4*i);
			imageInfo.image[i].index = i;
			printf("[%s:%d]:imageAddr[%d]:0x%x\n",__FUNCTION__,__LINE__,i,imageInfo.image[i].addr);
		}
	}

	if(fontInfo.fontNum > 0)
	{
		fontInfo.font = (FontInfo_T *)malloc(sizeof(FontInfo_T) * fontInfo.fontNum);
		memset(buf,0,sizeof(buf));
		read(fd,buf,4*fontInfo.fontNum); //字库地址
		for(i = 0;i < fontInfo.fontNum;i++)
		{
			fontInfo.font[i].addr = btos(buf+4*i);	
			printf("[%s:%d]:fontAddr[%d]:0x%x\n",__FUNCTION__,__LINE__,i,fontInfo.font[i].addr);
		}
	}

	if(pageInfo.pageNum > 0)
	{
		pageInfo.page = (PageInfo_T *)malloc(sizeof(PageInfo_T)*pageInfo.pageNum);
		memset(buf,0,sizeof(buf));
		read(fd,buf,4*pageInfo.pageNum); //页面地址
		for(i = 0;i < pageInfo.pageNum;i++)
		{
			pageInfo.page[i].addr = btos(buf+4*i);		
			pageInfo.page[i].index = i;
			printf("[%s:%d]:pageAddr[%d]:0x%x\n",__FUNCTION__,__LINE__,i,pageInfo.page[i].addr);
		}
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

/**---------------------------------------------------------------------------*
**                         Compiler Flag                                     *
**---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern   "C"
}
#endif

#endif	//_CMDPROC_C_

