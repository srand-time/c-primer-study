#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>
#define n 5000000    //总共有多少个数字
int a[n];       //待排序数组
int sample1[5000000]; //样本
int sample2[10]; //主元


//qsort中使用到的cmp
int cmp ( const void *a , const void *b )
{ return *(int *)a - *(int *)b; }

void main(int argc,char *argv[])
{
    init();
    int i,j,k;
    int myid, numprocs;
    double start=0.0,end=0.0;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    int* mpi_buffer=malloc(sizeof(int)*100000000);
	MPI_Buffer_attach(mpi_buffer,sizeof(int)*100000000);
    if(myid == 0)
    {
		//MPI_Wtime返回一个用浮点数表示的秒数,计时
		start = MPI_Wtime();
	}

	//局部排序
    qsort(a+(n/numprocs)*myid,n/numprocs,sizeof(int),cmp);
    MPI_Barrier(MPI_COMM_WORLD);

    //将局部排序结果汇总到0号线程中
	if(myid!=0)
    MPI_Bsend((a+((n/numprocs)*(myid))),4*(n/numprocs),
        MPI_BYTE,0,myid,MPI_COMM_WORLD);


    if(myid==0)
    {
        //0号线程接收其他线程的消息
        MPI_Status status;
        for(j=1;j<numprocs;j++)
        MPI_Recv((a+((n/numprocs)*(j))),4*(n/numprocs),
                 MPI_BYTE,j,j,MPI_COMM_WORLD,&status);

        //选出排序样本并对其排序
        for(i=0;i<numprocs*numprocs;i++)
            sample1[i]=a[i*n/(numprocs*numprocs)];
        qsort(sample1,numprocs*numprocs,sizeof(int),cmp);

        //选出主元
        for(i=1;i<numprocs;i++)
            sample2[i-1]=sample1[i*numprocs];


        //将主元传给其他所有线程
        for(j=1;j<numprocs;j++)
        MPI_Bsend(sample2,4*(numprocs-1),MPI_BYTE,
                  j,10+j,MPI_COMM_WORLD);

    }

    //除了0号线程以外的线程接收主元
    if(myid!=0)
    {
        MPI_Status status;
        MPI_Recv(sample2,4*(numprocs-1),MPI_BYTE,
                  0,10+myid,MPI_COMM_WORLD,&status);
    }


    //主元已传递给各个线程



    int partitionSizes[9]={0};
    //每个线程划分其所拥有的元素
    int newpartitionSizes[9];
    //全局交换后每个线程所拥有的元素
    int index=0;
    //按照主元对各个线程进行划分
    for(i=(n/numprocs)*myid;i<(n/numprocs)*(myid+1);i++)
    {
        if(a[i]>sample2[index])
        {
            //如果当前位置的数字大小超过主元位置，则进行下一个划分
            index++;
        }
        if(index==numprocs)
        {
            //最后一次划分，子数组总长减掉当前位置即可得到最后一个子数组划分的大小
            partitionSizes[numprocs-1]=(n/numprocs)*(myid+1)-i+1;
            break;
        }
        partitionSizes[index]++;   //划分大小自增
    }
    //partitonSizes已正确计算


    // 全局到全局的发送
    MPI_Alltoall(partitionSizes,4,MPI_BYTE,
        newpartitionSizes,4,MPI_BYTE,MPI_COMM_WORLD);
    int totalSize=0;
    // 计算划分的总大小，并给新划分分配空间
    for(i=0;i<numprocs;i++) {
        totalSize+=newpartitionSizes[i];
    }
    int *newpartitions = (int *) malloc(totalSize * sizeof(int));
    int *sendDisp=(int*)malloc(numprocs*4);
    int *recvDisp=(int*)malloc(numprocs*4);

    // 在发送划分之前计算相对于sendbuf的位移，此位移处存放着输出到进程的数据
    sendDisp[0]=0;
    recvDisp[0]=0;//计算相对于recvbuf的位移，此位移处存放着从进程接受到的数据
    for(i=1;i<numprocs;i++){
    sendDisp[i]=partitionSizes[i-1]+sendDisp[i-1];
    recvDisp[i]=newpartitionSizes[i-1]+recvDisp[i-1];
    }


    MPI_Alltoall(partitionSizes, 1, MPI_INT, newpartitionSizes,
               1, MPI_INT, MPI_COMM_WORLD);

    //发送数据，实现n次点对点通信
    MPI_Alltoallv(a+(n/numprocs)*myid, partitionSizes, sendDisp,
                MPI_INT, newpartitions,
                newpartitionSizes, recvDisp, MPI_INT, MPI_COMM_WORLD);




    qsort(newpartitions,totalSize,sizeof(int),cmp);
    //现在已经局部有序并且按线程号有序,还差汇总


    //将局部排序结果汇总到0号线程中
    /*----------------------------MPI_Gather详解-----------------------------*/
    //功能：
    //  Each process (root process included) sends the contents of its send
    //  buffer to the root process. The root process receives the messages and
    //  stores them in rank order.
    //  每个进程(包含根进程)将自己send数据缓存中的数据发送给根进程，根进程接收
    //  所有发来的消并按进程标识排序
    //函数参数：
    //  MPI_Gather(数据发送缓存地址，数据个数，数据类型，数据接收缓存地址，
    //  数据个数，数据类型，根进程标识，通信域）

    int *subListSizes = (int *) malloc(numprocs * sizeof(int));
    // 发送各子列表的大小回根进程中
    MPI_Gather(&totalSize, 1, MPI_INT,
            subListSizes, 1, MPI_INT, 0, MPI_COMM_WORLD);
    // 计算根进程上的相对于recvbuf的偏移量
    if(myid ==0){
        recvDisp[0] = 0;
        for ( i = 1; i < numprocs; i++) {
        recvDisp[i] = subListSizes[i - 1] + recvDisp[i - 1];
        }
    }
    //发送各排好序的子列表回根进程中
    MPI_Gatherv(newpartitions,totalSize, MPI_INT, a,
                subListSizes, recvDisp, MPI_INT, 0, MPI_COMM_WORLD);


    if(myid==0)
    {
        end=MPI_Wtime();
        printf("Time:%.4f ms\n",(end-start)*1000);
        print();
    }
    MPI_Finalize();
}

void init()
{
    srand(time(NULL));
    int i;
    for(i=0;i<n;i++)
    {
        a[i]=rand()%100;
    }
}
void print()
{
    printf("sort finished!\n");
}

