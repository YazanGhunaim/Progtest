#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int id;
	char name[20];
	int  marks;
} Student_t;

int compareMarks(const void *pa, const void *pb){
	const Student_t *p1 = pa;
	const Student_t *p2 = pb;
	return p1-> marks - p2-> marks;
}

int compareNames(const void *pa, const void *pb){
	const Student_t *p1 = pa;
	const Student_t *p2 = pb;
	return strcmp(p1->name, p2->name);
}

int main () {
	// we have to decide on what element we want to sort
	
	Student_t records[] = {
						{1,"Yazan", 100},
						{2,"Saif", 90},
						{3,"Laith", 89},
						{4,"Louai", 99}
						};

	int length = sizeof(records)/sizeof(Student_t);

	qsort(records,length,sizeof(Student_t), compareMarks);

	printf("Sort on Marks:\n");
	for (int i = 0; i < length; ++i)
	{
		printf("%d %s %d\n", records[i].id,records[i].name,records[i].marks);
	}

	qsort(records,length,sizeof(Student_t), compareNames);

	printf("\nSort on names:\n");
	for (int i = 0; i < length; ++i)
	{
		printf("%d %s %d\n", records[i].id,records[i].name,records[i].marks);
	}

	return 0;
}
