#include <stdio.h>
#include <stdlib.h>

struct reg
{
    int bit;
}r[16];

int n;

void crc(int data[])
{
    int feedback;

    for(int i=0;i<16;i++)
        r[i].bit = 0;

    for(int i=0;i<n+16;i++)
    {
        feedback = r[15].bit;

        for(int j=15;j>=0;j--)
            r[j].bit = r[j-1].bit;

        r[0].bit = data[i];

        if(feedback == 1)
        {
            r[12].bit = r[12].bit ^ feedback;
            r[5].bit = r[5].bit ^ feedback;
            r[0].bit = r[0].bit ^ feedback;
        }
    }

    printf("Register content :\n");
    for(int i=15;i>=0;i--)
        printf("%d ",r[i].bit);

    int pos = 15;
    for(int i=n;i<n+16;i++)
        data[i] = r[pos--].bit;

    printf("\nThe message with CRC:\n");
    for(int i=0;i<n+16;i++)
        printf("%d ",data[i]);
}

void main()
{
    printf("Sender side : \n");
    printf("Enter the number of bits of data: ");
    scanf("%d",&n);

    int data[n+16];
    printf("Enter the data :");
    for(int i=0;i<n;i++)
        scanf("%d",&data[i]);
    for(int i=n;i<n+16;i++)
        data[i] = 0;
    crc(data);

    printf("\nData being transmitted.");
    int ch;
    int pos;
    printf("\nDo you want to corrupt the data? Yes = 1 / No = 0 :");
    scanf("%d",&ch);
    while(ch == 1)
    {
        printf("Enter the bit position between 0 to %d : ",n+15);
        scanf("%d",&pos);
        if(data[pos] == 0)
            data[pos] = 1;
        else
            data[pos] = 0;
        printf("\nDo you want to corrupt another data bit? Y/N :");
        scanf("%d",&ch);
    }

    printf("\nReceiver side : \n");
    printf("Message received:\n");
    for(int i=0;i<n+16;i++)
        printf("%d ",data[i]);
    printf("\n");
    crc(data);
    printf("\nError check:\n");
    for(int i=15;i>=0;i--)
        if(r[i].bit != 0)
        {
             printf("Data has been altered.");
             printf("Position : %d",i);
             exit(0);
        }
    printf("Received data is unaltered.");
}
