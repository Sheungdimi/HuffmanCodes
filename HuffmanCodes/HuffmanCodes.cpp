#include <stdio.h>
#include <malloc.h>

#define MinPQsize		2
#define MaxPQsize		63
#define MinData			-1
#define HeapStructType	int
struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;

int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);
PriorityQueue Initialize(int MaxElments);

struct HeapStruct
{
	int Capacity;
	int Size;
	HeapStructType *Elements;
};

int main()
{

	return 0;
}

//ɾ�����ȶ��е���Сֵ
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
		if (Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
			Child++;

		if (LastElement > H->Elements[Child])
			H->Elements[i] = H->Elements[Child];
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}

//���뵽���ȶ���
void Insert(HeapStructType X, PriorityQueue H)
{
	int i = 0;

	if (IsFull(H))
		return;

	for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
		H->Elements[i] = H->Elements[i / 2];

	H->Elements[i] = X;
}

//���ȶ��еĳ�ʼ��
PriorityQueue Initialize(int MaxElments)
{
	PriorityQueue H;

	if (MaxElments < MinPQsize || MaxElments > MaxElments)
		return NULL;

	H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
	if (H == NULL)
		printf("Out of space");

	H->Elements = (HeapStructType *)malloc(sizeof(HeapStruct) * MaxElments);
	if(H->Elements == NULL)
		printf("Out of space");

	H->Capacity = MaxElments;
	H->Size = 0;
	H->Elements[0] = MinData;

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