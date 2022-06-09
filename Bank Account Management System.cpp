#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

class Account_Intro
{
	public:
		Account_Intro()
	   	{
			cout<<endl<<"\t BANK ACCOUNT";
	    	cout<<endl<<endl<<"\t MANAGEMENT";
	    	cout<<endl<<endl<<"\t SYSTEM";
	    	cout<<endl<<endl<<"PROJECT MADE BY :- "<<endl<<"Archit Sarkar"<<endl<<"Aayushi Singh";
	    	cout<<endl<<"Pranay Kumar"<<endl<<"Pritom Mukherjee"<<endl;
	    	cout<<endl<<endl<<"COLLEGE : KIIT University"<<endl<<endl<<"STREAM : Electronics and Computer Science Engineering";
	    	cin.get();
	   	}
		void instruction()
   		{
	    	cout<<endl<<"Select one option below:"<<endl;
        	cout<<"\n\t1-->Add Record to file";
        	cout<<"\n\t2-->Show Record from file";
          	cout<<"\n\t3-->Search Record from file";
          	cout<<"\n\t4-->Update Record";
        	cout<<"\n\t5-->Delete Record";
        	cout<<"\n\t6-->Quit";	
   		}
};

class Account_Data
{
protected:
	char account_number[20];
    char firstName[10];
    char lastName[10];
    float total_Balance;
public:
   	void read_data()
  	{
    	cout<<" Enter Account Number: ";
    	cin>>account_number;
    	cout<<" Enter First Name: ";
    	cin>>firstName;
    	cout<<" Enter Last Name: ";
    	cin>>lastName;
    	cout<<" Enter Balance: ";
    	cin>>total_Balance;
    	cout<<endl;
  	}		
  
  	void show_data()
    {
    	cout<<"Account Number: "<<account_number<<endl;
    	cout<<"First Name: "<<firstName<<endl;
    	cout<<"Last Name: "<<lastName<<endl;
    	cout<<"Current Balance: Rs.  "<<total_Balance<<endl;
    	cout<<"-------------------------------"<<endl;
    }
};

class Account_Rec : public Account_Data
{
public:
    void write_rec()
  	{
    	ofstream fout;
    	fout.open("Record.txt",ios::app);
    	if(!fout)
    	{
    		cout<<"Error"<<endl;
		}	
		read_data();
		fout.write((char *)this, sizeof(*this));
    	fout.close();
  	}			
 	void read_rec()
  	{
     	ifstream fin;
    	fin.open("Record.txt", ios::app);
    	if(!fin)
    	{
        	cout<<" Error in Opening! File Not Found!!"<<endl;
        	return;
    	}
    	cout<<endl<<"**Data from file**"<<endl;
    
    	while(!fin.eof())
    	{
    		if(fin.read((char*)(this), sizeof(*this))>0)
        	{	
            	show_data();
        	}
    	}
    	fin.close();
 	}
};

class Account_Search : public Account_Data
{
public:  
	void search_rec()
    {
    	int n,count;
    	ifstream fin;
    	fin.open("Record.txt", ios::app);
    	if(!fin)
    	{
        	cout<<endl<<" Error in opening! File Not Found!! "<<endl;
        	return;
    	}
    	fin.seekg(0,ios::end);
    	count = fin.tellg()/sizeof(*this);
    	cout<<endl<<" There are "<<count<<" records in the file"<<endl;
    	cout<<" Enter Record Number to Search: ";
    	cin>>n;
    	fin.seekg((n-1)*sizeof(*this));
    	fin.read((char *)this, sizeof(*this));
    	show_data();
   	}
};

class Account_Update: public Account_Data
{
public:   
    void modify_rec()
    {
    	int n;
    	fstream iofile;
    	iofile.open("Record.txt", ios::in|ios::ate);
    	if(!iofile)
    	{
        	cout<<"\nError in opening! File Not Found!!"<<endl;
        	return;
    	}
    	iofile.seekg(0, ios::end);
    	int count = iofile.tellg()/sizeof(*this);
    	cout<<"\n There are "<<count<<" records in the file"<<endl;
    	cout<<"\n Enter Record Number to Modify: ";
    	cin>>n;
    	iofile.seekg((n-1)*sizeof(*this));
    	iofile.read((char *)this, sizeof(*this));
    	cout<<"Record "<<n<<" has following data"<<endl;
    	show_data();
    	iofile.close();
    	iofile.open("Record.txt", ios::out|ios::in|ios::ate);
    	iofile.seekp((n-1)*sizeof(*this));
    	cout<<"\nEnter data to Modify "<<endl;
    	read_data();
    	iofile.write((char *)this, sizeof(*this));
	}
    void delete_rec()
    {
    	int n,count;
    	ifstream fin;
        fin.open("Record.txt", ios::app);
        if(!fin)
        {
        	cout<<endl<<" Error in opening! File Not Found!! "<<endl;
        	return;
       	}
       	fin.seekg(0, ios::end);
        count = fin.tellg()/sizeof(*this);
       	cout<<"\n There are "<<count<<" records in the file"<<endl;
	   	cout<<"\n Enter Record Number to Delete: ";
    	cin>>n;
    
    	fstream tmpfile;
    	tmpfile.open("Tmpfile.txt", ios::out|ios::app);
    	fin.seekg(0);
    	for(int i=0; i<count; i++)
    	{
        	fin.read((char *)this, sizeof(*this));
        	if(i==(n-1))
            	continue;
        	tmpfile.write((char *)this, sizeof(*this));
    	}
    	fin.close();
    	tmpfile.close();
    	remove("Record.txt");
    	rename("Tmpfile.txt", "Record.txt");
	}
};

int main()
{
	Account_Intro I;
	I.instruction();
    Account_Data D;
    Account_Rec R;
    Account_Search S;
    Account_Update U;
    
    int choice;
    
    while(true)
    {
        cout<<endl<<endl<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            R.write_rec();
            break;
        case 2:
            R.read_rec();
            break;
        case 3:
            S.search_rec();
            break;
        case 4:
            U.modify_rec();
            break;
        case 5:
            U.delete_rec();
            break;
        case 6:
            exit(0);
            break;   
        default:
            cout<<endl<<"Enter the correct choice";
            exit(0);
        }
    }
    return 0;
}
