#if 0
#include <stdio.h>
#include <malloc.h>

#define MinPQsize		2
#define MaxPQsize		63
#define MinData			-1
#define HeapStructType	HuffmanTreeNode

struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;

struct TreeNode;
typedef struct TreeNode HuffmanTreeNode;
typedef struct TreeNode *HuffmanTree;

struct InfoNode;
typedef struct InfoNode *HuffmanInfo;

HuffmanTree Huffman(PriorityQueue H);

//优先队列的基本操作
int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);
PriorityQueue Initialize(int MaxElments);
HeapStructType DeleteMin(PriorityQueue H);
PriorityQueue Insert(HeapStructType X, PriorityQueue H);

//定义哈夫曼树的结构体
struct TreeNode
{
	//char Element;
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

struct InfoNode 
{
	char Data;
	int Weight;
};

int main()
{
	PriorityQueue H = NULL;
	HuffmanTree	  HT = NULL;
	HuffmanInfo	  HI = NULL;

	HeapStructType *temp = NULL;
	int HuffmanSize = 0;
	int *test;

	scanf("%d", &HuffmanSize);
	HI = (HuffmanInfo)malloc(sizeof(struct InfoNode) * HuffmanSize);
	temp = (HeapStructType *)malloc(sizeof(struct TreeNode));
	
	H = Initialize(HuffmanSize);

	for (int i = 0; i < HuffmanSize; i++)
	{
		getchar();
		scanf("%c %d", &HI[i].Data, &HI[i].Weight);
		temp->Weight = HI[i].Weight;
		temp->Right = temp->Left = NULL;
		H = Insert(*temp, H);
	}

	printf("HI:\n");
	for (int i = 0; i < HuffmanSize; i++)
	{
		printf("%c %d\n", HI[i].Data, HI[i].Weight);
	}

	printf("H:\n");
	for (int i = 0; i < HuffmanSize + 1; i++)
	{
		printf("%d\n", H[i].Elements->Weight);
	}
	//HT = Huffman(H);


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
		*T->Left = DeleteMin(H);	
		*T->Right = DeleteMin(H);
		T->Weight = T->Left->Weight + T->Right->Weight;
		Insert(*T, H);
	}

	*T = DeleteMin(H);
	return T;
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
		if (Child != H->Size && H->Elements[Child + 1].Weight < H->Elements[Child].Weight)
			Child++;

		if (LastElement.Weight > H->Elements[Child].Weight)
			H->Elements[i] = H->Elements[Child];
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}

//插入到优先队列
PriorityQueue Insert(HeapStructType X, PriorityQueue H)
{
	int i = 0;

	if (IsFull(H))
		return NULL;

	for (i = ++H->Size; H->Elements[i / 2].Weight > X.Weight; i /= 2)
		H->Elements[i] = H->Elements[i / 2];

	H->Elements[i] = X;

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

//优先队列的初始化
PriorityQueue Initialize(int MaxElments)
{
	PriorityQueue H = NULL;

	if (MaxElments < MinPQsize || MaxElments > MaxElments)
		return NULL;

	H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
	if (H == NULL)
		printf("Out of space");

	H->Elements = (HeapStructType *)malloc(sizeof(struct TreeNode) * (MaxElments + 1));
	if (H->Elements == NULL)
		printf("Out of space");

	H->Capacity = MaxElments;
	H->Size = 0;
	H->Elements[0].Weight = MinData;

	return H;
}

#endif

#include <malloc.h>
#include <stdio.h>

struct InfoNode;
typedef struct InfoNode *HuffmanInfo;

struct HuffmanNode;
typedef struct HuffmanNode HuffmanTreeNode;
typedef struct HuffmanNode *HuffmanTree;

struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;

struct InfoNode
{
	char Data;
	int  Weight;
};

struct HuffmanNode
{
	int Weight;
	HuffmanTree Left;
	HuffmanTree Right;
};

struct HeapStruct
{
	int Capacity;
	int Size;
	HuffmanTree TreeCell;
};

HuffmanTree DeleteMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
PriorityQueue Initialize(int MaxElements);
int IsFull(PriorityQueue H);
void Insert(HuffmanTree X, PriorityQueue H);

int main()
{
	int HuffmanSize = 0;
	HuffmanInfo HI = NULL;
	PriorityQueue H = NULL;
	
	HuffmanTree temp = NULL;
	scanf("%d", &HuffmanSize);

	HI = (HuffmanInfo)malloc(sizeof(struct InfoNode) * HuffmanSize);
	H = Initialize(HuffmanSize);
	temp = (HuffmanTree)malloc(sizeof(struct HuffmanNode));

	for (int i = 0; i < HuffmanSize; i++)
	{
		getchar();
		scanf("%c %d", &HI[i].Data, &HI[i].Weight);
		temp->Weight = HI[i].Weight;
		Insert(temp, H);
	}

	printf("HI:\n");
	for (int i = 0; i < HuffmanSize; i++)
	{
		printf("%c %d\n", HI[i].Data, HI[i].Weight);
	}

	printf("H:\n");
	for (int i = 0; i < HuffmanSize; i++)
	{
		printf("%d\n", H->TreeCell[i].Weight);
	}

	temp = DeleteMin(H);
	printf("Delete1:%d\n", temp->Weight);

	temp = DeleteMin(H);
	printf("Delete2:%d\n", temp->Weight);

	temp = DeleteMin(H);
	printf("Delete3:%d\n", temp->Weight);

	temp = DeleteMin(H);
	printf("Delete4:%d\n", temp->Weight);

	temp = DeleteMin(H);
	printf("Delete5:%d\n", temp->Weight);

	temp = DeleteMin(H);
	printf("Delete6:%d\n", temp->Weight);

	temp = DeleteMin(H);
	printf("Delete7:%d\n", temp->Weight);
	return 0;
}

HuffmanTree DeleteMin(PriorityQueue H)
{
	int Parent = 0;
	int Child = 0;
	HuffmanTreeNode LastElement;
	HuffmanTree MinElement;
	
	MinElement = (HuffmanTree)malloc(sizeof(struct HuffmanNode));
	if (IsEmpty(H))
		return H->TreeCell;

	*MinElement = H->TreeCell[1];
	LastElement = H->TreeCell[H->Size--];

	for ( Parent = 1; Parent * 2 <= H->Size; Parent = Child)
	{
		Child = Parent * 2;
		if (Child != H->Size && H->TreeCell[Child + 1].Weight < H->TreeCell[Child].Weight)
			Child++;
		
		if (LastElement.Weight > H->TreeCell[Child].Weight)
			H->TreeCell[Parent] = H->TreeCell[Child];
		else
			break;
	}

	H->TreeCell[Parent] = LastElement;
	return MinElement;
}

int IsEmpty(PriorityQueue H)
{
	return H->Size == 0;
}

int IsFull(PriorityQueue H)
{
	return H->Size == H->Capacity;
}

void Insert(HuffmanTree X, PriorityQueue H)
{
	int i;

	if (IsFull(H))
		return;

	for (i = ++H->Size; H->TreeCell[i / 2].Weight > X->Weight; i /= 2)
		H->TreeCell[i] = H->TreeCell[i / 2];

	H->TreeCell[i] = *X;
}

PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue H;

	H = (PriorityQueue)malloc(sizeof(struct HeapStruct));

	H->TreeCell = (HuffmanTree)malloc(sizeof(struct HuffmanNode) * MaxElements + 1);

	H->Capacity = MaxElements;
	H->Size = 0;
	H->TreeCell[0].Weight = -1;

	return H;
}