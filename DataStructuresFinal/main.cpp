#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "Final.h"

using namespace std;

int main()
{
    Final HT;
    ifstream inFile;
    inFile.open("HeroNames.txt");
    string data;
    if(inFile.is_open()){
        while(getline(inFile,data)){
            //MovieNode *tmp=new MovieNode();

            stringstream gold(data);

            string firstName;
            getline(gold,firstName,',');
            //cout<<firstName<<endl;

            string secondName;
            getline(gold,secondName,',');
            //cout<<secondName<<endl;

            HT.addNames(firstName,secondName);
            }
        inFile.close();
    }
    else{
        cout<<"File not opened"<<endl;
    }

    HT.printNames();
    int input=0;

        cout << "Greetings agent," << endl;
        cout << endl;
        cout << "Your last tour ended pretty rough for you and it seems as though" <<endl;
        cout << "you've lost your memory! Luckily you created a file on all the" << endl;
        cout << "information you found most essential to know in case this ever happened." << endl;
        cout << "Please use the attached file to answer all your questions." << endl;
        cout << endl;
        cout << "Good Luck!" << endl;
        cout << endl;

    while(input<7){
        cout << "1. What is my Super name!?" << endl;
        cout << "2. Learn your abilities" << endl;
        cout << "3. Learn your weakness" << endl;
        cout << "4. Discover your friends" << endl;
        cout << "5. Discover your enemies" << endl;
        cout << "6. Learn your catch phrase" << endl;
        cout << "7. Quit" << endl;
        cin>>input;
        cin.ignore();
        cout<<endl;

        if(input==1){
            string input;
            cout<<"Enter First Name:"<<endl;
            getline(cin,input);

            string input2;
            cout<<"Enter Last Name:"<<endl;
            getline(cin,input2);

            HT.firstName1 = input;
            HT.lastName1 = input2;
            HT.nameCounter++;

            cout<<"Your Super Name:"<<endl;
            HT.getName(input,input2);
        }
        if(input==2){
            cout<<"Your Power:"<<endl;
            HT.getPower();
        }
        if(input==3){
            cout<<"Your Weakness:"<<endl;
            HT.getWeakness();
        }
        if(input==4){
            cout<<"Your Friends:"<<endl;
            HT.getFriends();
        }
        if(input==5){
            cout<<"Your Enemies:"<<endl;
            HT.getEnemies();
        }
        if(input==6){
            cout<<"Your Catch Phrase:"<<endl;
            HT.getPhrase();
        }
        cout<<endl;
    }
    cout<<"Goodbye!"<<endl;
    return 0;
}
