/*
 * DataSave.h
 *
 *  Created on: 2018Äê7ÔÂ24ÈÕ
 *      Author: YAO
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "MetrixOp.h"
#include "LineOp.h"
using namespace std;
#ifndef DATASAVE_H_
#define DATASAVE_H_
template<class type>
class DataSave {
private:
	string basefile="data";
	string subname=".csv";
	string fileurl="data.csv";
	ifstream fin;
	ofstream fout;
public:
	DataSave();
	DataSave(string fileaddr);
	void setbasefile(string fileaddr);
	bool writeLine(int index,Line<type> &data);
	bool writeLine(int index,type *p,int size);
	bool writeMetrix(int index,Metrix<type> &m);
	bool writeLine(type time,Line<type> &data);
	Metrix<type> & readMetrix(int i);
	bool writeheader(vector<string> header);
	bool writeheader(vector<type> header);
	bool writeheader(int size);
	bool writeheader(type *header,int size);
	virtual ~DataSave();
};
template <class type>
DataSave<type>::DataSave()
{
}
template <class type>
DataSave<type>::~DataSave()
{
}
template <class type>
DataSave<type>::DataSave(string fileaddr)
{
	basefile=fileaddr;
	fileurl=basefile+subname;
	cout<<"fileurl "<<fileurl<<endl;
}
template <class type>
bool DataSave<type>::writeLine(int index,Line<type>& data)
{
	int size = data.getCols();
	//this->fileurl=this->basefile+this->subname;
	this->fout.open(this->fileurl,ios::out|ios::app);

	if (fout)
	{
		this->fout << index  ;
		for (int i = 0; i < size; i++)
		{
			fout << "," << "\t"<< data[i] ;
		}
		fout << endl;
		fout.close();
		return true;
	}
	else return false;
}
template <class type>
bool DataSave<type>::writeLine(type time,Line<type>& data)
{
	int size = data.getCols();
	//this->fileurl=this->basefile+this->subname;
	this->fout.open(this->fileurl,ios::out|ios::app);

	if (fout)
	{
		this->fout << time  ;
		for (int i = 0; i < size; i++)
		{
			fout << "," << "\t"<< data[i] ;
		}
		fout << endl;
		fout.close();
		return true;
	}
	else return false;
}
template <class type>
bool DataSave<type>::writeLine(int index,type *p,int size)
{

	this->fout.open(this->fileurl, ios::out | ios::app);
	if (fout)
	{
		this->fout << index;
		for (int i = 0; i < size; i++)
		{
			fout << "," << "\t" <<*(p+i) ;
		}
		fout << endl;
		fout.close();
		return true;
	}
	else return false;
}
template <class type>
bool DataSave<type>:: writeheader(vector<string> header)
{
	int size = header.size();
	this->fout.open(this->fileurl);
	if (fout)
	{
		for (int i = 0; i < size-1; i++)
		{
			fout << header[i] << "," << "\t";
		}
		fout << header[size - 1];
		fout << endl;
		fout.close();
		return true;
	}

	else return false;
}

template <class type>
bool DataSave<type>:: writeheader(int size)
{
	this->fout.open(this->fileurl);
	if (fout)
	{
		for (int i = 0; i < size-1; i++)
		{
			fout << i << "," << "\t";
		}
		fout << (size - 1);
		fout << endl;
		fout.close();
		return true;
	}

	else return false;
}
#endif /* DATASAVE_H_ */
