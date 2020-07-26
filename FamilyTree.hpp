#pragma once
#include <iostream>
using namespace std;
namespace family{

class Tree{
    private:
    size_t size_gen;//the number of genarations that are stored array
    size_t max_gen;//the max number of genarations that can be stored array
    string *tree;
    size_t length;
    void resize(int);//add x generations
    int getInd(string);//returns index of given person
    public:
    Tree(string);
    Tree addFather(string ,string);
    Tree addMother(string ,string);
    void display();
    string relation(string);
    string find(string);
    void remove(string);
};
}