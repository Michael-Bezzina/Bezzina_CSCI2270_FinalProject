#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "Final.h"

using namespace std;

Final::Final()  //sets all tables to NULL
{
    for(int i=0;i<tableSize;i++){
        hashTable[i] = NULL;
    }

    for(int i=0;i<tableSize;i++){
        hashTable2[i] = NULL;
    }

    for(int i=0;i<tableSize;i++){
        hashTable3[i] = NULL;
    }

    for(int i=0;i<tableSize;i++){
        hashTable4[i] = NULL;
    }
}

Final::~Final()
{
    //dtor
}

int Final::hashSum1(string x, int y){   //hash function
    int sum = 0;
    for(int i=0;i<x.size();i++){
        sum = sum + static_cast<int>(x[i]);
    }
    if(y != 0){
        sum = sum % y;
    }
    else{
        sum = sum % 1;
    }
    return sum;
}

void Final::addNames(string first,string second){ //makes two hash tables of first and last names
    HashElem* firstName = new HashElem();
    firstName->name = first;
    HashElem* lastName = new HashElem();
    lastName->name = second;

    int key1 = hashSum1(first,tableSize);   //runs first name through hash function
    int key2 = hashSum1(second,tableSize);  //runs last name through hash function

    HashElem* curr = hashTable[key1];   //uses key to place in first hash table
    if(hashTable[key1] == NULL){
        hashTable[key1] = firstName;
    }
    else{
        if(curr->next != NULL){
            while(curr->next != NULL){
                curr = curr->next;
            }
            curr->next = firstName;
            firstName->previous = curr;
        }
        else{
            curr->next = firstName;
            firstName->previous = curr;
        }
    }

    HashElem* curr2 = hashTable2[key2]; //uses key to place in second hash table
    if(curr2 == NULL){
        hashTable2[key2] = lastName;
    }
    else{
        if(curr2->next != NULL){
            while(curr2->next != NULL){
                curr2 = curr2->next;
            }
            curr2->next = lastName;
            lastName->previous = curr2;
        }
        else if(hashTable2[key2]->next == NULL){
            curr2->next = lastName;
            lastName->previous = curr2;
        }
    }
}


string Final::getName(string first, string second){ //gives super name using first and last name
    int key1 = hashSum1(first,tableSize);

    HashElem *tmp = hashTable[key1];
    int counter = 0;
    while(tmp != NULL){ //counts number of elements at index
        tmp = tmp->next;
        counter++;
    }
    int key2 = hashSum1(second,counter);

    int counter2 = 0;   //finds your first super name
    tmp = hashTable[key1];
    string firstName;
    if(tmp != NULL){
        if(key2 != NULL){
            while(counter2 != key2){
                tmp=tmp->next;
                counter2++;
            }
            firstName = tmp->name;
        }
        else{
            firstName = tmp->name;
        }
    }
    else{
        if(key1 == 1){
            firstName = "Boss";
        }
        else{
            firstName = "Vengeful";
        }
    }


    key1 = hashSum1(second,tableSize);  //finds your second super name
    tmp = hashTable2[key1];
    counter = 0;
    while(tmp != NULL){ //counts number of elements at index
        tmp = tmp->next;
        counter++;
    }
    key2 = hashSum1(first,counter);

    counter2 = 0;
    tmp = hashTable2[key1];
    string lastName;
    if(tmp != NULL){
        if(key2 != 0){
            while(counter2 != key2){
                tmp=tmp->next;
                counter2++;
            }
            lastName = tmp->previous->name;
        }
        else{
            lastName = tmp->name;
        }
    }
    else{
        if(key1 == 1){
            lastName = "Dolphin";
        }
        else{
            lastName = "Kitten";
        }
    }

    cout<<"CONFIDENTIAL: "<<firstName<<" "<<lastName<<endl;
    if(nameCounter == 1){   //saves super name but if allows to be saved only by the user, not other functions
        superName = firstName+lastName;
        nameCounter--;
    }

    return firstName,lastName;
}

void Final::printNames(){   //creates table for first and second hero name
    for(int i=0;i<tableSize;i++){
            if(hashTable[i] != NULL){
                if(hashTable[i]->next != NULL){
                    HashElem* curr = hashTable[i]->next;
                    while(curr!=NULL){
                        curr=curr->next;
                    }
                }
            }
    }

    for(int i=0;i<tableSize;i++){
        if(hashTable2[i] != NULL){
            if(hashTable2[i]->next != NULL){
                HashElem* curr = hashTable2[i]->next;
                while(curr!=NULL){
                    curr=curr->next;
                }
            }
        }
    }
}

void Final::getPower(){ //reads in Power.txt and refers to getPower2 function
    if(superName != "Bob"){
    ifstream inFile;
    inFile.open("Powers.txt");  //reads in file
    string data;
    int i=0;
    if(inFile.is_open()){
        while(getline(inFile,data)){
            stringstream gold(data);

            string powers;
            getline(gold,powers,',');

            HashElem* curr = new HashElem();
            curr->name = powers;

            hashTable3[i] = curr;
            i++;
        }
        inFile.close();
    }
    else{
        cout<<"File not opened"<<endl;
    }
    getPower2(superName);
    }
    else{
        cout<<"Please create your super name first."<<endl;
    }
}

void Final::getPower2(string x){    //this uses the super name to create a power
    int key = hashSum1(x,tableSize);

    cout<<hashTable3[key]->name<<endl;
}

void Final::getFriends(){   //refers to the same function to create your super name
    if(superName != "Bob"){
    getName(firstName1+"myyy",lastName1+"name");
    getName(firstName1+"iz",lastName1+"inigo");
    getName(firstName1+"montoya",lastName1+"you");
    }
    else{
        cout<<"Please create your super name first."<<endl;
    }
}

void Final::getEnemies(){   //refers to the same function to create your super name
    if(superName != "Bob"){
    getName(firstName1+"kill",lastName1+"my");
    getName(firstName1+"father",lastName1+"prepare");
    getName(firstName1+"tu",lastName1+"die");
    }
    else{
        cout<<"Please create your super name first."<<endl;
    }
}

void Final::getPhrase(){    //uses second name in super name to give relevant phrase
    if(superName != "Bob"){
        int key1 = hashSum1(lastName1,tableSize);

        HashElem* tmp = hashTable2[key1];
        int counter = 0;
        while(tmp != NULL){ //counts number of elements at index
            tmp = tmp->next;
            counter++;
        }
        int key2 = hashSum1(firstName1,counter);

        int counter2 = 0;
        tmp = hashTable2[key1];
        string lastName;
        if(tmp != NULL){    //finds the second super name for later steps
            if(key2 != 0){
                while(counter2 != key2){
                    tmp=tmp->next;
                    counter2++;
                }
                lastName = tmp->previous->name;
            }
            else{
                lastName = tmp->name;
            }
        }
        else{
            if(key1 == 1){
                lastName = "Dolphin";
            }
            else{
                lastName = "Kitten";
            }
        }
        //uses super name to cout relevant phrase

        if(lastName == "Beetle"){
            cout<<"Prepare yourself for a Beetle Bashdown!"<<endl;
        }
        else if(lastName == "Sloth"){
            cout<<"Just...gimme..a sec...*POW!*"<<endl;
        }
        else if(lastName == "Tiger"){
            cout<<"I'm Tony the Tiger's evil sibling!"<<endl;
        }
        else if(lastName == "Viper"){
            cout<<"Ohhai how you doin? Dead."<<endl;
        }
        else if(lastName == "Cheetah"){
            cout<<"Run...I dare you."<<endl;
        }
        else if(lastName == "Buffalo"){
            cout<<"I said it sucks to be a CSU Ram!!"<<endl;
        }
        else if(lastName == "Moose"){
            cout<<"Call me an elk ONE more time."<<endl;
        }
        else if(lastName == "Cricket"){
            cout<<"Trust me, you'll never see me coming."<<endl;
        }
        else if(lastName == "Frog"){
            cout<<"I got those mad hops bro!"<<endl;
        }
        else if(lastName == "Puppy"){
            cout<<"The most adorable way to die!"<<endl;
        }
        else if(lastName == "Octopus"){
            cout<<"I have 8. You have 2. Do the math."<<endl;
        }
        else if(lastName == "Shark"){
            cout<<"Dun Dun...Duuuun Dun..."<<endl;
        }
        else if(lastName == "Ladybug"){
            cout<<"Call me a lady ONE more time."<<endl;
        }
        else if(lastName == "Lizard"){
            cout<<"I'm as cold blooded as it gets my friend."<<endl;
        }
        else if(lastName == "Hippo"){
            cout<<"I can end you with a yawn..."<<endl;
        }
        else if(lastName == "Goat"){
            cout<<"Don't underestimate the Goat."<<endl;
        }
        else if(lastName == "Yak"){
            cout<<"Watch the horns. They're a tad deadly."<<endl;
        }
        else if(lastName == "Pigeon"){
            cout<<"Who needs a bath when you bathing in all these wins?"<<endl;
        }
        else if(lastName == "Turtle"){
            cout<<"We've all seen Teenage Mutant Ninja Turtles, back up."<<endl;
        }
        else if(lastName == "Panda"){
            cout<<"I know the ways of Kung Fu. Proceed with caution."<<endl;
        }
        else if(lastName == "Werewolf"){
            cout<<"I'm a werewolf. Need I say more?"<<endl;
        }
        else if(lastName == "Leprechaun"){
            cout<<"I'll beat ye silly and make off with ye lucky charms mate!"<<endl;
        }
        else if(lastName == "Penguin"){
            cout<<"I am 007. Just look at the tux."<<endl;
        }
    }
    else{
        cout<<"Please create your super name first."<<endl;
    }
}

void Final::getWeakness(){  //reads in Weaknesses.txt and refers to getWeakness2
    if(superName != "Bob"){
    ifstream inFile;
    inFile.open("Weaknesses.txt");  //reads in weakness
    string data;
    int i=0;
    if(inFile.is_open()){
        while(getline(inFile,data)){
            stringstream gold(data);

            string weakness;
            getline(gold,weakness,',');

            HashElem* curr = new HashElem();
            curr->name = weakness;

            hashTable4[i] = curr;
            i++;
        }
        inFile.close();
    }
    else{
        cout<<"File not opened"<<endl;
    }
    getWeakness2(superName);
    }
    else{
        cout<<"Please create your super name first."<<endl;
    }
}

void Final::getWeakness2(string x){     //uses super name to get weakness using hash function
    int key = hashSum1(x,tableSize);

    cout<<hashTable4[key]->name<<endl;
}
