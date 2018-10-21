  1 /* signal-to-parent.c */
  2
  3 #include <stdio.h>
  4 #include <stdlib.h>
  5 #include <errno.h>
  6 #include <sys/types.h>
  7 #include <sys/wait.h>
  8 #include <unistd.h>
  9 #include <signal.h>
 10
 11 /* user signal handler */
 12 static void sig_usr(int signo) {
 13     if(signo == SIGUSR1)
 14         printf("SIGUSR1 received from its child\n");
 15     else if(signo == SIGUSR2)
 16         printf("SIGUSR2 received from its child\n");
 17     /*
 18     else if(signo == SIGINT)
 19         printf("SIGINT received from its child\n");
 20     */
 21 }
 22
 23 int main(void)
 24 {
 25     /* 자식 프로세스 */
 26     if(!fork()) {
 27         int ppid;
 28
 29         ppid = getppid();
 30         kill(ppid, SIGUSR1);
 31         kill(ppid, SIGUSR2);
 32         kill(ppid, SIGINT);
 33
 34         exit(0);
 35     }
 36
 37     /* 부모 프로세스 */
 38     else {
 39
 40         /* signal handler registration */
 41         if(signal(SIGUSR1, sig_usr) == SIG_ERR)
 42             perror("cannot catch SIGUSR1\n");
 43         if(signal(SIGUSR2, sig_usr) == SIG_ERR)
 44             perror("cannot catch SIGUSR2\n");
 45 /*
 46         if(signal(SIGINT, sig_usr) == SIG_ERR)
 47             perror("cannot catch SIGINT\n");
 48 */
 49
 50         /* 자식 프로세스의 종료를 기다리기 */
 51         wait(NULL);
 52
 53     }
 54     return 0;
 55 }
