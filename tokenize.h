#define MAXLABELS 1024

extern char *labels[MAXLABELS];
extern int labelcount;

struct ll *tokenize(char *line);
struct ll *lex(char *filename);
