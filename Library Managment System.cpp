/*************************************************
HEADER FILES USED IN PROJECT
*************************************************/

#include<iostream>
#include<iomanip>
#include<conio.h>
#include<stdio.h>
#include<fstream>
#include<string.h>
#include<windows.h>
#include<iomanip>
void clrscr(){}
using namespace std;

/*************************************************
CLASS USED IN PROJECT
*************************************************/

class book
{
		char bno[10];
		char bname[60];
		char aname[21];
	public:
		void create_book()
			{
				cout<<endl<<".......NEW BOOK ENTRY......."<<endl;
				cout<<endl<<"Enter Book Number:";
				cin>>bno;
				cout<<endl<<"Enter The Name Of The Book:";
				cin.ignore();
				cin.getline(bname,60);
				cout<<endl<<"Enter The Author's Name:";
				cin.getline(aname,21);
				cout<<endl<<".......BOOK RECORD CREATED.......";
			}
		void print_book()
			{
			    cout<<endl<<"Book Details"<<endl;
				cout<<endl<<"Book Number:"<<bno<<endl;
				cout<<endl<<"Name Of The Book:"<<bname<<endl;
				cout<<endl<<"The Author's Name:"<<aname<<endl;
			}
        void modify_book()
            {
                cout<<endl<<"Book Number:"<<bno<<endl;
                cout<<endl<<"Modify Book Name:";
                cin.ignore();
                gets(bname);
                cout<<endl<<"Modify Author's Name:";
                gets(aname);
            }
        char* retbno()
            {
                return bno;
            }
        void report()
            {
                std::cout<<endl<<bno<<std::setw(37)<<bname<<std::setw(33)<<aname<<endl;
            }
};

class student
{
       int token;
       char admno[10];
       char name[21];
       char stbno[10];
    public:
        void create_student()
            {
                clrscr();
                cout<<endl<<".......NEW STUDENT ENTRY........"<<endl;
                cout<<endl<<"Enter The Admission Number:";
                cin>>admno;
                cout<<endl<<"Enter The Name Of The Student:";
                cin.ignore();
                gets(name);
                token=0;
                stbno[0]='/0';
                cout<<endl<<".......STUDENT RECORD CREATED......."<<endl;
            }
        void print_student()
            {
                cout<<endl<<"Admission Number:"<<admno<<endl;
                cout<<endl<<"Student Name:"<<name<<endl;
                cout<<endl<<"Number Of Book Issued:"<<token<<endl;
                if(token==1)
                    cout<<endl<<"Book No:"<<stbno;
            }
        void modify_student()
            {
                cout<<endl<<"Admission No:"<<admno<<endl;
                cout<<endl<<"Modify Student Name:";
                gets(name);
            }
        char* retadmno()
            {
                return admno;
            }
        char* retstbno()
            {
                return stbno;
            }
        int rettoken()
            {
                return token;
            }
        void addtoken()
            {

                token=1;
            }
        void resettoken()
            {
                token=0;
            }
         void getstbno(char t[])
            {
                strcpy(stbno,t);
            }
        void report_student()
            {

                cout<<admno<<std::setw(20)<<name<<std::setw(10)<<token<<endl;
            }
};

/*************************************************
GLOBAL DECLARATION FOR STREAM OBJECT,OBJECTS
*************************************************/

fstream fp, fp1;
book bk;
student st;

/*************************************************
FUNCTION TO WRITE INTO THE FILE
*************************************************/

void write_book()
    {
        char ch;
        fp.open("Book.dat",ios::out|ios::app);
        do
        {
            clrscr();
            bk.create_book();
            fp.write((char*)&bk,sizeof(book));
            cout<<endl<<"Do you Want To Add More Record (Y/N):";
            cin>>ch;
        }while(ch=='y'||ch=='Y');
        fp.close();
    }
void write_student()
    {
        char ch;
        fp.open("Student.dat",ios::out|ios::app);
        do
        {
          st.create_student();
          fp.write((char*)&st,sizeof(student));
          cout<<endl<<"Do you Want To Add More Record (Y/N):";
          cin>>ch;
        }while(ch=='y'||ch=='Y');
        fp.close();
    }

/*************************************************
FUNCTION TO READ SPECIFIC RECORD FROM FILE
*************************************************/

void display_spb(char n[])
    {
        cout<<endl<<".................BOOK DETAILS................."<<endl;
        int flag=0;
        fp.open("Book.dat",ios::in);
        while(fp.read((char*)&bk,sizeof(book)))
            {
                if(strcmpi(bk.retbno(),n)==0)
                    {
                        bk.print_book();
                        flag=1;
                    }
            }
    fp.close();
    if(flag==0)
        cout<<endl<<"BOOK DOES NOT EXIT"<<endl;
    }
void display_sps(char n[])
    {
        cout<<endl<<".................STUDENT DETAILS..............."<<endl;
        int flag=0;
        fp.open("Student.dat",ios::binary|ios::in);
        while(fp.read((char*)&st,sizeof(student)))
            {
                if(strcmpi(st.retadmno(),n)==0)
                    {
                        st.print_student();
                        flag=1;
                    }
            }
        fp.close();
        if(flag==0)
            cout<<endl<<"STUDENT DOES NOT EXIST"<<endl;
    }

/*************************************************
FUNCTION TO MODIFY RECORD OF FILE
*************************************************/

void modify_book()
    {
        char n[6];
        int found=0;
        clrscr();
        cout<<endl<<".......MODIFY BOOK RECORD......."<<endl;
        cout<<endl<<"Enter The Book Number:";
        cin>>n;
        fp.open("Book.dat",ios::binary|ios::in|ios::out);
        while(fp.read((char*)&bk,sizeof(book)) && found==0)
            {
               if(strcmpi(bk.retbno(),n)==0)
                    {
                        bk.print_book();
                        cout<<endl<<"Enter The New Details Of The Book"<<endl;
                        bk.modify_book();
                        int pos=-1*sizeof(bk);
                        fp.seekp(pos,ios::cur);
                        fp.write((char*)&bk,sizeof(book));
                        cout<<endl<<".......RECORD UPDATED......."<<endl;
                        found=1;
                    }
            }
        fp.close();
        if(found==0)
            cout<<endl<<"Record Not Found"<<endl;
    }
void modify_student()
    {
        char n[6];
        int found=0;
        clrscr();
        cout<<endl<<".......MODIFY STUDENT RECORD......."<<endl;
        cout<<endl<<"Enter The Admission Number Of The Student";
        cin>>n;
        fp.open("Student.dat",ios::binary|ios::in|ios::out);
        while(fp.read((char*)&st,sizeof(student))&&found==0)
            {
                if(strcmpi(st.retadmno(),n)==0)
                    {
                        st.print_student();
                        cout<<endl<<"Enter The Details Of The Student"<<endl;
                        st.modify_student();
                        int pos=-1*sizeof(st);
                        fp.seekp(pos,ios::cur);
                        fp.write((char*)&st,sizeof(student));
                        cout<<endl<<".......RECORD UPDATED......."<<endl;
                        found=1;
                    }
            }
        fp.close();
        if(found==0)
            cout<<endl<<"Record Not Found"<<endl;
    }

/*************************************************
FUNCTION TO DELETE RECORD OF FILE
*************************************************/

void delete_student()
    {
        char n[6];
        int flag=0;
        clrscr();
        cout<<endl<<".....DELETE STUDENT RECORD......."<<endl;
        cout<<endl<<"Enter The Admission Number Of the Student:";
        cin>>n;
        fp.open("Student.dat",ios::binary|ios::in|ios::out);
        fstream fp2;
        fp2.open("Temp.dat",ios::out);
        fp.seekg(0,ios::beg);
        while(fp.read((char*)&st,sizeof(student)))
            {
                if(strcmpi(st.retadmno(),n)!=0)
                    fp2.write((char*)&st,sizeof(student));
                else
                    flag=1;
            }
        fp2.close();
        fp.close();
        remove("Student.dat");
        rename("Temp.dat","Student.dat");
        if(flag==1)
            cout<<endl<<"RECORD DELETED"<<endl;
        else
            cout<<endl<<"RECORD NOT FOUND"<<endl;
    }
void delete_book()
    {
        char n[6];
        int flag=0;
        clrscr();
        cout<<endl<<".......DELETE BOOK......."<<endl;
        cout<<endl<<"Enter The Book Number:";
        cin>>n;
        fp.open("Book.dat",ios::binary|ios::in|ios::out);
        fstream fp2;
        fp2.open("Temp.dat",ios::binary|ios::out);
        fp.seekg(0,ios::beg);
        while(fp.read((char*)&bk,sizeof(book)))
            {
                if(strcmpi(bk.retbno(),n)!=0)
                        fp2.write((char*)&bk,sizeof(book));
                else
                    flag=1;
            }
        fp2.close();
        fp.close();
        remove("Book.dat");
        rename("temp.dat","Book.dat");
        cout<<endl<<"RECORD DELETED"<<endl;
    }

/************************************************
FUNCTION TO DISPLAY ALL STUDENT LIST
*************************************************/

void display_alls()
    {
        clrscr();
        fp.open("Student.dat",ios::binary|ios::in);
        if(!fp)
            {
                cout<<"ERROR!!! FILE COULD NOT BE OPENED"<<endl;
                return;
            }
        cout<<endl<<"......STUDENTS LIST......."<<endl;
        cout<<endl<<"Admission Number"<<setw(10)<<"Name"<<setw(20)<<"Book issued"<<endl;
        while(fp.read((char*)&st,sizeof(student)))
            {
                st.report_student();
            }
        fp.close();
    }

/************************************************
FUNCTION TO DISPLAY BOOK LIST
************************************************/

void display_allb()
    {
        clrscr();
       fp.open("Book.dat",ios::binary|ios::in);
       if(!fp)
            {
                cout<<endl<<"ERROR!!! FILE COULD NOT BE OPENED"<<endl;
                return;
            }
        cout<<endl<<".......BOOK LIST......."<<endl;
        cout<<"Book Number"<<setw(29)<<"Book Name"<<setw(29)<<"Authers Name"<<endl;
        while(fp.read((char*)&bk,sizeof(book)))
            {
                bk.report();
            }
        fp.close();
    }
/************************************************
FUNCTION OF ISSUE BOOK
************************************************/

void book_issue()
    {
        char sn[6],bn[6];
        int found=0,flag=0;
        clrscr();
        cout<<endl<<".......BOOK ISSUE......."<<endl;
        cout<<endl<<"Enter The Student's Admission Number:";
        cin>>sn;
        fp.open("Student.dat",ios::binary|ios::in|ios::out);
        fp1.open("Book.dat",ios::binary|ios::in|ios::out);
        while(fp.read((char*)&st,sizeof(student)) && found==0)
            {
                if(strcmpi(st.retadmno(),sn)==0)
                    {
                        found==1;
                        if(st.rettoken()==0)
                            {
                                cout<<endl<<"Enter The Book Number:";
                                cin>>bn;
                                while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
                                    {

                                        if(strcmpi(bk.retbno(),bn)==0)
                                            {
                                                bk.print_book();
                                                flag=1;
                                                st.addtoken();
                                                st.getstbno(bk.retbno());
                                                int pos=-1*sizeof(st);
                                                fp.seekp(pos,ios::cur);
                                                fp.write((char*)&st,sizeof(student));
                                                cout<<endl<<"BOOK HAS SUCCESSFULLY ISSUED"<<endl;
                                                cout<<endl<<"PLEASE NOTE: Book Should Be Returned Back Within 15 Days After That There Will Be Fine OF RS:5 per day"<<endl;
                                            }
                                    }
                                if(flag==0)
                                    cout<<"Book Number Does Not Exist"<<endl;
                            }
                        else
                            cout<<endl<<"You Have Not Returned The Last Book"<<endl;
                    }
            }
        if(found==0)
            cout<<endl<<"Student Record Not Exist"<<endl;
        fp.close();
        fp1.close();
    }
/************************************************
FUNCTION TO DEPOSIT BOOK
************************************************/

void book_deposit()
    {
        char sn[6],bn[6];
        int found=0,flag=0,day,fine;
        clrscr();
        cout<<endl<<".......BOOK DEPOSIT......."<<endl;
        cout<<endl<<"Students Admission Number:";
        cin>>sn;
        fp.open("Student.dat",ios::binary|ios::in|ios::out);
        fp1.open("Book.dat",ios::binary|ios::in|ios::out);
        while(fp.read((char*)&st,sizeof(student))&& found==0)
            {
                if(strcmpi(st.retadmno(),sn)==0)
                    {
                        found=1;
                        if(st.rettoken()==1)
                        {
                            while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
                                {
                                    if(strcmpi(bk.retbno(),st.retstbno())==0)
                                        {
                                            bk.print_book();
                                            flag=1;
                                            cout<<endl<<"Book Deposited In Number Of Days:";
                                            cin>>day;
                                            if(day>15)
                                                {
                                                    fine=(day-15)*5;
                                                    cout<<endl<<"Fine Has To Deposited Rs:"<<fine<<endl;
                                                }
                                            st.resettoken();
                                            int pos=-1*sizeof(st);
                                            fp.seekp(pos,ios::cur);
                                            fp.write((char*)&st,sizeof(student));
                                            cout<<endl<<"BOOK DEPOSITED SUCCESSFULLY";
                                        }
                                }
                            if(flag==0)
                                cout<<endl<<"Book Does Not Exist"<<endl;
                        }
                    else
                        cout<<endl<<"No Book Is Issued...Please Check!!";
                    }

            }
        if(found==0)
            cout<<endl<<"Student Record Not Exist..."<<endl;
        fp.close();
        fp1.close();
    }
/************************************************
INTODUCTION FUNCTION
************************************************/

void intro()
    {
        clrscr();
        cout<<"LIBRARY"<<"   MANAGMENT"<<"    SYSTEM";
        cout<<endl<<"MADE BY : JISS"<<endl;
        cout<<endl<<"SCHOOL : DEPAUL PUBLIC SCHOOL"<<endl;
    }
/************************************************
ADMINISTRATOR MENU FUNCTION
************************************************/

void ad_menu()
	{
				int ch2;
                cout<<"\n\n\n\tADMINISTRATOR MENU";
                cout<<"\n\n\t1.CREATE STUDENT RECORD";
                cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORD";
                cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
                cout<<"\n\n\t4.MODIFY STUDENT RECORD";
                cout<<"\n\n\t5.DELETE STUDENT RECORD";
                cout<<"\n\n\t6.CREATE BOOK ";
                cout<<"\n\n\t7.DISPLAY ALL BOOKS ";
                cout<<"\n\n\t8.DISPLAY SPECIFIC BOOK ";
                cout<<"\n\n\t9.MODIFY BOOK ";
                cout<<"\n\n\t10.DELETE BOOK ";
                cout<<"\n\n\t11.BACK TO MAIN MENU";
                cout<<"\n\n\tPlease Enter Your Choice (1-11) ";
                cin>>ch2;
                switch(ch2)
                    {
                        case 1:	clrscr();
                                write_student();break;
                        case 2: display_alls();break;
                        case 3:
                                char num[6];
                                clrscr();
                                cout<<"\n\n\tPlease Enter The Admission No. ";
                                cin>>num;
                                display_sps(num);
                                break;
                        case 4: modify_student();break;
                        case 5: delete_student();break;
                        case 6: clrscr();
                                write_book();break;
                        case 7: display_allb();break;
                        case 8: {
                                char num[6];
                                clrscr();
                                cout<<"\n\n\tPlease Enter The book No. ";
                                cin>>num;
                                display_spb(num);
                                break;
                                }
                        case 9: modify_book();break;
                        case 10: delete_book();break;
                        case 11: return;
                        default:cout<<"\a";
                    }
                ad_menu();
                exit(0);
    }

void admin_menu()
    {
        clrscr();
        char password[10];
        cout<<endl<<"Enter The Password:";
        cin.ignore();
        gets(password);
        if(strcmp(password,"adam")==1)
            {
            ad_menu();
            }
        else
            cout<<endl<<"Wrong Password Try Again!!!"<<endl;
    }
/************************************************
THE MAIN FUNCTION OF THE PROGRAM
************************************************/

int main()
{
	char ch;
	intro();
	do
	{
        clrscr();
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. BOOK ISSUE";
		cout<<"\n\n\t02. BOOK DEPOSIT";
	  	cout<<"\n\n\t03. ADMINISTRATOR MENU";
	  	cout<<"\n\n\t04. EXIT";
	  	cout<<"\n\n\tPlease Select Your Option (1-4) ";
	  	ch=getche();
	  	switch(ch)
	  	{
			case '1':clrscr();
                     book_issue();
                     break;
		  	case '2':book_deposit();
			    	 break;
		  	case '3':admin_menu();
                     break;
		  	case '4':exit(0);
		  	default :cout<<"\a";
		}
    }while(ch!='4');
}

