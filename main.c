#include <stdio.h>
#include <stdlib.h>

int is_negative = 0;

//获取长整数，返回整数长度加1
char* get_num(char *str, int *n, int strlen)
{
    int count = 0,i;
    char cha;
    do
    {
        cha = getchar();
        if(count >= strlen)
        {
            str = (char*)realloc(str, sizeof(char*) * (++strlen));
        }
        count ++;
        str[count - 1] = cha;
    }
    while (cha != '\n'); //输入回车时终止输入
    if (str[0]=='-') //输入为负数时的处理
    {
        if(is_negative == 0)
            is_negative = 1;
        else
            is_negative = 0;

        for(i=0;i<count;i++)
        {
            str[i]=str[i+1];
        }
        count--;
    }
    *n = count;
    return str;
}

//将字符串转化为整数数组
void str_to_arr(char *s, int *a, int n)
{
    int i,j;
    a[0] = n -1 ;
    for(i=1, j=n-1; i<n;i++,j--)-1
    {
        a[j] = s[i-1] - 48; //48为0的ASCII编码
    }
}

//输出长整数
void print_int(int *a, int n)
{
    int i=n-1;
    while (a[i] == 0 && i != 1) i--; //去除整数前多余的0
    for(;i>0;i--)
    {
        printf("%d", a[i]);
    }
    printf("\n");
}

//乘法函数
void multiply_arr(int *a, int *b, int *c, int n1, int n2)
{
    int i,j,k,temp=0, n3 = n1 + n2 + 1;
    c[0] = n3;
    //初始化结果数组
    for(i=1;i<n3;i++) c[i] = 0;

    for(i=1;i<n1;i++)
        for(j=1;j<n2;j++)
        {
            k = i+j-1;
            c[k] += a[i] * b[j];
        }

    //进位操作
    for(i=1;i<n3;i++)
    {
        c[i] += temp;
        temp = c[i] / 10;
        c[i] %= 10;
    }
}


int main()
{
    int strlenth = 5; //默认长度
    int count1, count2;

    printf("请输入第一个整数:\n");
    char *str1 = (char*)calloc(strlenth, sizeof(char*)); //获取第一个整数
    str1 = get_num(str1, &count1, strlenth); //获取第一个整数长度

    printf("请输入第二个整数:\n");
    char *str2 = (char*)calloc(strlenth, sizeof(char*)); //获取第二个整数
    str2 = get_num(str2, &count2, strlenth); //获取第二个整数长度

    int a[count1], b[count2], fin[count1 + count2 + 1]; //两个乘数，一个积

    str_to_arr(str1, a, count1);
    str_to_arr(str2, b, count2); //将乘数转换为长整数

    multiply_arr(a,b,fin,count1,count2);

    printf("两个整数的积为:\n");
    if(is_negative == 1) printf("-");
    print_int(fin, count1 + count2);

    free(str1); //释放内存
    free(str2);
    return 0;
}
