#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Node {
public:
    string type;
    string brand;
    string model;
    string year;
    bool rented;
    Node* next;
    Node(string t, string b, string m, string y) : type(t), brand(b), model(m), year(y), next(NULL) {}
};


class Node2 {
public:
    string name;
    string contact;
    Node2* next2;
    Node2(string n, string c, string h) : name(n), contact(c), next2(NULL) {}
};

