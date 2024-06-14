# SABANCI-CS

These are almost all Sabanci CS courses I took and their corresponding projects.

## CS204: Object Oriented Programming

Basic C++ projects that mainly focus on the object-oriented features of C++, maximizing the utilities of LinkedLists, pointers, dynamic linking, and implementing some complex algorithms.

## CS210: Introduction to Data Science

### Project Overview
This course involved projects that applied data science techniques to analyze and predict economic and market trends. The primary focus was on exploring relationships between various economic indicators and stock market prices using machine learning models.

### Projects

#### 1. Stock Market vs. Mental Health (2019-2021)
- **Objective**: To analyze the relationship between crude oil prices and public mental health.
- **Summary**: This project examined how fluctuations in crude oil prices impacted mental health metrics. Data visualization techniques such as histograms and scatter plots were used to highlight trends and correlations between these variables.
- **Key Findings**: 
  - Stability in oil prices generally corresponded with economic predictability, while broader mental health metrics indicated more variability and external influences.
  - The scatter plot of crude oil prices versus mentally unhealthy days suggested complex interactions not solely explained by oil prices.

#### 2. Natural Gas Prices and S&P 500 Prediction
- **Objective**: To predict changes in the S&P 500 index based on natural gas prices and GDP growth rates.
- **Summary**: This project employed machine learning models to predict S&P 500 price changes using natural gas price changes and GDP growth as predictors.
  - **Models Used**: Random Forest Regressor and Support Vector Regressor (SVR).
  - **Data Preparation**: Cleaned and merged datasets from stock market data (2019-2024) and world GDP growth data (1980-2024), focusing on relevant years and metrics.
  - **Key Findings**: 
    - The Random Forest Regressor performed slightly better than the SVR but neither model showed high accuracy (both had negative R² values).
    - The analysis indicated that natural gas prices alone are not strong predictors of S&P 500 prices, suggesting the influence of other economic factors.
- **Code Highlights**:
  ```python
  # Example from main.py
  # Train a linear regression model to predict S&P 500 prices based on natural gas prices
  from sklearn.linear_model import LinearRegression
  
  model = LinearRegression()
  model.fit(X_train, y_train)
  y_pred = model.predict(X_test)
  
  print(f"Mean Squared Error: {mean_squared_error(y_test, y_pred)}")
  ```

  ```python
  # Example from ML_Models.py
  # Train and evaluate Random Forest and SVR models
  from sklearn.ensemble import RandomForestRegressor
  from sklearn.svm import SVR
  
  rf = RandomForestRegressor(n_estimators=100, random_state=42)
  rf.fit(X_train, y_train)
  rf_predictions = rf.predict(X_test)
  
  svr = SVR(kernel='linear')
  svr.fit(X_train, y_train)
  svr_predictions = svr.predict(X_test)
  
  print(f"Random Forest Regressor MSE: {mean_squared_error(y_test, rf_predictions)}")
  print(f"Support Vector Regressor MSE: {mean_squared_error(y_test, svr_predictions)}")
  ```

### Key Documents and Notebooks
- [Project Proposal](CS210%20Project%20Proposal.pdf): Initial project ideas and objectives.
- [Project Phase 2](CS210%20Project%20Phase%202.pdf): Detailed data preparation and initial findings.
- [Project Phase 3](CS210%20Project%20Phase%203.pdf): Final report on machine learning models and results.
- [Sample Project Notebook](Sample_Project.ipynb): Jupyter Notebook demonstrating data analysis and visualization.

## CS300: Data Structures

### Project Overview
This course focused on implementing and understanding various data structures and their applications. Projects included working with stacks, binary search trees, and hash tables, with a particular emphasis on solving complex problems using these structures.

### Projects

#### 1. Maze Generation and Pathfinding
- **Objective**: To generate random mazes and find paths between designated entry and exit points using stack data structures.
- **Summary**: 
  - **Maze Generation**: Implemented a program to generate a random maze of size MxN using a stack-based depth-first search algorithm.
  - **Pathfinding**: Implemented a function to find the path between specified entry and exit points in the maze using stack-based backtracking.
  - **Key Features**:
    - Generated K random MxN mazes and ensured every cell was reachable from any other cell.
    - Used a stack to keep track of the path and backtrack when no unvisited neighbors were available.
- **Code Highlights**:
  ```cpp
  // Example from bartus_sisman_bartu_hw1.cpp
  // Function to create a maze and write to file
  void createMaze(int row, int column, string fileName) {
      // Implementation details...
  }

  // Function to find path in a maze
  void path_find(int ID, int x_entry, int y_entry, int x_exit, int y_exit) {
      // Implementation details...
  }
  ```
- **Documents**:
  - [Homework 1 Description](Homework1.pdf): Detailed description of the maze generation and pathfinding project.
  - [Code Implementation](bartus_sisman_bartu_hw1.cpp): Source code for the maze generation and pathfinding project.

#### 2. Binary Search Tree and Hash Table Implementations
- **Objective**: To implement and utilize binary search trees (BST) and hash tables for various data operations.
- **Summary**:
  - **Binary Search Tree (BST)**: Implemented a BST to handle dynamic data insertion, deletion, and search operations efficiently.
  - **Hash Table**: Implemented a hash table to demonstrate efficient data storage and retrieval using hashing techniques.
  - **Key Features**:
    - The BST implementation included functions for adding, deleting, and searching for items.
    - The hash table implementation demonstrated handling collisions and efficient data retrieval.
- **Code Highlights**:
  ```cpp
  // Example from BSTree.cpp
  template<typename T>
  bool BSTree<T>::addItem(T* newItem) {
      // Implementation details...
  }

  // Example from Hash.h
  class Hash {
      // Implementation details...
  }
  ```
- **Documents**:
  - [BST Implementation](BSTree.cpp): Source code for the binary search tree implementation.
  - [Hash Table Implementation](Hash.h): Source code for the hash table implementation.
  - [Homework Descriptions](Homework3.pdf, Homework4.pdf, Homework5.pdf): Detailed descriptions of the projects involving BSTs and hash tables.

#### 3. Sorting and Searching Algorithms
- **Objective**: To sort a given unsorted PhoneBook and implement search algorithms to find contact names.
- **Summary**:
  - **Sorting Algorithms**: Compared four sorting algorithms: Insertion Sort, Quick Sort (with median pivot), Merge Sort (in-place), and Heap Sort.
  - **Search Algorithms**: Compared Sequential Search and Binary Search for full and partial name searches.
  - **Key Features**:
    - Measured and compared execution times for sorting and searching algorithms.
    - Calculated speedups between different algorithms to determine the most efficient one.
- **Code Highlights**:
  ```cpp
  // Example from main.cpp
  // Sorting and searching contacts in a PhoneBook
  void QuickSort(vector<Contact>& vec, int low, int high) {
      // Implementation details...
  }

  void BinarySearch(vector<Contact>& vec, string query) {
      // Implementation details...
  }
  ```
- **Documents**:
  - [Homework 5 Description](Homework5.pdf): Detailed description of the sorting and searching project.
  - [Code Implementation](main.cpp): Source code for the sorting and searching algorithms project.

## CS303: Logic and Digital System Design

### Project Overview
This course focused on controlling components in digital systems and writing Verilog code. The main project involved designing a digital system for a vault with password storage and entry.

### Projects

#### 1. Digital Combination Lock with User ID
- **Objective**: To design a digital combination lock with unique codes for up to 100 users, allowing them to set and enter vault passwords.
- **Summary**: 
  - **System Design**: Created a digital combination lock using Verilog HDL and a provided project template. The system included user identification through a 2-digit decimal number and password verification against stored codes.
  - **Key Features**:
    - The keypad input was encoded, and user IDs were displayed on a seven-segment display.
    - The system handled password entry, storage, and verification with feedback through LEDs indicating "GRANTED" or "DENIED".
    - Used synchronous design principles with a 100Hz clock for all flip-flops, ensuring reliable operation.
- **Documents**:
  - [Project Description](CS303_PROJECT_2023.pdf): Detailed description of the digital combination lock project and requirements.



## CS305: Programming Languages

### Project Overview
This course involved creating a compiler part by part through a series of homework assignments. The main focus was on developing a scanner, parser, type checker, and optimizer for a Lisp-like toy programming language called JISP. The final project involved implementing a Scheme interpreter.

### Projects

#### 1. Lexical Analyzer for JISP
- **Objective**: To implement a scanner (lexical analyzer) for the JISP programming language.
- **Summary**: 
  - The scanner was designed to tokenize various language constructs such as keywords, operators, identifiers, numbers, and strings.
  - It outputted the token names along with their positions in the input file.
- **Key Features**:
  - Implemented tokenization for JISP keywords like "Get", "Set", "Function", "Print", "For", "If", and "Return".
  - Handled operators and punctuation such as `+`, `-`, `*`, `/`, `==`, `<`, `>`, `<=`, `>=`, `++`, `--`, `,`, `[`, and `]`.
  - Recognized identifiers, numbers, and strings, storing their lexemes and positions.
  - Produced output indicating tokens and detected illegal characters in the input.
- **Documents**:
  - [Homework 1 Description](CS305_Spring_2022_2023_Homework_1.pdf): Detailed description of the lexical analyzer implementation.
  - [Code Implementation](bartus-hw1.flx): Flex file for the lexical analyzer.

#### 2. Parser for JISP
- **Objective**: To write a context-free grammar and implement a simple parser for the JISP language.
- **Summary**: 
  - The parser was designed to validate the syntax of JISP programs based on the grammar rules.
  - It used the tokens produced by the scanner to check for grammatical correctness.
- **Key Features**:
  - Defined grammar rules for JISP statements, including "Set", "If", "Print", increment and decrement statements, and function declarations.
  - Implemented parsing for conditions, expressions, and function calls.
  - Outputted "OK" for grammatically correct programs and "ERROR" otherwise.
- **Documents**:
  - [Homework 2 Description](CS305_Spring_2022_2023_Homework_2_v3.pdf): Detailed description of the parser implementation.
  - [Code Implementation](bartus-hw2.y, bartus-hw2.flx): Bison and Flex files for the parser.

#### 3. Type Checker and Optimizer for JISP
- **Objective**: To implement a type checker and a simple optimizer for the JISP language.
- **Summary**: 
  - The type checker performed simple type checks for constant expressions.
  - The optimizer simplified expressions by evaluating constant subexpressions.
- **Key Features**:
  - Detected type mismatches for operations involving incompatible types.
  - Simplified constant expressions and printed their evaluated results.
- **Documents**:
  - [Homework 3 Description](CS305_Spring_2022_2023_Homework_3-v2.pdf): Detailed description of the type checker and optimizer.
  - [Code Implementation](parser.y, scanner.flx): Bison and Flex files for the type checker and optimizer.

#### 4. Scheme Procedures
- **Objective**: To implement various Scheme procedures to demonstrate understanding of the language.
- **Summary**: 
  - Implemented procedures for manipulating lists, performing arithmetic operations, and handling conditionals.
  - Developed a main procedure that processes a list of triples representing triangles, filtering and sorting them based on specified rules.
- **Key Features**:
  - Implemented error handling for invalid inputs.
  - Sorted and filtered triangles based on the triangle inequality and Pythagorean theorem.
- **Documents**:
  - [Homework 4 Description](CS305_HW4.pdf): Detailed description of the Scheme procedures.
  - [Code Implementation](bartus-hw4.scm): Scheme file for the procedures.

#### 5. Scheme Interpreter
- **Objective**: To implement a Scheme interpreter that supports a subset of the Scheme language.
- **Summary**: 
  - Developed an interpreter that evaluates Scheme expressions, including definitions, conditionals, and arithmetic operations.
  - Supported additional features such as `let`, `let*`, `cond`, and function definitions.
- **Key Features**:
  - Implemented a read-eval-print loop (REPL) for interactive evaluation.
  - Handled syntax and semantic errors, providing meaningful error messages.
- **Documents**:
  - [Homework 5 Description](CS305_202202_HW5.pdf): Detailed description of the Scheme interpreter implementation.
  - [Code Implementation](s7): Scheme file for the interpreter.


## CS306: Database Systems

### Project Overview
This course focused on the principles of database design, query languages, and database management. The projects were designed to provide hands-on experience with MySQL and MongoDB, implementing CRUD operations, and managing database systems.

### Projects

#### 1. SU_Stock Relational Database (MySQL)
- **Objective**: To design and implement a relational database for a stock trading platform.
- **Summary**: 
  - The database included entities such as Company, Stock, User, Portfolio, Ownership, and Order.
  - The tables were designed to capture various aspects of stock trading, including company information, daily stock prices, user portfolios, stock ownership, and order transactions.
- **Key Features**:
  - **Company Table**: Stores company details like symbol, name, and outstanding shares.
  - **Stock Table**: Tracks daily stock prices for each company.
  - **User Table**: Records user information.
  - **Portfolio Table**: Maintains the value of each user's portfolio.
  - **Ownership Table**: Shows which stocks and quantities are owned by users.
  - **Order Table**: Captures details of buy/sell orders placed by users.
- **Documents**:
  - [Phase 1 Report](CS306_Project_Phase1_Report_bartu_sisman_bartus.pdf): Detailed design and implementation of the relational database.
  - [Phase 2 Report](SU_Stock_Phase2_Report.pdf): Functional dependencies and BCNF evaluation for the tables.

#### 2. CRUD Operations and User Interface (MySQL)
- **Objective**: To develop a Python application that performs CRUD operations on the SU_Stock database.
- **Summary**: 
  - Implemented a user interface for interacting with the database using Python scripts.
  - Provided functionalities for creating, reading, updating, and deleting records in the Company and Stock tables.
- **Key Features**:
  - **Insert Operations**: Added new records to the Company and Stock tables.
  - **Select Operations**: Retrieved data from the tables.
  - **Update Operations**: Modified existing records.
  - **Delete Operations**: Removed records from the tables.
- **Documents**:
  - [Phase 3 Report](CS306_Project_Phase_III_Report.pdf): Implementation of CRUD operations and user interface.

#### 3. NoSQL Database Implementation (MongoDB)
- **Objective**: To create a service using MongoDB to handle user comments and market news.
- **Summary**: 
  - Developed collections for UserComments and MarketNews in MongoDB.
  - Implemented CRUD operations to interact with these collections through a Python script.
- **Key Features**:
  - **UserComments Collection**: Stores user comments about various stocks.
  - **MarketNews Collection**: Stores news articles related to the stock market.
  - **Python Script**: Provided a menu-driven interface for performing CRUD operations on the collections.
- **Code Highlights**:
  ```python
  # Connection to MongoDB
  from pymongo import MongoClient

  def get_database():
      CONNECTION_STRING = "mongodb+srv://bartu:12345@cluster0.mvtl2ui.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0"
      client = MongoClient(CONNECTION_STRING)
      return client['SU_Stock']
  ```

  ```python
  # CRUD operations
  def create_collection(db, name):
      collection = db[name]
      return collection

  def read_all_data(collection):
      data = collection.find()
      for item in data:
          print(item)

  def insert_data(collection, data):
      collection.insert_one(data)
      print("Data inserted successfully.")
  ```

  ```python
  # Main script for interaction
  from connection import get_database
  from crud_operations import create_collection, read_all_data, insert_data

  def main():
      db = get_database()
      # Menu-driven interaction for CRUD operations
      ...
  if __name__ == "__main__":
      main()
  ```
- **Documents**:
  - [Phase 4 Report](CS306_Project_Phase_4_Report.pdf): Implementation of the NoSQL database and demonstration of CRUD operations.


## CS307: Operating Systems

### Course Overview
This course provided in-depth knowledge of operating systems, focusing on advanced terminal control in Unix systems, detailed understanding of Linux components, process management, inter-process communication, system calls, and threading. The course projects included practical assignments that required implementing and simulating various operating system concepts through hands-on programming.

### Projects

#### 1. PA1: Pipe Simulation
- **Objective**: To simulate the behavior of pipes in Unix-like operating systems using C.
- **Summary**: 
  - The project involved creating a parent (SHELL) process that forks two child processes (MAN and GREP). The first child executes the `man` command and the second child executes the `grep` command, simulating a pipeline between them.
  - The output of the `man` command is passed through a pipe to the `grep` command, which then writes the filtered output to a file.
- **Key Features**:
  - Process creation using `fork()`.
  - Pipe communication using `pipe()`, with redirection of standard input/output using `dup2()`.
  - Command execution using `execvp()`.
  - File operations for output redirection using `open()`.
- **Code Highlights**:
  ```c
  // Example from PA1
  int fd[2]; // fd[0] for read, fd[1] for write
  pipe(fd);
  int child1 = fork();

  if (child1 == 0) { // MAN process
      close(fd[0]);
      dup2(fd[1], STDOUT_FILENO);
      char *man_parts[4] = {"man", "grep", "ls", NULL};
      execvp("man", man_parts);
  } else {
      int child2 = fork();
      if (child2 == 0) { // GREP process
          wait(NULL);
          close(fd[1]);
          dup2(fd[0], STDIN_FILENO);
          close(STDOUT_FILENO);
          open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
          char *grep_parts[5] = {"grep", "-A2", "-e", "-n, --line-number", NULL};
          execvp("grep", grep_parts);
      }
  }
  ```
- **Documents**:
  - [PA1 Source Code](pipeSim.c): The C file implementing the pipe simulation.
  - [PA1 Output](output.txt): The output file containing the results of the pipeline execution.

#### 2. PA2: Command Parser and Executor
- **Objective**: To create a C program that parses and executes a series of commands from a file.
- **Summary**: 
  - The program reads commands from `commands.txt`, parses each command, and executes it. The parsed command details are written to `parse.txt`.
  - Commands can include options, redirections, and can be run in the background.
- **Key Features**:
  - Command parsing to extract the command name, input files, options, redirection symbols, and background execution flags.
  - Command execution with support for input/output redirection and background processing.
- **Code Highlights**:
  ```c
  // Example from PA2
  char *com_parts[1024];
  while (fgets(str, 1024, fptr)) {
      char *token = strtok(str, " ");
      int count = 0;
      while (token != NULL) {
          com_parts[count++] = token;
          token = strtok(NULL, " ");
      }
      // Command parsing logic...
      if (fork() == 0) {
          execvp(real_arr[0], real_arr);
      } else {
          wait(NULL);
      }
  }
  ```
- **Documents**:
  - [PA2 Source Code](hw2.c): The C file implementing the command parser and executor.
  - [Parsed Commands](parse.txt): The file containing details of parsed commands.
  - [Command Inputs](commands.txt): The file with commands to be parsed and executed.
  - [Command Output](output1.txt): Example output from executed commands.

#### 3. PA3: Ride Sharing Simulation
- **Objective**: To simulate a ride-sharing system using semaphores and pthreads in C.
- **Summary**: 
  - The program simulates a scenario where fans from two clubs (A and B) are looking for rides to a game. Each car can take four passengers, and the program ensures cars are filled with valid combinations of passengers before departing.
- **Key Features**:
  - Custom semaphore functions to manage shared resources and synchronize threads.
  - Pthread synchronization using pthreads, barriers, and condition variables to coordinate the actions of fans looking for rides.
  - Ride allocation to ensure that each car had the correct number of passengers from each team before starting the ride.
- **Code Highlights**:
  ```c
  // Example from PA3
  void sem_wait(sem_t *s) {
      pthread_mutex_lock(&s->lock);
      s->value--;
      if (s->value < 0) {
          pthread_cond_wait(&s->cond, &s->lock);
      }
      pthread_mutex_unlock(&s->lock);
  }

  void *routine_A() {
      printf("Thread ID: %ld, Team: A, I am looking for a car\n", pthread_self());
      routine(&semA, &semB, 'A');
  }
  ```
- **Documents**:
  - [PA3 Source Code](rideshare.c): The C file implementing the ride-sharing simulation.

#### 4. PA4: Name Corrector
- **Objective**: To develop a C program that corrects names in text files within a directory by prefixing titles based on a provided database.
- **Summary**: 
  - The program reads a list of names and titles from `database.txt`. It then searches through all text files in the specified directory, updating occurrences of the names with the appropriate title and surname.
- **Key Features**:
  - Database reading to store name and title information from `database.txt` into a linked list.
  - Recursive directory traversal to find and process text files.
  - File correction to update names in text files with the appropriate title and surname from the database.
- **Code Highlights**:
  ```c
  // Example from PA4
  void ReadDatabase() {
      FILE *ptr = fopen("database.txt", "r");
      while (fscanf(ptr, "%s", inputstring) != EOF) {
          // Processing logic...
      }
      fclose(ptr);
  }

  void correctfile(char *dir, char *dname) {
      FILE *ptr = fopen(txtname, "r+");
      while (fscanf(ptr, "%s", word) != EOF) {
          // Correction logic...
      }
      fclose(ptr);
  }
  ```
- **Documents**:
  - [PA4 Source Code](corrector.c): The C file implementing the name corrector.
  - [Name Database](database.txt): The file containing names and titles used for correction.
 


## CS310: Mobile Application Development

### Course Overview
CS310 focused on developing mobile applications using a comprehensive stack of backend and frontend technologies. The backend utilized Spring Boot, MySQL, MongoDB, and Docker, while the frontend was built using Java, Android Studio, and Jetpack. The course emphasized RESTful API development, database management, and creating intuitive mobile user interfaces.

### Project: GameSphere

#### Project Overview
GameSphere is a centralized platform designed for gamers to share their experiences, manage gaming activities across multiple platforms, and discover new games tailored to their preferences. This project treats games as an art form deserving of in-depth exploration. On GameSphere, users can write detailed reviews, rate games, share favorite characters, compile wishlists, and track playtime across platforms. The platform includes social features such as following friends and viewing their gaming profiles. A standout feature is the "What to Play?" recommendation system, which suggests games based on user preferences.

- **Objective**: To create a centralized platform for gamers to share experiences, integrate playtime data across platforms, and discover games tailored to their preferences.

#### Backend Overview
The backend of GameSphere was developed to manage user interactions and efficiently handle data storage. It utilized Spring Boot for the application logic, MySQL for relational data, and MongoDB for flexible document storage. Docker was used for containerizing the services, and Postman was employed for API testing.

- **Technologies Used**: Spring Boot, MySQL, MongoDB, Docker, Postman
- **Key Components**:
  - **Users**: Managed in the `Users` collection, containing user-specific information linked to `Credentials` and `Profiles`.
  - **Credentials**: Stored in the `Credentials` collection, containing encrypted authentication data.
  - **Profiles**: Detailed user profiles in the `Profiles` collection, including game histories, follower counts, and social links, linked to the `Games` collection.
  - **Games**: The `Games` collection contains details of game titles available on various platforms.

#### Backend Code Highlights

```java
// Example from GameSphereRestController.java
@RestController
@RequestMapping("/GameSphere")
public class GameSphereRestController {

    @Autowired
    private UserService userService;

    @GetMapping("/Users")
    public List<User> listAllUsers() {
        return userService.findAll();
    }

    @PostMapping("/Users/save")
    public User saveUser(@RequestBody UserPayload userPayload) {
        return userService.save(userPayload);
    }
}
```

#### Frontend Overview
The frontend of GameSphere was built using Java, Android Studio, and Jetpack, offering a robust and user-friendly interface for users to interact with the platform. The design focused on intuitive navigation and seamless integration with backend services.

- **Features**:
  - **User Authentication Screen**: Facilitates user registration and login.
  - **Game Library Screen**: Displays games from linked gaming accounts.
  - **Playtime Tracker**: Shows aggregated playtime data from various platforms.
  - **Game Reviews and Social Interaction**: Users can write reviews, like, comment, and follow other users.
  - **Search Functionality**: Enables searching for games and other users.
  - **Game Detail Screens**: Provides comprehensive information about each game.
  - **Social Feed**: Displays activities (comments, likes, reviews) of followed users.
  - **Profile Management**: Allows users to view and manage their profiles, follow others, and see followers.
  - **Problem Reporting**: Users can report specific game-related issues.
  - **"What to Play?" Recommendation System**: Offers personalized game suggestions.

#### Frontend Code Highlights

```java
// Example from MainActivity.java
public class MainActivity extends AppCompatActivity {

    private EditText usernameEditText;
    private EditText passwordEditText;
    private Button loginButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        usernameEditText = findViewById(R.id.username);
        passwordEditText = findViewById(R.id.password);
        loginButton = findViewById(R.id.loginButton);

        loginButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                login();
            }
        });
    }

    private void login() {
        String username = usernameEditText.getText().toString();
        String password = passwordEditText.getText().toString();
        // Perform login operation...
    }
}
```

#### Navigation Diagram
The navigation diagram outlines the flow between different screens in the GameSphere mobile application, illustrating how users navigate from login/register to the main page, game details, profile, and post creation screens.

![Navigation Diagram](navigation_diagram.png)

### Documentation
- [Project Proposal](GameSphere_ProjectProposal.pdf): Detailed project proposal and objectives.
- [Backend Explanations](GameSphere_Backend_Explanations.docx): Detailed explanations of the backend structure and endpoints.


## CS408: Computer Networks

### Course Overview
CS408 focused on understanding computer networks, including HTTP, packet analysis using Wireshark, server-client relationships, and network protocols. The course included a project where students developed a basic Discord-like messaging application, DiSUcord, to apply their knowledge of networking principles in a practical context.

### Project: DiSUcord

#### Project Overview
DiSUcord is a simple messaging application designed to mimic the core functionalities of Discord. It allows users to subscribe to channels, send messages, and interact in a networked environment. The project includes both a client and a server module, demonstrating key concepts such as TCP socket programming, real-time communication, and multi-client handling.

- **Objective**: To develop a messaging application with functionalities such as channel subscription, message sending, and real-time updates using TCP sockets.

#### Key Functionalities

1. **Client Module**:
   - **User Interface**: The client application provides a GUI for users to connect to the server, subscribe to channels, and send messages.
   - **Connection Management**: Users can connect to the server by providing the server's IP address and port number. The client handles connection establishment and disconnection gracefully.
   - **Channel Subscription**: Users can subscribe to two fixed channels, "IF100" and "SPS101". Subscription status is managed through buttons on the GUI.
   - **Message Sending and Receiving**: Users can send messages to subscribed channels and receive messages in real-time from other users.
   - **Client Actions**: The client interface logs all actions and server responses, providing feedback to the user.

2. **Server Module**:
   - **User Interface**: The server application provides a GUI to monitor connected clients, channel subscriptions, and server actions.
   - **Connection Management**: The server listens for incoming client connections on a specified port, managing multiple clients simultaneously.
   - **Client Authentication**: The server ensures that usernames are unique and manages client connections and disconnections.
   - **Message Broadcasting**: The server broadcasts messages to all subscribers of a channel. It handles subscribe and unsubscribe requests and updates the GUI accordingly.

#### Client Code Highlights

```csharp
// Example from client.cs
public partial class client : Form
{
    private void Handle_Connection()
    {
        string IP = IP_box.Text;
        int portNum;
        if (string.IsNullOrWhiteSpace(IP) || !Int32.TryParse(port_box.Text, out portNum))
        {
            client_actions.AppendText("Please enter a valid IP and Port to connect.\n");
            return;
        }
        clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        try
        {
            clientSocket.Connect(IP, portNum);
            connected = true;
            login_button.Enabled = true;
            port_box.Enabled = false;
            IP_box.Enabled = false;
        }
        catch
        {
            client_actions.AppendText("Could not connect to the server!\n");
        }
    }

    private void ReceiveMessage()
    {
        while (connected)
        {
            try
            {
                byte[] buffer = new byte[1024];
                int rec = clientSocket.Receive(buffer);
                if (rec <= 0)
                {
                    throw new SocketException();
                }
                string response = Encoding.Default.GetString(buffer).Trim('\0');
                if (response == "Name accepted")
                {
                    this.Invoke((MethodInvoker)delegate
                    {
                        client_actions.AppendText("Welcome " + name_box.Text + "!\n");
                        if100_subscribe_button.Enabled = true;
                        sps101_subscribe_button.Enabled = true;
                        login_button.Text = "Log out";
                        login_button.BackColor = Color.Red;
                        name_box.Enabled = false;
                    });
                }
                else if (response.StartsWith("if100:") || response.StartsWith("sps101:"))
                {
                    this.Invoke((MethodInvoker)delegate
                    {
                        DisplayMessage(response);
                    });
                }
                else
                {
                    this.Invoke((MethodInvoker)delegate
                    {
                        client_actions.AppendText(response + "\n");
                    });
                }
            }
            catch
            {
                if (!terminating)
                {
                    this.Invoke((MethodInvoker)delegate
                    {
                        client_actions.AppendText("Lost connection to the server.\n");
                        if100_send_button.Enabled = false;
                        if100_subscribe_button.Enabled = false;
                        sps101_send_button.Enabled = false;
                        sps101_subscribe_button.Enabled = false;
                    });
                }
                clientSocket.Close();
                connected = false;
            }
        }
    }
}
```

#### Server Code Highlights

```csharp
// Example from server.cs
public partial class server : Form
{
    private void Accept()
    {
        while (listening)
        {
            try
            {
                Socket newClient = serverSocket.Accept();
                Thread receiveThread = new Thread(() => ReceiveMessage(newClient));
                receiveThread.Start();
            }
            catch
            {
                if (terminating)
                {
                    listening = false;
                }
                else
                {
                    this.Invoke((MethodInvoker)delegate
                    {
                        server_actions.AppendText("The socket stopped working.\n");
                    });
                }
            }
        }
    }

    private void ReceiveMessage(Socket clientSocket)
    {
        bool connected = true;
        string clientName = null;
        while (connected && !terminating)
        {
            try
            {
                byte[] buffer = new byte[1024];
                int rec = clientSocket.Receive(buffer);
                if (rec <= 0)
                {
                    throw new SocketException();
                }
                string receivedMessage = Encoding.Default.GetString(buffer).Trim('\0');
                if (receivedMessage.StartsWith("Log out"))
                {
                    HandleClientLogout(receivedMessage, clientSocket);
                    return;
                }
                else if (clientName == null)
                {
                    clientName = ProcessClientName(receivedMessage, clientSocket);
                }
                else if (receivedMessage.StartsWith("Subscribe "))
                {
                    string channel = receivedMessage.Split(' ')[1];
                    SubscribeClientToChannel(clientName, channel);
                    this.Invoke((MethodInvoker)delegate
                    {
                        server_actions.AppendText(clientName + " has subscribed to " + channel.ToUpper() + "\n");
                    });
                }
                else if (receivedMessage.StartsWith("Unsubscribe "))
                {
                    string channel = receivedMessage.Split(' ')[1];
                    UnsubscribeClientFromChannel(clientName, channel);
                    this.Invoke((MethodInvoker)delegate
                    {
                        server_actions.AppendText(clientName + " has unsubscribed from " + channel.ToUpper() + "\n");
                    });
                }
                else if (receivedMessage.StartsWith("Message "))
                {
                    string[] parts = receivedMessage.Split(new[] { ' ' }, 3);
                    string channel = parts[1];
                    string message = parts[2];
                    BroadcastMessage(clientName, channel, message);
                }
            }
            catch
            {
                if (!terminating)
                {
                    this.Invoke((MethodInvoker)delegate
                    {
                        server_actions.AppendText(clientName != null ? $"Client {clientName} has disconnected.\n" : "A client has disconnected.\n");
                    });
                    lock (clientSockets)
                    {
                        if (clientName != null && clientSockets.ContainsKey(clientName))
                        {
                            clientSockets.Remove(clientName);
                        }
                    }
                }
                clientSocket.Close();
                connected = false;
            }
        }
    }
}
```

### Summary
The CS408 project DiSUcord offered a hands-on experience in building a client-server messaging application using C# and Windows Forms. It involved critical aspects of computer networks, such as TCP socket programming, real-time communication, and managing multiple client connections. The project emphasized both the theoretical and practical understanding of network protocols and client-server architecture, reinforcing the concepts learned throughout the course.

