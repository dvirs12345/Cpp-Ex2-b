#include "FamilyTree.hpp"
#include <cmath>
using namespace std;
namespace family
{
Tree::Tree(string root)
{
    string s[1000]; //defualt to 7 generations 2^7 each generation is twice the size of the last generation
    tree = s;
    tree[0] = root;
    length = 127;
    for(size_t i = 1; i < length;i++){
        tree[i] = "/";
    }
    this->size_gen = 0;
    this->max_gen = 7;
}
int Tree::getInd(string child)
{
    bool found = false;
    size_t index = -1;
    for (size_t i = 0; i < length && !found; i++)
    {
        
        if (!tree[i].compare(child))
        {
            found = true;
            index = i;
        }
    }

    return index;
}
Tree Tree::addFather(string child, string father)
{
    //i*2+1 father
    size_t index = getInd(child);
    if(tree[index * 2 + 1].compare("/"))throw runtime_error("already has a father");
    cout << "here2" << "\n";
    if(index * 2 + 1 >= length)resize(4);
    tree[index * 2 + 1] = father;
    return *this;
}
Tree Tree::addMother(string child, string mother)
{
    //i*2+2 mother
    size_t index = getInd(child);
    if(tree[index * 2 + 2].compare("/"))throw runtime_error("already has a mother");
    cout << "here" << mother <<"\n";
    if(index * 2 + 2 >= length)resize(4);


    tree[index * 2 + 2] = mother;
    return *this;
}
string Tree::relation(string name)
{
    int i;
    for (i = 0; i < length; i++)
    {
        if (name.compare(tree[i])==0)
        {
            
            if (i == 0)
                return "me";
            else if (i == 1)
                return "father";
            else if (i == 2)
                return "mother";
            
            else
            {

                if (i % 2 == 1)
                {
                    string ans = "grandfather";
                    int j=i;
                    while (j >6)
                    {
                        
                        ans = "great-" + ans;
                        j = j / 2;
                    }
                    return ans;
                }
                else
                {
                    string ans = "grandmother";
                    int j=i;
                    while (j >=8){
                        ans = "great-" + ans;
                        j = j / 2;
                    }
                    return ans;
                }
            }
        }
    }
    return "unrelated";
}
bool checkForCharta (string relate){
    if(relate.std::string::find("?") != std::string::npos || relate.std::string::find(",") != std::string::npos || 
    relate.std::string::find(" ") != std::string::npos || relate.compare("grandfatrher")==0 || relate.compare("friend")==0 ||
    relate.compare("great")==0)
        return true;
    return false;
}

string Tree::find(string relate)
{
    string toreturn = "";
    bool found = false;
    if(checkForCharta(relate))
        throw runtime_error("charta throw");
    if (relate.compare("me") == 0)
        toreturn= tree[0];
    else if (relate.compare("father") == 0)
        toreturn= tree[1];
    else if (relate.compare("mother") == 0)
        toreturn= tree[2];
    else
    { 
        int c = 0;
        int i = 0;
        while (i < relate.length())
        {
            if (relate.at(i) == '-')
                c++;
            i++;
        }
        int x = 3;
        int y = c;
        while (y != 0)
        {
            x = 2 * x;
            y--;
        }
        if (relate.std::string::find("great-grandfather") != std::string::npos){
            bool b = false;
            c=c*4;
            while (c!=0&&!b){
                if(tree[x+1].compare("/")==0){
                    x=x+2;
                }
                else
                    b=true;
                c--;
            }
            toreturn=tree[x + 1];
        }
        else if(relate.std::string::find("grandfather") != std::string::npos)
        {
            bool b = false;
            c=1;
            while (c!=0&&!b){
                if(tree[x].compare("/")==0){
                    x=x+2;
                }
                else
                {
                    b=true;
                }
                
                c--;
            }
            toreturn=tree[x];
        }
        if (relate.std::string::find("great-grandmother") != std::string::npos){
            bool b = false;
            c=c*4;
            while (c!=0&&!b){
                if(tree[x+2].compare("/")==0)
                    x=x+2;
                else
                    b=true;
                
                
                c--;
            }
            toreturn=tree[x+2];
        }
            
        else if (relate.std::string::find("grandmother") != std::string::npos)
        {
            bool b = false;
            c=1;
            while (c!=0&&!b){
                if(tree[x+1].compare("/")==0){
                    x=x+2;
                }
                else
                {
                   b=true; 
                }
                
                c--;
            }
            toreturn=tree[x + 1];
        }
        
    }
    if(toreturn.compare("/") !=0)
        return toreturn;
    throw runtime_error("didn't find someone with that relation in the tree");
}
void recremove(int ind , string* t, size_t length){//auxaillry
    t[ind] = "/";
    if(2*ind+1 < length && t[2*ind+1].compare("/"))
    recremove(2*ind+1, t,length);
    if(2*ind+2 < length && t[2*ind+2].compare("/"))
    recremove(2*ind+2, t,length);
}
void Tree::remove(string toremove)
{
    size_t ind = getInd(toremove);
    if(ind==0)
        throw runtime_error("can't delete root");
    else if(ind==-1)
        throw runtime_error("does not exist in the tree");
    tree[ind] = "/";
    if(2*ind+1 < length && tree[2*ind+1].compare("/"))
    recremove(2*ind+1, tree,length);
    if(2*ind+2 < length && tree[2*ind+2].compare("/"))
    recremove(2*ind+2, tree,length);
}
void recdisplay(int ind , string* t){//auxaillry
    if(2*ind+1 < t->length() && t[2*ind+1].compare("/")){
        cout << t[2*ind+1].c_str();
    recdisplay(2*ind+1, t);
    }
    if(2*ind+2 < t->length() && t[2*ind+2].compare("/")){
   cout << t[2*ind+2].c_str();
    recdisplay(2*ind+2, t);
    }
    if((ind-1 & (ind-2))==0)//check if this cell is the end of a generation
   cout << "\n";
}
void Tree::display()
{
   cout << tree[0].c_str() << '\n';
    if(tree[1].compare("/"))
        recdisplay(1, tree);
    if(tree[2].compare("/"))
        recdisplay(2, tree);
    
}
void Tree::resize(int x)
{
    cout << "here" << "\n";
    this->max_gen = this->max_gen + x;
    string newtree[(int)pow(2, (this->max_gen + x)) - 1];
    
    for(size_t i = 0; i < (int)pow(2, (this->max_gen + x)) - 1; i++){
        newtree[i] = "/";
    }
    
    for (size_t i = 0; i < length; i++)
    {
        newtree[i] = tree[i];
    }
    
    length = (int)pow(2, (this->max_gen + x)) - 1;
    this->tree = newtree;
    for(size_t i = 0; i < length; i++){
        cout << newtree[i] << "," ;
    }
    cout << "\n";
}


} // namespace family