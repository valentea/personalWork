/*CSCI 103 Six Degrees of Kevin Bacon
Name:Alex Valente
Email Address: valentea@usc.edu*/

#include "network.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <deque>
#include <queue>

Network::Network() {
    totalPeopleInNetwork = 0;
}

Network::~Network() {
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

int Network::write_friends(const char *filename) {
    int totalPeople = (int) networkArray.size();
    std::ofstream myFile;
    myFile.open(filename);

    if(!myFile.is_open()){
        return -1;
    }


    for (int k = 0; k < totalPeople; k++) {
        myFile << totalPeople << std::endl;
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

int Network::remove_connection(std::string name1, std::string name2) {
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
    if(-1 == correctNames){
        return -1;
    }
    return usernameID;
}

void Network::printFriends(int userId) {
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

void Network::printNetwork() {
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

User Network::get_user(int id) {
    for (int i = 0; i < networkArray.size(); i++) {
        if (networkArray[i].id == id) {
            return networkArray[i];
        }
    }
//    return NULL;
}

std::string Network::get_name(int id) {
    for(int i=0;i<networkArray.size();i++)
    {
        if(networkArray[i].id==id)
        {
            return networkArray[i].name;
        }
    }
    return " ";
}

void Network::cleanVisitPath() {
    for(int i=0;i<networkArray.size();i++)
    {
        networkArray[i].isVisit=false;
    }
}

std::vector<int> Network::shortest_path(int from, int to) {
    std::vector<int> forwardList;
    std::vector<int> backwardsList;
    std::queue<User> tempList;
    if (from == to) {
        return forwardList;
    }
    User fromUser = get_user(from);
    User toUser = get_user(to);
    fromUser.isVisit = true;
    fromUser.predecessor = -1;
    tempList.push(fromUser);
    while (tempList.size() != 0) {
        if (tempList.front().id == toUser.id) {
            forwardList.push_back(to);
            forwardList.push_back(tempList.front().predecessor);
            User previous = get_user(tempList.front().predecessor);
            while (previous.id != fromUser.id) {
                forwardList.push_back(previous.predecessor);
                previous = get_user(previous.predecessor);
            }
            cleanVisitPath();
            for (int i = (int) forwardList.size() - 1; i >= 0; i--) {
                backwardsList.push_back(forwardList[i]);
            }
            return backwardsList;
        }
        User frontUser = tempList.front();
        tempList.pop();
        for (int i = 0; i < frontUser.friends.size(); i++) {
            User temp = get_user(frontUser.friends[i]);
            if (!temp.isVisit) {
                temp.predecessor = frontUser.id;
                temp.isVisit = true;
                tempList.push(temp);
            }
        }
    }
    cleanVisitPath();
    return forwardList;
}

std::vector<std::vector<int> > Network::groups() {
    std::vector <std::vector<int> > kliq;
    for (int i = 0; i < networkArray.size(); i++) {
        int count = 0;
        for (int j = 0; j < kliq.size(); j++) {
            for (int m = 0; m < (kliq[j]).size(); m++) {
                if ((kliq[j])[m] == networkArray[i].id) {
                    count++;
                }
            }
        }
        if (count == 0) {
            std::vector<int> numberInKliq;
            std::queue <User> tempList;
            networkArray[i].isVisit = true;
            tempList.push(networkArray[i]);
            std::cout << "antahoesutahosu" << std::endl;
            while (tempList.size() != 0) {
                User firstUser = tempList.front();
                numberInKliq.push_back(firstUser.id);
                tempList.pop();
                std::cout << "test" << std::endl;
                for (int k = 0; k < (int)firstUser.friends.size(); k++) {
                    std::cout << "test1" << std::endl;
                    User temp = get_user(firstUser.friends[k]);
                    if (!temp.isVisit) {
                        std::cout << "test2" << std::endl;
                        temp.isVisit = true;
                        tempList.push(temp);
                    }
                }
            }
            kliq.push_back(numberInKliq);
        }
    }
    return kliq;
}

int Network::count_common_friend(int id1, int id2) {
    User first = get_user(id1);
    User second = get_user(id2);
    int count = 0;
    for (int i = 0; i < first.friends.size(); i++) {
        for (int j = 0; j < second.friends.size(); j++) {
            if (first.friends[i] == second.friends[j]) {
                count++;
            }
        }
    }
    return count;
}

std::vector<int> Network::suggest_friends(int who, int& score) {
    std::vector<int> suggestList;
    std::vector<int> tempList;
    std::vector<int> scoreList;
    int max_score = 0;
    for (int i = 0; i < networkArray.size(); i++) {
        std::cout << "test" << std::endl;
        std::vector<int> forward = shortest_path(who, networkArray[i].id);
        if (2 == (int)forward.size() - 1) {
            std::cout << "test1" << std::endl;
            tempList.push_back(networkArray[i].id);
        }
    }
    if (tempList.size() > 0) {
        max_score = count_common_friend(who, tempList[0]);
        for (int j = 0; j < tempList.size(); j++) {
            int temp = count_common_friend(who, tempList[j]);
            if (temp > max_score) {
                max_score = temp;
            }
            scoreList.push_back(temp);
        }
        for (int j = 0; j < scoreList.size(); j++) {
            if (scoreList[j] == max_score) {
                suggestList.push_back(tempList[j]);
            }
        }
    }
    score = max_score;
    return suggestList;
}