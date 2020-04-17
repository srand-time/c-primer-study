import java.util.*;
import java.io.*;

public class solve{
	public static void main(String args[])
	{
		int i,j,k;
		System.out.println("请输入测试数据，仅仅只用空格隔开数字,不要打逗号!");
		int []input=new int [va.n*va.n];//输入数组
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
        System.out.println("初始状态的曼哈顿距离:");
        System.out.println(va.init_d);
        va.result=0;
        try_to_solve(s);//对问题进行求解尝试的函数
        if(va.result==0)
            System.out.println("问题求解失败,可以尝试增加循环次数以解决问题");
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
        );//定义优先队列的数据结构
    
        int i,j,k;
        State head2=new State();
        head2.array=s;head2.distant=va.init_d;
        head2.action="";head2.step=0;
        q.offer(head2);
        String act="";
        
        
        int []t=new int [va.n*va.n];
        int init_d=va.init_d;
        for(k=0;k<100000 && !q.isEmpty();k++)//到底循环求解多少次
        {
            State head=q.poll();
            String temp=head.array;
            va.init_d=init_d-head.step/4;
            String temp2="";
            if(head.distant==0)
                {   
                va.result=1;   
                System.out.println("success!!!");    
                //System.out.println("现在队列长度:"+q.size());
                System.out.println("循环次数k:"+k);
                System.out.println("要采取的行动:"+head.action);
                System.out.println("所需要的步数:"+head.step);
                return;  
                }
            int flag=0;
            va.pos_zero1=0;//第一个零所在的位置
            int pos_x1,pos_y1;
           va.pos_zero2=0;//第二个零所在的位置
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
            System.out.printf("队列不为空且失败，最后一步的曼哈顿距离:%d 执行步数:%d\n",s2.distant,s2.step);
	   }
        //System.out.println("现在队列长度"+q.size());
        System.out.println("循环次数k="+k);
    }

private static String exchange(String s,int index1,int index2)//交换位置
{
        char temp1,temp2;
        char []res=s.toCharArray();
        temp1=res[index1];
        temp2=res[index2];
        if(temp2!='h')//如果交换的位置中不是7
        {
            res[index1]=temp2;res[index2]=temp1;
            String news="";
            for(int i=0;i<va.n*va.n;i++)
                news=news+res[i];
            return news;
        }
        else//交换的位置是7
        {
            int x1,y1,x2,y2;//index1,index2的x,y坐标
            x1=index1/5;y1=index1%5;
            x2=index2/5;y2=index2%5;
                if(x2+1<5&&y2-1>=0&&res[index2-1]=='h'&&res[index2+5]=='h')//7在右上
                {
                    if(index1-index2==1&&index1+5<25&&res[index1+5]=='a')//7右移 
                    {
                       res[index2-1]='a';res[index1]='h';
                       res[index2+5]='a';res[index1+5]='h';
                    }
                    else if(index1-index2==5&&x1>0&&res[index1-1]=='a')//7上移
                    {
                        res[index1]='h';res[index2+5]='a';
                        res[index1-1]='h';res[index2-1]='a';
                    }
				}
                else if(y2-1>=0&&x2-1>=0&&res[index2-5]=='h'&&res[index2-6]=='h')//7在右下
                {
                    if(index1-index2==1&&res[index1-5]=='a')//右移
                    {
                        res[index1-5]='h';res[index2-6]='a';
                        res[index1]='h';res[index2]='a';
					}
                    else if(index1-index2==5&&res[index1-6]=='a')//下移
                    {
                        res[index1]='h';res[index2-5]='a';
                        res[index1-6]='h';res[index2-6]='a';
					}
                    else if(index1-index2==-1&&x1-1>=0&&y1-1>=0&&res[index1-6]=='a')//左移
                    {
                        res[index1]='h';res[index2]='a';
                        res[index1-6]='h';res[index2-6]='a';
					}
				}
                else if(x2+1<5&&y2+1<5&&res[index2+1]=='h'&&res[index2+6]=='h')//7在左上
                {
                    if(index1-index2==-1&&res[index1+6]=='a')//左移
                    {
                        res[index1]='h';res[index2+1]='a';
                        res[index1+6]='h';res[index2+6]='a';
					}
                    else if(y1+1<5&&res[index1+1]=='a')//上移
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
    
private static int compute_distant(int b[])//计算曼哈顿距离
{
    int x,y;
    int i,j;
    int distant=0;
    int flag=0;
    int []temp={1,2,3,4,5, 7,7,8,9,10, 6,7,11,12,13, 14,15,16,17,18,
    19,20,21,0,0};
    //定义目标状态
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


//一个用来定义全局变量的类
public class va{
	public static Map<String,Integer> map = new HashMap<>();
	//哈希表的定义
	//String代表某个数组状态，而将其key置为1表示这个状态已经用过了
    public static int n=5;//定义整个空间到底有多大
    public static int init_d;//初始状态的曼哈顿距离
    public static int result;//定义结果数目，如果没有结果，打印失败信息
    public static int pos_zero1;//第一个零所在的位置
    public static int pos_zero2;//第二个零所在的位置
}

//状态类，用来记录某个状态
public class State{
//类中变量的声明别加static啊笨蛋！！！！！

    public String array;    //数组当前状态
    public int    distant;  //当前的曼哈顿距离
    public String action;   //当前用过了哪些动作
    public int    step;     //初始状态到当前状态有多少步
}