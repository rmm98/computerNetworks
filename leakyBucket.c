#include <stdio.h>
#include <stdlib.h>
#define bucketSize 250
#define outRate 25

struct
{
    int arrivalTime;
    int size;
}packet[15];


void leakyBucket()
{
    int pno=0;
    int free = bucketSize;
    int used =0;
    int i;

    //30 seconds
    for(i=0;i<=30;i++)
    {
        //input
        if(packet[pno].arrivalTime == i)
        {
            if(packet[pno].size <= free)
            {
                free -= packet[pno].size;
                used += packet[pno].size;
                printf("\nAt Time = %d, Packet %d inserted into bucket",i,pno);
                printf("\nAvailable bucket size = %d",free);
                pno++;
            }
            else
            {
                printf("At time = %d, Packet %d discarded",i,pno);
                pno++;
            }
        }

        //output
        if(i%5 == 0)
        {
            if(used >= outRate)
            {
                used -= outRate;
                free += outRate;
                printf("\nAt time = %d, 25KB transferred",i);
                printf("\nAvailable bucket space = %d",free);
            }
            else if(used > 0)
            {
                free += used;
                printf("\nAt time = %d, %KB transferred",i,used);
                used = 0;
                printf("\nAvailable space in bucket = %d",free);
            }
        }
        printf("\n");
    }

    //after
    i += 4;
    while(used > 0)
    {
        if(used >= outRate)
        {
            free += outRate;
            used -= outRate;
            printf("\nAt time = %d, 25KB transferred",i);
            printf("\nAvailable bucket size = %d",free);
            i += 5;
        }
        else
        {
            free += used;
            printf("\nAt time = %d, %dKB transferred",i,used);
            used = 0;
            printf("\nAvailable space in bucket = %d",free);
        }
        printf("\n");
    }

    printf("\nBucket is empty!");
}
void main()
{
    int n;
    printf("Enter the number of packets:");
    scanf("%d",&n);
    printf("Enter the arrival time and size:\n");
    for(int i=0;i<n;i++)
    {
        printf("Packet %d :",i);
        scanf("%d%d",&packet[i].arrivalTime,&packet[i].size);
    }
    leakyBucket();
}
