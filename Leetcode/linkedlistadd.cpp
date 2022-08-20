#include <iostream>
#include <cmath>
#include <string>

using namespace std;

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
void push (ListNode** head, int new_val)
{   
    //Create a new node
    ListNode* newNode = new ListNode();
    newNode->val = new_val;
    
    //Set head as the next node of new node
    //Let the newNode be the head 
    newNode->next = (*head);
    *head = newNode;
}

void printList(ListNode *node) 
{ 
    while (node != NULL) 
    { 
        cout<<node->val << " "; 
        node = node->next; 
    } 
} 


class Solution {
public:
    void addTwoNumbers(ListNode* l1, ListNode* l2) {

        //convert from int to string
        string n1;
        string n2;
        while(l1 != NULL)
        {   
            string x = to_string(l1->val);
            n1.insert(0, x);
            l1 = l1->next;
        }

        while(l2 != NULL)
        {
            string x = to_string(l2->val);
            n2.insert(0, x);
            l2 = l2->next;
        }

        
        ListNode *sumnode = NULL;

        int s1 = n1.length() - 1;
        int s2 = n2.length() - 1;
        int char1;
        int char2;
        if (s1 >= s2)
        {
            char1 = s1;
            char2 = s2;

        }
        else 
        {
            char1 = s2;
            char2 = s1;
        }

        int extra = 0;
        //While there are still number to add
        while (char2 >= 0)
        {
            int a = n1[s1] - '0';
            int b = n2[s2] - '0';
            int added = a+b+extra;
            string sum = to_string(added);
            //cout << sum;
            extra = 0;
            if (sum.length() > 1)
            {
                extra = sum[0] - '0';
                int x = sum[1] - '0';
                //cout << x;
                //Create a new node
                ListNode* newNode = new ListNode();
                newNode->val = x;
                newNode->next = NULL;
                
                if(sumnode == NULL)
                {
                    sumnode = newNode;
                }
                else 
                {
                    ListNode *temp = sumnode;
                    while (temp->next != NULL)
                    {
                        temp = temp->next;  
                    }
                    temp->next = newNode;
                }
            }
            else
            {
                
                int x = sum[0] - '0';
                //cout << x;
                //Create a new node
                ListNode* newNode = new ListNode();
                newNode->val = x;
                newNode->next = NULL;
    
                if(sumnode == NULL)
                {
                    sumnode = newNode;
                }
                else 
                {
                    ListNode *temp = sumnode;
                    while (temp->next != NULL)
                    {
                        temp = temp->next;  
                    }
                    temp->next = newNode;
                }
                
            }
            char1--;
            char2--;
            s1--;
            s2--;
        }
        //printList(sumnode);
        //Add the remaining
        while ((char1) >= 0)
        {
            int a;
            if (s1 >= s2)
            {
                a = (n1[char1] - '0') + extra;
            }
            else 
            {
                a = (n2[char1] - '0') + extra;
            }
            string sum = to_string(a);
            extra = 0;

            if (sum.length() > 1)
            {
                extra = sum[0] - '0';
                int x = sum[1] - '0';
                //cout << x;
                //Create a new node
                ListNode* newNode = new ListNode();
                newNode->val = x;
                newNode->next = NULL;
                
                if(sumnode == NULL)
                {
                    sumnode = newNode;
                }
                else 
                {
                    ListNode *temp = sumnode;
                    while (temp->next != NULL)
                    {
                        temp = temp->next;  
                    }
                    temp->next = newNode;
                }
            }
            else
            {
                
                int x = sum[0] - '0';
                //cout << x;
                //Create a new node
                ListNode* newNode = new ListNode();
                newNode->val = x;
                newNode->next = NULL;
    
                if(sumnode == NULL)
                {
                    sumnode = newNode;
                }
                else 
                {
                    ListNode *temp = sumnode;
                    while (temp->next != NULL)
                    {
                        temp = temp->next;  
                    }
                    temp->next = newNode;
                }
                
            }
            char1--;
        }
        
        if (extra != 0)
        {
            ListNode* newNode = new ListNode();
            newNode->val = extra;
            newNode->next = NULL;
            ListNode *temp = sumnode;
            while (temp->next != NULL)
            {
                temp = temp->next;  
            }
            temp->next = newNode;
        }
        printList(sumnode);
    }
};


int main()
{
    ListNode *l1 = NULL;
    ListNode *l2 = NULL;
    
    push(&l1, 9);
    push(&l1, 4);
    push(&l1, 6);
    push(&l1, 5);
    
    push(&l2, 9);
    push(&l2, 4);
    push(&l2, 2);
    //printList(l1);
    Solution s;
    s.addTwoNumbers(l1, l2);
    
    return 0;
}
