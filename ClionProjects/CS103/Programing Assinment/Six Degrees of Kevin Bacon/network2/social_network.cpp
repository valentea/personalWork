/*CSCI 103 Six Degrees of Kevin Bacon
Name:Alex Valente
Email Address: valentea@usc.edu*/

#include <fstream>
#include <iostream>
#include "network.h"

using namespace std;

int main(int argc, char *argv[]) {
    int error = 0;
    Network USC;
    int menuOpption = 0;
    error = USC.read_friends(argv[1]); //read friends
    if (error == -1) {
        return -1;
    }

    cout << "Welcome to the SocialNetwork" << endl;
    cout << "Please choose one of the following menu items:";
    while (menuOpption != 6) {
        cout << endl << endl;
        cout << "Select menu item" << endl;
        cout << "1) Add new User" << endl << "2) Add a new Friend" << endl << "3) Remove a Friend" <<
        endl << "4) Print users and info" << endl << "5) List all friends of a user" << endl <<
        "6) Make a new file with all the network info" << endl << "7) Find shortest path between two people" << endl <<
        "8) Print a list of all subgroups in a network" << endl << "9) Give friend suggestions" << endl <<
        "For information on each opption, type '0' followed by number of menu item." << endl << endl;
        int menuInput = 0;
        cin >> menuInput;
        menuOpption = menuInput;

        if (0 == menuOpption) {
            int helpItem;
            cin >> helpItem;
            if (7 < helpItem || 1 > helpItem) {
                cout << "Please select a number from the menu." << endl;
            }
            else if (1 == helpItem) {
                cout << "To add a new User you must  provide their name (both first "
                                "and last), birth year, and zip code input on the same line.";
            }
            else if (2 == helpItem) {
                cout << "Provide two usernames to make friends.";
            }
            else if (3 == helpItem) {
                cout << "Provide two usernames to break friendship.";
            }
            else if (4 == helpItem) {
                cout << "Print a list of users and their associated info in a table format.";
            }
            else if (5 == helpItem) {
                cout << "Provide a username and then "
                                "the program should print all the friends of that user along "
                                "with their information.";
            }
            else if (6 == helpItem) {
                cout << "Provide a filename to write "
                                "the user database to.";
            }
            else if (7 == helpItem) {
                cout << "Computes the shortest relational distance between two users. The output of this option "
                                "should print the relational distance/shortest path to the screen and then list "
                                "the shortest path of relational connections that make up the given distance." << endl;
            }
            else if (8 == helpItem) {
                cout << "Computes how many disjoint sets of users are present in the network." << endl;
            }
            else if (9 == helpItem) {
                cout << "Computes a list of users who are most likely suggestions for the specified user to add as a "
                                "friend. These users can obviously not be current friends." << endl;
            }
            else {
                cout << "Please use number that correlates to one of the menu items." << endl;
            }
        }


        if (1 == menuOpption) {
            string newFirst;
            string newLast;
            int newBY;
            int newZip;
            cout << "The format is: " << endl << "'New Name' 'New BirthYear' 'New Zipcode'" << endl;
            cin >> newFirst >> newLast >> newBY >> newZip;
            string newName = newFirst + " " + newLast;
            USC.add_user(newName, newBY, newZip);
        }
        if (2 == menuOpption) {
            string name1First;
            string name1Last;
            string name2First;
            string name2Last;
            cout << "The format is: " << endl << "'Friend One' 'Friend Two'" << endl;
            cin >> name1First >> name1Last;
            cin >> name2First >> name2Last;
            string name1 = name1First + " " + name1Last;
            string name2 = name2First + " " + name2Last;
            error = USC.add_connection(name1, name2);
            if (-1 == error) {
                cerr << "One or both of these users do not exist" << endl;
                continue;
            }
        }
        if (3 == menuOpption) {
            string name1First;
            string name1Last;
            string name2First;
            string name2Last;
            cout << "The format is: " << endl << "'Friend One' 'Friend Two'" << endl;
            cin >> name1First >> name1Last;
            cin >> name2First >> name2Last;
            string name1 = name1First + " " + name1Last;
            string name2 = name2First + " " + name2Last;
            error = USC.remove_connection(name1, name2);
            if (-1 == error) {
                cerr << "One or both of these users do not exist" << endl;
                continue;
            }
        }
        if (4 == menuOpption) {
            USC.printNetwork();
        }
        if (5 == menuOpption) {
            string nameFirst;
            string nameLast;
            int nameID;
            cout << "The format is: " << endl << "'User Name'" << endl;
            cin >> nameFirst >> nameLast;
            string name = nameFirst + " " + nameLast;
            nameID = USC.get_id(name);
            if (-1 == nameID) {
                cerr << "This user does not exist" << endl;
                continue;
            }
            USC.printFriends(nameID);
        }
        if (6 == menuOpption) {
            string newFile;
            cout << "The format is: " << endl << "'New text File name'" << endl;
            cin >> newFile;
            USC.write_friends(newFile.c_str());
        }
        if (7 == menuOpption) {
            string name1First;
            string name1Last;
            string name2First;
            string name2Last;
            cin >> name1First >> name1Last;
            string name1 = name1First + " " + name1Last;
            cin >> name2First >> name2Last;
            string name2 = name2First + " " + name2Last;
            int name1Id = USC.get_id(name1);
            int name2Id = USC.get_id(name2);
            if (-1 == name1Id || -1 == name2Id) {
                cerr << "One or both these users do not exist" << endl;
                continue;
            }
            vector<int> forward = USC.shortest_path(USC.get_id(name1), USC.get_id(name2));
            if (forward.size() != 0) {
                cout << forward.size() - 1 << endl;
                for (int i = 0; i < forward.size() - 1; i++) {
                    cout << USC.get_name(forward[i]) << " -> ";
                }
                cout << USC.get_name(forward[forward.size() - 1]) << endl;
            }
            else {
                cout << "None" << endl;
            }
        }
        if (8 == menuOpption) {
            vector<vector<int> > group = USC.groups();
            for (int i = 0; i < group.size(); i++) {
                cout << "Set " << i + 1 << " => ";
                for (int j = 0; j < (group[i]).size(); j++) {
                    cout << USC.get_name((group[i])[j]) << ", ";
                }
                cout << endl;
            }
        }
        if(9 == menuOpption) {
            string first;
            string last;
            cin >> first >> last;
            string name = first + " " + last;
            int nameID = USC.get_id(name);
            int score = 0;
            vector<int> suggestionList = USC.suggest_friends(nameID, score);
            if (suggestionList.size() != 0) {
                cout << "The suggested friend(s) is/are:" << endl;
                for (int i = 0; i < suggestionList.size(); i++) {
                    cout << "\t" << USC.get_name(suggestionList[i]) << "      " << "Score: " << score << endl;
                }
            }
            else {
                cout << "None" << endl;
            }
        }
    }
    return 0;
}