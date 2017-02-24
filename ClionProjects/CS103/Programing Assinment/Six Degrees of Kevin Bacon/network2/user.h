/*CSCI 103 Six Degrees of Kevin Bacon
Name:Alex Valente
Email Address: valentea@usc.edu*/

#ifndef USER_H
#define USER_H
#include <vector>
#include <string>

class User {
 public:
    User();
    ~User();
    void add_friend(int id1);
    void delete_friend(int id2);
    int id;
    std::string name;
    int birthYear;
    int zipCode;
    std::vector<int> friends;
    int predecessor;
    bool isVisit;
};
#endif