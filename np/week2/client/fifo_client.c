#include<unistd.h>
#include<unistd.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdio.h>

#define FIFO_NAME "/home/chetan/programs/np/week2/fifo/indian_republic"
#define FIFO_SEND "/home/chetan/programs/np/week2/fifo/send"
int main(void)
{
char s[300];
int num, fd,fd1;
mknod(FIFO_SEND, S_IFIFO | 0666, 0);
printf("waiting for readers...\n");
fd1 = open(FIFO_SEND, O_WRONLY);
printf("got a reader--write file name\n");
gets(s);
if ((num = write(fd1, s, strlen(s))) == -1)
perror("write");
else
printf("speak: wrote %d bytes\n", num);

close(fd1);

mknod(FIFO_NAME, S_IFIFO | 0666, 0);
printf("waiting for writers...\n");
fd = open(FIFO_NAME, O_RDONLY);
printf("got a writer\n");

if ((num = read(fd, s, 300)) == -1)
perror("read");
else {
s[num] = '\0';
printf("tick: read %d bytes: \"%s\"\n", num, s);
}

close(fd);

return 0;
}

