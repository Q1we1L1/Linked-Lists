/*
 * File: intSort_funcs.c
 * Author:Qiwei Li
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "proj07_intList.h"

/* Insertion sort */
IntList *readInput(FILE *in)
{
	/* Use dummy as the dummy head */
	IntList dummy = {0, NULL};
	IntList *prev, *node;
	int val;
	int ret;

	while ((ret = fscanf(in, "%d", &val)) == 1) {
		/* Allocate a new node */
		node = (IntList *)malloc(sizeof(IntList));
		if (!node) {
			perror("malloc");
			break;
		}

		/* Init the new node */
		node->val = val;
		node->next = NULL;

		/* Find the suitable position to insert */
		prev = &dummy;
		while (prev->next && prev->next->val < val)
			prev = prev->next;
		node->next = prev->next;
		prev->next = node;
	}

	if (ret != EOF)
		fprintf(stderr, "INPUT ERROR: rc=%d.  Terminating the read of the input.", ret);

	/* Return the first node */
	return dummy.next;
}

int getLen(IntList *list)
{
	int len = 0;

	while (list) {
		len++;
		list = list->next;
	}
	return len;
}

void writeOutput(IntList *list, FILE *out)
{
	int i = 0;

	while (list) {
		fprintf(out, "%d: %d\n", i, list->val);
		list = list->next;
		i++;
	}
}

void freeList(IntList *list)
{
	IntList *next;

	while (list) {
		/* Record list->next */
		next = list->next;
		free(list);
		list = next;
	}
}
