#include <iostream>
#include <string>
#include <stdexcept>
#include <time.h>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution
{
public:
    int fromLastSum = 0;

    /// @brief Prints the ListNode until it finds nullptr.
    /// @param list The lsit we want to print.
    void printList(ListNode *list)
    {
        while (list->next != nullptr)
        {
            std::cout << list->val << " ";
            list = list->next;
        }
        std::cout << list->val << std::endl;
    }

    /// @brief This is the solving method for when the digits are in a normal order
    /// thus the first first digit is the MOST significant one.
    /// @param l1 First ListNode array.
    /// @param l2 Second ListNode array.
    /// @return The sum of the ListNodes.
    ListNode *recursiveGetListNodeValues(ListNode *l1, ListNode *l2)
    {
        ListNode *result;
        if (l1->next != nullptr && l2->next != nullptr)
        {
            result = new ListNode(0, recursiveGetListNodeValues(l1->next, l2->next));
        }
        else
        {
            result = new ListNode();
        }
        result->val = l1->val + l2->val + fromLastSum;
        fromLastSum = result->val / 10;
        result->val = result->val % 10;
        return result;
    }

    ListNode *addTwoNumbersWithDigitsInCorrectorder(ListNode *l1, ListNode *l2)
    {
        int numberOfDigits1 = 0;
        int numberOfDigits2 = 0;
        ListNode *dummy = l1;
        while (dummy->next != nullptr)
        {
            dummy = dummy->next;
            numberOfDigits1++;
        }
        dummy = l2;

        while (dummy->next != nullptr)
        {
            dummy = dummy->next;
            numberOfDigits2++;
        }

        if (numberOfDigits1 - numberOfDigits2 > 0)
        {
            ListNode *equalizerArray = new ListNode[numberOfDigits1 - numberOfDigits2];
            for (int i = 0; i < numberOfDigits1 - numberOfDigits2 - 1; i++)
            {
                equalizerArray[i].next = &equalizerArray[i + 1];
                equalizerArray[i].val = 0;
            }
            equalizerArray[numberOfDigits1 - numberOfDigits2 - 1].val = 0;
            equalizerArray[numberOfDigits1 - numberOfDigits2 - 1].next = l2;
            dummy = recursiveGetListNodeValues(l1, equalizerArray);
        }
        else if (numberOfDigits2 - numberOfDigits1 > 0)
        {
            ListNode *equalizerArray = new ListNode[numberOfDigits2 - numberOfDigits1];
            for (int i = 0; i < numberOfDigits2 - numberOfDigits1 - 1; i++)
            {
                equalizerArray[i].next = &equalizerArray[i + 1];
            }
            equalizerArray[numberOfDigits2 - numberOfDigits1 - 1].val = 0;
            equalizerArray[numberOfDigits2 - numberOfDigits1 - 1].next = l1;
            dummy = recursiveGetListNodeValues(equalizerArray, l2);
        }
        else
        {
            dummy = recursiveGetListNodeValues(l1, l2);
        }
        if (fromLastSum != 0)
        {

            ListNode *result = new ListNode(fromLastSum, dummy);
            return result;
        }
        return dummy;
    }
    /// @brief This is the solving method for when the digits are in a reverse order
    /// thus the first first digit is the LEAST significant one.
    /// @param l1 First ListNode array.
    /// @param l2 Second ListNode array.
    /// @return The sum of the ListNodes.
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        int overshoot = 0;
        ListNode final;
        ListNode *realResult = &final;
        ListNode *result;
        do
        {
            result = new ListNode( overshoot);
             if(l1!=nullptr){
                result->val+=l1->val;
                l1 = l1->next;                
            }
            if(l2!=nullptr){
                result->val+=l2->val;
                l2 = l2->next;                
            }
            overshoot = result->val / 10;
            result->val = result->val % 10;
            realResult->next = result;
            realResult = realResult->next;           
        } while (l1 != nullptr || l2 != nullptr);
      
        if (overshoot != 0)
        {
            result = new ListNode(overshoot);
            realResult->next = result;
            realResult = realResult->next;
        }

        return final.next;
    }
};

int main(int argc, char const *argv[])
{
    std::srand(time(0));
    uint elsInL1 = 5;
    uint elsInL2 = 4;
    ListNode *l1 = new ListNode[elsInL1 + 1];
    ListNode *l2 = new ListNode[elsInL2 + 1];
    for (int i = 0; i < elsInL1; i++)
    {
        l1[i].val = std::rand() & 1 + 2 + 4;
        l1[i].next = &l1[i + 1];
    }
    l1[elsInL1].val = std::rand() & 1 + 2 + 4;
    for (int i = 0; i < elsInL2; i++)
    {
        l2[i].val = std::rand() & 1 + 2 + 4;
        l2[i].next = &l2[i + 1];
    }
    l2[elsInL2].val = std::rand() & 1 + 2 + 4;
    Solution sol;
    sol.printList(l1);
    sol.printList(l2);
    sol.printList(sol.addTwoNumbers(l1, l2));
    return 0;
}