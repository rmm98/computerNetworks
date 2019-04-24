#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define llu unsigned long long int

llu gcd(llu a,llu b);
llu xpowymodn(llu x,llu y,llu n);

void main()
{
    llu p,q;
    printf("Enter two large prime numbers p and q:");
    scanf("%llu%llu",&p,&q);

    llu n,z,e,d;
    n = p*q;
    z = (p-1)*(q-1);
    printf("n = %llu\nz = %llu\n",n,z);

    for(llu i =2;i<z;i++)
    {
        if(gcd(i,z)==1)
        {
            for(llu j=0;j<=n;j++)
            {
                if((i*j)%z == 1)
                {
                    e = i;
                    d = j;
                    printf("%llu\t%llu\n",e,d);
                }
            }
        }
    }

    printf("Public Key = {%llu, %llu}\n",e,n);
    printf("Private Key = {%llu, %llu}\n",d,n);

    printf("Enter the message:");
    char mssg[100];
    scanf("%s",mssg);
    int len = strlen(mssg);
    llu plaintext[100],ciphertext[100];
    for(int i=0;i<len;i++)
    {
        plaintext[i] = mssg[i];
        printf("%llu ",plaintext[i]);
    }

    printf("\nEncrypting:\n");
    for(int i=0;i<len;i++)
    {
        ciphertext[i] = xpowymodn(plaintext[i],e,n);
        printf("%llu ",ciphertext[i]);
    }

    printf("\nDecrypting:\n");
    for(int i=0;i<len;i++)
    {
        printf("%c ",xpowymodn(ciphertext[i],d,n));
    }
}

llu gcd(llu a,llu b)
{
    if(b==0)
        return a;
    else
        return gcd(b,a%b);
}

llu xpowymodn(llu x,llu y,llu n)
{
    llu r = 1;
    while(y > 0)
    {
        if((int)y%2 == 1)
            r = (r*x)%n;
        x = (x*x)%n;
        y = y/2;
    }
    return r;
}













