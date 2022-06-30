
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <limits>

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

vector<itemHolder> selectItems(vector<items>& localreborns,int elementcount[]) {
    int currentElements[6];
    for (int i = 0; i < 6; i++) {
        currentElements[i] = elementcount[i];
    }
    
    vector<itemHolder>currentItems;
    
    
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
    /*int localAmount = 0;
    cout << "Items stored: " << endl;
    for (int i = 0; i < currentItems.size(); i++) {
        cout << currentItems[i].test2->getName() << ": " << currentItems[i].test1 << endl;
        localAmount += currentItems[i].test1;
    }
    cout << "Items needed: " << localAmount << endl;
    cout << "Elements: ";
    for (int i = 0; i < 6; i++) {
        cout << currentElements[i] << " ";
    }*/
    return currentItems;
}

int countItems(vector<itemHolder>& countableItems) {
    int itemAmount = 0;
    for (int i = 0; i < countableItems.size(); i++) {
        itemAmount += countableItems[i].test1;
    }
    return itemAmount;
}


int countElements(int element[],vector<itemHolder>&itemList) {
    return 1;
}


double fitness(vector<itemHolder>& localItems) {
    return (1 / (double)(countItems(localItems))*100);
}

struct fitnessScale {

    double fitnessValue;
    vector<itemHolder>storedItems;

};

int main()
{

    //object initialization 
    vector<items>reborns;
    createItemObjects(reborns);
    srand(time(0));
    int startElements[] = { 0,0,0,0,0,0 };
    vector<itemHolder>finishedProduct;
    int localAmount = INT_MAX;
    vector<fitnessScale>rankedSolution;
    
    while (localAmount>35) {
        finishedProduct = selectItems(reborns, startElements);
        localAmount = countItems(finishedProduct);
        cout << "items needed: " << localAmount << " and fitness: " << fitness(finishedProduct) << endl;
    }
    fitnessScale test{fitness(finishedProduct),finishedProduct};
    
    cout <<"Test fitness value: " << test.fitnessValue << endl;
    cout << test.storedItems[0].test2->getName() << endl;
    cout << finishedProduct[0].test2->getName() << endl;



    finishedProduct = selectItems(reborns, startElements);
    fitnessScale test2{ fitness(finishedProduct),finishedProduct };
    finishedProduct = selectItems(reborns, startElements);
    fitnessScale test3{ fitness(finishedProduct),finishedProduct };


    cout << test2.storedItems[0].test2->getName() << endl;
    cout << test.storedItems[0].test2->getName() << endl;
    

    rankedSolution.push_back(test);
    rankedSolution.push_back(test2);
    rankedSolution.push_back(test3);
    cout << test3.storedItems[0].test2->getName() << endl;

    sort(rankedSolution.begin(), rankedSolution.end(), [](const fitnessScale& a, const fitnessScale& b) {
        return a.fitnessValue > b.fitnessValue;
        });
    cout << "Test value: " << rankedSolution[0].fitnessValue << endl;
    cout << "Test value: " << rankedSolution[1].fitnessValue << endl;
    cout << "Test value: " << rankedSolution[2].fitnessValue << endl;
   /* for (int i = 0; i < finishedProduct.size(); i++) {
        cout << finishedProduct[i].test2->getName() << ": " << finishedProduct[i].test1 << endl;
        
    }*/

    
    
    // [fitness value, vector<itemHolder>]
    //

    

}


