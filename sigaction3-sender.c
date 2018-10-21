  1 /* sigaction3-sender.c */
  2
  3 /*
  4  * main.c -- C Test App.
  5  *
  6  * Copyright (C) 2012-2013, 2013 heesoon.kim <chipmaker.tistory.com>
  7  *
  8  * This program is free software; you can redistribute it and/or modify
  9  * it under the terms of the GNU General Public License as published by
 10  * the Free Software Foundation; version 2 of the License.
 11  *
 12  * This program is distributed in the hope that it will be useful,
 13  * but WITHOUT ANY WARRANTY; without even the implied warranty of
 14  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 15  * GNU General Public License for more details.
 16  *
 17  * You should have received a copy of the GNU General Public License along
 18  * with this program; if not, write to the Free Software Foundation, Inc.,
 19  */
 20 #include <stdio.h>
 21 #include <stdlib.h>
 22 #include <string.h>
 23 #include <errno.h>
 24 #include <signal.h>
 25 #include <unistd.h>
 26
 27 #define MAX_SEND_SIGNUM 1000000
 28
 29 int main(int argc, char *argv[])
 30 {
 31     int i;
 32     int sig;
 33     pid_t pid;
 34
 35     puts("insert PID");
 36     scanf("%ud", &pid);
 37     getchar(); // fflush(stdin);
 38
 39     puts("insert signal");
 40     scanf("%ud", &sig);
 41     getchar(); // fflush(stdin);
 42
 43
 44     printf("%s: sending signal %d to process %ld %d times\n", argv[0], sig, (long)pid, MAX_SEND_SIGNUM);
 45
 46     for(i = 0; i < MAX_SEND_SIGNUM; i++)
 47         if(kill(pid, sig) == -1)
 48             fprintf(stderr, "kill error [%s]\n", strerror(errno));
 49
 50     printf("%s: exiting\n", argv[0]);
 51
 52     return 0;
 53 }
 54
