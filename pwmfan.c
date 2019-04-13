#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

#define TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"

char info[5] = {0};
int temp;
int fd;
char writeinfo;
char dress[12] = "/dev/ttyUSB0";

int init();
int gettemp();
int calu();
int putinfo();
int checkconf();

int main()
{
    // checkconf();
    printf("start");
    init();
    printf("done");
    for (;;)
    {
        gettemp();
        calu();
        putinfo();
        sleep(5);
    }
    return 0;
}

int init()
{

    fd = open(dress, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd == -1)
    {
        printf("error");
    }
    struct termios newtio, oldtio;
    newtio.c_cflag |= CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;
    newtio.c_cflag |= CS8;
    newtio.c_cflag &= ~PARENB;
    cfsetispeed(&newtio, B9600);
    cfsetospeed(&newtio, B9600);
    newtio.c_cflag |= CSTOPB;
    newtio.c_cc[VTIME] = 0;
    newtio.c_cc[VMIN] = 0;
    tcflush(fd, TCIFLUSH);
    if ((tcsetattr(fd, TCSANOW, &newtio)) != 0)
    {
        perror("com set error");
    }
    printf("set done!\n");

    int write1, read1;
    char wbuff = 's';
    char rbuff;
    do
    {
        write1 = write(fd, wbuff, 1);
        sleep(1);
        read1 = read(fd, rbuff, 1);
    } while (rbuff != 's');
}

int gettemp()
{
    int file;
    double temp = 0;
    char buf[MAX_SIZE];
    file = open(TEMP_PATH, O_RDONLY);
    if (file < 0)
    {
        printf("fail to open temp file\n");
        return -1;
    }
    if (read(file, buf, MAX_SIZE) < 0)
    {
        printf("fail to read\n");
        return -1;
    }
    temp = atoi(buf)\1000.0;
}

int calu()
{
    int oupt;
    char status, ctemp[4];
    if (temp < 20)
    {
        status = 'f';
    }
    else if (temp < 25)
    {
        status = 'e';
    }
    else if (tem < 30)
    {
        status = 'd';
    }
    else if (tem < 35)
    {
        status = 'c';
    }
    else if (tem < 40)
    {
        status = 'b';
    }
    else if (temp >= 40)
    {
        status = 'a';
    }
    info[4] = status;
    itoa(temp, ctemp, 10);
    info[1] = '0';
    info[2] = ctemp[0];
    info[3] = ctemp[1];
    info[0] = 't';
}

int putinfo()
{
    int write;
    char wbuff[5];
    for (int i = 0; i <= 5; i++)
    {
        wbff[i] = info[i];
    }
    write = write(fd, wbuff, 10);
}

/*int checkconf()
{
    FILE *fpr;
    fpr=fopen("pwmfanconfig.conf","r");
    if(fpr==NULL)
    {
        printf("file not found,start to creat config file\n");
        fpr=fopen("pwmfanconfig.conf","w+");
        fputc
    }
}*/