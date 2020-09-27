//include statements
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//function declarations
int isEmpty(char* str);
char* splitTokens(char* str, const char* delim);

//main driver function
int main(char* input)
{
    int limit = 30;
     
    //allocate memory dynamically
    input = (char*) malloc(limit * sizeof(char));
    
    //prompt and store user-defined string
    printf("Enter string: ");
    gets(input);
    //scanf("%[^\n]", input);

    //if string is empty or entirely whitespace,
    //cut off program right away
    if(isEmpty(input) == 1)
    {
    	printf("Zero Tokens Present (Empty String)");
    	return 0;
    }
    //Testing Input
    //printf("Input: %s\n\n", input);

    //manipulating a copy of user string
    char* copy = (char*) malloc(limit * sizeof(char));
    strcpy(copy, input);
    //Testing Copy
    //printf("Copy: %s\n\n", copy);

    char* token = splitTokens(copy, " \t\v\f\n\r");
    //Testing Token
    //printf("Token: %s\n\n", token);

    // loop through the string to extract all other tokens
    while(token != NULL) 
    {
        printf( "%s\n", token ); //printing each token
        token = splitTokens(NULL, " \t\v\f\n\r");
    }
     
    //free dynamically allocated memory
    free(input);
    free(copy);
    free(token);
    return 0;
}

//function to determine if string is empty
//(only contains null terminator) or is pure whitespace
int isEmpty(char* str) 
{
	//user just pressed the "Enter" key for empty string
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

//implementation of strTok() function
char* splitTokens(char* str, const char* delimiter)
{
    //pointer to return token value upon function exit
    char* result;
    //static pointer which will move us through the 
    //input string, which is pointed to by copy and token,
    //keeps track of tokens in between delimiters
    static char* currentTokenPtr;

    //empty string input, no tokens left
    if (str == NULL && currentTokenPtr == NULL)
        return NULL;

    //string pointer exists, set token pointer to that value
    if (str)
        currentTokenPtr = str;

    //strspn(s1, s2) finds how many characters from the start of s1
    //match only the characters in s2;
    //this will increase the token pointer index 
    //to skip over any amount of consecutive whitespace
    currentTokenPtr += strspn(currentTokenPtr, delimiter);
    //pointer hits the null terminator
    if (*currentTokenPtr == '\0')
        return NULL;

    //result will hold the value pointed to by currentTokenPtr
    result = currentTokenPtr;
    //strcspn(s1,s2) adds up the number of characters from the
    //start of s1 until it finds a character that matches between
    //s1 and s2; this will increase the pointer index until
    //a delimiter character is found, skipping over other chars
    currentTokenPtr += strcspn(currentTokenPtr, delimiter);
    //pointer hits null terminator
    if (*currentTokenPtr == '\0') 
    {
        //end of token, reset value
        currentTokenPtr = NULL;
        //return resulting token
        return result;
    }

    //current pointer value is not null terminated,
    //so we set the following memory value to null terminator
    //to prepare for next function call for reading upcoming tokens
    *currentTokenPtr++ = '\0';

    //return resulting token
    return result;
}
