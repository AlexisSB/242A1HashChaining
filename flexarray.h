#ifndef FLEXARRAY_H_
#define FLEXARRAY_H_

typedef struct flexarrayrec *flexarray;

extern void flexarray_append(flexarray f, char* item);
extern void flexarray_free(flexarray f);
extern flexarray flexarray_new();
extern int is_present(flexarray f, char* str);
extern void flexarray_sort(flexarray f);
extern void visit(flexarray a, void f(char* str));
extern void flexarray_print(char *str);

#endif
