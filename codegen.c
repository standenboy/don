#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "tokenize.h"
#include "stack.h"

void codegen(struct ll *code, char *filename){
	FILE *f = fopen(filename, "w");
	if (f == NULL) {
		fprintf(stderr, "failed to open tmp.ssa\n");
		exit(1);
	}

	struct ll *exp = code;
	struct ll *tmp;

	fprintf(f, "export function w $main() {\n@start\n");
	fprintf(f, "%%stack =l call $initstack(w 1024)\n");

	while (exp != NULL){
		switch (exp->data->type){
			case PUSH:
				if (exp->next->data->type == LITTERAL){
					fprintf(f, "%%r =w call $push(l %%stack, w %d) # push\n", 
							exp->next->data->data);
				}else
					fprintf(f, "%%r =w call $push(l %%stack, w %%acc) # push\n");
				break;

			case POP: 
			        fprintf(f, "%%acc =w call $pop(l %%stack) # pop\n");
				break;
			case WRITE:
			        fprintf(f, "%%r =w call $putchar(w %%acc) # write\n");
				break;
			case READ:
       				fprintf(f, "%%acc =w call $getchar() # read\n");
				break;
			case LABEL:
				tmp = code;
				while (tmp->data->type != LABEL && 
						labels[tmp->data->data] != 
						labels[exp->next->data->data]){
					if (tmp->next == NULL) exit(1);
					tmp = tmp->next;
				}
				fprintf(f, "@label%d\n", tmp->data->data);
				break;
			case GOTO:
				tmp = code;
				while (tmp->data->type != LABEL && 
						labels[tmp->data->data] != 
						labels[exp->next->data->data]){
					if (tmp->next == NULL) exit(1);
					tmp = tmp->next;
				}
				fprintf(f, "jmp @label%d\n", tmp->data->data);
				break;
			case GOTOIFZERO:
				tmp = code;
				while (tmp->data->type != LABEL && 
						labels[tmp->data->data] != 
						labels[exp->next->data->data]){
					if (tmp->next == NULL) exit(1);
					tmp = tmp->next;
				}
				fprintf(f, "jnz %%acc, @endlabel%d, @label%d\n", tmp->data->data, 
						tmp->data->data);
				fprintf(f, "@endlabel%d\n", tmp->data->data);
				exp = exp->next;
				break;
			case GOTOIFNOTZERO:
				tmp = code;
				while (tmp->data->type != LABEL && 
						labels[tmp->data->data] != 
						labels[exp->next->data->data]){
					if (tmp->next == NULL) exit(1);
					tmp = tmp->next;
				}
				fprintf(f, "jnz %%acc, @label%d, @endlabel%d\n", tmp->data->data, 
						tmp->data->data);
				fprintf(f, "@endlabel%d\n", tmp->data->data);
				exp = exp->next;
				break;
			case ADD:
				fprintf(f, "%%acc =w add %%acc, %d # add\n", exp->next->data->data);
				break;
			case SUB:
				fprintf(f, "%%acc =w sub %%acc, %d # add\n", exp->next->data->data);
				break;
		}
		exp = exp->next;
	}
	fprintf(f, "ret 0\n}\n");
	fclose(f);
}
