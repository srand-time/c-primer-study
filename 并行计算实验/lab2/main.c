#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
int a[10001][2];
//������ά�ֱ���v,d
//���ģ��10000����

int step=10000;//ģ��������
int n=10000;//������Ŀ
int v_max=10;
//�����,�����������ʱprint�����е�v����ҲҪ����
double p=0.1;   //���ٸ���,֧����λС��

int main(int argc,char *argv[]){
	int i,j;
	int max;
	int myid, numprocs;
	double start =0.0,stop = 0.0;
    a[0][1]=v_max;
    srand(time(NULL));
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    int* mpi_buffer=malloc(sizeof(int)*100000);
	MPI_Buffer_attach(mpi_buffer,sizeof(int)*100000);
	if(myid == 0)
    {
		//MPI_Wtime����һ���ø�������ʾ������,��ʱ
		start = MPI_Wtime();
	}
	for(i=0;i<step;i++)
        {
            //����ÿ���������ٶ�
            for(j=(n/numprocs)*myid;j<(n/numprocs)*(myid+1);j++)
            {
                if(a[j][1]>a[j][0])
                    a[j][0]++;
                if(a[j][0]>v_max)
                    a[j][0]=v_max;
                double r=rand()%100/100.0;
                //r��0��0.99
                if(r<p)
                    a[j][0]--;
                if(a[j][0]<0)
                    a[j][0]=0;
            }
            MPI_Barrier(MPI_COMM_WORLD);

            /*
            for(j=0;j<numprocs;j++)
            {
            if(j!=myid)
            MPI_Bsend((a+(n/numprocs)*myid),8*n/numprocs,MPI_BYTE,j,i*10+myid,MPI_COMM_WORLD);
            //�����������̷߳��ͱ��߳���ӵ�е�����
            }
            for(j=0;j<numprocs;j++)
            {
                if(j!=myid)
                {
				MPI_Status status;
				MPI_Recv((a+(n/numprocs)*j),8*n/numprocs,MPI_BYTE,j,i*10+j,MPI_COMM_WORLD,&status);
                //�����������߳̽��������߳�ӵ�е�����
                }
            }
            */

            if(myid!=numprocs-1)
                MPI_Bsend((a+((n/numprocs)*(myid+1)-1)),8,MPI_BYTE,myid+1,i*10+myid,MPI_COMM_WORLD);
                //�����������̷߳��ͱ��߳���ӵ�е�����

            if(myid!=0)
            {
                MPI_Status status;
                MPI_Recv((a+((n/numprocs)*(myid)-1)),8,MPI_BYTE,myid-1,i*10+myid-1,MPI_COMM_WORLD,&status);
                //�����������߳̽��������߳�ӵ�е�����
            }

            //����ÿ��������֮ǰ���ٶȸ��¾���
            for(j=0;j<n-1;j++)
            {
                a[j+1][1]=a[j+1][1]+a[j][0]-a[j+1][0];
            }
        }



            if(myid!=0)
            MPI_Bsend((a+(n/numprocs)*myid),8*n/numprocs,MPI_BYTE,0,i*10+myid,MPI_COMM_WORLD);
            //��0���̷߳��ͱ��߳���ӵ�е�����

    if(myid == 0)
    {
        for(j=0;j<numprocs;j++)
            {
                if(j!=myid)
                {
				MPI_Status status;
				MPI_Recv((a+(n/numprocs)*j),8*n/numprocs,MPI_BYTE,j,i*10+j,MPI_COMM_WORLD,&status);
                //0���̴߳����������߳̽��������߳�ӵ�е�����
                }
            }
        printf("ѭ������: %d\n",step);
		stop = MPI_Wtime();
		printf("Time:%.4f ms\n",(stop-start)*1000);
		print();
	}
    MPI_Finalize();
	return 0;
}
void print(){
    int i,j;
    int v[11];
    for(i=0;i<11;i++)
        v[i]=0;
    for(i=0;i<n;i++){
        for(j=0;j<=v_max;j++)
        if(a[i][0]==j)
            v[j]++;
    }
    for(i=0;i<=10;i++){
        printf("v:%d count:%d\n",i,v[i]);
    }
}
