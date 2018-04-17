#include <iostream>
#include <string>
using namespace std;

class GiftList;
class ListNode
{
private:
	int price;
	string gift;
	ListNode *next;
public:
	ListNode(string gift, int price) : price(price), gift(gift), next(0) {};
	friend class GiftList;
};

class GiftList
{
private:
	ListNode * first;
public:
	GiftList() : first(0) {};
	void InsertBack(string gift, int price);
	void InsertAfter(string gift, int price, int priceToInsertAfter);
	void Delete(int price);
	void Reverse();
	void ShowList();
	bool IsEmpty()
	{
		if (first == 0)
			return true;
		else
			return false;
	}
};
int main()
{
	string function;
	GiftList giftList;
	while (cin >> function)
	{
		string gift;
		int price, priceToInsertAfter;
		if (function == "InsertBack")
		{
			cin >> gift; cin >> price;
			giftList.InsertBack(gift, price);
		}
		else if (function == "InsertAfter")
		{
			cin >> gift; cin >> price; cin >> priceToInsertAfter;
			giftList.InsertAfter(gift, price, priceToInsertAfter);
		}
		else if (function == "Delete")
		{
			cin >> price;
			giftList.Delete(price);
		}
		else if (function == "Reverse")
			giftList.Reverse();
		else if (function == "End")
			break;
	}
	if (giftList.IsEmpty())
		cout << "Empty" << endl;
	else
	{
		cout << "List" << endl;
		giftList.ShowList();
	}
	return 0;
}
void GiftList::InsertBack(string gift, int price)
{
	ListNode *newNode = new ListNode(gift, price);
	ListNode *current = first;
	if (first == 0) //¡@If list is empty, add the node.
	{
		first = newNode;
		return;
	}
	else // current !=0
	{
		while (current->price != price) // searching for the same price
		{
			if (current->next == 0)
				break;
			current = current->next;
		}
		if (current->price != price) // If there is no the same price, add the node.
		{
			current = first;
			while (current->next != 0)
				current = current->next;
			current->next = newNode;
		}
	}
}
void GiftList::InsertAfter(string gift, int price, int priceToInsertAfter)
{
	ListNode *newNode = new ListNode(gift, price);
	ListNode *current = first;
	ListNode *tail = 0;
	if (first != 0)// check if it has at least one node
	{
		if (first->next != 0)// If it has at least two nodes
		{
			while (current->price != price)
			{
				if (current->next == 0)
					break;
				current = current->next;
			}
			if (current->price != price)
			{
				current = first;
				while (current->price != priceToInsertAfter)
				{
					current = current->next;
					if (current->next == 0)
						break;
				}
				if (current->price == priceToInsertAfter)
				{
					if (current->next == 0)
						current->next = newNode;
					else
					{
						tail = current->next;
						current->next = newNode;
						newNode->next = tail;
					}
				}
			}
		}
		else // first->next == 0 (one node)
		{
			if (current->price == priceToInsertAfter && current->price != price)
				current->next = newNode;
		}
	}
}
void GiftList::Delete(int price)
{
	ListNode *current = first;
	ListNode *tail = 0;
	if (first != 0) // check if it has at least one node
	{
		if (current->price != price)
		{
			if (current->next != 0) // If it has at least two nodes else do nothing
			{
				while (current->next->price != price)
				{
					current = current->next;
					if (current->next != 0)
					{
						if (current->next->next == 0)
							break;
					}
					else break;
				}
				if (current->next != 0)
				{
					if (current->next->price == price)
					{
						if (current->next->next == 0)
						{
							delete current->next;
							current->next = 0;
						}
						else
						{
							tail = current->next->next;
							delete current->next;
							current->next = 0;
							current->next = tail;
						}
					}
				}
			}
		}
		else if (current->price == price)
		{
			first = current->next;
			delete current;
			current = 0;
		}
	}
}
void GiftList::Reverse()
{
	ListNode *previous = 0; ListNode *current = first; 
	if (first == 0)
		return;
	else if (first != 0 && first->next == 0)
		return;	
	ListNode *preceeding = first->next;
	while (preceeding != 0)
	{
		current->next = previous;
		previous = current;
		current = preceeding;
		preceeding = preceeding->next;
	}
	current->next = previous;
	first = current;
}
void GiftList::ShowList()
{
	ListNode *current = first;
	while (current->next != 0)
	{
		if (current->next != 0)
			cout << "(" << current->gift << "," << current->price << ")->";
		current = current->next;
	}
	cout << "(" << current->gift << "," << current->price << ")" << endl;
}
