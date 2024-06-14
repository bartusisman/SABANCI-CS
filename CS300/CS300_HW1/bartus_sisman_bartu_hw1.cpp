// Bartu Sisman 

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <ctime>
#include <string>

using namespace std;

template <class T>
class Stack {
private:
    struct Node // node of the stack
	{
        T data;
        Node* next;
        Node(T d) : data(d), next(nullptr) {}
    };
    
    Node* top; // top element of the stack
    int size; // size of the stack
    
public:
    Stack() : top(nullptr), size(0) {} // constructor

    ~Stack() // destructor
	{
        while (!isEmpty()) 
		{
            pop();
        }
    }
    
    void push(T val) // adds a new element to the top of the stack
	{
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
        size++;
    }
    
    void pop() 
	{
        if (isEmpty()) 
		{
			cout << "Stack is empty" << endl;
            return;
        }

        Node* temp = top;
        top = top->next;
        delete temp;
        size--;
    }
    
    T peek() const 
	{
        if (isEmpty()) 
		{
			cout << "Stack is empty" << endl;
        }

        return top->data;
    }
    
    bool isEmpty() const 
	{
        return size == 0;
    }
    
    int getSize() const 
	{
        return size;
    }
};

struct cell
{
	int x, y; // x and y location of the cell (row and column)
	bool left, right, up, down, visited; // up, down, right and left parts are true if there is a wall exists in those parts. 
										//	Visited variable is true if this cell has been acessed before

	cell(){}
	cell(int column, int row): left(true), right(true), up(true), down(true), visited(false) 
	{
		x = column;
		y = row;
	}
};

vector<cell*> getUnvisitedNeighbors(cell currentCell, vector<vector<cell>>& maze, int row, int column) // return all available cells around the current cell in a vector. vector is empty if there are no available cells
{
    vector<cell*> neighbors;
	// Check the cell that is at the left of the current cell
    if (currentCell.x > 0 && !maze[currentCell.x - 1][currentCell.y].visited) 

	{
        neighbors.push_back(&maze[currentCell.x - 1][currentCell.y]);
    }

	// Check the cell that is at the right of the current cell
    if (currentCell.x < column - 1 && !maze[currentCell.x + 1][currentCell.y].visited) 
	{
        neighbors.push_back(&maze[currentCell.x + 1][currentCell.y]);
    }

	// Check the cell that is above the current cell
    if (currentCell.y < row -1 && !maze[currentCell.x][currentCell.y + 1].visited) 
	{
        neighbors.push_back(&maze[currentCell.x][currentCell.y + 1]);
    }

	// Check the cell that is below the current cell
    if (currentCell.y > 0 && !maze[currentCell.x][currentCell.y - 1].visited) 
	{
        neighbors.push_back(&maze[currentCell.x][currentCell.y - 1]);
    }

    return neighbors;
}

void removeWall(cell &current, cell &next) // removes the wall between current and next cell by figuring each of their positions according to each other
{
    int x = current.x - next.x;
    int y = current.y - next.y;

    if (y == -1) // curent is below the next
	{
        current.up = false;
        next.down = false;
    }
    else if (y == 1) // current is above the next 
	{
        current.down = false;
        next.up = false;
    }
    else if (x == 1) /// current is at the right of next
	{
        current.left = false;
        next.right = false;
    }
    else if (x == -1)  // current is at the left of next
	{
        current.right = false;
        next.left = false;
    }
}

void createMaze(int row, int column, string fileName) //Given amount of rows and columns of a maze generates a random maze of rowxcolumn sized and prints it to the file named "filename"
{
    // Create a 2D array of cells
    vector<vector<cell>> maze(column, vector<cell>(row, cell(0, 0)));

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			maze[j][i].x = j;
			maze[j][i].y = i;
		}
	}

    // Choose a random cell as the starting point
    int startX = 0;
    int startY = 0;

    // Initialize the stack and push the starting cell to it
    Stack<cell*> stack;
    maze[startX][startY].visited = true;
    stack.push(&maze[startX][startY]);

    // Perform a randomized depth-first search
    while (!stack.isEmpty()) 
	{
        // Pop the top cell from the stack
		
        cell* currentCell = stack.peek();

        // Get the neighboring cells of the current cell
        vector<cell*> neighbors = getUnvisitedNeighbors(*currentCell, maze, row, column);

		
        if (!neighbors.empty()) 
		{
            // Choose a random unvisited neighbor
            int randomIndex = rand() % neighbors.size();
            cell* nextCell = neighbors[randomIndex];

            // Remove the wall between the current cell and the next cell
            removeWall(*currentCell, *nextCell);

            // Mark the next cell as visited and push it to the stack
			nextCell->visited=true;
            stack.push(nextCell);
        }
		else
		{
			stack.pop();
		}
    }

    // Write the maze to a file
    ofstream outFile(fileName);
    outFile << row << " " << column << endl;

    for (int i = 0; i < row; i++) 
	{
        for (int j = 0; j < column; j++) 
		{
            cell currentCell = maze[j][i];
            outFile << "x=" << currentCell.x << " y=" << currentCell.y << " l=" << currentCell.left << " r=" << currentCell.right << " u=" << currentCell.up << " d=" << currentCell.down << endl;
        }
    }

    outFile.close();
}

void writeStackToFileRecursively(Stack<cell>& myStack, ofstream& outfile) 
{
    if (myStack.isEmpty()) {
        return;
    }

    cell currentData = myStack.peek();
    myStack.pop();

    writeStackToFileRecursively(myStack, outfile);

	outfile << currentData.x << " " << currentData.y << endl;

    myStack.push(currentData);
}

void writeStackToFile(Stack<cell>& myStack, const string& filename) 
{
    ofstream outfile;
    outfile.open(filename);

    writeStackToFileRecursively(myStack, outfile);

    outfile.close();
}

void path_find(int ID,int x_entry, int y_entry, int x_exit, int y_exit)
{
    ifstream maze_file("maze_" + to_string(ID) + ".txt");
    int row, column;
	string line, filename;

    maze_file >> row >> column;
	vector<vector<cell>> maze(column, vector<cell>(row)); // we will read the spesific file then store the cells into this maze according to correct cordinates
   
    getline(maze_file, line);

    for (int y = 0; y < row; y++) 
	{
        for (int x = 0; x < column; x++) 
		{
            getline(maze_file, line);

            int x_pos, y_pos, left, right, up, down;
            sscanf_s(line.c_str(), "x=%d y=%d l=%d r=%d u=%d d=%d", &x_pos, &y_pos, &left, &right, &up, &down);

            cell temp(x_pos,y_pos);
			temp.left = left;
			temp.right = right;
			temp.up = up;
			temp.down = down;

            maze[x][y] = temp;
        }
    }
	Stack<cell> stack;

	cell current_cell = maze[x_entry][y_entry];
	current_cell.visited = true;
	stack.push(current_cell);

	current_cell = stack.peek();
	// entry point is marked visited and in the stack
	while( !((current_cell.x == x_exit) && (current_cell.y == y_exit)) ) // until we find the exit point
	{
		// if there is no wall and the direction we are trying to go is not out of range then go into that direction
		// if cant go any direction go backwards and check for a direction to go again

		// check if we can go to the right
		if ( (current_cell.x < column - 1) && (!maze[current_cell.x + 1][current_cell.y].visited) && (current_cell.right == 0) )
		{
			maze[current_cell.x + 1][current_cell.y].visited = true;
			stack.push(maze[current_cell.x + 1][current_cell.y]);
			current_cell = stack.peek();
		}
		// check if we can go to the left
		else if ( (current_cell.x > 0) && (!maze[current_cell.x - 1][current_cell.y].visited) && (current_cell.left == 0) )
		{
			maze[current_cell.x - 1][current_cell.y].visited = true;
			stack.push(maze[current_cell.x - 1][current_cell.y]);
			current_cell = stack.peek();
		}
		// check if we can go down
		else if ( (current_cell.y > 0) && (!maze[current_cell.x][current_cell.y - 1].visited) && (current_cell.down == 0) )
		{
			maze[current_cell.x][current_cell.y - 1].visited = true;
			stack.push(maze[current_cell.x][current_cell.y - 1]);
			current_cell = stack.peek();
		}
		// check if we can go up
		else if ( (current_cell.y < row - 1) && (!maze[current_cell.x][current_cell.y + 1].visited) && (current_cell.up == 0) )
		{
			maze[current_cell.x][current_cell.y + 1].visited = true;
			stack.push(maze[current_cell.x][current_cell.y + 1]);
			current_cell = stack.peek();
		}
		else // if cant go anywhere go backwards in the traveled path until we can go somewhere
		{
			stack.pop();
			current_cell = stack.peek();
		}
	}

	filename = "maze_" + to_string(ID) + "_" + to_string(x_entry) + "_" + to_string(y_entry) + "_" + to_string(x_exit) + "_" + to_string(y_exit); // generate a string for the name of the file
	writeStackToFile(stack, filename);
}

int main()
{
	srand(time(nullptr));

	int K, M, N, maze_ID, x_entry, y_entry, x_exit, y_exit;
	string mazefile_name;

	// maze generation part
	cout << "Enter the number of mazes: ";
	cin >> K;
	cout << "Enter the number of rows and columns (M and N): ";
	cin >> M >> N;

	for (int i = 1; i <= K; i++) // generate K amount of mazes with consecutive IDs
	{
		mazefile_name = "maze_" + to_string(i) + ".txt"; 
		createMaze(M, N , mazefile_name);
	}
	cout << "All mazes are generated." << endl;
	cout << endl;

	//path finding part
	cout << "Enter a maze ID between 1 to " << K << " inclusive to find a path: ";
	cin >> maze_ID;

	while (!( (1 <= maze_ID) && (K >= maze_ID) ))
	{
		cout << "Enter a maze ID between 1 to " << K << " inclusive to find a path: ";
		cin >> maze_ID;
	}

	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin >> x_entry >> y_entry;

	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin >> x_exit >> y_exit;

	path_find(maze_ID, x_entry, y_entry, x_exit, y_exit);

    return 0;
}

