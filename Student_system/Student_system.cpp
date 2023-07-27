#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct student {
	string username;
	string password;
	int id;
};

struct course {
	string name;
	string code;
};

const int MAX_STUDENTS = 100;
const int MAX_COURSES = 100;

student students[MAX_STUDENTS];
int numstudents = 0;

course courses[MAX_COURSES];
int numcourses = 0;

bool login(string user, string pass)
{
	for (int i = 0; i < numstudents; i++)
	{
		if (students[i].username == user && students[i].password == pass)
		{
			return true;
		}
	}
	return false;
}

void singup(student user)
{
	students[numstudents] = user;
	numstudents++;
	ofstream singupfile("students.txt", ios::app);
	singupfile << user.username << "   " << user.password << "   " << user.id << endl;
	singupfile.close();
}

void addcourse(course course)
{
	courses[numcourses] = course;
	numcourses++;
	ofstream addfile("courses.txt", ios::app);
	addfile << course.name << "   " << course.code << endl;
	addfile.close();
}

void displaycourses()
{
	for (int i = 0; i < numcourses; i++)
	{
		cout << "Course name :" << " " << courses[i].name << endl;
		cout << "Course code :" << " " << courses[i].code << endl;
		cout << "=====================" << endl;
	}
}

bool drop(string code)
{
	for (int i = 0; i < numcourses; i++)
	{
		if (courses[i].code == code)
		{
			for (int j = 0; j < numcourses - 1; j++)
			{
				courses[j] = courses[j + 1];
			}
			numcourses--;
			ofstream addfile("courses.txt");
			for (int j = 0; j < numcourses; j++)
			{
				addfile << courses[j].name << "   " << courses[j].code << endl;
			}
			addfile.close();
			return true;
		}
	}
	return false;
}

bool updateuser(string username, string newpass)
{
	for (int i = 0; i < numstudents; i++)
	{
		if (students[i].username == username)
		{
			students[i].password = newpass;
			ofstream singupfile("students.txt");
			for (int j = 0; j < numstudents; j++)
			{
				singupfile << students[j].username << "  " << students[j].password << "  " << students[j].id << endl;
			}
			singupfile.close();
			return true;
		}
	}
	return false;
}

bool string_compare(string value, string search_name)
{
	int size = search_name.length();
	for (int i = 0; i < size; i++)
	{
		if (value[i] != search_name[i])
		{
			return false;
		}
	}
	return true;
}

bool searchbyname(string name)
{
	for (int i = 0; i < numstudents; i++)
	{
		if (string_compare(courses[i].name, name) == 1)
		{
			return true;
		}
	}
	return false;
}

bool searchbycode(string code)
{
	for (int i = 0; i < numcourses; i++)
	{
		if (string_compare(courses[i].code, code) == 1)
		{
			return true;
		}
	}
	return false;
}

void showmenue1()
{
	cout << " Chooce login method : " << endl;
	cout << " 1:-) login " << endl;
	cout << " 2:-) sing up " << endl;
}


void showmenue2()
{
	cout << " 1:-) Add course           " << endl;
	cout << " 2:-) Drop course          " << endl;
	cout << " 3:-) Display all cousrses " << endl;
	cout << " 4:-) Search               " << endl;
	cout << " 5:-) Change username      " << endl;
}
void showmenue3()
{
	cout << " 1:-) search by name " << endl;
	cout << " 2:-) search by code " << endl;

}





int main()
{
	int choice;
	string name, pass;
	while (true)
	{
		showmenue1();
		cin >> choice;
		if (choice == 1)
		{
			cout << "Enter your name :     " << endl;
			cin >> name;
			cout << "Enter your password : " << endl;
			cin >> pass;
			if (login(name, pass))
			{
				cout << "Login successful!" << endl;
				while (true)
				{
					showmenue2();
					cin >> choice;
					if (choice == 1)
					{
						course course;
						cout << "Enter course name : " << endl;
						cin >> course.name;
						cout << "Enter course code : " << endl;
						cin >> course.code;
						addcourse(course);
						cout << "Course added successfully" << endl;
					}
					else if (choice == 2)
					{
						string code;
						cout << "Enter code of the course you need to drop: " << endl;
						cin >> code;
						if (drop(code))
						{
							cout << "Course droped successfullY" << endl;
						}
						else
						{
							cout << "Course not found! " << endl;
						}
					}
					else if (choice == 3)
					{
						displaycourses();
					}
					else if (choice == 4)
					{

						showmenue3();
						cin >> choice;
						if (choice == 1)
						{
							string name;
							cout << "Enter course name :" << endl;
							cin >> name;
							if (searchbyname(name) == 1)
							{
								cout << "The course found" << endl;
							}
							else
							{
								cout << "The course not found!" << endl;
							}
						}
						else if (choice == 2)
						{
							string code;
							cout << "Enter the course code :" << endl;
							cin >> code;
							if (searchbycode(code) == 1)
							{
								cout << "The course found" << endl;
							}
							else
							{
								cout << "The course not found!" << endl;
							}
						}
						else
						{
							cout << "Invalid choice!" << endl;
						}

					}
					else if (choice == 5)
					{
						string newname;
						cout << "Enter new name:" << endl;
						cin >> newname;
						if (updateuser(name, newname))
						{
							cout << "Username updated successfully!" << endl;
							name = newname;
						}
						else
						{
							cout << "Failed to update username!" << endl;
						}

					}
					else
					{
						cout << "Invalid choice!" << endl;
					}
				}
			}
			else
			{
				cout << "Invalid username or password. Please try again!" << endl;
			}
		}
		else if (choice == 2)
		{
			student newstudent;
			cout << "enter your name :" << endl;
			cin >> newstudent.username;
			cout << "enter your password :" << endl;
			cin >> newstudent.password;
			cout << "enter your id :" << endl;
			cin >> newstudent.id;
			singup(newstudent);
			cout << "Sign up successful! Please login with your new account." << endl;
		}
		else
		{
			cout << "Invalid choice!" << endl;
		}
	}

	return 0;
}