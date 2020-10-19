#include <stdio.h>
#define MAXSIZE 1000006
int prices[MAXSIZE];
int n;
int maxProfit(int prices[])
{
    int minprice = 2147483647;
    int maxprofit = 0;
    for (int i = 0; i < n; i++)
    {
        if (prices[i] < minprice)
            minprice = prices[i];
        else if (prices[i] - minprice > maxprofit)
        {
            maxprofit = prices[i] - minprice;
        }
    }
    return maxprofit;
}
int main()
{

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &prices[i]);
    }
    printf("%d", maxProfit(prices));
    return 0;
}
