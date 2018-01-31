//
//  main.cpp
//  reverse
//
//  Created by Jeffry Sandoval on 9/19/17.
//  Copyright � 2017 Jeffry Sandoval. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"


string toLowercase(string lineToUncap);
string removeSeparators(string line);
bool checkIfEmpty(string checkLine);
string sepWordsAndNumbers(string sepLine);
string removeSpaces(string word);


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
    void removeNumberNodes();
};





struct globalNodeType   //my global nodes for linked list of linked list is of type nodeType(my inner node)
{
    nodeType globalInfo;
    globalNodeType *nextGlobal;
    globalNodeType *prevGlobal;
    
};
globalNodeType *globalFirst, *globalLast;


class listOfLists
{
public:
    void insertToLL(nodeType currentNode);
    //void LLreversePrint(doublyLinkedList currList);
};




using namespace std;

int main(int argc, char* argv[]) {
    
    
    if (argc < 2) {
        std::cerr << "Usage: reverse inputfile=input.txt;clean=<y/n>" << std::endl;
        return -1;
    }
    
    ArgumentManager am(argc, argv);
    const std::string input_file_name = am.get("inputfile");
    cout << "input file name is " << input_file_name << std::endl;
    bool clean = false;
    const string clean_str = am.get("clean");
    if (clean_str[0] == 'y') {
        clean = true;                ////so for phase 1 and 2, they will be based on, if clean = true, do the clean
        ////if clean = false, just do the normal one w numbers. Do this last
    }
    cout << "clean flag: " << clean << endl;
    
    
    ifstream inStream;
    ofstream outStream;
    string line = "";
    string temp = "";
    int Linecounter = 0;
    doublyLinkedList doublyList;
    listOfLists LL;
    globalFirst = NULL;
    bool emptyFile = true;
    
    
    
    inStream.open(input_file_name);
    while (!inStream.eof())
    {
        getline(inStream, temp); // we input the file line by line
        
        
        if (checkIfEmpty(temp) == true) // if theres an empty line we just skip it
        {
            continue;
        }
        
        emptyFile = false;  //if there's at least one non empty line, emptyFile == false
        
        
        line = toLowercase(temp);  //uncapitalize every capital letter
        
        
        string newLine = removeSeparators(line);   //removes anything that isnt a letter, number, or space
        
        ////should remove any spaces before
        
        string finalLine = sepWordsAndNumbers(newLine);  //separate the words and numbers in lines
        
        
        if (checkIfEmpty(finalLine) == true) // if there are any empty lines after undergoing all the processes, we once again skip over them
        {
            continue;
        }
        
        first = NULL;
        
        
        
        string addToNode = "";
        
        char b = 0;
        for(int i = 0; i < finalLine.size(); i++){
            char a = finalLine[i];
            int finalIter = (int)finalLine.size();
            int realFinal = finalIter - 1;
            
            if (a == 32)
            {
                b = 32;
            }
            
            
            if(a == 32) // && (addToNode != "") && b != 32)          // if current char is equal to a space, the word isnt empty and prev char wasnt a space
            {                                                    //we add the word to our list as a node
                
                doublyList.insertToDoubly(addToNode);
                
                addToNode = "";                 //reset the word
                
                
            }
            else {
                addToNode = addToNode + a;      //if the char isnt a space, then we add it to the current word
            }
            
            
            
            
            
            if(i == realFinal)                  //if i is the final iterator, then we add the current word to the beginning of the list
            {
                if (checkIfEmpty(addToNode) == true)
                {
                    continue;
                }
                
                doublyList.insertToDoubly(addToNode);
            }
            b = a;  //b will now be the previous char in every iteration
            
        }
        
        //traverse the list and delete any nodes w
        
        if(clean == true)  //if clean = y
        {
            doublyList.removeNumberNodes();

        }
        

        
        
        
        if(first == NULL)   //if our list becomes empty by removing our number nodes, then we skip this list
        {
            continue;
        }
        
        
        //add the linked list here to another list of linked lists
        
        Linecounter++;
        
        
        LL.insertToLL(*last);   // add the current line to List of Lists
        
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    inStream.close();
    
    
    outStream.open("output.txt");
    
    if (emptyFile == true)
    {
        outStream << "" << endl;
        
        outStream.close();
        return 0;
    }

    
    cout << "the number of lines is " << Linecounter << endl;
    int sizeOfNodes = 8 + 8 + sizeof(string);   //each pointer is 8 bytes and the size of each string is 24
    
    
    
    
    int newTotalNodes = 0;
    
    
    globalNodeType *current;
    current = globalLast;
    while(current != NULL)  //while loop loops through Lists of Lists
    {
        nodeType *traverse;
        traverse = &current->globalInfo;   //traverse(of doublyLinkedINNER) is put equal to each address of ListsofLists, in reverse order
        
        while(traverse != NULL)   //traverse loops through all nodes of the inner list in reverse
        {
            outStream << traverse->info << " ";
            newTotalNodes = newTotalNodes + 1;
            traverse = traverse->prevLink;
        }
        outStream << endl;
        current = current->prevGlobal;
        
        
        
    }
    
    outStream.close();
    
    cout << "the number of bytes is " << newTotalNodes * sizeOfNodes << endl;
    
    
    return 0;
    
    
}






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






string removeSeparators(string line)
{
    string newLine = "";
    bool previousWasSpace = false;
    
    
    bool spaceInFront = true;
    int spaceCounter = 0;
    
    while(spaceInFront == true)
    {
        char a = line[spaceCounter];
        
        if(a != 32)
        {
            spaceInFront = false;
            continue;
        }
        
        spaceCounter++;
        
    }
    
    
    
    for(int i = spaceCounter; i < line.size(); i++){
        char a = line[i];
        

        
        
        if(isalpha(a) || (a >= 48 && a <= 57))             //if current char is a letter or number (48-57 are ascii values of numbers)
        {                                                  //we add it to the string that we will be returning. else we just ignore the current character
            newLine = newLine + a;
            
        }else if(a == 32 && previousWasSpace == false){    //if current char is a space(32 ascii value) and the previous letter wasnt a space, we add it
            //to the string
            newLine = newLine + a;
            
        } else if(previousWasSpace == false)               //if current char isnt a letter, number or space, and the previous letter wasnt a space, we
        {                                                  //turn it into a space and add it to the string, which splits the left and right number
            a = 32;
            newLine = newLine + a;
        }
        
        
        
        if(a == 32)
        {
            previousWasSpace = true;
            
        } else {
            previousWasSpace = false;
        }
        
        
    }
    
    
    
    return newLine;
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









string sepWordsAndNumbers(string sepLine)
{
    string line = "";
    int emptyCounter = 0;
    
    for(int i = 0; i < sepLine.size(); i++) //first we run this for loop to see if the line has any spaces before any letters or numbers
    {                                       //once we get the first non space, we use that index number to start the actual line in the next loop
        char check = sepLine[i];
        if(check != 32)
        {
            emptyCounter = i;
            break;
        }
    }
    
    
    
    
    line = line + sepLine[emptyCounter];
    char space = 32;
    
    for(int i = emptyCounter +1; i < sepLine.size(); i++)
    {
        char current = sepLine[i];
        char previous = sepLine[i-1];
        
        if(current == 32 && previous != 32)   //if current char is just a space, and the previous wasnt, then we can add it and go to the next iteration in loop
        {
            line = line + current;
            continue;
        }
        
        
        if (current == 32 && previous == 32)  //if current char and previous char are spaces, we skip to the next iteration in loop
        {
            continue;
        }
        
        
        
        
        if(isalpha(current) && isalpha(previous)) // if current and previous character are both letters, we keep them together in a word
        {
            line = line + current;
            
        } else if( (isalpha(current) == false) && (isalpha(previous) == false) ) //if current and previous char are both numbers, we keep them together in a word
        {
            line = line + current;
        } else {
            
            if( previous != 32)
            {                          //if current and prev have a true/false combo, and prev wasnt a space, we add a space then add current next
                line = line + space;
                line = line + current;
            } else {
                line = line + current;   //if prev was a space, we just add the current word to the string
            }
        }
        
        
    }
    return line;
}





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
        cout << traverse->info << " ";
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







void doublyLinkedList::removeNumberNodes()
{
    nodeType *currentPosition;
    nodeType *previousPosition;
    
    currentPosition = first;        //current pointer is pointing at what first is pointing to
    //bool firstNodeDone = false;
    
    while(currentPosition != NULL)
    {
        char b = currentPosition->info[0];
        
        if(b >= 48 && b <= 57)   //if char b is a number
        {
            if(currentPosition->prevLink == NULL)  //if this is the first node in list
            {
                first = first->nextLink;            //we set first to the next node
                
                if(first != NULL)                   //if there is at least one item in the list, first prev pointer is NULL
                {
                    first->prevLink = NULL;
                }
                
                delete currentPosition;
                currentPosition = first;
                
            } else {
                previousPosition = currentPosition->prevLink;               ///previous position pointer is set to the previous node
                previousPosition->nextLink = currentPosition->nextLink;     //its next link points to the node after the one that going to be deleted
                
                
                
                if(currentPosition->nextLink != NULL)                       //if the nextLink isnt NULL
                {
                    currentPosition->nextLink->prevLink = previousPosition;   //the next node's prev link points at the previous position pointer's node
                }
                
                if(currentPosition == last)             //if node we are to delete is the last, then we move last pointer to the new position
                {
                    last = previousPosition;
                }
                
                
                delete currentPosition;
                currentPosition = previousPosition->nextLink;
                
                
            }
            

        } else {
            currentPosition = currentPosition->nextLink;
        }
        
        
        
        
    }
        
    
    
    
    
    return;
    
    
    
}














void listOfLists::insertToLL(nodeType currentNode)
{
    globalNodeType *newNode;
    newNode = new globalNodeType;
    newNode->globalInfo = currentNode;
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
