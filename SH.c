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

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* �꾩슂�� �곕씪 �⑥닔 異붽� 媛��� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function�쇰줈 援ы쁽 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a�먮� �� hash table�� 留뚮뱺��. */
int hashing(int *a, int **ht);

/* hash table�먯꽌 key瑜� 李얠븘 hash table�� index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
    int *temp = NULL;

    // 만약 *a가 NULL인 경우
    if(*a == NULL) {
        // temp에 MAX_ARRAY_SIZE만큼의 int형 메모리를 동적으로 할당
        temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        // a가 가리키는 포인터에 temp의 주소를 저장하여 할당된 메모리를 a가 가리키도록 함
        *a = temp; 
    } else
        // *a가 NULL이 아닌 경우, temp에 *a의 값(메모리 주소) 할당
        temp = *a;

    // temp 배열의 각 요소에 0부터 MAX_ARRAY_SIZE-1까지의 난수를 저장
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)
        temp[i] = rand() % MAX_ARRAY_SIZE;

    return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
    // 만약 a가 NULL인 경우
    if (a == NULL) {
        printf("nothing to print.\n");
        return;
    }
    // 배열의 인덱스를 출력
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)
        printf("a[%02d] ", i);
    printf("\n");
    // 배열의 요소를 출력
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)
        printf("%5d ", a[i]);
    printf("\n");
}


int selectionSort(int *a)
{
    int min;
    int minindex;
    int i, j;

    printf("Selection Sort: \n");
    printf("----------------------------------------------------------------\n");

    // 정렬 이전 배열 출력
    printArray(a);

    // 선택 정렬 알고리즘 수행
    for (i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        minindex = i;
        min = a[i];
        // 현재 인덱스(i) 이후의 요소들 중에서 최솟값을 찾음
        for(j = i+1; j < MAX_ARRAY_SIZE; j++)
        {
            if (min > a[j])
            {
                min = a[j];
                minindex = j;
            }
        }
        // 현재 인덱스(i)와 최솟값의 인덱스(minindex)에 있는 요소를 교환
        a[minindex] = a[i];
        a[i] = min;
    }

    printf("----------------------------------------------------------------\n");
    // 정렬된 배열 출력
    printArray(a);
    return 0;
}

int insertionSort(int *a)
{
    int i, j, t;

    printf("Insertion Sort: \n");
    printf("----------------------------------------------------------------\n");

    // 정렬 이전 배열 출력
    printArray(a);

    // 삽입 정렬 알고리즘 수행
    for(i = 1; i < MAX_ARRAY_SIZE; i++)
    {
        t = a[i];
        j = i;
        // 현재 요소를 정렬된 부분 배열에 삽입하기 위해 비교 및 이동
        while (a[j-1] > t && j > 0)
        {
            a[j] = a[j-1];
            j--;
        }
        a[j] = t;
    }

    printf("----------------------------------------------------------------\n");
    // 정렬된 배열 출력
    printArray(a);

    return 0;
}

int bubbleSort(int *a)
{
    int i, j, t;

    printf("Bubble Sort: \n");
    printf("----------------------------------------------------------------\n");

    // 정렬 이전 배열 출력
    printArray(a);

    // 버블 정렬 알고리즘 수행
    for(i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        for (j = 0; j < MAX_ARRAY_SIZE; j++)
        {
            // 인접한 요소들을 비교하여 크기가 순서대로 되도록 교환
            if (a[j-1] > a[j])
            {
                t = a[j-1];
                a[j-1] = a[j];
                a[j] = t;
            }
        }
    }

    printf("----------------------------------------------------------------\n");
    // 정렬된 배열 출력
    printArray(a);

    return 0;
}
int shellSort(int *a)
{
    int i, j, k, h, v;

    printf("Shell Sort: \n");
    printf("----------------------------------------------------------------\n");

    // 정렬 이전 배열 출력
    printArray(a);

    // 셸 정렬 알고리즘 수행
    for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
    {
        for (i = 0; i < h; i++)
        {
            for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
            {
                v = a[j];
                k = j;
                // 삽입 정렬과 유사한 방식으로 요소를 삽입 정렬하며 부분 배열을 만들어감
                while (k > h-1 && a[k-h] > v)
                {
                    a[k] = a[k-h];
                    k -= h;
                }
                a[k] = v;
            }
        }
    }

    printf("----------------------------------------------------------------\n");
    // 정렬된 배열 출력
    printArray(a);

    return 0;
}

int quickSort(int *a, int n)
{
    int v, t;
    int i, j;

    if (n > 1)
    {
        v = a[n-1];
        i = -1;
        j = n - 1;

        // 퀵 정렬 알고리즘 수행
        while(1)
        {
            while(a[++i] < v);
            while(a[--j] > v);

            if (i >= j) break;
            // i번째와 j번째 요소를 교환
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
        // v 값을 기준으로 배열을 분할하고, 재귀적으로 퀵 정렬을 호출하여 정렬 수행
        t = a[i];
        a[i] = a[n-1];
        a[n-1] = t;

        quickSort(a, i);
        quickSort(a+i+1, n-i-1);
    }

    return 0;
}

int hashCode(int key) {
	return key % MAX_HASH_TABLE_SIZE;
}
int hashing(int *a, int **ht)
{
    int *hashtable = NULL;

    if (*ht == NULL) {
        hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *ht = hashtable; 
    } else {
        hashtable = *ht;	
    }

    // 해시 테이블 초기화
    for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        hashtable[i] = -1;

    int key = -1;
    int hashcode = -1;
    int index = -1;
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        key = a[i];
        hashcode = hashCode(key);

        if (hashtable[hashcode] == -1)
        {
            // 해당 해시 코드 위치가 비어있을 경우, 키를 저장
            hashtable[hashcode] = key;
        } else {
            // 해당 해시 코드 위치가 이미 사용 중인 경우, 선형 탐사(linear probing) 방법으로 빈 위치를 찾아 키를 저장
            index = hashcode;

            while (hashtable[index] != -1)
            {
                index = (++index) % MAX_HASH_TABLE_SIZE;
            }
            hashtable[index] = key;
        }
    }

    return 0;
}

int search(int *ht, int key)
{
    int index = hashCode(key);

    // 해시 코드 위치에 저장된 값이 키와 일치하는 경우, 해당 인덱스 반환
    if (ht[index] == key)
        return index;

    // 일치하는 값이 나올 때까지 선형 탐사(linear probing) 방법으로 해시 테이블을 탐색
    while (ht[++index] != key)
    {
        index = index % MAX_HASH_TABLE_SIZE;
    }
    return index;
}
