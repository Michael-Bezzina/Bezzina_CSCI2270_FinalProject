#ifndef FINAL_H
#define FINAL_H
#include <string>
#include <vector>


class Final
{
    struct HashElem{
        std::string name;
        HashElem *next;
        HashElem *previous;

        HashElem(){};
        HashElem(std::string in_name, int in_year)
        {
            name = in_name;
            next = NULL;
            previous = NULL;
        }
    };

    public:
        Final();
        ~Final();
        std::string getName(std::string input1, std::string input2); //store name
        void getPower();
        void getPower2(std::string x);
        void getFriends();
        void getFriends2(std::string x);
        void getEnemies();
        void getEnemies2(std::string x);
        void addNames(std::string first, std::string second);
        void printNames();
        void getWeakness();
        void getWeakness2(std::string x);
        void getPhrase();
        std::string superName = "Bob";
        std::string firstName1;
        std::string lastName1;
        int nameCounter = 0;
    protected:
    private:
        int tableSize = 10;
        int hashSum1(std::string x,int y);
        //int hashSum2(std::string x,int y);
        //int hashSum3(std::string x,int y);
        HashElem* hashTable[10];
        HashElem* hashTable2[10];
        HashElem* hashTable3[10];
        HashElem* hashTable4[10];
};

#endif // FINAL_H
