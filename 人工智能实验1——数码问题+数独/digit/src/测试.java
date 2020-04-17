import java.util.*;
import java.io.*;

public class solve{
	public static void main(String args[])
	{
		int i,j,k;
		System.out.println("������������ݣ�����ֻ�ÿո��������,��Ҫ�򶺺�!");
		int []input=new int [va.n*va.n];//��������
		Scanner sc=new Scanner(System.in);
		for(i=0;i<va.n;i++)
			for(j=0;j<va.n;j++)
				input[i*va.n+j]=sc.nextInt();
		String s="";
		for(i=0;i<va.n;i++)
			for(j=0;j<va.n;j++)
				s=s+(char)(input[i*va.n+j]+'a');
		va.map.put(s,1);
        va.init_d=compute_distant(input);
        System.out.println("��ʼ״̬�������پ���:");
        System.out.println(va.init_d);
        va.result=0;
        try_to_solve(s);//�����������Ⳣ�Եĺ���
        if(va.result==0)
            System.out.println("�������ʧ��,���Գ�������ѭ�������Խ������");
	}


    private static void try_to_solve(String s)
    {
        Queue<State> q = new PriorityQueue<>(
            new Comparator<State>() {
                @Override
            public int compare(State e1,State e2) {
                return (e1.distant+e1.step-e2.distant-e2.step);
                }
            }
        );//�������ȶ��е����ݽṹ
    
        int i,j,k;
        State head2=new State();
        head2.array=s;head2.distant=va.init_d;
        head2.action="";head2.step=0;
        q.offer(head2);
        String act="";
        
        
        int []t=new int [va.n*va.n];
        int init_d=va.init_d;
        for(k=0;k<100000 && !q.isEmpty();k++)//����ѭ�������ٴ�
        {
            State head=q.poll();
            String temp=head.array;
            va.init_d=init_d-head.step/4;
            String temp2="";
            if(head.distant==0)
                {   
                va.result=1;   
                System.out.println("success!!!");    
                //System.out.println("���ڶ��г���:"+q.size());
                System.out.println("ѭ������k:"+k);
                System.out.println("Ҫ��ȡ���ж�:"+head.action);
                System.out.println("����Ҫ�Ĳ���:"+head.step);
                return;  
                }
            int flag=0;
            va.pos_zero1=0;//��һ�������ڵ�λ��
            int pos_x1,pos_y1;
           va.pos_zero2=0;//�ڶ��������ڵ�λ��
            int pos_x2,pos_y2;
            for(i=0;i<va.n*va.n;i++)
                {if(temp.charAt(i)=='a'&&flag==0)
                    {va.pos_zero1=i;flag=1;}
                else if(temp.charAt(i)=='a'&&flag==1)
                    {va.pos_zero2=i;flag=2;break;}
                }
            
            pos_x1=va.pos_zero1/va.n;pos_y1=va.pos_zero1%va.n;
            pos_x2=va.pos_zero2/va.n;pos_y2=va.pos_zero2%va.n;
                if(pos_x1>0)
                {
                    temp2=exchange(temp,va.pos_zero1,va.pos_zero1-va.n);
                    if(va.map.get(temp2)==null)
                        {
                            State now=new State();
                            for(j=0;j<va.n*va.n;j++)
                                t[j]=temp2.charAt(j)-'a';
                            act=head.action;
                            act=act+t[va.pos_zero1]+"down ";
                            now.array=temp2;
                            now.distant=compute_distant(t);
                            now.action=act;
                            now.step=head.step+1;
                            if(now.distant<=va.init_d)
                                {
                                    q.add(now);
                                    va.map.put(temp2,1);
                                }
                        }
			    }

                if(pos_x1<va.n-1)
                {
                    temp2=exchange(temp,va.pos_zero1,va.pos_zero1+va.n);
                    //System.out.println(temp);
                    if(va.map.get(temp2)==null)
                        {
                            State now=new State();
                            for(j=0;j<va.n*va.n;j++)
                                t[j]=temp2.charAt(j)-'a';
                            act=head.action;
                            act=act+t[va.pos_zero1]+"up ";
                            now.array=temp2;
                            now.distant=compute_distant(t);
                            now.action=act;
                            now.step=head.step+1;
                            if(now.distant<=va.init_d)
                                {
                                    q.add(now);
                                    va.map.put(temp2,1);
                                }
                        }
			    }

                if(pos_y1>0)
                {
                    temp2=exchange(temp,va.pos_zero1,va.pos_zero1-1);
                    //System.out.println(temp);
                    if(va.map.get(temp2)==null)
                        {
                            State now=new State();
                            for(j=0;j<va.n*va.n;j++)
                                t[j]=temp2.charAt(j)-'a';
                            act=head.action;
                            act=act+t[va.pos_zero1]+"right ";
                            now.array=temp2;
                            now.distant=compute_distant(t);
                            now.action=act;
                            now.step=head.step+1;
                            if(now.distant<=va.init_d)
                                {
                                    q.add(now);
                                    va.map.put(temp2,1);
                                }
                        }
			    }

                if(pos_y1<va.n-1)
                {
                    temp2=exchange(temp,va.pos_zero1,va.pos_zero1+1);
                    //System.out.println(temp);
                    if(va.map.get(temp2)==null)
                        {
                            State now=new State();
                            for(j=0;j<va.n*va.n;j++)
                                t[j]=temp2.charAt(j)-'a';
                            act=head.action;
                            act=act+t[va.pos_zero1]+"left ";
                            now.array=temp2;
                            now.distant=compute_distant(t);
                            now.action=act;
                            now.step=head.step+1;
                            if(now.distant<=va.init_d)
                                {
                                    q.add(now);
                                    va.map.put(temp2,1);
                                }
                        }
			    }




                if(pos_x2>0)
                {
                    temp2=exchange(temp,va.pos_zero2,va.pos_zero2-va.n);
                    //System.out.println(temp);
                    if(va.map.get(temp2)==null)
                        {
                            State now=new State();
                            for(j=0;j<va.n*va.n;j++)
                                t[j]=temp2.charAt(j)-'a';
                            act=head.action;
                            act=act+t[va.pos_zero2]+"down ";
                            now.array=temp2;
                            now.distant=compute_distant(t);
                            now.action=act;
                            now.step=head.step+1;
                            if(now.distant<=va.init_d)
                                {
                                    q.add(now);
                                    va.map.put(temp2,1);
                                }
                        }
			    }

                if(pos_x2<va.n-1)
                {
                    temp2=exchange(temp,va.pos_zero2,va.pos_zero2+va.n);
                    //System.out.println(temp);
                    if(va.map.get(temp2)==null)
                        {
                            State now=new State();
                            for(j=0;j<va.n*va.n;j++)
                                t[j]=temp2.charAt(j)-'a';
                            act=head.action;
                            act=act+t[va.pos_zero2]+"up ";
                            now.array=temp2;
                            now.distant=compute_distant(t);
                            now.action=act;
                            now.step=head.step+1;
                            if(now.distant<=va.init_d)
                                {
                                    q.add(now);
                                    va.map.put(temp2,1);
                                }
                        }
			    }

                if(pos_y2>0)
                {
                    temp2=exchange(temp,va.pos_zero2,va.pos_zero2-1);
                    //System.out.println(temp);
                    if(va.map.get(temp2)==null)
                        {
                            State now=new State();
                            for(j=0;j<va.n*va.n;j++)
                                t[j]=temp2.charAt(j)-'a';
                            act=head.action;
                            act=act+t[va.pos_zero2]+"right ";
                            now.array=temp2;
                            now.distant=compute_distant(t);
                            now.action=act;
                            now.step=head.step+1;
                            if(now.distant<=va.init_d)
                                {
                                    q.add(now);
                                    va.map.put(temp2,1);
                                }
                        }
			    }

                if(pos_y2<va.n-1)
                {
                    temp2=exchange(temp,va.pos_zero2,va.pos_zero2+1);
                    //System.out.println(temp);
                    if(va.map.get(temp2)==null)
                        {
                            State now=new State();
                            for(j=0;j<va.n*va.n;j++)
                                t[j]=temp2.charAt(j)-'a';
                            act=head.action;
                            act=act+t[va.pos_zero2]+"left ";
                            now.array=temp2;
                            now.distant=compute_distant(t);
                            now.action=act;
                            now.step=head.step+1;
                            if(now.distant<=va.init_d)
                                {
                                    q.add(now);
                                    va.map.put(temp2,1);
                                }
                        }
			    }
            
		}
        
       if(q.peek()!=null)
       {
            State s2=q.poll();
            System.out.printf("���в�Ϊ����ʧ�ܣ����һ���������پ���:%d ִ�в���:%d\n",s2.distant,s2.step);
	   }
        //System.out.println("���ڶ��г���"+q.size());
        System.out.println("ѭ������k="+k);
    }

private static String exchange(String s,int index1,int index2)//����λ��
{
        char temp1,temp2;
        char []res=s.toCharArray();
        temp1=res[index1];
        temp2=res[index2];
        if(temp2!='h')//���������λ���в���7
        {
            res[index1]=temp2;res[index2]=temp1;
            String news="";
            for(int i=0;i<va.n*va.n;i++)
                news=news+res[i];
            return news;
        }
        else//������λ����7
        {
            int x1,y1,x2,y2;//index1,index2��x,y����
            x1=index1/5;y1=index1%5;
            x2=index2/5;y2=index2%5;
                if(x2+1<5&&y2-1>=0&&res[index2-1]=='h'&&res[index2+5]=='h')//7������
                {
                    if(index1-index2==1&&index1+5<25&&res[index1+5]=='a')//7���� 
                    {
                       res[index2-1]='a';res[index1]='h';
                       res[index2+5]='a';res[index1+5]='h';
                    }
                    else if(index1-index2==5&&x1>0&&res[index1-1]=='a')//7����
                    {
                        res[index1]='h';res[index2+5]='a';
                        res[index1-1]='h';res[index2-1]='a';
                    }
				}
                else if(y2-1>=0&&x2-1>=0&&res[index2-5]=='h'&&res[index2-6]=='h')//7������
                {
                    if(index1-index2==1&&res[index1-5]=='a')//����
                    {
                        res[index1-5]='h';res[index2-6]='a';
                        res[index1]='h';res[index2]='a';
					}
                    else if(index1-index2==5&&res[index1-6]=='a')//����
                    {
                        res[index1]='h';res[index2-5]='a';
                        res[index1-6]='h';res[index2-6]='a';
					}
                    else if(index1-index2==-1&&x1-1>=0&&y1-1>=0&&res[index1-6]=='a')//����
                    {
                        res[index1]='h';res[index2]='a';
                        res[index1-6]='h';res[index2-6]='a';
					}
				}
                else if(x2+1<5&&y2+1<5&&res[index2+1]=='h'&&res[index2+6]=='h')//7������
                {
                    if(index1-index2==-1&&res[index1+6]=='a')//����
                    {
                        res[index1]='h';res[index2+1]='a';
                        res[index1+6]='h';res[index2+6]='a';
					}
                    else if(y1+1<5&&res[index1+1]=='a')//����
                    {
                        res[index1]='h';res[index2]='a';
                        res[index1+1]='h';res[index2+6]='a';
					}
                    else if(x1+1<5&&res[index1+6]=='a')
                    {
                        res[index1]='h';res[index2]='a';
                        res[index1+6]='h';res[index2+6]='a';
					}
				}
            String news="";
            for(int i=0;i<va.n*va.n;i++)
                news=news+res[i];
            return news;
		}
}
    
private static int compute_distant(int b[])//���������پ���
{
    int x,y;
    int i,j;
    int distant=0;
    int flag=0;
    int []temp={1,2,3,4,5, 7,7,8,9,10, 6,7,11,12,13, 14,15,16,17,18,
    19,20,21,0,0};
    //����Ŀ��״̬
    for(x=0;x<va.n;x++)
        for(y=0;y<va.n;y++)
            {
            for(i=0;i<va.n;i++)
                {
                flag=0;
                    for(j=0;j<va.n;j++)
                    {
                        if(b[x*va.n+y]==temp[i*va.n+j])
                            {
                            distant+=Math.abs(x-i)+Math.abs(y-j);
                            temp[i*va.n+j]=-1;
                            flag=1;
                            break;
                            }
                    }
                    if(flag==1)
                        break;
                }
            }
    return distant;
    }
}


//һ����������ȫ�ֱ�������
public class va{
	public static Map<String,Integer> map = new HashMap<>();
	//��ϣ��Ķ���
	//String����ĳ������״̬��������key��Ϊ1��ʾ���״̬�Ѿ��ù���
    public static int n=5;//���������ռ䵽���ж��
    public static int init_d;//��ʼ״̬�������پ���
    public static int result;//��������Ŀ�����û�н������ӡʧ����Ϣ
    public static int pos_zero1;//��һ�������ڵ�λ��
    public static int pos_zero2;//�ڶ��������ڵ�λ��
}

//״̬�࣬������¼ĳ��״̬
public class State{
//���б������������static����������������

    public String array;    //���鵱ǰ״̬
    public int    distant;  //��ǰ�������پ���
    public String action;   //��ǰ�ù�����Щ����
    public int    step;     //��ʼ״̬����ǰ״̬�ж��ٲ�
}