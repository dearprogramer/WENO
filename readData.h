/*
 * readData.h
 *
 *  Created on: 2018Äê7ÔÂ31ÈÕ
 *      Author: YAO
 */

#ifndef READDATA_H_
#define READDATA_H_
#include <iostream>
#include <string>
#include <fstream>
#include<vector>
#include <sstream>
#include <regex>
#include "LineOp.h"
#include "MetrixOp.h"
#include "CalulateException.h"
using namespace std;
template <class type>
class ReadData
	{
	private:
	string fileurl;
	ifstream fin;
	int rows=0;
	int cols=0;
	int mode=0;
	int maxsize=32*1024*1024;
	int count=0;
	int curentpage=0;
	int pagesize=40;
	stringstream ss;
	vector<vector<string>> sdata;
public:
	ReadData(string filename,int tmode=0);
	~ReadData();
	bool readall();
	bool readStringline(int  col,vector<string>  & data);
	bool readdataline(int col,vector<type> &data);
	bool readdataline(int begin,int end,vector<vector<type>> &data);
	void showdata();
	int readnextpage();
     void firstpage() ;
	void setpagesize(int size);
	bool reload(string filename);
	Line<type> & readdataLine(int col);
	Metrix<type> &readdataMetrix();
	};
template <class type>
ReadData<type>::ReadData(string filename,int tmode)
{
	this->fileurl=filename;
	mode=tmode;
	fin.open(fileurl, ios::in);
	if(mode==0) this->readall();
	if(mode==1)
	{
		this->readnextpage();
	}
}
template <class type>
ReadData<type>::~ReadData()
{
	fin.close();
}
template <class type>
void ReadData<type>::showdata()
{
	cout<<"rows:"<<rows<<" cols"<<cols<<endl;
	int rsize=sdata.size();
	for(int i=0;i<rsize;i++)
	{
		int csize=sdata[i].size();
		for(int j=0;j<csize;j++)
		{
			cout<<sdata[i][j]<<" \t ";
		}
		cout<<endl;
	}
}
template <class type>
bool ReadData<type>::readdataline(int col,vector<type> &data)
{

   if((col<cols)&&(col>=0))
   {
	   data.clear();
	   int size=sdata[col].size();
	   type temp;
	   for(int i=0;i<size;i++)
	   {
		   temp=type(sdata[col][i]);
		   data.push_back(temp);
	   }
	 return true;
   }
   else
   {
	   return false;
   }
}
template <class type>
bool ReadData<type>::reload(string filename)
{
	this->fileurl=filename;
	this->fin.close();
	fin.open(fileurl, ios::in);
	if(mode==0) return this->readall();
	if(mode==1)
	{
		return (this->readnextpage()>=0);
}
}

template <class type>
int ReadData<type>::readnextpage()
{
	if(mode==1)
	{
		 string s;
		 string temp;
	     regex re("\\S.*?,");
		 smatch result;
		 sdata.clear();
         if(fin)
		{
		 count=0;
		 int index=0;
		 int tcols=0;
		 while(!fin.eof())
		 {
			 getline(fin, s);
			 vector<string> ts;
			 tcols=0;
			 string::const_iterator start=s.begin();
			 string::const_iterator end=s.end();
			 while(regex_search(start,end, result, re))
			  {

					temp=result[0];
					temp.pop_back();
					//cout<<temp<<endl;
					tcols=tcols+1;
					ts.push_back(temp);
					start=result[0].second;
					count=count+1;
			   }
				if(count>this->maxsize)
				{
				break;
				}
			   sdata.push_back(ts);
			   index=index+1;
			   if(tcols>cols) cols=tcols;
			   if(index>=pagesize)
				   {

				   curentpage=curentpage+1;
				   break;
				   }
		   }
		          rows=index;
				   return curentpage;
			   }
			   else
			   {
				   return -1;
			   }
	}
};
template <class type>
void ReadData<type>::firstpage()
{
    fin.clear();
    fin.seekg(0,ios::beg);
    this->readnextpage();


}
template <class type>
void  ReadData<type>::setpagesize(int size)
{
	if(size>0)
	{
		this->pagesize=size;
	}
}
template <class type>
bool ReadData<type>::readall()
{
	   string s;
	   string temp;
	   regex re("\\S.*?,");
	   smatch result;
	   sdata.clear();
	   if(fin)
	   {
		   count=0;
		   int index=0;
		   int tcols=0;
		   while(!fin.eof())
		   {
			 getline(fin, s);
			 vector<string> ts;
			 string::const_iterator start=s.begin();
			 string::const_iterator end=s.end();
			   while(regex_search(start,end, result, re))
			   {
			        temp=result[0];
			        temp.pop_back();
			        //cout<<temp<<endl;
			        tcols=tcols+1;
			        ts.push_back(temp);
			        start=result[0].second;
			        count=count+1;
			   }
		        if(count>this->maxsize)
		        {
		        break;
		        }
			   sdata.push_back(ts);
			   index=index+1;
			   if(tcols>cols) cols=tcols;
		   }
		   return true;
	   }
	   else
	   {
		   return false;
	   }
}
template <class type>
bool ReadData<type>::readStringline(int  col,vector<string> &data)
{
   string s;
   string temp;
   regex re("\\S.*?,");
   smatch result;
   data.clear();
   fin.open(fileurl, ios::in);
   if(fin)
   {
	   int index=0;
	   while(!fin.eof())
	   {
		 getline(fin, s);
		 if (index==col) break;
	   }
	  // cout<<s;
	   string::const_iterator start=s.begin();
	   string::const_iterator end=s.end();
	   while(regex_search(start,end, result, re))
	   {
	        temp=result[0];
	        temp.pop_back();
	        //cout<<temp<<endl;
	        start=result[0].second;
	   }
	   fin.close();
	   return true;
   }
   else
   {
	   fin.close();
	   return false;
   }
}
template <class type>
Line<type> & ReadData<type>::readdataLine(int col)
{
	if((col>cols)&&(col<0))
		{
		throw CalulateException(2);
		};
	cout<<"1"<<endl;
	int size=sdata[col].size();
	cout<<"2"<<endl;
	Line<type> *tl;
	cout<<"3"<<endl;
	type tep;
	cout<<"4"<<endl;
	type temp;
	tl=Line<type>::addTempNode(size);
	for(int i=0;i<size;i++)
	{
		ss.clear();
		ss<<sdata[col][i];
	     ss>>temp;
		(*tl)[i]=temp;
	}
	return (*tl);
}
template <class type>
Metrix<type> & ReadData<type>::readdataMetrix()
{
	Metrix <type>* tp;

	int row=sdata.size();
	int col=sdata[0].size();
	tp=Metrix<type>::addTempNode(row, col);
	type temp;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			ss.clear();
			ss<<sdata[i][j];
		     ss>>temp;
			(*tp)[i][j]=temp;
		}
	}
	return (*tp);

}
#endif /* READDATA_H_ */
