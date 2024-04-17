
//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:

    pair<ListNode*, ListNode*> reversePart(ListNode *head, int k){
        ListNode *nextHead = head;
        int count = 0;
        while(count < k){
            if(nextHead == nullptr){
                return {head, nullptr};
            }
            count++;
            nextHead = nextHead->next;
        }
        ListNode *previous = nextHead;
        ListNode *current = head;
        while(current!=nextHead){
            ListNode *next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        return {previous, nextHead};
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *fakeStart = new ListNode();
        ListNode *prevChunk = fakeStart;
        ListNode *currentChunk = head;
        while(true){
            auto p = reversePart(currentChunk, k);
            prevChunk->next = p.first;
            if(p.second == nullptr){
                break;
            }
            prevChunk = currentChunk;
            currentChunk = p.second;
        } 
        return fakeStart->next;
    }
};