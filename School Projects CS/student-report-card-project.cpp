//*********************************************
//~~~~~~~HEADER FILE USED IN PROJECT~~~~~~~~~~~
//*********************************************

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

//********************************************
//~~~~~~~~CLASS USED IN PROJECT~~~~~~~~~~~~~~~
//********************************************

class student
{
    int rollno;
    char name[50];
    int p_marks, c_marks, m_marks, e_marks, cs_marks, as_marks;
    double per;
    char grade;
    void calculate();        //function to calculate grade

public:
    void getdata();            //function to accept data from user
    void showdata() const;     //function to show data on screen
    void show_tabular() const;
    int retrollno() const;

};//Class end here

//CALCULATE() START  HERE

void student::calculate()
{
    int minimum = min({p_marks,c_marks,m_marks,cs_marks});
    per=( p_marks + c_marks + m_marks + e_marks + cs_marks + as_marks - minimum )/5.0;
    if(per >= 75)
    {
        grade = 'A';
    }
    else if(per >= 60)
    {
        grade = 'B';
    }
    else if(per >= 45)
    {
        grade = 'C';
    }
    else if(per >= 30)
    {
        grade = 'D';
    }
    else 
    {
        grade = 'F';
    }
}

//CALCULATE() END HERE

//getdata() start here

void student::getdata()
{
    cout << "\nEnter the Roll No. of student : ";
    cin >> rollno;
    cout << "\nEnter the name of the student : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nEnter the marks in Physics out of 100 : ";
    cin >> p_marks;
    cout << "\nEnter the marks in Chemistry out of 100 : ";
    cin >> c_marks;
    cout << "\nEnter the marks in Maths out of 100 : ";
    cin >> m_marks;
    cout << "\nEnter the marks in English out of 100 : ";
    cin >> e_marks;
    cout << "\nEnter the marks in Computer Science out of 100 : ";
    cin >> cs_marks;
    cout << "\nEnter the marks in Assamese out of 100 : ";
    cin >> as_marks;
    calculate();
}
//getdata() end here

//showdata() start here
void student::showdata() const
{
    cout << "\nRoll number of student : " << rollno;
    cout << "\nName of student : " << name;
    cout << "\nMarks in Physics : " << p_marks;
    cout << "\nMarks in Chemistry : " << c_marks;
    cout << "\nMarks in Mathematics : " << m_marks;
    cout << "\nMarks in English : " << e_marks;
    cout << "\nMarks in Computer Science : " << cs_marks;
    cout << "\nMarks in Assamese : " << as_marks;
    cout << "\nPercentage of student is : " << per;
    cout << "\nGrade of student is : " << grade;
}
//showdata() end here

//show_tabular() start here
void student::show_tabular() const
{
    cout << rollno << setw(6) << " " << name << setw(10) << p_marks << setw(4) << c_marks << setw(4) << m_marks << setw(4) << e_marks << setw(4) << cs_marks << setw(4) << as_marks << setw(8) << per << setw(6) << grade << endl;
}
//show_tabular() end here

//retrollno() start here
int student::retrollno() const
{
    return rollno;
}
//retrollno() end here

//**************************************************
//~~~~~~~~~~~FUNCTION DECLARATION~~~~~~~~~~~~~~~~~~~
//**************************************************

void write_student();        //write the records in binary file
void display_all();          //read all records from binary file
void display_sp(int);        //accept rollno and read record from binary file
void modify_student(int);    //accept rollno and update record of binary file
void delete_student(int);    //accept rollno and delete selected record from binary file
void class_result();         //display all records in tabular format from binary file
void result();               //display result menu
void intro();                //display welcome screen
void entry_menu();           //display entry menu on screen

//*************************************************
//~~~~~~~~~~~~~THE MAIN FUNCTION OF PROGRAM~~~~~~~~
//*************************************************

int main()
{
    char ch;
    cout.setf(ios::fixed|ios::showpoint);
    cout<<setprecision(2);  // program outputs decimal number to two decimal places
    intro();
    do
    {
        system("cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. RESULT MENU";
        cout << "\n\n\t02. ENTRY/EDIT MENU";
        cout << "\n\n\t03. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-3) ";
        cin >> ch;
        switch(ch)
        {
            case '1': result();
                     break;
            case '2': entry_menu();
                    break;
            case '3': 
                    break;
            default :cout<<"\a";
        }

    }while(ch!='3');
    return 0;
}

//*****************************************************
//~~~~~~~~~~FUNCTION TO WRITE IN FILE~~~~~~~~~~~~~~~~~~
//*****************************************************

void write_student()
{
         student st;
         ofstream outFile;
         outFile.open("student.dat", ios::binary|ios::app);
         st.getdata();
         outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
         outFile.close();
         cout << "\n\nStudent record has been created ";
         cin.ignore();
         cin.get();
}

//***************************************************
//~~~~~~~~FUNCTION TO READ ALL RECORDS FROM FILE~~~~~
//***************************************************

void display_all()
{
    student st;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if(!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
    }
    cout <<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
    {
        st.showdata();
        cout << "\n\n=========================================\n";

    }
    inFile.close();
    cin.ignore();
    cin.get();
}

//*********************************************************
//~~~~~~~FUNCION TO READ SPACIFIC RECORD FROM FILE~~~~~~~~~
//*********************************************************

void display_sp(int n)
{
    student st;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if(!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag=false;
    while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
    {
        if(st.retrollno()==n)
        {
            st.showdata();
            flag=true;
        }

    }
    inFile.close();
    if(flag==false)
              cout << "\n\nrecord not exist";
    cin.ignore();
    cin.get();
}

//***************************************************
//~~~~~~FUNCTION TO MODIFY RECORD OF FILE~~~~~~~~~~~~
//***************************************************

void modify_student(int n)
{
    bool found = false;
    student st;
    fstream File;
    File.open("student.dat", ios::binary|ios::in|ios::out);
    if(!File)
    {
            cout << "File could not be open !! Press any key...";
            cin.ignore();
            cin.get();
            return;
    }

    while(!File.eof() && found==false)
    {
            File.read(reinterpret_cast<char *> (&st), sizeof(student));
            if(st.retrollno()==n)
            {
                        st.showdata();
                        cout <<"\n\nPlease Enter The New Details of Student" << endl;
                        st.getdata();
                        int pos=(-1)*static_cast<int>(sizeof(st));
                        File.seekp(pos,ios::cur);
                        File.write(reinterpret_cast<char *> (&st), sizeof(student));
                        cout << "\n\n\t Record Updated";
                        found=true;
            }
    }
    File.close();
    if(found==false)
                cout<<"\n\n Record Not Found ";
    cin.ignore();
    cin.get();
}

//***************************************************
//~~~~~~FUNCTION TO DELETE RECORD OF FILE~~~~~~~~~~~~
//***************************************************

void delete_student(int n)
{
          student st;
          ifstream inFile;
          inFile.open("student.dat", ios::binary);
          if(!inFile)
          {
                  cout << "File could not be open !! Press any Key...";
                  cin.ignore();
                  cin.get();
                  return;
          }
          ofstream outFile;
          outFile.open("Temp.dat", ios::out);
          inFile.seekg(0, ios::beg);
          while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
          {
                   if(st.retrollno()!=n)
                   {
                           outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
                   }
          }
          outFile.close();
          inFile.close();
          remove("student.dat");
          rename("Temp.dat" , "student.dat");
          cout << "\n\n\tRecord Deleted ..";
          cin.ignore();
          cin.get();
}

//********************************************************
//~~~~~FUNCTION TO DISPLAY ALL STUDENT GRADE REPORT~~~~~~~
//********************************************************

void class_result()
{
    student st;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if(!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n\t\tALL STUDENT RESULT \n\n";
    cout << "=================================================================\n";
    cout << "R.No       Name          P   C   M   E   CS   AS   %age   Grade"<< endl;
    cout << "=================================================================\n";

    while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
    {
        
            st.show_tabular();
            

    }
    
    cin.ignore();
    cin.get();
    inFile.close();

}

//******************************************************
//~~~~~~~FUNCTION TO DISPLAY THE RESULT MENU~~~~~~~~~~~~
//******************************************************

void result()
{
             char ch;
             int rno;
             system("cls");
             cout << "\n\n\n\tRESULT MENU";
             cout << "\n\n\n\t1. Class Result";
             cout << "\n\n\n\t2. Student Report Card";
             cout << "\n\n\n\t3. Back to Main Menu";
             cout << "\n\n\n\tEnter Choice (1/2/3)? ";
             cin >> ch;
             system("cls");
             switch(ch)
             {
                 case '1': class_result();
                          break;
                 case '2' : cout << "\n\n\tEnter Roll Number Of Student : ";
                            cin >>rno;
                            display_sp(rno);
                            break;
                 case '3' : break;
                 default : cout << "\a";

             }

}

//*********************************************************
//~~~~~~~~~~~~~~~~ENTRY / EDIT MENU FUNCTION ~~~~~~~~~~~~~~
//*********************************************************

void entry_menu()
{
           char ch;
           int num;
           system("cls");
           cout << "\n\n\n\tENTRY MENU";
           cout << "\n\n\t1. CREATE STUDENT RECORD";
           cout << "\n\n\t2. DISPLAY ALL STUDENTS RECORDS";
           cout << "\n\n\t3. SEARCH STUDENT RECORD";
           cout << "\n\n\t4. MODIFY STUDENT RECORD";
           cout << "\n\n\t5. DELETE STUDENT RECORD";
           cout << "\n\n\t6. BACK TO MAIN MENU";
           cout << "\n\n\tPlease Enter Your Choice (1-6)";
           cin >> ch;
           system("cls");
           switch(ch)
           {
                 case '1' : write_student(); break;
                 case '2' : display_all(); break;
                 case '3' : cout << "\n\n\tPlease Enter The Roll Number : ";
                            cin >> num;
                            display_sp(num);
                            break;
                 case '4' : cout << "\n\n\tPlease Enter The Roll Number : ";
                            cin >> num;
                            modify_student(num);
                            break; 
                 case '5' : cout << "\n\n\tPlease Enter The Roll Number : ";
                            cin >> num;
                            delete_student(num);
                            break;
                 case '6' : break;
                 default : cout << "\a"; entry_menu();
           }
}

//*******************************************************
//~~~~~~~~~~~~~~INTRODUCTION FUNCTION~~~~~~~~~~~~~~~~~~~~
//*******************************************************

void intro()
{
       cout << "\n\n\n\t\t   PROJECT";
       cout << "\n\t\t     ON";
       cout << "\n\t COMPUTER SCIENCE & APPLICATION";
       cout << "\n\n\n\t   STUDENT REPORT CARD";
       cout << "\n\n\n\tROLL : 0182";
       cout << "\n\tNO : 20025";
       cout << "\n\tREG NO : 048953";
       cout << "\n\tSESSION : 2020-21";
       cin.get();
}



//*******************************************************
//~~~~~~~~~~~~~~~~~~END OF THE PROJECT~~~~~~~~~~~~~~~~~~~
//*******************************************************