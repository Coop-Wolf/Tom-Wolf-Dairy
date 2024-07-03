/*****************************************************************************
*
*  Author:           Cooper Wolf
*  Email:            cooper.wolf13@gmail.com
*  Title:            Breeding Report Optimization
*  Label:            BRO
*  Date:             June 13, 2024
*
*  Description:
*        This program reads in a file that contains information about
*        cows that are being breeded. The program will take that information
*        and calculate when each cow is expected to go dry, have her calf, and
*        when she needs to be brought in to be further cared for.
*        
*  Usage:
*       - The program will ask for input and output files
*       - The input file needs to be a list of cow information 
*         in form of Cow ID (100), Breed date (2024-01-01),
*         and the sire (2D5GE6) 
*
*  Files:
*       main.cpp    : driver program
*****************************************************************************/

#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <vector>
#include "termcolor.hpp"
using namespace std;

struct Node
{
    int cow;
    string breed;
    string calf;
    string bring_in;
    string dry;
    string sire;
    Node* next;

    Node();

    Node(int c, string b, string calf, string dry,
         string bring, string sire);    
};

class Vector
{
    Node* front;
    Node* rear;

public:

/**
* Public    : Vector
*
* Description:
*      This function sets front and rear to Null.
*
* Params:
*      None
*
* Returns:
*      void
*/
Vector();

/**
* Public    : pushFront
*
* Description:
*      This function pushes a value to the front of a vector
*
* Params:
*      [int]    :   tag of cow
*      [string] :   date cow was breeded
*      [string] :   date cow is planned to have calf
*      [string] :   date cow is expected to go dry
*      [string] :   date cow is to be brough in for care
*      [string] :   Id of bull used for birth.
*
* Returns:
*      void
*/
void pushFront(int c, string b, string calf,
               string dry, string bring, string sire);

/**
* Public    : pushAt
*
* Description:
*      This function pushes a node into the vector at the given index
*
* Params:
*      [int]    :   index to push node into vector
*      [int]    :   tag of cow
*      [string] :   date cow was breeded
*      [string] :   date cow is planned to have calf
*      [string] :   date cow is expected to go dry
*      [string] :   date cow is to be brough in for care
*      [string] :   Id of bull used for birth.
*
* Returns:
*      void
*/
void pushAt(int index, int c, string b, string calf,
            string dry, string bring, string sire);

/**
* Public    : inOrderPush
*
* Description:
*      This function pushes a value to the vector in order
*
* Params:
*      [int]    :   tag of cow
*      [string] :   date cow was breeded
*      [string] :   date cow is planned to have calf
*      [string] :   date cow is expected to go dry
*      [string] :   date cow is to be brough in for care
*      [string] :   Id of bull used for birth.
*
* Returns:
*      void
*/
void inOrderPush(int c, string b, string calf,
                 string dry, string bring, string sire);

/**
* Public    : popAt
*
* Description:
*      This function pops a node at the given index
*
* Params:
*      [int]  :   index to pop node at
*
* Returns:
*      [int]  :   cow popped off of the vector
*/
int popAt(int index);

/**
* Public    : find
*
* Description:
*      This function finds the cow id and returns the index if its there
*
* Params:
*      [int]  :   cow to search for
*
* Returns:
*      [int]  :   index that the value is at in the vector
*/
int find(int cow);

/**
* Public    : popFront
*
* Description:
*      This function pops the first node in the vector
*
* Params:
*      None
*
* Returns:
*      [int]  :   value popped off of the vector        
*/
int popFront();

/**
* Public    : get_calfDate
*
* Description:
*      This function prints the projected calf date
*
* Params:
*      [string] :   date cow was breeded
*
* Returns:
*      void
*/
void get_calfDate(string breed);

/**
* Public    : get_dryDate
*
* Description:
*      This function prints the projected dry date
*
* Params:
*      [string] :   date cow was breeded
*
* Returns:
*      void
*/
void get_dryDate(string breed);

/**
* Public    : get_dringDate
*
* Description:
*      This function prints the date the cow needs to be brought in
*
* Params:
*      [string] :   date cow was breeded
*
* Returns:
*      void
*/
void get_bringDate(string breed);

/**
* Public    : is_old
*
* Description:
*      This function determines if cow has already had baby
*
* Params:
*      [string] :   date cow was breeded
*
* Returns:
*      bool
*/
bool is_old(string breed);

/**
* Public    : print
*
* Description:
*      This function prints the vector
*
* Params:
*      none
*
* Returns:
*      void
*/
void print();

/**
* Public    : pushRear
*
* Description:
*      This function pushes cow info to the back of the vector
*
* Params:
*      [int]    :   cow id to push onto another vector
*      [string] :   date cow was breeded
*      [string] :   date cow is projected to have calf
*      [string] :   date cow is projected to go dry
*      [string] :   date cow needs to be brought in 
*      [string] :   bull id
*
* Returns:
*      void
*/
void pushRear(int c, string b, string calf, string dry, 
              string bring, string sire);
};

/**
* Public    : heading
*
* Description:
*      This function prints the heading
*
* Params:
*      none
*
* Returns:
*      void
*/
void heading();

/**
* Public    : clear_screen
*
* Description:
*      This function clears the screen
*
* Params:
*      none
*
* Returns:
*      void
*/
void clear_screen();
void openfiles(ifstream& infile, ofstream& outfile);
void due_dates(string b_date, int cow, string sire);
void add_cow(ofstream& outfile, string answer, int num, int tag,
             string b_date, string b_daddy, Vector& herd);

int main() 
{
    // creating variables
    ifstream infile;
    ofstream outfile;
    Vector herd;
    int cow, num, tag;
    string sire, due_date, answer, b_date, b_daddy, d_date, bring;

    // initializing variables
    sire = due_date = answer = b_date = b_daddy = d_date = bring = "";
    cow = num = tag = 0;

    // opening input/output files
    openfiles(infile, outfile);

    // reading in data from input file
    while (infile >> cow >> b_date >> sire)
    {  
        // copying info to output file
        outfile << cow << endl << b_date << endl << sire << endl;

        // pushing cows to vector in order
        herd.inOrderPush(cow, b_date, due_date, d_date, bring, sire);
    }

    // adding new cows if needed
    add_cow(outfile, answer, num, tag, b_date, b_daddy, herd);

    // printing updated cows in order
    clear_screen();
    heading();
    herd.print();
}

void due_dates(string b_date, int cow, string sire)
{
    
    tm input_tm = {};
    strptime(b_date.c_str(), "%Y-%m-%d", &input_tm);
    
    // convert to time_t
    time_t calf, dry, bring_in;
    calf = dry = bring_in = mktime(&input_tm);
    
    // adding days to origial date
    calf += (285 * 24 * 60 * 60); // 285 days in seconds
    dry = calf - (55 * 24 * 60 * 60);
    bring_in = calf - (14 * 24 * 60 * 60);

    // convert back to tm
    tm calf_date = *localtime(&calf);
    tm dry_date = *localtime(&dry);
    tm bring_in_date = *localtime(&bring_in);

    // printing dates
    cout << endl << cow << "   " << b_date << "  " 
         << setw(1) << " " << put_time(&calf_date, "%Y-%m-%d") 
         << setw(4) << "  " << put_time(&dry_date, "%Y-%m-%d") 
         << setw(3) << " " << put_time (&bring_in_date, "%Y-%m-%d")
         << setw(9) << sire;
}

// prints heading
void heading()
{
    cout << termcolor::bold << termcolor::blue << "\nCow  " << setw(9) << " Breed Date "
         << setw(11) << "  Dry Date " << setw(16) << " Bring date  "
         << setw(10) << "Calf Date"   << setw(8) << "Sire"
         << termcolor::reset << termcolor::bold << termcolor::grey
         << "\n-----------------------------------------------------------------\n" << termcolor::reset;
}

// opens files
void openfiles(ifstream& infile, ofstream& outfile)
{
    // string to hold fine names
    string in_name, out_name;

    // getting file names from user
    cout << "Input File: ";
    cin >> in_name;
    cout << "Output File: ";
    cin >> out_name;
    cout << endl;

    // opening files
    infile.open(in_name);
    outfile.open(out_name);
}

// adds new cows to the vector
void add_cow(ofstream& outfile, string answer, int num, int tag, 
             string b_date, string b_daddy, Vector& herd)
{
    string calf = "", dry = "", bring = "";

    // asking user if they need to add cows
    cout << termcolor::yellow << "\n\nAdd cow(s)? ";
    cin >> answer;

    // receives info if user wants to add more
    if(answer == "yes" || answer == "Yes")
    {
        cout << "How many cows?";
        cin >> num;
        cout << endl << termcolor::reset;

        for(int i = 0; i < num; i++)
        {
            cout << termcolor::grey << "Enter Cow #: ";
            cin >> tag;
            cout << "Enter breed date (YYYY-MM-DD): ";
            cin >> b_date;
            cout << "Baby Daddy: ";
            cin >> b_daddy;
            cout << endl << termcolor::reset;

            herd.inOrderPush(tag, b_date, calf, dry, bring, b_daddy);

            //updated info goes to output file
            outfile << tag << endl << b_date << endl 
                    << b_daddy << endl;
        }
    }
    
    cout << termcolor::reset << endl;
}

// clears the screen
void clear_screen() 
{
    #ifdef _WIN32
    // Windows-specific code
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    DWORD count;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdOut, &csbi);

    FillConsoleOutputCharacter(hStdOut, ' ',
                               csbi.dwSize.X * csbi.dwSize.Y,
                               coord, &count);
    SetConsoleCursorPosition(hStdOut, coord);
    #else
    // ANSI escape code for Unix-like systems
    std::cout << "\033[2J\033[1;1H";
    #endif
}

Node::Node()
{
    cow = 0;
    sire = "";
    breed = "";
    calf = "";
    bring_in = "";
    dry = "";
    next = NULL;
}

Node::Node(int c, string b, string calf, string dry,
     string bring, string sire)
{
    cow = c;
    breed = b;
    this->calf = calf;
    this->dry = dry;
    bring_in = bring;
    this->sire = sire;
    next = NULL;
}

Vector::Vector()
{
    front = rear = NULL;
}

void Vector::pushFront(int c, string b, string calf,
                       string dry, string bring, string sire)
{
    // variable to sore node
    Node* temp = new Node(c, b, calf, dry, bring, sire);

    // checking if vector is empty
    if (front == NULL)
    {
        front = temp;
        rear = temp;
    }
    else
    {
        temp->next = front;
        front = temp;
    }
}

void Vector::inOrderPush(int c, string b, string calf,
                         string dry, string bring, string sire)
{
    Node* temp = new Node(c, b, calf, dry, bring, sire);         // variable to store new node
    Node* temp2 = front;                // variable to traverse vector
    int i = 0;                          // variable to track the index

    // if vector is empty, add it to the list 
    if(!front)
    {
        pushFront(temp->cow, temp->breed, temp->calf, temp->dry,
                  temp->bring_in, temp->sire);
        return;
    }

    // if value is less than front, pushFront
    if (front->breed > b) //in this case data will be calf date
    {
        pushFront(temp->cow, temp->breed, temp->calf, temp->dry,
                  temp->bring_in, temp->sire);
    }

    //if value is more than rear, pushRear
    else if (rear->breed < b)
    {
        pushRear(temp->cow, temp->breed, temp->calf, temp->dry,
                 temp->bring_in, temp->sire);
    }

    // if value is somewhere between, traverse list
    else
    {
        // traversing til value is less than node
        while (temp2->breed < b && temp2->next)
        {
            temp2 = temp2->next;
            i++;
        }
        // pushing new node to correct index
        pushAt(i, temp->cow, temp->breed, temp->calf,
               temp->dry, temp->bring_in, temp->sire);
    }
}

int Vector::popFront()
{
    int x;                          // variable to store popped value
    Node* temp = front;             // variable to pop item in vector

    // checking if vector is empty
    if (front == NULL)
        return -1;

    // switching front to second item and deleting first
    front = front->next;
    x = temp->cow;
    delete temp;
    return x;
}

int Vector::popAt(int index)
{
    int size = 0;                   // variable to store size of vector
    Node* temp = front;             // variable to pop item in vector
    Node* temp2 = front;            // variable to traverse vector

    // if index is 0, popping front
    if (index == 0)
    {
        return popFront();
    }

    // checking size of Vector
    while (temp)
    {
        temp = temp->next;
            size++;
    }
    // returning -1 if index if greater than size
    if (index >= size)
    {
        cout << "Index is too large\n";
        return -1;
    }

    else
    {
        // looping to pop value at index
        for (int i = 0; i < index; i++)
        {
            temp = temp2;
            temp2 = temp2->next;
        }
        temp->next = temp2->next;
        return temp2->cow;
    }
}

void Vector::pushRear(int c, string b, string calf, string dry,
                      string bring, string sire)
{
    Node* temp = new Node(c, b, calf, dry, bring, sire); // variable to traverse vector

    // checking if vector is empty
    if (front == NULL)
    {
        rear = temp;
        front = temp;
    }
    // pushing node to back of vector
    else
    {
        rear->next = temp;
        rear = temp;
        rear->next = NULL;
    }
}

int Vector::find(int cow)
{
    int i = 0;                      // variable to use for index
    Node* temp = front;             // variable to find vector

    // traversing vector
    while (temp != NULL)
    {
        // if item is found, return index
        if (temp->cow == cow)
            popAt(i);    //needs to remove cow when its found;

        temp = temp->next;
        i++;
    }
    return -1;
}

void Vector::pushAt(int index, int c, string b, string calf,
                    string dry, string bring, string sire)
{
    int size = 0;               // variable to store size of vector
    Node* temp = front;         // variable to traverse vector

    // checking size of Vector
    while (temp)
    {
        temp = temp->next;
        size++;
    }

    // if index is 0, pushing to front of vector
    if (index == 0)
        pushFront(c, b, calf, dry, bring, sire);

    // if index is larger than vector size, error message
    else if (index > size)
        cout << "Index to too large\n";

    // placing value into vector at the index
    else
    {
        Node* temp2 = new Node(c, b, calf, dry, bring, sire);    // variable to traverse vector
        temp = front;
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        temp2->next = temp->next;
        temp->next = temp2;
    }
}

void Vector::get_calfDate(string breed)
{
    tm input_tm = {};
    strptime(breed.c_str(), "%Y-%m-%d", &input_tm);
    
    // Convert to time_t
    time_t calf;
    calf = mktime(&input_tm);
    
    // adding days to origial date
    calf += (285 * 24 * 60 * 60); //285 days in seconds
    
    // Convert back to tm
    tm calf_date = *localtime(&calf);

    cout << setw(1) << " " << put_time(&calf_date, "%Y-%m-%d");

}
void Vector::get_dryDate(string breed)
{
    tm input_tm = {};
    strptime(breed.c_str(), "%Y-%m-%d", &input_tm);

    // Convert to time_t
    time_t dry, calf;
    dry = calf = mktime(&input_tm);

    // adding days to origial date
    calf+= (285 * 24 * 60 * 60);
    dry = calf - (55 * 24 * 60 * 60);

    // Convert back to tm
    tm dry_date = *localtime(&dry);

    cout << setw(1) << " " << put_time(&dry_date, "%Y-%m-%d");
}

void Vector::get_bringDate(string breed)
{
    tm input_tm = {};
    strptime(breed.c_str(), "%Y-%m-%d", &input_tm);

    // Convert to time_t
    time_t bring, calf;
    bring = calf = mktime(&input_tm);

    // adding days to origial date
    calf += (285 * 24 * 60 * 60);
    bring = calf - (14 * 24 * 60 * 60);

    // Convert back to tm
    tm bring_date = *localtime(&bring);

    cout << setw(1) << " " << put_time(&bring_date, "%Y-%m-%d");
}

void Vector::print()
{
    Node* temp = front;             // variable to traverse vector

    // looping til temp = NULL
    while (temp)
    {

        if(is_old(temp->breed) == true)
        {
            //bring stuff in red
            cout << termcolor::red << temp->cow << "   " << temp-> breed << " " 
                 << setw(1) << " " << setw(4);

            get_dryDate(temp-> breed);
            cout << "  ";

            get_bringDate(temp->breed);
            cout << setw(2) << " ";

            get_calfDate(temp-> breed);
            cout << setw(3) << " " << temp-> sire << endl << termcolor::reset;

            temp = temp->next;
        }
        else
        {
        cout << termcolor::green << temp->cow << "   " << temp-> breed << " " 
             << setw(1) << " " << setw(4);
        
        get_dryDate(temp-> breed);
        cout << "  ";
        
        get_bringDate(temp->breed);
        cout << setw(2) << " ";
        
        get_calfDate(temp-> breed);
        cout << setw(3) << " " << temp-> sire << endl << termcolor::reset;

        temp = temp->next;
        }
    }
    cout << termcolor::bold << termcolor::grey
         << "\n-----------------------------------------------------------------" << termcolor::reset;
}

bool Vector::is_old(string breed)
{
    tm input_tm = {};
    bool old;
    tm test = {};
    string local = "";
    
    strptime(local.c_str(), "%Y-%m-%d", &test);
    strptime(breed.c_str(), "%Y-%m-%d", &input_tm);
    
    // Convert to time_t
    time_t t = time(0); // Get current time
    time_t calf;
    
    calf = mktime(&input_tm);

    // adding days to origial date
    calf += (285 * 24 * 60 * 60); //285 days in seconds

    //seeing if cow had already had her baby
    if(t > calf)
        old = true;
    else
        old = false;
    
    return old;
}