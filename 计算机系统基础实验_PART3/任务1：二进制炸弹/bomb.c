#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "support.h"

FILE *infile;

char  studentid[11];
void    initialize_bomb(char *userid) 
{
   int len;
   int x=1,y=2,z=3,u=4,v=5,w=6;
   len =strlen(userid);
   if (len !=10)  {
       printf("The student number has 10 characters, such as U202315001 \n");
       exit(0);
   }
   strcpy(studentid, userid);
   printf("welcome  %s \n",userid);
   #ifdef U0
      if (userid[len-1]=='0')   {
          x=100;  x=~x;  w = 2*x;   
          return;
     }
   #endif
   #ifdef U1
      if (userid[len-1]=='1')   {
            w = 2*x+3*y;   return;
      }
   #endif
   #ifdef U2
      if (userid[len-1]=='2')  {
          w = 2*x+3*y+4*u;  return;
      }
   #endif
   #ifdef U3
      if (userid[len-1]=='3')   {
         w = 2*x+3*y+4*u+x;  return;
      }
   #endif
   #ifdef U4
      if (userid[len-1]=='4')   {
         w = 2*x+3*y+4*u+x+5*w;  return;
      }
   #endif
   #ifdef U5
      if (userid[len-1]=='5')   {
          w =-u;  return;
      }
   #endif
   #ifdef U6
      if (userid[len-1]=='6')   {
        w =-u-v;   return;
      }
   #endif
   #ifdef U7
      if (userid[len-1]=='7')   {
          return;
      }
   #endif
   #ifdef U8
      if (userid[len-1]=='8')   {
           x=4*w+10;   return;
      }
   #endif
   #ifdef U9
      if (userid[len-1]=='9')   {
          x=4*w+5*y;   return;
      }
   #endif
   printf(" gcc  -g -o binarybomb -D U* bomb.c  support.c  phase.o\n");
   printf(" U* : * is the last number of your Student Id . \n");
    printf(" example :  U202315001  ->   -D U1 . \n"); 
   exit(0);
}

int main(int argc, char *argv[])
{
    char *input, *userid;
    if (argc == 1)   
	infile = stdin;
    else if (argc == 2) {
                infile = fopen(argv[1], "r");
	if (!infile) {
	    printf("%s: Error: Couldn't open %s\n", argv[0], argv[1]);
	    exit(8);
	}
    }
    else {
	printf("Usage: %s [<input_file>]\n", argv[0]);
	exit(8);
    }

    printf("Input your Student ID : \n");
    userid = read_line();
    initialize_bomb(userid);

    printf("You have 6 bombs to defuse! \n");

    printf("Gate 1 :  input a string that meets the requirements. \n");
    input = read_line();             /* 输入一行信息                   */
    phase_1(input);                   /* 若一关炸弹拆除失败，会报错  */
    printf("Phase 1 passed! \n");

    printf("Gate 2 :  input six intergers that meets the requirements. \n");
    input = read_line();
    phase_2(input);
    printf("Phase 2 passed! \n");

    printf("Gate 3 :  input 2 intergers. \n");
    input = read_line();
    phase_3(input);
    printf("Phase 3 passed! \n");

    printf("Gate 4 :  input 2 intergers and a string. \n");
    input = read_line();
    phase_4(input);
    printf("Phase 4 passed! \n");
    
   printf("Gate 5 :  input  a string. \n");
    input = read_line();
    phase_5(input);
    printf("Phase 5 passed! \n");

   printf("Gate 6 :  input 6 intergers. \n");
    input = read_line();
    phase_6(input);
    printf("Phase 6 passed! \n");

    printf("Congratulations! You have passed all the tests! \n");
    return 0;
}

