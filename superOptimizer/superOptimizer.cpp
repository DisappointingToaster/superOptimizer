
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;




class itemE {
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
    itemE(string n ,int a, int e, int w, int o, int f, int d) {
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


int main()
{
    ifstream myFile;
    myFile.open("ItemElements.csv");
    char desturctor = ';';
    vector<string>v;

    while (myFile.good()) {
        string line;
        getline(myFile, line);
        cout << line<<endl;
        v = split(line, desturctor);
        for (auto i : v) cout << i << endl;

    };


    itemE testItem("name", 1, 7, 3, 4, 5, 65);
    cout << *(testItem.getElements() + 5) << endl;
    
    itemE testItem2("test2", 1, 2, 3, 4, 5, 146);
    cout << *(testItem2.getElements() + 5) << endl;
    cout << *(testItem.getElements() + 5) << endl;


}


