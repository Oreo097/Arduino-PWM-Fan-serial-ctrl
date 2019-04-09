#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
//int init();
//int main()
//{
//	init();
//}



int fd;
	
struct termios newtio, oldtio;


int main()
{
	opencom();
	setcom();
	

	int write1;
	char buff = 's';
	for (;;)
	{
		write1 = write(fd, buff, 10);
	}
	return 0;
}
int opencom()
{
	fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd == -1)
	{
		printf("error");
	}
}
int setcom()
{
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

}