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
#include <algorithm>
#include <math.h>

int operationsCounter = 0;


string toLowercase(string lineToUncap);

void recQuickSortBegin(string *list, int size);
void recQuickSort(string *list, int first, int last);
int purelyIterateQuickSort(string *list, string pivot, int minIndex, int currIndex, int last);



void pureRecSelectionSort(string *list, int first, int last);   //which is of O(n^2)
int recursiveMinimumsLocation(string *list, int minIndex, int currElement, int end);

void recSelectionSort(string *list, int first, int last);   //which is of O(n^2)
void swap(string *list, int element1, int element2);
int minimumsLocation(string *list, int start, int end);

int recSequentialSearch(string *listToSearch, int currPosition, int listSize, string searchItem);
int normalSequentialSearch(string *listToSearch, int start, int listSize, string searchItem);

int normalBinarySearch(string *listToSearch, int first, int length, string searchItem);
int recBinarySearch(string *listToSearch, int first, int length, string searchItem);




double t_nForRecBinary(double n);
double t_nForNormalBinary(double n);
double bigOForBinary(int n);

long long int t_nForQuickSort(long long int n);
long long int bigOforQuickSort(long long int n);

long long int t_nForSelectionSort(long long int n);
long long int bigOForSelectionSort(long long int n);






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
        std::cerr << "Usage: spellchecker input=<input.txt>;dictionary=<dictionary.txt>;recursive=<y/n>;sort=<slow/fast>" << std::endl;
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

    bool sortSlow = true;  //by default we use a slow sort
    const string sort_Speed = am.get("sort");
    if(sort_Speed[0] == 'f')
    {
        cout << "we are using a fast sort" << endl;
        sortSlow = false;
    }

    if(sortSlow == true)
    {
        cout << "we are using a slow sort" << endl;
    }


    
    
    ofstream outStream;
    outStream.open("output.txt");
    ifstream dictStream;


    int dictCounter = 0;
    string currentWord;
    doublyLinkedList doublyList;
    first = NULL;
    bool dictIsEmpty = true;



    dictStream.open(dictionary_file_name);  //dictionary_file_name
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

    


    



    if(sortSlow == true)
    {
        recSelectionSort(dictionaryArray, 0, dictCounter);          //use recursiveSelectionSort to sort the dictionary
        //pureRecSelectionSort(dictionaryArray, 0, dictCounter);
    } else {
        recQuickSortBegin(dictionaryArray, dictCounter);

        //recQuickSort(dictionaryArray, 0, dictCounter);

    }

    

    
    
    


    ifstream inStream;
    string currWord;
    doublyLinkedList newDoublyList;
    first = NULL;
    int inputCounter = 0;
    bool isEmpty = true;


    inStream.open(input_file_name); //input_file_name
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
        cout << "hey" << endl;
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
    
 

    
    
    if(sortSlow == true)
    {
        recSelectionSort(inputArray, 0, inputCounter);          //use recursiveSelectionSort to sort the dictionary
        //pureRecSelectionSort(inputArray, 0, inputCounter);
    } else {
        recQuickSortBegin(inputArray, inputCounter);
        //recQuickSort(inputArray, 0, inputCounter);
        //recSelectionSort(inputArray, 0, inputCounter);
    }



    
    

    int wordFreq = 1;
    string thisWord = "";







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
                cout << thisWord << " " << wordFreq << endl;
            }

            thisWord = outputNode->info;     //set thisWord to the current node's info(word)
            wordFreq = 1;                    //set wordFreq back to 1


        }


        if(outputNode->nextLink == NULL)  //if the next link is gonna be NULL, the while loop will end but before it does,
        {                                 //we want to output the last thisWord and its frequency

            outStream << thisWord << " " << wordFreq << endl;
            cout << thisWord << " " << wordFreq << endl;
        }



        outputNode = outputNode->nextLink;
    }



    outStream.close();


    finalList.destroyList();

    
////////////////////////////////////////////// Time Complexity Tables //////////////////////////////////////////////

    //    ofstream outerStream;
    //    outerStream.open("time.txt");
    //
    //
    ////
    ////
    ////
    //
    //    outerStream << "NON-RECURSIVE BINARY SEARCH" << endl << endl;
    //
    //    outerStream << "T(n) = 5*log_2(n) + 3   O(log_2(n))" << endl;
    //    outerStream << "c = 6, n_0=10" << endl;
    //
    //
    //    outerStream << "n      #operations     T(n)        O(f(n))" << endl;
    //    outerStream << "-------------------------------------------------" << endl;
    //
    //
    //
    //    operationsCounter = 0;
    //    int n = 10;
    //
    //    string *numArray = new string[n];
    //
    //    for(int i = 0; i < n; i++)
    //    {
    //        numArray[i] = to_string(i);
    //
    //    }
    //
    //    normalBinarySearch(numArray, 0, 10, "z");
    //
    //
    //    outerStream << n << "      " << operationsCounter << "             " << t_nForNormalBinary(n) << "            " << bigOForBinary(n) << endl;
    //
    //    delete [] numArray;
    //
    //
    //
    //    operationsCounter = 0;
    //    n = 100;
    //
    //    string *numArray2 = new string[n];
    //
    //    for(int i = 0; i < n; i++)
    //    {
    //        numArray2[i] = to_string(i);
    //
    //    }
    //
    //    normalBinarySearch(numArray2, 0, 100, "z");
    //
    //
    //
    //
    //    outerStream << n << "      " << operationsCounter << "             " << t_nForNormalBinary(n) << "            " << bigOForBinary(n) << endl;
    //
    //
    //    delete [] numArray2;
    //
    //
    //
    //    operationsCounter = 0;
    //    n = 1000;
    //
    //    string *numArray3 = new string[n];
    //
    //    for(int i = 0; i < n; i++)
    //    {
    //        numArray3[i] = to_string(i);
    //
    //    }
    //
    //    normalBinarySearch(numArray2, 0, 1000, "z");
    //
    //
    //
    //
    //    outerStream << n << "      " << operationsCounter << "             " << t_nForNormalBinary(n) << "            " << bigOForBinary(n) << endl;
    //
    //
    //    delete [] numArray3;
    //
    //
    //
    //
    //
    //    operationsCounter = 0;
    //    n = 10000;
    //
    //    string *numArray4 = new string[n];
    //
    //    for(int i = 0; i < n; i++)
    //    {
    //        numArray4[i] = to_string(i);
    //
    //    }
    //
    //    normalBinarySearch(numArray4, 0, 10000, "z");
    //
    //
    //
    //
    //    outerStream << n << "      " << operationsCounter << "             " << t_nForNormalBinary(n) << "            " << bigOForBinary(n) << endl;
    //
    //
    //    delete [] numArray4;
    //
    //
    //
    //
    //
    //    operationsCounter = 0;
    //    n = 100000;
    //
    //    string *numArray5 = new string[n];
    //
    //    for(int i = 0; i < n; i++)
    //    {
    //        numArray5[i] = to_string(i);
    //
    //    }
    //
    //    normalBinarySearch(numArray5, 0, 100000, "z");
    //
    //
    //
    //
    //    outerStream << n << "      " << operationsCounter << "             " << t_nForNormalBinary(n) << "            " << bigOForBinary(n) << endl;
    //
    //
    //    delete [] numArray5;
    //
    //
    //
    /////////////////////////Recursive Binary/////////////////////////////
    //
    //
    //    outerStream << endl << endl;
    //    outerStream << "=================================================" << endl;
    //    outerStream << "=================================================" << endl;
    //
    //
    //    outerStream << "RECURSIVE BINARY SEARCH" << endl << endl;
    //
    //    outerStream << "T(n) = 5*log_2(n) + 1   O(log_2(n))" << endl;
    //    outerStream << "c = 6, n_0=10" << endl;
    //
    //
    //    outerStream << "n      #operations     T(n)        O(f(n))" << endl;
    //    outerStream << "-------------------------------------------------" << endl;
    //
    //
    //    operationsCounter = 0;
    //    n = 10;
    //
    //    string *recBinary = new string[n];
    //
    //    for(int i = 0; i < n; i++)
    //    {
    //        recBinary[i] = to_string(i);
    //
    //    }
    //
    //    recBinarySearch(recBinary, 0, n, "z");
    //
    //
    //
    //
    //    outerStream << n << "      " << operationsCounter << "             " << t_nForRecBinary(n) << "            " << bigOForBinary(n) << endl;
    //
    //
    //    delete [] recBinary;
    //
    //
    //
    //    operationsCounter = 0;
    //    n = 100;
    //
    //    string *recBinary2 = new string[n];
    //
    //    for(int i = 0; i < n; i++)
    //    {
    //        recBinary2[i] = to_string(i);
    //
    //    }
    //
    //    recBinarySearch(recBinary2, 0, n, "z");
    //
    //
    //
    //
    //    outerStream << n << "      " << operationsCounter << "             " << t_nForRecBinary(n) << "            " << bigOForBinary(n) << endl;
    //
    //    delete [] recBinary2;
    //
    //
    //
    //
    //
    //
    //
    //
    //    operationsCounter = 0;
    //    n = 1000;
    //
    //    string *recBinary3 = new string[n];
    //
    //    for(int i = 0; i < n; i++)
    //    {
    //        recBinary3[i] = to_string(i);
    //
    //    }
    //
    //    recBinarySearch(recBinary3, 0, n, "z");
    //
    //
    //
    //
    //    outerStream << n << "      " << operationsCounter << "             " << t_nForRecBinary(n) << "            " << bigOForBinary(n) << endl;
    //
    //    delete [] recBinary3;
    //
    //
    //
    //
    //
    //
    //
    //    operationsCounter = 0;
    //    n = 10000;
    //
    //    string *recBinary4 = new string[n];
    //
    //    for(int i = 0; i < n; i++)
    //    {
    //        recBinary4[i] = to_string(i);
    //
    //    }
    //
    //    recBinarySearch(recBinary4, 0, n, "z");
    //
    //
    //
    //
    //    outerStream << n << "      " << operationsCounter << "             " << t_nForRecBinary(n) << "            " << bigOForBinary(n) << endl;
    //
    //
    //
    //
    //
    //    operationsCounter = 0;
    //    n = 100000;
    //
    //    string *recBinary5 = new string[n];
    //
    //    for(int i = 0; i < n; i++)
    //    {
    //        recBinary5[i] = to_string(i);
    //
    //    }
    //
    //    recBinarySearch(recBinary5, 0, n, "z");
    //
    //
    //
    //
    //    outerStream << n << "      " << operationsCounter << "             " << t_nForRecBinary(n) << "            " << bigOForBinary(n) << endl;
    //
    //    delete [] recBinary5;
    //
    //
    //
    //
    //    ///////////////////////Purely Recursive Selection Sort/////////////////////////////
    //
    //
    //    outerStream << endl << endl;
    //    outerStream << "=================================================" << endl;
    //    outerStream << "=================================================" << endl;
    //
    //
    //    outerStream << "PURELY RECURSIVE SELECTION SORT" << endl << endl;
    //
    //    outerStream << "T(n) = 12n^2 - 1    O(n^2))" << endl;
    //    outerStream << "c = 12, n_0= 6" << endl;
    //
    //
    //    outerStream << "n      #operations     T(n)        O(f(n))" << endl;
    //    outerStream << "-------------------------------------------------" << endl;
    //
    //
    //
    //    operationsCounter = 0;
    //    long long int n1 = 10;
    //    string *selecSort = new string[n1];
    //
    //    for(int i = 0; i < n1; i++)
    //    {
    //        selecSort[i] = to_string(i);
    //    }
    //
    //    random_shuffle(&selecSort[0], &selecSort[n1]);
    //
    //    pureRecSelectionSort(selecSort, 0, 10);
    //    outerStream << n1 << "      " << operationsCounter << "             " << t_nForSelectionSort(n1) << "            " << bigOForSelectionSort(n1) << endl;
    //
    //
    //    delete [] selecSort;
    //
    //
    //
    //
    //    operationsCounter = 0;
    //    n1 = 100;
    //    string *selecSort2 = new string[n1];
    //
    //    for(int i = 0; i < n1; i++)
    //    {
    //        selecSort2[i] = to_string(i);
    //    }
    //
    //    random_shuffle(&selecSort2[0], &selecSort2[n1]);
    //
    //    pureRecSelectionSort(selecSort2, 0, 100);
    //
    //    outerStream << n1 << "      " << operationsCounter << "             " << t_nForSelectionSort(n1) << "            " << bigOForSelectionSort(n1) << endl;
    //
    //
    //    delete [] selecSort2;
    //
    //
    //
    //
    //    operationsCounter = 0;
    //    n1 = 1000;
    //    string *selecSort3 = new string[n1];
    //
    //    for(int i = 0; i < n1; i++)
    //    {
    //        selecSort3[i] = to_string(i);
    //    }
    //
    //    random_shuffle(&selecSort3[0], &selecSort3[n1]);
    //
    //    pureRecSelectionSort(selecSort3, 0, 1000);
    //
    //    outerStream << n1 << "      " << operationsCounter << "             " << t_nForSelectionSort(n1) << "            " << bigOForSelectionSort(n1) << endl;
    //
    //
    //    delete [] selecSort3;
    //
    //
    //
    //
    //
    //
    //    operationsCounter = 0;
    //    n1 = 10000;
    //    string *selecSort4 = new string[n1];
    //
    //    for(int i = 0; i < n1; i++)
    //    {
    //        selecSort4[i] = to_string(i);
    //    }
    //
    //    random_shuffle(&selecSort4[0], &selecSort4[n1]);
    //
    //    pureRecSelectionSort(selecSort4, 0, 10000);
    //
    //    outerStream << n1 << "      " << operationsCounter << "             " << t_nForSelectionSort(n1) << "            " << bigOForSelectionSort(n1) << endl;
    //
    //
    //    delete [] selecSort4;
    //
    //
    ////
    ////
    ////
    ////    operationsCounter = 0;
    ////    n1 = 100000;
    ////    string *selecSort5 = new string[n1];
    ////
    ////    for(int i = 0; i < n1; i++)
    ////    {
    ////        selecSort5[i] = to_string(i);
    ////    }
    ////
    ////    random_shuffle(&selecSort5[0], &selecSort5[n1]);
    ////
    ////    pureRecSelectionSort(selecSort5, 0, 100000);
    ////
    ////    outerStream << n1 << "      " << operationsCounter << "             " << t_nForSelectionSort(n1) << "            " << bigOForSelectionSort(n1) << endl;
    ////
    ////
    ////    delete [] selecSort5;
    //
    //
    //
    //
    //
    //
    //
    //
    //    ///////////////////////Purely Recursive Quick Sort/////////////////////////////
    //
    //
    //    outerStream << endl << endl;
    //    outerStream << "=================================================" << endl;
    //    outerStream << "=================================================" << endl;
    //
    //
    //    outerStream << "PURELY RECURSIVE QUICK SORT" << endl << endl;
    //
    //    outerStream << "T(n) = 3 + (4n)(7log_2(n)    O(nlog_2(n))" << endl;
    //    outerStream << "c = 29, n_0= 4" << endl;
    //
    //
    //    outerStream << "n      #operations     T(n)        O(f(n))" << endl;
    //    outerStream << "-------------------------------------------------" << endl;
    //
    //
    //
    //
    //
    //
    //    operationsCounter = 0;
    //    n1 = 10;
    //    string *quickSort = new string[10000];
    //
    //    for(int i = 0; i < n1; i++)
    //    {
    //        quickSort[i] = to_string(i);
    //    }
    //
    //    random_shuffle(&quickSort[0], &quickSort[n1]);
    //
    //    recQuickSort(quickSort, 0, 10);
    //
    //    outerStream << n1 << "      " << operationsCounter << "             " << t_nForQuickSort(n1) << "            " << bigOforQuickSort(n1) << endl;
    //
    //
    //    delete [] quickSort;
    //
    //
    //
    //
    //    operationsCounter = 0;
    //    n1 = 100;
    //    string *quickSort1 = new string[n1];
    //
    //    for(int i = 0; i < n1; i++)
    //    {
    //        quickSort1[i] = to_string(i);
    //    }
    //
    //    random_shuffle(&quickSort1[0], &quickSort1[n1]);
    //
    //    recQuickSort(quickSort1, 0, 100);
    //
    //    outerStream << n1 << "      " << operationsCounter << "             " << t_nForQuickSort(n1) << "            " << bigOforQuickSort(n1) << endl;
    //
    //
    //
    //
    //    delete [] quickSort1;
    //
    //
    //
    //    operationsCounter = 0;
    //    n1 = 1000;
    //    string *quickSort3 = new string[1000];
    //
    //    for(int i = 0; i < n1; i++)
    //    {
    //        quickSort3[i] = to_string(i);
    //    }
    //
    //    random_shuffle(&quickSort3[0], &quickSort3[n1]);
    //
    //    recQuickSort(quickSort3, 0, 1000);
    //
    //    outerStream << n1 << "      " << operationsCounter << "             " << t_nForQuickSort(n1) << "            " << bigOforQuickSort(n1) << endl;
    //
    //
    //
    //    delete [] quickSort3;
    //
    //
    //
    //
    //
    //
    ////    operationsCounter = 0;
    ////    n1 = 10000;
    ////    string *quickSort4 = new string[10000];
    ////
    ////    for(int i = 0; i < n1; i++)
    ////    {
    ////        quickSort4[i] = to_string(i);
    ////    }
    ////
    ////    random_shuffle(&quickSort4[0], &quickSort4[n1]);
    ////
    ////    recQuickSort(quickSort4, 0, 10000);
    ////    //recQuickSortBegin(quickSort4, 10000);
    ////
    ////    outerStream << n1 << "      " << operationsCounter << "             " << t_nForQuickSort(n1) << "            " << bigOforQuickSort(n1) << endl;
    ////
    ////
    ////    delete [] quickSort4;
    //
    ////
    ////
    ////
    ////
    ////    operationsCounter = 0;
    ////    n1 = 100000;
    ////    string *quickSort5 = new string[100000];
    ////
    ////    for(int i = 0; i < n1; i++)
    ////    {
    ////        quickSort5[i] = to_string(i);
    ////    }
    ////
    ////    random_shuffle(&quickSort5[0], &quickSort5[n1]);
    ////
    ////    recQuickSort(quickSort5, 0, 100000);
    ////
    ////    outerStream << n1 << "      " << operationsCounter << "             " << t_nForQuickSort(n1) << "            " << bigOforQuickSort(n1) << endl;
    ////
    ////
    ////
    ////    delete [] quickSort5;
    //
    //


//
//
//
    
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
    
    

    
    
    for(int current = start + 1; current < end; current++)
    {
        if( list[current].compare(list[minIndex]) < 0) //if curr element is smaller (comes first in alphabetical) than the minIndex
        {
            minIndex = current;      //minIndex is set to curr Index
        }
    }
    
    
    
    return minIndex;
}


///////////////////////////////////PurelyRecursive SelectionSort///////////////////////////////////////////////




void pureRecSelectionSort(string *list, int first, int last)   //which is of O(n^2)
{
    int indexOfMin;
    
    indexOfMin = recursiveMinimumsLocation(list, first, first+1, last);   //we get the index number where the smallest element is located
    
    swap(list, first, indexOfMin);          //we swap leftmost element with indexOfMine
    
    first++;
    
    if(first < last)    //if leftmost element is less than total # of elements in array, we use recursion
    {
        //////cout << "purely" << endl;

        pureRecSelectionSort(list, first, last);
    }
}



int recursiveMinimumsLocation(string *list, int minIndex, int currElement, int end)
{

    if (currElement < end)
    {
        if( list[currElement].compare(list[minIndex]) < 0) //if curr element is smaller (comes first in alphabetical) than the minIndex
        {
            minIndex = currElement;
            return recursiveMinimumsLocation(list, minIndex, currElement+1, end);

        } else {
            return recursiveMinimumsLocation(list, minIndex, currElement+1, end);


        }



    } else {
        ////cout << "recursive" << endl;
        return minIndex;
        
    }




}






////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////











////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////    ** Quick Sort **      //////////////////////////////////////////



void recQuickSortBegin(string *list, int size)
{
    recQuickSort(list, 0, size - 1);
    
    
    
}





void recQuickSort(string *list, int first, int last)
{
    
    
    if(first < last)
    {
        int pivot = (first+last) / 2; //func
        string currPivot = list[pivot];
        swap(list, first, pivot);
        int pivotLocation = purelyIterateQuickSort(list, currPivot, first, first + 1, last);
        
        swap(list, first, pivotLocation);
        
        
        recQuickSort(list, first, pivotLocation - 1);
        recQuickSort(list, pivotLocation + 1, last);
        
        
    }
    
    
    
    
}



int purelyIterateQuickSort(string *list, string pivot, int minIndex, int currIndex, int last)
{
    if(currIndex <= last)
    {
        if( list[currIndex].compare(pivot) < 0) //if curr element is smaller (comes first in alphabetical) than the pivot
        {
            minIndex = minIndex + 1;
            swap(list, minIndex, currIndex);
            return purelyIterateQuickSort(list, pivot, minIndex, currIndex + 1, last);
            
        } else {
            
            return purelyIterateQuickSort(list, pivot, minIndex, currIndex + 1, last);
            
        }
        
    } else
    {
        return minIndex;
        
    }
    
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
    int last = length - 1; //the number of the last element   //line 1
    operationsCounter++;
    
    int middleElement;              //line 2
    operationsCounter++;
    
    
    operationsCounter++; // for the first comparison of the while loop
    while(first <= last)    //line 3
    {

        middleElement = (first + last) / 2;    //line 4
        operationsCounter++;
        if(searchItem == listToSearch[middleElement])       //line 5
        {
            operationsCounter++;
            return middleElement;       //line 6
            
        } else if(searchItem.compare(listToSearch[middleElement]) > 0)  { //if searchItem comes after middleElement alphabetically
            operationsCounter = operationsCounter + 2;
            first = middleElement + 1;
            operationsCounter++;
            
        } else { //.compare will return less than 0 if searchItem comes before middleElement alphabetically
            operationsCounter = operationsCounter + 2;
            last = middleElement - 1;
            operationsCounter++;
        }
        operationsCounter++;   //for the next comparison of the while loop. itll add one even in the last case
    }
    
    
    return -1;
}


/////////////////////////////////////  ** Recursive Binary //////////////////////////////////////


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











double t_nForNormalBinary(double n)
{
    return 5* log2(n) + 3;
    
}

double bigOForBinary(int n)
{
    return 6 * log2(n);
    
    
}

double t_nForRecBinary(double n){
    
    return 5*log2(n) + 1;
    
}


long long int t_nForQuickSort(long long int n)
{
    long long int usingN = (4*n) * (7 * log2(n));
    
    return usingN + 3;
    
}


long long int bigOforQuickSort(long long int n)
{
    
    return 29 * (n * log2(n));
    
}

long long int t_nForSelectionSort(long long int n)
{
    long squareN = n * n;
    
    return (12 * squareN) + 1;
    
    
}





long long int bigOForSelectionSort(long long int n)
{
    return 12 * (n * n);
}














