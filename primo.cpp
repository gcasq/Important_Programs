#include <iostream>

using namespace std;

bool eh_primo(int x){
	
	int i,m=0;
	for(i=2;i<=x;i++)
	{
		if(x%i==0&&i!=x){m=1;break;}
	}
if(m==1){return false;}
if(m==0){return true;}

}

int main(){
	int x;

	cin>>x;

	if(eh_primo(x)){
		cout << "S" << "\n";
	}else{
		cout << "N" << "\n";
	}
}


