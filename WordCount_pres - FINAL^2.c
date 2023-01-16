#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define _CRT_SECURE_NO_WARNINGS
//#define _CRT_NONSTDC_NO_DEPRECATE
#define MAX_WORDLEN 30
#define INIT_COUNT 8045		//31 8044

struct wordcount {
	char strw[INIT_COUNT][MAX_WORDLEN];
	int strc[INIT_COUNT];
};

//SORT 1
void insertion_sort(struct wordcount list[], int n)
{
	int i, j, key;
	char keys[MAX_WORDLEN] = "";

	for (i = 1; i < n; i++) {
		strcpy(keys, list->strw[i]);
		key = list->strc[i];

		for (j = i - 1; j >= 0 && strcmp(list->strw[j],keys)==1; j--) {
			strcpy(list->strw[j + 1], list->strw[j]);
			list->strc[j + 1] = list->strc[j];
		}
		strcpy(list->strw[j + 1], keys);
		list->strc[j + 1] = key;
	}
}

//SORT 2
void inc_insertion_sort(struct wordcount list[], int first, int last, int gap)
{
	int i, j, key;
	char keyw[MAX_WORDLEN] = "";

	for (i = first + gap; i <= last; i = i + gap)
	{
		key = list->strc[i];
		strcpy(keyw,list->strw[i]);

		for (j = i - gap; j >= first && key < list->strc[j]; j = j - gap)
		{
			list->strc[j + gap] = list->strc[j];
			strcpy(list->strw[j + gap],list->strw[j]);
		}
		list->strc[j + gap] = key;
		strcpy(list->strw[j + gap],keyw);
	}
}
void shell_sort(struct wordcount list[], int n)
{
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)
			inc_insertion_sort(list, i, n - 1, gap);
	}
}

//SORT 3
int partition(struct wordcount list[], int left, int right)
{
	int temp;
	char tempw[MAX_WORDLEN] = "";
	int low, high;
	char pivotw[MAX_WORDLEN] = "";

	low = left;
	high = right + 1;
	strcpy(pivotw, list->strw[left]);
	do {
		do
			low++;
		while (strcmp(list->strw[low], pivotw) == -1);
		do
			high--;
		while (strcmp(list->strw[high], pivotw) == 1);
		if (low < high) {
			strcpy(tempw, list->strw[low]);
			strcpy(list->strw[low], list->strw[high]);
			strcpy(list->strw[high], tempw);
			temp = list->strc[low];
			list->strc[low] = list->strc[high];
			list->strc[high] = temp;
		}
	} while (low < high);

	strcpy(tempw, list->strw[left]);
	strcpy(list->strw[left], list->strw[high]);
	strcpy(list->strw[high], tempw);
	temp = list->strc[left];
	list->strc[left] = list->strc[high];
	list->strc[high] = temp;

	return high;
}
void quick_sort(struct wordcount list[], int left, int right)
{
	if (left < right) {
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

//main
int main(int argc, char* argv[]) 
{
	printf("===WordCount.c===\n");

	//argv
	if ((argc == 2 && strcmp(argv[1], "-3")) || (argc == 3 && !strcmp(argv[1], "-3"))) {
		//printf("The argument supplied is %s\n\n", argv[1]);
	}
	else if ((argc > 2 && strcmp(argv[1], "-3")) || (argc > 3) && !strcmp(argv[1], "-3")) {
		printf("Too many arguments supplied.\n");
		exit(0);
	}
	else {
		printf("One argument expected.\n");
		exit(0);
	}

	// OPEN FILE
	FILE* fp = fopen("d2.txt", "r");
	if (!fp) {
		printf("Cannot open '%s'\n", fp);
		exit(1);
	}

	// word extract by me
	int i, index, isUnique;

	struct wordcount str;
	char word[50];

	for (i = 0; i < INIT_COUNT; i++)
		str.strc[i] = 0;

	index = 0;

	while (fscanf(fp, "%s\n", word) != EOF)
	{
		isUnique = 1;
		for (i = 0; i < index && isUnique; i++)	
			if (strcmp(str.strw[i], word) == 0)
				isUnique = 0;		
		if (isUnique)
		{
			strcpy(str.strw[index], word);
			str.strc[index]++;
			index++;
		}
		else
			str.strc[i - 1]++;
	}
	fclose(fp);

	/*for (i = 0; i < index; i++)
		printf("%s %d\n", str.strw[i], str.strc[i]);

	printf("\n");
	*/

	//switch~case
	switch (atoi(argv[1]))
	{
	case -1:
		printf("---SORT 1---\n");

		insertion_sort(&str,index);

		for (i = 0; i < index; i++)
			printf("%s %d\n", str.strw[i], str.strc[i]);

		break;

	case -2:
		printf("---SORT 2---\n");

		shell_sort(&str, index);

		for (int i = 0; i < index; i++)
			printf("%d - %s\n", str.strc[i],str.strw[i]);

		break;

	case -3:
		printf("---SORT 3---\n");

		quick_sort(&str, 0, index);

		char* s = argv[2];

		int check = 0;
		for (i = 0; i < index; ++i)
			if (!strcmp(str.strw[i], s)) {
				printf("%s %d\n", str.strw[i], str.strc[i]);
				check = 1;
			}
		if (!check)
			printf("not found.\n");

		break;
	}

    return 0;
}