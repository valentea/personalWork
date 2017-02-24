#include "network.h"
#include "user.h"
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
	Network net;
	if(argc==2)
	{
		net.read_friends(argv[1]); 
	}
	bool game=true;
	while(game)
	{
		cout<<"Option 1. Add a user\nOption 2. Add friend connection\nOption 3. Remove friend connection"<<endl;
		cout<<"Option 4. Print users\nOption 5. List friends\nOption 6. Write to file\nOption 7. Shortest path\nOption 8. Groups"<<endl;
		cout<<"Option 9. Suggest Friend\nOption 10. Quit"<<endl;
		cout<<"Enter your choice follow by parameters";
		int option;
		string input;
		getline(cin,input);
		string first1,first2,last1,last2,name1,name2,outfile;
		int year,zip;
		stringstream ss(input);
		ss>>option;
		switch(option)
		{
		case 1:
			ss>>first1>>last1>>year>>zip;
			name1=first1+" "+last1;
			if(ss.fail())
			{
				cout<<"The parameters are wrong"<<endl;
				break;
			}
			net.add_user(name1,year,zip);
			break;
		case 2:
			ss>>first1>>last1>>first2>>last2;
			name1=first1+" "+last1;
			name2=first2+" "+last2;
			if(ss.fail())
			{
				cout<<"The parameters are wrong"<<endl;
				break;
			}
			net.add_connection(name1,name2);
			break;
		case 3:
			ss>>first1>>last1>>first2>>last2;
			name1=first1+" "+last1;
			name2=first2+" "+last2;
			if(ss.fail())
			{
				cout<<"The parameters are wrong"<<endl;
				break;
			}
			net.remove_connection(name1,name2);
			break;
		case 4:
			net.print_list();
			break;
		case 5:
			ss>>first1>>last1;
			name1=first1+" "+last1;
			if(ss.fail())
			{
				cout<<"The parameters are wrong"<<endl;
				break;
			}
			net.print_friend(name1);
			break;
		case 6:
			ss>>outfile;
			if(ss.fail())
			{
				cout<<"The parameters are wrong"<<endl;
				break;
			}
			net.write_friends(outfile.c_str());
			break;
		case 7:
			{
				ss>>first1>>last1>>first2>>last2;
				name1=first1+" "+last1;
				name2=first2+" "+last2;
				if(ss.fail())
				{
					cout<<"The parameters are wrong"<<endl;
					break;
				}
				vector<int> mpath=net.shortest_path(net.get_id(name1),net.get_id(name2));
				if(mpath.size()!=0)
				{
					cout<<mpath.size()-1<<endl;
					for(int i=0;i<mpath.size()-1;i++)
					{
						cout<<net.get_name(mpath[i])<<" -> ";
					}
					cout<<net.get_name(mpath[mpath.size()-1])<<endl;
				}
				else
				{
					cout<<"None"<<endl;
				}
			}
			break;
		case 8:
			{
				vector<vector<int> >group=net.groups();
				for(int i=0;i<group.size();i++)
				{
					cout<<"Set "<<i+1<<" => ";
					for(int j=0;j<(group[i]).size();j++)
					{
						cout<<net.get_name((group[i])[j])<<", ";
					}
					cout<<endl;
				}				
			}
			break;
		case 9:
			{
				ss>>first1>>last1;
				name1=first1+" "+last1;
				if(ss.fail())
				{
					cout<<"The parameters are wrong"<<endl;
					break;
				}
				int score=0;
				vector<int> suggest=net.suggest_friends(net.get_id(name1),score);
				if(suggest.size()!=0)
				{
					cout<<"The suggested friend(s) is/are:"<<endl;
					for(int i=0;i<suggest.size();i++)
					{
						cout<<"\t"<<net.get_name(suggest[i])<<"      "<<"Score: "<<score<<endl;
					}
				}
				else
				{
					cout<<"None"<<endl;
				}
			}
			break;
		case 10:
			cout<<"Quiting"<<endl;
			game=false;
			break;
		default:
			break;
		}
	}
  return 0;
}
