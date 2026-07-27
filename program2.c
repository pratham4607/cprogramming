#include<stdio.h>
int main(){
	int stack[5];
	int top=-1;
	int choice,item,i;
	do{
		printf("\n1.push\n");
		printf("2.pop\n");
		printf("3.peek\n");
		printf("4.Dispaly\n");
		printf("5.Extra\n");
		printf("Enter your choice:");
		scanf("%d",&choice);
		switch(choice){
			case 1://push
			if(top==4){
				printf("Stack overflow\n");
			}
			else{
				printf("Enter element:");
				scanf("%d",&item);
				top=top+1;
				stack[top]=item;
			}
			break;
			case 2:
				if(top==-1){
					printf("stack underflow");
				}
				else{
					printf("deleted element:%d\n",stack[top]);
					top=top-1;
				}
				break;
			case 3:
				if(top==-1){
					printf("stack is empty\n");
					
				}
				else{
					printf("top element:%d\n",stack[top]);
				}
				break;
				case 4:
				if(top==-1)
				{
					printf("Stack is empty\n");
			}
			else
			{
				printf("Stack element are:\n");
				for(i=top;i>=0;i--)
				{
					printf("%d\n",stack[i]);
				}
			}
			    break;
			    case 5:
			    printf("program Ended\n");
			    break;
				default:
				printf("Invalid Choice\n");
			}
		}while(choice !=5);
		return 0;
		}