#include <stdio.h>
#include <stdlib.h>
#define infinite 99

struct
{
    int cost;
    int via;
}table[10][10];

int n;

void buildTable()
{
    for(int i=0;i<n;i++)
    {
        printf("Routing table for %c: \n",'A'+i);
        printf("Enter 999 if not immediate neighbour.\n");
        for(int j=0;j<n;j++)
        {
            printf("->%c = ",'A'+j);
            if(i==j)
                table[i][j].cost = 0,printf("0\n");
            else
                scanf("%d",&table[i][j].cost);
            if(table[i][j].cost != infinite)
                table[i][j].via = j;
            else
                table[i][j].via = infinite;
        }
    }
}

void constructTable(int i)
{
    for(int j=0;j<n;j++)
    {
        for(int k=0;k<n && j!= i;k++)
        {
            if(table[i][j].cost != infinite)
            {
                int newCost = table[i][j].cost + table[j][k].cost;
                if(table[i][k].cost > newCost)
                {
                    table[i][k].cost = newCost;
                    table[i][k].via = table[i][j].via;
                }
            }
        }
    }
}

void dispTable(int i)
{
    printf("Routing table of %c:\n",'A'+i);
    printf("%5s%5s%5s\n","Node","Cost","Via");
    for(int j=0;j<n;j++)
    {
        printf("%5c%5d%5c\n",'A'+j,table[i][j].cost,'A'+table[i][j].via);
    }
}

void findPath(int i,int j)
{
    printf("%c",'A'+i);
    if(i != j)
    {
        printf("-->");
        findPath(table[i][j].via,j);
    }
}
void main()
{
    printf("Enter the number of nodes: ");
    scanf("%d",&n);

    buildTable();

    int c = 2;
    while(c != 0)
    {
        for(int i=0;i<n;i++)
            constructTable(i);
        c--;
    }

    for(int i=0;i<n;i++)
        dispTable(i);

    while(1)
    {
        int src,dest;
        printf("\nEnter the source node (0 to %d): ",n-1);
        scanf("%d",&src);
        printf("Enter the dest node(0 to %d): ",n-1);
        scanf("%d",&dest);
        printf("The shortest path is: ");
        findPath(src,dest);
        printf("\nCost of shortest path = %d",table[src][dest].cost);
        printf("\nPress 1 to close: ");
        int op;
        scanf("%d",&op);
        if(op)
            exit(0);
    }
}
