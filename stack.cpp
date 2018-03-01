#include <stdio.h> 
#define maxsize 5
#define true 1
#define false 0
#define ERROR -1
typedef int eletype;
typedef struct slist
{	eletype data[maxsize];
	int top;
	
}slist;
int init_slist(slist &L)
{
	L.top = -1;
	return 1;
}
int is_empty(slist &L)
{
	if(L.top ==-1)return true;
	else return false;
}
int push_stack(slist &L,eletype x)
{
	if(L.top ==maxsize-1)return ERROR;
	else 
	L.data[++L.top] = x;
	return 1;
}
int pop_stack(slist &L)
{	eletype x;
	if(L.top ==-1)return ERROR;
	else
	{
		x = L.data[L.top--];
	}
	return x;
}

//利用栈来表示队列（利用两个栈模拟一个队列）
void enqueue(slist &L1,slist &L2,eletype x)//栈顶加入元素x
{
	if(L1.top==maxsize-1)//如果L1满
	{
		if(L2.top!=-1) return ERROR;//如果L2非空，那么无法入栈
		else
		{	while(L1.top!=-1)//将L1中的元素全部出栈，压到L2中
			L2.data[++L2.top] = L1.data[L1.top--];
			L1.data[++L1.top] = x;//将元素X入栈到L1

		}
	}
	else//如果L1非满，则直接入栈到L1
	{
		L1.data[++L1.top] =x;
	}
}

void dequeue(slist &L1,slist &L2,eletype x)//实现出栈
{
	if(L2.top!=-1) x = L.data[L2.top--];//如果L2非空，那么直接从L2出栈
	else//如果L2为空，判别两种情况
	{
		if(L1.top==-1) return false;//如果L1也为空
		else//如果L1不为空
		{	while(L1.top!=-1)//遍历，将L1中的元素出栈，压栈到L2中，并且从L2中出栈
			L2.data[++L2.top] = L1.data[L1.top--];
			x = L2.data[L2.top--];//输出出栈元素x
		}
	}
}
void is_queue_empty(slist &L1,slist &L2)//判别该模拟队列是否是空
{
	if(L1.top==-1&&L2.top==-1) return 1;
	else return 0;
}
typedef struct qlist
	{ 	int data[];
		int top;
	}qlist;

int op(int a,char op,int b)//该函数是运算函数，运算字符表达式
{
	if(op=='-') return a-b;
	if(op=='+') return a+b;
	if(op=='*') return a*b;
	if(op=='/')
	{
		if(b==0) printf("算式没意义，分母为0");
		else return a/b
	}
}
int  com(char exp[])//后缀表达式的转换以及计算
{	qlist L[maxsize];//建立一个顺序栈（注意栈应该是int形式，即便这里说明了L.data是个位的，但是不能保证在以后的计算中不会出现两位数）
	int a,b,m;
	for(int i=0;exp[i]!='\0';i++)//遍历，遍历条件为字符不等于结束字符‘\0’
	{	if(exp[i]>'0'&&exp[i]<'9')//当字符是操作符时将该操作符转化为int然后入栈
			L.data[++L.top]=exp[i]-'0';//该步骤是整形变量与字符型变量之间的转换，该小技巧参见书p63页
		else//当为运算符时，依次取两个栈顶元素进行该运算符运算
		{	b = L.data[L.top--];
			a = L.data[L.top--];
			m = op(a,exp[i],b);//利用上一个函数进行计算
			L.data[++L.top] = m;//将计算后的数值入栈，然后继续遍历。
		}
	}
	x =L.data[L.top];//遍历完后将栈顶元素（实际栈中也只有一个元素）出栈
	return x；

}
int main()
{	slist L;
	init_slist(L);
	push_stack(L,30);
	push_stack(L,40);
	int w;
	w = pop_stack(L);
	printf("%d/n",w);
return 0;}