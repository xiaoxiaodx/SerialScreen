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
    uint8_t id; //页面 id 0-254
}pageData_S;

typedef struct  _tagcleanData_S{
    uint16_t color; //颜色值 0-65535
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
    uint32_t data;
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

typedef struct _serialParam_T{
	int headflag;
	int trailflag;
	int loadflag;
	char buf[256];
	int posit;
}serialParam_T;


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

#include <QObject>
#include <shape/marc.h>
#include <shape/mtext.h>
#include <shape/mimage.h>
#include <shape/mcurve.h>
#include <shape/mdashboard.h>
#include <shape/mline.h>
#include <shape/mpoint.h>
#include <shape/mrect.h>

class SerialUtils  : public QObject{


    Q_OBJECT

public:
    explicit SerialUtils(QObject *parent = nullptr);


    int ParseSerialInt();
    int ParseSerialComm(char *str,int len);
    int analysisBin();
signals:

    void signal_addPage(int id,QString name,bool isuseimg,QString imgpaht,QColor color);
    void signal_addMWidget(int pageid,QWidget *mwbase,int x,int y,int w,int h);

    void signal_switchPage(int id);
    void signal_cleanPage(QColor color);
    void signal_addShape(Shape *);

    void signal_process_cmd(QString cmdtype,QString cmdstr);

private:
    void widget_proc(char* cmd,char *str,int num,void *data);
    int cmdproc(char *str);

    void addPage(int id,QString name);
    void addButton(int id,QString name);
    void addButton(int pageid,ButtonParam_T *bt);
    void addLabel(int pageid,LabelParam_T *);
    void addPanel(int pageid,PanelParam_T *);
    void addSlide(int pageid,SlideParam_T *);
    void addRolllabel(int pageid,RolllabelParam_T *);
    void addGraph(int pageid,GraphParam_T *);
    void addRadio(int pageid,RadioParam_T *);
    void addCheckBox(int pageid,CheckBoxParam_T *);
    void addHotSpot(int pageid,HotSpotParam_T *);
    void addTimer(int pageid,TimerParam_T *);
    void addVariable(int pageid,VariableParam_T *);
    void addPic(int pageid,PicParam_T *);
    void addCPic(int pageid,CPicParam_T *);
    void addCNum(int pageid,CNumParam_T *);
    void addPgbar(int pageid,PgbarParam_T *);

};


#endif	//_CMDPROC_H_

