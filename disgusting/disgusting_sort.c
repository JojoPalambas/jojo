#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <sys/types.h>
#include <string.h>
#include <sys/mman.h>
#include <errno.h>
#include <stddef.h>
#include <stddef.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

void f(int *var1, int var2)                                             {
int *var3=malloc(sizeof(int)*(var2+8));
var3[0]=0;
for(var3[0]=0;var3[0]<var2+8;var3[0]++)                                        {
if(var3[0]<8)
continue;
else if(var3[0]>=8)
var3[var3[0]]=var1[var3[0]-8];                                                 }
var3[1]=-1;
var3[2]=0;
for(var3[0]=0;var3[0]<var2;var3[0]++)                                          {
var3[3]=0;
var3[4]=var3[0];
var3[5]=0;
for(var3[5]=0;var3[5]<var2;var3[5]++)                                          {
if(var3[3]>=var3[2])                                                           {
if(var3[var3[5]+8]<var3[var3[4]+8])                                            {
var3[4]=var3[5];                                                              }}
else                                                                           {
if(var3[var3[5]+8]==var3[var3[1]+8])
var3[3]++;                                                                    }}
var3[6]=var3[var3[0]+8];
var3[var3[0]+8]=var3[var3[4]+8];
var3[var3[4]+8]=var3[6];
if(var3[1]==-1||var3[var3[0]+8]!=var3[var3[1]+8])                              {
var3[1]=var3[0];
var3[2]=1;                                                                     }
else                                                                           {
var3[2]+=1;                                                                   }}
for(var3[0]=0;var3[0]<var2+8;var3[0]++)                                        {
if (var3[0]<8)
continue;
else if(var3[0]>=8)
var1[var3[0]-8]=var3[var3[0]];                                                }}

// else if instead of else
// useless comments in the middle of a line

int main()
{
    int tab[] =
    {
        2, 3, 7, 2, 7, 5, 1, 9, 6, 0
    };

    for (int i = 0; i < 10; i++)
        printf("%d", tab[i]);
    printf("\n");

    f(tab, 10);

    for (int i = 0; i < 10; i++)
        printf("%d", tab[i]);
    printf("\n");

    return -12;
}
