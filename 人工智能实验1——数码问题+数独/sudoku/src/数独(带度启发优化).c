#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<time.h>
int result=0; //�����
char cc;//�Ƿ���Ҫ������н⣬��Ȼ���������н�Ļ�������ô�Ż�
//����Ҫ��������״̬�����Բ�������н⣬������һ���⡣
int save[9][9];
int yueshu[9][9];//��ǰλ�ñ����ٸ�������Լ��
int count=81;//���ж��ٸ���λ
int cishu=0;
clock_t start,end;
int main()
{
    int i,j,k;

    int check(int a[9][9],int i,int j,int k);
    //����i,j���λ���ܲ��ܰڷ�k�������

    void update_yueshu(int a[9][9],int x,int y,int flag);
    //��x,yλ������������ȥ��x,yλ�õ���֮��
    //����Լ������
    //flag=1ʱ������
    //flag=-1ʱ��ȥ����

    void shudu(int a[9][9],int n,FILE *f);
    //������⺯��,n����λ��0<=n<81��
    //��Ҫ��������ѧ֪ʶ�ĺ���



    int get_max_yueshu();
    //�õ���ǰԼ�����������Ԫ�ص����꣬���ص���������ʽ��

    int getAllTestcase(char filename[][256]);
    //�õ����еĲ����������ļ���������ֵΪ�ļ�������

    char filename[50][256];
    int filenum=getAllTestcase(filename);
    printf("%d\n",filenum);
    printf("input file name\n");
    for(i=0;i<filenum;i++)
        printf("%s\n",filename[i]);

        printf("��ȡ�����ļ������������\n");
            for(k=0;k<filenum;k++)
            {
                cishu=0;
                count=81;
                memset(save,0,sizeof(save));
                memset(yueshu,0,sizeof(yueshu));
                result=0;
                FILE *f1;//�ļ�ָ��
                char i_f_name[256]="../input/";//�����ļ���
                char o_f_name[256]="../output/optimization_";//����ļ�
                strcat(i_f_name,filename[k]);
                f1=fopen(i_f_name,"r");
                printf("%s",i_f_name);
                printf("�����е�ԭʼ���ݣ�û�����ݵ���0���档\n");
                for(i=0;i<9;i++)
                    {
                        for(j=0;j<9;j++)
                            fscanf(f1,"%d",&save[i][j]);
                        fscanf(f1,"\n");
                    }
                fclose(f1);//���ļ��ж�ȡ���ݲ�������

                strcat(o_f_name,filename[k]);
                f1=fopen(o_f_name,"w");
                for(i=0;i<9;i++)
                    {for(j=0;j<9;j++)
                        {
                            printf("%d ",save[i][j]);
                            if(save[i][j]!=0)
                            {
                            count--;//��Ҫ�������һ
                            update_yueshu(save,i,j,1);
                            }
                        }
                    printf("\n");
                    }
                printf("Լ������----->>>>>>>>>\n");
                for(i=0;i<9;i++)
                    {for(j=0;j<9;j++)
                        printf("%5d ",yueshu[i][j]);
                    printf("\n");
                    }
                printf("ʣ���λ��%d\n",count);
                printf("�����Ľ�Ϊ��\n\n");
                cc='n';
                shudu(save,get_max_yueshu(),f1);
                printf("Լ������----->>>>>>>>>\n");
                    for(i=0;i<9;i++)
                    {for(j=0;j<9;j++)
                        printf("%5d ",yueshu[i][j]);
                    printf("\n");
                    }
                if(result==0)
                    {
                        printf("�������޽�!");
                        fprintf(f1,"�������޽�!\n");
                    }
                fclose(f1);
                result=0;
                printf("\n\n\n");
            }
    end=clock();
    printf("\n ��������ʱ��%d ms",end-start);
    return 0;
}



    //������еĽ�
void print(int a[9][9],FILE *f)
{
    int i,j;
    result++;
        printf("��������:%d \n",cishu);
        fprintf(f,"��������:%d \n",cishu);
        cishu=0;
        printf("��%d���Ϊ��\n",result);
        fprintf(f,"��%d���Ϊ��\n",result);
        for(i=0;i<9;i++)
        {
        for(j=0;j<9;j++)
            {
                    printf("%d ",a[i][j]);
                    fprintf(f,"%d ",a[i][j]);
                if((j==2)||(j==5))
                    {
                        //printf(" ");
                        fprintf(f," ");
                    }
            }
        printf("\n");
        fprintf(f,"\n");
        if((i==2)||(i==5))
            {
                //printf("\n");
                fprintf(f,"\n");
            }
        }
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
        save[i][j]=a[i][j];
    printf("\n\n\n");
    fprintf(f,"\n\n\n");
}




//�ж��Ƿ���Խ���i�С���j�е�����Ϊk
int check(int a[9][9],int i,int j,int k)
{
    int m,n;
    //�ж���
    for(n=0;n<9;n++)
    {
    if(a[i][n] == k)
    return 0;
    }

    //�ж���
    for(m=0;m<9;m++)
    {
    if(a[m][j] == k)
    return 0;
    }

    //�ж�����С�Ź���
    int t1=(i/3)*3,t2=(j/3)*3;
    for(m=t1;m<t1+3;m++)
    {
    for(n=t2;n<t2+3;n++)
        {
        if(a[m][n] == k)
        return 0;
        }
    }

    //�ж϶Խ���
    if(i==j)
    for(m=0;m<9;m++)
    {
        if(a[m][m]==k)
            return 0;
    }
    if(i==8-j)
    for(m=0;m<9;m++)
    {
        if(a[m][8-m]==k)
            return 0;
    }
//���У�����true
return 1;
}


void shudu(int a[9][9],int n,FILE *f)
{
    cishu++;
    int temp[9][9];
    int i,j,k;
    if(count==0)
        print(a,f);
    else if(result<1)
    {
        //printf("\n\n count=%d a[%d][%d]=%d \n",count,n/9,n%9,a[n/9][n%9]);
        //printf("%d %d\n",get_max_yueshu()/9,get_max_yueshu()%9);
        for(i=0;i<9;i++)
        {
        for(j=0;j<9;j++)
            temp[i][j]=a[i][j];
        }

        for(k=1;k<=9;k++)
            {
            int flag=check(a,n/9,n%9,k);
            //printf("flag=%d i=%d j=%d k=%d \n",flag,n/9,n%9,k);
                if(flag) //��i�С���j�п�����k
                {
                a[n/9][n%9]=k; //��Ϊk

                count--;      //�ֶ�����һ����


                //����Լ������
                int x=n/9;int y=n%9;
                    yueshu[x][y]=-100000000;
                    for(i=0;i<9;i++)
                    {
                    if(i!=x)
                    yueshu[i][y]=yueshu[i][y]+flag;
                    }
                    for(i=0;i<9;i++)
                    {
                    if(i!=y)
                    yueshu[x][i]=yueshu[x][i]+flag;
                    }
                    if(x==y)
                    {
                    for(i=0;i<9;i++)
                        if(x!=i)
                        yueshu[i][i]=yueshu[i][i]+flag;
                    }
                if(x==8-y)
                {
                    for(i=0;i<9;i++)
                        if(x!=i)
                        yueshu[i][8-i]=yueshu[i][8-i]+flag;
                }


                if(count == 0)
                    print(a,f);
                else
                    {
                        int max=get_max_yueshu();
                        shudu(a,max,f);
                    }

                    a[x][y]=0; //�ָ�Ϊ0���ж���һ��k
                    count++;

                    yueshu[x][y]=0;
                for(i=0;i<9;i++)
                    if(temp[x][i]!=0)
                        yueshu[x][y]++;
                for(i=0;i<9;i++)
                    if(temp[i][y]!=0)
                        yueshu[x][y]++;
                if(x==y)
                    {
                    for(i=0;i<9;i++)
                        if(temp[i][i]!=0)
                            yueshu[x][y]++;
                    }
                if(x==8-y)
                    {
                    for(i=0;i<9;i++)
                        if(temp[i][8-i]!=0)
                            yueshu[x][y]++;
                    }
                }
            }
    }
}


/*
//������⺯��
void shudu(int a[9][9],int n,FILE *f)
{
    int temp[9][9];
    int i,j,k;
    if((cc=='y')||(result<1))
    //cc='y'����˼��������н�,
    //����cc!='y'����ҲҪ����һ����
    {
        for(i=0;i<9;i++)
        {
        for(j=0;j<9;j++)
        temp[i][j]=a[i][j];
        }
        i=n/9; j=n%9; //�����n����������������
        if(a[i][j] != 0) //�Ѿ���ԭʼ����
        {
            if(n == 80) //�����һ�����ӣ�������н�
                print(temp,f);
            else //�������һ�����ӣ�����һ������
                shudu(temp,n+1,f);
        }
        else //û������
        {
            for(k=1;k<=9;k++)
            {
            int flag=check(temp,i,j,k);
                if(flag) //��i�С���j�п�����k
                {
                temp[i][j]=k; //��Ϊk
                if(n == 80)
                    print(temp,f);
                else
                    shudu(temp,n+1,f);
                    temp[i][j]=0; //�ָ�Ϊ0���ж���һ��k
                }
            }
        }
    }
}
*/

int getAllTestcase(char filename[][256])
{
	DIR *dir;
	struct dirent *entry;
	int m=0;
	if (!(dir=opendir("../input"))){
		printf("[ERR] No input file\n");
		exit(1);
	}

	while(entry=readdir(dir)){
		char temp[5];
		//����д��temp[4],������û����ֹ���ˡ�
		int len=strlen(entry->d_name);
		int i;
        if(len<4)
            continue;
		for (i=0;i<4;i++)
		{
			temp[i]=entry->d_name[len-4+i];
		}
		if (!strcmp(temp,".txt")){
            //������strcmp����0������Ҫ��'!'��
			strcpy(filename[m],entry->d_name);
			m++;
		}
	}
	closedir(dir);
	return m;
}



void update_yueshu(int temp[9][9],int x,int y,int flag)
    //��x,yλ������������ȥ��x,yλ�õ���֮��
    //����Լ������
    //flag=1ʱ������
    //flag=-1ʱ��ȥ����
    {
        int i,j;
            if(flag==1)
            {
                yueshu[x][y]=-100000000;
                for(i=0;i<9;i++)
                {
                if(i!=x)
                yueshu[i][y]=yueshu[i][y]+flag;
                }
                for(i=0;i<9;i++)
                {
                if(i!=y)
                yueshu[x][i]=yueshu[x][i]+flag;
                }
                if(x==y)
                {
                    for(i=0;i<9;i++)
                        if(x!=i)
                        yueshu[i][i]=yueshu[i][i]+flag;
                }
            if(x==8-y)
                {
                    for(i=0;i<9;i++)
                        if(x!=i)
                        yueshu[i][8-i]=yueshu[i][8-i]+flag;
                }
            }
            //���ڶ�����ʱ����ȥ��Լ�����������
            //������ط��Ѿ�������
            //������Ϊ��С��һ����

            if(flag==-1)
            //ȥ�����λ�õ��������¼���Լ��������
            {
                yueshu[x][y]=0;
                for(i=0;i<9;i++)
                    if(temp[x][i]!=0)
                        yueshu[x][y]++;
                for(i=0;i<9;i++)
                    if(temp[i][y]!=0)
                        yueshu[x][y]++;
                if(x==y)
                {
                    for(i=0;i<9;i++)
                        if(temp[i][i]!=0)
                            yueshu[x][y]++;
                }
                if(x==8-y)
                {
                    for(i=0;i<9;i++)
                        if(temp[i][8-i]!=0)
                            yueshu[x][y]++;
                }
            }
    }

    int get_max_yueshu()
    {
        int i,j;
        int max=0;
        int res;
        for(i=0;i<9;i++)
            for(j=0;j<9;j++)
            {
                if(max<yueshu[i][j])
                {
                    max=yueshu[i][j];
                    res=i*9+j;
                }
            }
        return res;
    }
