//�ɸ������֪ʶ��֪������������ʽ�������pi/4��
#include<stdio.h>
#include<mpi.h>
int main(int argc,char *argv[]){
	int my_rank,num_procs;
	int i;
	int n=1000;//ѭ������
	double sum,width,local,mypi,pi;
	double start =0.0,stop = 0.0;


	MPI_Init(&argc,&argv);
	//��ʼ��
	//���еĲ���ȫ������MPI_Init(&argc,&argv)��MPI_Finalize()�ڲ���

	MPI_Comm_size(MPI_COMM_WORLD,&num_procs);
		//MPI_COMM_WORLD�����н��̵ļ��ϣ���ִ����MPI_Init���Զ�����
	/*
	int MPI_Comm_size (MPI_Comm comm ,int* size )
    ��ý��̸��� size��
    ָ��һ��ͨ����,Ҳָ����һ�鹲��ÿռ�Ľ���, ��Щ������ɸ�ͨ���ӵ�group���飩��
    ���ͨ����comm�й涨��group�����Ľ��̵�������
    */

	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	//�õ���������ͨ�ſռ��е�rankֵ,�������е��߼����
	//(�� rankֵΪ0��p-1�������,�൱�ڽ��̵�ID��)

	printf("Process rank:%d ,total process :%d\n",my_rank,num_procs);
	if(my_rank == 0)
    {
		//MPI_Wtime����һ���ø�������ʾ������,��ʱ
		start = MPI_Wtime();
	}
	sum =0.0;
	width = 1.0/n;

	//ÿ������my_rank������4.0/(1.0+local*local)����sum
	for(i = my_rank;i<n;i+=num_procs)
    {
		local =width*((double)i+0.5);
		sum += 4.0/(1.0+local*local);
	}
	mypi = width*sum;
	MPI_Reduce(&mypi,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    //ȫ�ֹ�Լ����MPI_Reduce�� �����еķ�����Ϣ����ͬһ��������
    //int MPI_Reduce(
    //void *input_data, /*ָ������Ϣ���ڴ���ָ�� */
    //void *output_data, /*ָ����գ��������Ϣ���ڴ���ָ�� */
    //int count��/*������*/
    //MPI_Datatype datatype,/*��������*/
    //MPI_Op operator,/*��Լ����*/
    //int dest��/*Ҫ���գ��������Ϣ�Ľ��̵Ľ��̺�*/
    //MPI_Comm comm);/*ͨ������ָ��ͨ�ŷ�Χ*/

	//��ӡ���������ʱ��
	if(my_rank == 0)
    {
        printf("ѭ������: %d\n",n);
		printf("PI is %.20f\n",pi);
		stop = MPI_Wtime();
		printf("Time:%.4f ms\n",(stop-start)*1000);
	}
	MPI_Finalize();
	return 0;
}
