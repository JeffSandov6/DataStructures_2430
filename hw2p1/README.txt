{\rtf1\ansi\ansicpg1252\cocoartf1504\cocoasubrtf830
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww14680\viewh7920\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs36 \cf0 * I have 2 classes and 2 structs*\
\

\b struct nodeType
\b0  is for my inner list. It is a doubly linked list node so each node has a prevLink and a nextLink and is of type string\
\

\b struct globalNodeType
\b0  is for my outer list of linked lists. It is a doubly linked list node so each node has a nextGlobal and a prevGlobal and is of type nodeType\
\
\

\b class doublyLinkedList
\b0  has 4 functions\
\
1. insertToDoubly(string theString) takes a string and adds it to a node at the end of the current list\
\
2. reversePrint() prints the nodes in reverse\
\
3. searchTraversal(string element) searches to see if the string used as an argument is in any of the nodes and it so, return a boolean == true\
\
4. outputToFile(ofstream& file) is just like reversePrint() except it outputs the nodes to the ofstream used as the argument\
\
\
\

\b class listOfLists
\b0  only has one function\
\
1. insertToLL(nodeType currentNode) takes in a node that is a complete list already, and adds that list to the outer List of Lists\
\
\
\
\
The entire inner doubly linked list is created as the inputFile is being parsed line by line in a while loop. Once each word has been added, entire list is added to the global List of Lists before the next iteration of the loop.\
\
As we\'92re outputting to an output text, we traverse each node in the global list, and per node, we traverse each inner list it contains.}