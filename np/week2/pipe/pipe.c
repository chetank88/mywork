#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
       {
           int pipefd[2],pip[2];
           pid_t cpid;
           


           if (pipe(pipefd) == -1 || pipe(pip) == -1) {
               perror("pipe");
               exit(EXIT_FAILURE);
           }

           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {    /* Child reads from pipe */

                char fname[30];
                printf("\n enter the file name:");
                scanf("%s",fname);
		
		

               close(pip[0]);          /* Close unused read end */
               write(pip[1], fname, strlen(fname));
               close(pip[1]);
              
	       close(pipefd[1]);          /* Close unused write end */
               char buff[300];int i=0;

               int rd=read(pipefd[0], buff, 300);
                  
               write(STDOUT_FILENO,buff, rd);
                  
               write(STDOUT_FILENO, "\n", 1);
               close(pipefd[0]);
              
               _exit(EXIT_SUCCESS);

           } else {            /* Parent writes argv[1] to pipe */
                         /* Close unused write end */
                
               close(pip[1]);
               char buf[30];
               int rd=read(pip[0], buf, 30);
                 write(STDOUT_FILENO, buf, rd);
                 write(STDOUT_FILENO, "\n", 1);
		close(pip[0]);

               //write(STDOUT_FILENO, "\n", 1);

               int fp=open(buf,O_RDONLY,0666);
                if(fp!=-1)
                {
                char buff[300];
		int rd=read(fp,buff,300);
                 close(pipefd[0]);          /* Close unused read end */
                 write(pipefd[1], buff,rd);
                 close(pipefd[1]);          /* Reader will see EOF */
	       }

               wait(NULL);            /* Wait for child */
               exit(EXIT_SUCCESS);
           }
           

            return 0;
       }
