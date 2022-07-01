
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
    int rarity;
public:
    items(vector<string>&test) {
        for (int i = 0; i < 8; i++) {
            if (i == 0) {
                name = test[i];
            }
            else {
                int localint;
                stringstream ss;
                ss << test[i];
                ss >> localint;
                if (i == 7) {
                    rarity = localint;
                }
                else {
                    elements[i - 1] = localint;
                }
                
            } 
        }
    }
    int  *getElements() {
        return elements;
    }
    string getName() {
        return name;
    }
    int getRarity() {
        return rarity;
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

const int SuperReq[6] = { 200,50,50,200,50,100 };

void selectItems(vector<items>& localreborns,int elementcount[], vector<itemHolder>&currentItems) {
    int currentElements[6];
    for (int i = 0; i < 6; i++) {
        currentElements[i] = elementcount[i];
    }
    
    
    
    
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
    
    
    
}

int countItems(vector<itemHolder>& countableItems) {
    int itemAmount = 0;
    for (int i = 0; i < countableItems.size(); i++) {
        itemAmount += countableItems[i].test1;
    }
    return itemAmount;
}


void countElements(int element[],vector<itemHolder>&itemList) {
    
    for (int i = 0; i < itemList.size(); i++) {
    
        for (int j = 0; j < itemList[i].test1; j++) {
            
            
            for (int k = 0; k < 6; k++) {
                element[k]+=*(itemList[i].test2->getElements()+k);
            }
        }
        
        
    
    }
      
}

double countRarities(vector<itemHolder>& countableItems) {
    int itemRarity = 0;
    for (int i = 0; i < countableItems.size(); i++) {
        itemRarity += countableItems[i].test2->getRarity();
    }
    return itemRarity;
}




double fitness(vector<itemHolder>& localItems) {
      
    return(
        pow((1 / (double)(countItems(localItems))), 1) *
        pow(countRarities(localItems), 2)) *
        pow((1 / (double)localItems.size()), 3);
}




struct fitnessScale {

    double fitnessValue;
    vector<itemHolder>storedItems;

};



int SolutionSize=100;
int GenerationAmount = 100000;
int main()
{

    //object initialization 
    vector<items>reborns;
    createItemObjects(reborns);
    srand(time(0));
    int startElements[] = { 0,0,0,0,0,0 };
    vector<itemHolder>finishedProduct;
    int localAmount = INT_MAX;
    vector<fitnessScale>Solutions;
    
    

    while (Solutions.size()< SolutionSize) {
        
        selectItems(reborns, startElements, finishedProduct);
        fitnessScale test{ fitness(finishedProduct),finishedProduct };
        Solutions.push_back(test);
        finishedProduct.clear();
    }
    int generationCounter = 0;

    while(generationCounter< GenerationAmount){

        sort(Solutions.begin(), Solutions.end(), [](const fitnessScale& a, const fitnessScale& b) {
            return a.fitnessValue > b.fitnessValue;
            });
    
        cout << "Best fitness of Gen " << generationCounter << " : " << Solutions[0].fitnessValue << endl;
        vector<fitnessScale>newGen;
        for (int i = 0; i < 5; i++) {
            newGen.push_back(Solutions[i]);
        }
        vector<vector<itemHolder>>newSolutions;
    
        while (newSolutions.size() < SolutionSize-5) {
            int randomNumber = rand() % Solutions.size();
            int randomNumber2 = rand() % Solutions.size();
        
            if (Solutions[randomNumber].fitnessValue > Solutions[randomNumber2].fitnessValue) {
                newSolutions.push_back(Solutions[randomNumber].storedItems);
            }
            else {
                newSolutions.push_back(Solutions[randomNumber2].storedItems);
            }

        }
    


        for (int i = 0; i < newSolutions.size(); i++) {
            vector<itemHolder>::iterator it = newSolutions[i].begin();
            while (it != newSolutions[i].end()) {
                int randomNum = rand() % 100;
                if (randomNum < 50) {
                    it->test1 -= 1;
                }


                if (it->test1==0) {
                
                    it = newSolutions[i].erase(it);
                }
                else {
                    it++;
                }
            }
       
        }
    

        for (int i = 0; i < newSolutions.size(); i++) {
            int localElements[] = { 0,0,0,0,0,0 };
            countElements(localElements, newSolutions[i]);
            selectItems(reborns, localElements, newSolutions[i]);
        }
        for (int i = 0; i < newSolutions.size(); i++) {
            newGen.push_back(fitnessScale{fitness(newSolutions[i]),newSolutions[i]});
    
    
        }

    
        Solutions.clear();
        Solutions = newGen;
        newGen.clear();
    

        generationCounter += 1;
    }
   /* cout << "New solutions after modification: " << endl;
    for (int i = 0; i < newSolutions.size(); i++) {
        int localElements[] = { 0,0,0,0,0,0 };
        countElements(localElements, newSolutions[i]);
        cout << "Local elements of solution:" << i<< "- ";
        for (int i = 0; i < 6; i++) {
            cout << localElements[i] << " ";
        }
        cout << endl;
        cout << "Item amount: " << countItems(newSolutions[i]) << endl;
    }*/







    countElements(startElements, Solutions[0].storedItems);

    for (int i = 0; i < Solutions[0].storedItems.size(); i++) {
        cout << Solutions[0].storedItems[i].test2->getName() << ": "<< Solutions[0].storedItems[i].test1<<" "<<endl;
        
    }
    cout << endl<<"start elements ";
    for (int i = 0; i < 6; i++) {
        cout << startElements[i] << " ";
    }
    cout << endl<<"Items amount: " << countItems(Solutions[0].storedItems);
    cout << endl<<"Fitness value of best solution: " << Solutions[0].fitnessValue << endl;
    
}


