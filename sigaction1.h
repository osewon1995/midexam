  1 /* sigaction1.h */
  2
  3 #include <signal.h>
  4 #include <unistd.h>
  5 #include <string.h>
  6 #include <stdio.h>
  7
  8 void sig_int(int signo)
  9 {
 10     sigset_t sigset, oldset;
 11
 12     // 핸들러가 수행되는 동안 수신되는 모든 시그널에 대해서
 13     // 블럭한다.
 14     sigfillset(&sigset);
 15
 16     // blocking all signals while performing the handler function by puttying SIG_BLOCK
 17     if (sigprocmask(SIG_BLOCK, &sigset, &oldset) < 0)
 18     {
 19         printf("sigprocmask %d error \n", signo);
 20     }
 21
 22     fprintf(stderr, "SIGINT !!!!\n");
 23
 24     sleep(10);
 25 }
 26
 27 void sig_usr(int signo)
 28 {
 29     printf("sig_usr: %d\n", signo);
 30 }
