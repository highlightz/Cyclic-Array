// This is only a simple test using primitive data type 'int'.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "DataCache.h"

const int CACHE_CAPACITY = 5;

int main( )
{
	DataCache< int, CACHE_CAPACITY > dc;
	while ( 1 )
	{
		cout << "Enter a new data: ";
		int newData;
		cin >> newData;
		dc.writeData( newData );
		cout << "The current number of datas in cache is: " << dc.getLastDatas( ).numDatas << endl;
		cout << "The newest data is: " << dc.getLastData( ) << endl;

		DataInfo< int, CACHE_CAPACITY > di;
		di = dc.getLastDatas( );
		if ( di.numDatas > 1 )
		{
			cout << "Your last datas are: " << endl;
			for ( int i = 0; i < di.numDatas; i++ )
			{
				cout << di.datas[ i ] << endl;
			}
		}
	}

	return 0;
}
