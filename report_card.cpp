#include<iostream>
#include<windows.h>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;
class student
{
    int roll_no;
    string name;
    int DS_marks, DBMS_marks, ES_marks, ECO_marks;
    double percentage;
    char grade;
    void calculate();
public:
    void getall();
    void showall() const;
    void tabular_show() const;
    int rollno() const;
};
void student::calculate()
{
    percentage=(DS_marks+DBMS_marks+ES_marks+ECO_marks)/4.0;
    if(percentage>=70)
    {
        grade='A';
    }
    else if(percentage>=50 && percentage<70)
    {
        grade='B';
    }
    else if(percentage>=20 && percentage<50)
    {
        grade='C';
    }
    else
    {
        grade='F';
    }
}
void student::getall()
{
    cout<<"-->";
    cout<<"Enter roll number:"<<endl;
    cin>>roll_no;
    cout<<"-->";
    cout<<"Enter name:"<<endl;
    cin>>name;
    cout<<"-->";
    cout<<"DS marks:"<<endl;
    cin>>DS_marks;
    cout<<"-->";
    cout<<"DBMS marks:"<<endl;
    cin>>DBMS_marks;
    cout<<"-->";
    cout<<"ES marks:"<<endl;
    cin>>ES_marks;
    cout<<"-->";
    cout<<"ECO marks:"<<endl;
    cin>>ECO_marks;
    calculate();
}
void student::showall() const
{
    cout<<"Roll number:"<<roll_no<<endl;
    cout<<"Name:"<<name<<endl;
    cout<<"Marks in DS:"<<DS_marks<<endl;
    cout<<"Marks in DBMS:"<<DBMS_marks<<endl;
    cout<<"Marks in ES:"<<ES_marks<<endl;
    cout<<"Marks in ECO:"<<ECO_marks<<endl;
    cout<<"Percentage:"<<percentage<<endl;
    cout<<"Grade:"<<grade<<endl;
}
void student::tabular_show() const
{
    cout<<roll_no<<setw(8)<<" "<<name<<setw(10)<<DS_marks<<setw(4)<<DBMS_marks<<setw(4)<<ES_marks<<setw(4)<<ECO_marks<<setw(4)<<percentage<<setw(6)<<grade<<endl;
}
int student::rollno() const
{
    return roll_no;
}
void student_write()
{
    student s;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	s.getall();
	outFile.write(reinterpret_cast<char *> (&s), sizeof(student));
	outFile.close();
    cout<<"\n\nRecord Has Been Created ";
}
void read()
{
    student s;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key";
		cin.get();
		return;
	}
	cout<<"\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&s), sizeof(student)))
	{
		s.showall();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cin.get();
}
void display(int n)
{
    student s;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key";
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&s), sizeof(student)))
	{
		if(s.rollno()==n)
		{
	  		 s.showall();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\nRecord does not exist";
	cin.get();
}
void modify(int n)
{
    bool found=false;
	student s;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key";
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{

		File.read(reinterpret_cast<char *> (&s), sizeof(student));
		if(s.rollno()==n)
		{
			s.showall();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			s.getall();
		    	int pos=(-1)*static_cast<int>(sizeof(s));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&s), sizeof(student));
		    	cout<<"\n\n\t Record Updated";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
	cin.get();
}
void delete_student(int n)
{
    student s;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key";
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&s), sizeof(student)))
	{
		if(s.rollno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&s), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tRecord Deleted";
	cin.get();
}
void class_result()
{
    student s;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key";
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULTS \n\n";
	cout<<"==========================================================\n";
	cout<<"R.No       Name        DS   DBMS   ES   ECO   %age   Grade"<<endl;
	cout<<"==========================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&s), sizeof(student)))
	{
		s.tabular_show();
	}
	cin.get();
	inFile.close();
}
void result()
{
    char ch;
	int rno;
	system("cls");
	cout<<"\n\n\tRESULT MENU";
	cout<<"\n\n\t 1. Class Result";
	cout<<"\n\n\t 2. Student Report Card";
	cout<<"\n\n\t 3. Back to Main Menu";
	cout<<"\n\n\tEnter Choice ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1' :	class_result(); break;
	case '2' :	cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
				display(rno); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}
void introduction()
{
    cout<<"\n\n\t\t STUDENT"<<endl;
    cout<<"\t\t REPORT CARD"<<endl;
    cin.get();
}
void entry_menu()
{
    char ch;
	int num;
	system("cls");
	cout<<"\n\n\t ENTRY MENU";
	cout<<"\n\n\t 1.CREATE STUDENT RECORD";
	cout<<"\n\n\t 2.DISPLAY ALL STUDENTS RECORDS";
	cout<<"\n\n\t 3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t 4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t 5.DELETE STUDENT RECORD";
	cout<<"\n\n\t 6.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice  ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	student_write(); break;
	case '2':	read(); break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			display(num); break;
	case '4':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			modify(num);break;
	case '5':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			delete_student(num);break;
	case '6':	break;
	default:	cout<<"\a"; entry_menu();
	}
}
int main()
{
    char ch;
    cout.setf(ios::fixed|ios::showpoint);
    cout<<setprecision(2);
    introduction();
    do
	{
		system("cls");
		cout<<"\n\n\tMAIN MENU"<<endl;;
		cout<<"\t 1. RESULT MENU"<<endl;
		cout<<"\t 2. ENTRY/EDIT MENU"<<endl;
		cout<<"\t 3. EXIT"<<endl;
		cout<<"\tPlease Select Your Option "<<endl;
		cin>>ch;
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
