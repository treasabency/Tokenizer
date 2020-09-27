#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
int main()
{
    char *test;
    int limit;
     
    limit=30;
     
    //allocate memory dynamically
    test=(char*)malloc(limit*sizeof(char));
     
    printf("Enter string: ");
     
    scanf("%[^\n]s",test);
    //gets(name);
     
    printf("%s",test);
     
    //free dynamically allocated memory
    free(test); // <-- Hey, dont forget.
    return 0;
}


