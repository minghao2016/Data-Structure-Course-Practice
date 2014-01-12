#include <iostream>
#include <list>
using namespace std;


void printLots(const list<int>& L, const list<int>& P)
{
	printf("printLots Called.\n");
	for( list<int>::const_iterator itr_P=P.begin(); itr_P != P.end(); itr_P++)
	{
		int k = 1;
		for( list<int>::const_iterator itr_L=L.begin(); itr_L != L.end(); itr_L++)
		{
			if( k == *itr_P )
				cout<<*itr_L<<" ";
			k++;
		}
	}
	cout<<endl;
}

int main()
{
	list<int> P;
	list<int> L;
	
	printf("Please enter list P. Put 0 to stop.\n");
	while(1)
	{
		int k;
		cin>>k;
		P.push_back(k);
		if(k == 0)
			break;
	}
	printf("Done.\n\n");	// End when meets 0.
	
	printf("Please enter list L.Put 0 to stop.\n");
	while(1)
	{
		int k;
		cin>>k;
		L.push_back(k);
		if(k == 0)
			break;
	}
	printf("Done.\n\n");
	
	if(L.size() >= P.size())
		printLots(L,P);
	else
		cout<<"Error! The P.size() is greater than L.size() "<<endl;
	
	return 0;
}

















