//
//  main.cpp
//  web
//
//  Created by Jeffry Sandoval on 12/4/17.
//  Copyright © 2017 Jeffry Sandoval. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <algorithm>
#include <vector>
#include "ArgumentManager.h"
#include <unordered_map>


using namespace std;


string formatLink(string linkName);

struct fileInfo
{
    string fileID;
    int inDegree;

};




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
    void forwardPrint();
    void reversePrint();
    bool searchTraversal(string element);
    void destroyList();
    bool isEmpty();
    
    nodeType* beginningOfList();  //returns the start of list if list isnt empt
    nodeType *head;
};


bool cmpIntsOfStructLowToHigh(const fileInfo &a, const fileInfo &b)   //for sorting vec of type fileInfo struct by indegree value from small to big
{
    return a.inDegree < b.inDegree;
    
    
};


bool cmpIntsOfStructHighToLow(const fileInfo &a, const fileInfo &b)   //for sorting vec of type fileInfo struct by indegree value from big to small
{
    return a.inDegree > b.inDegree;
    
    
};




int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: web script=input.script" << std::endl;
        return -1;
    }
    
    ArgumentManager am(argc, argv);
    const std::string script_name = am.get("script");
    cout << "script name is " << script_name << std::endl;
    
    
    
    
    
    
    ifstream inStream;
    string temp = "";
    
    inStream.open(script_name);  //from here we open the original file
    while (!inStream.eof())
    {
        getline(inStream, temp);    //only one line, temp gets the input scripts name
        // << temp << endl;
    }
    

    string fileListName = "";
    int elementOfApostrophe = 0;
    
    for(int i = 0; i < temp.length(); i++)  //this loop stops at the first apostrophe
    {
        if(temp[i] == 39)
        {
            elementOfApostrophe = i + 1;  //we set this int to the index of the first char after the first apostrophe
            break;
            
        }
        
    }
    
    
    while(temp[elementOfApostrophe] != 39)  //while loop stops when we reach second apostrophe
    {
        fileListName = fileListName + temp[elementOfApostrophe];
        elementOfApostrophe++;
        
    }
    
    
    
    
    
    ifstream fileList;
    string fileNames;
    doublyLinkedList doublyList;
    int fileCounter = 0;
    
    fileList.open(fileListName);  //parse through the file line by line
    while (fileList >> fileNames)
    {
        
        doublyList.insertToDoubly(fileNames); //the fileNames are all added to a doublyList
        fileCounter++;
        
    }
    
    
    
    
    
    unordered_map<string, int> fileIndexPair;           //creates a map w/ fileName as key, and int pair
    
    nodeType *graphArray = new nodeType[fileCounter];  //create an array of lists, w the counter specifying the size
    nodeType *current = doublyList.beginningOfList();
    int tempCounter = 0;
    
    vector<fileInfo> fileInDegree;  //holds the fileNames, along w their indegree value
    fileInDegree.reserve(fileCounter);
    
    while(current != NULL)
    {
        nodeType *newNode;                  //create a new node at each iteration w the file name as its info
        newNode = new nodeType;
        newNode->info = current->info;
        newNode->prevLink = NULL;
        newNode->nextLink = NULL;
        
        string currFile = current->info;  //the currfileName
        
        fileIndexPair.insert(make_pair(currFile, tempCounter) );  //adds the fileName and its position in array to unordered map
        
        graphArray[tempCounter] = *newNode;  //add the curr new node at its position in the array
        
        
        fileInDegree.push_back(fileInfo());  //fills the inDegree vector w struct
        fileInDegree[tempCounter].fileID = currFile;    //the fileName is added
        fileInDegree[tempCounter].inDegree = 0;         //as well as its inDegree value
        
        
        tempCounter++;
        current = current->nextLink;



    }
    
    doublyList.destroyList();
    


    
    
    
    unordered_map<string, int>::iterator iter;

    int totalNumOfEdges = 0;
    
    for(int i = 0; i < fileCounter; i++)
    {
        nodeType *tempNode;
        tempNode = &graphArray[i];      //set temp node equal to address of node at graphArray[i]
        
        
        string currFile = "";

        string openCurrFile = tempNode->info;

        
        ifstream openFiles;
        openFiles.open(openCurrFile);     //use the string to open the file
        
        if(openFiles.fail())                //condition for a in case a file doesn't open
        {
            // << "file isnt opening" << endl;
            continue;
            
        }
        
        
        string formattedLink;
        
        while (!openFiles.eof())   //open the curr file and parse it line by line, revealing its links
        {
            getline(openFiles, currFile);
            
            if(currFile[0] != '<')          //skip this line if its an invalid line (not a reference)
            {
                // << "invalid char" << endl;
                continue;
                
            }
            // << currFile << endl;
            
            formattedLink = formatLink(currFile);   //format the link name
            
            if(formattedLink == "invalid")
            {
                // << "invalid entry so we will skip it" << endl;
                continue;
            }
            
            // << "the formatted link is: " << formattedLink << endl;
            
            iter = fileIndexPair.find(formattedLink);
            
            if( iter == fileIndexPair.end() ) //if key doesnt exist
            {
                // << "the word isn't in the map" << endl;
                
                fileInDegree.push_back(fileInfo());                                          //add this file to the vector and start its indegree at 1
                fileInDegree[fileCounter].fileID = formattedLink;
                fileInDegree[fileCounter].inDegree = 1;
                
                fileIndexPair.insert(make_pair(formattedLink, fileCounter) );       //add this file to the unordered_map w its key being the new file and
                                                                                    //its value being the next filecounter value
                
                fileCounter = fileCounter + 1;   //then update the fileCounter
                
                
    
            } else  //if key is found
            {
                // << "the word is in the map" << endl;
                // << iter->first << " is the word and " << iter->second << " is its int value" << endl << endl;
                int positionInVec = iter->second;    //this returns the value of the word (its position in array and vec)
                
                fileInDegree[positionInVec].inDegree = fileInDegree[positionInVec].inDegree + 1;  //update the indegreeValue of the file we are linking to by 1
    
            }

            totalNumOfEdges = totalNumOfEdges + 1;
            
            ////////////////link the nodes
            
        }
        
        
        
    }
    
    

    sort(fileInDegree.begin(), fileInDegree.end(), cmpIntsOfStructHighToLow);  //this sorts the vector by inDegree values from high to low

    
    
    ofstream outStream;
    outStream.open("graph.txt");

    
    outStream << "n=" << fileCounter << endl;
    outStream << "m=" << totalNumOfEdges << endl;
    
    // << "n=" << fileCounter << endl;
    // << "m=" << totalNumOfEdges << endl;
    
    

    
    int prevSize = 0;
    int numOfFiles = 0;
    vector<string> top3;
    int currSize;
    string currentFile;
    
    for(int i = 0; i < fileInDegree.size(); i++)   //looking for top 3
    {
        currSize = fileInDegree[i].inDegree;
        currentFile = fileInDegree[i].fileID;
        
        if( (currSize == prevSize) || (numOfFiles < 3) )   //if currSize == prevSize, we still add to top3 vector, even if theres already 3 files
        {                                                   //if theres 2 files, we still add.
            top3.push_back(currentFile);
            
            prevSize = currSize;
            numOfFiles = numOfFiles + 1;
            continue;               //so long as these conditions are met, we continue in loop


        }
        
        break;          //if the if conditions aren't met, we must end the loop
        

    }
    
    
    sort(top3.begin(),top3.end());
    
    
    for(int j = 0; j < top3.size(); j++)
    {
        // << "top3=" << top3[j] << endl;
        outStream << "top3=" << top3[j] << endl;
        
    }
    
    
    
    
    int lastIndex = fileInDegree.size() - 1;
    
    
    while(fileInDegree[lastIndex].inDegree == 0 && lastIndex >= 0)   //while loop continues until indegree is no longer equal to 0
    {
        outStream << "isolated=" << fileInDegree[lastIndex].fileID << endl;

        // << "isolated=" << fileInDegree[lastIndex].fileID << endl;
        lastIndex = lastIndex - 1;
        
        
    }
    
    
 
    
    return 0;
}



///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////



string formatLink(string linkName)
{
    string returnWord = "";
    int elementOfQuotation = 0;
    int quotations = 0;
    
    for(int i = 0; i < linkName.length(); i++)
    {
        if(linkName[i] == 34) //if its equal to the first quotation mark
        {
            elementOfQuotation = i + 1; //set this int to the element after the first quotation
            quotations = quotations + 1;
            break;                      //and end loop
            
        }
    }
    
    
    for(int j = elementOfQuotation; j < linkName.length(); j++)
    {
        if(linkName[j] == 34)   //end loop at second quotation
        {
            quotations = quotations + 1;
            break;
        }
        
        returnWord = returnWord + linkName[j];  //add to the returnWord if valid
        
    }
    
    
    if(quotations == 2)   //the link is valid and we are returning a fileName
    {
        return returnWord;
        
    } else
        
    {
        return "invalid";
    }
    
    
    
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
    
    
    nodeType *newNode;
    newNode = new nodeType;
    newNode->info = theString;
    newNode->prevLink = NULL;
    newNode->nextLink = NULL;
    
    if (first == NULL) //if the list is empty, we insert newNode, and it is now the only one in list
    {
        first = newNode;
        last = newNode;
        head = newNode;
        
        
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




void doublyLinkedList::forwardPrint() {
    nodeType *traverse;
    
    traverse = first;   //our traverse pointer starts at the end
    
    while(traverse!= NULL)
    {
        cout << traverse->info << endl;
        traverse = traverse->nextLink;   //traverse then moves to the prevLink/Node to continue whileLoop
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


nodeType* doublyLinkedList::beginningOfList()
{
    return head;
    
    
}





