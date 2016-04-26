#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "Final.h"

using namespace std;

Final::Final()
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
}

Final::~Final()
{
    //dtor
}

int Final::hashSum1(string x, int y){
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
    //cout<<"test1"<<endl;

    int key1 = hashSum1(first,tableSize);
    int key2 = hashSum1(second,tableSize);

    HashElem* curr = hashTable[key1];
    if(hashTable[key1] == NULL){
        hashTable[key1] = firstName;
        //cout<<"First "<<first<<" index "<<key1<<endl;
    }
    else{
        //cout<<"First "<<first<<" index "<<key1<<endl;
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

    HashElem* curr2 = hashTable2[key2];
    if(curr2 == NULL){
        hashTable2[key2] = lastName;
        //cout<<"Last "<<second<<" index "<<key2<<endl;
    }
    else{
        //cout<<lastName->name<<endl;
        //cout<<"Last "<<second<<" index "<<key2<<endl;
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


string Final::getName(string first, string second){
    int key1 = hashSum1(first,tableSize);
    //cout<<"First "<<first<<" index "<<key1<<endl;

    HashElem *tmp = hashTable[key1];
    int counter = 0;
    while(tmp != NULL){ //counts number of elements at index
        tmp = tmp->next;
        counter++;
    }
    int key2 = hashSum1(second,counter);
    //cout<<"Key1 "<<key1<<endl;

    int counter2 = 0;
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


    key1 = hashSum1(second,tableSize);
    //cout<<"Last "<<second<<" index "<<key1<<endl;
    //cout<<"Key1 "<<key1<<endl;

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
    if(nameCounter == 1){
        superName = firstName+lastName;
        nameCounter--;
    }

    return firstName,lastName;
}

void Final::printNames(){
    //cout<<"Table 1"<<endl;
    for(int i=0;i<tableSize;i++){
            if(hashTable[i] != NULL){
                //cout<<i<<" "<<hashTable[i]->name<<endl;
                if(hashTable[i]->next != NULL){
                    //cout<<hashTable[i]->next->name<<endl;
                    HashElem* curr = hashTable[i]->next;
                    while(curr!=NULL){
                        //cout<<i<<" "<<curr->name<<endl;
                        curr=curr->next;
                    }
                }
            }
    }

    //cout<<"Table 2"<<endl;
    for(int i=0;i<tableSize;i++){
        if(hashTable2[i] != NULL){
            //cout<<i<<" "<<hashTable2[i]->name<<endl;
            if(hashTable2[i]->next != NULL){
                HashElem* curr = hashTable2[i]->next;
                while(curr!=NULL){
                    //cout<<i<<" "<<curr->name<<endl;
                    curr=curr->next;
                }
            }
        }
    }
}

void Final::getPower(){
    //read in Power txt
    if(superName != "Bob"){
    ifstream inFile;
    inFile.open("Powers.txt");
    string data;
    int i=0;
    if(inFile.is_open()){
        while(getline(inFile,data)){
            //MovieNode *tmp=new MovieNode();
            stringstream gold(data);

            string powers;
            getline(gold,powers,',');
            //cout<<powers<<endl;

            HashElem* curr = new HashElem();
            curr->name = powers;

            hashTable3[i] = curr;
            i++;

            /*HashElem* curr = new HashElem();
            curr->name = powers;
            int key = hashSum1(powers,tableSize);
            if(hashTable3[key] == NULL){
                hashTable[key] = curr;
            }
            else if(hashTable3[key] != NULL){
                if(hashTable3[key]->next == NULL){
                    hashTable3[key]->next = curr;
                }
                else if(hashTable3[key]->next != NULL){
                    HashElem* tmp = hashTable3[key];
                    while(tmp->next != NULL){
                        tmp->next = curr;
                        curr->previous = tmp;
                    }
                }
            }*/
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

void Final::getPower2(string x){
    int key = hashSum1(x,tableSize);

    cout<<hashTable3[key]->name<<endl;
}

void Final::getFriends(){
    if(superName != "Bob"){
    getName(firstName1+"myyy",lastName1+"name");
    getName(firstName1+"iz",lastName1+"inigo");
    getName(firstName1+"montoya",lastName1+"you");
    }
    else{
        cout<<"Please create your super name first."<<endl;
    }
}

void Final::getEnemies(){
    if(superName != "Bob"){
    getName(firstName1+"kill",lastName1+"my");
    getName(firstName1+"father",lastName1+"prepare");
    getName(firstName1+"tu",lastName1+"die");
    }
    else{
        cout<<"Please create your super name first."<<endl;
    }
}

void Final::getPhrase(){
    if(superName != "Bob"){
    int key1 = hashSum1(lastName1,tableSize);
    //cout<<"Last "<<second<<" index "<<key1<<endl;
    //cout<<"Key1 "<<key1<<endl;

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

void Final::getWeakness(){
    if(superName != "Bob"){
    ifstream inFile;
    inFile.open("Weaknesses.txt");
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

void Final::getWeakness2(string x){
    int key = hashSum1(x,tableSize);

    cout<<hashTable4[key]->name<<endl;
}
