void cmp_until_diff(char **s, char **p) {
    while('*' != **p && **s && **p && (**s == **p || '?' == **p)) {
        (*s) += 1;
        (*p) += 1;
    }
}

int isMatch(char* s, char* p) {

    if('\0' == *s) {
        while(*p) {
            if('*' != *p)
                return 0;
            ++p;
        }
        return 1;
    }

    if('?' == *p) {
        return isMatch(++s, ++p);
    } else if('*' == *p) {
        while(*p) {
            if('*' == *p)
                ++p;
            else
                break;
        }
        while(*s) {
            char *p_s=s, *p_p=p;
            cmp_until_diff(&p_s, &p_p);

            if('\0' == *p_p && '\0' == *p_s) {
                return 1;
            }

            if ('*' == *p_p && isMatch(p_s, p_p)) {
                return 1;
            } else {
                ++s;
            }
        }
        return isMatch(s, p);

    } else if(*p == *s) {
        cmp_until_diff(&s, &p);
        return isMatch(s, p);
    }
    return 0;
}
