#include <stdio.h>
int main()
{
    int queue[5];
    int front = -1, rear = -1;
    int choice, item, i;
    do
    {
        printf("\n1. Enqueue (Insert)\n");
        printf("2. Dequeue (Delete)\n");
        printf("3. Peek (Front)\n");
        printf("4. Display\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:   // Enqueue
                if(rear == 4)
                {
                    printf("Queue Overflow\n");
                }
                else
                {
                    printf("Enter element: ");
                    scanf("%d", &item);

                    if(front == -1)
                    {
                        front = 0;
                    }

                    rear = rear + 1;
                    queue[rear] = item;

                    printf("Inserted successfully\n");
                }
                break;

            case 2:   // Dequeue
                if(front == -1 || front > rear)
                {
                    printf("Queue Underflow\n");
                }
                else
                {
                    printf("Deleted element = %d\n", queue[front]);
                    front = front + 1;
                }
                break;

            case 3:   // Peek
                if(front == -1 || front > rear)
                {
                    printf("Queue is empty\n");
                }
                else
                {
                    printf("Front element = %d\n", queue[front]);
                }
                break;

            case 4:   // Display
                if(front == -1 || front > rear)
                {
                    printf("Queue is empty\n");
                }
                else
                {
                    printf("Queue elements are:\n");

                    for(i = front; i <= rear; i++)
                    {
                        printf("%d ", queue[i]);
                    }
                    printf("\n");
                }
                break;

            case 5:
                printf("Program Ended\n");
                break;

            default:
                printf("Invalid Choice\n");
        }

    } while(choice != 5);

    return 0;
}