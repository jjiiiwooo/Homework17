#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 20
#define SWAP(x,y,t) ((t)=(x), (x)=(y),(y)=(t))

int list[MAX_SIZE];
int n;

int S_compareCount = 0; //선택정렬 비교횟수
int S_moveCount = 0; //선택정렬 이동 횟수 

int In_compareCount = 0; //삽입정렬 비교횟수
int In_moveCount = 0; //삽입정렬 이동 횟수 

int B_compareCount = 0; //버블 정렬 비교횟수
int B_moveCount = 0; //버블 정렬 이동 횟수 

int Shell_compareCount = 0; //쉘 정렬 비교 횟수
int Shell_moveCount = 0; //쉘 정렬 이동 횟수 

int M_compareCount = 0; //합병 정렬 비교 횟수
int M_moveCount = 0; //합병 정렬 이동 횟수 

int Q_compareCount = 0; //퀵 정렬 비교횟수
int Q_moveCount = 0; //퀵 정렬 이동횟수


int sorted[MAX_SIZE]; //합병정렬 추가 공간 

//0~99범위의 랜덤 숫자 생성
void Random(int array[], int n) {
	srand((unsigned)time(NULL)); //시드값 설정
	for (int i = 0; i < n; i++) {
		array[i] = rand() % 100;
		//중복없이
		for (int j = 0; j < i; j++) {
			if (array[i] == array[j])i--;
		}
	}
}

//선택 정렬 
void selection_sort(int list[], int n)
{
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++) {// 최솟값 탐색
			S_compareCount++; //비교횟수 증가 
			if (list[j] < list[least]) {
				least = j;
			}
			SWAP(list[i], list[least], temp);
			S_moveCount++; //이동횟수 증가 
		}
	}
}

//삽입 정렬
void insertion_sort(int list[], int n)
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--) {
			list[j + 1] = list[j]; //레코드의 오른쪽 이동
			In_moveCount++; //이동횟수 증가
			In_compareCount++; //비교횟수 증가
		}
		In_compareCount++; //비교횟수 증가
		list[j + 1] = key;
	}
}

//버블 정렬
void bubble_sort(int list[], int n)
{
	int i, j, temp;
	int flag; //정렬 여부를 확인하기 위한 변수 

	//바깥에 있는 for 루프는 자료구조 크기만큼 내부에 있는 for루프 실행
	for (i = n - 1; i > 0; i--) {
		flag = 0; //정렬 여부 초기화 
		//내부에 있는 for 루프는 바깥에 있는 for 루프가 한 번 실행될 때마다 그 반복 횟수가 줄어듬
		for (j = 0; j < i; j++) {
			//앞뒤의 레코드를 비교한 후 교체
			B_compareCount++; //비교횟수 증가 
			if (list[j] > list[j + 1])
			{
				SWAP(list[j], list[j + 1], temp);
				B_moveCount++; //이동횟수 증가 
				flag = 1; //요소 간 교환이 발생했으므로 정렬 여부 갱신
			}
		}
		if (flag == 0) {
			//교환없이 루프가 종료된 경우, 이미 정렬된 배열
			break;
		}
	}
}

//gap 만큼 떨어진 요소들을 삽입정렬
//정렬의 범위는 first에서 last
inc_insertion_sort(int list[], int first, int last, int gap)
{
	int i, j, key;

	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i]; //현재 삽입될 숫자인 i번째 정수를 key 변수로 복사 

		//현재 정렬된 배열은 i-gap까지이므로 i-gap번째부터 역순으로 조사
		//j 값은 first 이상이어야 하고
		//key 값보다 정렬된 배열에 있는 값이 크면 j번째를 j+gap번째로 이동
		for (j = i - gap; j >= first && list[j] > key; j = j - gap) {
			list[j + gap] = list[j]; //gap만큼 오른쪽으로 이동
			Shell_moveCount++; //이동횟수 증가
		}

		list[j + gap] = key;
		Shell_compareCount++; //비교횟수 증가 
	}

}

//쉘정렬
void shell_sort(int list[], int n) {
	int i, gap;

	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++) //부분 리스트의 개수는 gap
			inc_insertion_sort(list, i, n - 1, gap);
	}
}


//합병
void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	//분할 정렬된 list의 합병
	while (i <= mid && j <= right) {
		M_compareCount++;
		if (list[i] <= list[j]) {
			sorted[k++] = list[i++];
		}
		else {
			sorted[k++] = list[j++];
		}
	}
	if (i > mid) //남아 있는 레코드의 일괄 복사
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else //남아 있는 레코드의 일괄 복사
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	for (l = left; l <= right; l++) {
		list[l] = sorted[l];
		M_moveCount++;
	}

}

//합병 정렬
void merge_sort(int list[], int left, int right)
{
	int mid;
	if (left < right) {
		mid = (left + right) / 2; //리스트의 균등 분할
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

//분할
int partition(int list[], int left, int right)
{
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left]; //pivot을 배열의 시작 위치로 설정
	do {
		do {
			low++;
			Q_compareCount++; //비교횟수 증가
		} while (list[low] < pivot);
		do {
			high--;
			Q_compareCount++; //비교횟수 증가
		} while (list[high] > pivot);
		if (low < high) {
			SWAP(list[low], list[high], temp);
			Q_moveCount++; //이동 횟수 증가
		}
	} while (low < high);

	SWAP(list[left], list[high], temp);
	Q_compareCount++;
	return high;
}


//퀵 정렬
void quick_sort(int list[], int left, int right)
{
	if (left < right) {
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}



int main(void)
{
	//20개 20회 생성한 난수를 담을 2차원 배열
	int array[MAX_SIZE][MAX_SIZE];
	int n = sizeof(array[0]) / sizeof(array[0][0]);

	for (int i = 0; i < 20; i++) {
		Random(array[i], n);
	}
	
	printf("선택,삽입,버블,쉘,합병,퀵 정렬 비교분석\n");
	printf("\n");

	printf("선택정렬 20회 수행 평균 비교,이동횟수 :\n");
	//20회의 선택정렬 수행
	for (int i = 0; i < 20; i++) {
		selection_sort(list, n);
	}
	printf("Selection_sort_Average Move Count: %d\n", S_moveCount / 20);
	printf("Selection_srot_Average Compare Count:%d\n", S_compareCount / 20);
	printf("\n");

	printf("삽입정렬 20회 수행 평균 비교,이동횟수 :\n");
	//20회의 삽입정렬 수행
	for (int i = 0; i < 20; i++) {
		insertion_sort(list, n);
	}
	printf("Insertion_sort_Average Move Count: %d\n", In_moveCount/20);
	printf("Insertion_srot_Average Compare Count:%d\n", In_compareCount/20);
	printf("\n");

	printf("버블정렬 20회 수행 평균 비교,이동횟수 :\n");
	//20회의 버블정렬 수행
	for (int i = 0; i < 20; i++) {
		bubble_sort(list, n);
	}
	printf("Bubble_sort_Average Move Count: %d\n", B_moveCount/20);
	printf("Bubble_sort_Average Compare Count:%d\n",B_compareCount/20);
	printf("\n");

	printf("쉘 정렬 20회 수행 평균 비교,이동횟수:\n");
	//20회의 쉘 정렬 수행
	for (int i = 0; i < 20; i++) {
		shell_sort(array[i], n);
	}
	printf("Shell_sort_Average Move Count: %d\n", Shell_moveCount/20);
	printf("Shell_sort_Average Compare Count:%d\n", Shell_compareCount/20);
	printf("\n");

	printf("합병 정렬 20회 수행 평균 비교, 이동횟수:\n");
	//20회의 합병정렬 수행
	for (int i = 0; i < 20; i++) {
		merge_sort(list, 0, n - 1);
	}
	printf("Merge_sort_Average Move Count: %d\n", M_moveCount/20);
	printf("Merge_sort_Average Compare Count:%d\n", M_compareCount/20);
	printf("\n");

	printf("퀵 정렬 20회 수행 평균 비교, 이동횟수:\n");
	//20회의 퀵정렬 수행
	for (int i = 0; i < 20; i++) {
		quick_sort(array[i], 0, n - 1);
	}
	printf("Quick_sort_Average Move Count: %d\n", Q_moveCount/20);
	printf("Quick_sort_Average Compare Count:%d\n", Q_compareCount/20);


}
