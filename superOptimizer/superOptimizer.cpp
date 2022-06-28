
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


class items {
private:
    int aether;
    int earth;
    int water;
    int order;
    int fire;
    int death;
    string name;
    int elements[6];
public:
    items(string n ,int a, int e, int w, int o, int f, int d) {
        name = n;
        elements[0] = a;
        elements[1] = e;
        elements[2] = w;
        elements[3] = o;
        elements[4] = f;
        elements[5] = d;
    }
    int * getElements() {
        return elements;
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


void createItemObjects() {
    ifstream myFile;
    myFile.open("ItemElements.csv");
    char desturctor = ';';
    vector<string>v;
    string line;
    while (getline(myFile, line)) {
        v = split(line, desturctor);
        for (int i = 0; i < 7;i++) 
            cout << v[i] << endl;

    };
};


int main()
{
    vector<items>reborns;

    createItemObjects();

    items testItem("name", 1, 7, 3, 4, 5, 65);
    cout << *(testItem.getElements() + 5) << endl;
    
    items testItem2("test2", 1, 2, 3, 4, 5, 146);
    cout << *(testItem2.getElements() + 5) << endl;
    cout << *(testItem.getElements() + 5) << endl;


}


