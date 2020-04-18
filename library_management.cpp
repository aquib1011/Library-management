
#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<iomanip>
#include<stdlib.h>

using namespace std;

class book
{
    char book_number[6];
    char book_name[50];
    char book_author[20];

public:

    void create_book();
    void show_book();
    void modify_book();
    char* ret_book_no();
    void report();
};



class student
{
    char student_admno[6];
    char student_name[20];
    char student_booknumber[6];
    int student_token;

public:
    void create_student();
    void show_student();
    void modify_student();
    char* ret_admn_no();
    char* ret_st_bookno();
    int ret_token();
    void addtoken();
    void resettoken();
    void get_st_bookno(char t[]);
    void report();
};


fstream fp,fp1;
book bk;
student st;


void write_book();
void write_student();

void display_spb(char n[]);
void display_sps(char n[]);

void modify_book();
void modify_student();

void delete_student();
void delete_book();

void display_alls();
void display_allb();

void book_issue();
void book_deposit();

void intro();

void admin_menu();



void write_book()
{
    char ch;
    fp.open("book.dat",ios::out|ios::app);
    do
    {
        bk.create_book();
        fp.write((char*)&bk,sizeof(book));
        cout<<"\n\nDo you want to add more record..(y/n?)";
        fflush(stdin);
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}

void write_student()
{
    char ch;
    fp.open("student.dat",ios::out|ios::app);
    do
    {
        st.create_student();
        fp.write((char*)&st,sizeof(student));
        cout<<"\n\ndo you want to add more record..(y/n?)";
        fflush(stdin);
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}

void display_spb(char n[])
{
    cout<<"\nBOOK DETAILS\n";
    int flag=0;
    fp.open("book.dat",ios::in);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmp(bk.ret_book_no(),n)==0)
        {
            bk.show_book();
             flag=1;
        }
    }

    fp.close();
    if(flag==0)
        cout<<"\n\nBook does not exist";
    getch();
}

void display_sps(char n[])
{
    cout<<"\nSTUDENT DETAILS\n";
    int flag=0;
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if((strcmp(st.ret_admn_no(),n)==0))
        {
            st.show_student();
            flag=1;
        }
    }

    fp.close();
    if(flag==0)
            cout<<"\n\nStudent does not exist";
     getch();
}

void modify_book()
{
    char n[6];
    int found=0;
    cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
    cout<<"\n\n\tEnter The book no. of The book";
    fflush(stdin);
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&bk,sizeof(book)) && found==0)
    {
        if(strcmp(bk.ret_book_no(),n)==0)
        {
            bk.show_book();
            cout<<"\nEnter The New Details of book"<<endl;
            bk.modify_book();
            int pos=-1*sizeof(bk);
                fp.seekp(pos,ios::cur);
                fp.write((char*)&bk,sizeof(book));
                cout<<"\n\n\t Record Updated";
                found=1;
        }
    }

        fp.close();
        if(found==0)
            cout<<"\n\n Record Not Found ";
        getch();
}

void modify_student()
{
    char n[6];
    int found=0;
    cout<<"\n\n\tMODIFY STUDENT RECORD... ";
    cout<<"\n\n\tEnter The admission no. of The student";
    fflush(stdin);
    cin>>n;
    fp.open("student.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
        if(strcmp(st.ret_admn_no(),n)==0)
        {
            st.show_student();
            cout<<"\nEnter The New Details of student"<<endl;
            st.modify_student();
            int pos=-1*sizeof(st);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&st,sizeof(student));
            cout<<"\n\n\t Record Updated";
            found=1;
        }
    }

    fp.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";
    getch();
}

void delete_student()
{
    char n[6];
    int flag=0;
        cout<<"\n\n\n\tDELETE STUDENT...";
        cout<<"\n\nEnter The admission no. of the Student You Want To Delete : ";
        fflush(stdin);
        cin>>n;
        fp.open("student.dat",ios::in|ios::out);
        fstream fp2;
        fp2.open("Temp.dat",ios::out);
        fp.seekg(0,ios::beg);
        while(fp.read((char*)&st,sizeof(student)))
    {
        if(strcmp(st.ret_admn_no(),n)!=0)
                 fp2.write((char*)&st,sizeof(student));
        else
               flag=1;
    }
}


void delete_book()
{
    char n[6];
    cout<<"\n\n\n\tDELETE BOOK ...";
    cout<<"\n\nEnter The Book no. of the Book You Want To Delete : ";
    fflush(stdin);
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmp(bk.ret_book_no(),n)!=0)
        {
            fp2.write((char*)&bk,sizeof(book));
        }
    }

    fp2.close();
        fp.close();
        remove("book.dat");
        rename("Temp.dat","book.dat");
        cout<<"\n\n\tRecord Deleted ..";
        getch();
}

void display_alls()
{
         fp.open("student.dat",ios::in);
         if(!fp)
         {
               cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
               getch();
               return;
         }

    cout<<"\n\n\t\tSTUDENT LIST\n\n";
    cout<<"==================================================================\n";
    cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
    cout<<"==================================================================\n";

    while(fp.read((char*)&st,sizeof(student)))
    {
        st.report();
    }

    fp.close();
    getch();
}


void display_allb()
{
    fp.open("book.dat",ios::in);
    if(!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
               getch();
               return;
         }

    cout<<"\n\n\t\tBook LIST\n\n";
    cout<<"=========================================================================\n";
    cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
    cout<<"=========================================================================\n";

    while(fp.read((char*)&bk,sizeof(book)))
    {
        bk.report();
    }
         fp.close();
         getch();
}


void book_issue()
{
    char sn[6],bn[6];
    int found=0,flag=0;
    cout<<"\n\nBOOK ISSUE ...";
    cout<<"\n\n\tEnter The student's admission no.";
    fflush(stdin);
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
        fp1.open("book.dat",ios::in|ios::out);
        while(fp.read((char*)&st,sizeof(student)) && found==0)
           {
        if(strcmp(st.ret_admn_no(),sn)==0)
        {
            found=1;
            if(st.ret_token()==0)
            {
                      cout<<"\n\n\tEnter the book no. ";
                      fflush(stdin);
                cin>>bn;
                while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
                {
                       if(strcmp(bk.ret_book_no(),bn)==0)
                    {
                        bk.show_book();
                        flag=1;
                        st.addtoken();
                        st.get_st_bookno(bk.ret_book_no());
                               int pos=-1*sizeof(st);
                        fp.seekp(pos,ios::cur);
                        fp.write((char*)&st,sizeof(student));
                        cout<<"\n\n\t Book issued successfully\n\nPlease Note: Write current date in backside of book and submit within 15 days fine Rs. 1 for each day after 15 days period";
                    }
                }
                  if(flag==0)
                        cout<<"Book no does not exist";
            }
                else
                  cout<<"You have not returned the last book ";

        }
    }
          if(found==0)
        cout<<"Student record not exist...";
    getch();
      fp.close();
      fp1.close();
}


void book_deposit()
{
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    cout<<"\n\nBOOK DEPOSIT ...";
    cout<<"\n\n\tEnter The students admission no.";
    fflush(stdin);
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
        if(strcmp(st.ret_admn_no(),sn)==0)
        {
            found=1;
            if(st.ret_token()==1)
            {
            while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
            {
               if(strcmp(bk.ret_book_no(),st.ret_st_bookno())==0)
            {
                bk.show_book();
                flag=1;
                cout<<"\n\nBook deposited in no. of days";
                cin>>day;
                if(day>15)
                {
                   fine=(day-15)*1;
                   cout<<"\n\nFine has to deposited Rs. "<<fine;
                }
                    st.resettoken();
                    int pos=-1*sizeof(st);
                    fp.seekp(pos,ios::cur);
                    fp.write((char*)&st,sizeof(student));
                    cout<<"\n\n\t Book deposited successfully";
            }
            }
          if(flag==0)
            cout<<"Book no does not exist";
              }
         else
            cout<<"No book is issued..please check!!";
        }
       }
      if(found==0)
    cout<<"Student record not exist...";
    getch();
  fp.close();
  fp1.close();
  }


void intro()
{
    cout<<"LIBRARY ";
    cout<<"MANAGEMENT ";
    cout<<"SYSTEM";
    cout<<"\n\nMADE BY : AQUIB IQBAL";
    cout<<"\n\nSCHOOL : AMITY INTERNATIONAL SCHOOL NOIDA";
    getch();
}


void admin_menu()
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
            case 1: write_student();
                    break;

            case 2: display_alls();
                    break;

            case 3: char num[6];
                    cout<<"\n\n\tPlease Enter The Admission No. ";
                    fflush(stdin);
                    cin>>num;
                    display_sps(num);
                    break;

            case 4: modify_student();
                    break;

            case 5: delete_student();
                    break;

            case 6: write_book();
                    break;

            case 7: display_allb();
                    break;

            case 8: {
                        char num[6];
                        cout<<"\n\n\tPlease Enter The book No. ";
                        fflush(stdin);
                        cin>>num;
                        display_spb(num);
                        break;
                    }

            case 9: modify_book();
                    break;
            case 10: delete_book();
                     break;

            case 11: return;

            default: cout<<"\a";
       }
       admin_menu();
}





int main()
{
    char ch;
    intro();
    do
    {
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. BOOK ISSUE";
        cout<<"\n\n\t02. BOOK DEPOSIT";
          cout<<"\n\n\t03. ADMINISTRATOR MENU";
          cout<<"\n\n\t04. EXIT";
          cout<<"\n\n\tPlease Select Your Option (1-4) ";
          ch=getche();
          fflush(stdin);
          switch(ch)
          {
            case '1':book_issue();
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





//DEFINITION OF BOOK CLASS FUNCTIONS


void book::create_book()
{
    cout<<"\nNEW BOOK ENTRY...\n";
    cout<<"\nEnter The book no.";
    cin>>book_number;
    cout<<"\n\nEnter The Name of The Book ";
    fflush(stdin);
    gets(book_name);
    cout<<"\n\nEnter The Author's Name ";
    fflush(stdin);
    gets(book_author);
    cout<<"\n\n\nBook Created..";
}

void book::show_book()
{
    cout<<"\nBook no. : "<<book_number;
    cout<<"\nBook Name : ";
    puts(book_name);
    cout<<"Author Name : ";
    puts(book_author);
}

void book::modify_book()
{
    cout<<"\nBook no. : "<<book_number;
    cout<<"\nModify Book Name : ";
    fflush(stdin);
    gets(book_name);
    cout<<"\nModify Author's Name of Book : ";
    fflush(stdin);
    gets(book_author);
}

char* book::ret_book_no()
{
    return book_number;
}

void book::report()
{
    cout<<book_number<<setw(30)<<book_name<<setw(30)<<book_author<<endl;
}


//DEFINITION OF STUDENT CLASS FUNCTIONS


void student::create_student()
{
    cout<<"\nNEW STUDENT ENTRY...\n";
    cout<<"\nEnter The admission no. ";
    cin>>student_admno;
    cout<<"\n\nEnter The Name of The Student ";
    fflush(stdin);
    gets(student_name);
    student_token=0;
    student_booknumber[0]='\0';
    cout<<"\n\nStudent Record Created..";
}

void student::show_student()
{
    cout<<"\nAdmission no. : "<<student_admno;
    cout<<"\nStudent Name : ";
    puts(student_name);
    cout<<"\nNo of Book issued : "<<student_token;
    if(student_token==1)
        cout<<"\nBook No "<<student_booknumber;
}

void student::modify_student()
{
    cout<<"\nAdmission no. : "<<student_admno;
    cout<<"\nModify Student Name : ";
    fflush(stdin);
    gets(student_name);
}

char* student::ret_admn_no()
{
    return student_admno;
}

char* student::ret_st_bookno()
{
    return student_booknumber;
}

int student::ret_token()
{
    return student_token;
}

void student::addtoken()
{
    student_token=1;
}

void student::resettoken()
{
    student_token=0;
}

void student::get_st_bookno(char t[])
{
    strcpy(student_booknumber,t);
}

void student::report()
{
    cout<<"\t"<<student_admno<<setw(20)<<student_name<<setw(10)<<student_token<<endl;
}
