#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_t {
  struct node_t *next;
  int data;
};

struct node_t *read_list(FILE *inp){

    int num;

    size_t struct_size = sizeof(struct node_t);
    struct node_t *odd_head = NULL;
    struct node_t *odd_tail = NULL;
    struct node_t *even_head = NULL;
    struct node_t *even_tail = NULL;

    while (fscanf(inp, "%d", &num) != EOF)
    {
        struct node_t **cur;
        if (num % 2 == 0) cur = &even_tail;
        else cur = &odd_tail;

        struct node_t *tmp = malloc(struct_size);
        tmp->data = num;
        tmp->next = NULL;
        if (*cur) {
            (*cur)->next = tmp;
            (*cur) = tmp;
        }
        else {
            if (num % 2 == 0) {
                even_head = tmp;
                even_tail = tmp;
            }
            else {
                odd_head = tmp;
                odd_tail = tmp;
            }
        }
    }
    fclose(inp);

    if (even_head){
        even_tail->next = odd_head;
        return even_head;
    }
    else {
        return odd_head;
    }
}

void delete_list(struct node_t *top){
    while (top)
    {
        struct node_t *cur = top;
        top = top->next;
        free(cur);      
    }
}

int main() {
  struct node_t *top = read_list(stdin);
  struct node_t *cur = top;

  while (cur) {
    printf("%d ", cur->data);
    cur = cur->next;
  }
  printf("\n");

  delete_list(top);
}