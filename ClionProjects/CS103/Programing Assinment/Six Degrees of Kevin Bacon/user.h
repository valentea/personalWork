#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class User {
 public:
 	User();
 	void add_friend(int id);
 	void delete_friend(int id);
 	int get_id();
 	int get_year();
 	int get_zip();
 	string get_name();
 	int friend_num(); // return how many friends does the user have
 	int get_friend_id(int index);// return the firend's id at the certain index
 	void set_id(int id);
 	void set_year(int year);
 	void set_zip(int zip);
 	void set_name(string name);
 	int predecessor;
 	bool isVisit;
 private:
 	int _id,_year,_zip;
 	string _name;
 	vector<int> _friend;
};


#endif
