//由高数里的知识可知，根据上述公式可以求得pi/4。
#include<stdio.h>
#include<mpi.h>
int main(int argc,char *argv[]){
	int my_rank,num_procs;
	int i,j;
	int n=500000;//循环次数
	int sum,mysum;
	double start =0.0,stop = 0.0;


	MPI_Init(&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&num_procs);

	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

	printf("Process rank:%d ,total process :%d\n",my_rank,num_procs);
	if(my_rank == 0)
    {
		start = MPI_Wtime();
	}
    sum=0;
    mysum=0;
	for(i = 3+my_rank;i<n;i+=num_procs)
    {
        int flag=0;
		for(j=2;j<sqrt(i)+1;j++)
            if(i%j==0)
                {flag=1;break;}
        if(flag==0)
            mysum++;
	}
	MPI_Reduce(&mysum,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

	if(my_rank == 0)
    {
        printf("循环次数: %d\n",n);
		printf("素数个数 %d\n",sum+1);
		stop = MPI_Wtime();
		printf("Time:%.4f ms\n",(stop-start)*1000);
	}
	MPI_Finalize();
	return 0;
}
