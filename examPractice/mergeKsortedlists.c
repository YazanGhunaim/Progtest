/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode * mergeSort(struct ListNode *l1, struct ListNode * l2)
{
    if(!l1 && !l2) return NULL;
    if(!l1) return l2;
    if(!l2) return l1;

    struct ListNode * newList = (struct ListNode *)malloc(sizeof(*newList));
    struct ListNode * dummy = newList;

    while(l1 && l2)
    {
        if(l1 -> val < l2 -> val)
        {
            dummy -> next = l1;
            l1 = l1 -> next;
        }
        else
        {
        dummy -> next = l2;
        l2 = l2 -> next;
        }
        dummy = dummy -> next;
    }

    if(l1) dummy -> next = l1;
    if(l2) dummy -> next = l2;

    return newList -> next;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){
    if(listsSize == 0) return NULL;
    if(listsSize == 1) return lists[0];

    struct ListNode * result = mergeSort(lists[0], lists[1]);
    for(int i = 2; i < listsSize; ++i)
        result = mergeSort(result,lists[i]);

    return result;
}
