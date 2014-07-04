#ifndef List_H
#define List_H

#define listAdd listNew

typedef struct List List;

struct List{
  List *next;
  void *data;
};

List *listNew(void *data, List *next);
void listDump(List *list, void (*dump)(void *));

#endif // List_H
