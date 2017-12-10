#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

struct fn{
	char group[100];
	int arr;
};

struct stdata {
	char word[100];
};

void main() {
	struct fn *name;
	struct _finddata_t fd;
	struct fn temp;
	long handle;
	int result = 1;
	int size = 0;
	int i = 0;
	int j = 0;
	int a;
	int count, num = 0;
	FILE *f = NULL;
	char ch[1000];
	char search[100];
	int b, c, r;

	struct stdata *data;

	handle = _findfirst("*.txt", &fd);
	if (handle == -1) return;
	while (result != -1)
	{
		result = _findnext(handle, &fd);
		size++;
	}

	name = (struct fn*)malloc(sizeof(struct fn)* size);

	result = 1;
	handle = _findfirst("c:\*.txt", &fd);
	if (handle == -1) return;
	while (result != -1)
	{
		strcpy(name[i].group, fd.name);
		i++;
		result = _findnext(handle, &fd);
	}

	_findclose(handle);

	printf("검색 : ");
	scanf("%s", search);
	strlwr(search);

	for (j = 0; j < size;j++) {
		num = 0;

		f = fopen(name[j].group, "r");

		count = 0;
		while (!feof(f)) {
			fscanf(f, "%s", ch);
			count++;
		}

		fseek(f, 0, SEEK_SET);

		data = (struct stdata*)calloc(count, sizeof(struct stdata));

		count = 0;
		while (!feof(f)) {
			fscanf(f, "%s", data[count].word);
			count++;
		}
	
		for (a = 0;a < count;a++) {
			fscanf(f, "%s", data[a].word);
			strlwr(data[a].word);
			if (strstr(data[a].word, search) != NULL) {
				num++;
			}
		}
		name[j].arr = num;
		fclose(f);
	}

	for (b = 0; b < size;b++) {
		for (c = 0;c < size - 1;c++) {
			if (name[c].arr < name[c + 1].arr) {
				temp = name[c];
				name[c] = name[c + 1];
				name[c + 1] = temp;
			}
		}
	}

	for (r = 0;r < 1000;r++) {
		if (name[r].arr == 0) {
			continue;
		}
		
		printf("파일이름: %s, 포함단어개수: %d, Rank : %d\n", name[r].group, name[r].arr, r+1);
	}
	free(name);
}