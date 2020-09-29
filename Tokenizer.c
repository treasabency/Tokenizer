#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
int main()
{
    char* test;
    int limit;
     
    limit=30;
     
    //allocate memory dynamically
    test=(char*)malloc(limit*sizeof(char));
     
    printf("Enter string: ");
     
    scanf("%[^\n]s",test);
     
   splitStr(test);    

    free(test); 
    return 0;
}

void splitStr (char* str) {
    char splitStrings[strlen(str)][strlen(str)]; 
    int i,j,count;
 
    j=0; count=0;
    for(i=0;i<=(strlen(str));i++)
    {
        if(str[i]==' '||str[i]=='\0')
        {
            splitStrings[count][j]='\0';
            count++;  
            j=0;    
        }
        else
        {
            splitStrings[count][j]=str[i];
            j++;
        }
    }
    for(i=0;i < count;i++) {
	 	printf("word: %s\n", splitStrings[i]);
}
}



