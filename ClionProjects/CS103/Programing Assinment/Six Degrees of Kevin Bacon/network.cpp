#include "network.h"

using namespace std;

Network::Network()
{
	list.clear();
}

Network::~Network()
{
	for(int i=0;i<list.size();i++)
	{
		delete list[i];
	}
}

int Network::read_friends(const char *filename)
{
	ifstream infile(filename);
	if(infile.fail())
		{
			cout<<"file not found"<<endl;
			return -1;
		}
	int num;
	infile>>num;
	for(int i=0;i<num;i++)
	{
		User* myuser=new User; // creat a pointer point to the temp User
		int id;
		infile>>id;
		myuser->set_id(id);
		string s;
		infile.ignore();
		getline(infile,s);
		stringstream ss1(s);
		string name,first,last;
		ss1>>first>>last;
		name=first+" "+last;
		myuser->set_name(name);
		int year;
		infile>>year;
		myuser->set_year(year);
		int zip;
		infile>>zip;
		myuser->set_zip(zip);
		string mfriend;
		infile.ignore();
		getline(infile,mfriend);
		stringstream ss(mfriend);
		int f_id;
		while(ss>>f_id)
		{
			myuser->add_friend(f_id);
		}
		list.push_back(myuser);
	}
	return 0;
}

int Network::write_friends(const char *filename)
  {
  	ofstream outfile(filename);
  	if(outfile.fail())
  	{
  		cout<<"file cannot be created"<<endl;
  		return -1;
  	}
  	outfile<<list.size()<<endl;
  	for(int i=0;i<list.size();i++)
  	{
  		outfile<<list[i]->get_id()<<endl;
  		outfile<<"\t"<<list[i]->get_name()<<endl;
  		outfile<<"\t"<<list[i]->get_year()<<endl;
  		outfile<<"\t"<<list[i]->get_zip()<<endl;
      outfile<<"\t";
  		for(int j=0;j<list[i]->friend_num();j++)
  		{
  			outfile<<list[i]->get_friend_id(j)<<" ";
  		}
  		outfile<<endl;
  	}
    cout<<"Write the file successfully"<<endl;
  	return 0;
  }

void Network::add_user(string username, int yr, int zipcode)
  {
  	User* temp=new User;
  	temp->set_id(list.size());
  	temp->set_zip(zipcode);
  	temp->set_name(username);
  	temp->set_year(yr);
  	list.push_back(temp);
  }


int Network::add_connection(std::string name1, std::string name2)
  {
  	int index1=list.size()+1,index2=list.size()+1;

  	for(int i=0;i<list.size();i++)
  	{
  		if(list[i]->get_name()==name1)
  		{
  			index1=i;
  		}
  		if(list[i]->get_name()==name2)
  		{
  			index2=i;
  		}
  	}
  	// if the index remains unchanged, then the name is not found, return -1
  	if(index1==list.size()+1||index2==list.size()+1) 
  	{
      cout<<"One of the user doesn't exist"<<endl;
  		return -1;
  	}
  	list[index1]->add_friend(list[index2]->get_id());
  	list[index2]->add_friend(list[index1]->get_id());
  	return 0; // return 0 if success
  }

int Network::remove_connection(std::string name1, std::string name2)
  {
  	int index1=list.size()+1,index2=list.size()+1;

  	for(int i=0;i<list.size();i++)
  	{
  		if(list[i]->get_name()==name1)
  		{
  			index1=i;
  		}
  		if(list[i]->get_name()==name2)
  		{
  			index2=i;
  		}
  	}
  	// if the index remains unchanged, then the name is not found, return -1
  	if(index1==list.size()+1||index2==list.size()+1) 
  	{
  		return -1;
  	}
  	list[index1]->delete_friend(list[index2]->get_id());
  	list[index2]->delete_friend(list[index1]->get_id());
  	return 0;	// return 0 if success
  }

int Network::get_id(std::string username)
  {
  	for(int i=0;i<list.size();i++)
  	{
  		if(list[i]->get_name()==username)
  		{
  			return list[i]->get_id();
  		}
  	}
  	return -1;
  }

std::string Network::get_name(int id)
{
	for(int i=0;i<list.size();i++)
  	{
  		if(list[i]->get_id()==id)
  		{
  			return list[i]->get_name();
  		}
  	}
  	return " ";
}

  void Network::print_list()
  {
    if(list.size()==0)
    {
      cout<<"The list is empty"<<endl;
      return;
    }
    cout<<setw(8)<<"ID";
    cout<<setw(20)<<"Name";
    cout<<setw(10)<<"Year";
    cout<<setw(5)<<"Zip"<<endl;
    cout<<"============================================================"<<endl;
    for(int i=0;i<list.size();i++)
    {
      cout<<setw(7)<<list[i]->get_id()<<".";
      cout<<setw(20)<<list[i]->get_name();
      cout<<setw(9)<<list[i]->get_year();
      cout<<setw(8)<<list[i]->get_zip()<<endl;
    }
  }

void Network::print_user(int id)
{ 
  cout<<setw(7)<<list[id]->get_id()<<".";
  cout<<setw(20)<<list[id]->get_name();
  cout<<setw(9)<<list[id]->get_year();
  cout<<setw(8)<<list[id]->get_zip()<<endl;
}

  void Network::print_friend(string name)
  {
    if(list.size()==0)
    {
      cout<<"The list is empty"<<endl;
      return;
    }
    int count=0;
    for(int i=0;i<list.size();i++)
    {
      if(list[i]->get_name()==name)
      {
        count++;
        if(list[i]->friend_num()==0)
        {
          cout<<"The user doesn't have any friend!"<<endl;
          return;
        } 
        cout<<setw(8)<<"ID";
        cout<<setw(20)<<"Name";
        cout<<setw(10)<<"Year";
        cout<<setw(5)<<"Zip"<<endl;
        cout<<"============================================================"<<endl;
        for(int j=0;j<list[i]->friend_num();j++)
        {
          print_user(list[i]->get_friend_id(j));
        }
      }
    }
    if(count==0)
    {
      cout<<"User doesn't exist!!!"<<endl;
      return;
    }
  }


User* Network::get_user(int id)
{
	for(int i=0;i<list.size();i++)
	{
		if(list[i]->get_id()==id)
		{
			return list[i];
		}
	}
	return NULL;

}

void Network::clearVisit()
{
	for(int i=0;i<list.size();i++)
	{
		list[i]->isVisit=false;
	}
}

  vector<int> Network::shortest_path(int from, int to)
  {
  	vector<int> path;
  	vector<int> reverse_path;
  	queue<User*> mlist;
  	if(from==to)
  	{
  		return path;
  	}

  	User* fromuser=get_user(from);
  	User* touser=get_user(to);

  	fromuser->isVisit=true;
  	fromuser->predecessor=-1;

  	mlist.push(fromuser);

  	while(mlist.size()!=0)
  	{
  		if(mlist.front()->get_id()==touser->get_id())
  		{
  			path.push_back(to);
  			path.push_back(mlist.front()->predecessor);
  			User* previous=get_user(mlist.front()->predecessor);
  			while(previous->predecessor!=-1)
  			{
  				path.push_back(previous->predecessor);
  				previous=get_user(previous->predecessor);
  			}
  			clearVisit();
  			for(int i=path.size()-1;i>=0;i--)
  			{
  				reverse_path.push_back(path[i]);
  			}
  			return reverse_path;
  		}

  		User* frontuser=mlist.front();
  		mlist.pop();
		for(int i=0;i<frontuser->friend_num();i++)
  		{
  			User* temp=get_user(frontuser->get_friend_id(i));
  			if(temp->isVisit==false)
  			{
  				temp->predecessor=frontuser->get_id();
  				temp->isVisit=true;
  				mlist.push(temp);
  			}
  		}
  	}
  	clearVisit();
  	return path;
  }

  vector<vector<int> > Network::groups()
  {
  	vector<vector<int> > group;
  	for(int i=0;i<list.size();i++)
  	{
  		int count=0;
  		for(int j=0;j<group.size();j++)
  		{
  			for(int m=0;m<(group[j]).size();m++)
  			{
  				if((group[j])[m]==list[i]->get_id())
  				{
  					count++;
  				}
  			}

  		}
  		if(count==0)
  		{
  			vector<int> set;
  			queue<User*> mlist;
  			list[i]->isVisit=true;
  			mlist.push(list[i]);
  			while(mlist.size()!=0)
  			{
  				User* frontuser=mlist.front();
  				set.push_back(frontuser->get_id());
  				mlist.pop(); 
  				for(int m=0;m<frontuser->friend_num();m++)
  				{
  					User* temp=get_user(frontuser->get_friend_id(m));
  					if(temp->isVisit==false)
  					{
  						temp->isVisit=true;
  						mlist.push(temp);
  					}
  				}
  			}
  			group.push_back(set);
  		}
  	}
  	return group;

  }


int Network::count_common_friend(int id1, int id2)
{
	User* first=get_user(id1);
	User* second=get_user(id2);
	int count=0;
	for(int i=0;i<first->friend_num();i++)
	{
		for(int j=0;j<second->friend_num();j++)
		{
			if(first->get_friend_id(i)==second->get_friend_id(j))
			{
				count++;
			}
		}
	}
	return count;
}

  vector<int> Network::suggest_friends(int who, int& score)
  {
  	vector<int> suggest;
  	vector<int> slist;
  	vector<int> score_list;
  	int max_score=0;
  	for(int i=0;i<list.size();i++)
  	{
  		vector<int> path=shortest_path(who,list[i]->get_id());
  		if(path.size()-1==2)
  		{
  			slist.push_back(list[i]->get_id());
  		}
	}
	if(slist.size()>0)
	{
		max_score=count_common_friend(who,slist[0]);
  		for(int j=0;j<slist.size();j++)
  		{
  			int temp=count_common_friend(who,slist[j]);
  			if(temp>max_score)
  				{
  					max_score=temp;
  				}
  			score_list.push_back(temp);
  		}
  		for(int j=0;j<score_list.size();j++)
  		{
  			if(score_list[j]==max_score)
  			{
  				suggest.push_back(slist[j]);
  			}
 	 	}
 	}
 	score=max_score;
  	return suggest;
  }