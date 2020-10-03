//October 2, 2020
//Tokenizer.c

//include directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//function headers
int isEmpty(char* str);
void tokenize (char* str);

//main driver function
int main(int argc, char* argv[])
{	
	//*argv[0] contains the pointer for input
    int limit = 30;
     
    //allocate memory dynamically
    argv[0] = (char*)malloc(limit*sizeof(char));
    
    //error handling for malloc() call
    if (argv[0] == NULL) 
    {
        perror("Memory Allocation failed. Exiting...");
        exit(EXIT_FAILURE);
    } 

    //prompt and store input 
    puts("Enter string: ");
	scanf("%[^\n]", argv[0]);

    //end early if string empty or purely whitespace
    if(isEmpty(argv[0]) == 1)
    {
    	printf("Zero Tokens Present (Empty String)\n");
    	return 0;
    }

    //split string and return found tokens
    tokenize(argv[0]);    

    //free allocated memory
    free(argv[0]); 
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
    //breaking tokens into specific types
    //then displaying categorically
    //until end of pointer reached
    while(*str)
    {
    	//whitespace characters
    	if(isspace(*str))
    		*str++;

    	//word: alphabetic char, followed by 
    	//alphanumeric char(s)
		else if(isalpha(*str))
		{
			if(*str == 's'
				&& *(str + 1) == 'i'
				&& *(str + 2) == 'z'
				&& *(str + 3) == 'e'
				&& *(str + 4) == 'o'
				&& *(str + 5) == 'f')
			{
				printf("sizeof: ");
				for(int pos = 0; pos <= 5; pos++)
				{
					printf("%c", *str);
					*str++;
				}
				printf("\n");
			}

			else
			{
				printf("word: ");
				while(isalnum(*str))
				{
					printf("%c", *str);
					*str++;
				}
				printf("\n");
			}
		}

		//hexadecimal integer: 0x or 0X, followed by
		//[0-9][a-f][A-F] char(s)
		else if((*str == '0' && *(str + 1) == 'x'
			|| *str == '0' && *(str + 1) == 'X')
			&& isxdigit(*(str + 2)))
		{
			printf("hexadecimal integer: ");
			for(int pos = 0; pos <= 2; pos++)
			{
				printf("%c", *str);
				*str++;
			}
			while(isxdigit(*str))
			{
				printf("%c", *str);
				*str++;
			}
			printf("\n");
		}

		//octal integer: 0, followed by
		//[0-7] char(s)
		else if(*str == '0'
			&& (*(str + 1) >= '0' && *(str + 1) <= '7')) 
		{
			printf("octal integer: ");
			while(*str >= '0' && *str <= '7')
			{
				printf("%c", *str);
				*str++;
			}
			printf("\n");
		}

		//decimal integer: digit char, followed by
		//digit char(s)
		else if(isdigit(*str)) 
		{
			//floating point: decimal with '.' but 
			//not at the end of token, optional 
			//exponent term (a decimal type)
			int index = 0; int isFloat = 0;
			while((isdigit(str[index])
				|| str[index] == '.')
				&& isFloat != 1) 
			{
				if(str[index] == '.')
					if(isdigit(str[index + 1]))
						isFloat = 1;
				index++;
			}

			if(isFloat)
			{
				printf("floating point: ");
				while(isdigit(*str)
					|| *str == '.'
					|| *str == 'e'
					|| *str == 'E'
					|| *str == '+'
					|| *str == '-')
				{
					printf("%c", *str);
					*str++;

					switch(*(str + 1))
					{
						case '.':
							printf("%c", *str);
							*str++;
							break;
						case 'e':
							printf("%c", *str);
							*str++;
							break;
						case 'E':
							printf("%c", *str);
							*str++;
							break;
						case '+':
							printf("%c", *str);
							*str++;
							break;
						case '-':
							printf("%c", *str);
							*str++;
							break;
					}
				}
				printf("\n");
			}

			else
			{
				printf("decimal integer: ");
				while(isdigit(*str))
				{
					printf("%c", *str);
					*str++;
				}
				printf("\n");
			}
		}

		//C operators 
		//(or anything that can be printed)
		else if(isprint(*str))
		{
			switch(*str) 
			{
			   	case '(':
					printf("left parenthesis: ");
					printf("%c\n", *str);
					*str++;
					break;
				
			   	case ')':
					printf("right parenthesis: ");
					printf("%c\n", *str);
					*str++;
					break;
			  
				case '[':
			     	printf("left bracket: ");
			     	printf("%c\n", *str);
			     	*str++;
			     	break;

				case ']':
			     	printf("right bracket: ");
			     	printf("%c\n", *str);
			     	*str++;
			     	break;

				case '.':
			     	printf("structure member: ");
			     	printf("%c\n", *str);
			     	*str++;
			     	break;

				case '-':
					switch(*(str + 1))
					{
						case '>':
							printf("structure pointer: ");
							printf("%c", *str);
							*str++;
							printf("%c\n", *str);
							*str++;
							break;

						case '-':
							printf("decrement: ");
							printf("%c", *str);
							*str++;
							printf("%c\n", *str);
							*str++;
							break;

						case '=':
							printf("minus equals: ");
							printf("%c", *str);
							*str++;
							printf("%c\n", *str);
							*str++;
							break;

						default:
							printf("minus/subtract operator: ");
							printf("%c\n", *str);
							*str++;
					}
					break;

				case ',':
			     	printf("comma: ");
			     	printf("%c\n", *str);
			     	*str++;
			     	break;

			    case '!':
			    	if(*(str + 1) == '=')
			    	{
						printf("inequality test: ");
						printf("%c", *str);
						*str++;
						printf("%c\n", *str);
						*str++;
					}
					else
					{
				     	printf("negate: ");
				     	printf("%c\n", *str);
				     	*str++;
				    }
			     	break;

			    case '~':
			     	printf("1s complement: ");
			     	printf("%c\n", *str);
			     	*str++;
			     	break;

			    case '>':
			     	switch(*(str + 1))
					{
						case '>':
							if(*(str + 2) == '=')
							{
								printf("shift right equals: ");
								printf("%c", *str);
								*str++;
								printf("%c", *str);
								*str++;
								printf("%c\n", *str);
								*str++;
							}
							else
							{
								printf("shift right: ");
								printf("%c", *str);
								*str++;
								printf("%c\n", *str);
								*str++;
							}
							break;

						case '=':
							printf("greater than or equal test: ");
							printf("%c", *str);
							*str++;
							printf("%c\n", *str);
							*str++;
							break;

						default:
							printf("greater than test: ");
							printf("%c\n", *str);
							*str++;
					}
					break;

			    case '<':
			     	switch(*(str + 1))
					{
						case '<':
							if(*(str + 2) == '=')
							{
								printf("shift left equals: ");
								printf("%c", *str);
								*str++;
								printf("%c", *str);
								*str++;
								printf("%c\n", *str);
								*str++;
							}
							else
							{
								printf("shift left: ");
								printf("%c", *str);
								*str++;
								printf("%c\n", *str);
								*str++;
							}
							break;

						case '=':
							printf("less than or equal test: ");
							printf("%c", *str);
							*str++;
							printf("%c\n", *str);
							*str++;
							break;

						default:
							printf("less than test: ");
							printf("%c\n", *str);
							*str++;
					}
					break;

				case '^':
			    	if(*(str + 1) == '=')
			    	{
						printf("bitwise XOR equals: ");
						printf("%c", *str);
						*str++;
						printf("%c\n", *str);
						*str++;
					}
					else
					{
				     	printf("bitwise XOR: ");
				     	printf("%c\n", *str);
				     	*str++;
				    }
			     	break;

				case '|':
					switch(*(str + 1))
					{
						case '|':
							printf("logical OR: ");
							printf("%c", *str);
							*str++;
							printf("%c\n", *str);
							*str++;
							break;

						case '=':
							printf("bitwise OR equals: ");
							printf("%c", *str);
							*str++;
							printf("%c\n", *str);
							*str++;
							break;

						default:
							printf("bitwise OR: ");
							printf("%c\n", *str);
							*str++;
					}
					break;

				case '+':
					switch(*(str + 1))
					{
						case '+':
							printf("increment: ");
							printf("%c", *str);
							*str++;
							printf("%c\n", *str);
							*str++;
							break;

						case '=':
							printf("plus equals: ");
							printf("%c", *str);
							*str++;
							printf("%c\n", *str);
							*str++;
							break;

						default:
							printf("addition: ");
							printf("%c\n", *str);
							*str++;
					}
					break;

				case '/':
			    	if(*(str + 1) == '=')
			    	{
						printf("divide equals: ");
						printf("%c", *str);
						*str++;
						printf("%c\n", *str);
						*str++;
					}
					else
					{
				     	printf("division: ");
				     	printf("%c\n", *str);
				     	*str++;
				    }
			     	break;

				case '*':
			    	if(*(str + 1) == '=')
			    	{
						printf("times equals: ");
						printf("%c", *str);
						*str++;
						printf("%c\n", *str);
						*str++;
					}
					else
					{
				     	printf("multiply/dereference operator: ");
				     	printf("%c\n", *str);
				     	*str++;
				    }
			     	break;

			    case '=':
			    	if(*(str + 1) == '=')
			    	{
						printf("equality test: ");
						printf("%c", *str);
						*str++;
						printf("%c\n", *str);
						*str++;
					}
					else
					{
				     	printf("assignment: ");
				     	printf("%c\n", *str);
				     	*str++;
				    }
			     	break;

			    case '&':
					switch(*(str + 1))
					{
						case '&':
							printf("logical AND: ");
							printf("%c", *str);
							*str++;
							printf("%c\n", *str);
							*str++;
							break;

						case '=':
							printf("bitwise AND equals: ");
							printf("%c", *str);
							*str++;
							printf("%c\n", *str);
							*str++;
							break;

						default:
							printf("AND/address operator: ");
							printf("%c\n", *str);
							*str++;
					}
					break;

			    case '%':
			    	if(*(str + 1) == '=')
			    	{
						printf("mod equals: ");
						printf("%c", *str);
						*str++;
						printf("%c\n", *str);
						*str++;
					}
					else
					{
				     	printf("modulus/remainder: ");
				     	printf("%c\n", *str);
				     	*str++;
				    }
			     	break;

				case '?':
			     	printf("conditional true: ");
			     	printf("%c\n", *str);
			     	*str++;
			     	break;

				case ':':
			     	printf("conditional false: ");
			     	printf("%c\n", *str);
			     	*str++;
			     	break;

			    default :
			   		*str++;
			}

		}
	}
}
