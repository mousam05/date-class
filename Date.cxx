
#include<string.h>
#include<exception>
#include<stdlib.h>
#include<ctime>
#include "Date.h"

DateFormat Date::format("d", "m", "yy");

DateFormat::DateFormat(const char* dateFormat, const char* monthFormat, const char* yearFormat){

	if(dateFormat){
		if(strcmp(dateFormat, "d") && strcmp(dateFormat, "dd"))
			cout<<dateFormat<<": Invalid date format. Assigning 0."<<endl;

		else{
			this->dateFormat = new char[strlen(dateFormat) + 1];
			strcpy(this->dateFormat, dateFormat);
		}
	}
	else{
		this->dateFormat = 0;
	}

	if(monthFormat){
		if(strcmp(monthFormat, "m") && strcmp(monthFormat, "mm") && strcmp(monthFormat, "mmm"))
			cout<<monthFormat<<": Invalid month format. Assigning 0."<<endl;

		else{
			this->monthFormat = new char[strlen(monthFormat) + 1];
			strcpy(this->monthFormat, monthFormat);
		}
	}
	else{
		this->monthFormat = 0;
	}

	if(yearFormat != NULL){
		if(strcmp(yearFormat, "yy") && strcmp(yearFormat, "yyyy"))
			cout<<yearFormat<<": Invalid year format. Assigning 0."<<endl;

		else{
			this->yearFormat = new char[strlen(yearFormat) + 1];
			strcpy(this->yearFormat, yearFormat);
		}
	}
	else{
		this->yearFormat = 0;
	}

}

DateFormat::DateFormat(const char* format){
	char *temp = new char[strlen(format) + 1];
	strcpy(temp, format);
	int len = strlen(temp);
	char* temp2 = temp;

	int noOfHyphens =0;
	for(int i=0; temp[i] != '\0'; i++){
		if(temp[i] == '-')
			noOfHyphens++;
	}
	if(noOfHyphens != 2){
		cout<<temp<<": Invalid format string for DateFormat. Assigning 0, 0, 0."<<endl;
		dateFormat= monthFormat = yearFormat = 0;
		delete[] temp;
		return;
	}

	for(int i=0; temp[i]!='\0'; i++){
		if(temp[i] == '-')	temp[i] = '\0';  //temporary replacing hyphens in format string by NULL chars
	}


	if(*temp && strcmp(temp, "d") && strcmp(temp, "dd")){

		cout<<temp<<": Invalid date format. Assigning 0."<<endl;
		dateFormat = 0;
	}
	else if(*temp == 0){
		dateFormat = 0;
	}
	else{
		dateFormat = new char[strlen(temp) + 1];
		strcpy(dateFormat, temp);
	}
	temp += strlen(temp) + 1;


	if(*temp && strcmp(temp, "m") && strcmp(temp, "mm") && strcmp(temp, "mmm") ){
		cout<<temp<<": Invalid month format. Assigning 0."<<endl;
		monthFormat = 0;
	}
	else if(*temp == 0){
		monthFormat = 0;
	}
	else{
		monthFormat = new char[strlen(temp) + 1];
		strcpy(monthFormat, temp);
	}

	temp += strlen(temp) + 1;


	if(*temp && strcmp(temp, "yy") && strcmp(temp, "yyyy")){
		cout<<temp<<": Invalid year format. Assigning 0."<<endl;
		yearFormat = 0;
	}
	else if(*temp == 0){
		yearFormat = 0;
	}
	else{
		yearFormat = new char[strlen(temp) + 1];
		strcpy(yearFormat, temp);
	}

	for(int i=0; i<len; i++){
		if(temp2[i] == '\0')			//restoring hyphens in original format string
			temp2[i] = '-';
	}

	delete[] temp2;

}

DateFormat::DateFormat(){			 //default DateFormat object is dd-mmm-yy
	dateFormat = new char[3];
	strcpy(dateFormat,"dd");

	monthFormat = new char[4];
	strcpy(monthFormat,"mmm");

	yearFormat = new char[3];
	strcpy(yearFormat,"yy");
}

DateFormat::~DateFormat(){
	if(dateFormat != 0)
		delete[] dateFormat;
	if(monthFormat != 0)
		delete[] monthFormat;
	if(yearFormat != 0)
		delete[] yearFormat;

	dateFormat = 0;
	monthFormat = 0;
	yearFormat = 0;

}

bool isLeapYear(Year y){ //a leap year is multiple of 4  except century years, or a multiple of 400
	return(y%400 == 0 || (y%4==0 && y%100 != 0));
}

bool isValidDate(Day d, Month m, Year y) throw(invalid_argument, domain_error, out_of_range){
	if(d<1 || d>31 || m<1 || m >12 || y<1)
			throw invalid_argument("Date/month out of bounds.");
	if(m==2){
		if(isLeapYear(y)){
			if(d > 29) throw domain_error("Date of month out of bounds.");
		}else
			if(d > 28) throw domain_error("Date of month out of bounds.");
	}
	if((m == 4 || m == 6 || m==9 || m==11 )&& d>30)
		throw domain_error("Date of month out of bounds.");

	if(y < 1950 || y> 2049)
		throw out_of_range("Year out of range (1950-2049).");

	return true;

}
Date::Date(Day d, Month m, Year y) throw(invalid_argument, domain_error, out_of_range){


	if(isValidDate(d, m, y)){
		this->d = d;
		this->m = m;
		this->y = y;
	}

}

bool isCorrectFormat(const char* date, DateFormat& df){ //helper function to check
										//whether a given input string matches the current date format


	int i;
	if(strcmp(df.getdateFormat(), "d")==0){
		if(!isdigit(date[0]) || date[0] == '0') return false;

		if (isdigit(date[1]))
				i=2;
		else i=1;

	}
	else if(strcmp(df.getdateFormat(), "dd")==0){
		if(!isdigit(date[0]) || !isdigit(date[1])) return false;
		i=2;
	}
	if(date[i] != '-') return false;

	if(strcmp(df.getmonthFormat(), "m")==0){
		if(!isdigit(date[i+1]) || date[i+1] == '0') return false;

		if (isdigit(date[i+2]))
				i= i+3;
		else i=i+2;
	}
	else if(strcmp(df.getmonthFormat(), "mm")==0){
		if(!isdigit(date[i+1]) || !isdigit(date[i+2])) return false;
		i = i+3;
	}
	if(date[i] != '-') return false;

	if(strcmp(df.getyearFormat(), "yy")==0){
		if(!isdigit(date[i+1]) || !isdigit(date[i+2]) || date[i+3]) return false;
	}
	else if(strcmp(df.getyearFormat(), "yyyy")==0){
		if(!isdigit(date[i+1]) || !isdigit(date[i+2]) || !isdigit(date[i+3]) || !isdigit(date[i+4])) return false;
	}

	return true;
}


Date::Date(const char* date) throw(invalid_argument, domain_error, out_of_range){
														//constructor to parse date from string

	if(!Date::format.getdateFormat() || !Date::format.getmonthFormat()
			|| !strcmp(Date::format.getmonthFormat(), "mmm")
			|| !Date::format.getyearFormat()){
			throw invalid_argument("Date format not suitable for input/creation.");

	}

	if(!isCorrectFormat(date, Date::format)){
		throw invalid_argument("Mismatch between date format and supplied date string.");
	}
	char* temp = new char[strlen(date) + 1];
	char* temp2 = temp;
	strcpy(temp, date);

	for(int i=0; temp[i] != '\0'; i++){
		if(temp[i] == '-')
			temp[i] = '\0';
	}
	Day d = (Day)(atoi(temp));

	while(*temp != '\0') temp ++;
	*temp = '-';
	temp++;
	Month m = (Month) (atoi(temp));

	while(*temp != '\0') temp ++;
	*temp = '-';
	temp++;
	unsigned int y;
	if(strcmp(Date::format.getyearFormat(), "yy")==0){
		y = atoi(temp);
		if(y>=50 && y<=99)
			y += 1900;
		else if(y>=0 && y<=49)
			y += 2000;
	}
	else if(strcmp(Date::format.getyearFormat(), "yyyy")==0){
		y = atoi(temp);
	}


	delete[] temp2;
	if(isValidDate(d, m, y)){
		this->d = d;
		this->m = m;
		this->y = y;
	}

}

Date::Date() throw(domain_error, out_of_range){ //default constructor that assigns today's date
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    Day d = (Day)( now->tm_mday);
    Month m = (Month)(now->tm_mon + 1);
    Year y = (Year)(now->tm_year + 1900);

    if(isValidDate(d, m, y)){
		this->d = d;
		this->m = m;
		this->y = y;
	}
}

Date::Date(const Date& date){ //copy constructor
	d = date.d;
	m = date.m;
	y = date.y;
}

Date::~Date(){

}

Date& Date::operator=(const Date& date){ //copy assignment operator
	d = date.d;
	m = date.m;
	y = date.y;
	return *this;
}

Date& Date::operator++(){ // Next	day
	d =	(Day)((int)d + 1);
	if((d == 29 && m==2 && !isLeapYear(y)) ||( d== 30 && m==2 && isLeapYear(y))){
		m = (Month)((int)m + 1);
		d = D01;

	}
	else if(d == 32 && m==12){
		y++;
		if(y==2050)
			throw out_of_range("Cannot increment beyond 31-12-2049.");
		d = D01;
		m = Jan;
	}
	else if(d == 32 && (m==1 || m == 3 || m==5 || m==7 || m==8 || m == 10 || m==12)){
		m = (Month)((int)m + 1);
		d = D01;
	}
	else if(d == 31 &&(m == 4 || m== 6 || m == 9 || m==11)){
		m = (Month)((int)m + 1);
		d = D01;
	}

	return *this;
}
Date Date::operator++(int){	// Same	day next week

	Date temp = *this;
	for(int i=0; i<7; i++){
		++(*this);
	}

	return temp;
}

Date& Date::operator--(){
	d =	(Day)((int)d - 1);
	if((int)d>0)
		return *this;

	if(m==3){
		m = (Month)((int)m - 1);
		if(isLeapYear(y))
			d=D29;
		else
			d=D28;
	}
	else if(m==1){
		y--;
		if(y==1949)
			throw out_of_range("Cannot decrement beyond 1-1-1950.");
		m = Dec;
		d = D31;
	}
	else if(m==2 || m == 4 || m==6 || m==8 || m==9 || m == 11){
		m = (Month)((int)m - 1);
		d = D31;
	}
	else {
		m = (Month)((int)m - 1);
		d = D30;
	}

	return *this;
}

Date Date::operator--(int){

	Date temp = *this;
	for(int i=0; i<7; i++){
		--(*this);
	}
	return temp;
}

unsigned int Date::operator-(const Date& otherDate){
	Date temp1, temp2;                    //setting temp1 to earlier date, temp2 to later date
	if(*this > otherDate){
		temp1 = otherDate;
		temp2 = *this;
	}else{
		temp1 = *this;
		temp2 = otherDate;
	}

	unsigned int i=0;
	while(temp1 != temp2){				//incrementing temp1 till it becomes equal to temp2
		i++;
		++temp1;
	}

	return i;
}
Date Date::operator+(int noOfDays) throw(domain_error, out_of_range){

	Date newDate = *this;
	if(noOfDays > 0){
		for(int i=0; i<noOfDays; i++)
			++newDate;					//increment date required no. of times
	}
	else if(noOfDays < 0){
		for(int i=0; i>noOfDays; i--)
			--newDate;
	}

	return newDate;

}

Date::operator WeekNumber() const{
	Date thisDate = *this;
	if(thisDate == Date((Day)1, (Month)1, 1950)) //special treatment of 1-1-1950 to prevent underflow
		return (WeekNumber)52;

	WeekDay wd = (WeekDay)*this;

	Date temp = *this;
	temp = temp + (int)(Thr - wd);				//temp stores Thursday of that week
	int i=0;
	Year tempYear = temp.y;
	while(temp.y == tempYear ){
		if(temp == Date((Day)5, (Month)1, 1950)){ //special treatment of dates in 1950 to prevent underflow
			i++;
			break;
		}
		temp--;									//go back week-by-week till year changes
		i++;
	}
	return (WeekNumber)i;
}

Date::operator Month() const{
	return m;
}

Date::operator WeekDay() const{

												// 1/1/1950 was a Sunday, using this as reference point
	Date thisDate = *this, ref(D01, Jan, 1950);
	unsigned int noOfDays = thisDate - ref;
	if(noOfDays%7 == 0)
		return (WeekDay)7;
	else
		return (WeekDay)(noOfDays%7);
}

bool Date::leapYear() const{
	return (isLeapYear(y));
}

bool Date::operator==(const Date& otherDate){
	return (d == otherDate.d && m == otherDate.m && y == otherDate.y);
}
bool Date::operator!=(const Date& otherDate){
	return !(*this == otherDate);
}

bool Date::operator<(const Date& otherDate){
	return(y< otherDate.y
			|| (y == otherDate.y && m < otherDate.m)
			|| (y == otherDate.y && m == otherDate.m && d < otherDate.d));
}

bool Date::operator<=(const Date& otherDate){
	return (*this < otherDate || *this == otherDate);
}

bool Date::operator>(const Date& otherDate){
	return !(*this <= otherDate);
}

bool Date::operator>=(const Date& otherDate){
	return !(*this < otherDate);
}

ostream& operator<<(ostream& os, const Date& date){

	if(Date::format.getdateFormat()){
		if(strcmp( Date::format.getdateFormat(), "d")==0){
			os << (int)(date.d);
		}
		else if(strcmp( Date::format.getdateFormat(), "dd") ==0){


			if(date.d < 10)
				os << 0;
			os << (int)(date.d);
		}
	}

	if(Date::format.getmonthFormat()){
		if(strcmp( Date::format.getmonthFormat(), "m")==0){
			os<< '-' <<(int)(date.m);
		}
		else if(strcmp( Date::format.getmonthFormat(), "mm")==0){
			if(date.m < 10)
				os << 0;
			os <<'-'<< (int)(date.m);
		}
		else if(strcmp( Date::format.getmonthFormat(), "mmm")==0){
			os << '-';
			switch((int)(date.m)){
			case 1:
				os << "Jan"; break;
			case 2:
				os <<"Feb"; break;
			case 3:
				os <<"Mar"; break;
			case 4:
				os <<"Apr"; break;
			case 5:
				os << "May"; break;
			case 6:
				os <<"Jun"; break;
			case 7:
				os << "Jul"; break;
			case 8:
				os << "Aug"; break;
			case 9:
				os << "Sep"; break;
			case 10:
				os << "Oct"; break;
			case 11:
				os << "Nov"; break;
			case 12:
				os << "Dec"; break;
			}
		}
	}
	else{
		os << '-';
		switch((int)(date.m)){

		case 1:
			os << "January"; break;
		case 2:
			os <<"February"; break;
		case 3:
			os <<"March"; break;
		case 4:
			os <<"April"; break;
		case 5:
			os << "May"; break;
		case 6:
			os <<"June"; break;
		case 7:
			os << "July"; break;
		case 8:
			os << "August"; break;
		case 9:
			os << "September"; break;
		case 10:
			os << "October"; break;
		case 11:
			os << "November"; break;
		case 12:
			os << "December"; break;
		}
	}

	if(Date::format.getyearFormat()){
		os << '-';
		if(strcmp(Date::format.getyearFormat(), "yy") == 0){
			if (date.y % 100 < 10){
				os << 0;
			}
			os << date.y % 100;
		}
		else if(strcmp(Date::format.getyearFormat(), "yyyy") == 0){
			os << date.y;
		}
	}

	return os;
}

istream& operator>>(istream& is, Date& date){

	if(!Date::format.getdateFormat() || !Date::format.getmonthFormat()
		|| !strcmp(Date::format.getmonthFormat(), "mmm")
		|| !Date::format.getyearFormat()){
		cout<<"Rejected input: Format is output-only.";
		return is;
	}


	char* temp = new char[50];
	is >> temp;

	if(!isCorrectFormat(temp, Date::format)){
		cout<<"Rejected input: Mismatch b/w format and date string.";
		return is;
	}

	try{
		date = Date(temp);
	}
	catch(exception &e){
		cout<<"Rejected input: "<<e.what()<<endl;
	}

	delete[] temp;
	return is;
}

DateFormat& DateFormat::operator=(const DateFormat& df){ //copy assignment operator required in setFormat()

	if(this == &df)
		return *this;

	if(dateFormat)
		delete[] dateFormat;
	if(monthFormat)
		delete[] monthFormat;
	if(yearFormat)
		delete[] yearFormat;

	dateFormat = monthFormat = yearFormat = 0;

	if(df.dateFormat) {
		dateFormat = new char[strlen(df.dateFormat) + 1];
		strcpy(dateFormat, df.dateFormat);
	}
	if(df.monthFormat){
		monthFormat = new char[strlen(df.monthFormat) + 1];
		strcpy(monthFormat, df.monthFormat);
	}
	if(df.yearFormat){
		yearFormat = new char[strlen(df.yearFormat) + 1];
		strcpy(yearFormat, df.yearFormat);
	}

	return *this;
}
char* DateFormat::getdateFormat(){
	return dateFormat;
}
char* DateFormat::getmonthFormat(){
	return monthFormat;
}
char* DateFormat::getyearFormat(){
	return yearFormat;
}
void Date::setFormat(DateFormat& df){
	format = df;
}

DateFormat& Date::getFormat(){
	return format;
}
