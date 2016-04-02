#include <stdio.h>
#include <malloc.h>

#define MinPQsize		2
#define MaxPQsize		63
#define MinData			-1
#define HeapStructType	HuffmanTree

struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;

struct TreeNode;
typedef struct TreeNode *HuffmanTree;



//优先队列的基本操作
int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);
PriorityQueue Initialize(int MaxElments);
HeapStructType DeleteMin(PriorityQueue H);
void Insert(HeapStructType X, PriorityQueue H);
PriorityQueue BuildMinHeap(int HuffmanSize);

//定义哈夫曼树的结构体
struct TreeNode
{
	char Element;
	int Weight;
	HuffmanTree Left;
	HuffmanTree Right;
};

//定义优先队列的结构体
struct HeapStruct
{
	int Capacity;
	int Size;
	HeapStructType *Elements;
};

int main()
{
	PriorityQueue H = NULL;
	int HuffmanSize = 0;
	int *test;

	scanf("%d", &HuffmanSize);
	H = BuildMinHeap(HuffmanSize);

	return 0;
}

//构建哈夫曼树
HuffmanTree Huffman(PriorityQueue H)
{
	int i; 
	HuffmanTree T;

	for (i = 1; i < H->Size; i++)
	{
		T = (HuffmanTree)malloc(sizeof(struct TreeNode));
		T->Left = DeleteMin(H);
		T->Right = DeleteMin(H);
		T->Weight = T->Left->Weight + T->Right->Weight;
		Insert(T, H);
	}

	T = DeleteMin(H);
	return T;
}

PriorityQueue BuildMinHeap(int HuffmanSize)
{
	PriorityQueue H;
	HeapStructType X;
	int i = 0;
	char Element;
	int Weight;

	H = Initialize(HuffmanSize);

	for (i = 0; i < HuffmanSize; i++)
	{
		getchar();
		scanf("%c %d", &X->Element, &X->Weight);
		Insert(X, H);
	}

	return H;
}


//删除优先队列的最小值
HeapStructType DeleteMin(PriorityQueue H)
{
	int i, Child;
	HeapStructType MinElement, LastElement;

	if (IsEmpty(H))
		return H->Elements[0];

	MinElement = H->Elements[1];
	LastElement = H->Elements[H->Size--];

	for (i = 1; i * 2 <= H->Size; i = Child)
	{
		Child = i * 2;
		if (Child != H->Size && H->Elements[Child + 1]->Weight < H->Elements[Child]->Weight)
			Child++;

		if (LastElement->Weight > H->Elements[Child]->Weight)
			H->Elements[i] = H->Elements[Child];
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}

//插入到优先队列
void Insert(HeapStructType X, PriorityQueue H)
{
	int i = 0;

	if (IsFull(H))
		return;

	for (i = ++H->Size; H->Elements[i / 2]->Weight > X->Weight; i /= 2)
		H->Elements[i] = H->Elements[i / 2];

	H->Elements[i] = X;
}

//优先队列的初始化
PriorityQueue Initialize(int MaxElments)
{
	PriorityQueue H = NULL;

	if (MaxElments < MinPQsize || MaxElments > MaxElments)
		return NULL;

	H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
	if (H == NULL)
		printf("Out of space");

	printf("MaxElements:%d\n", MaxElments);
	H->Elements = (HuffmanTree *)malloc(sizeof(TreeNode) * MaxElments);
	//if(H->Elements == NULL)
	//	printf("Out of space");

	H->Capacity = MaxElments;
	H->Size = 0;
	H->Elements[0]->Weight = MinData;

	return H;
}

int IsFull(PriorityQueue H)
{
	return H->Size == H->Capacity;
}

int IsEmpty(PriorityQueue H)
{
	return H->Size == 0;
}