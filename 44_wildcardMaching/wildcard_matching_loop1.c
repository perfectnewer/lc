#include <stdbool.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

void usage() {
    printf("<string> <pattern>,...\n");
}

size_t getStringSize(const char *pt) {
    size_t size = 0;
    if(pt == NULL) {
        return 0    ;
    }
    while(*pt != '\0') ++size, ++pt;

    return size    ;
}

typedef struct {
    bool empty      ;
    size_t size     ;
    size_t top      ;
    char** container;
} Stack;

void push2Stack(Stack *stack, char* value) {
    size_t STEP = 10 ;
    if(stack->top+1 > stack->size) {
        char* *tp = NULL;
        tp = realloc(stack->container, (stack->size+STEP)*sizeof(char*));
        if(tp == NULL) {
            printf("not enough memory\n") ;
            if(stack->container != NULL) free(stack->container)      ;
            exit(1) ;
        }
        stack->container = tp    ;
        stack->size += STEP      ;
    }

    stack->top += 1      ;
    stack->empty = false ;
    stack->container[stack->top] = value  ;
}

void* popStack(Stack *stack) {
    if(stack->top == 0) {
        stack->empty = true  ;
        return NULL   ;
    }

    void* tmp = stack->container[stack->top--];
    if(stack->top == 0) stack->empty = true;

    return tmp;
}

void* getStackTop(Stack *stack) {
    return stack->container[stack->top]   ;
}

bool trailingAsterisk(char *p) {
    if(p == NULL || *p == '\0') return false;
    while(*p == '*' && *p != '\0') ++p;
    return *p == '\0';
}

bool isMatch(char *s, char *p) {
    size_t string_size, pattern_size  ;
    char *valid_pattern = NULL  ;

    Stack stack_p = {.empty=true, .size=0, .top=0, .container=NULL}   ;
    Stack stack_s = {.empty=true, .size=0, .top=0, .container=NULL}   ;

    if(*s == '\0') {
        if(*p == '\0' || trailingAsterisk(p)) goto pattern_match;
        goto pattern_dismatch;
    }
    if(trailingAsterisk(p)) goto pattern_match;

    string_size = getStringSize(s) ;
    pattern_size = getStringSize(p);
    valid_pattern = (char*)malloc((pattern_size+1)*sizeof(char))    ;
    if(valid_pattern == NULL) {
        printf("not enough memory\n") ;
        exit(0) ;
    }

    unsigned int loc = 0    ;
    char current_char       ;
    char previous_char = ' ' ;
    size_t valid_pattern_size = 0;
    while(loc <= pattern_size) {

        current_char = *(p+loc) ;
        if(!(previous_char == '*' && current_char == '*')) {
            *(valid_pattern+valid_pattern_size) = current_char;
            valid_pattern_size += 1 ;
        }

        previous_char = current_char    ;
        loc += 1    ;
    }

    p = valid_pattern;

    char* addr_end_s = s + string_size;
    char* addr_end_p = p + valid_pattern_size;

    while(*s != '\0') {

        if(*p == '*') {
            char *tmp = p++;

            while(*s != '\0' && (*p != '?' && *p != *s) ) ++s;

            if((addr_end_s-s) < (addr_end_p-p)/2) goto pattern_dismatch;

            if(*s != '\0') {
                push2Stack(&stack_s, ++s);
                push2Stack(&stack_p, tmp);
                ++p;
            }
        } else if(*p == '?' || *p == *s) {
            ++p;
            ++s;
        } else if(!stack_p.empty) {
            p = popStack(&stack_p);
            s = popStack(&stack_s);
        } else {
            goto pattern_dismatch;
        }

    }

    if(*s == '\0') {
        if(*p == '\0' || trailingAsterisk(p)) goto pattern_match;
        goto pattern_dismatch;
    }

pattern_dismatch:
    if(valid_pattern != NULL) free(valid_pattern) ;
    if(stack_p.container != NULL) free(stack_p.container);
    if(stack_s.container != NULL) free(stack_s.container);
    return false;
pattern_match:
    if(valid_pattern != NULL) free(valid_pattern) ;
    if(stack_p.container != NULL) free(stack_p.container);
    if(stack_s.container != NULL) free(stack_s.container);
    return true;
}

int main(int argc, char **argv) {
    if(argc < 2 || (argc-1) % 2 != 0) {
        usage() ;
        exit(0) ;
    }

    int i = 1   ;
    char *s=NULL, *p=NULL   ;
    char *result=NULL;
    while(i < argc) {
        s = *(argv+i), p = *(argv+i+1) ;
        printf("matching %s in %s\n", s, p) ;

        if(isMatch(s, p)) {
            result="match"  ;
        } else {
            result="dismatch"   ;
        }
        printf("\t\t:%s\n", result) ;

        i += 2  ;
    }
    return 0;
}
