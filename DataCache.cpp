template < class DataType, int CAPACITY >
DataCache< DataType, CAPACITY >::DataCache( )
{
	lastIndex = -1;
	numDatas = 0;
}

template < class DataType, int CAPACITY >
void DataCache< DataType, CAPACITY >::writeData( const DataType& newData )
{
	lastIndex++;
	if ( lastIndex == CAPACITY )
	{
		lastIndex = 0;
	}

	lastDatas[lastIndex] = newData;

	if ( numDatas != CAPACITY )
	{
		numDatas++;
	}
}

template < class DataType, int CAPACITY >
DataType DataCache< DataType, CAPACITY >::getLastData( ) const
{
	return lastDatas[ lastIndex ];
}

// getLastDatas returns up to CAPACITY datas in a DataInfo struct;
// the number of datas is also in the DataInfo struct.
// Datas in the datas array are stored in order, with the latest data first
template< class DataType, int CAPACITY >
DataInfo< DataType, CAPACITY > DataCache< DataType, CAPACITY >::getLastDatas( ) const
{
	DataInfo< DataType, CAPACITY > info;
	info.numDatas = numDatas;

	for ( int i = 0, j = lastIndex; i < numDatas; i++, j-- )
	{
		if ( j == -1 )
		{
			j = CAPACITY - 1;
		}

		info.datas[ i ] = lastDatas[ j ];
	}

	return info;
}
