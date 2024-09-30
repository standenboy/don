#include <stddef.h>

#include "types.h"

void append(struct ll *l1, struct ll *l2){
	if (l1->next != NULL) append(l1->next, l2);
	else l1->next = l2;
}
