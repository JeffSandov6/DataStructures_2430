//
//  main.cpp
//  web
//
//  Created by Jeffry Sandoval on 11/12/17.
//  Copyright © 2017 Jeffry Sandoval. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include "ArgumentManager.h"


using namespace std;



string removeSpaces(string word);
bool checkIfEmpty(string checkLine);
string toLowercase(string lineToUncap);

string checkType(string word);
string formatted(string word);
string formatEquation(string word);

void readFunction(string setName, string inputFile);

string writeFunction(string varName, string outputFile);


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


void quickSortBegin(string *list, int size);
void recQuickSort(string *list, int first, int last);
int partitionQuickSort(string *list, int first, int last);
void swap(string *list, int element1, int element2);


int recBinarySearch(string *listToSearch, int first, int length, string searchItem);
int normalBinarySearch(string *listToSearch, int first, int length, string searchItem);



///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////



int precedenceValue(char a);
string infixToPostfix(string equation);


struct infixToPostfixNode
{
    char itsOperator;
    infixToPostfixNode *itsLink;
};



class infixToPostfixStack
{
public:
    
    infixToPostfixNode *stackTop;
    
    
    infixToPostfixStack()   //constructor
    {
        stackTop = NULL;
    }
    
    
    void push(char c);
    
    char top(); //returns top element in stack
    
    void pop(); //removes top element in stack
    
    void emptyTheStack(); //delete everything in stack
    
    
};


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////



string evaluatePostfix(string postfix, string nameOfVar);



struct evaluatePostfixNode
{
    string operand;
    evaluatePostfixNode *nextLink;
};



class evaluatePostfixStack
{
public:
    
    evaluatePostfixNode *topOfStack;
    
    
    evaluatePostfixStack()   //constructor
    {
        topOfStack = NULL;
    }
    
    
    void push(string variable);
    
    string top(); //returns top element in stack
    
    void pop(); //removes top element in stack
    
    //void emptyTheStack(); //delete everything in stack
    
    
};





///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////





struct nodeType
{
    string info;
    nodeType *nextLink;
    nodeType *prevLink;
};

nodeType *first, *last;

class doublyLinkedList
{
public:
    void insertToDoubly(string theString);
    void reversePrint();
    bool searchTraversal(string element);
    void outputToFile(ofstream& file);
    void addToGlobalList(string name, int numOfElements);
    void destroyList();
    bool isEmpty();
};





struct globalNodeType   //my global nodes for linked list of linked list is of type nodeType(my inner node)
{
    string* addressOfArray;
    string nameOfArray;
    int numberOfElements;
    globalNodeType *nextGlobal;
    globalNodeType *prevGlobal;
    
};
globalNodeType *globalFirst, *globalLast;



class listOfLists
{
public:
    void insertToLL(string* currentNode, string arrayName, int elements);  //it'll be the set name
    //void LLreversePrint(doublyLinkedList currList);
    bool variableIsInList(string var);
    void deleteThisArray(string arrayName);
};

listOfLists LL;   //creare a list of lists object








int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        std::cerr << "Usage: web script=input.script" << std::endl;
        return -1;
    }

    ArgumentManager am(argc, argv);
    const std::string script_name = am.get("script");
    cout << "script name is " << script_name << std::endl;

    ofstream errorStream;
    errorStream.open("log.txt", ios_base::app);
    ifstream inStream;
    
    string temp = "";
    string type;
    string justToHold;
    globalFirst = NULL;
    
    
    inStream.open(script_name);   //script_name
    while (!inStream.eof())
    {
        getline(inStream, temp); // we input the file line by line
        string setName;
        string fileName;
        string cmd;
        
        
        if (checkIfEmpty(temp) == true) // if theres an empty line we just skip it
        {
            continue;
        }
        

        type = checkType(temp);
        

        if(type == "read")  //this if condition is for read expressions
        {
            cmd = formatted(temp);
            stringstream ss(cmd);
            ss >> cmd >> setName >> fileName;
             // << cmd << "\\" << setName << "\\" << fileName << "\\" << endl;


            readFunction(setName,fileName);
            
        }
        else if(type == "write")   // this else if is for write expressions
        {
            
            cmd = formatted(temp);
            stringstream ss(cmd);
            ss >> cmd >> setName >> fileName;
            // << temp << endl;
            // << cmd << "\\" << setName << "\\" << fileName << "\\" << endl;
            

            justToHold = writeFunction(setName, fileName);
            
            if(justToHold == "non-existant")
            {  //if the write function wants us to output a variable that doesn't exist
                errorStream << "INVALID: " << temp << endl;
                continue;
                
            }

            
            
            
            
            
            
        }
        else if(type == "invalid")   //this else if, is for whehn we have an incorrect amount of parenthesis
        {
            errorStream << "INVALID: " << temp << endl;
            continue;
            
            
        }
        else  //this final else is for functions
        {

            cmd = formatEquation(temp);
            
 
            if(cmd == "invalid char")
            {
                //this function has an invalid character, has nothing after =, or is missing an = sign, so we skip it
                
                errorStream << "INVALID: " << temp << endl;
                continue;
            }
            
            
            
            // << "the original equation is: " << temp << endl;
            // << "the equation after being formatted is: " << cmd << endl;
            string postfix = infixToPostfix(cmd);
            
            if(postfix == "invalid postFix expression")
            {
                //this if function is called if the (variables - operators) != 1
                //there should always be 1 more var than there is operators for postFix to be valid
                // << "INVALID: " << temp << endl;
                errorStream << "INVALID: " << temp << endl;
                continue;

            }
            
            // << "the post fix equation is: " << postfix << endl << endl;
            
            stringstream ss(cmd);
            ss >> cmd;
            
            justToHold = evaluatePostfix(postfix, cmd);

            if(justToHold == "non-existant")
            {
                //this is if the function holds a non existant value
                // << "INVALID: " << temp << endl;
                errorStream << "INVALID: " << temp << endl;
                continue;

            }
            
            
            
        }
        
    }
    
    


    
    
    return 0;
}




///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


//              SORTING FUNCTIONS



void quickSortBegin(string *list, int size)
{
    
    recQuickSort(list, 0, size - 1);
    
}



void recQuickSort(string *list, int first, int last)
{
    int pivot;
    if(first < last)
    {
        pivot = partitionQuickSort(list, first, last);
        recQuickSort(list, first, pivot - 1);
        recQuickSort(list, pivot + 1, last);
    }
    
    
}



int partitionQuickSort(string *list, int first, int last)
{
    string currPivot;
    int index, smallIndex;
    swap(list, first, (first+last) / 2);
    currPivot = list[first];
    smallIndex = first;
    
    for(index = first + 1; index <= last; index++)
    {
        if( list[index].compare(currPivot) < 0) //if element in this index is smaller(comes first alphabetically)
        {
            smallIndex++;
            swap(list, smallIndex, index);
        }
        
        
    }
    
    swap(list, first, smallIndex);
    
    return smallIndex;
    
    
}












void swap(string *list, int element1, int element2)
{
    string temp = list[element1];          //temp holds the string thats in list[first] location
    list[element1] = list[element2];         //string at first location is replaced (swapped) with the string thats in list[second] locations
    list[element2] = temp;                //string at second location is replaced (swapped) with the string in temp
    
    
}





///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////



int normalBinarySearch(string *listToSearch, int first, int length, string searchItem)
{
    int last = length - 1; //the number of the last element   //line 1
    
    int middleElement;              //line 2
    
    
    while(first <= last)    //line 3
    {
        
        middleElement = (first + last) / 2;    //line 4
        if(searchItem == listToSearch[middleElement])       //line 5
        {
            return middleElement;       //line 6
            
        } else if(searchItem.compare(listToSearch[middleElement]) > 0)  { //if searchItem comes after middleElement alphabetically
            first = middleElement + 1;
            
        } else { //.compare will return less than 0 if searchItem comes before middleElement alphabetically
            last = middleElement - 1;
        }
    }
    
    
    return -1;
}














int recBinarySearch(string *listToSearch, int first, int length, string searchItem)
{
    
    int middleElement;
    
    if(first <= length)
    {
        middleElement = (first + length) / 2;
        
        if(searchItem == listToSearch[middleElement])
        {
            return middleElement;
            
        } else if(searchItem.compare(listToSearch[middleElement]) > 0)  { //if search item comes before middleElement alphabetically
            return recBinarySearch(listToSearch, middleElement + 1, length, searchItem);
            
        } else { //if search item comes after middleElement element alphabetically
            return recBinarySearch(listToSearch, first, middleElement - 1, searchItem);
            
            
        }
        
    }
    
    
    
    
    
    return -1;
}







///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////



string removeSpaces(string word)
{
    string returnWord = "";
    
    for(int i = 0; i < word.size(); i++)
    {
        char a = word[i];
        
        if(a != 32 || isalpha(a) || (a >= 48 && a <= 57))  //if current char isnt a space, we add it to return word
        {
            returnWord = returnWord + a;
        }
        
        
    }
    
    
    
    return returnWord;
}











string toLowercase(string lineToUncap)
{
    string newWord = "";
    int i = 0;
    char b;
    for (i = 0; i < lineToUncap.size(); i++)
    {
        char a = lineToUncap[i];
        
        if (a < 65 || a > 90) //the ascii decimal numbers for capital letters range from 65 to 89, so if they aren't in that range, the character stays as is
        {
            newWord = newWord + a;
            
        } else  //if the letters are in that range, we add 32 to them, to make them lowercase
        {
            b = a + 32;
            newWord = newWord + b;
        }
        
    }
    
    
    return newWord;
}









bool checkIfEmpty(string checkLine)
{
    int lineCharacters = (int)checkLine.size();
    bool lineIsEmpty = false;
    int emptySpaces = 0;
    
    for(int i = 0; i < checkLine.size(); i++)
    {
        char a = checkLine[i];
        
        if(a == 32 || a == 9)
        {
            emptySpaces++;
        }
    }
    
    if(emptySpaces == lineCharacters)   //if the number of empty spaces is equal to the number of characters in line, the line is empty
    {
        lineIsEmpty = true;
        
    }
    
    
    return lineIsEmpty;
}




string checkType(string word)
{
    int openParenthesis = 0;
    int closeParenthesis = 0;
    
    for(int j = 0; j < word.size(); j++)   //first we check to see if we have a correct ammount of parenthesis, dont have to recheck this for any afterwards
    {
        
       if(word[j] == 40)
       {
           openParenthesis++;
           
       }else if(word[j] == 41)
       {
           closeParenthesis++;
           
       }else
       {
           continue;
       }
        
    }
    
    
    if(openParenthesis != closeParenthesis)
    {
        return "invalid";
    }


    
    string expression = "";
    for(int i = 0; i < word.size(); i++)
    {
        expression = expression + word[i];
        
        if(expression == "read")
        {
            return "read";
            
        } else if (expression == "write")
        {
            return "write";
        } else {
            continue;
        }
        
        
    }
    return "operation";
    
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

//      FORMATTING THE INPUT EQUATIONS



string formatted(string word)
{
    string newWord = "";
    for(int i = 0; i < word.size(); i++)
    {
        char a = word[i];
        
        if(isalpha(a) || a == 46 || (a >= 48 && a <= 57)){
            
            newWord = newWord + a;
            
        }
        else
        {
            newWord = newWord + " ";
        }
        
    }
    
    return newWord;
    
    
}



string formatEquation(string word)
{
    int holdIndexOfEquals = 0;
    string newWord = "";
    bool hasEqual = false;
    int preEqualsCount;
    int postEqualsCount;
    
    for(int i = 0; i < word.size(); i++)
    {
        char a = word[i];
        
        if(a == 61) //if is equal to an equal sign
        {
            newWord = newWord + " " + a + " ";
            holdIndexOfEquals = i + 1;
            hasEqual = true;
            break;  //this for loop ends after the equal sign is added
        }
        
        newWord = newWord + a;

    }
    
    
    if(hasEqual == false) //if the function doesn't have an equals sign
    {
        return "invalid char";
    }
    
    preEqualsCount = newWord.size();
    
    
    
    for(holdIndexOfEquals = holdIndexOfEquals; holdIndexOfEquals < word.size(); holdIndexOfEquals++)
    {
        char b = word[holdIndexOfEquals];
        
        if(b == 40 || b == 41 || b == 42 || b == 43) //if curr char is a (), + or *, we add a space, add char, then another space
        {
            newWord = newWord + " " + b + " ";
            
        } else if( (isalpha(b)) || (b >= 48 && b <= 57) ) {  //if curr char is word or letter, we just add it together
            newWord = newWord + b;
            
        } else {
            return "invalid char";
        }
        
    }
    
    
    postEqualsCount = newWord.size();
    
    
    if(preEqualsCount == postEqualsCount)
    {
        return "invalid char"; //handles if the error of equation having nothing after the equals sign
    }
    
    
    return newWord;
    
    
}





///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////








void readFunction(string setName, string inputFile)
{
    ifstream inputStream;
    string word;
    doublyLinkedList firstdoublyList;
    int counter = 0;
    
    inputStream.open(inputFile.c_str());
    
    if(inputStream.fail())  //might have to change this to an empty list
        //actually, i should leave it to not exist, then the resulting list will be
        //just the other list if its +, and no list if its *
    {
        // << "this file doesn't exist, so we will skip it" << endl;
        return;
    }
    
    
    string newWord = "";
    string letter;

    
    while (inputStream >> word) //here we will create the linked list, and list of lists
    {
        word = toLowercase(word);
        
        for(int i = 0; i < word.length(); i++)   //splits the words if any are together like h3llo
        {
            letter = word[i];
            
            if(isalpha(word[i])) //if the char of the word is a letter, we add it to newWOrd
            {
                newWord = newWord + letter;
                
            } else if (newWord != "") //if it isnt, and newWord isnt empty, add newWord to list and reset it
            {
                firstdoublyList.insertToDoubly(newWord);
                counter++;
                newWord = "";
            } else  //if newWord is empty, just skip it
            {
                continue;
            }
            
        }
        
        if(newWord != "") //if after the loop, newWord isnt empty, we add it to our list and reset it
        {
            firstdoublyList.insertToDoubly(newWord);
            counter++;
            newWord = "";

        }
        
    }
    
    string *wordArray = new string[counter];
    nodeType *current = first;
    
    int newCounter = 0;
    
    while(current != NULL)
    {
        wordArray[newCounter] = current->info;
        
        current = current->nextLink;
        
        newCounter++;
        
    }
    firstdoublyList.destroyList();
    
    ////need to sort the wordArray
    
    quickSortBegin(wordArray, counter);
    
    
    LL.insertToLL(wordArray, setName, counter); //// we insert this array to our global Linked list of Arrays
    
}









string writeFunction(string varName, string outputFile)    //////overwrite function, dont forget
{
    // << varName << ": at write function" << endl;
    ofstream outStream;
    outStream.open(outputFile.c_str());
    globalNodeType *current;
    current = globalFirst;
    int counter = 0;
    string *holdlist1 = nullptr;
    int numElementsList1 = 0;
    
    while(current != NULL && counter != 1)  //while loop loops through Lists of Lists
    {
        
        if(current->nameOfArray == varName)
        {
            counter++;
            holdlist1 = current->addressOfArray; //this pointer will be equal to the array of list 1's name pretty much
            numElementsList1 = current->numberOfElements;
            
        }
        
        current = current->nextGlobal;
        
    }
    
    if(counter != 1)  //if the expression contains a non existant variable
    {
        return "non-existant";
    }
    
    counter = 0;
    
    string prevWord = "";
    
    for(int i = 0; i < numElementsList1; i++)
    {
        if(prevWord == holdlist1[i]) //skip duplicates
        {
            continue;
            
        }
        
        
        outStream << holdlist1[i] << endl;
        // << holdlist1[i] << endl;
        
        prevWord = holdlist1[i];
        
        
    }
    
    // << "end Of write Function" << endl;
    
    
    outStream.close();
    
    return "";
    
}











///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

//          LINKED LISTS SECTION




void doublyLinkedList::insertToDoubly(string theString)
{
    
    theString = removeSpaces(theString);
    
    nodeType *newNode;
    newNode = new nodeType;
    newNode->info = theString;
    newNode->prevLink = NULL;
    newNode->nextLink = NULL;
    
    if (first == NULL) //if the list is empty, we insert newNode, and it is now the only one in list
    {
        first = newNode;
        last = newNode;
        
        
    } else {
        newNode->prevLink = last;  //newNode prev linker is pointing at the previous node in list
        last->nextLink = newNode;  //node before this one's next linker now points at newNode
        last = newNode;  //now the last pointer points at last node;
        //also its nextLink is NULL bc when newNode was created, its nextLink was set to NULL
        
    }
    
    
    
    
}



void doublyLinkedList::reversePrint() {
    nodeType *traverse;
    
    traverse = last;   //our traverse pointer starts at the end
    
    while(traverse!= NULL)
    {
        cout << traverse->info << endl;
        traverse = traverse->prevLink;   //traverse then moves to the prevLink/Node to continue whileLoop
    }
    
    
}




bool doublyLinkedList::searchTraversal(string element)
{
    bool inList = false;
    nodeType *traverse;
    traverse = first;
    
    while(traverse != NULL)
    {
        if(traverse->info == element)
        {
            inList = true;
            break;
        }
        
        traverse = traverse->nextLink; //traverse moves to nextLink/node to continue whileLoop
        
    }
    
    return inList;
}




void doublyLinkedList::outputToFile(ofstream& file)
{
    nodeType *traverse;
    
    traverse = last;
    
    while(traverse != NULL)
    {
        file << traverse->info << " ";   //same as with print func, traverse adds to output in reverse
        traverse = traverse->prevLink;
    }
    
    file << endl;
}




void doublyLinkedList::destroyList()
{
    nodeType *temp;
    
    while(first != NULL)
    {
        temp = first;
        first = first->nextLink;
        delete temp;
        
    }
    
    last = NULL;
    
    
    
}


bool doublyLinkedList::isEmpty()
{
    if(first == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
    
    
    
}

void doublyLinkedList::addToGlobalList(string name, int numOfElements)
{
    
    nodeType *current;
    current = first;
    string *wordArray = new string[numOfElements];
    int counter = 0;
    
    
    while(current != NULL)
    {
        wordArray[counter] = current->info;
        // << current->info << endl;
        current = current->nextLink;
        counter++;
        
    }
    
    quickSortBegin(wordArray, numOfElements);
    
    LL.insertToLL(wordArray, name, numOfElements);
    
    
    
}






///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////




void listOfLists::insertToLL(string* currentNode, string arrayName, int elements)
{
    globalNodeType *newNode;
    newNode = new globalNodeType;
    newNode->addressOfArray = currentNode;    //stores the address of array
    newNode->nameOfArray = arrayName;         //stores name of array
    newNode->numberOfElements = elements;     // # of elements in array
    newNode->prevGlobal = NULL;
    newNode->nextGlobal = NULL;
    
    if (globalFirst == NULL) //if list is empty, this node becomes the first
    {
        globalFirst = newNode;
        globalLast = newNode;
        
    } else {
        newNode->prevGlobal = globalLast; //new node linker pointing to last node in list
        globalLast->nextGlobal = newNode; //prev last node now points to newNode
        globalLast = newNode; //last node is now the Newest node being added
        
        
        
    }
}


bool listOfLists::variableIsInList(string var)
{
    globalNodeType *traverse;
    traverse = globalFirst;
    bool isInList = false;
    
    while(traverse != NULL)
    {
        if(traverse->nameOfArray == var) //an array w/ this name is in list
        {
            isInList = true;
            break;
        }
        
     
        traverse = traverse->nextGlobal;
    }
    
    return isInList;
    
    
    
}


void listOfLists::deleteThisArray(string arrayName)
{
    globalNodeType *traverse, *behindTraverse;
    
    if(globalFirst->nameOfArray == arrayName)  //if the array we're looking for is the first node
    {
        traverse = globalFirst;
        globalFirst = globalFirst->nextGlobal;
        
        if(globalFirst != NULL)
        {
            globalFirst->prevGlobal = NULL;
        } else {
            globalLast = NULL;
            
        }
        delete traverse;
        
    }else {
        
        traverse = globalFirst;
        
        while(traverse != NULL)
        {
            if(traverse->nameOfArray == arrayName)
            {
                behindTraverse = traverse->prevGlobal;  //set this to the node before the one we're deleting
                behindTraverse = traverse->nextGlobal;  //and set the previous node to point to the node the one we're deleting is pointing to
                
                if(traverse->nextGlobal != NULL)  //if the next node after the one we are deleting isn't NULL
                {
                    //set the next node's prev node to point to node before the one we are going to delete
                    traverse->nextGlobal->prevGlobal = behindTraverse;
                    
                }
                
                if(traverse == globalLast)  //if the node we are going to delete is the last one
                {
                    globalLast = behindTraverse;
                    
                }
                
                delete traverse;
                break;
                
                
            }
            
            
            
            traverse = traverse->nextGlobal;
            
        }
        
        
    }
    
    

    
    
}




///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


//      INFIX TO PREFIX SECTION





int precedenceValue(char a)  //this is only going to be called to compare multiplication and addition
{
    if(a == '*')            //multiplication values are worth more than addition
    {
        return 2;
        
    }
    else if (a == '+')
    {
        return 1;
    }
    else
    {
        return 0;
        
    }
    
}





string infixToPostfix(string equation)
{
    string postfix = "";
    // << "hi" << endl;
    
    istringstream iss(equation);    /////use this for postfix to infix
    string word;
    infixToPostfixStack stack;
    int counter = 0;
    
    int numOfOperands = 0;  //variables
    int numOfOperators = 0;  //+ and *
    
    
    while( iss >> word)  //go through operands and words 1 by 1
    {
        counter++;
        
        if(counter < 3) // the first 2 words will be the expression name, and the equals sign
        {
            continue;
        }
        
        
        
        if( (word[0] != '+') && (word[0] != '(' ) && (word[0] != '*' ) && (word[0] != ')' ) )  //if char is not a +, (, *, or ). if its a variable (operand)
        {
            postfix = postfix + word + " ";
            numOfOperands++;
            
        }else if(word[0] == '(')  //add opening parenthesis to stack
        {

            stack.push('(');
            
        }else if(word[0] == ')' )
        {

            while(stack.top() != -1 && stack.top() != '(' )  //.top() returns -1 when its equal to NULL
            {
                postfix = postfix + stack.top() + " ";  //add the current top element of stack to the postfix
                stack.pop();
            }
            
            if(stack.top() == '('  )  //skip over the opening parenthesis
            {
                stack.pop();
                
            }
            
        }else   //if the curr char is an * or + sign
        {
            
            numOfOperators++;
            
            while(stack.top() != -1 && ( precedenceValue(word[0]) <= precedenceValue(stack.top()) ) ) //if curr operator has less precedence or equal precedence to curr top char in stack
            {
                
                if(stack.top() == '('  )  //skip over the opening parenthesis if its here
                {
                    // << stack.top() << endl;
                    stack.pop();
                    
                    continue;
                }
                
                
                
                postfix = postfix + stack.top() + " ";  //add the current top element of stack to the postfix so that itll come first, aka have precedence
                stack.pop();                            //remove the top element after adding it
                
            }
            stack.push(word[0]); //add curr operator the stack
            
        }
        
    }
    
    
    while(stack.top() != -1)
    {
        postfix = postfix + stack.top() + " ";  //add the current top element of stack to the postfix
        stack.pop();
        
    }
    
    
    postfix = postfix + " " + '=';   //at the end we add an equal sign to the postfix equation
    
    if( (numOfOperands - numOfOperators) != 1 )   //valid postfix must have 1 more operand than operators
    {
        return "invalid postFix expression";
        
    }
    // << postfix << endl;
    return postfix;
    
    
}





char infixToPostfixStack::top()   //this will be used to do comparisons
{
    if(stackTop == NULL)
    {
        return -1; //the operands will be getting compared so if its -1, DONT POP, just add
    } else {
        return stackTop->itsOperator;  //else we return its operand
    }
    
    
}



void infixToPostfixStack::pop()   //delete the current top node
{
    infixToPostfixNode *curr;
    if(stackTop != NULL)
    {
        curr = stackTop;   //curr node is equal to the stack top
        stackTop = stackTop->itsLink; //move stackTop to the node under it
        delete curr;  //then we delete the current top node;
        
        
    } else {
        
        // << "Stack is empty, so nothing happened" << endl;
    }
    
    
    
}





void infixToPostfixStack::push(char c) //add to the top of the stack
{
    infixToPostfixNode *newNode;
    
    newNode = new infixToPostfixNode;
    
    newNode->itsOperator = c;
    newNode->itsLink = stackTop;  //the nodes link will be pointing to the current top of the stack
    stackTop = newNode;    //we make stackTop point to the new top node

    
}




void infixToPostfixStack::emptyTheStack()    //delete everything in Stack
{
    infixToPostfixNode *temp;
    
    while(stackTop != NULL)
    {
        temp = stackTop;
        stackTop = stackTop->itsLink;
        delete temp;
        
    }
    
    
}




///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

//          POSTFIX EVALUATION



string evaluatePostfix(string postfix, string nameOfVar)
{
    // << nameOfVar << " its postfix is " << postfix << endl;
    
    istringstream iss(postfix);    /////use this for postfix to infix
    string word;
    evaluatePostfixStack postStack;
    
    string list1, list2;
    string *holdlist1 = nullptr, *holdlist2 = nullptr;
    int numElementsList1 = 0, numElementsList2 = 0;
    int counter, *pointsToCounter;
    int newArrayNumElements = 0;
    int backupCounterNumElements = 0;
    doublyLinkedList doublyList, backUpDoublyList;
    doublyLinkedList *pointsToList;
    bool temp1InList = false;

    counter = 0;

    
    string var1, var2;
    
 
    while(iss >> word)
    {
        if( (word[0] != '+') && (word[0] != '*' ) && (word[0] != '=') )  //if char is not a +, =, or * (if its a variable)
        {
            postStack.push(word);
            continue;
            
            
            
        }
        else if (word[0] == '+')
        {

            
                    globalNodeType *current;
                    current = globalFirst;
            
                    list1 = postStack.top();
                    postStack.pop();
                    list2 = postStack.top();
                    postStack.pop();
            
            
            
                    if(list2 != "temp" && list1 != "temp")
                    {
                        
                        while(current != NULL && counter != 2)  //while loop loops through Lists of Lists
                        {
                            
                            if(current->nameOfArray == list1)
                            {
                                counter++;
                                holdlist1 = current->addressOfArray; //this pointer will be equal to the array of list 1's name pretty much
                                numElementsList1 = current->numberOfElements;
                                
                            }
                            
                            
                            if(current->nameOfArray == list2)
                            {
                                counter++;
                                holdlist2 = current->addressOfArray; //this pointer will be equal to the array of list 1's name pretty much
                                numElementsList2 = current->numberOfElements;
                                
                                
                            }
                            
                            
                            
                            current = current->nextGlobal;
                            
                            
                            
                        }
                        
                        
                        if(counter != 2)  //if the expression contains a non existant variable
                        {
                            doublyList.destroyList();
                            return "non-existant";
                        }
                        
                        counter = 0;
                        
                        
                        
                        for(int i = 0; i < numElementsList1; i++)
                        {
                            doublyList.insertToDoubly(holdlist1[i]);
                            
                            
                        }
                        
                        
                        for(int j = 0; j < numElementsList2; j++)
                        {
                            doublyList.insertToDoubly(holdlist2[j]);
                            
                        }
                        
                        newArrayNumElements = newArrayNumElements + numElementsList1 + numElementsList2;
                        
                        postStack.push("temp");
                        
                        
                        // << numElementsList2 << " or " << numElementsList1 << endl;
                        // << newArrayNumElements << endl;

                     
                    } else if (list1 == "temp" && list2 == "temp") {
                        postStack.push("temp");
                        //continue;
                        //if both of the lists in stack are called temp, then we can just skip this command bc the linkedList holds the values for both
                        
                        
                        
                        
                    } else if(list2 == "temp") {  //if list2 is the one with the temp var name
                        
                        
                        
                        while(current != NULL && counter != 1)  //while loop loops through Lists of Lists
                        {
                            
                            if(current->nameOfArray == list1)
                            {
                                counter++;
                                holdlist1 = current->addressOfArray; //this pointer will be equal to the array of list 1's name pretty much
                                numElementsList1 = current->numberOfElements;
                                
                            }
                            
                            current = current->nextGlobal;


                        }
                        
                        if(counter != 1)  //if the expression contains a non existant variable
                        {
                            doublyList.destroyList();
                            return "non-existant";
                        }
                        
                        counter = 0;
                        
                        for(int i = 0; i < numElementsList1; i++)
                        {
                            doublyList.insertToDoubly(holdlist1[i]);
                            
                            
                        }
                        
                        
                        newArrayNumElements = newArrayNumElements + numElementsList1;

                        postStack.push("temp");
                        
                        // << numElementsList2 << " or " << numElementsList1 << endl;
                        // << newArrayNumElements << endl;

                        
                        
                    } else { //if list1 is the one with the temp var name
                        
                        
                        while(current != NULL && counter != 1)  //while loop loops through Lists of Lists
                        {
                            // << current->nameOfArray << endl;
                            
                            if(current->nameOfArray == list2)
                            {
                                counter++;
                                holdlist2 = current->addressOfArray; //this pointer will be equal to the array of list 1's name pretty much
                                numElementsList2 = current->numberOfElements;
                                
                            }
                            
                            current = current->nextGlobal;
                            
                        }
                        
                        if(counter != 1)  //if the expression contains a non existant variable
                        {
                            doublyList.destroyList();
                            return "non-existant";
                        }
                        
                        
                        counter = 0;
                        // << newArrayNumElements << endl;
                        for(int i = 0; i < numElementsList2; i++)
                        {
                            doublyList.insertToDoubly(holdlist2[i]);
                            

                        }

                        
                        newArrayNumElements = newArrayNumElements + numElementsList2;
                        // << newArrayNumElements << endl;

                        postStack.push("temp");

                        
                        
                    }
            
            
            
       //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////

            
            
            
            
        }
        else if (word[0] == '*')    //if the current char calls for a multiplication expression
        {
            
                globalNodeType *current;
                current = globalFirst;
            
                list1 = postStack.top();
                postStack.pop();
                list2 = postStack.top();
                postStack.pop();
            

            
                counter = 0;
            
            
            
                if(list2 != "temp" && list1 != "temp")
                {
                    
                    while(current != NULL && counter != 2)  //while loop loops through Lists of Lists
                    {
                        
                        if(current->nameOfArray == list1)
                        {
                            counter++;
                            holdlist1 = current->addressOfArray; //this pointer will be equal to the array of list 1's name pretty much
                            numElementsList1 = current->numberOfElements;
                            
                        }
                        
                        
                        if(current->nameOfArray == list2)
                        {
                            counter++;
                            holdlist2 = current->addressOfArray; //this pointer will be equal to the array of list 1's name pretty much
                            numElementsList2 = current->numberOfElements;
                            
                            
                        }
                        
                        
                        
                        current = current->nextGlobal;
                        
                        
                        
                    }
                    
                    
                    if(counter != 2)  //if the expression contains a non existant variable
                    {
                        doublyList.destroyList();
                        return "non-existant";
                    }
                    
                    counter = 0;  //reset the counter
                    
                    string currElement;
                    string prevWord = "";
                    pointsToCounter = NULL;
                    
                    
                    if(doublyList.isEmpty() == true)
                    {
                        // << "isempty" << endl;
                        pointsToList = &doublyList;  //use a pointer to add to the list
                        newArrayNumElements = 0;
                        pointsToCounter = &newArrayNumElements;
                        temp1InList = false;
                        
                        
                    } else {
                        cout << "doubly list isNotempty, using backup DoublyList" << endl;
                        //doublyList.reversePrint();
                        pointsToList = &backUpDoublyList;  //if temp is already in list, this pointer creates a new value
                        temp1InList = true;
                        backupCounterNumElements = 0;
                        pointsToCounter = &backupCounterNumElements;
                    }
                    
                    
                    int newVar = 0;
                    
                    if(numElementsList1 <= numElementsList2) //we want to use the smaller list as the basis for mult, if list1 is smaller
                    {
                        for (int i = 0; i < numElementsList1; i++)  //go through every word
                        {
                            currElement = holdlist1[i];

                            
                            if(currElement == prevWord) //skip dups
                            {
                                continue;
                            }
                            
                            if( normalBinarySearch(holdlist2, 0, numElementsList2, currElement) != -1 ) //if the item is on the other list, add to new
                            {
 
                                pointsToList->insertToDoubly(currElement);  //inserts to the indicated list
                                newVar++;

       
                            }
                            
                            prevWord = holdlist1[i];
                            
                        }
                        
                        
        
                    }else  //if numElementsList1 > numElementsList2
                    {
                        for (int i = 0; i < numElementsList2; i++)  //go through every word
                        {
                            currElement = holdlist2[i];
                            
                            if(currElement == prevWord) //skip dups
                            {
                                continue;
                            }
                            
                            if( normalBinarySearch(holdlist1, 0, numElementsList1, currElement) != -1 ) //if the item is on the other list, add to new
                            {
                                pointsToList->insertToDoubly(currElement);  //inserts to the indicated list
                                //pointsToCounter++;  //updates the appropriate counter
                                newVar++;
                                
                            }
                            
                            prevWord = holdlist2[i];
                            
                        }
                        
                        
                    }
                    
                    *pointsToCounter = newVar;   //we update the value that of the appropriate counter by setting it equal to the newVar counter
                    
                    
                    /////if temp1inList == true, put temp2 in stack, add the list to a newArray, then add to global list
                    
                    if(temp1InList == true) //if temp is in stack, then the original linked list is not empty
                    {
                        // << "temp is in doublyList so temp2 array being added to stack and global list" << endl;
                        postStack.push("temp2");
                        //backupCounterNumElements = *pointsToCounter;
                        backUpDoublyList = *pointsToList;
                        backUpDoublyList.addToGlobalList("temp2", backupCounterNumElements); //adds this new array to list
                        backUpDoublyList.destroyList();
                        backupCounterNumElements = 0;
                        // << backupCounterNumElements << " tempInList" << endl;
                        
                        
                    }
                    else
                    {
                        //doublyList.reversePrint();
                        postStack.push("temp");
                        //newArrayNumElements = *pointsToCounter;
                        doublyList = *pointsToList;
                        /// << newArrayNumElements << " elese" << endl;
                        
                    }
                    
                    
                    //pointsToList = NULL;
                    //pointsToCounter = NULL;
                    
                    
                }
                else if(list2 == "temp") //if list2 is the one holding the temp var name
                {
                    
                    
                    while(current != NULL && counter != 1)  //while loop loops through Lists of Lists
                    {
                        
                        if(current->nameOfArray == list1)
                        {
                            counter++;
                            holdlist1 = current->addressOfArray; //this pointer will be equal to the array of list 1's name pretty much
                            numElementsList1 = current->numberOfElements;
                            
                        }
                        
                        current = current->nextGlobal;

                        
                    }
                    
                    if(counter != 1)  //if the expression contains a non existant variable
                    {
                        doublyList.destroyList();
                        return "non-existant";
                    }
                    
                    counter = 0;
      
                    string *tempArray = new string[newArrayNumElements];
                    nodeType *tempTraverser = first;
                    int tempCounter = 0;
                    
                    while(tempTraverser != NULL)  //we will make the doubly list into an array
                    {
                        tempArray[tempCounter] = tempTraverser->info;
                        
                        tempTraverser = tempTraverser->nextLink;
                        
                        tempCounter++;
                        
                    }
                    
                    doublyList.destroyList();
                    quickSortBegin(tempArray, newArrayNumElements);
                    
                    
                    
                    string currElement;
                    string prevWord = "";
                    tempCounter = 0;
                    
                    if(numElementsList1 <= newArrayNumElements) //we want to use the smaller list as the basis for mult, if list1 is smaller
                    {
                        for (int i = 0; i < numElementsList1; i++)  //go through every word
                        {
                            currElement = holdlist1[i];
                            
                            if(currElement == prevWord) //skip dups
                            {
                                continue;
                            }
                            
                            if( normalBinarySearch(tempArray, 0, newArrayNumElements, currElement) != -1 ) //if the item is on the other list, add to new
                            {
                                doublyList.insertToDoubly(currElement);  //inserts to the indicated list
                                tempCounter++;  //updates the appropriate counter
                                
                            }
                            
                            prevWord = holdlist1[i];
                            
                        }
                        
                        
                        
                    }else  //if numElementsList1 > newArrayNumElements
                    {
                        for (int i = 0; i < newArrayNumElements; i++)  //go through every word
                        {
                            currElement = tempArray[i];
                            
                            if(currElement == prevWord) //skip dups
                            {
                                continue;
                            }
                            
                            if( normalBinarySearch(holdlist1, 0, numElementsList1, currElement) != -1 ) //if the item is on the other list, add to new
                            {
                                doublyList.insertToDoubly(currElement);  //inserts to the doubly list
                                tempCounter++;  //updates the  counter
                                
                            }
                            
                            prevWord = tempArray[i];
                            
                        }
                        
                        
                    }
                    
                    
                    newArrayNumElements = tempCounter;  //set this back to the new size of the doubly
                    
                    
                    delete [] tempArray;
                    tempArray = NULL;
                    
                    postStack.push("temp");
                    
                    
                    
                    
                }
                else  //if list1 is the one holding the temp var name
                {
                    
                    while(current != NULL && counter != 1)  //while loop loops through Lists of Lists
                    {
                        
                        if(current->nameOfArray == list2)
                        {
                            counter++;
                            holdlist2 = current->addressOfArray; //this pointer will be equal to the array of list 1's name pretty much
                            numElementsList2 = current->numberOfElements;
                            
                        }
                        
                        current = current->nextGlobal;

                        
                    }
                    
                    if(counter != 1)  //if the expression contains a non existant variable
                    {
                        doublyList.destroyList();
                        return "non-existant";
                    }
                    
                    counter = 0;
                    
                    string *tempArray = new string[newArrayNumElements];
                    nodeType *tempTraverser = first;
                    int tempCounter = 0;
                    
                    while(tempTraverser != NULL)  //we will make the doubly list into an array
                    {
                        tempArray[tempCounter] = tempTraverser->info;
                        
                        tempTraverser = tempTraverser->nextLink;
                        
                        tempCounter++;
                        
                    }
                    
                    doublyList.destroyList();
                    quickSortBegin(tempArray, newArrayNumElements);
                    
                    
                    
                    string currElement;
                    string prevWord = "";
                    tempCounter = 0;
                    
                    if(numElementsList2 <= newArrayNumElements) //we want to use the smaller list as the basis for mult, if list1 is smaller
                    {
                        for (int i = 0; i < numElementsList2; i++)  //go through every word
                        {
                            currElement = holdlist2[i];
                            
                            if(currElement == prevWord) //skip dups
                            {
                                continue;
                            }
                            
                            if( recBinarySearch(tempArray, 0, newArrayNumElements, currElement) != -1 ) //if the item is on the other list, add to new
                            {
                                doublyList.insertToDoubly(currElement);  //inserts to the indicated list
                                tempCounter++;  //updates the appropriate counter
                                
                            }
                            
                            prevWord = holdlist2[i];
                            
                        }
                        
                        
                        
                    }else  //if numElementsList2 > newArrayNumElements
                    {
                        for (int i = 0; i < newArrayNumElements; i++)  //go through every word
                        {
                            currElement = tempArray[i];
                            
                            if(currElement == prevWord) //skip dups
                            {
                                continue;
                            }
                            
                            if( recBinarySearch(holdlist2, 0, numElementsList2, currElement) != -1 ) //if the item is on the other list, add to new
                            {
                                doublyList.insertToDoubly(currElement);  //inserts to the doubly list
                                tempCounter++;  //updates the  counter
                                
                            }
                            
                            prevWord = tempArray[i];
                            
                        }
                        
                        
                    }
                    
                    
                    newArrayNumElements = tempCounter;  //set this back to the new size of the doubly
                    
                    
                    delete [] tempArray;
                    tempArray = NULL;
                    
                    postStack.push("temp");
                    

                }
            
            
        }
        else  //this is if word is an = sign
        {
                globalNodeType *current;
                current = globalFirst;
                string finalList = postStack.top();  //set this string to the name of the final list
                postStack.pop();
            
            
            
                ////the overwrite check must be done here, and use continue if overwrite is needed
            
            
            
                if(finalList == "temp")
                {
                    
                    if(LL.variableIsInList(nameOfVar) == true) //check if this var is already in global list, if so, delete it
                    {
                        LL.deleteThisArray(nameOfVar);
                        
                    }
                    
                    
                    doublyList.addToGlobalList(nameOfVar, newArrayNumElements); //adds the last item in the stack to globalList
                    
                }
                else  //if the equation calls for just 1 var (ex; R1 = R2; R4 = A, etc.)
                {
                    
                    if(LL.variableIsInList(nameOfVar) == true) //check if this var is already in global list. if so, delete it
                    {
                        LL.deleteThisArray(nameOfVar);
                        
                    }
                    
                    
                    while(current != NULL && counter != 1)  //while loop loops through Lists of Lists
                    {
                        
                        if(current->nameOfArray == finalList)
                        {
                            counter++;
                            holdlist1 = current->addressOfArray; //this pointer will be equal to the array of list 1's name pretty much
                            numElementsList1 = current->numberOfElements;
                            
                        }
                        
                        current = current->nextGlobal;

                        
                    }
                    
                    
                    
                    if(counter != 1)  //if the expression contains a non existant variable
                    {
                        doublyList.destroyList();
                        return "non-existant";
                    }
                    counter = 0;
                    
                    
                    for(int i = 0; i < numElementsList1; i++)
                    {
                        doublyList.insertToDoubly(holdlist1[i]);
                    }
                    
                    doublyList.addToGlobalList(nameOfVar, numElementsList1);
                    
                    
                    
                }
            
        }
        
        
        
    }
      //the postfix evaluationg is done (after the while loop is done)
    doublyList.destroyList();

    
    return "";
    
    
}







string evaluatePostfixStack::top()   //this will be used to do comparisons
{
    if(topOfStack == NULL)
    {
        return "empty"; //the operands will be getting compared so if its -1, DONT POP, just add
    } else {
        return topOfStack->operand;  //else we return its operand
    }
    
    
}



void evaluatePostfixStack::pop()   //delete the current top node
{
    evaluatePostfixNode *current;
    if(topOfStack != NULL)
    {
        current = topOfStack;   //curr node is equal to the stack top
        topOfStack = topOfStack->nextLink; //move stackTop to the node under it
        delete current;  //then we delete the current top node;
        
        
    } else {
        
        // << "Stack is empty, so nothing happened" << endl;
    }
    
    
    
}





void evaluatePostfixStack::push(string variable) //add to the top of the stack
{
    evaluatePostfixNode *newNode;
    
    newNode = new evaluatePostfixNode;
    
    newNode->operand = variable;
    newNode->nextLink = topOfStack;  //the nodes link will be pointing to the current top of the stack
    topOfStack = newNode;    //we make stackTop point to the new top node
    
    
}


