#include<iostream>
#include<fstream>
#include<conio.h>
#include<algorithm>
#include<string>
#include<ctype.h>
#include<algorithm>
#include<windows.h>
#include<string.h>
#include "headerSource.h"
using namespace std;
//Start
//-------------------------------------------------------------------Global Scope Declarations----------------------------------------------------------
fstream users;
fstream tuser;
fstream fbook;
fstream admins;
fstream all;
fstream allbooks;
fstream authornames;
fstream genere;
fstream publisher;
struct book{
	string book_name;
	string author_name;
	string genere;
	string publisher_name;
	string year;
	string summary;
	int cost;
	int quanitity;
};
//--------------------------------------------------------------------Class Person----------------------------------------------------------------------
class person{
protected:
	//friend void add(string line);
	//friend void fd(string line);
	//friend void transfer(string);
	string password;
	string status;
	void cls() {
		for (int i = 0; i < 100; i++)
			cout << "\n";
	}
	void bdis(book n) {
		cls();
		cout <<"\nBook Name: "<< n.book_name << endl;
		cout <<"\nAuthor Name: "<< n.author_name << endl;
		cout <<"\nGenere: "<< n.genere << endl;
		cout <<"\nPublisher: "<<n.publisher_name << endl;
		cout <<"\nYear: "<< n.year << endl;
		cout <<"\nSynopsis: " << n.summary << endl;
		//cout << n.cost << endl;
		//cout << n.quanitity << endl;
		_getch();
	}
	book intake(string t) {
		fbook.clear();
		transform(t.begin(), t.end(), t.begin(), ::tolower);
		fbook.open(t.c_str(), ios::in);
		if (fbook.is_open()) {
			book NewBook;
			getline(fbook, NewBook.book_name);
			getline(fbook, NewBook.author_name);
			getline(fbook, NewBook.genere);
			getline(fbook, NewBook.publisher_name);
			getline(fbook, NewBook.year);
			getline(fbook, NewBook.summary);
			fbook >> NewBook.cost;
			fbook >> NewBook.quanitity;
			fbook.close();
			fbook.clear();
			//bdis(NewBook);
			//_getch();
			return NewBook;
		}
		else
		{
			cout << "failed intake\n";
			_getch();
			exit(1);
		}
	}
	void bookdumper(book t) {
		fbook.clear();
		//bdis(t);
		transform(t.book_name.begin(), t.book_name.end(), t.book_name.begin(), ::tolower);
		fbook.open(t.book_name.c_str(), ios::out);
		if (fbook.is_open()) {
			fbook << t.book_name << endl;
			fbook << t.author_name << endl;
			fbook << t.genere << endl;
			fbook << t.publisher_name << endl;
			fbook << t.year << endl;
			fbook << t.summary << endl;
			fbook << t.cost << endl;
			fbook << t.quanitity << endl;
			fbook.close();
			fbook.clear();
		}
		else
			cout << "\nBook dumper failed\n";
		}
	string id;
public:
	void change_password() {
		cls();
		string line;
		cout << "\nEnter your old password\n";
		string old_pass = ::take_password();
		//cout << "Old password" << endl;
		if (strcmp(old_pass.c_str(), password.c_str()) == 0)
		{
			cout << "\nEnter new password\n";
			string newpass1 = ::take_password();
			cout << "\nRe enter your new password\n";
			string newpass2 = ::take_password();
			if (strcmp(newpass1.c_str(), newpass2.c_str()) == 0) {
				password = newpass1;
				cout << "\nPassword updated succesfully\n";
				users.clear();
				users.open(id.c_str());
				users << password;
				users.close();
			}
			else {
				cout << "\nPasswords Didn't match\n";
				_getch();
				change_password();
			}
		}
		else
		{
			cout << "\nPassword Entered was invalid\n";
			change_password();
		}
		_getch();
		}
	string person_name;
//constructor
	person() {
		password = "N/A";
		person_name = "N/A";
		id = "N/A";
		}
	void searchfiller(string type, string keyword, string name) {
		char a = 'k';
		int i = 1, k = 1, z = 0;
		cout << name << endl << endl;
		all.clear();
		all.open(type, ios::in);
		if (all.is_open()) {
			string line;
			while (getline(all, line)) {
				std::size_t found = line.find(keyword);
				if (found != std::string::npos) {
					cout << k << ". " << line << endl;
					k++;
				}
			}
			if (k == 1)
				cout << "No Results\n";
			all.close();
			all.clear();		
		}
		else { cout << "Couldnt open " << name << endl; }
		cout << endl;
	}

	void searchfiller(string type, string keyword) {
		char a = 'k';
		int i = 1, k = 0, z = 0;
		//cout << name << endl << endl;
		all.clear();
		all.open(type, ios::in);
		if (all.is_open()) {
			string line;
			while (getline(all, line)) {
				std::size_t found = line.find(keyword);
				if (found != std::string::npos) {
					cout << line <<":-"<< endl;
					fbook.clear();
					fbook.open(line);
					string str;
					int l = 1;
					while (getline(fbook, str)) {
						cout <<"\t"<< l << ". " << str << endl;
						l++;
					}
					k++;
					fbook.close();
				}
			}
			if (k == 0)
				cout << "No Results\n";
			all.close();
			all.clear();
		}
		else { cout << "Couldnt open " << endl; }
		cout << endl;
	}
	void searchresults() {
		char ch = ' ';
		do {
			cls();
		string index;
			cout << "<b> Search from all books\n";
			cout << "<a> Search in author\n";
			cout << "<g> Search in Genere\n";
			cout << "<p> Search from publisher\n";
			cout << "<q> Search from Everything\n\n";
			cout << "<A> Search by Author\n";
			cout << "<G> Search by Genere\n";
			cout << "<P> Search by Publisher\n";
			cout << "<e> Exit\n";
			if (ch != 'e') {
				ch = ' ';
				cin >> ch;
				cls();
				cout << "Search key :";
				cin >> index;
				transform(index.begin(), index.end(), index.begin(), ::tolower);
				switch (ch) {
				case 'b':searchfiller("allbooks.dat", index, "Books:");
					_getch();
					break;
				case 'a':searchfiller("author_name.dat", index, "Authors:");
					_getch();
					break;
				case 'g':searchfiller("genere.dat", index, "Generes:");
					_getch();
					break;
				case 'p':searchfiller("publisher.dat", index, "Publishers:");
					_getch();
					break;
				case 'q':  searchfiller("allbooks.dat", index, "Books:");
					searchfiller("author_name.dat", index, "Authors:");
					searchfiller("genere.dat", index, "Generes:");
					searchfiller("publisher.dat", index, "Publishers:");
					_getch();
					break;
				case 'A':searchfiller("author_name.dat", index);
					_getch();
					break;
				case 'P':searchfiller("publisher.dat", index);
					_getch();
					break;
				case 'G':searchfiller("genere.dat", index);
					_getch();
					break;
				};
			}
			//searchfiller("allbooks.dat", index, "Books:");
			//searchfiller("author_name.dat", index, "Authors:");
			//searchfiller("genere.dat", index, "Generes:");
			//searchfiller("publisher.dat", index, "Publishers:");
			} while (ch!='e');
		//admin_menu();
			_getch();
	}
	void copier(string user_idx) {
		users.clear();
		users.open(user_idx, ios::in);
		id = user_idx;
		//cout << "Entered copy loop\n";
		getline(users, password);
		//cout << password << endl;
		users.clear();
		getline(users, person_name);
		//cout << person_name << endl;
		users.clear();
		getline(users, status);
		users.clear();
		//cout << status << endl;
		users.close();
		users.clear();
	}
};
//---------------------------------------------------------------------admin class----------------------------------------------------------------
class admin :public person {
public:
	
	void modifybook() {
		cls();
		cout << "Enter Book name\n";
		string line;
		cin.ignore();
		//cin.clear();
		getline(cin, line);
		if (strcmp(line.c_str(), "\n") != 0) {
			book temp = intake(line);
			cout << "Enter Parameter to be changed\n";
			string para;
			cin.clear();
			getline(cin, para);
			if (strcmp(para.c_str(), "quantity") == 0)
			{
				cout << "\nExisting Quantity: ";
				cout << temp.quanitity << endl;
				cout << "\nNew Quantity: ";
				cin >> temp.quanitity;
				cout << "\nChanges Applied\n";
			}
			if (strcmp(para.c_str(), "price") == 0) {
				cout << "Existing price :" << temp.cost << endl;
				cout << "\nNew Price: ";
				cin >> temp.cost;
				cout << "\nChanges applied\n";

			}
			if (strcmp(para.c_str(), "synopsis")) {
				cout << "\nExisting synopsis\n" << endl;
				cout << temp.summary << endl;
				cout << "New Synopsis\n";
				cin.ignore();
				//in.clear();
				getline(cin, temp.summary);
				cout << "\nChanges applied\n";
			}
			bookdumper(temp);
			_getch();
		}
	}
	void cpassa() {
		change_password();
		admindumper();
	}
	void admindumper() {
		admins.clear();
		admins.close();
		admins.open(id.c_str(),ios::out);
		if (admins.is_open()) {
			admins << password << endl;
			admins << person_name << endl;
		}
		else {
			cout << "Admin dumper fail " << endl;
			_getch();
		}
		admins.close();
	}
	void create_book() {
		cls();
		book NewBook;
		cin.ignore();
		cout << "\nBook Title: ";
		getline(cin, NewBook.book_name);
		cin.clear();
		cout << "\nAuthor Name: ";
		getline(cin, NewBook.author_name);
		cin.clear();
		cout << "\nGenere: ";
		getline(cin, NewBook.genere);
		cin.clear();
		cout << "\nPublisher: ";
		getline(cin, NewBook.publisher_name);
		cin.clear();
		cout << "\nYear: ";
		getline(cin, NewBook.year);
		cin.clear();
		cout << "\nSynopsis: ";
		getline(cin, NewBook.summary);
		cin.clear();
		cout << "\nCost per day";
		cin >> NewBook.cost;
		cin.clear();
		cout << "\nQuantity :";
		cin >> NewBook.quanitity;
		cin.clear();
		string filname=NewBook.book_name;
		transform(NewBook.book_name.begin(), NewBook.book_name.end(), NewBook.book_name.begin(), ::tolower);
		fbook.clear();
		fbook.open(NewBook.book_name.c_str(), ios::out);
		if (fbook.is_open()) {
			fbook << NewBook.book_name << endl;
			fbook << NewBook.author_name << endl;
			fbook << NewBook.genere << endl;
			fbook << NewBook.publisher_name << endl;
			fbook << NewBook.year << endl;
			fbook << NewBook.summary << endl;
			fbook << NewBook.cost << endl;
			fbook << NewBook.quanitity << endl;
			fbook.close();
			fbook.clear();
		}
		allbooks.open("allbooks.dat", ios::out|ios::app);
		allbooks << NewBook.book_name << endl;
		allbooks.close();
		allbooks.clear();
		filler("author_name.dat", NewBook.book_name, NewBook.author_name);
		filler("genere.dat", NewBook.book_name, NewBook.genere);
		filler("publisher.dat", NewBook.book_name, NewBook.publisher_name);
		_getch();
	}
	void filler(string type, string bookname, string bookref) {
		all.clear();
		all.open(type, ios::in);
		if (all.is_open()) {
			transform(bookref.begin(), bookref.end(), bookref.begin(), ::tolower);
			transform(bookname.begin(), bookname.end(), bookname.begin(), ::tolower);
			string line;
			bool flag=1;
			while (getline(all, line))
			{
				if (strcmp(line.c_str(), bookref.c_str()) == 0)
				{
					fstream temp;
					temp.clear();
					temp.open(line.c_str(),ios::app);
					temp << bookname << endl;
					temp.close();
					flag = 0;
				}
				
			}
			all.close();
			all.clear();
			all.open(type, ios::app);
			if (flag)
			{
				all << bookref << endl;
				fstream temp;
				temp.clear();
				temp.open(bookref.c_str(),ios::out|ios::app);
				temp << bookname << endl;
				temp.close();
			}
			all.close();
			all.clear();
					}
		else
			cout << "Couldnt open book ref file" << type << endl;

		
	}
	void stocks() {
		cls();
		char ch = ' ';
		string line;
		string quant;
		int quanti=0;
		allbooks.clear();
		all.clear();
		cout << "\nEnter your choice\n<a>All books\n<s>Specific book\n ";
		cin >> ch;
		if (ch == 'a') {
			allbooks.open("allbooks.dat", ios::in);
			while (getline(allbooks, line)) {
				all.open(line.c_str(), ios::in);
				for (int i = 0; getline(all, quant) && i < 8; i++)
				{
					if (i == 7) {
						cout << line << "\t" << quant << endl;
					}
				}
				all.close();
			}
			allbooks.close();
			
		}
		else if (ch == 's') {
			cout << "Enter book name\n";
			string liner;
			cin.clear();
			cin.ignore();
			getline(cin, liner);
			transform(liner.begin(), liner.end(), liner.begin(), ::tolower);
			all.clear();
			cls();
			all.open(liner.c_str(), ios::in);
			if (all.is_open()) {
				for (int i = 0; getline(all, quant) && i < 7; i++)
				{
					if (i == 6) {
						cout << liner << "\t" << quant;
					}
				}
				all.close();
			}
			else
			{
				cout << "couldnt open file\n";
			}
		}
		else {
			cout << "invalid option\n";
			stocks();
		}
		_getch();
	}
	void signup() {
		cls();
		string tuser_id, tpass, tname, fname;
		cout << "\t\t\tSign-Up Infomation\n";
		cout << "\nUser-Id:";
		cin >> tuser_id;
		cout << "\nPassword: ";
		tpass = take_password();
		cout << "\nName :";
		cin >> tname;
		transform(tuser_id.begin(), tuser_id.end(), tuser_id.begin(), ::tolower);
		users.open(tuser_id.c_str(), ios::out);
		if (users.is_open())
		{
			users << tpass;
			users << endl;
			users << tname;
			users << endl;
			users << "N/A";
			users << endl;
			users << "N/A";
			users << endl;
			users << "N/A";
			users << endl;
			users << "N/A";
			users << endl;
			cout << "User created successfully\n";
			users.close();
		}
		else {
			cout << "Couldnt create a admin. Please try again\n";
		
		}
			admins.open("admins.dat",ios::app);
			admins << tuser_id;
			admins << endl;
			admins.close();
			_getch();
		
	}	
//------------------------------------------------------------------Admin Menu--------------------------------------------------------------
	void admin_menu()
	{


		char ch=' ';
		do {
			cls();
			cout << "\nEnter your option\n";
			cout << "<c> Create book\n\n<m> Modify Book\n\n<s> Search\n\n<q> Stocks\n\n<n> Create new Admin\n\n<p> Change password\n\n<d> Display Book details\n\n<l> Log Out\n\n";
			cin >> ch;
			switch (ch)
			{
			case 'c':create_book();
				break;
			case 's':searchresults();
				break;
			case 'n':signup();
				break;
			case 'q':stocks();
				break;
			case 'p':cpassa();
				break;
			case 'm':modifybook();
				break;
			case 'd':cls();
				cout << "Enter book name\n";
				string line;
				cin.ignore();
				cin.clear();
				getline(cin, line);
				book temp = intake(line);
				bdis(temp);
				break;
			};
		} while (ch != 'l');
		cls();
	}
};
//-------------------------------------------------------------------------student class----------------------------------------------------------------
class student :public person {
protected:
	string book_taken1;
	string date1;
	string book_taken2;
	string date2;
public: 
	void cpass() {
		change_password();
		dumper();
	}
	void userdetails() {
		cls();
		cout << "\nId:" << id << endl;
		cout << "Password:" << password << endl;
		cout << "User name:" << person_name << endl;
		cout << "Book Taken \n" << book_taken1 << endl;
		cout << "Book taken 2\n" << book_taken2 << endl;
		_getch();
	}
	//fucntions
	void dumper() {
		tuser.open(id.c_str(),ios::out);
			if (tuser.is_open()) {
				tuser << password << endl;
				tuser << person_name << endl;
				tuser << book_taken1 << endl;
				tuser << date1 << endl;
				tuser << book_taken2 << endl;
				tuser << date2 << endl;
				tuser.close();
			}
			else {
				cout << "Dumper failed\n";
				exit(0);
					
			}
		}
	void copier1(string user_idx) {
		string line;
		users.open(user_idx, ios::in);
		for (int lineno = 0; getline(users, line) && lineno < 6; lineno++) {
			if (lineno == 2) 
				book_taken1 = line;
			if (lineno == 3)
				date1 = line;
			if (lineno == 4) 
				book_taken2 = line;
			if (lineno == 5)
				date2 = line;
			}
		users.close();
	
	}
	void take_book() {
		cls();
		if (strcmp(book_taken2.c_str(), "N/A") == 0 || strcmp(book_taken1.c_str(), "N/A") == 0) {

			cout << "Enter book name\n";
			string bname;
			string line, liner;
			string date;
			string t;
			book NewBook;
			cin.ignore();
			cin.clear();
			getline(cin, bname);
			tuser.clear();
			//cout << bname;
			tuser.open(bname, ios::in);
			if (tuser.is_open()){
				tuser.close();
				NewBook = intake(bname);
				if (NewBook.quanitity != 0) {
					cout << "\nBook costs:" << NewBook.cost << " Rs Per day\n";
					char ch = ' ';
					cout << "Do you want to continue (y/n)\n";
					cin >> ch;
					if (ch == 'y') {
						cin.clear();
						cin.ignore();
						cout << "\nEnter date\n";
						cin >> date;
						//date = ::datex();
						cin.clear();
						NewBook.quanitity--;
						bookdumper(NewBook);
						if (book_taken1 == "N/A")
						{
							
								date1 = date;
								book_taken1 = bname;
					
						}
						else
						{
							if (book_taken2 == "N/A") {
								book_taken2 = bname;
								date2 = date;
							}
						}
						cout.clear();
						cout << "\nBook Issued\n";
						cout << bname << endl << date << endl;
						dumper();
						_getch();

					}

					else {
						cout << "Sorry, The book is currently unavailable\n Please come again later\n";
						_getch();
					}
				}
		}
			else {
				cout << "No Book such exists\n";
			}
		}
		else {
			cout << "\nYou still need to return the books taken \n\n";
			cout << "Book Name:" << book_taken1 << endl << "Date taken:" << date1 << endl << endl;
			cout <<"Book Name:"<< book_taken2 << endl << "Date taken:" << date2 << endl;
			_getch();
		}
	}
	void return_book() {
		cls();
		if (book_taken1 == "N/A"&&book_taken2 == "N/A")
		{
			cout << "\nYou haven't taken any books\n";
			_getch();
		}
		else {
			int i = 0;
			cout << "\nEnter your choice\n\n";
			if ((strcmp(book_taken1.c_str(), "N/A") != 0)&&(strcmp(book_taken2.c_str(), "N/A") == 0))
			{
				cout << "1." << book_taken1 << endl;
				cin >> i;
				if (i == 1)
					calculator(book_taken1, date1);
				else
					cout << "\nInvalid option\n";
				_getch();
			}
			if ((strcmp(book_taken1.c_str(), "N/A") == 0) && (strcmp(book_taken2.c_str(), "N/A") != 0))
			{
				cout << "1." << book_taken2 << endl;
				cin >> i;
				if (i == 1)
					calculator(book_taken2, date2);
				else
					cout << "\nInvalid option\n";
				_getch();
			}
			if ((strcmp(book_taken1.c_str(), "N/A") != 0) && (strcmp(book_taken2.c_str(), "N/A") != 0))
			{
				cout << "1." << book_taken1 << endl;
				cout << "2." << book_taken2 << endl;
				cin >> i;
				if (i == 1)
					calculator(book_taken1, date1);
				else if (i == 2)
					calculator(book_taken2, date2);
				else
					cout << "\nInvalid option\n";
				_getch();
			}


		}
	}
	void calculator(string name,string date) {
		cls();
		book temp=intake(name);
		int days,sum=0;
		cout << "Enter number of days\n";
		cin >> days;
		cls();
		cout << "Return Statement:\n";
		cout << "Book: " << temp.book_name << endl << "Date taken: " << date << endl;
		if (days <=7) {
			sum = days*temp.cost;
		}
		else {
			sum = 10 + days*(temp.cost + 1);
		}
		cout << "Cost of book per day: " <<temp.cost<<endl<<"No: of days taken: "<<days<<"\nNet amount: "<< sum << endl;
		temp.quanitity++;
		bookdumper(temp);
		if (strcmp(name.c_str(), book_taken1.c_str()) == 0)
		{
			//cout << "deleting one\n";
			date1 = "N/A";
			book_taken1 = "N/A";
			//_getch();
		}
		if(strcmp(name.c_str(), book_taken2.c_str()) == 0)
		{
			//cout << "deleting 2\n";
			
			date2 = { "N/A" };
			book_taken2 = { "N/A" };
			//_getch();
		}

		dumper();
		_getch();
		cls();

	}
//---------------------------------------------------------------------------Student menu----------------------------------------------------------------
	void student_menu() {
		
		char ch = ' ';
		do {
			cls();
			cout << "\nEnter your choice\n\n<s> Search\n\n<t> Take book\n\n<m> Change password\n\n<r> Return Book\n\n<d> Display Book details\n\n<l> Log out\n";
			cin >> ch;
			switch (ch)
			{
			case 's':searchresults();
				break;
			case 't':take_book();
				break;
			case 'm':cpass();
				break;
			case 'x':userdetails();
				break;
			case 'r':return_book();
				break;
			// -----------------------------case 'l':return;
				//break;
			case 'd':cls();
				cout << "Enter book name\n";
				string line;
				cin.ignore();
				cin.clear();
				getline(cin, line);
				book temp = intake(line);
				bdis(temp);
				break;
			
			};
		} while (ch !='l');
		cls();
	}
	};
//------------------------------------------------------------------------Function declarations---------------------------------------------------------
void clrscr();
void login_page();
void login();
void signup();
void enter(string );
int identify(string);
void create();
//------------------------------------------------------------------------Function definations------------------------------------------------------------
void clrscr() {
	for (int i = 0; i < 100; i++)
		cout << "\n";
}
void login() {
	clrscr();
	string temp_userid1;
	cout << "\nUser-id: ";
	cin >> temp_userid1;
	users.open(temp_userid1,ios::in);
	if (users.is_open())
	{
		cout << "Password :";
		string temp_pass = {};
		temp_pass = take_password();
		string org_pass = {};
		getline(users, org_pass);
		if (strcmp(org_pass.c_str(), temp_pass.c_str())==0)
		{
			users.close();
			enter(temp_userid1);
			
		}
		else {
			cout << "\nInvalid Password";
			users.close();
			_getch();
			clrscr();
			login();
		}
	}
	else {
		_getch();
		char ch;
		do {
			cout << "\nThe user doesnt exist\n";
			cout << "Enter c to create a new user\nEnter l to login with different user\n";
			
			cin >> ch;
			//ch = _getch();
			switch (ch)
			{
			case 'c':signup();
				break;
			case 'l':login();
				break;
			default:cout << "Invalid option\n";
				_getch();
				clrscr();
				//login();
				break;
			};
		} while (ch != 'c' || ch != 'l');
	}

}
void signup() {
	clrscr();
	string tuser_id, tpass, tname, fname;
	cout << "\t\t\tSign-Up Infomation\n";
	cout << "\nUser-Id:";
	cin >> tuser_id;
	cout << "\nPassword: ";
	tpass = take_password();
	cout << "\nName :";
	cin>>tname;
	transform(tuser_id.begin(), tuser_id.end(), tuser_id.begin(), ::tolower);
	users.open(tuser_id.c_str(),ios::out);
	if (users.is_open())
	{
		users << tpass;
		users << endl;
		users << tname;
		users << endl;
		users << "N/A";
		users << endl;
		users << "N/A";
		users << endl;
		users << "N/A" << endl;
		users << "N/A" << endl;
		cout << "User created successfully\n";
		users.close();
		_getch();
		clrscr();
		//login_page();
	}
	else {
		cout << "Couldnt create a user. Please try again\n";
		_getch();
		//login_page();
	}
	
}
void login_page()
{
	clrscr();
	
	char ch=' ';
	do {
		ch = ' ';
		cout << "\t\tWelcome to The Library \n";
		cout << "\t\tEnter l to login \n\t\tEnter s to sign up\n\t\tEnter e to exit\n";
		cin >> ch;
		switch (ch) {
		case 'l':login();
			break;
		case 's':signup();
			break;
		case 'e'://out();
			exit(0);
			break;
		default:cout << "Invalid option\n";
			_getch();
			//login_page();
			clrscr();
			break;
		};
	} while (ch != 'l' || ch != 's' || ch != 'e');
}
int identify(string temp_userid3) {
	admins.open("admins.dat",ios::in);
	string line;
	bool flag = 0;
	while (getline(admins, line)) {
		if (strcmp(line.c_str(),temp_userid3.c_str())==0) {
			flag = 1;
			break;
		}
	}
	if (flag)
		return 1;
	else return 0;
	admins.close();
}
void enter(string temp_userid2){
	
	//cout << "\nEnter function\n";
	if (identify(temp_userid2))
	{
		//cout << "\nYour an admin\n\n";
		admin var;
		var.copier(temp_userid2);
		var.admin_menu();


	}
	else
	{
		//cout << "Your an user\n";
		student var;
		var.copier(temp_userid2);
		var.copier1(temp_userid2);
		var.student_menu();
	}

	//cout << "you have entered\n";
	_getch();

}
void create() {
	admins.open("admins.dat", ios::out);
	admins << "admin";
	admins.close();
	
	allbooks.open("allbooks.dat", ios::out);
	allbooks << "hello"<<endl;
	allbooks.close();

	authornames.open("author_name.dat",ios::out);
	authornames << "Hello"<<endl;
	authornames.close();

	genere.open("genere.dat",ios::out);
	genere << "Hello"<<endl;
	genere.close();

	publisher.open("publisher.dat", ios::out);
	publisher << "Hello"<<endl;
	publisher.close();

}
//--------------------------------------------------------------------------Main-----------------------------------------------------------------
void main() {
	login_page();
	_getch();
}
