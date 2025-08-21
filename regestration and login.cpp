//Please run the program to start using the application

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

class User
{
    protected:
        string userID;
        string password;
    public:
        User(string name, string pass)
        {
            userID=name;
            password=pass;
        }
        // initialising getter functions for login purpusses
        string getUserID()
        {
            return userID;
        }
        string getPassword()
        {
            return password;
        }
};

class Teacher;
class Student;

class Course
{
public:
    string courseID;
    string course_name;
    string teacherID;
    unordered_set <string> enrolled_students;

    Course (string _courseID , string _course_name , string _teacherID){
        courseID = _courseID;
        course_name = _course_name;
        teacherID = _teacherID;
    }

    void add_student ( string _studentID){
        enrolled_students.insert(_studentID);
    }

    void save_to_file(std::ofstream& outFile) {
        outFile << courseID << "\n";
        outFile << course_name << "\n";
        outFile << teacherID << "\n";
        outFile << enrolled_students.size() << "\n";  // Store number of students

        for (const string& studentID : enrolled_students) {
            outFile << studentID << "\n";  // Store each student's ID
        }
    }

    static Course* load_from_file(std::ifstream& inFile) {
        string courseID, course_name, teacherID;
        getline(inFile, courseID);
        getline(inFile, course_name);
        getline(inFile, teacherID);

        Course* course = new Course(courseID, course_name, teacherID);

        int num_students;
        inFile >> num_students;
        inFile.ignore();  // Ignore the newline after reading the number

        for (int i = 0; i < num_students; ++i) {
            string studentID;
            getline(inFile, studentID);
            course->add_student(studentID);
        }

        return course;
    }

};

class Project
{
public:
    string projectID;
    string project_name;
    Teacher* teacher;
    unordered_set <Student*> enrolled_students;

    Project (string _projectID , string _project_name , Teacher* _teacher){
        projectID = _projectID;
        project_name = _project_name;
		teacher = _teacher;
    }

    void add_student ( Student* _student){
        enrolled_students.insert(_student);
    }
};

class DataBase
{
    public:
        vector <Student*> students_list;
        vector <Teacher*> teachers_list;
        vector <Course*> courses_list;
        vector <Project*> projects_list;

        vector<Course* > show_all_courses  (){
			return courses_list;
		}
        vector<Project*> show_all_projects (){
			return projects_list;
		}
		vector<Teacher*> show_all_teachers (){
			return teachers_list;
		}
        vector<Student*> show_all_students (){
            return students_list;
        }
};

class Teacher:public User
{
    public:
		string name;
        vector<pair<Student*,Course*>> requests;

        Teacher(string userID, string pass, string _name) : User(userID,pass){
            name = _name;
        }

        void save_to_file (ofstream & outFile){
            outFile << userID << "\n" << password << "\n" << name << "\n";
        }

        static Teacher* load_from_file(ifstream & inFile){
            string userID, password, name;

            getline(inFile,userID);
            getline(inFile,password);
            getline(inFile,name);

            return new Teacher(userID,password,name);
        }

        vector<Course*> show_my_courses (DataBase* d){
            vector<Course*> all_courses = d->courses_list;
            vector<Course*> my_courses;
            int n = all_courses.size();
            for(int i =0 ; i<n ;i++){
                if(all_courses[i]->teacherID == this->userID){
                    my_courses.push_back(all_courses[i]);
                }
            }
            return my_courses;
        }

        vector<Project*> show_my_projects (DataBase* d){
            vector<Project*> all_projects = d->projects_list;
            vector<Project*> my_projects;
            int n = all_projects.size();
            for(int i =0 ; i<n ;i++){
                if(all_projects[i]->teacher == this){
                    my_projects.push_back(all_projects[i]);
                }
            }
            return my_projects;
        }
};

class Student:public User
{
    public:
        string name;
        int CGPA ;
    
        Student(string userID, string pass, string _name, int cg =8):User(userID,pass){
            name = _name;
            CGPA = cg;
        }

        void save_to_file (ofstream & outFile){
            outFile << userID << "\n" << password << "\n" << name << "\n" << CGPA << "\n";
        }

        static Student* load_from_file(ifstream & inFile){
            string userID, password, name;

            int CGPA;
            getline(inFile,userID);
            getline(inFile,password);
            getline(inFile,name);
            inFile>>CGPA;
            inFile.ignore();

            return new Student(userID,password,name,CGPA);
        }



        vector<Course*> show_my_courses (DataBase* d){
            vector<Course*> all_courses = d->courses_list;
            vector<Course*> my_courses;
            int n = all_courses.size();
            for(int i =0 ; i<n ;i++){
                if(all_courses[i]->enrolled_students.find(this->userID) != all_courses[i]->enrolled_students.end()){
                    my_courses.push_back(all_courses[i]);
                }
            }
            return my_courses;
        }

        vector<Project*> show_my_projects (DataBase* d){
            vector<Project*> all_projects = d->projects_list;
            vector<Project*> my_projects;
            int n = all_projects.size();
            for(int i =0 ; i<n ;i++){
                if(all_projects[i]->enrolled_students.find(this) != all_projects[i]->enrolled_students.end()){
                    my_projects.push_back(all_projects[i]);
                }
            }
            return my_projects;
        }

        int show_my_CGPA(){
            return CGPA;
        }

        void generate_request();
};

void student_page (Student* student , DataBase* d){

    int select = 0;
    do
    {
        cout<<"\n\n------------- STUDENT PORTEL --------------"<<endl;
        cout<<"******  Get work done page  ******"<<endl;
        cout<<"1.Show my courses"<<endl;
        cout<<"2.Show my projects"<<endl;
        cout<<"3.Show all courses"<<endl;
        cout<<"4.Show all projects"<<endl;
        cout<<"5.Show all teachers"<<endl;
        cout<<"6.Register for a course"<<endl;
        cout<<"7.Register for a project"<<endl;
        cout<<"8.Go back to main menu"<<endl;
        cout<<"Enter Your Choice : ";

        cin>>select;

        switch(select){
            case 1:{
                vector<Course*> my_curses = student->show_my_courses(d);
                cout<<"Here is the list of your courses :"<<endl;
                for(int i=0; i<my_curses.size(); i++){
                    cout<< i+1 << " -> course ID :" << my_curses[i]->courseID<< " -> course name :" << my_curses[i]->course_name<<endl;
                }
                break;
            }
            case 2:{
                vector<Project*> my_projects = student->show_my_projects(d);
                cout<<"Here is the list of your projects :"<<endl;
                for(int i=0; i<my_projects.size(); i++){
                    cout<< i+1 << " -> project ID :" << my_projects[i]->projectID << " -> project name :" << my_projects[i]->project_name<<endl;
                }
                break;
            }
            case 3:{
                vector<Course*> all_curses = d->show_all_courses();
                cout<<"Here is the list of all courses :"<<endl;
                for(int i=0; i<all_curses.size(); i++){
                    cout<< i+1 << " -> course ID :" << all_curses[i]->courseID<< " -> course name :" << all_curses[i]->course_name<<" -> course teacherID :" << all_curses[i]->teacherID<<endl;
                }
                break;
            }
            case 4:{
                vector<Project*> all_projects = d->show_all_projects();
                cout<<"Here is the list of all projects :"<<endl;
                for(int i=0; i<all_projects.size(); i++){
                    cout<< i+1 << " -> project ID :" <<all_projects[i]->projectID << " -> project name :" << all_projects[i]->project_name<<endl;
                }
                break;
            }
            case 5:{
                vector<Teacher*> all_teachers = d->show_all_teachers();
                cout<<"Here is the list of all teachers :"<<endl;
                for(int i=0; i<all_teachers.size(); i++){
                    cout<< i+1 << " -> teacher ID :" <<all_teachers[i]->getUserID() << " -> project name :" << all_teachers[i]->name<<endl;
                }
                break;
            }
            case 6:{
                string courseID;
                bool found = false;
                Course* c;

                do{
                    cout<<"\nPlease mention the course ID of the course you want to join :";
                    cin>>courseID;

                    vector<Course*> all_courses = d->courses_list;
                    int n = all_courses.size();
                    
                    
                    for(int i=0 ; i<n; i++){
                        if(all_courses[i]->courseID == courseID){
                            c = all_courses[i];
                            found = true;
                            break;
                        }
                    }

                    if(found == false){
                        cout<<"\nCourseID provided is Invalid, please recheck. Please type 0 if you want to exit, or type 1 if you want to retry.\n";
                        bool retry = true;
                        cin>>retry;
                        if(retry == false)  return;
                    }

                }while(found==false);

                if(found == true){
                    int n = d->teachers_list.size();
                    Teacher* course_teacher;
                    for(int i=0 ; i<n ; i++){
                        if(d->teachers_list[i]->getUserID() == c->teacherID){
                            course_teacher = d->teachers_list[i];
                            break;
                        }
                    }
                    course_teacher->requests.push_back({student,c});
                    cout<<"\nYou have successfully sent a request. Please wait till the professor accepts it.\n";
                }
                break;
            }
            case 7:{
                cout<<"yet to add this function"<<endl;
                break;
            }
            case 8:{
                break;
            }
            default:{
                cout<<"enter valid option"<<endl;
            }
        }
	}while (select!=8);
}
void teacher_page (Teacher* teacher , DataBase* d){

    int select=0;

    do{
        cout<<"\n\n------------- TEACHER PORTEL --------------"<<endl;
        cout<<"******  Get work done page  ******"<<endl;
        cout<<"1.Show my courses"<<endl;
        cout<<"2.Show my projects"<<endl;
        cout<<"3.Deal with the requests"<<endl;
        cout<<"4.Show all courses"<<endl;
        cout<<"5.Show all projects"<<endl;
        cout<<"6.Add a course"<<endl;
        cout<<"7.Add a project"<<endl;
        cout<<"8.Go back to main menu"<<endl;
        cout<<"Enter Your Choice : ";

        
        cin>>select;

        switch(select){
            case 1:{
                vector<Course*> my_curses = teacher->show_my_courses(d);
                cout<<"Here is the list of your courses :"<<endl;
                for(int i=0; i<my_curses.size(); i++){
                    cout<< i+1 << " -> course ID :" << my_curses[i]->courseID<< " -> course name :" << my_curses[i]->course_name<<endl;
                }
                break;
            }
            case 2:{
                vector<Project*> my_projects = teacher->show_my_projects(d);
                cout<<"Here is the list of your projects :"<<endl;
                for(int i=0; i<my_projects.size(); i++){
                    cout<< i+1 << " -> project ID :" << my_projects[i]->projectID << " -> project name :" << my_projects[i]->project_name<<endl;
                }
                break;
            }
            case 3:{
                vector<pair<Student*,Course*>> requests = teacher->requests;
                int n = requests.size();

                for(int i=n-1 ; i>=0 ; i--){
                    Student* s = requests[i].first;
                    Course*  c = requests[i].second;
                    cout<<"Request from studentID:"<<s->getUserID()<<" , to join the courseID:"<<c->courseID<<endl;
                    cout<<"Please select from below :"<<endl;
                    cout<<"1.Accept"<<endl;
                    cout<<"2.Reject"<<endl;
                    cout<<"3.Deal Later"<<endl;
                    cout<<"4.exit"<<endl;
                    cout<<"Enter your choice :";

                    int select =0;
                    cin>>select;

                    if(select == 1){
                        c->add_student(s->getUserID());
                        requests.erase(requests.begin()+i);
                        cout<<"\nStudent Successfully Added to the course"<<endl;
                    }
                    else if(select == 2){
                        requests.erase(requests.begin()+i);
                        cout<<"\nStudent Denied to the course"<<endl;
                    }
                    else if(select == 3){
                        cout<<"Deal Later option selected."<<endl;
                    }
                    else if(select = 4){
                        return;
                    }
                    else{
                        cout<<"\nplease enter valid choice"<<endl;
                        i++;
                    }
                }
                break;
            }
            case 4:{
                vector<Course*> all_curses = d->show_all_courses();
                cout<<"Here is the list of all courses :"<<endl;
                for(int i=0; i<all_curses.size(); i++){
                    cout<< i+1 << " -> course ID :" << all_curses[i]->courseID<< " -> course name :" << all_curses[i]->course_name<<endl;
                }
                break;
            }
            case 5:{
                vector<Project*> all_projects = d->show_all_projects();
                cout<<"Here is the list of all projects :"<<endl;
                for(int i=0; i<all_projects.size(); i++){
                    cout<< i+1 << " -> project ID :" <<all_projects[i]->projectID << " -> project name :" << all_projects[i]->project_name<<endl;
                }
                break;
            }
            case 6:{
                string course_name ;
                cout<<"What is the name of your course :";
                cin>> course_name;

                string courseID ;
                cout<<"Create a unique course ID :";
                cin>> courseID;

                Course* course = new Course(courseID,course_name,teacher->getUserID());
                d->courses_list.push_back(course);
                break;
            }
            case 7:{
                string project_name ;
                cout<<"What is the name of your project :";
                cin>> project_name;

                string projectID ;
                cout<<"Create a unique course ID :";
                cin>> projectID;

                Project* project = new Project(projectID,project_name,teacher);
                break;
            }
            case 8:
                break;
            default:{
                cout<<"enter valid option"<<endl;
            }
        }
    }while(select != 8);

}

void teacher_registration_portal (Teacher* teacher, DataBase* d){
    vector<pair<Student*,Course*>> requests = teacher->requests;
    int n = requests.size();

    for(int i=n-1 ; i>=0 ; i--){
        Student* s = requests[i].first;
        Course*  c = requests[i].second;
        cout<<"Request from studentID:"<<s->getUserID()<<" , to join the courseID:"<<c->courseID<<endl;
        cout<<"Please select from below :"<<endl;
        cout<<"1.Accept"<<endl;
        cout<<"2.Reject"<<endl;
        cout<<"3.Deal Later"<<endl;
        cout<<"4.exit"<<endl;
        cout<<"Enter your choice :";

        int select =0;
        cin>>select;

        if(select == 1){
            c->add_student(s->getUserID());
            requests.erase(requests.begin()+i);
            cout<<"\nStudent Successfully Added to the course"<<endl;
        }
        else if(select == 2){
            requests.erase(requests.begin()+i);
            cout<<"\nStudent Denied to the course"<<endl;
        }
        else if(select == 3){
            cout<<"Deal Later option selected."<<endl;
        }
        else if(select = 4){
            return;
        }
        else{
            cout<<"\nplease enter valid choice"<<endl;
            i++;
        }
    }
}
void student_registration_portal (Student* student, DataBase* d){

    
}

Student* student_login (DataBase* d){

	string userID,password;
	cout<<"Enter your UserID : ";
	cin>>userID;
	cout<<"Enter Password : ";
	cin>>password;

	int n = d->students_list.size();

	for(int i=0 ; i<n ;i++){
		if(d->students_list[i]->getUserID() == userID && d->students_list[i]->getPassword() == password){
			return d->students_list[i];
		}
	}
	return nullptr;
}
Teacher* teacher_login (DataBase* d){
	string userID,password;
	cout<<"Enter your UserID : ";
	cin>>userID;
	cout<<"Enter Password : ";
	cin>>password;

	int n = d->teachers_list.size();

	for(int i=0 ; i<n ;i++){
		if(d->teachers_list[i]->getUserID() == userID && d->teachers_list[i]->getPassword() == password){
			return d->teachers_list[i];
		}
	}
	return nullptr;
}

void student_registration(DataBase* d){

	string _name;
	string _userID;
	string _password;

	cout<<"Enter your name : ";
	cin>>_name;
	cout<<"Enter a unique UserID : ";
	cin>>_userID;
	cout<<"Enter Password : ";
	cin>>_password;
	
	Student* s = new Student (_userID , _password, _name);
	d->students_list.push_back(s);
}
void teacher_registration(DataBase* d){

	string _name;
	string _userID;
	string _password;

	cout<<"Enter your name : ";
	cin>>_name;
	cout<<"Enter a unique UserID : ";
	cin>>_userID;
	cout<<"Enter Password : ";
	cin>>_password;
	
	Teacher* t = new Teacher (_userID , _password, _name);
	d->teachers_list.push_back(t);
}

void show_student_menu  (DataBase* d) {
	cout<<"\n\n------------- STUDENT PORTEL --------------"<<endl;
	cout<<"******  Login and Registration Page  ******"<<endl;
	cout<<"1.Student Login"<<endl;
	cout<<"2.New Student Registration"<<endl;
	cout<<"3.Return to main menu"<<endl;
	cout<<"Enter Your Choice : ";

	int select;
	cin>>select;

	if(select == 1){
		Student* std = student_login(d);
		if(std != nullptr){
			student_page(std,d);
		}
		else{
			cout<<"\nWrong credentials, please retry.\n";
			show_student_menu(d);
		}
	}
	else if(select ==2){
		student_registration(d);
	}
	else if(select ==3){
		return;
	}
	// else{
	// 	cout<<"please select a valid option.\n";
	// 	show_student_menu(d);
	// }
}
void show_teacher_menu  (DataBase* d) {
	cout<<"\n\n------------- TEACHERS PORTEL -------------"<<endl;
	cout<<"******  Login and Registration Page  ******"<<endl;
	cout<<"1.Teacher Login"<<endl;
	cout<<"2.New Teacher Registration"<<endl;
	cout<<"6.Return to main menu"<<endl;
	cout<<"Enter Your Choice : ";

    int select;
	cin>>select;

	if(select == 1){
		Teacher* tch = teacher_login(d);
		if(tch != nullptr){
			teacher_page(tch,d);
		}
		else{
			cout<<"\nWrong credentials, please retry.\n";
			show_teacher_menu(d);
		}
	}
	else if(select ==2){
		teacher_registration(d);
	}
	else if(select ==3){
		return;
	}
}

void show_main_menu (DataBase* d) {

	cout<<"\n******* Main Page *******\n\n";
	cout<<"Welcome! Which of the following are you : "<<endl;
	cout<<"1.Student"<<endl;
	cout<<"2.Teacher"<<endl;
	cout<<"3.Exit program"<<endl;
	cout<<"Enter the corresponding number: ";

    int select ;
	cin>> select;

	if(select == 1){
		show_student_menu(d);
	}
	else if(select == 2){
		show_teacher_menu(d);
	}
	else if(select == 3){
		return;
	}
	else{
		"\n please select a valid number.\n";
	}
	show_main_menu(d);
	return;
}

void load_all_students(DataBase* d){
    ifstream inFile("students.txt");
    while (!inFile.eof()) {
        Student* student = Student::load_from_file(inFile);
        if (!student->getUserID().empty()) {  // To avoid loading an empty student
            d->students_list.push_back(student);
        }
    }
    inFile.close();
}
void save_all_students(DataBase* d){
    ofstream outFile("students.txt");
    for (Student* student : d->students_list) {
        student->save_to_file(outFile);
    }
    outFile.close();
}

void load_all_teachers(DataBase* d){
    ifstream inFile("teachers.txt");
    while (!inFile.eof()) {
        Teacher* teacher = Teacher::load_from_file(inFile);
        if (!teacher->getUserID().empty()) {  // To avoid loading an empty student
            d->teachers_list.push_back(teacher);
        }
    }
    inFile.close();
}
void save_all_teachers(DataBase* d){
    ofstream outFile("teachers.txt");
    for (Teacher* teacher : d->teachers_list) {
        teacher->save_to_file(outFile);
    }
    outFile.close();
}

void load_all_courses(DataBase* d){
    ifstream inFile("courses.txt");
    while (!inFile.eof()) {
        Course* course = Course::load_from_file(inFile);
        if (!course->courseID.empty()) {  // Check to avoid loading empty courses
            d->courses_list.push_back(course);
        }
    }
    inFile.close();
}
void save_all_courses(DataBase* d){
    ofstream outFile("courses.txt");
    for (Course* course : d->courses_list) {
        course->save_to_file(outFile);
    }
    outFile.close();
}

void load_all_data(DataBase* d){
    load_all_students(d);
    load_all_teachers(d);
    load_all_courses(d);
    // load_all_projects(d);
}
void save_all_data(DataBase* d){
    save_all_students(d);
    save_all_teachers(d);
    save_all_courses(d);
    // save_all_projects(d);
}

int main()
{
	DataBase d ;
    load_all_data(&d);
	show_main_menu(&d);
    save_all_data(&d);
	return 0;
}

/*

Problems to be addressed:
->solving the request erasing problem
->adding all project functionalities just like courses
->adding viewing functionalities of student and teacher

*/
