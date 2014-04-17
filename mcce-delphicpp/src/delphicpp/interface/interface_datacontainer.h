#ifndef IDATACONTAINER_H
#define IDATACONTAINER_H

#include <iostream> 
#include <string.h>      // STL::string 
#include <vector>        // STL::vector
#include <map>           // STL::map
#include <boost/any.hpp> // boost::any

#include "environment.h"
#include "../io/io_datatype.h"
#include "interface_exceptions.h"

using namespace std;
using boost::any_cast;

typedef map<string, boost::any> DataMap;

//-----------------------------------------------------------------------//
class IDataContainer
{
   protected:   
	   DataMap myData;
	               	                  
      virtual void setMap() = 0;      

	public:
	   IDataContainer(){};
	   
	   ~IDataContainer(){myData.clear();};

      bool keyExists(const string &strKey);
         
	   //----------read-only key content in the map
	   template <class T> const T& getKey_constRef(const string& strKey);
	   	   
	   template <class T> const T* getKey_constPtr(const string& strKey);
	   
	   template <class T> const T** getKey_constPtr(const string& strKey,const int& iRows,const int& iColumns);

	   template <class T> const T*** getKey_constPtr(const string& strKey,const int& iRows,const int& iColumns,const int& iPages);

	   template <class T> const T**** getKey_constPtr(const string& strKey,const int& iRows,const int& iColumns,const int& iPages,const int& iSects);

	   //----------read and write key content in the map
      template <class T> T& getKey_Ref(const string& strKey);

	   template <class T> T getKey_Val(const string& strKey);
	   
	   template <class T> T* getKey_Ptr(const string& strKey);

	   template <class T> T*** getKey_Ptr(const string& strKey,const int& iRows,const int& iColumns,const int& iPages);

      virtual void showMap(const string& strMapFile) = 0;

      virtual void reset(const string& strF95File) = 0;
};

#endif // IDATACONTAINER_H
