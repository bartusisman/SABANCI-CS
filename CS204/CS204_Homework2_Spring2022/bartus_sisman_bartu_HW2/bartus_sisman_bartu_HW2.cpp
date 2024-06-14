#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct node
{
    node (char ch_param,node* next_param) // constructor
    {
        ch = ch_param;
        next = next_param;
    }
    
    char ch;
    node * next;
};

node* CreateLinkedList(ifstream & in)
{
    char ch;
    
    node* head;
    node* curr;
    node* temp;
    
    in >> ch;
    
    head = new node(ch, NULL);
    curr = head;
    while (in >> ch)
    {
        temp = new node(ch, NULL);
        curr->next = temp;
        curr = temp;
    }
    return head;
}  // takes input from the file transfers those inputs into nods and then connects them to make a linked list

void FileOperations(node* & node_1, node* & node_2)
{
    string filename;
    ifstream in;
    
    do {
        cout << "Please enter the file 1 name: ";
        cin >> filename;
        in.open(filename);
        }
    while (in.fail());
    
    node_1 = CreateLinkedList(in);
    in.seekg(0);
    in.close();
    
    ifstream in2;
    do {
        cout << "Please enter the file 2 name: ";
        cin >> filename;
        in.open(filename);
        }
    while (in.fail());
    node_2 = CreateLinkedList(in);
}

void PrintList(node* head)
{
    while (head != NULL)
    {
        cout << head->ch;
        head = head->next;
    }
}

void ContentsOfLists(node* node_1, node* node_2)
{
    cout << "List1: ";
    PrintList(node_1);
    cout << endl;
    
    cout << "List2: ";
    PrintList(node_2);
    cout << endl;
}

int similarity_check(node* node_1, node* node_2)
{
    int count = 0;

    while ((node_1 != NULL) && (node_2 != NULL))
    {
        if (node_1->ch == node_2->ch)
        {
            count ++;
        }
        node_1 = node_1->next;
        node_2 = node_2-> next;
    }
    return count;
}

bool Insert(node* & head, char &ch, char &loc)
{
	node* temp = head;
	node* new_node;

	if (temp == NULL)
	{
		head = new node(ch, head);
		return false;
	}

	while (temp != NULL)
	{
		if (temp->ch == loc)
		{
			new_node = new node(ch, temp->next);
			temp->next = new_node;
			return true;
		}
		temp = temp->next;
	}

	head = new node(ch, head);
	return false;

}

bool Delete(node* & head, char ch)
{
	node* curr = head;
	node* temp = curr;
	if (head == NULL)
	{
		return false;
	}
	while (curr->ch != ch)
	{
		if (curr->next == NULL)
		{
			return false;
		}
		temp = curr;
		curr = curr->next;
	}

	if (curr == head)
	{
		head = head->next;
		delete curr;
		return true;
	}
	temp->next = curr->next;
	delete curr;
	return true;
}

void ClearLinkedList(node* &head)
   {
	   node * curr = head;
	   while (head != NULL)
	   {
		   curr = curr->next;
		   delete head;
		   head = curr;
	   }
   }

void Command_Menu(node* & node_1, node*  & node_2)
{
    string command;
    char inp1, inp2;
    
    cout << "Enter a command and its corresponding argument(s), if any: ";
    cin >> command;

        if (command == "sim")
        {
			cout << "Displaying the contents of the two lists:" << endl;
			ContentsOfLists(node_1, node_2);
			cout << "There is/are " << similarity_check(node_1, node_2) << " letter(s) matched in the same positions in both lists." << endl << endl;
            Command_Menu(node_1, node_2);
        }
        
        else if (command == "insert1")
        {
            cin >> inp1 >> inp2;

			if (isupper(inp1) || isupper(inp2))
			{
				cout << "Invalid arguments." << endl << endl;
				Command_Menu(node_1, node_2);
			}
			cout << "Inserting " << inp1 << " after " << inp2 << " in List1." << endl;
			if (!(Insert(node_1,inp1, inp2)))
			{
				cout << "The node with " << inp2 << " value does not exist. Therefore, Inserting " << inp1 << " at the beginning of the list." << endl;
			}
			else
			{
				cout << "The node with " << inp1 << " has been inserted after the first occurrence of a node with " << inp2 << " value." << endl;
			}
			cout << "The current content of List1 is: ";
			PrintList(node_1);

			cout << endl << endl;
            Command_Menu(node_1, node_2);
            
        }
        
        else if (command == "insert2")
        {
            cin >> inp1 >> inp2;

			if (isupper(inp1) || isupper(inp2))
			{
				cout << "Invalid arguments." << endl << endl;
				Command_Menu(node_1, node_2);
			}
			cout << "Inserting " << inp1 << " after " << inp2 << " in List2." << endl;
			if (!(Insert(node_2,inp1, inp2)))
			{
				cout << "The node with " << inp2 << " value does not exist. Therefore, Inserting " << inp1 << " at the beginning of the list." << endl;
			}
			else
			{
				cout << "The node with " << inp1 << " has been inserted after the first occurrence of a node with " << inp2 << " value." << endl;
			}
			cout << "The current content of List2 is: ";
			PrintList(node_2);

			cout << endl << endl;
            Command_Menu(node_1, node_2);
        }
        
        else if (command == "del1")
        {
            cin >> inp1;

			if (isupper(inp1))
			{
				cout << "Invalid arguments." << endl << endl;
				Command_Menu(node_1, node_2);
			}

			if (!(Delete(node_1, inp1)))
			{
				cout << "No deletion as the value " << inp1 << " was not found in the list" << endl << endl;
				Command_Menu(node_1, node_2);
			}
			while (Delete(node_1, inp1))
			{
				Delete(node_1, inp1);
			}

			cout << "Deleting all occurrences of "<< inp1 <<" in List1." << endl;
			cout << "The current content of List1 is: ";
			PrintList(node_1);


			cout << endl << endl;
            Command_Menu(node_1, node_2);
        }
        
        else if (command == "del2")
        {
            cin >> inp1;

			if (isupper(inp1))
			{
				cout << "Invalid arguments." << endl << endl;
				Command_Menu(node_1, node_2);
			}

			if (!(Delete(node_2, inp1)))
			{
				cout << "No deletion as the value " << inp1 << " was not found in the list" << endl << endl;
				Command_Menu(node_1, node_2);
			}
			while (Delete(node_2, inp1))
			{
				Delete(node_2, inp1);
			}

			cout << "Deleting all occurrences of "<< inp1 <<" in List2." << endl;
			cout << "The current content of List2 is: ";
			PrintList(node_2);

			cout << endl << endl;
            Command_Menu(node_1, node_2);
        }

        else if (command == "exit")
        {
			ClearLinkedList(node_1);
			ClearLinkedList(node_2);

			cout << "Clearing the two lists and saying Goodbye!" << endl;
            exit(0);
        }

        else
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            cout << "Invalid command." << endl << endl;
            Command_Menu(node_1, node_2);
   }

int main()
{
	node* node_1;
	node* node_2;
    FileOperations(node_1, node_2);
    
    ContentsOfLists(node_1, node_2);
	cout << endl;
    
    Command_Menu(node_1, node_2);
}
