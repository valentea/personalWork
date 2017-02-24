#include "network.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

Network::Network(){
    totalPeopleInNetwork = 0;
}

Network::~Network(){
    //dealocate memroy if needed
}

int Network::read_friends(const char *filename) {
    std::ifstream networkFile;
    networkFile.open(filename);

    if (!networkFile.is_open()) {
        std::cout << "you fail" << std::endl;
        return -1;
    }
    networkFile >> totalPeopleInNetwork;

    for (int i = 0; i < totalPeopleInNetwork; ++i) {
        User temp;
        networkFile >> temp.id;
        std::string tempName;
        getline(networkFile, tempName);
        getline(networkFile, tempName);
        std::stringstream ss1(tempName);
        std::string first;
        std::string last;
        ss1 >> first;
        ss1 >> last;
        std::string fullName;
        fullName = first + " " + last;
        temp.name = fullName;
        networkFile >> temp.birthYear;
        networkFile >> temp.zipCode;
        std::string friendsList;
        getline(networkFile, friendsList);
        getline(networkFile, friendsList);
        std::stringstream ss(friendsList);
        int j;
        while (ss >> j) {
            temp.add_friend(j);
        }
        networkArray.push_back(temp);
    }
    networkFile.close();
    return 0;
}

int Network::write_friends(const char *filename){
    int totalPeople = (int) networkArray.size();
    std::ofstream myFile;
    myFile.open(filename);

    if(!myFile.is_open()){
        std::cout << "Please enter valid name." << std::endl;
        return 0;
    }

    for (int k = 0; k < totalPeople; k++) {
        myFile << networkArray[k].id << std::endl;
        myFile << '\t' << networkArray[k].name << std::endl;
        myFile << '\t' << networkArray[k].birthYear << std::endl;
        myFile << '\t' << networkArray[k].zipCode << std::endl;
        int totalFriends = (int) networkArray[k].friends.size();
        myFile << '\t';
        for (int i = 0; i < totalFriends; ++i) {
            myFile << networkArray[k].friends[i] << " ";
        }
        myFile << std::endl;
    }
    myFile.close();
    return 0;
}

void Network::add_user(std::string username, int yr, int zipcode) {
    User temp;
    temp.name = username;
    temp.birthYear = yr;
    temp.zipCode = zipcode;
    temp.id = totalPeopleInNetwork;
    networkArray.push_back(temp);
    totalPeopleInNetwork = (int)networkArray.size();
}

int Network::add_connection(std::string name1, std::string name2) {
    int name1ID = -1;
    int name2ID = -1;
    int correctNames = 0;
    for (int i = 0; i < totalPeopleInNetwork; ++i) {
        if (networkArray[i].name == name1) {
            name1ID = networkArray[i].id;
            correctNames += 1;
        }
        if (networkArray[i].name == name2) {
            name2ID = networkArray[i].id;
            correctNames += 1;
        }
    }
    if (2 == correctNames) {
        networkArray[name1ID].add_friend(name2ID);
        networkArray[name2ID].add_friend(name1ID);
        return 0;
    }
    else {
        return -1;
    }
}

int Network::remove_connection(std::string name1, std::string name2){
    int name1ID = -1;
    int name2ID = -1;
    int correctNames = 0;
    for (int i = 0; i < totalPeopleInNetwork; ++i) {
        if (networkArray[i].name == name1) {
            name1ID = networkArray[i].id;
            correctNames += 1;
        }
        if (networkArray[i].name == name2) {
            name2ID = networkArray[i].id;
            correctNames += 1;
        }
    }
    if (2 == correctNames) {
        networkArray[name1ID].delete_friend(name2ID);
        networkArray[name2ID].delete_friend(name1ID);
        return 0;
    }
    else {
        return -1;
    }
}

int Network::get_id(std::string username) {
    int usernameID = -1;
    int correctNames = -1;
    for (int i = 0; i < totalPeopleInNetwork; ++i) {
        if (networkArray[i].name == username) {
            usernameID = networkArray[i].id;
            correctNames += 1;
        }
    }
    if(correctNames == -1){
        return -1;
    }
    return usernameID;
}

void Network::printFriends(int userId){
    int totalFriends = (int)networkArray[userId].friends.size();
    std::cout << "ID" << std::setw(8) << "Name" << std::setw(15) << "Year" << std::setw(8) <<
            "Zip" << std::endl <<
            "=============================================" << std::endl;
    for (int i = 0; i < totalFriends; ++i) {
        int tempFriendId = networkArray[userId].friends[i];
        int lengthOfName = (int)networkArray[tempFriendId].name.size();
        std::cout << tempFriendId <<  "." <<  std::setw(4 + lengthOfName) << networkArray[tempFriendId].name <<
                std::setw(19-lengthOfName) << networkArray[tempFriendId].birthYear <<  std::setw(10) <<
                networkArray[tempFriendId].zipCode
                << std::endl;
    }
}

void Network::printNetwork(){
    int totalFriends = (int)networkArray.size();
    std::cout << "ID" << std::setw(8) << "Name" << std::setw(15) << "Year" << std::setw(8) <<
    "Zip" << std::endl <<
    "=============================================" << std::endl;
    for (int i = 0; i < totalFriends; ++i) {
        int lengthOfName = (int)networkArray[i].name.size();
        std::cout << networkArray[i].id << "." << std::setw(4 + lengthOfName) << networkArray[i].name << std::setw(19-lengthOfName)
                << networkArray[i].birthYear << std::setw(10) << networkArray[i].zipCode << std::endl;
    }
}