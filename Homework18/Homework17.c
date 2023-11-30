#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 20
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

int list[MAX_SIZE];
int n;
int compareCount = 0; //��Ƚ��
int moveCount = 0; //�̵� Ƚ�� 

//���� ���� ���
void Print(int list[], int n) {
    for (int i = 0; i < n; i++)
        printf("%3d", list[i]);
    printf("\n");
}

//0~99������ ���� ���� ����
void Random(int array[], int n) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 100;
        //�ߺ�����
        for (int j = 0; j < i; j++) {
            if (array[i] == array[j])i--;
        }
    }
}


//����
int partition(int list[], int left, int right)
{
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left];
    do {
        do {
            low++;
            compareCount++;
        }while (list[low] < pivot);
        do {
            high--;
            compareCount++;
        }
        while (list[high] > pivot);
        if (low < high) {
            SWAP(list[low], list[high], temp);
            moveCount++;
        }
    } while (low < high);

    SWAP(list[left], list[high], temp);
    compareCount++;
    return high;
}

//����(���� ���� ����)
int partition_print(int list[], int left, int right)
{
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left];
    do {
        do {
            low++;
        } while (list[low] < pivot);
        do {
            high--;
        } while (list[high] > pivot);
        if (low < high) {
            SWAP(list[low], list[high], temp);
        }
        for (int i = 0; i < MAX_SIZE; i++) {
            printf("%3d", list[i]);
        }
        printf("\n");
    } while (low < high);

    SWAP(list[left], list[high], temp);
    return high;
}

//�� ���� 
void quick_sort(int list[], int left, int right)
{
    if (left < right) {
        int q = partition(list, left, right);
        quick_sort(list, left, q - 1);
        quick_sort(list, q + 1, right);
    }
}

//������ (���İ��� ����)
void quick_sort_print(int list[], int left, int right)
{
    if (left < right) {
        int q = partition_print(list, left, right);
        quick_sort_print(list, left, q - 1);
        quick_sort_print(list, q + 1, right);
    }
}

int main(void)
{
    //20�� 20ȸ ������ ������ ���� 2���� �迭
    int array[MAX_SIZE][MAX_SIZE];
    int n = sizeof(array[0]) / sizeof(array[0][0]);

    for (int i = 0; i < 20; i++) {
        Random(array[i], n);
    }
    printf("Original List\n");
    Random(list, n);
    Print(list, n);
    printf("\n");

    printf("quick sort\n");
    quick_sort_print(list, 0, n - 1);
    printf("����� ���� ���İ��:\n");
    Print(list, n);

    //20ȸ�� ������ ����
    for (int i = 0; i < 20; i++) {
        quick_sort(array[i],0,n-1);
    }
    printf("Average Move Count: %d\n", moveCount / 20);
    printf("Average Compare Count:%d\n", compareCount / 20);
    
}

