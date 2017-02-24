/*CSCI 103 Six Degrees of Kevin Bacon
Name:Alex Valente
Email Address: valentea@usc.edu*/

#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include <vector>
#include "user.h"


class Network {
 public:
    Network();
    ~Network();
    int read_friends(const char *filename);
    int write_friends(const char *filename);
    void add_user(std::string username, int yr, int zipcode);
    int get_id(std::string username);
    int totalPeopleInNetwork;
    int add_connection(std::string name1, std::string name2);
    int remove_connection(std::string name1, std::string name2);
    void printFriends(int userId);
    void printNetwork();
    User get_user(int id);
    void cleanVisitPath();
    std::vector<int> shortest_path(int from, int to);
    std::string get_name(int id);
    std::vector<std::vector<int> > groups();
    int count_common_friend(int id1, int id2);
    std::vector<int> suggest_friends(int who, int& score);
    std::vector<User> networkArray;

};
#endif