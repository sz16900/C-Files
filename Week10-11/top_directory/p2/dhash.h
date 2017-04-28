#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDSIZE 30
#define PRIME  1567
#define CONST 5381
#define SHIFT 5
#define strsame(A,B) (strcmp(A,B) == 0)

struct data{
int used; /* 0 -> unused : 1 -> used */
int key;
char word[WORDSIZE];
struct data *next;
};
typedef struct data Data;

int hashKey(char *name, int prime);
Data *initTable(Data *table, int prime);
int primeFinder(int prime);
int doublePrime(int prime);
Data *crateNewTable(Data *tableptr, int prime, int array_size);
void insertData(Data *tableptr, char *names, int prime);
Data *readFile(int argc, char **argv, Data *tableptr, int prime);
Data *allocateNode(char *names, int key);
int tableFull(int cnt, int prime);
void findAverage(Data *tableptr, int prime, char **argv);
float checkWordExistance(float number_of_touches, int key, char *x, Data *tableptr);
