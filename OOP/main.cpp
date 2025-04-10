#include "People.h"
#include <iostream>
using namespace std;

int main() {
    People p1("Ronak", "Basketball", 2);
    p1.display();

    cout << "Changing Hobby and Hobby Time" << endl;
    
    p1.setHobby("Pickleball");
    p1.setNewHobbyTime(5);
    p1.display();
    return 0;
}