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
			  	//printf("�߳�ID=%d,������=%d\n",omp_get_thread_num(),i);
			  }
	  	}
	  }
	t2=clock();
	int sum=0;
	for(int i=0;i<NUM_THREADS;i++)
		sum+=num[i];
	printf("��ʱ���г����� %d\n",NUM_THREADS);
	printf("С��%d����������%d��\n",N,sum);
	printf("����ʱ����%d ms\n",t2-t1);
}
