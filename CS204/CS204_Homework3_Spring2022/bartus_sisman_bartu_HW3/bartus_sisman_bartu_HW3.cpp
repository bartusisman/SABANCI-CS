#include <iostream>
#include <string>
#include "TwoDLinkedList.h"

using namespace std;

TwoDLinkedList::TwoDLinkedList()
{
    head = NULL;
}

void TwoDLinkedList::add_row_sorted(string s)
{
	node * row_to_be_added = new node(s[0], NULL, NULL); // creates the head
	node *temp = row_to_be_added;
	node* new_node;
	node * prev_colmn;
	for (int i = 1; i < s.length(); i++) // creates the node to be added
	{
		new_node = new node(s[i], NULL, NULL);
		temp->right = new_node;
		temp = temp->right;
	}
	temp = NULL;

	if (head == NULL) // If the matrix is empty add the new row as the first row
	{
		head = row_to_be_added;
		return;
	}

	node *colmn_node = head;

	while (colmn_node != NULL)
	{

		if (s[0] == colmn_node->data) 
		{
			node* temp2;
			if (colmn_node == head)
			{
				temp = head; // temp is old head
				head = row_to_be_added;
				temp2 = head; // temp2 is the new head

				for (int i = 0; i < s.length(); i++)
				{
					temp2->down = temp;
					temp = temp->right;
					temp2 = temp2->right;
				}
				break;
			}
			temp = row_to_be_added;
			temp2 = colmn_node;
			while(temp != NULL)
			{
				prev_colmn->down = temp;
				temp->down = temp2;

				prev_colmn = prev_colmn->right;
				temp = temp->right;
				temp2 = temp2->right;
			}
			break;	
		}

		if (s[0] < head->data) // if the the new row's first letter is bigger than head's letter inserts the new node as head and connects the matrix
		{
			temp = head; // old head
			head = row_to_be_added; // new head
			node*temp2 = head; // copy of new head

			for (int i = 0; i < s.length(); i++)
			{
				temp2->down = temp;
				temp2 = temp2->right;
				temp = temp->right;
			}
			break;
		}

		else if (s[0] > colmn_node->data)
		{
			if (colmn_node->down == NULL)
			{
				for (int i = 0; i < s.length(); i++)
				{
					colmn_node->down = row_to_be_added;
					colmn_node = colmn_node->right;
					row_to_be_added = row_to_be_added->right;
				}
				break;
			}

			else if (s[0] < colmn_node->down->data)
			{
				node* down = colmn_node->down;

				for (int i = 0; i < s.length(); i++)
				{
					colmn_node->down = row_to_be_added;
					row_to_be_added->down = down;

					colmn_node = colmn_node->right;
					down = down->right;
					row_to_be_added = row_to_be_added->right;
				}
				break;
			}
		}
		prev_colmn = colmn_node;
		colmn_node = colmn_node->down;
	}



	
		
}

void TwoDLinkedList::displayFullMatrix()
{
	node* row = head;
	node* colmn = head;
	while (colmn != NULL)
	{
		while (row != NULL)
		{
			cout << row->data;
			row = row->right;
		}
		cout << endl;
		colmn = colmn->down;
		row = colmn;
	}
}

void TwoDLinkedList::Reverse(node* temp)
{
	node* row;
	if (temp == NULL)
	{
		return;
	}
	Reverse(temp->down);

	row = temp;

	while (row!= NULL)
	{
		cout << row->data;
		row = row->right;
	}
	cout << endl;
}

void TwoDLinkedList::displayFullMatrixReversed()
{
	Reverse(head);
}

void TwoDLinkedList::display_rows_starting_with(char c)
{
	node* temp = head;
	node * row;
	while (temp != NULL)
	{
		if (temp->data == c)
		{
			row = temp;

			while (row != NULL)
			{
				cout << row->data;
				row = row->right;
			}
			cout << endl;
		}
		temp = temp->down;
	}
}

void TwoDLinkedList::display_cols_starting_with(char c)
{
	node* temp = head;
	node * colmn;
	while (temp != NULL)
	{
		if (temp->data == c)
		{
			colmn = temp;

			while (colmn != NULL)
			{
				cout << colmn->data << endl;
				colmn = colmn->down;
			}
			cout << endl;
		}
		temp = temp->right;
	}
}

int TwoDLinkedList::delete_rows_starting_with(char c)
{
	int count = 0;
	node* row_head = head;
	node* temp;
	node* temp2;
	node* prev_row_head;
	while (row_head != NULL)
	{
		if (head->data == c)
		{
			count ++;
			temp = head;
			head = head->down;
			while (temp != NULL)
			{
				temp2 = temp->right;
				delete temp;
				temp = temp2;
			}
			row_head = head;
		}

		else if (row_head->data == c)
		{
			count ++;
			temp = row_head;

			while (temp != NULL)
			{
				prev_row_head->down = temp->down;
				prev_row_head = prev_row_head->right;
				temp = temp->right;
			}
			temp2 = row_head;
			temp = temp2;
			while (temp2 != NULL)
			{
				temp = temp2->right;
				delete temp2;
				temp2 = temp;
			}
			row_head = head;
		}
		prev_row_head = row_head;
		if (row_head != NULL)
		{
			row_head = row_head->down;
		}
	}
	return count;

}

int TwoDLinkedList::delete_cols_starting_with(char c)
{
	int count = 0;

	node* colmn_head = head;
	node* temp;
	node* temp2;
	node* prev_colmn_head;
	while (colmn_head != NULL)
	{
		if (head->data == c)
		{
			count ++;
			temp = head;
			head = head->right;
			while (temp != NULL)
			{
				temp2 = temp->down;
				delete temp;
				temp = temp2;
			}
			colmn_head = head;
		}

		else if (colmn_head->data == c)
		{
			count ++;
			temp = colmn_head;

			while (temp != NULL)
			{
				prev_colmn_head->right = temp->right;
				prev_colmn_head = prev_colmn_head->down;
				temp = temp->down;
			}
			temp2 = colmn_head;
			temp = temp2;
			while (temp2 != NULL)
			{
				temp = temp2->down;
				delete temp2;
				temp2 = temp;
			}
			colmn_head = head;
		}
		prev_colmn_head = colmn_head;
		if (colmn_head != NULL)
		{
			colmn_head = colmn_head->right;
		}
	}
	return count;
}

void TwoDLinkedList::clear()
{
	node* temp;
	node* temp2;
	while (head != NULL)
	{
		temp = head;
		head = head->down;

		while (temp != NULL)
		{
			temp2 = temp->right;
			delete temp;
			temp = temp2;
		}
	}
}



