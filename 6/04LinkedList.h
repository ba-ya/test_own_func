#ifndef _4LINKEDLIST_H
#define _4LINKEDLIST_H

#include "00solution.h"

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

namespace LinkedList_Reverse {
// 206反转链表
ListNode* reverseList(ListNode* head) {
    ListNode *pre = nullptr;
    ListNode *cur = head;
    while (cur) {
        ListNode *next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    return pre;
}

// 92反转链表2
ListNode* reverseBetween(ListNode* head, int left, int right) {
    // ListNode *pre =
}
}

namespace LinkedList_QuickNSlow {

}

namespace LinkedList_Delete {

}

#endif // _4LINKEDLIST_H
