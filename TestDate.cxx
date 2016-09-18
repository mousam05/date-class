
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "Date.h"

using namespace std;

void show(DateFormat& df){ //helper function to display a DateFormat object
	if(df.getdateFormat()) cout<<df.getdateFormat()<<"-";
	else cout<<"(NULL)-";
	if(df.getmonthFormat()) cout<<df.getmonthFormat()<<"-";
	else cout<<"(NULL)-";
	if(df.getyearFormat()) cout<<df.getyearFormat();
	else cout<<"(NULL)";
}

int getInt(){ //helper function to get an integer from input
	char s[50];
	int flag;
	do{
		flag = 1;
		cout<<"(integer)";
		cin>>s;
		cout<<s<<endl; //for echoing input while taking input from file
		if(!atoi(s) && strcmp(s, "0")) //if entered string cannot be parsed as int
			flag = 0;
	}while(!flag);


	return atoi(s);
}

Date getDateFromInput(){ //helper function to get a date from input with built-in exception handling
	int flag=0;
	char str[50];
	cout<<"NOTE: Current date format: "; show(Date::getFormat()); cout<<endl;
	cout<<"Enter a date (as string): ";
	cin>>str;
	cout<<str<<endl;//for echoing input while taking input from file
	Date d1;
	do{
		try{
			flag = 0;
			d1 = Date(str);
		}
		catch(exception& e){
			flag = 1;
			cout<<e.what()<<" Try again: ";
			cin>>str;
			cout<<str<<endl;//for echoing input while taking input from file
		}
	}while(flag);
	return d1;
}
void arithmeticTest(){
	int n;

	//testing unary operators first

	cout<<"Taking input of d1:"<<endl;
	Date d1 = getDateFromInput();
	Date d2 = d1;
	try{
		cout<<"Prefix ++ result: "<< ++d1<<endl;
	}
	catch(exception& e){

		cout<<e.what()<<endl;
	}
	try{
		d1 = d2;
		cout<<"Prefix -- result: "<< --d1<<endl;
	}
	catch(exception& e){
		cout<<e.what()<<endl;
	}
	try{
		d1 = d2;
		d1++;
		cout<<"Postfix ++ result: "<< d1<<endl;
	}
	catch(exception& e){
		cout<<e.what()<<endl;
	}
	try{
		d1 = d2;
		d1--;
		cout<<"Posfix -- result: "<< d1<<endl;
	}
	catch(exception& e){
		cout<<e.what()<<endl;
	}

	d1 = d2;

	//now testing binary operators

	cout<<"Enter no. of days to add: ";
	n = getInt();
	try{
		cout<<"Result of binary addition: "<<(d1+n)<<endl;
	}
	catch(exception& e){
		cout<<e.what()<<endl;
	}
	cout<<"Taking input of d2:"<<endl;
	d2 = getDateFromInput();
	cout<<"Result of binary subtraction: "<<(d1-d2)<<endl;
}

void relationalTest(){

	cout<<"Taking input of d1:"<<endl;
	Date d1 = getDateFromInput();

	cout<<"Taking input of d2:"<<endl;
	Date d2 = getDateFromInput();

	cout<<"d1 == d2: "<<(d1==d2)<<endl;
	cout<<"d1 != d2: "<<(d1!=d2)<<endl;
	cout<<"d1 < d2: "<<(d1<d2)<<endl;
	cout<<"d1 <= d2: "<<(d1<=d2)<<endl;
	cout<<"d1 > d2: "<<(d1>d2)<<endl;
	cout<<"d1 >= d2: "<<(d1>=d2)<<endl;
}

void castTest(){

	Date d1 = getDateFromInput();
	cout<<"WeekNumber cast result: "<<(WeekNumber)d1;
	cout<<"\nMonth cast result: "<<(Month)d1;
	cout<<"\nWeekDay cast result: "<<(WeekDay)d1;

}

void IOTest(){

	Date d1;
	cout<<"Taking input through >> operator: "<<endl;
	cin>>d1;
	//cout<<d1<<endl;//for echoing input while taking input from file
	cout<<"\nShowing output through << operator: "<<d1;

}

void TestDate(){

	DateFormat* df[100];
	int dfcount = 0;
	int ch = 0, ch1;
	char dd[20], mm[20], yy[20];
	char st[50];

	cout<<"1. Create DateFormat object by entering triplet"<<endl;
	cout<<"2. Create DateFormat object by entering format string"<<endl;
	cout<<"3. Create default DateFormat object (dd-mmm-yy)"<<endl;
	cout<<"4. Select current date format"<<endl;
	cout<<"5. Create Date object by Entering triplet"<<endl;
	cout<<"6. Create Date object by Entering parse-able string"<<endl;
	cout<<"7. Create default Date object (today)"<<endl;
	cout<<"8. Test arithmetic operators"<<endl;
	cout<<"9. Test relational operators"<<endl;
	cout<<"10. Test cast operators"<<endl;
	cout<<"11. Test for leap year"<<endl;
	cout<<"12. Test I/O operators"<<endl;
	cout<<"Other. Exit"<<endl;

	do{
		cout<<endl<<endl;
		
		cout<<"Enter main menu choice no.: ";
		ch = getInt();
		switch(ch){
		case 1:
			cout<<"Enter date format (any invalid string for 0):"; cin>>dd;
			cout<<dd<<endl;	//for echoing input while taking input from file
			cout<<"Enter month format (any invalid string for 0):"; cin>>mm;
			cout<<mm<<endl;//for echoing input while taking input from file
			cout<<"Enter year format (any invalid string for 0):"; cin>>yy;
			cout<<yy<<endl;//for echoing input while taking input from file

			df[dfcount] = new DateFormat(dd, mm, yy);
			cout<<"New object created: ";
			show(*df[dfcount]); dfcount++;

			break;

		case 2:

			cout<<"Enter format string:"; cin>>st;
			cout<<st<<endl;//for echoing input while taking input from file
			df[dfcount] = new DateFormat(st);
			cout<<"New object created: ";
			show(*df[dfcount]); dfcount++;
			break;

		case 3:
			df[dfcount] = new DateFormat;
			cout<<"New object created: ";
			show(*df[dfcount]); dfcount++;
			break;

		case 4:
			cout<<"NOTE: Current date format: "; show(Date::getFormat()); cout<<endl;
			for(int i=0; i<dfcount; i++){
				cout<<i<<". "; show(*df[i]);
				cout<<endl;
			}
			ch1 = getInt();
			if(ch1 >= 0 && ch1 < dfcount){
				Date::setFormat(*df[ch1]);
				cout<<"Successfully set current date format as ";
				show(*df[ch1]);
				//cout<<endl<<"Today's date: "<<dt<<endl;
			}else{
				cout<<"Invalid choice"<<endl;
			}
			break;

		case 5:
			unsigned int day, month, year;
			cout<<"Enter day no.: ";
			day = getInt();
			cout<<"Enter month no.: ";
			month = getInt();
			cout<<"Enter year: ";
			year = getInt();
			try{
				Date myDate((Day)day, (Month)month, (Year)year);
				cout<<"Date object creation threw no exceptions"<<endl;
			}
			catch(invalid_argument& e){
				cout<<"Invalid argument caught: "<<e.what()<<endl;
			}
			catch(domain_error& e){
				cout<<"Domain error caught: "<<e.what()<<endl;
			}
			catch(out_of_range& e){
				cout<<"Out of range error caught: "<<e.what()<<endl;
			}
			break;
		case 6:
			char str[50];
			cout<<"NOTE: Current date format: "; show(Date::getFormat()); cout<<endl;
			cout<<"Enter date string:"; cin>>str;
			cout<<str<<endl;//for echoing input while taking input from file
			try{
				Date myDate(str);
				cout<<"Date object creation threw no exceptions"<<endl;
			}
			catch(invalid_argument& e){
				cout<<"Invalid argument caught: "<<e.what()<<endl;
			}
			catch(domain_error& e){
				cout<<"Domain error caught: "<<e.what()<<endl;
			}
			catch(out_of_range& e){
				cout<<"Out of range error caught: "<<e.what()<<endl;
			}
			break;
		case 7:
			try{
				Date myDate;
				cout<<"Date object creation threw no exceptions"<<endl;
			}catch(...){
				cout<<"Creation of default Date object threw exception"; //this is not likely to ever happen before 2051
			}
			break;
		case 8:
			arithmeticTest();
			break;
		case 9:
			relationalTest();
			break;
		case 10:
			castTest();
			break;
		case 11:{
			Date d1 = getDateFromInput();
			cout<<"Result of leap year check: "<<d1.leapYear();
			break;
		}case 12:
			IOTest();
		}
	}while(ch > 0 && ch< 13);

	for(int i=0; i<dfcount; i++){
		delete df[i];
	}


}

int main(){
		TestDate();

}
