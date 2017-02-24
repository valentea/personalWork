#include <string>
#include "user.h"

User::User(){
    id = -1;
    birthYear = 0;
    zipCode = 0;
}

User::~User() {
    //deallocate mem if its ever needed.
}

void User::add_friend(int id){
    friends.push_back(id);
}

void User::delete_friend(int id){
    int i = 0;
    while(id != friends[i]){
        i++;
    }
    friends.erase(friends.begin()+i);
}