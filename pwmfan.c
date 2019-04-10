#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>


char info[5]={0};

int init();
int gettemp();
int calu();
int putinfo();



int main()
{
    printf("start");
    init();
    printf("done");
    for(;;)
    {
        gettemp();
        calu();
        putinfo();
        sleep(5);
    }
    return 0;
}

int init ()
{
    int fd;
    fd=open("/dev/ttyUSB0",O_RDWR | O_NOCTTY | O_NONBLOCK);
    if(fd==-1)
    {
        printf("error");
    }
    struct termios newtio,oldtio;
    newtio.c_cflag  |=  CLOCAL | CREAD;  
    newtio.c_cflag &= ~CSIZE; 
    newtio.c_cflag |= CS8; 
    newtio.c_cflag &= ~PARENB;
    cfsetispeed(&newtio, B9600); 
    cfsetospeed(&newtio, B9600);
    newtio.c_cflag |=  CSTOPB;
    newtio.c_cc[VTIME]  = 0; 
    newtio.c_cc[VMIN] = 0;
    tcflush(fd,TCIFLUSH);
    if((tcsetattr(fd,TCSANOW,&newtio))!=0) 
     { 
      perror("com set error"); 
     } 
     printf("set done!\n"); 


     int write1,read1;
     char wbuff='s';
     char rbuff;
     do
         write1=write(fd,wbuff,1);
         sleep(1);
         read1=read(fd,rbuff,1);
    while(rbuff!='s');
}
int gettemp()
{

}
int calu()
{

}
int putinfo()
{

}
