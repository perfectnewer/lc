#define MAX(x, y) x > y ? x : y

int recursion(char *s, int start, int stop, int k) {
    int i = 0, max = 0, tmp_id=start;
    char split_char = 0;
    int character_table[26]  = {0};

    if(stop - start < k)    return 0;

    for(i=start; i < stop; ++i) {
        character_table[s[i] - 'a'] += 1;
    }

    for(i=start; i < stop; ++i) {
        if(character_table[s[i] - 'a'] < k) {
            split_char = s[i];
            break;
        }
    }
    if(split_char) {
        for( ; i<stop; ++i) {
            if(s[i] == split_char) {
                max = MAX(max, recursion(s, tmp_id, i, k));
                tmp_id = i + 1;
            }
        }
    } else {
        return stop - start;
    }

    return MAX(max, recursion(s, tmp_id, stop, k));
}

int longestSubstring(char* s, int k) {
    int character_table[26]  = {0};
    int i = 0, length = 0, max=0, tmp_id=0;
    char split_char = 0;
    for(i=0; s[i] != '\0'; ++i) {
        character_table[s[i]-'a'] += 1;
    }
    length = i;

    for(i=0; s[i] != 0; ++i) {
        if(character_table[s[i]-'a'] < k) {
            split_char = s[i];
            break;
        }
    }
    if(split_char) {
        for( ; i<length; ++i) {
            if(s[i] == split_char) {
                max = MAX(max, recursion(s, tmp_id, i, k));
                tmp_id = i + 1;
            }
        }
    } else {
        return length;
    }


    return MAX(max, recursion(s, tmp_id, length, k));
}
