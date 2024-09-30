#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

int checker(struct ll *code){
	int ret = 0;
	struct ll *exp = code;
	int linecount = 0;

	while (exp != NULL){
		switch (exp->data->type){
			case END:
				linecount++;
				break;
			case PUSH:
				if (exp->next->data->type != LITTERAL &&
						exp->next->data->type != END){
					fprintf(stderr, "%d:expected END or LITTERAL\n", 
							linecount);
					ret++;
				}
				break;
			case POP: 
				if (exp->next->data->type != END){
					fprintf(stderr, "%d:expected END\n", linecount);
					ret++;
				}
				break;
			case WRITE:
				if (exp->next->data->type != END){
					fprintf(stderr, "%d:expected END\n", linecount);
					ret++;
				}
				break;
			case READ:
				if (exp->next->data->type!= END){
					fprintf(stderr, "%d:expected END\n", linecount);
					ret++;
				}
				break;
			case LABEL:
				if (exp->next->data->type != END){
					fprintf(stderr, "%d:expected END\n", linecount);
					ret++;
				}
				break;
			case GOTO:
				if (exp->next->data->type != LABEL){
					fprintf(stderr, "%d:expected LABEL\n", linecount);
					ret++;
				}
				break;
			case GOTOIFZERO:
				if (exp->next->data->type != LABEL){
					fprintf(stderr, "%d:expected LABEL\n", linecount);
					ret++;
				}
				break;
			case GOTOIFNOTZERO:
				if (exp->next->data->type != LABEL){
					fprintf(stderr, "%d:expected LABEL\n", linecount);
					ret++;
				}
				break;
			case ADD:
				if (exp->next->data->type != LITTERAL){
					fprintf(stderr, "%d:expected LITERAL\n", linecount);
					ret++;
				}
				break;
			case SUB:
				if (exp->next->data->type != LITTERAL){
					fprintf(stderr, "%d:expected LITERAL\n", linecount);
					ret++;
				}
				break;
			case LITTERAL:
				if (exp->next->data->type != END){
					fprintf(stderr, "%d:expected END\n", linecount);
					ret++;
				}
				break;
		}
		exp = exp->next;
	}
	return ret;
}
