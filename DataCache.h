#ifndef DATACACHE_H
#define DATACACHE_H

// The templates for an associated DataInfo and DataCache must match in DataType
template < class DataType, int CAPACITY >
struct DataInfo
{
	int numDatas;
	DataType datas[ CAPACITY ];
};

template < class DataType, int CAPACITY >
class DataCache
{
public:
	DataCache( );
	void writeData( const DataType& newData );
	DataType getLastData( ) const;
	// getLastDatas returns up to CAPACITY datas in a DataInfo struct;
	// the number of datas is also in the DataInfo struct.
	// Datas in the datas array are stored in order, with the latest data first.
	DataInfo< DataType, CAPACITY > getLastDatas( ) const;
private:
	int numDatas;  // The number of datas stored in the array
	int lastIndex;  // The index of the last data that was stored
	DataType lastDatas[ CAPACITY ];  // Saves up to CAPACITY datas
};

#include "DataCache.cpp"

#endif // DATACACHE_H
