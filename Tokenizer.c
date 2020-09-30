//include directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//function headers
int isEmpty(char* str);
void tokenize (char* str);

//main driver function
int main()
{	
	//pointer for input
    char* test;

    int limit; 
    limit = 30;
     
    //allocate memory dynamically
    test=(char*)malloc(limit*sizeof(char));
    
    //prompt and store input 
    printf("Enter string: ");
    scanf("%[^\n]",test);

    //end early if string empty or purely whitespace
    if(isEmpty(test) == 1)
    {
    	printf("Zero Tokens Present (Empty String)\n");
    	return 0;
    }

    //split string and return found tokens
    tokenize(test);    

    //free allocated memory
    free(test); 
    return 0;
}

//helper function, recognize empty string
int isEmpty(char* str)
{
	//user likely pressed the "Enter" key for empty string
	if(str[0] == '\0')
		return 1;

	//loop through to see if string is entirely whitespace
	int index = 0;
	while (str[index] != '\0') 
	{
		//as long as there is one non-whitespace char,
		//the string is not empty
		if (!isspace(str[index]))
			return 0;
		index++;
	}
	//1 indicates pure whitespace string
	return 1;
}

//helper function, recognize and print tokens
void tokenize (char* str) 
{
	//tokenArr is separate from user input,
	//input string remains unchanged afterwards
    char tokenArr[strlen(str)][strlen(str)]; 

    //i = rows for each distinct token, 
    //j = columns for each token character
    int i, j, numTokens;
    j = 0, numTokens = 0;

    //any whitespace in input string
    //becomes null operator in char array
    for(i = 0; i <= (strlen(str)); i++)
    {
    	//any whitespace or null operator
    	//signals the end of a token
        if(str[i] == ' ' || str[i] == '\0' 
        	|| str[i] == '\t' || str[i] == '\v'
        	|| str[i] == '\f' || str[i] == '\n'
        	|| str[i] == '\r')
        {
            tokenArr[numTokens][j] = '\0';
            numTokens++;
            j = 0;
        }
        //store entire token into a row
        //in char array
        else
        {
            tokenArr[numTokens][j] = str[i];
            j++;
        }
    }

    //breaking tokens into specific types
    //then displaying categorically
    for(i = 0; i < numTokens; i++) 
    {
    	//word: alphabetic char, followed by 
    	//alphanumeric char(s)
		if(isalpha(tokenArr[i][0]))
		{
			printf("word: ");
			j = 0;
			while(isalnum(tokenArr[i][j]))
			{
				printf("%c", tokenArr[i][j]);
				j++;
			}
			printf("\n");
		}

		//hexadecimal integer: 0x or 0X, followed by
		//[0-9][a-f][A-F] char(s)
		else if(tokenArr[i][0] == '0' && tokenArr[i][1] == 'x'
			|| tokenArr[i][0] == '0' && tokenArr[i][1] == 'X') 
		{
			printf("hexadecimal integer: ");
			printf("%c", tokenArr[i][0]);
			printf("%c", tokenArr[i][1]);
			j = 2;
			while(isxdigit(tokenArr[i][j]))
			{
				printf("%c", tokenArr[i][j]);
				j++;
			}
			printf("\n");
		}

		//octal integer: 0, followed by
		//[0-7] char(s)
		else if(tokenArr[i][0] == '0') 
		{
			printf("octal integer: ");
			j = 0;
			while(tokenArr[i][j] >= '0' && tokenArr[i][j] <= '7')
			{
				printf("%c", tokenArr[i][j]);
				j++;
			}
			printf("\n");
		}

		//decimal integer: digit char, followed by
		//digit char(s)
		else if(isdigit(tokenArr[i][0])) 
		{
			printf("decimal integer: ");
			j = 0;
			while(isdigit(tokenArr[i][j]))
			{
				printf("%c", tokenArr[i][j]);
				j++;
			}
			printf("\n");
		}

		else 
		 	printf("");
	}
}
