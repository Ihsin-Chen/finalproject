#include<stdio.h>
#define MAXNUM 1000006

int arr[MAXNUM];
long long int prefix[MAXNUM];

int main()
{
    int n,q,l,r,m;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&arr[i]);
        if(arr[i]<0) arr[i]=0;
        prefix[i] = prefix[i-1]+arr[i];
    }

    while(q--)
    {
        scanf("%d%d%d",&l,&r,&m);
        printf("%lld\n",prefix[l+m-1]-prefix[l-1]);
    }
    return 0;

}
