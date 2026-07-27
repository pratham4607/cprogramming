#include<stdio.h>
int main()
{
	int arr[100],n,i;
	int pos,value,key;
	printf("Enter number of element:");
	scanf("%d",&n);
	printf("Enter array element:\n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	printf("\nArray Elements:");
	for(i=0;i<n;i++)
	{
		printf("%d",arr[i]);
	} 
	printf("n\nEnter position to insert(0 to %d):",n);
	scanf("%d",&pos);
	printf("Enter a value to insert:");
	scanf("%d",&value);
	for(i=n;i>pos;i--)
	{
		arr[i]=arr[i-1];
	}
	arr[pos]=value;
	n++;
	printf("Array after=r insertion:");
	for(i=0;i<n;i++)
	{
		printf("%d",&arr[i]);
	}
	printf("n\nEnter position to delete(0 to %d):",n-1);
	scanf("%d",&pos);
	for(i=pos;i<n-1;i++)
	{
		arr[i]=arr[i+1];
	}
	n--;
	printf("Array after delection: ");
	for(i=0;i<n;i++)
	{
		printf("%d",arr[i]);
	}
	printf("n\nEnter element to serach:");
	scanf("%d",&key);
	for(i=0;i<n;i++)
	{
		if(arr[i]==key)
		{
	     printf("Element found at index %d",i);
		 break;
        }
    }
    if(i==n)
    {
    	printf("Element not found");
    }
        return 0;
	
}