#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

int comread(char buff[1024])
{
    int fd;
    fd = open("/dec/ttys0", O_RDWR);
    if (-1 == fd)
    {
        cout << "不能打开串口" << endl;
    }
    struct termios Opt;
    tcgetattr(fd, &Opt);
    cfsetispeed(&Opt, B9600);
    cfsetospeed(&Opt, B9600);
    tcsetattr(fd, TCANOW, &Opt);
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;
    char buff[1024];
    int Len;
    int readByte = read(fd, buff, Len);
    close(fd);
}
int comwrite(char buffer[1024])
{
    int fd;
    fd = open("/dec/ttys0", O_RDWR);
    if (-1 == fd)
    {
        cout << "不能打开串口" << endl;
    }
    struct termios Opt;
    tcgetattr(fd, &Opt);
    cfsetispeed(&Opt, B9600);
    cfsetospeed(&Opt, B9600);
    tcsetattr(fd, TCANOW, &Opt);
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;
    int Length;
    int nByte;
    nByte = write(fd, buffer, Length);
    close(fd);
}
int main()

{
    for(;;)
    {
        comwrite('s')
        
    }
    return 0;
}
