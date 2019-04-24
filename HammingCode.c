#include <stdio.h>
#include <stdlib.h>
#define max 50

int data[max],hamCode[max];

int computeHamCode(int k)
{
    int r = 0,j = 0;
    for(int i=1;i<=k+r;i++)
    {
        if( i == pow(2,r))
        {
            hamCode[i] = 0;
            r++;
        }
        else
            hamCode[i] = data[j++];
    }
    return r;
}

int findParityBits(int k,int r)
{
    int t = 0,errpos = 0;
    for(int i=0;i<k+r;i++)
    {
        if(i == pow(2,t))
        {
            int xor = hamCode[i];
            for(int j = i+1;j<=k+r;j++)
            {
                if((i&j) != 0)
                    xor = xor ^ hamCode[j];
            }
            hamCode[i] = xor;
            t++;
            if(xor)
                errpos += i;
        }
    }
    return errpos;
}

int findErrorType(int errpos,int r)
{
    for(int i=1;i<pow(2,r);i*=2)
    {
        if(i == errpos)
            return 1;
    }
    return 0;
}

void main()
{
    int k,r;
    printf("Enter the number of data bits: ");
    scanf("%d",&k);
    printf("Enter the data bits: ");
    for(int i=0;i<k;i++)
        scanf("%d",&data[i]);

    r = computeHamCode(k);
    printf("The number of parity bits are: %d",r);
    findParityBits(k,r);
    printf("Transmitted data: \n");
    for(int i=1;i<=k+r;i++)
        printf("%d ",hamCode[i]);
    printf("\n");

    int ch,pos;
    printf("Do you want to corrupt the data?");
    scanf("%d",&ch);
    if(ch)
    {
        printf("Enter the pos between 1 and %d: ",(k+r));
        scanf("%d",&pos);
        hamCode[pos] = !(hamCode[pos]);
    }

    printf("Receiver:\n");
    printf("Received data:\n");
    for(int i=1;i<=k+r;i++)
        printf("%d ",hamCode[i]);
    int errpos = findParityBits(k,r);
    if(errpos)
    {
        if(findErrorType(errpos,r))
        {
            printf("Data is fine.Parity bit at %d corrupted.",errpos);
        }
        else
        {
            printf("data bit at &d corrupted.\n",errpos);
            hamCode[errpos] = !(hamCode[errpos]);
            printf("Corrected data:\n");
            for(int i=1;i<=k+r;i++)
                printf("%d ",hamCode[i]);
        }
    }
    else
        printf("No error.");
}
