/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE 13 /* prime number */
#define MAX_HASH_TABLE_SIZE MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a); // 초기화 함수
int freeArray(int *a);	 // 배열 메모리 해제 함수
void printArray(int *a); // 배열 출력 함수

int selectionSort(int *a); // 선택정렬
int insertionSort(int *a); // 삽입정렬
int bubbleSort(int *a);	   // 버블정렬
int shellSort(int *a);	   // 셸정렬
/* recursive function으로 구현 */
int quickSort(int *a, int n); // 퀵솔트

/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);

int main()
{
	char command;		   // 명령 입력받을 변수
	int *array = NULL;	   // 배열
	int *hashtable = NULL; // 해시 테이블
	int key = -1;		   // 검색에 사용할 키
	int index = -1;		   // 배열 원소의 인덱스

	srand(time(NULL)); // 랜덤함수

	do
	{
		printf("----------------------------------------------------------------\n"); // 안내문 출력
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = "); // 명령 입력받기
		scanf(" %c", &command);

		switch (command) // 입력받은 명령에 따라 case문 실행
		{
		case 'z':
		case 'Z':
			initialize(&array); // z 입력시 배열 초기화
			break;
		case 'q':
		case 'Q':
			freeArray(array); // q 입력시 배열 메모리 해제하고 프로그램 종료
			break;
		case 's':
		case 'S':
			selectionSort(array); // s 입력시 선택정렬
			break;
		case 'i':
		case 'I':
			insertionSort(array); // i 입력시 삽입 정렬
			break;
		case 'b':
		case 'B':
			bubbleSort(array); // b 입력시 버블정렬
			break;
		case 'l':
		case 'L':
			shellSort(array); // l 입력시 셸정렬
			break;
		case 'k':
		case 'K':
			printf("Quick Sort: \n"); // k 입력시 퀵정렬
			printf("----------------------------------------------------------------\n");
			printArray(array);				  // 정렬 전 배열 출력
			quickSort(array, MAX_ARRAY_SIZE); // 퀵정렬 실행
			printf("----------------------------------------------------------------\n");
			printArray(array); // 정렬 후 배열 출력

			break;

		case 'h':
		case 'H':
			printf("Hashing: \n"); // h 입력시 해싱
			printf("----------------------------------------------------------------\n");
			printArray(array);			// 해싱 전 배열 출력
			hashing(array, &hashtable); // 해시테이블 함수 실행
			printArray(hashtable);		// 해싱 후 배열 출력
			break;

		case 'e':
		case 'E':
			printf("Your Key = "); // e 입력시 검색, 키 입력받고
			scanf("%d", &key);
			printArray(hashtable);																		// 해시테이블 출력
			index = search(hashtable, key);																// 테이블에서 인덱스 검색
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]); // 키, 인덱스, 해시태이블 값 출력
			break;

		case 'p':
		case 'P':
			printArray(array); // p 입력시 배열 출력
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 기타 입력시 안내문 출력후 반복문 재실행
			break;
		}

	} while (command != 'q' && command != 'Q'); // q 입력시까지 반복

	return 1; // 반복문 종료시 반환 후 프로그램 종료
}

int initialize(int **a) // 배열 초기화 함수
{
	int *temp = NULL; // 임시로 사용할 포인터변수 선언 및 초기화

	/* array가 NULL인 경우 메모리 할당 */
	if (*a == NULL)
	{
		temp = (int *)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp; /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0; // 반환 후 함수 종료
}

int freeArray(int *a) // 배열 메모리 해제 함수
{
	if (a != NULL) /// null이 아닐 경우 메모리 해제
		free(a);
	return 0; // 반환 후 함수 종료
}

void printArray(int *a) // 배열 출력 함수
{
	if (a == NULL) // 배열이 null이면
	{
		printf("nothing to print.\n"); // 안내문 출력 후 반환 후 함수 종료
		return;
	}
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) // 배열 사이즈만큼 배열 원소 이름 출력
		printf("a[%02d] ", i);
	printf("\n");
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) // 배열 사이즈만큼 배열 원소 값 출력
		printf("%5d ", a[i]);
	printf("\n");
}

int selectionSort(int *a) // 선택 정렬
{
	int min;	  // 최소값 변수
	int minindex; // 최소값 인덱스 변수
	int i, j;	  // 반복문용 변수

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 전 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++) // 배열 사이즈만큼 반복
	{
		minindex = i;							 // 최소값 인덱스 값 수정
		min = a[i];								 // 최소값 추정
		for (j = i + 1; j < MAX_ARRAY_SIZE; j++) // 다음 원소부터 끝까지 반복
		{
			if (min > a[j]) // 새로운 최소값 발견하면
			{
				min = a[j]; // 최소값과 인덱스 값 수정
				minindex = j;
			}
		}
		a[minindex] = a[i]; // 발견한 최소 원소와 기존 원소 교체
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 후 배열 출력 후 반환 후 함수 종료
	return 0;
}

int insertionSort(int *a) // 삽입 정렬
{
	int i, j, t; // 반복문용 변수

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 전 배열 출력

	for (i = 1; i < MAX_ARRAY_SIZE; i++) // 배열 사이즈만큼 반복
	{
		t = a[i];					  // 해당 원소값 저장
		j = i;						  // while문에 사용할 변수 해당 원소 인덱스로  초기화
		while (a[j - 1] > t && j > 0) // 이전 원소가 현재 원소보다 크면 반복
		{
			a[j] = a[j - 1]; // 이전 원소를 현재 원소 자리로 이동
			j--;			 // 인덱스를 이전으로 이동하여 비교를 위해 반복
		}
		a[j] = t; // 현재 원소를 적절한 위치에 삽입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 후 배열 출력

	return 0;
}

int bubbleSort(int *a) // 버블 정렬
{
	int i, j, t; // 반복문용 변수

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 전 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++) // 배열 전체 돌면서 반복
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++) // 배열 전체 돌면서 반복
		{
			if (a[j - 1] > a[j]) // 연속한 두 원소 중 앞 원소가 뒤 원소보다 크면
			{
				t = a[j - 1]; // 두 원소의 값을 교체
				a[j - 1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 후 배열 출력

	return 0; // 반환 후 함수 종료
}

int shellSort(int *a) // 셸 정렬
{
	int i, j, k, h, v; // 반복문용 변수 및 임시 변수

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 전 배열 출력

	for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2) // 간격 h를 배열 전체의 절반부터 시작하여 1까지 반으로 줄여가며 반복
	{
		for (i = 0; i < h; i++) // h만큼의 그룹으로 나누어 반복
		{
			for (j = i + h; j < MAX_ARRAY_SIZE; j += h) // 그룹 내에서 삽입 정렬 수행
			{
				v = a[j];						  // 현재 원소값 저장
				k = j;							  // while문에 사용할 변수에 현재 원소 인덱스 저장
				while (k > h - 1 && a[k - h] > v) // 그룹 내에서 삽입 정렬 수행
				{
					a[k] = a[k - h]; // 간격 h만큼 뒤로 이동
					k -= h;
				}
				a[k] = v; // 정렬된 위치에 원소값 삽입
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 후 배열 출력

	return 0; // 반환 후 함수 종료
}

int quickSort(int *a, int n) // 퀵 정렬
{
	int v, t; // 값 저장용 변수
	int i, j; // 반복문용 변수

	if (n > 1) // 정렬할 배열의 길이가 1보다 큰 경우에만 실행
	{
		v = a[n - 1]; // 마지막 원소를 피벗으로 선택
		i = -1;		  // 왼쪽 부분 배열의 인덱스 초기값
		j = n - 1;	  // 오른쪽 부분 배열의 인덱스 초기값

		while (1) // 무한 반복
		{
			while (a[++i] < v) // 피벗보다 작은 원소를 찾을 때까지 i 증가
				;
			while (a[--j] > v) // 피벗보다 큰 원소를 찾을 때까지 j 감소
				;

			if (i >= j) // i와 j가 엇갈리면 반복문 종료
				break;

			t = a[i]; // i와 j가 엇갈리지 않았다면 a[i]와 a[j]의 값을 교환
			a[i] = a[j];
			a[j] = t;
		}

		t = a[i]; // 피벗을 올바른 위치에 배치
		a[i] = a[n - 1];
		a[n - 1] = t;

		quickSort(a, i);				 // 왼쪽 부분 배열에 대해 재귀적으로 퀵 정렬 수행
		quickSort(a + i + 1, n - i - 1); // 오른쪽 부분 배열에 대해 재귀적으로 퀵 정렬 수행
	}

	return 0; // 반환 후 함수 종료
}

int hashCode(int key) // 해시코드 함수
{
	return key % MAX_HASH_TABLE_SIZE; // key값을 해시테이블 크기로 나눈 나머지 반환 후 함수 종료
}

int hashing(int *a, int **ht) // 해싱 함수
{
	int *hashtable = NULL; // 해시테이블 포인터변수 선언 및 초기화

	/* hash table이 NULL인 경우 메모리 할당 */
	if (*ht == NULL)
	{
		hashtable = (int *)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable; /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else
	{
		hashtable = *ht; /* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++) // 해시테이블 원소들의 값을 -1로 함
		hashtable[i] = -1;

	int key = -1; // 키값, 해시코드, 인덱스값 모두 -1로 초기화
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) // 배열을 돌면서 반복
	{
		key = a[i];				  // 해당 원소를 키값으로 저장
		hashcode = hashCode(key); // 해시코드 생성

		if (hashtable[hashcode] == -1) // 해시테이블의 해당 인덱스가 비어있으면
		{
			hashtable[hashcode] = key; // 키값 저장
		}
		else // 비어있지 않으면
		{

			index = hashcode; // 인덱스에 해시코드값 저장

			while (hashtable[index] != -1) // 저장 안된 인덱스 나올 때 까지
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; // 인덱스를 1씩 증가시킴
			}
			hashtable[index] = key; // 빈 인덱스 찾아서 키값 저장
		}
	}

	return 0; // 반환 후 함수 종료
}

int search(int *ht, int key) // 탐색 함수
{
	int index = hashCode(key); // key값을 해시코드화 해서 인덱스로 저장

	if (ht[index] == key) // 해시테이블의 해당 인덱스 값이 키값과 일치하면
		return index;	  // 인덱스값 반환 후 함수 종료

	while (ht[++index] != key) // 같지 않다면 같을 때 까지 인덱스를 1씩 증가시킴
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index; // 인덱스값 반환 후 함수 종료
}
