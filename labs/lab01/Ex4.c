#include <stdio.h>
#include <string.h>

int isPalindrom(char *s, int start, int stop);

int main()
{
    char s[100];
   
    scanf("%s", s);
    printf("%d", isPalindrom(s, 0, strlen(s) - 1));

    return 0;
}

int isPalindrom(char *s, int start, int stop){
    if(start >= stop)
        return 1;
    if(s[start] != s[stop])
        return 0;
    else
        return isPalindrom(s, start + 1, stop - 1);
}