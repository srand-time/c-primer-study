#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<time.h>
int result=0; //�����
char cc;//�Ƿ���Ҫ������н�
int cishu=0;
int save[9][9];
int yueshu[9][9];//��ǰλ�ñ����ٸ�������Լ��
clock_t start,end;
int main()
{
    start=clock();
    //int a[9][9];
    int i,j,k,way;
    int check(int a[9][9],int i,int j,int k);
    //����i,j���λ���ܲ��ܰڷ�k�������

    void shudu(int a[9][9],int n,FILE *f);
    //������⺯��,n����λ��0<=n<81��
    //��Ҫ��������ѧ֪ʶ�ĺ���

    int getAllTestcase(char filename[][256]);
    //�õ����еĲ����������ļ���������ֵΪ�ļ�������

    char filename[50][256];
    int filenum=getAllTestcase(filename);
    printf("%d\n",filenum);
    printf("input file name\n");
    for(i=0;i<filenum;i++)
        printf("%s\n",filename[i]);

        printf("��ȡ�����ļ������������\n");
        memset(save,0,sizeof(save));
            for(k=0;k<filenum;k++)
            {
                cishu=0;
                FILE *f1;//�ļ�ָ��
                char i_f_name[256]="../input/";//�����ļ���
                char o_f_name[256]="../output/";//����ļ�
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
                fclose(f1);
                strcat(o_f_name,filename[k]);
                f1=fopen(o_f_name,"w");
                for(i=0;i<9;i++)
                    {for(j=0;j<9;j++)
                        printf("%d ",save[i][j]);
                    printf("\n");
                    }
                printf("�����Ľ�Ϊ��\n\n");
                cc='y';
                shudu(save,0,f1);
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
    if(a[5][5]!=0)
    {
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
    }
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



//������⺯��
void shudu(int a[9][9],int n,FILE *f)
{
    cishu++;
    int temp[9][9];
    int i,j,k;
    if(result<1)
    //cc='y'����˼��������н�,����ҲҪ����һ����
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
