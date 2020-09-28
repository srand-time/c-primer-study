#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>
#define n 5000000    //�ܹ��ж��ٸ�����
int a[n];       //����������
int sample1[5000000]; //����
int sample2[10]; //��Ԫ


//qsort��ʹ�õ���cmp
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
		//MPI_Wtime����һ���ø�������ʾ������,��ʱ
		start = MPI_Wtime();
	}

	//�ֲ�����
    qsort(a+(n/numprocs)*myid,n/numprocs,sizeof(int),cmp);
    MPI_Barrier(MPI_COMM_WORLD);

    //���ֲ����������ܵ�0���߳���
	if(myid!=0)
    MPI_Bsend((a+((n/numprocs)*(myid))),4*(n/numprocs),
        MPI_BYTE,0,myid,MPI_COMM_WORLD);


    if(myid==0)
    {
        //0���߳̽��������̵߳���Ϣ
        MPI_Status status;
        for(j=1;j<numprocs;j++)
        MPI_Recv((a+((n/numprocs)*(j))),4*(n/numprocs),
                 MPI_BYTE,j,j,MPI_COMM_WORLD,&status);

        //ѡ��������������������
        for(i=0;i<numprocs*numprocs;i++)
            sample1[i]=a[i*n/(numprocs*numprocs)];
        qsort(sample1,numprocs*numprocs,sizeof(int),cmp);

        //ѡ����Ԫ
        for(i=1;i<numprocs;i++)
            sample2[i-1]=sample1[i*numprocs];


        //����Ԫ�������������߳�
        for(j=1;j<numprocs;j++)
        MPI_Bsend(sample2,4*(numprocs-1),MPI_BYTE,
                  j,10+j,MPI_COMM_WORLD);

    }

    //����0���߳�������߳̽�����Ԫ
    if(myid!=0)
    {
        MPI_Status status;
        MPI_Recv(sample2,4*(numprocs-1),MPI_BYTE,
                  0,10+myid,MPI_COMM_WORLD,&status);
    }


    //��Ԫ�Ѵ��ݸ������߳�



    int partitionSizes[9]={0};
    //ÿ���̻߳�������ӵ�е�Ԫ��
    int newpartitionSizes[9];
    //ȫ�ֽ�����ÿ���߳���ӵ�е�Ԫ��
    int index=0;
    //������Ԫ�Ը����߳̽��л���
    for(i=(n/numprocs)*myid;i<(n/numprocs)*(myid+1);i++)
    {
        if(a[i]>sample2[index])
        {
            //�����ǰλ�õ����ִ�С������Ԫλ�ã��������һ������
            index++;
        }
        if(index==numprocs)
        {
            //���һ�λ��֣��������ܳ�������ǰλ�ü��ɵõ����һ�������黮�ֵĴ�С
            partitionSizes[numprocs-1]=(n/numprocs)*(myid+1)-i+1;
            break;
        }
        partitionSizes[index]++;   //���ִ�С����
    }
    //partitonSizes����ȷ����


    // ȫ�ֵ�ȫ�ֵķ���
    MPI_Alltoall(partitionSizes,4,MPI_BYTE,
        newpartitionSizes,4,MPI_BYTE,MPI_COMM_WORLD);
    int totalSize=0;
    // ���㻮�ֵ��ܴ�С�������»��ַ���ռ�
    for(i=0;i<numprocs;i++) {
        totalSize+=newpartitionSizes[i];
    }
    int *newpartitions = (int *) malloc(totalSize * sizeof(int));
    int *sendDisp=(int*)malloc(numprocs*4);
    int *recvDisp=(int*)malloc(numprocs*4);

    // �ڷ��ͻ���֮ǰ���������sendbuf��λ�ƣ���λ�ƴ��������������̵�����
    sendDisp[0]=0;
    recvDisp[0]=0;//���������recvbuf��λ�ƣ���λ�ƴ�����Ŵӽ��̽��ܵ�������
    for(i=1;i<numprocs;i++){
    sendDisp[i]=partitionSizes[i-1]+sendDisp[i-1];
    recvDisp[i]=newpartitionSizes[i-1]+recvDisp[i-1];
    }


    MPI_Alltoall(partitionSizes, 1, MPI_INT, newpartitionSizes,
               1, MPI_INT, MPI_COMM_WORLD);

    //�������ݣ�ʵ��n�ε�Ե�ͨ��
    MPI_Alltoallv(a+(n/numprocs)*myid, partitionSizes, sendDisp,
                MPI_INT, newpartitions,
                newpartitionSizes, recvDisp, MPI_INT, MPI_COMM_WORLD);




    qsort(newpartitions,totalSize,sizeof(int),cmp);
    //�����Ѿ��ֲ������Ұ��̺߳�����,�������


    //���ֲ����������ܵ�0���߳���
    /*----------------------------MPI_Gather���-----------------------------*/
    //���ܣ�
    //  Each process (root process included) sends the contents of its send
    //  buffer to the root process. The root process receives the messages and
    //  stores them in rank order.
    //  ÿ������(����������)���Լ�send���ݻ����е����ݷ��͸������̣������̽���
    //  ���з��������������̱�ʶ����
    //����������
    //  MPI_Gather(���ݷ��ͻ����ַ�����ݸ������������ͣ����ݽ��ջ����ַ��
    //  ���ݸ������������ͣ������̱�ʶ��ͨ����

    int *subListSizes = (int *) malloc(numprocs * sizeof(int));
    // ���͸����б�Ĵ�С�ظ�������
    MPI_Gather(&totalSize, 1, MPI_INT,
            subListSizes, 1, MPI_INT, 0, MPI_COMM_WORLD);
    // ����������ϵ������recvbuf��ƫ����
    if(myid ==0){
        recvDisp[0] = 0;
        for ( i = 1; i < numprocs; i++) {
        recvDisp[i] = subListSizes[i - 1] + recvDisp[i - 1];
        }
    }
    //���͸��ź�������б�ظ�������
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

