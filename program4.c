#include<stdio.h>
#include<ctype.h>
int main()
{
    char infix[50],postfix[50],stack[50];
	int top=-1;
	int i=0,j=0;
	
	printf("Enter infix expression:");
	scanf("%s",infix);
	
	while(infix[i] !='\0')
	{
		char ch = infix[i];
		
		if(isalnum(ch))
		{
		   postfix[j++]=ch;	
		}
		else if(ch=='(')
		{
			stack[++top]=ch;
		}
		else if(ch==')')
		{
			while(top != -1 && stack[top]!='(')
			{
				postfix[j++]= stack[top--];
			}
			top--;
			else{
				while(top!=-1 && stack[top] !='('&&((ch=='+'||ch=='-')&&(stack[top]=='*'||stack[top]=='/'||stack[top]=='^'))||((ch=='*'||ch=='/')&&(stack[top]=='^')))
				)
				{
					postfix[j++]=stack[top-1];
				}
				stack[++top]=ch;
			}
			i++;
		}
		while(top!=-1)
		{
			postfix[j++]=stack[top--];
		}
	}
	postfix[j]='\0';
	printf("postfix Expression:%s\n",postfix);
	return 0;	
}