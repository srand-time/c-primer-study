#include<stdio.h>
#include <omp.h>
#include <sys/time.h>
static long num_steps = 10000000;
double step;
#define NUM_THREADS 4
void main ()
{
	  int i;
	  double x, pi, sum;
	  step = 1.0/(double) num_steps;
	  omp_set_num_threads(NUM_THREADS);
	  struct timeval tpstart,tpend;
    	  float timeuse;
     	  gettimeofday(&tpstart,NULL);
	  sum=0.0;
	  printf("此时并行程序数 %d\n",NUM_THREADS);
	  printf("此时循环次数 %ld\n",num_steps);
	  #pragma omp parallel private(i,x)
	  {
		#pragma omp parallel for reduction(+:sum)
	 	for (i=0;i< num_steps; i++)
		{
			//printf("线程ID=%d,i=%d\n",omp_get_thread_num(),i);
		 	 x = i*step;
		  	sum += 4.0/(1.0+x*x);
	  	}
	 }
pi += sum* step;
printf("Pi = %.16lf\n",pi);
	gettimeofday(&tpend,NULL);
    	timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
   	timeuse/=1000000;
  	printf("Used Time:%f s\n",timeuse);
}
