#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>

void initKmpBaseArray(char *str, int *map, int str_len) {
    int i = 1, j = 0, k = 0;

    memset(map, 0, str_len*sizeof(int));
    for (i=1; i<str_len; i++, j=0)
    {
        for(k=i - map[i-1]; k <= i; ++k) {
            if(str[k] == str[j] || str[k] == '?' || str[j] == '?') {
                map[i] += 1;
                ++j;
            } else {
                map[i] = 0;
                k -= j;
                j = 0;
            }
        }
    }
}

bool isMatch(char *s, char *p) {
    if(*s == '\0' && *p == '\0') return true;

    if(*p == '*') {
        while(*p == '*') ++p;
        if(*p == '\0')
            return true;
        else
            p -= 1;
    }

    int *map = NULL;
    int pattern_len = strlen(p);
    int str_len = strlen(s);
    // calloc failed ignored
    char* *asterisk_loc_map = calloc(pattern_len, sizeof(char *));

    char *tmp = p;
    int map_idx = 1, left_asterisk_amount = 0;
    while(*tmp != '\0') {
        if(*tmp == '*') {
            left_asterisk_amount += 1;
            asterisk_loc_map[map_idx++] = tmp;
        }
        ++tmp;
    }

    tmp = NULL;
    char *base_pattern = NULL;
    int base_pattern_len = 0;
    if(str_len < pattern_len - left_asterisk_amount) {
        goto dismatch;
    }
    // malloc failed ignored
    tmp = malloc((pattern_len+1-left_asterisk_amount)*sizeof(char));

    int match_loc = 0, max_search = 0;

    map_idx = 0;
    if(*p != '*') {
        base_pattern_len = left_asterisk_amount > 0 ? asterisk_loc_map[map_idx+1] - p : pattern_len;
        if(str_len < base_pattern_len) goto dismatch;

        while(*p != '*' && *p != '\0' && *s != '\0' && (*p == *s || *p == '?')) {
            ++p, ++s, --str_len, --pattern_len;
        }

        if(*p != *s && *p != '*') goto dismatch;
    }

    map = calloc(pattern_len-left_asterisk_amount, sizeof(int));
    while(*s != '\0' && *p != '\0') {

        while(*p == '*') {
            ++p, ++map_idx, --pattern_len, --left_asterisk_amount;
        }

        if(*p == '\0' ) goto match;

        if(left_asterisk_amount == 0) {
            s += str_len - pattern_len;
            while(*p != '\0' && *s != '\0' && (*p == *s || *p == '?')) {
                            ++p, ++s, --str_len, --pattern_len;
            }

            if(*s == '\0')
                goto match;
            goto dismatch;
        } else {
            base_pattern_len = asterisk_loc_map[map_idx+1] - p;

            max_search = str_len-(pattern_len-base_pattern_len-left_asterisk_amount);
            if(max_search < base_pattern_len) goto dismatch;


            // calloc failed ignored
            initKmpBaseArray(p, map, base_pattern_len);
            int i = 0, j = 0;
            while(i < max_search && j < base_pattern_len) {
                if(p[j] == s[i] || p[j] == '?') {
                    ++j, ++i;
                } else {
                    // ori_pos = i - j, move j > 0 ? j - map[j] : 1
                    i = i + (j > 0 ? -map[j-1] : 1);
                    j = 0;
                }
            }

            if(j < base_pattern_len) goto dismatch;

            //
            s += i;
            str_len -= i;
            p += base_pattern_len;
            pattern_len -= base_pattern_len;
        }

    }

    if(*s == '\0' && *p == '\0') goto match;

    if(*p == '*') {
        while(*p == '*') ++p;
        if(*p == '\0') goto match;
    }

dismatch:
    free(asterisk_loc_map);
    free(tmp);
    free(map);
    return false;
match:
    free(asterisk_loc_map);
    free(tmp);
    free(map);
    return true;
}


int main(int argc, char **argv) {
    if(argc < 2 || (argc-1) % 2 != 0) {
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
