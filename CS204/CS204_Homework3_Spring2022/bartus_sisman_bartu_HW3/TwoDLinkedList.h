#ifndef TwoDLinkedList_h
#define TwoDLinkedList_h

#include <string>
#include <iostream>

using namespace std;

struct node
{
    char data;
    node *right;
    node *down;
    
    node(char c, node *r, node *d)
    {
        data = c;
        right = r;
        down = d;
    }
    
};

class TwoDLinkedList
{
private:
    node* head;
    
public:
    TwoDLinkedList();
    void add_row_sorted(string s); 
	void displayFullMatrix();
	void Reverse(node* temp);
	void displayFullMatrixReversed();
	void display_rows_starting_with(char c);
	void display_cols_starting_with(char c);
	int delete_rows_starting_with(char c);
	int delete_cols_starting_with(char c);
	void clear();
};

#endif /* TwoDLinkedList_h */
