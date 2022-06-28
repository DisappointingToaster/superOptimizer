
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

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
    int * getElements() {
        return elements;
    }
    string getName() {
        return name;
    }
};

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


int main()
{
    vector<items>reborns;

    createItemObjects(reborns);

    cout << reborns[1].getName() << " elements: " << endl;
    for (int i = 0; i < 6; i++) {
        cout<<*(reborns[1].getElements() + i)<<" ";
    };

    cout <<endl<< *(reborns[1].getElements() + 0) + *(reborns[1].getElements() + 2);
    //items testItem("name", 1, 7, 3, 4, 5, 65);
    //cout << *(testItem.getElements() + 5) << endl;
    
    //items testItem2("test2", 1, 2, 3, 4, 5, 146);
    //cout << *(testItem2.getElements() + 5) << endl;
    //cout << *(testItem.getElements() + 5) << endl;


}


