#include <stdio.h>
#include <ctype.h>
int main()
{
int stack[50];
int top = -1;
char postfix[50];
int i, op1, op2, result;
printf("Enter postfix expression: ");
scanf("%s", postfix);
for(i = 0; postfix[i] != '\0'; i++)
{
char ch = postfix[i];
// If operand → push to stack
if(isdigit(ch))
{
stack[++top] = ch - '0'; // convert char to int
}
// If operator → pop two elements
else
{
op2 = stack[top--];
op1 = stack[top--];
switch(ch)
{
case '+':
result = op1 + op2;
break;
case '-':
result = op1 - op2;

break;
case '*':
result = op1 * op2;
break;
case '/':
result = op1 / op2;
break;
}
stack[++top] = result;
}
}
printf("Result = %d\n", stack[top]);
return 0;
}
