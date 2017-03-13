#include<stdio.h>

int lengthOfLongestSubstring(char* s) {
    int character_table[255];
    int max_length = 0;
    int start_pos = 0;
    int tmp_length = 0;

    if(!*s) return 0;

    for(int i = 0; i < 255; ++i) {
        character_table[i] = -1;
    }

    for(int i = 0, exists_pos=0; s[i] != '\0'; ++i) {
        exists_pos = character_table[s[i]];
        if(exists_pos != -1 && exists_pos >= start_pos) {
            max_length = tmp_length > max_length ? tmp_length : max_length ;
            start_pos = exists_pos + 1;
            tmp_length = i - start_pos;
        }
        tmp_length += 1;
        character_table[s[i]] = i;
    }
    max_length = tmp_length > max_length ? tmp_length : max_length ;
    return max_length;
}
