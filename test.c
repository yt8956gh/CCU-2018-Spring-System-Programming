#include<stdio.h>
#include<string.h>
#include <unistd.h>
#define MAX 100000

int count=1;//紀錄現為第幾個Fibonacci數

void Fibonacci(int *a, int *b);

int main(void)
{
	int a[MAX],b[MAX];

	//將int陣列中所有的元素設為0，並初始化f0 f1
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	a[0]=0; b[0]=1;

	printf("%04d : %d\n",count++,a[0]);
	printf("%04d : %d\n",count++,b[0]);

	Fibonacci(a,b);

	printf("\npid: %d\n", getpid());

	return 0;
}

void Fibonacci(int *a, int *b)
{
	if(count<=1000000)
	{
		int carry=0,i=0,turn=0,tmp=0;

		for(i=0;i<MAX;i++)//將a[]當作儲存fn的空間
		{
			tmp=a[i]+b[i]+carry;//第一次進位初始為零
			a[i]=tmp%10;
			carry=tmp/10;//計算下一次進位
		}
		
		printf("%04d : ", count++);

		for(i=(MAX-1);i>=0;i--)
		{
			if(turn==0 && a[i]!=0) turn=1;//找出最高位的非零數字
			if(turn==1) printf("%d", a[i]);//找到後開啟printf
		}

		printf("\n");

		Fibonacci(b,a);//因為a[]變成新的Fibonacci數,所以呼叫時放在後面
	}
	
}

