#include<stdio.h>
#include<stdlib.h>


#define LIST_INIT_SIZE 100
#define LIST_INCREASMENT 10
#define FALSE 0
#define TRUE 1
#define ERROR 0
#define OK 1
typedef int ElemType;	//定义的数据元素的类型,之所以设置为ElemType是考虑到可扩展行的原因,如果想把数据元素的类型修改成其他的话,只需要在这里修改一次据好了,比较方便
typedef int Status;
/*
**定义线性表的数据结构
*/
typedef struct{
	ElemType *base;		//base为线性表指向线性表起始地址的指针
	int length;			//length为当前线性表的长度
	int listSize;		//listSize为线性表的总长度
} SqList;

/*创建线性表
*/
void initList(SqList *L){
	L->listSize = LIST_INIT_SIZE;  //初始化线性表的总长度为我们事先定义好的LIST_INIT_SIZE,也就是100
	L->base = (ElemType *)malloc(L->listSize * sizeof(ElemType));  //为线性表申请内存空间,大小为线性表的总长度 乘以 每一个元素所占空间的大小
	L->length = 0;	//创建线性表的时候没有数据元素,长度默认为0	
}

/*
**判断顺序表是否为空
*/
int  listEmpty(SqList *L){
	return L->length =0;
}

/*
**得到线性表当前的长度
*/
int listLength(SqList *L){
	if(L->length >= 0 && L->length <= L->listSize){
		return L->length;
	} else{
		return -1;
	}
}

/*
**线性表的插入操作
*/
Status listInsert(SqList *L, int i, ElemType e){
	//我们这里传入的i是用户眼中的位置,意思就是从1开始,而不是从程序员熟悉的0开始
	int k;
	if(L->length == L->listSize){
		printf("线性表已满,不能插入");
		return ERROR;
	}
	if(i<1 || i>L->length + 1){
		printf("插入的位置不正确");
		return ERROR;
	}
	if(i <= L->length){  //若插入的位置不在表尾
		for(k=L->length - 1; k>i - 1; k--){
			L->base[k + 1] = L->base[k];
		}
	}
	L->base[i - 1] = e;
	L->length = L->length + 1;

	return OK;
}

/*
**删除一个表中的元素
*/
Status listDelete(SqList *L, int i, ElemType *e){
	int k;
	//这里的e是用来暂存被删除的元素的
	if(L->length == 0){	//如果表为空的话,则返回错误
		return ERROR;
	}
	if(i<1 || i>L->length){	//如果删除的位置不正确
		return ERROR;
	}
	*e = L->base[i - 1]; 
	if(i < L->length){
		for(k=i; k<L->length; k++){
			L->base[k - 1] = L->base[k];
		}
	}
	L->length = L->length - 1;
	
	return OK;
}
/*
**得到指定位置的元素的值
*/
ElemType getElem(SqList *L, int i){
	if(i<1 || i>L->length){		//先做检查
		return ERROR;
	}
	return L->base[i - 1];	//结果一返回值的形式得到
}
/*
**得到指定位置元素的前驱
*/
ElemType priorElem(SqList *L, int i){
	if(i<1 || i>L->length){		//先做检查
		return ERROR;
	}
	if(i != 1){
		return L->base[i-2];
	} else {
		printf("线性表的第一个元素没有前驱,操作错误!");
		return ERROR;
	}
}
/*
**得到指定位置元素的后继
*/
ElemType nextElem(SqList *L, int i){
	if(i<1 || i>L->length){		//先做检查
		return ERROR;
	}
	if(i != L->length){
		return L->base[i];
	} else {
		printf("线性表的最后一个元素没有后继,操作错误!");
		return ERROR;
	}
}

/*
**清空线性表
*/
int  clearList(SqList *L){
	if(L->length>0 && L->length<L->listSize){
		L->length = 0;
		return 1;
	} else{
		return 0;
	}
}

/*
**销毁线性表
*/
Status destroyList(SqList *L){
	clearList(L);	//先清空线性表
	L->listSize = 0;	//把线性表的总长度归零
	free(L->base);		//释放内存空间
	if(L->base == NULL && L->length == 0 && L->listSize == 0){	//最后再进行确认
		return TRUE;
	} else{
		return FALSE;
	}
}
/*
**遍历当前线性表,打印输出所有的元素
*/
void listTraverse(SqList *L)  
{  
    ElemType *p;  
    int i;  
    p = L->base;  
  
    for(i = 1; i <= L->length; i++)  
    {  
        printf("%d ", *(L->base + i - 1));  
    }  
  
    printf("\n\n");  
}  
/*
**定位一个指定的值在线性表里的具体位置
*/
int LocateElem(SqList *L, int e)  
{  
    ElemType *p;  
    int i = 1; // i的初值为第1个元素的位序  
    p = L->base; // p的初值为第1个元素的存储位置  
  
    while(i <= L->length && *(p++) != e){  
        ++i;  
    }  
  
    if(i <= L->length)  
    {  
        return i;  
    }  
    else  
    {  
        return 0;  
    }  
  
}  
int main()
{
	ElemType e;
	char ch = NULL;
	SqList L;
	initList(&L);	//创建一个表
	printf("创建线性表后\n线性表的当前长度:%d", L.length);
	printf("\n线性表的总长度:%d", L.listSize);
	if(listEmpty(&L)){	//判断表是否为空
		printf("\n此时线性表为空");
	} else {
		printf("\n此时线性表不为空");
	}
	//插入一个元素
	if(listInsert(&L, 1, 500)){
		printf("\n第一个元素的值:%d", getElem(&L, 1));
	}
	printf("\n线性表的当前长度:%d", L.length);

	if(listInsert(&L, 2, 1000)){
		printf("\n第二个元素的值:%d", getElem(&L, 2));
	}
	printf("\n线性表的当前长度:%d", L.length);

	if(listInsert(&L, 3, 2000)){
		printf("\n第三个元素的值:%d", getElem(&L, 3));
	}
	printf("\n线性表的当前长度:%d\n", L.length);

	listTraverse(&L);
	
	printf("\n第二个元素的前驱是:%d", priorElem(&L, 2));
	printf("\n第二个元素的后继是:%d", nextElem(&L, 2));

	if(listDelete(&L, 1, &e)){
		printf("\n被删除的元素的值:%d", e);
	}

	printf("\n线性表的当前长度:%d\n", L.length);
	
	listTraverse(&L);
	
	scanf("%c", &ch);
	return 0;
}
