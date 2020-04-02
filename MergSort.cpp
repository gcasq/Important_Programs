#include<stdio.h>

#define max 1100
int n,v[max],u[max];

void merge_sort(int ini, int fim)
{
    int j,i,tam;
    if(ini==fim){return;}  //vetor ja ordenado
    else
    {
        merge_sort(ini,(ini+fim)/2);
        merge_sort((ini+fim)/2+1,fim);

        tam=0;
        j=(ini+fim)/2+1;

        for(i=ini;i<=(ini+fim)/2;i++)
        {
            while(j<=fim && v[j]<v[i])
            {
                u[tam]=v[j];
                j++;tam++;
            }
            u[tam]=v[i];
            tam++;
        }
        while(j<=fim)
        {
            u[tam]=v[j];
            tam++;j++;
        }

        for(i=ini;i<=fim;i++){v[i]=u[i-ini];}

    }
}

int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++){scanf("%d",&v[i]);}

    merge_sort(0,n-1);

    for(int i=0;i<n;i++){printf("%d\t",v[i]);}

    printf("\n");

return 0;}
