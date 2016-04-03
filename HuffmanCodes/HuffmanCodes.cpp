#include <malloc.h>
#include <stdio.h>
#include <string.h>

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
HuffmanTree Huffman(PriorityQueue H);
int GetWPL(HuffmanTree HT, int Deepth);
int FindWeight(HuffmanInfo HI, char X, int Len);
int IsPrefix(char Number[][64], int len);

int main()
{
	int HuffmanSize = 0;
	int WPL = 0;
	HuffmanInfo HI = NULL;
	PriorityQueue H = NULL;
	HuffmanTree	HT = NULL;
	HuffmanTree temp = NULL;

	int CompareGroup = 0;
	char CompareChar;
	char Number[64][64];
	int CompareWPL = 0;
	int test = 0;

	scanf("%d", &HuffmanSize);

	HI = (HuffmanInfo)malloc(sizeof(struct InfoNode) * HuffmanSize);
	H = Initialize(HuffmanSize);
	HT = (HuffmanTree)malloc(sizeof(struct HuffmanNode));
	temp = (HuffmanTree)malloc(sizeof(struct HuffmanNode));

	for (int i = 0; i < HuffmanSize; i++)
	{
		getchar();
		scanf("%c %d", &HI[i].Data, &HI[i].Weight);
		temp->Weight = HI[i].Weight;
		temp->Left = temp->Right = NULL;
		Insert(temp, H);
	}

	HT = Huffman(H);
	WPL = GetWPL(HT, 0);

	printf("end\n");
	scanf("%d", &CompareGroup);

	//ComperList = (PNumberChar)malloc(sizeof(struct NumberChar) * CompareGroup);
	
	for (int i = 0; i < CompareGroup; i++)
	{
		for (int j = 0; j < HuffmanSize; j++) 
		{
			getchar();
			scanf("%c %s", &CompareChar, Number[i]);
			test = FindWeight(HI, CompareChar, HuffmanSize);
			CompareWPL += FindWeight(HI, CompareChar, HuffmanSize) * strlen(Number[i]);
		}
		if (CompareWPL == WPL)
		{
			if (IsPrefix(Number, HuffmanSize))
				printf("Yes\n");
			else
				printf("No\n");
		}
		else
			printf("No\n");
		CompareWPL = 0;
	}
	

	return 0;
}

int IsPrefix(char Number[][64], int len)
{
	char *temp;
	char ComperTemp[64];
	for (int j = 0; j < len - 1; j++)
	{
		for (int i = 0; i < len - 1 - j; i++)
		{
			if (strlen(Number[i]) > strlen(Number[i + 1]))
			{
				temp = Number[i];
				Number[i][64] = Number[i + 1][64];
				Number[i + 1][64] = *temp;
			}
		}
	}

	for (int i = 0; i < len; i++)
	{
		printf("Number:%s\n", Number[i]);
	}

	for (int i = 0; i < len - 1; i++)
	{
		temp = Number[i];
		for (int j = i + 1; j < len - 1; j++)
		{
			strncpy(ComperTemp, temp, strlen(Number[i]));
			ComperTemp[strlen(Number[i])] = '\0';
			if (strcmp(temp, ComperTemp) == 0)
				return 0;
		}

	}
	return 1;
}

int FindWeight(HuffmanInfo HI, char X, int Len)
{
	for (int i = 0; i < Len; i++)
	{
		if (HI[i].Data == X)
			return HI[i].Weight;
	}
}

int GetWPL(HuffmanTree HT, int Deepth)
{
	if (HT->Left == NULL && HT->Right == NULL)
	{
		return (HT->Weight * Deepth);
	}	
	else
	{
		Deepth++;
		return(GetWPL(HT->Left, Deepth) + GetWPL(HT->Right, Deepth));
	}
}

HuffmanTree Huffman(PriorityQueue H)
{
	int i = 0;
	int j = 7;
	HuffmanTree HT;

	while (H->Size != 1)
	{
		HT = (HuffmanTree)malloc(sizeof(struct HuffmanNode));
		HT->Left = DeleteMin(H);
		HT->Right = DeleteMin(H);
		HT->Weight = HT->Left->Weight + HT->Right->Weight;
		Insert(HT, H);
	}
	return HT;
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