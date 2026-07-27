#include<stdio.h>
int main()
{
	int a[10],b[10],c[10];
	int m,n,i,max;
	printf("Enter degreen of first polynomial:");
	scanf("%d",&m);
	printf("Enter coefficients of first polynomial:\n");
	for(i=0;i<=m;i++)
	{
		scanf("%d",&a[i]);
	}
	printf("Enter degree of second polynomial:");
	scanf("%d",&n);
	printf("Enter coefficient of second polynomial:\n");
	for(i=0;i<=n;i++)
	{
	    scanf("%d",&b[i]);	
	}
	if(m>n)
	max=m;
	else
	max=n;
	for(i=0;i<=max;i++)
	{
		a[i]=(i<=m?a[i]:0);
		b[i]=(i<=n?b[i]:0);
		c[i]=a[i]+b[i];
	}
	printf("\nResultant polynomial coefficient:\n");
	for(i=max;i>=0;i--)
	{
		printf("%dx^%d",c[i],i);
		if(i !=0)
		printf("+ ");
	}
	return 0;
}