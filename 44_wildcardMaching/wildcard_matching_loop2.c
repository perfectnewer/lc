#include <stdbool.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

void usage() {
    printf("<string> <pattern>,...\n");
}

bool trailingAsterisk(char *p) {
    while(*p == '*' && *p != '\0') ++p;
    return *p == '\0';
}

void moveToDismatch(char **s, char **p) {
    while('*'!=**p && **s && **p && (**s==**p || '?'==**p)) ++(*s), ++(*p);
}

void moveToMatch(char **s, char p) {
    while(**s != '\0' && (p != '?' && p != **s) ) ++(*s);
}

bool isMatch(char *s, char *p) {

    if(*p == '\0' && *s != '\0') return false;
    if(trailingAsterisk(p)) return true;

    while(*s != '\0') {

        if(*p == '*') {
            while(*p == '*') ++p    ;

            char *tmp_p = p ;
            char *tmp_s = s ;

            moveToMatch(&s, *p) ;
            if(*s != '\0') tmp_s = s;

            moveToDismatch(&s, &p);

            if(*s != '\0' && *p != '*') { p = tmp_p - 1, s = tmp_s + 1; }

        } else if(*p == '?' || *p == *s) {

            moveToDismatch(&s, &p);

            if(*s != '\0' && *p == '\0') return false;

            if(*s != '\0' && *p != '*')  return false;

        } else {
            return false    ;
        }
    }

    if(*p == '\0' || trailingAsterisk(p))
        return true;

    return false;
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
