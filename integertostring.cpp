#include<iostream>
#include<string>
using namespace std;

string itoa(int a)
{
    string ss="";   //create empty string
    while(a)
    {
        int x=a%10;
        a/=10;
        char i='0';
        i=i+x;
        ss=i+ss;      //append new character at the front of the string!
    }
    return ss;
}

int main()
{
	int a;string s;
	cin >>a;
	s=itoa(a);
	cout << s<<endl;
}
