/*
 * File: strSort_funcs.c
 * Author:Qiwei Li
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "proj07_strList.h"

/* Read long string with fgetc() and dynamic buffer */
char *readLongStr(FILE *in)
{
	char *buf;
	int capacity = 8, nr = 0;
	char ch;

	/* Skip leading space(s) */
	while ((ch = fgetc(in)) != EOF) {
		if (!isspace(ch))
			break;
	}
	if (ch == EOF)
		return NULL;

	/* Initial the buffer with size as 8 */
	buf = (char *)malloc(sizeof(char) * capacity);
	if (!buf) {
		perror("malloc");
	        return NULL;
	}

	/* Push the first char */
	buf[nr++] = ch;

	/* Read the rest word */
	while ((ch = fgetc(in)) != EOF) {
		char *tmp;

		if (isspace(ch))
			break;

		buf[nr++] = ch;
		/* Keep the space for the null terminator */
		if (nr < capacity - 1)
			continue;

		/* Extend the buffer */
		tmp = (char *)malloc(sizeof(char) * (capacity * 2));
		if (!tmp) {
			perror("malloc");
			break;
		}
		memcpy(tmp, buf, sizeof(char) * capacity);
		free(buf);
		buf = tmp;
		capacity *= 2;
	}

	/* Add the null terminator */
	buf[nr] = '\0';

	return buf;
}

/* Insertion sort */
StrList *readInput(FILE *in)
{
	/* Use dummy as the dummy head */
	StrList dummy = {0, NULL};
	StrList *prev, *node;
	char *val;

	while ((val = readLongStr(in)) != NULL) {
		/* Allocate a new node */
		node = (StrList *)malloc(sizeof(StrList));
		if (!node) {
			perror("malloc");
			break;
		}

		/* Init the new node */
		node->val = val;
		node->next = NULL;

		/* Find the suitable position to insert */
		prev = &dummy;
		while (prev->next && strcmp(prev->next->val, val) < 0)
			prev = prev->next;
		node->next = prev->next;
		prev->next = node;
	}

	/* In case of malloc failure */
	if (val)
		free(val);

	/* Return the first node */
	return dummy.next;
}

int getLen(StrList* list)
{
	int len = 0;

	while (list) {
		len++;
		list = list->next;
	}
	return len;
}

void writeOutput(StrList* list, FILE* out)
{
	int i = 0;

	while (list) {
		fprintf(out, "%d: %s\n", i, list->val);
		list = list->next;
		i++;
	}
}

void freeList(StrList* list)
{
	StrList *next;

	while (list) {
		/* Record list->next */
		next = list->next;
		/* Free the char buffer in node */
		free(list->val);
		/* Free the list node itself */
		free(list);
		/* Get to the next node */
		list = next;
	}
}
