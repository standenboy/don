#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "types.h"

#define MAXLABELS 1024

char *labels[MAXLABELS];
int labelcount = 0;

struct ll *tokenize(char *line){
	struct ll *out = malloc(sizeof(struct ll));
	struct ll *current = out; 
	char *type= strtok(line, " \n");
	while (type != NULL) {
		char *endptr;
		int n = strtol(type, &endptr, 10);
		struct lextok *tok = malloc(sizeof(struct lextok));
		current->data = tok;
		if (strcmp(type, "push") == 0) tok->type = PUSH;	
		else if (strcmp(type, "pop") == 0) tok->type = POP;	
		else if (strcmp(type, "write") == 0) tok->type = WRITE;	
		else if (strcmp(type, "read") == 0) tok->type = READ;	
		else if (strcmp(type, "goto") == 0) tok->type = GOTO;	
		else if (strcmp(type, "gotoiz") == 0) tok->type = GOTOIFZERO;	
		else if (strcmp(type, "gotoinz") == 0) tok->type = GOTOIFNOTZERO;	
		else if (strcmp(type, "add") == 0) tok->type = ADD;	
		else if (strcmp(type, "sub") == 0) tok->type = SUB;	

		else if (endptr != type) {
			tok->type = LITTERAL;
			tok->data = n;
		} else {
			tok->type = LABEL;
			labels[labelcount] = malloc(256);
			strcpy(labels[labelcount], type);
			tok->data = labelcount;
			labelcount++;
		}
		type = strtok(NULL, " \n");
		current->next = malloc(sizeof(struct ll));
		current = current->next;
	}
	struct lextok *tok = malloc(sizeof(struct lextok));
	tok->type = END;
	current->data = tok;
	current->next = NULL;
	return out;
}
struct ll *lex(char *filename){
	FILE *f = fopen(filename, "r");
	if (f == NULL){
		fprintf(stderr, "failed to open %s, does it exist?\n", filename);
		exit(0);
	}
	char *buf = malloc(256);
	struct ll *out = malloc(sizeof(struct ll));
	while (fgets(buf, 256, f) != NULL){
		append(out, tokenize(buf));
	}
	free(buf);
	fclose(f);
	out = out->next;
	return out;
}
