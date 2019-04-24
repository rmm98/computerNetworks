#include <stdio.h>
#include <stdlib.h>
#define fsize 10
#define msize 100
#include <string.h>

struct frame
{
    int fno,sno;
    char mssg[fsize];
};

int n;

void sequence(struct frame frames[])
{
    int ch;
    printf("\n\n1)Manual sequence 2)Random sequence: ");
    scanf("%d",&ch);
    if(ch == 1)
    {
        for(int i=0;i<n;i++)
        {
            printf("\n%s\tSequence no:",frames[i].mssg);
            scanf("%d",&frames[i].sno);
        }
    }
    else if(ch == 2)
    {
        for(int i=0;i<n;i++)
        {
            int r = rand();
            frames[i].sno = r;
            printf("\n%s\tSequence no: %d",frames[i].mssg,r);
        }
    }
}

void sort_disp(struct frame frames[])
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n-1-i;j++)
        {
            if(frames[j].sno > frames[j+1].sno)
            {
                struct frame temp = frames[j];
                frames[j] = frames[j+1];
                frames[j+1] = temp;
            }
        }

    printf("\nThe message on shuffling:\n");
    for(int i=0;i<n;i++)
        printf("Frame no:%d\t%s\n",frames[i].fno,frames[i].mssg);
    printf("The shuffled message:\n");
    for(int i=0;i<n;i++)
        printf("%s",frames[i].mssg);
}

void receiver(struct frame frames[])
{
    printf("\n\nSorting at receiver side to recover original message:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<n-1-i;j++)
        {
            if(frames[j].fno > frames[j+1].fno)
            {
                struct frame temp = frames[j];
                frames[j] = frames[j+1];
                frames[j+1] = temp;
            }
        }

    for(int i=0;i<n;i++)
        printf("Frame no: %d\t%s\n",frames[i].fno,frames[i].mssg);

    printf("Received message:\n");
    for(int i=0;i<n;i++)
        printf("%s",frames[i].mssg);
    printf("\n");
}

void sep()
{
    printf("\nEnter the number of frames: ");
    scanf("%d",&n);
    struct frame frames[n];

    printf("\nEnter the message for each frame:\n");
    for(int i=0;i<n;i++)
    {
        printf("Frame %d: ",i);
        frames[i].fno = i;
        scanf("%s",frames[i].mssg);
    }

    sequence(frames);
    sort_disp(frames);
    receiver(frames);
}

void whole()
{
    char mssg[msize],len,pos=0;
    printf("Enter the message: ");
    scanf("%s",mssg);

    len = strlen(mssg);
    int m = len % fsize;
    n = (len / fsize)+1;
    printf("Frames : %d",n);

    struct frame frames[n];

    int i,j;
    for(i=0;i<n;i++)
    {
        frames[i].fno = i;
        for(j=0;j<fsize;j++)
            frames[i].mssg[j] = mssg[pos++];
        frames[i].mssg[j] = '\0';
    }
    frames[i].fno = i;
    for(j=0;j<m;j++)
        frames[i].mssg[j] = mssg[pos++];
    frames[i].mssg[j] = '\0';

    for(int i=0;i<n;i++)
        printf("\nFrame %d : %s",frames[i].fno,frames[i].mssg);

    sequence(frames);
    sort_disp(frames);
    receiver(frames);
}

void main()
{
    int ch;
    printf("1)Independent frame messages 2)Whole message : ");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1:
            sep();
            break;
        case 2:
            whole();
            break;
        default:
            printf("Enter a valid choice");
    }
}
