//
//  main.cpp
//  spellchecker
//
//  Created by Jeffry Sandoval on 10/13/17.
//  Copyright © 2017 Jeffry Sandoval. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"


string toLowercase(string lineToUncap);


void recSelectionSort(string *list, int first, int last);   //which is of O(n^2)
void swap(string *list, int element1, int element2);
int minimumsLocation(string *list, int start, int end);


int recSequentialSearch(string *listToSearch, int currPosition, int listSize, string searchItem);
int normalSequentialSearch(string *listToSearch, int start, int listSize, string searchItem);

int normalBinarySearch(string *listToSearch, int first, int length, string searchItem);
int recBinarySearch(string *listToSearch, int first, int length, string searchItem);



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
    bool searchTraversal(string element);
    void reversePrint();
    void destroyList();

};










using namespace std;

int main(int argc, char* argv[]) {
    
    
    if (argc < 2) {
        std::cerr << "Usage: spellchecker input=<input.txt>;dictionary=<dictionary.txt>;recursive=<y/n>" << std::endl;
        return -1;
    }
    
    ArgumentManager am(argc, argv);
    const std::string input_file_name = am.get("input");
    cout << "input file name is " << input_file_name << std::endl;
    const string dictionary_file_name = am.get("dictionary");
    cout << "dictionary file name is: " << dictionary_file_name << endl;
    
    bool isRecursive = true;  //by default, we do our searches recursively
    const string recursive_str = am.get("recursive");
    if(recursive_str[0] == 'n')
    {
        cout << "running non recursive" << endl;
        isRecursive = false;
    }
    
    if (isRecursive == true) {
        cout << "running recursively" << endl;
    }
    
    

    
    
    
    ofstream outStream;
    outStream.open("output.txt");
    ifstream dictStream;


    int dictCounter = 0;
    string currentWord;
    doublyLinkedList doublyList;
    first = NULL;
    bool dictIsEmpty = true;
    
    
    
    dictStream.open(dictionary_file_name);
    while(dictStream >> currentWord)   //look through the dict word by word
    {
        bool duplicateWord = false;    //by default, we say every word isnt a duplicate
        
        currentWord = toLowercase(currentWord);
        
        if(!isalpha(currentWord[0]))  //if the current word has a number, we skip it
        {
            continue;
        }
        
        
        if(first != NULL) //if first is not equal to NULL, then we check if this word is already in the dictionary
        {
            duplicateWord = doublyList.searchTraversal(currentWord); //this function returns true if this word is already in our linked list
            
        }
        
        if(duplicateWord == true)  //if the word is in the dictionary, then we skip over it and move to the next one
        {
            continue;
        }
        
        dictIsEmpty = false;  //if the list gets at least one word, we say dictionary file is not empty
        doublyList.insertToDoubly(currentWord);
        dictCounter++;
        
        
        
        
        
    }
    
    dictStream.close();
    
    if(dictIsEmpty == true)
    {
        cout << "no dictionary file" << endl;
        outStream << "" << endl;
        outStream.close();
        return 0;
        
    }
    
    
    
    
    
    
    
    
    
    
    
    string dictionaryArray[dictCounter];   //make an array of the size of the # of words that are in our lists
    nodeType *current = first;
    
    int counter = 0;
    
    
    while(current != NULL)     //adds the words in the nodes to the dictionary array
    {
        dictionaryArray[counter] = current->info;
        
        
        current = current->nextLink;
        
        
        counter++;
    }

    doublyList.destroyList();  //destroys the doubly linked list
    
    recSelectionSort(dictionaryArray, 0, dictCounter);          //use recursiveSelectionSort to sort the dictionary
    
    
    
    
    
    
    
    
    
    
    
    ifstream inStream;
    string currWord;
    doublyLinkedList newDoublyList;
    first = NULL;
    int inputCounter = 0;
    bool isEmpty = true;
    
    
    inStream.open(input_file_name);
    while(inStream >> currWord)    //process the input file word by word
    {
        
        currWord = toLowercase(currWord);
        
        if(!isalpha(currWord[0]))  //if the current word has a number, we skip it
        {
            continue;
        }
        
        isEmpty = false;  //we need at least one word to change this bool to false, stating that the list isnt empty
        
        
        newDoublyList.insertToDoubly(currWord);
        inputCounter++;
        
        
    }

    inStream.close();
    
    if(isEmpty == true)    //if the list didnt have any elements added to it, we output an empty string and end the program
    {
        outStream << "" << endl;
        outStream.close();
        return 0;
        
    }
    
    
    
    string inputArray[inputCounter];
    nodeType *thiscurrent = first;
    
    int iterator = 0;
    
    
    while(thiscurrent != NULL)     //adds the words in the nodes to the input array
    {
        inputArray[iterator] = thiscurrent->info;
        
        
        thiscurrent = thiscurrent->nextLink;
        
        
        iterator++;
    }
    
    newDoublyList.destroyList();  //destroys the doubly linked list

    
    recSelectionSort(inputArray, 0, inputCounter);  //sort the array that is holding the input words
    

    
    
    doublyLinkedList finalList;
    first = NULL;
    int number;
    
    for(int j = 0; j < inputCounter; j++) //iterate through each word in the array holding the input words, so as to search them
    {
        
        if(isRecursive == true)   //if the recursive arg is set to 'y', or if it isnt set at all, we run recursive search
        {
            number = recBinarySearch(dictionaryArray, 0, dictCounter, inputArray[j]);

        } else {                //if recursive arg is set to 'n', we run non recursive
            
            number = normalBinarySearch(dictionaryArray, 0, dictCounter, inputArray[j]);

            
        }
        
        
        
        
        
        if(number == -1)   //if the word isnt in the dictionary, we add it to a linkedList
        {
            finalList.insertToDoubly(inputArray[j]);
            
        }
        
        
        
    }
    
    
    
    
    
    
    
    
    
    int wordFreq = 1;
    string thisWord = "";
    
    
    
    nodeType *outputNode = first;
    while (outputNode != NULL)  //iterate through the final list so we can send the incorrectly spelled words and their frequency to an output file
    {
        
        if(outputNode->info == thisWord)   //if node's info(word) is the same as the prev word, increase the counter
        {
            wordFreq++;
            
        }else{          //if its a diff word, we output the word and its frequency, and set thisWord to the new word
                        //which is the nodes info, and reset the wordFreq to 1
            
            if(thisWord != "")   //we add this if function because originally the var thisWord is set to "", and we dont want to output that
            {
                outStream << thisWord << " " << wordFreq << endl;   //send thisWord to the output file
            }
            
            thisWord = outputNode->info;     //set thisWord to the current node's info(word)
            wordFreq = 1;                    //set wordFreq back to 1
            
            
        }
        
        
        if(outputNode->nextLink == NULL)  //if the next link is gonna be NULL, the while loop will end but before it does,
        {                                 //we want to output the last thisWord and its frequency
            
            outStream << thisWord << " " << wordFreq << endl;
        }
        
        
        
        outputNode = outputNode->nextLink;
    }

    
    
    outStream.close();
    
    
    finalList.destroyList();
    
    
    
    
    
    
    return 0;
    
}


////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


















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








////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////       **  Selection Sort  **             ////////////////////////////////





void recSelectionSort(string *list, int first, int last)
{

    int indexOfMin;
    
    indexOfMin = minimumsLocation(list, first, last);   //we get the index number where the smallest element is located
    
    swap(list, first, indexOfMin);          //we swap leftmost element with indexOfMine
    
    first++;
    
    if(first < last)    //if leftmost element is less than total # of elements in array, we use recursion
    {
        recSelectionSort(list, first, last);
    }

    
    
    
    
    
}



void swap(string *list, int element1, int element2) //swap element at first w element at seconf
{
    string temp = list[element1];          //temp holds the string thats in list[first] location
    list[element1] = list[element2];         //string at first location is replaced (swapped) with the string thats in list[second] locations
    list[element2] = temp;                //string at second location is replaced (swapped) with the string in temp
    
}





int minimumsLocation(string *list, int start, int end)
{
    int minIndex = start;
    
    
//    int current = start + 1;    /////might use this to make all of sort recursive in phase 2
//    if (current < end)
//    {
//        if( list[current].compare(list[minIndex]) < 0) //if curr element is smaller (comes first in alphabetical) than the minIndex
//        {
//            minIndex = current;
//            return minimumsLocation(list, minIndex, end);
//
//        } else {
//            return minimumsLocation(list, current, end);
//
//
//        }
//
//
//
//    } else {
//
//        return minIndex;
//    }
    
    
    for(int current = start + 1; current < end; current++)
    {
        if( list[current].compare(list[minIndex]) < 0) //if curr element is smaller (comes first in alphabetical) than the minIndex
        {
            minIndex = current;      //minIndex is set to curr Index
        }
    }
    
    
    
    return minIndex;
}








////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////















////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////        **  Non-Binary Sequential Searches   **             ////////////////////////



int recSequentialSearch(string *listToSearch, int currPosition, int listSize, string searchItem)
{
    if(currPosition == listSize) //returns -1 if the list doesnt find the item its looking for
        return -1;
    
    
    if(searchItem == listToSearch[currPosition])  //if item is in the list, we return the list's current position
    {
        return currPosition;
    }
    else {                      //if we have neither conditions, then we increment our currPosition and do recursion
        currPosition++;
        return recSequentialSearch(listToSearch, currPosition, listSize, searchItem);
        
    }
    
    
    
}





int normalSequentialSearch(string *listToSearch, int start, int listSize, string searchItem)
{
    for(int i = start; i < listSize; i++)
    {
        if(searchItem == listToSearch[i])  //if the item is in the list, we return its index
        {
            return start;
        }
        
        
    }
    
    
    return -1;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////










////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////        **  Binary Searches   **             ////////////////////////////////






int normalBinarySearch(string *listToSearch, int first, int length, string searchItem)
{
    int last = length - 1; //the number of the last element
    
    int middleElement;
    
    
    while(first <= last)
    {
        middleElement = (first + last) / 2;
        
        if(searchItem == listToSearch[middleElement])
        {
            return middleElement;
            
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





////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////















////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////        **  For Doubly Linked List Class   **             ////////////////////////




void doublyLinkedList::insertToDoubly(string theString)
{
    
    
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




////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////





















