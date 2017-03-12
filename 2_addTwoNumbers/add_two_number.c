/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode *result = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode *tmp = result;
    int p = 0;

    for(; l1 && l2 ; l1=l1->next, l2=l2->next) {
        tmp->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        tmp = tmp->next;

        tmp->val = l1->val + l2->val + p;
        if(tmp->val > 9) {
            tmp->val = tmp->val - 10;
            p = 1;
        } else {
            p = 0;
        }
    }

    l1 = l1 != NULL ? l1 : l2;
    for(; l1 ; l1 = l1->next) {
        tmp->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        tmp = tmp->next;
        tmp->val = l1->val + p;
        if(tmp->val > 9) {
            tmp->val = tmp->val - 10;
            p = 1;
        } else {
            p = 0;
        }
    }

    if(p) {
        tmp->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        tmp = tmp->next;
        tmp->val = p;
    }
    tmp->next = NULL;
    tmp = result;
    result = result->next;
    free(tmp);

    return result;
}
