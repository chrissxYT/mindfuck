//this program is heavily based on Urban Müller's original bfi

#include <stdio.h>
#include <stdlib.h>

int  p;
char a[5000], f[5000], b, *s=f;

void interpret(char *c)
{
        char *d;

        while(*c) {
                switch(*c++) {
                        case '>': p=(p+1)%5000; break;
                        case '+': a[p]++;       break;
                        case '-': a[p]--;       break;
                        case '.': putchar(a[p]); fflush(stdout); break;
                        case ',': a[p]=getchar();fflush(stdout); break;
                        case '[':
                                  for(b = 1,d = c; b && *c; c++)
                                          b += *c =='[', b -= *c == ']';
                                  if(!b) {
                                          c[-1]=0;
                                          while( a[p] )
                                                  interpret(d);
                                          c[-1]=']';
                                          break;
                                  }
                        case ']':
                                  puts("UNBALANCED BRACKETS"), exit(0);
                        default: ;
                }
        }
}

int main(int argc,char **argv) {
        if(argc < 2) {
                puts("No file given.");
                return 1;
        }

        FILE *z = fopen(argv[1], "r");

        if(!z) {
                puts("Can't open the file.");
                return 1;
        }

        while((b=getc(z)) > 0) *s++ = b;
        *s = 0;
        interpret(f);

        return 0;
}

