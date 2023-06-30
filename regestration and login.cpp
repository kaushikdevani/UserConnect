//Please run the program to start using the application

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User
{
    private:
        string username;
        string password;
    public:
        User(string name, string pass)
        {
            username=name;
            password=pass;
        }
        // initialising getter functions for login purpusses
        string getUsername()
        {
            return username;
        }
        string getPassword()
        {
            return password;
        }
};

class Teacher:public User
{
    private:
        string subject;
    public:
        Teacher(string name, string pass,string sub):User(name,pass)
        {
            subject=sub;
        }
        string getSubject()
        {
            return subject;
        }
};

class Student:public User
{
    private:
        int CGPA;
    public:
        Student(string name, string pass, int cg):User(name,pass)
        {
            CGPA = cg;
        }
        int getCGPA()
        {
            return CGPA;
        }
};

class UserManager
{
    private:
        vector <Student> students_list;
        vector <Teacher> teachers_list;
    public:
        void RegisterUser(int user_portal)
        {
            string username;
            string password , subject;
            int CGPA;

            cout<<"Enter a unique User Name : ";
            cin>>username;
            cout<<"Enter Password : ";
            cin>>password;

            if(user_portal==1)
            {
                cout<<"Enter your CGPA : ";
                cin>>CGPA;
                Student new_user = Student(username,password,CGPA);
                students_list.push_back(new_user);
                cout<<"** You have SUCCESSFULLY Registered! **"<<endl;
            }
            else
            {
                cout<<"Enter your Subject : ";
                cin>>subject;
                Teacher new_user = Teacher(username,password,subject);
                teachers_list.push_back(new_user);
                cout<<"** You have SUCCESSFULLY Registered! **"<<endl;
            }
            
        }

        bool Login(string name,string pass,int user_portal)
        {
            if(user_portal==1)
            {
                for(int i = 0;i<students_list.size();i++)
                {
                    if(students_list[i].getUsername()==name && students_list[i].getPassword()==pass)
                    {
                        cout<<"Login SUCCESSFUL !"<<endl;
                        cout<<"Student Name : "<<name<<endl;
                        cout<<"Student CGPA : "<<students_list[i].getCGPA()<<endl;
                        return true;
                    }
                }
                cout<<"Wrong Username or Password!\n";
                cout<<"Please Enter correct credentials"<<endl;
                return false;
            }
            else
            {
                for(int i = 0;i<teachers_list.size();i++)
                {
                    if(teachers_list[i].getUsername()==name && teachers_list[i].getPassword()==pass)
                    {
                        cout<<"Login SUCCESSFUL !";
                        cout<<"Teacher's Name : "<<name<<endl;
                        cout<<"Teacher's Subject : "<<teachers_list[i].getSubject()<<endl;
                        return true;
                    }
                }
                cout<<"Wrong Username or Password!\n";
                cout<<"Please Enter correct credentials"<<endl;
                return false;
            }

        }

        void Show_students_list()
        {
            cout<<"****** Student List ******"<<endl;
            for(int i=0;i<students_list.size();i++)
            {
                cout<<students_list[i].getUsername()<<endl;
            }
        }

        void Show_teachers_list()
        {
            cout<<"****** Teacher's List ******"<<endl;
            for(int i=0;i<teachers_list.size();i++)
            {
                cout<<teachers_list[i].getUsername()<<"-->"<<teachers_list[i].getSubject()<<endl;
            }
        }

        bool Search_student(string username)
        {
            for(int i=0;i<students_list.size();i++)
            {
                if(students_list[i].getUsername()==username)
                {
                    cout<<"Student Name   : "<<username<<endl;
                    cout<<"Student's CGPA : "<<students_list[i].getCGPA()<<endl;
                    return true;
                }
            }
            cout<<"Enter valied students username\n";
            return false;
        }

        void delete_user(string username, string password, int user_portal)
        {
            if(user_portal==1)
            {
                for(int i=0;i<students_list.size();i++)
                {
                    if(students_list[i].getUsername()==username && students_list[i].getPassword()==password)
                    {
                        students_list.erase(students_list.begin()+i);
                        cout<<"Student User Removed Successfully."<<endl;
                    }
                }
            }
            else
            {
                for(int i=0;i<teachers_list.size();i++)
                {
                    if(teachers_list[i].getUsername()==username && teachers_list[i].getPassword()==password)
                    {
                        teachers_list.erase(teachers_list.begin()+i);
                        cout<<"Teacher User Removed Successfully."<<endl;
                    }
                }
            }
        }
};

int main()
{
    UserManager user_manage;
    int user_portal;
    int user_option= 1;
    while(user_option!=0)
    {
        cout<<"\n******* Main Page *******\n\n";
        cout<<"Welcome! Which of the following are you : "<<endl;
        cout<<"1.Student"<<endl;
        cout<<"2.Teacher"<<endl;
        cout<<"3.Exit program"<<endl;
        cout<<"Enter the corresponding number: ";
        cin>>user_portal;
        int user_choice;

        if(user_portal==1)
        {
            cout<<"\nYou are being redirected to student's portal"<<endl;
            do
            {
                cout<<"\n\n------------- STUDENT PORTEL --------------"<<endl;
                cout<<"******  Login and Registration Page  ******"<<endl;
                cout<<"1.Student Login"<<endl;
                cout<<"2.New Student Registration"<<endl;
                cout<<"3.Teacher's List"<<endl;
                cout<<"4.Delete User"<<endl;
                cout<<"5.Return to main menu"<<endl;
                cout<<"Enter Your Choice : ";
                cin>>user_choice;
                string username,password;
                switch(user_choice)
                {
                    case 1:
                        bool correct;
                        cout<<"Enter your Username : ";
                        cin>>username;
                        cout<<"Enter Password : ";
                        cin>>password;
                        correct = user_manage.Login(username,password,user_portal);
                        break;
                    case 2:
                        user_manage.RegisterUser(user_portal);
                        break;
                    case 3:
                        //first verifing that the user is a student
                        cout<<"Enter your Username : ";
                        cin>>username;
                        cout<<"Enter Password : ";
                        cin>>password;
                        correct = user_manage.Login(username,password,user_portal);

                        //now showing the teachers list
                        if(correct)
                            user_manage.Show_teachers_list();
                        else
                            cout<<"Enter valied credentials"<<endl;
                        break;
                    case 4:
                        cout<<"You are trying to delete your account"<<endl;
                        cout<<"Enter your user Name : ";
                        cin>>username;
                        cout<<"Are you sure you want to delete your account"<<endl;
                        cout<<"If yes, Enter your Password : ";
                        cin>>password;
                        user_manage.delete_user(username,password,user_portal);
                        break;
                    case 5:
                        break;
                }
            } while (user_choice!=5);
        
        }
        else if(user_portal==2)
        {
            cout<<"\nYou are being redirected to teacher's portal"<<endl;

            do
            {
                cout<<"\n\n------------- TEACHERS PORTEL -------------"<<endl;
                cout<<"******  Login and Registration Page  ******"<<endl;
                cout<<"1.Teacher Login"<<endl;
                cout<<"2.New Teacher Registration"<<endl;
                cout<<"3.show students list"<<endl;
                cout<<"4.search a student"<<endl;
                cout<<"5.Delete User"<<endl;
                cout<<"6.Return to main menu"<<endl;
                cout<<"Enter Your Choice : ";
                cin>>user_choice;
                string username ,password;

                switch(user_choice)
                {
                    case 1:
                        bool correct;
                        cout<<"Enter your Username : ";
                        cin>>username;
                        cout<<"Enter Password : ";
                        cin>>password;
                        correct = user_manage.Login(username,password,user_portal);
                        break;
                    case 2:
                        user_manage.RegisterUser(user_portal);
                        break;
                    case 3:
                    //only if teacher login is true
                        cout<<"First verify you are a teacher by entering your login credentials."<<endl;
                        cout<<"Enter your Username : ";
                        cin>>username;
                        cout<<"Enter Password : ";
                        cin>>password;
                        correct = user_manage.Login(username,password,user_portal);
                        //now we show the student list
                        if(correct)
                            user_manage.Show_students_list();
                        else
                            cout<<"Invalied login credentials\n";
                        break;
                    case 4:
                    //only if teacher login is true
                        cout<<"First verify you are a teacher by entering your login credentials."<<endl;
                        cout<<"Enter your Username : ";
                        cin>>username;
                        cout<<"Enter Password : ";
                        cin>>password;
                        correct = user_manage.Login(username,password,user_portal);

                        //now we do the search
                        if(correct)
                        {
                            bool found;
                            string name;
                            cout<<"Enter Student's username : ";
                            cin>>name;
                            found=user_manage.Search_student(name);
                            if(!found)
                                cout<<"Invalied student username\n";                  
                        }
                        else
                                cout<<"Enter valied credentials"<<endl;
                        break;
                    case 5:
                        cout<<"You are trying to delete your account"<<endl;
                        cout<<"Enter your user Name : ";
                        cin>>username;
                        cout<<"Are you sure you want to delete your account"<<endl;
                        cout<<"If yes, Enter your Password : ";
                        cin>>password;
                        user_manage.delete_user(username,password,user_portal);
                        break;
                    case 6:
                        break;
                }
            } while (user_choice!=6);
        }
        else
            cout<<"\nEnter valied option\n"<<endl;
    }
}