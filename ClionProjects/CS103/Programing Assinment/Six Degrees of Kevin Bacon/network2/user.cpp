/*CSCI 103 Six Degrees of Kevin Bacon
Name:Alex Valente
Email Address: valentea@usc.edu*/

#include <string>
#include <vector>
#include "user.h"

User::User(){
    id = -1;
    birthYear = 0;
    zipCode = 0;
}

User::~User() {
    //deallocate mem if its ever needed.
}

void User::add_friend(int id1){
    friends.push_back(id1);
}

void User::delete_friend(int id2){
    int i = 0;
    while(id2 != friends[i]){
        i++;
    }
    friends.erase(friends.begin()+i);
}