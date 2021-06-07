// Khong Phuong Thao 
#include <stdio.h>
#include <stdlib.h> // exit()
#include <ctype.h>	// isdigit(char )
#include <string.h>

#define SIZE 100
// Char stack for converting infix to postfix
char cstack[SIZE];
int top = -1;

void cpush(char item)
{
	if (top >= SIZE - 1)
	{
		printf("\nstack Overflow.");
	}
	else
	{
		cstack[++top] = item;
	}
}

char cpop()
{
	char item;

	if (top < 0)
	{
		printf("stack underflow: invalid infix expression");
		getchar();
		exit(1);
	}
	else
	{
		item = cstack[top];
		top--;
		return item;
	}
}

// float stack for calculating postfix exp
float fstack[SIZE];
int ftop = -1;

void fpush(float item)
{
	if (ftop >= SIZE - 1)
	{
		printf("\nStack Overflow.");
	}
	else
	{
		fstack[++ftop] = item;
	}
}

float fpop()
{
	float item;

	if (ftop < 0)
	{
		printf("Stack underflow: invalid infix expression");
		getchar();
		exit(1);
	}
	else
	{
		item = fstack[ftop--];
		return item;
	}
}

int is_operator(char symbol)
{
	if (symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol == '-')
		return 1;
	else
		return 0;
}

int precedence(char symbol)
{
	if (symbol == '^') // exponent operator, highest precedence
		return 3;
	else if (symbol == '*' || symbol == '/')
		return 2;
	else if (symbol == '+' || symbol == '-') // lowest precedence
		return 1;
	else
		return 0;
}

void InfixToPostfix(char infix_exp[], char postfix_exp[])
{
	int i, j;
	char item;
	char x;
	cpush('(');				// cpush '(' onto cstack
	strcat(infix_exp, ")"); // add ')' to infix expression
	i = 0;
	j = 0;
	item = infix_exp[i];

	while (item != '\0') // loop till the end of infix
	{
		if (item == '(')
		{
			cpush(item);
		}
		else if (isdigit(item) || isalpha(item))
		{
			postfix_exp[j++] = item;
		}
		else if (is_operator(item) == 1)
		{
			postfix_exp[j++] = ',';
			x = cpop();
			while (is_operator(x) == 1 && precedence(x) >= precedence(item))
			{
				postfix_exp[j++] = x;
				postfix_exp[j++] = ',';
				// cpop all higher precedence operator to postfix
				x = cpop();
			}
			cpush(x);
			//one extra item for which condition fails and loop terminates
			cpush(item);
		}
		else if (item == ')')
		{
			// postfix_exp[j++] = ',';
			x = cpop();
			while (x != '(')
			{
				postfix_exp[j++] = ',';
				postfix_exp[j++] = x;
				x = cpop();
			}
		}
		else
		{
			printf("\nInvalid infix Expression.\n");
			getchar();
			exit(1);
		}
		item = infix_exp[++i];
	}
	//while loop ends

	if (top > 0)
	{
		printf("\nInvalid infix Expression.\n");
		getchar();
		exit(1);
	}

	postfix_exp[j] = '\0';
}
float calc(char postfix_exp[])
{
	int i = 0;

	while (postfix_exp[i] != '\0')
	{
		float ele = 0;
		if (isdigit(postfix_exp[i]))
		{
			do
			{
				ele = ele * 10 + postfix_exp[i++] - '0';
			} while (isdigit(postfix_exp[i]));
			fpush(ele);
			// printf("%d ", ftop);
			// printf("%.0f  ", ele);
		}

		else if (postfix_exp[i] == ',')
			i++;
		else if (is_operator(postfix_exp[i]))
		{
			float b = fpop();
			// printf("\n%.0f ", b);
			float a = fpop();
			// printf("\n%.0f ", a);

			switch (postfix_exp[i])
			{
			case '+':
				fpush(a + b);
				break;
			case '-':
				fpush(a - b);
				break;
			case '*':
				fpush(a * b);
				break;
			case '/':
			{
				if (b != 0)
					fpush(a / b);
				else
				{
					printf("\nError: divided by 0");
				}
				break;
			}
			}
			i++;
		}
	}
	return fpop();
}

int main()
{
	char ans = 'y';
	while (ans == 'y' || ans == 'Y')
	{
		char infix[SIZE], postfix[SIZE];
		printf("\nEnter infix expression: ");
		fflush(stdin);
		gets(infix);
		InfixToPostfix(infix, postfix);
		printf("Postfix expression: ");
		puts(postfix);
		printf("\nThe value of exp is: %.1f", calc(postfix));
		printf("\nContinue calculating?(y/n)");
		scanf("%c", &ans);
		if (ans == 'n' || ans == 'N')
			printf("\nSEE YOU LATER!");
	}
	return 0;
}
