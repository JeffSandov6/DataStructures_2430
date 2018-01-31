//
//  main.cpp
//  topword
//
//  Created by Jeffry Sandoval on 8/27/17.
//  Copyright © 2017 Jeffry Sandoval. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"

using namespace std;


string toLowercase(string wordToUncap);
bool isFirstInAlphabetical(string word1, string word2);


int main(int argc, char* argv[]) {
    
    
    string holdsWords[150];
    int wordCounter = 0;
    
    
    if (argc < 2) {
        std::cerr << "Usage: topword inputfile=input.txt" << std::endl;
        return -1;
    }
    
    ArgumentManager am(argc, argv);
    const std::string input_file_name = am.get("inputfile");
    cout << "input file name is " << input_file_name << std::endl;
    
    
    
    
    ifstream inStream;
    ofstream outStream;
    
    
    string currentWord;
    
    
    
    inStream.open(input_file_name);    
    for (int i = 0; (inStream >> currentWord) && (i < 150); i++)    //this for loop iterates through the file, word by word and adds to the array
    {
        
        string word = toLowercase(currentWord);

        holdsWords[wordCounter] = word;
        
        
        wordCounter++;
    
    }
    
    inStream.close();
    

    
    
    
    
    
    string checkForEmpty = "";
    for (int i = 0; i < 150; i++)   //this for loop checks to see if the file was empty by going through all the indexes to check if theyre all empty
    {
        
        if (holdsWords[i] == "")
        {
            continue;
            
        } else {
            checkForEmpty = "not empty";    //if at any point one of the indexes has something other than an empty string, we change checkForEmpty to "not empty"
                                            //and then we end the entire for loop
            break;
        }
        
        
        
    }
    
    
    
    if (checkForEmpty != "not empty")    //if the string check for empty isnt "not empty", then we open and output.txt, add an empty string to it and end the program
    {
        outStream.open("output.txt");
        
        outStream << "" << endl;
        
        outStream.close();
        
        return 0;
        
        
    }
    
    
    
    
    

    
    
    
    string holdingWord = "";
    string correctWords[150];
 
    string newWord = "";
    string letter = "";
    int newCounter = 0;
    
    for (int newIter = 0; newIter < wordCounter; newIter++)
    {
        holdingWord = holdsWords[newIter];
        
        for (int i = 0; i < holdingWord.length(); i++)
        {
            letter = holdingWord[i];
           
            if (isalpha(holdingWord[i])) { //if the current char is alphabetical, we add it to the newWord string
                
                newWord = newWord + letter;
                
            } else if (newWord != "") { //if the current char isnt alphabetical and newword isnt empty, we add what we have of new word as of now to the new array, and
                                        //reset newWord to an empty string so we split off any chars that arent letters from the string
                
                
                correctWords[newCounter] = newWord;
                newCounter++;
                newWord = "";
                letter = "";
                
            } else {
                continue;
            }
            
            
            
        }
        
        if (newWord != "") { // if newWord isnt emptyv after the loop of the current word is over, then we add it to the array and reset newWord to an empty string once again
            correctWords[newCounter] = newWord;
            newCounter++;
            newWord = "";
        }
        
        
        
    }
    
    
    

    

    
   
    
    
    int i = 0;
    int j = 0;
    int maxcount = 0;
    string freqWords[newCounter];
    int freqCounter = 0;
    
    for (i = 0; i < newCounter; i++)
    {
        string thisword = correctWords[i];
        int counter = 0;
        
        
        for (j = i; j < newCounter; j++)   //iterate through each word
        {
            string matchWord = correctWords[j];
            
            if (thisword == matchWord) {  //if this word matches another in the array, we increase the counter by 1
                counter++;
            }
            
            
        }

        
        if (counter > maxcount) {  //if the count of the current word is bigger than the current most frequent word, it is added as the first element in the array
                                    //and the max count is also set to this word's count

            freqWords[0] = thisword;
            freqCounter = 0;
        
            maxcount = counter;
            

        } else if (counter < maxcount) {   //if count is less than current count, just continue
            continue;
        
        } else {
            
            freqCounter++;
            freqWords[freqCounter] = thisword;
                                                // if count and max count is equal, we add it to the array in the next available element
            
        }
        
        
    }


    

    
    
    
    freqCounter = freqCounter + 1;
    int iter = 0;
    int compIter = 0;
    int wordIndex = 0;
    
    string lastArray[freqCounter];   //this array holds the frequent words alphabetically
    

    for (iter = 0; iter < freqCounter; iter++)
    {
        string firstWord = freqWords[iter];
        wordIndex = iter;

        
        
        for (compIter = 0; compIter < freqCounter; compIter++) //we compare all the words in the old array with each other
        {
            string compWord = freqWords[compIter];
            
            if (firstWord == compWord)       //if the words match, we just continue, but add it to the current array position
            {
                lastArray[iter] = firstWord;
                continue;
            }
            
            
            
            if (isFirstInAlphabetical(firstWord, compWord))     //if the current word we're comparing comes first, we add it to the current array position and continue
            {
                lastArray[iter] = firstWord;
                
                
                
            } else {                                    //if the second word come first, we return false and add this word to the current array position, change it to the first word and continue
                                                        //word index records the current position of the word in the freqWords array
                
                
                lastArray[iter] = compWord;
                firstWord = compWord;
                wordIndex = compIter;
                
                
            }
            
            
 
        }
        
        freqWords[wordIndex] = "zzzzzzzzzzzzzzzzzzzzzzzzz";     //we use the index of the word we added to the new array, to "delete" it from the old array by making its alpha values all zs

        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    outStream.open("output.txt");

    string amount = to_string(maxcount);
    int lastIterator = 0;
    for (lastIterator = 0; lastIterator < freqCounter; lastIterator++)
    {
        
        outStream << lastArray[lastIterator] << ":" << amount << endl;

    }
    
    outStream.close();


    return 0;
}









bool isFirstInAlphabetical(string word1, string word2)
{
    string firstWord = "";
    
    for (int i = 0; word1.length(); i++)
    {
        char word1Char = word1[i];
        char word2Char = word2[i];
        
        if (tolower(word1Char) < tolower(word2Char)) //char of wordChar comes first alphabetically, determined by ASCII number being lower
        {
            firstWord = word1;
            break;
            
            
        } else if (tolower(word1Char) > tolower(word2Char)) //char of compWordChar comes first alphabetically, determined by ASCII num being lower
        {
            
            firstWord = word2;
            
            break;
            
        } else //the chars are equal
        {
            continue;
            
        }
        
        
        
    }
    
    if (firstWord == word1)   //if word1 comes first, we return true
    {
        return true;
    } else {
        return false;
    }
    
    
}








string toLowercase(string wordToUncap)
{
    string newWord = "";
    int i = 0;
    char b;
    for (i = 0; i < wordToUncap.size(); i++)
    {
        char a = wordToUncap[i];
        
        if (a < 65 || a > 89) //the ascii decimal numbers for capital letters range from 65 to 89, so if they aren't in that range, the character stays as is
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






