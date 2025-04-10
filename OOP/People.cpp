#include "People.h"
#include <iostream>
#include <string>
using namespace std;

People::People(){
    name = "Unknown";
    hobby = "Unknown";
    hobbyHours = 0;
}

People::People(const string& newName, const string& newHobby, int newHobbyHour){
    name = newName;
    hobby = newHobby;
    hobbyHours = newHobbyHour;
}

void People::setName(const string& newName){
    name = newName;
}

void People::setHobby(const string& newHobby){
    hobby = newHobby;
}

void People::setNewHobbyTime(int newHobbyHour){
    hobbyHours = newHobbyHour;
}

string People::getName() const{
    return name;
}

string People::getHobby() const{
    return hobby;
}

int People::getHour() const{
    return hobbyHours;
}

void People::display() const{
    cout << "hi, I'm " << name <<" and I love playing " << hobby << " for " << hobbyHours << " hours" << endl;
}

