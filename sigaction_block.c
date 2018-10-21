  1 #include <stdio.h>
  2 #include <signal.h>
  3 #include <unistd.h>
  4
  5 void signalHandler(int signo);
  6
  7 int main(void)
  8 {
  9     struct sigaction act;
 10
 11     /* 시그널이 오면 signalHandler를 실행하도록 설정 */
 12     act.sa_handler = signalHandler;
 13     /* 모든 시그널은 시그널을 처리하는 동안 블록되도록 설정 */
 14     sigfillset(&act.sa_mask);
 15     act.sa_flags = 0;
 16     /* SIGINT에 대해 act 행동을 하도록 설정 */
 17     sigaction(SIGINT, &act, NULL);
 18
 19     printf("pid: %d, SIGINT handler installed; other signals will be blocked\n", getpid());
 20
 21     while(1)
 22         sleep(5);
 23
 24     return(0);
 25 }
 26
 27 void signalHandler(int signo)
 28 {
 29     printf("start handler\n");
 30     sleep(10);
 31     printf("end handler\n");
 32 }
