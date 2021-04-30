/******************************************************************************
 * 
 * 				Copyright (c), 2021,
 * 
 * *****************************************************************************
 * Filename:tty_dev.c
 * 
 *  File Description: 
 * -----------------------
 * 
 * Revision: 
 * Author: fan
 * DataTime: 08-04-2021
 * Modification History:
 * 	--------------------
 *****************************************************************************/
#ifndef _TTY_DEV_C_
#define _TTY_DEV_C_
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
#include <pthread.h>
#include <time.h>


#define DEV_TTY  "/dev/ttyS4"

/******************************************************************************
*	Macros
******************************************************************************/
#define MAX_RX_SIZE     (16*1024)

/******************************************************************************
*	Types
******************************************************************************/
//enum

//Struct
typedef struct  _tagttyDev_S{
	pthread_mutex_t 		mutex;	
	pthread_mutex_t 		wmutex;	
    uint8_t *rxbuf;
    uint32_t rxbufsize;
    uint32_t rx_pos;
    uint32_t rx_readpos;
    uint32_t tty_flag;
	uint32_t tty_fd; //����fd
    uint32_t tty_status;
    pthread_t pid;
}ttyDev_S;

/******************************************************************************
*	Constants
******************************************************************************/


/******************************************************************************
*	Variables
******************************************************************************/
//local variables
ttyDev_S s_ttydev = {0};
//extern variables

/******************************************************************************
*	Functions Prototypes
******************************************************************************/
//local Functions Prototypes


//extern Functions Prototypes

/******************************************************************************
*	Functions
******************************************************************************/
// ��ȡ tty rx �ж�������
int get_ttyinfo(uint32_t *plen)
{
    int ret=-1;
    if(s_ttydev.tty_status!=1)
    {
        return -1;
    }
    return  s_ttydev.rx_pos;
}

// �ȴ� tty ��0x0b�����ݰ�
int wait_ttycmd(uint8_t *pdata, uint32_t len,uint32_t timeout)
{
    int ret=-1;
    struct timespec tout;
    if(s_ttydev.tty_status!=1)
    {
        return -1;
    }
    clock_gettime(CLOCK_REALTIME, &tout);
	tout.tv_sec += 1;   //�ӳ�1s
    ret=pthread_mutex_timedlock(s_ttydev.mutex, &tout);
    if(ret==0)
    {
        // ��ȡ���� ִ�в���

    	pthread_mutex_unlock(&(s_ttydev.wmutex));
    }
    return ret;
}
// ��tty rx ��ȡ���� ָ����������
int get_ttydata(uint8_t *pdata, uint32_t len)
{
    int ret=-1;
    if(s_ttydev.tty_status!=1)
    {
        return -1;
    }
	pthread_mutex_lock(&(s_ttydev.wmutex));
    // ret=tty_send(pdata ,*plen);
	pthread_mutex_unlock(&(s_ttydev.wmutex));

    return ret;
}

// ����tty ����
int write_ttydata(uint8_t *pdata, uint32_t *plen)
{
    int ret=-1;
    if(s_ttydev.tty_status!=1)
    {
        return -1;
    }
	pthread_mutex_lock(&(s_ttydev.wmutex));
    // ret=tty_send(pdata ,*plen);
	pthread_mutex_unlock(&(s_ttydev.wmutex));
	return ret;
}

int ttyS4Init()
{
    struct termios options;
 	int	rv = -1 ;
	
    s_ttydev.tty_fd = open(DEV_TTY,O_RDWR|O_NOCTTY|O_NDELAY) ; //�򿪴����豸
 
    if(s_ttydev.tty_fd < 0)
    {
        printf("open tty failed:%s\n", strerror(errno)) ;
		return -1;
    }
    printf("open devices sucessful!\n") ;
    
    memset(&options, 0, sizeof(options)) ;
    rv = tcgetattr(s_ttydev.tty_fd, &options); //��ȡԭ�еĴ������Ե�����
    if(rv != 0)
    {
        printf("tcgetattr() failed:%s\n",strerror(errno)) ;
        return -1;
    }
 
    options.c_cflag|=(CLOCAL|CREAD ); // CREAD �����������ݽ��գ�CLOCAL���򿪱�������ģʽ
    options.c_cflag &=~CSIZE;// ��ʹ��CSIZE��λ����  
    options.c_cflag |= CS8; //����8λ����λ
    options.c_cflag &= ~PARENB; //��У��λ
 
    /* ����115200������  */
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);
 
    options.c_cflag &= ~CSTOPB;/* ����һλֹͣλ; */
    options.c_cc[VTIME] = 0;/* �ǹ淶ģʽ��ȡʱ�ĳ�ʱʱ�䣻*/
    options.c_cc[VMIN]  = 0; /* �ǹ淶ģʽ��ȡʱ����С�ַ���*/
    tcflush(s_ttydev.tty_fd ,TCIFLUSH);/* tcflush����ն�δ��ɵ�����/����������ݣ�TCIFLUSH��ʾ������յ������ݣ��Ҳ���ȡ���� */
 
    if((tcsetattr(s_ttydev.tty_fd, TCSANOW,&options))!=0)
    {
        printf("tcsetattr failed:%s\n", strerror(errno));
        return -1;;
    }

	return 0;
}

int ttyServ_Init(void)
{
	int ret = -1;

	memset(&s_ttydev,0,sizeof(ttyDev_S));
	ret = ttyS4Init();
	if(ret == -1)
	{
		printf("Init %s failed!!\n",DEV_TTY);
		return -1;
	}
    s_ttydev.rxbufsize=MAX_RX_SIZE;
    s_ttydev.rx_pos=0;
    s_ttydev.rx_readpos=0;
    s_ttydev.rxbuf=malloc(MAX_RX_SIZE);
    s_ttydev.tty_flag=1;
    pthread_mutex_init(&(s_ttydev.mutex), NULL);
    pthread_mutex_init(&(s_ttydev.wmutex), NULL);
    // ���������߳�;
	pthread_create(&s_ttydev.pid, NULL, tty_rx, &s_ttydev);
     
    s_ttydev.tty_status=1;
}
int ttyServ_DeInit(void)
{
     s_ttydev.tty_flag=0;
     s_ttydev.tty_status=0;
     // �ȴ������߳��˳�
     
     s_ttydev.rxbufsize=0;
     s_ttydev.rx_pos=0;
     s_ttydev.rx_readpos=0;
     free(s_ttydev.rxbuf);s_ttydev.rxbuf=NULL;
     pthread_mutex_destroy(&(s_ttydev.wmutex));
     pthread_mutex_destroy(&(s_ttydev.mutex));
}

/**---------------------------------------------------------------------------*
**                         Compiler Flag                                     *
**---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern   "C"
}
#endif

#endif	//_TTY_DEV_C_

