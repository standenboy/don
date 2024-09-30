enum tokens {
	PUSH,
	POP,
	LITTERAL,
	WRITE,
	READ,
	LABEL,
	GOTO,
	GOTOIFZERO,
	GOTOIFNOTZERO,
	END,
	ADD, 
	SUB,
};

struct lextok {
	enum tokens type;
	int data; // can either be string of labelname or int * of litteral
};

struct ll {
	struct lextok *data;
	struct ll *next;
};

struct dict {
	int key;
	char *data;
};

void append(struct ll *l1, struct ll *l2);
