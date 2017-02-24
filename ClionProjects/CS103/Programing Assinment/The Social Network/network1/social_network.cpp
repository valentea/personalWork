#include <fstream>
#include <iostream>
#include "network.h"

using namespace std;

int main(int argc, char *argv[]) {
    int error = 0;
    Network poop;
    int menuOpption = 0;
    error = poop.read_friends(argv[1]); //read friends
    if (error == -1) {
        return -1;
    }

    cout << "Welcome to the SocialNetwork" << endl;
    cout << "Please choose one of the following menu items:";
    while(menuOpption != 6){
        cout  << endl << endl;
        cout << "Select menu item" << endl;
        cout << "1) Add new User" << endl << "2) Add a new Friend" << endl << "3) Remove a Friend" <<
                endl << "4) Print users and info" << endl << "5) List all friends of a user" << endl <<
                "6) Make a new file will all the network info" << endl << "For information on each" <<
                " opption, type '0' followed by number of menu item." << endl << endl;
        int menuInput = 0;
        cin >> menuInput;
        menuOpption = menuInput;

        if(0 == menuOpption){
            int helpItem;
            cin >> helpItem;
            if(helpItem > 6 || helpItem < 1){
                cout << "Please select a number from the menu" << endl;
            }
            if(1 == helpItem){
                cout << "To add a new User you must  provide their name (both first"
                                "and last), birth year, and zip code input on the same line";
            }
            if(2 == helpItem){
                cout << "Provide two usernames to "
                                "make friends";
            }
            if(3 == helpItem){
                cout << "Provide two usernames to "
                                "break friendship";
            }
            if(4 == helpItem){
                cout << "Print a list of users and their associated info in a table format";
            }
            if(5 == helpItem){
                cout << "Provide a username and then "
                                "the program should print all the friends of that user along "
                                "with their information";
            }
            if(6 == helpItem){
                cout << "Provide a filename to write "
                                "the user database to";
            }
        }




        if(1 == menuOpption){
            string newFirst;
            string newLast;
            int newBY;
            int newZip;
            cout << "The format is: " << endl << "'New Name' 'New BirthYear' 'New Zipcode'" << endl;
            cin  >> newFirst >> newLast >> newBY >> newZip;
            string newName = newFirst + " " + newLast;
            poop.add_user(newName, newBY, newZip);
        }
        if(2 == menuOpption){
            string name1First;
            string name1Last;
            string name2First;
            string name2Last;
            cout << "The format is: " << endl << "'Friend One' 'Friend Two'" << endl;
            cin >> name1First >> name1Last;
            cin >> name2First >> name2Last;
            string name1 = name1First + " " + name1Last;
            string name2 = name2First + " " + name2Last;
            error = poop.add_connection(name1, name2);
            if(-1 == error){
                cerr << "One or both of these users do not exist" << endl;
                continue;
            }
        }
        if(3 == menuOpption){
            string name1First;
            string name1Last;
            string name2First;
            string name2Last;
            cout << "The format is: " << endl << "'Friend One' 'Friend Two'" << endl;
            cin >> name1First >> name1Last;
            cin >> name2First >> name2Last;
            string name1 = name1First + " " + name1Last;
            string name2 = name2First + " " + name2Last;
            error = poop.remove_connection(name1, name2);
            if(-1 == error){
                cerr << "One or both of these users do not exist" << endl;
                continue;
            }
        }
        if(4 == menuOpption){
            poop.printNetwork();
        }
        if(5 == menuOpption){
            string nameFirst;
            string nameLast;
            int nameID;
            cout << "The format is: " << endl << "'User Name'" << endl;
            cin >> nameFirst >> nameLast;
            string name = nameFirst + " " + nameLast;
            nameID = poop.get_id(name);
            if(-1 == nameID){
                cerr << "This user does not exist" << endl;
                continue;
            }
            poop.printFriends(nameID);
        }
        if(6 == menuOpption){
            string newFile;
            cout << "The format is: " << endl << "'New text File name'" << endl;
            cin >> newFile;
            poop.write_friends(newFile.c_str());
        }
    }
    return 0;
}