// this class is a header file for the People class


#ifndef PEOPLE_H
#define PEOPLE_H
#include <string>
using namespace std;

class People{
    private:
        string name;
        string hobby;
        int hobbyHours;
    public:
        People();
        People(const string& newName, const string& newHobby, int newHobbyHour);

        void setName(const string& newName);
        void setHobby(const string& newHobby);
        void setNewHobbyTime(int newHobbyHour);

        string getName() const;
        string getHobby() const;
        int getHour() const;

        void display() const;

};

#endif
