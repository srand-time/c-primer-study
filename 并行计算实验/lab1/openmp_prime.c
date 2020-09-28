#include <omp.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#define N 1000000
#define NUM_THREADS 4
//1000--->168
void main()
{
	omp_set_num_threads(NUM_THREADS);
	int num[NUM_THREADS];
	clock_t t1,t2;
	t1=clock();
	int i,j;
    #pragma omp parallel private(i,j)
	{
		int id;
	  	id = omp_get_thread_num();
		num[id] = 0;
		#pragma omp parallel for
	 	for (i=2+id;i< N; i=i+NUM_THREADS)
		{
		for(j=2; j<=sqrt(i); j++)
			 if(i%j==0 ) break;
		if( j>sqrt(i) )
			  {
				num[id]++;
			  	//printf("线程ID=%d,素数是=%d\n",omp_get_thread_num(),i);
			  }
	  	}
	  }
	t2=clock();
	int sum=0;
	for(int i=0;i<NUM_THREADS;i++)
		sum+=num[i];
	printf("此时并行程序数 %d\n",NUM_THREADS);
	printf("小于%d的素数共有%d个\n",N,sum);
	printf("并行时间是%d ms\n",t2-t1);
}
