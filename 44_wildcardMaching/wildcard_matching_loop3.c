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

bool isMatch(char *s, char *p) {

    if(*p == '\0' && *s != '\0') return false;
    if(trailingAsterisk(p)) return true;

    char *fp_s = s, *bp_s = s, *tmp_fp_s = NULL, *tmp_bp_s = NULL ;
    char *fp_p = p, *bp_p = p, *tmp_fp_p = NULL, *tmp_bp_p = NULL ;
    char tmp_c = '\0';

    while(*(bp_s+1) != '\0') ++bp_s;
    while(*(bp_p+1) != '\0') ++bp_p;

    while(fp_s <= bp_s) {

        // forward
        if(*fp_p == '*') {
            while(*fp_p == '*') ++fp_p;

            tmp_fp_p = fp_p;
            tmp_c = *fp_p ;

            // find first match
            while(fp_s <= bp_s && (tmp_c != '?' && tmp_c != *fp_s)) ++fp_s;
            if(fp_s <= bp_s) tmp_fp_s = fp_s;

            // move to dismatch
            while(*fp_p != '*' && fp_s <= bp_s && fp_p <= bp_p && (*fp_s == *fp_p || *fp_p == '?')) {
                ++fp_s, ++fp_p;
            }

            if(fp_s <= bp_s && *fp_p != '*') {
                fp_p = tmp_fp_p - 1;
                fp_s = tmp_fp_s + 1;
            }

        } else if(*fp_p == '?' || *fp_p == *fp_s) {

            // move to dismatch
            while(*fp_p != '*' && fp_s <= bp_s && fp_p <= bp_p && (*fp_s == *fp_p || *fp_p == '?')) {
                ++fp_s, ++fp_p;
            }

        } else {
            return false    ;
        }

        //backward
        if(*bp_p == '*') {
            while(*bp_p == '*') --bp_p;

            tmp_bp_p = bp_p ;
            tmp_c = *bp_p;

            // find first match
            while(fp_s <= bp_s && (tmp_c != '?' && tmp_c != *bp_s)) --bp_s;
            if(fp_s <= bp_s) tmp_bp_s = bp_s;

            // move to dismatch
            while(*bp_p != '*' && fp_s <= bp_s && fp_p <= bp_p && (*bp_s == *bp_p || *bp_p == '?')) {
                --bp_s, --bp_p;
            }

            if(fp_s <= bp_s && *bp_p != '*') {
                bp_p = tmp_bp_p + 1;
                bp_s = tmp_bp_s - 1;
            }

        } else if(*bp_p == '?' || *bp_p == *bp_s) {

            // move to dismatch
            while(*bp_p != '*' && fp_s <= bp_s && fp_p <= bp_p && (*bp_s == *bp_p || *bp_p == '?')) {
                --bp_s, --bp_p;
            }

        } else {
            return false    ;
        }

    }

    while(fp_p <= bp_p) {
        if(*fp_p != '*')
            return false;

        ++fp_p;
    }

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
