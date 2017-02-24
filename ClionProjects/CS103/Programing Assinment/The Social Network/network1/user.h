#ifndef USER_H
#define USER_H
#include <vector>
#include <string>

class User {
 public:
    User();
    ~User();
    void add_friend(int id);
    void delete_friend(int id);

    int id;
    std::string name;
    int birthYear;
    int zipCode;
    std::vector<int> friends;
};
#endif