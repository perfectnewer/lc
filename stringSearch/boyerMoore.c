#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ANSI 256
#define max(x,y) ((x) > (y) ? (x) : (y))

void initialBadCharTable(int *table, char *pattern, int pattern_size);
void initialReverseKmpTable(int *table, char *pattern, int pattern_size);
void initialGoodSuffixTable(int *table, char *pattern, int pattern_size);
int mbSearch(char *string, int str_len, char *pattern, int pat_len);

int main(int argc, char **argv) {
    int *table = NULL;
    int string_len = 0, pattern_len = 0;
    char *string = NULL, *pattern = NULL, *expand=NULL;
    int i = 0, idx = -1;

    if(argc < 2 || argc % 2 == 0) {
        printf("string, pattern ......\n");
        exit(0);
    }
    while(argc > 1) {
        string = argv[argc-2];
        pattern = argv[argc-1];
        string_len = strlen(string);
        pattern_len = strlen(pattern);
        idx = mbSearch(string, string_len, pattern, pattern_len);
        if(idx != -1) {
            expand = malloc((idx+1)*sizeof(char));
            memset(expand, ' ', idx);
            expand[idx] = '\0';
            printf("%s\n", string);
            printf("%s%s\n", expand, pattern);
            free(expand);
        }
        argc -= 2;
    }
}

void initialBadCharTable(int *table, char *pattern, int pattern_size) {
    for(int i = 0; i < pattern_size; ++i) {
        table[pattern[i]] = pattern_size - 1 - i;
    }
}

void initialReverseKmpTable(int *table, char *pattern, int pattern_size) {
    int suffix_long = 0;
    int cmp_idx = pattern_size-2;
    table[pattern_size-1] = 1;
    while(cmp_idx >= 0) {
        if(pattern[cmp_idx] == pattern[pattern_size-1-suffix_long]) {
            suffix_long += 1;
            table[cmp_idx] = suffix_long;
            cmp_idx -= 1;
        } else {
            if(suffix_long != 0) {
                // suffix_long =  table[suffix_long-1];
                suffix_long -= 0;
            } else {
                cmp_idx -= 1;
            }
        }
    }
}

int isPrefix(char *pattern, int pattern_size, int pos) {
    int i = 0;
    while(pos < pattern_size && pattern[i] == pattern[pos])  ++i, ++pos;
    return pos==pattern_size;
}

void initialGoodSuffixTable(int *table, char *pattern, int pattern_size) {
    // longsetest prefix idx
    int i = 0, j = 0;
}


int bmSearch(char *string, int str_len, char *pattern, int pat_len) {
    int *gs_table = NULL, *bc_table = NULL;


    bc_table = malloc(ANSI*sizeof(int));
    for(int i = 0; i<ANSI; ++i) bc_table[i] = pat_len;

    gs_table = malloc(pat_len*sizeof(int));

    initialBadCharTable(bc_table, pattern, pat_len) ;
    initialGoodSuffixTable(gs_table, pattern, pat_len);

    int i = pat_len - 1, p = pat_len - 1;
    while( i<str_len && p >= 0 ) {
        if (string[i] == pattern[p]) {
            --p;
            --i;
        } else {
            i += max(pat_len-p, bc_table[string[i]]);
            p = pat_len - 1;
        }
    }

    free(gs_table);
    return p == -1? i+1 : -1;
}
