#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct stack {
    void *base;
    unsigned int ele_size;
    unsigned int num_used;
    unsigned int bytes_allocated;
} stack;

void stack_ini(stack *s, unsigned int ele_size) {
    /*stack initialisation:
        Given a stack variable and the size of the basic element, the fuction
        will help you initialise the stack.
        This function should be called before you use a stack variable.
    */
    s->base = NULL;
    s->ele_size = ele_size;
    s->num_used = s->bytes_allocated = 0;
}

void stack_push(stack *s, void * element) {
    /*
    Given a stack variable and the address of the value to push into the stack, the
    function will first check whether there is enough space to hold the value.
    If the stack is full, it will try to reallocate the memory for the stack.
    If there is enough space, the value will be put at the top of the stack.
    */
    unsigned int bytes_used = s->ele_size * s->num_used;
    if(bytes_used == s->bytes_allocated) { //check
        void *temp = s->base;
        s->bytes_allocated = bytes_used ? bytes_used * 2 : s->ele_size; //Stack full, reallocate memory.
        s->base = malloc(s->bytes_allocated);
        assert(s->base);
        for(int i = 0; i < bytes_used; ++i) //Move the stack to new memory space.
            *( (char *)(s->base) + i ) = *( (char *)temp + i );
        free(temp); //Destroy the old space of the stack
    }

    for(int i = 0; i < s->ele_size; ++i) //PUSH
        *( (char *)(s->base) + bytes_used + i) = *( (char *)element + i);
    ++s->num_used;
}

void *stack_pop(stack *s) {
    /*
    Given a stack variable, the function will return the address of the value
    at the top of the stack. Since the memory space of the stack will not be shrunk,
     the top value will not be destroyed and still reachable.
    */
    --s->num_used;
    return ((char *)s->base + s->ele_size * s->num_used );
}

void stack_destroy(stack *s) {
    /*
    Given a stack variable, destroy everything and initialise the stack to be empty.
    */
    free(s->base);
    stack_ini(s, s->ele_size);
}

int main() {
    stack s;
    stack_ini(&s, sizeof(int));
    int temp;
    for(int i = 0; i < 10; ++i) {
        scanf("%d", &temp);
        stack_push(&s, &temp);
    }
    *(int *)(stack_pop(&s)) = 100;
    s.num_used++;
    for(int i = 0; i < 10; ++i) {
        printf("%d ", *(int * )stack_pop(&s));
    }
    stack_destroy(&s);

    return 0;
}
