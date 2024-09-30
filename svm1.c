#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "types.h"
#include "tokenize.h"
#include "checker.h"
#include "codegen.h"

int main(int argc, char **argv){
	char *filename = NULL;

	for (int i = 1; i < argc; i++){
		filename = argv[i];
	}

	if (filename == NULL) {
		fprintf(stderr, "failed to open file, no name given!\n");
		exit(1);
	}

	struct ll *code = lex(filename);
	int errs = checker(code);
	
	if (errs != 0){
		fprintf(stderr, "exiting with %d errors\n", errs);
		exit(1);
	}


	codegen(code, "tmp.ssa");
	char *cmd = malloc(strlen("tmp.ssa") + 5);
	for (int i = 0; i < strlen("tmp.ssa") + 5; i++) cmd[i] = 0;
	strcat(cmd, "qbe ");
	strcat(cmd, "tmp.ssa");
	system(cmd);
	remove("tmp.ssa");
}
