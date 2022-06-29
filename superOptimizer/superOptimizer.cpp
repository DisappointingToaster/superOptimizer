
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>

using namespace std;



class items {
private:
    string name;
    int elements[6];
public:
    items(vector<string>&test) {
        for (int i = 0; i < 7; i++) {
            if (i == 0) {
                name = test[i];
            }
            else {
                int localint;
                stringstream ss;
                ss << test[i];
                ss >> localint;
                elements[i-1] = localint;
            } 
        }
    }
    int  *getElements() {
        return elements;
    }
    string getName() {
        return name;
    }
};



//ObjectInitializer from CSV
vector<string> split(const string& s, char delim) {
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}


void createItemObjects(vector<items>& localItems) {
    ifstream myFile;
    myFile.open("ItemElements.csv");
    char desturctor = ';';
    vector<string>v;
    string line;
    getline(myFile, line);
    while (getline(myFile, line)) {
        v = split(line, desturctor);
        localItems.push_back(items(v));

    };
};



struct itemHolder{

    int test1;
    items* test2;
    
};


bool notEnoughItems( const int expectedElements[], int currentEl[]) {
    for (int i = 0; i < 6; i++) {
        if (expectedElements[i] != 0) {
            if (currentEl[i] < expectedElements[i]) {
                return true;
            }
        }

    }
    return false;
}

const int SuperReq[6] = { 35,40,0,5,125,55 };

void selectItems(vector<items>& localreborns) {
    int currentElements[6] = {0,0,0,0,0,0};
    vector<itemHolder>currentItems;
    srand(time(0));
    
    while (notEnoughItems(SuperReq, currentElements)) {
        
        int randomNumb = rand()%localreborns.size();

        items *testlocal = &localreborns[randomNumb];
        
        if (currentItems.empty()) {
            currentItems.push_back(itemHolder{ 1,testlocal });
        }
        else {
            bool found = false;
            for (int i = 0; i < currentItems.size(); i++) {
                if (currentItems[i].test2 == testlocal) {
                    currentItems[i].test1 += 1;
                    found = true;
                    break;
                }
            }
            if (!found) {
               currentItems.push_back(itemHolder{ 1,testlocal });
            }
        }
        
        for (int i = 0; i < 6; i++) {
            currentElements[i] += *(testlocal->getElements()+i);
        }
                
        
    };
    
    cout << endl;
    int localAmount = 0;
    cout << "Items stored: " << endl;
    for (int i = 0; i < currentItems.size(); i++) {
        cout << currentItems[i].test2->getName() << ": " << currentItems[i].test1 << endl;
        localAmount += currentItems[i].test1;
    }
    cout << "Items needed: " << localAmount << endl;
    cout << "Elements: ";
    for (int i = 0; i < 6; i++) {
        cout << currentElements[i] << " ";
    }
}


int main()
{

    //object initialization 
    vector<items>reborns;
    createItemObjects(reborns);
    selectItems(reborns);
    
    

    
    
    
    

}


