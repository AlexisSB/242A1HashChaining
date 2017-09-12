#ifndef FLEXARRAY_H_
#define FLEXARRAY_H_

/* header file for flexarray (of strings)  */

typedef struct flexarrayrec *flexarray;

/* appends string to flexarray
   (see flexarray.c for more information) */
extern void flexarray_append(flexarray f, char* item);

/* frees all memory associated with flexarray
   (see flexarray.c for more information) */
extern void flexarray_free(flexarray f);

/* creates new (empty) flexarray
   (see flexarray.c for more information) */
extern flexarray flexarray_new();

/* searches for a string in a flexarray
   (see flexarray.c for more information) */
extern int is_present(flexarray f, char* str);

/* applies a function to every item in a flexarray
   (see flexarray.c for more information) */
extern void visit(flexarray a, void f(char* str));

#endif
