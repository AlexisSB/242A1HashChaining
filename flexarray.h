#ifndef FLEXARRAY_H_
#define FLEXARRAY_H_

/* Header file for flexarray (of strings)  */

typedef struct flexarrayrec *flexarray;

/* Appends string to flexarray.
   (see flexarray.c for more information) */
extern void flexarray_append(flexarray f, char* item);

/* Frees all memory associated with flexarray.
   (see flexarray.c for more information) */
extern void flexarray_free(flexarray f);

/* Creates new (empty) flexarray.
   (see flexarray.c for more information) */
extern flexarray flexarray_new();

/* Searches for a string in a flexarray.
   (see flexarray.c for more information) */
extern int is_present(flexarray f, char* str);

/* Applies a function to every item in a flexarray.
   (see flexarray.c for more information) */
extern void visit(flexarray a, void f(char* str));

#endif
