#include <stdio.h>
#include <math.h>
main(void)
{
    int i, j, k, H, m;
    int N, N1, N2, N3;
    N1 = N2 = N3 = 0;
    int *p, *q, *n, *s;
    double b1[3], b2[3], b3[3];
    int a1[3], a2[3], a3[3]; /*a1,a2,a3代表三个车道*/
    p = a1;
    q = a2;
    n = a3;
    // s = b1;
    printf("请输入车道数：\n");
    scanf("%d", &m, 5);
    printf("%d", m);
    if (m == 3)
    {
        printf("请输入车道1各个方向的车流量：\n");
        for (i = 0; i < 3; p++, i++)
        {
            scanf("%d", q, 5);
        }
        printf("%d,%d,%d\n", a1[0], a1[1], a1[2]);
        printf("请输入车道2各个方向的车流量：\n");
        for (j = 0; j < 3; q++, j++)
        {
            scanf("%d", q, 5);
        }
        printf("%d,%d,%d\n", a2[0], a2[1], a2[2]);
        printf("请输入车道3各个方向的车流量：\n");
        /*将各个车道的车 流量输入，假设a[0]代表左转车流，a[1]代表直行车流,a[2]代表右转车流,若某车道没有某个方向的车流，则置零*/
        for (k = 0; k < 3; n++, k++)
        {
            scanf("%d", n, 5);
        }
        printf("%d,%d,%d\n", a3[0], a3[1], a3[2]);
        printf("冲突时距H：\n");
        scanf("%d", &H, 5);
        printf("%d\n", H);
        for (i = 0; i < 3; i++)
        {
            b1[i] = (a1[i] / (double)3600) * (exp(-H * (a1[i] / (double)3600)));
        }
        printf("%f\n", b1[1]);
        printf("车道11车流:%f，车道12车流 : %f，车道13车流 : %f\n", b1[0], b1[1], b1[2]);
        for (j = 0; j < 3; j++)
        {
            b2[j] = (a2[j] / (double)3600) * (exp(-H * (a2[j] / (double)3600)));
        }
        printf("车道21车流:%f，车道22车流 : %f，车道23车流 : %f\n", b2[0], b2[1], b2[2]);
        for (k = 0; k < 3; k++)
        {
            b3[k] = (a3[k] / (double)3600) * (exp(-H * (a3[k] / (double)3600)));
        }
        printf("车道311车流:%f，车道32车流 : %f，车道33车流 : %f\n", b3[0], b3[1], b3[2]);
        for (i = 0; i < 3; i++)
        {
            if (i == 0)
                continue;
            if (i == 1)
            {
                for (j = 0; j < 3; j++)
                {
                    if (j != 1)
                        N1 += 3600 * H * b1[i] * (b2[j] + b3[j]);
                }
            }
            else
                N1 += 3600 * H * b1[i] * (b2[1]);
        }
        for (j = 0; j < 3; j++)
            if (j == 1)
                continue;
        if (j == 0)
        {
            for (k = 0; k < 3; k++)
            {
                if (k != 2)
                    N2 += 3600 * H * b2[j] * (b1[k] + b3[k]);
            }
        }
        else
            N2 += 3600 * H * b2[j] * (b1[1]);
        for (k = 0; k < 3; k++)
            if (k == 2)
                continue;
        if (k == 1)
        {
            for (j = 0; j < 3; j++)
            {
                N3 += 3600 * H * b3[k] * (b1[j]);
                if (j != 2)
                    N3 += 3600 * H * b3[k] * (b2[j]);
            }
        }
        else
            N3 += 3600 * H * b3[k] * (b1[1]);
        N = N1 + N2 + N3;
        N = 0.5 * N;

        printf("该交叉口冲突数为：%f", N);
    }
    system("pause");
    return 0;
}
