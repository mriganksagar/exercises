
// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:

    ListNode* mergeTwoSortedList(ListNode* list1, ListNode* list2){
        if(list1 == nullptr) return list2;
        else if(list2 == nullptr) return list1;
        ListNode* start, *current;
        if(list1->val <= list2->val){
            current = list1;
            list1 = list1->next;
        }
        else {
            current = list2;
            list2 = list2->next;
        }
        start = current;
        while(list1 != nullptr and list2!= nullptr){
            if(list1->val <= list2->val){
                current->next = list1;
                list1 = list1->next;
            }
            else{
                current->next = list2;
                list2 = list2->next;
            }
            current = current->next;
        }
        if(list1 == nullptr) current->next = list2;
        else if(list2 == nullptr) current->next = list1;
        return start;
    }
    ListNode* helpMergeKList(vector<ListNode*>& lists, int start, int end){
        //if only one list in the range return itself
        if(start == end) return lists[start];
        //else divide and conquer
        int mid = start + (end-start)/2;
        ListNode* leftHalfList = helpMergeKList(lists, start, mid);
        ListNode* rightHalfList = helpMergeKList(lists, mid+1, end);
        return mergeTwoSortedList(leftHalfList, rightHalfList); 
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size() == 0) return nullptr;
        return helpMergeKList(lists, 0, lists.size()-1);
    }
};