/*
 * Line.h
 *
 *  Created on: 2018Äê7ÔÂ22ÈÕ
 *      Author: YAO
 */
#include "CalulateException.h"
#include<iostream>
#ifndef LINE_H_
#define LINE_H_
template<class Type>
class Line
{
private:
	static Line<Type> *begin;
	static Line<Type> *end;
	Line<Type> *next=nullptr;
	Line<Type> *privious=nullptr;
	int cols;
	Type *data=nullptr;
	bool istemp=false;
	static int index;
	static int tempcout;
    Line<Type> * addTempNode();
    Line<Type> * getNext();
    void setPrivious(Line<Type> *p);
    void setNext(Line<Type> *p);
    void cleardata();
    void clearTemps();
    void initdata(int col);
    void deletethis();

public:
	Line();

	Line(int col,Type initvalue=0);
    Type & operator[](int col);
    static Line<Type> * addTempNode(int col);
    Line<Type> & operator+(Line<Type> &n);
    Line<Type> & operator+();
    Line<Type> & operator+(Type tv);
    Line<Type> & operator-( Line<Type> &n1);
    Line<Type> & operator-();
    Line<Type> & operator-(Type tv);
    Line<Type> & operator*(Line<Type> &n1);
    Line<Type> & operator*(Type tv);
    Line<Type> & operator/(Line<Type> &n1);
    Line<Type> & operator/(Type tv);
    Line<Type> & operation(Type (* function)(Type));
    Line<Type> & operation(Type (* function)(Type,Type),Type);
    Line<Type> & operator=(Line<Type> &n);
    static Line<Type> & Linespace(int cols);
    static Line<Type> & Linespace(int first,int last,bool stop=false);
    static Line<Type> & ones(int cols);
    static Line<Type> & zeros(int cols);
    Line<Type> & ones();
    Line<Type> & zeros();
    Type getsum();
    int getCols();
    void show();
	~Line();
};
template<class Type>
int Line<Type>::index=0;

template<class Type>
int Line<Type>::tempcout=0;

template<class Type>
Line<Type> *Line<Type>::begin=nullptr;

template<class Type>
Line<Type> *Line<Type>::end=nullptr;

template<class Type>
Line<Type>::Line()
{
	cols=0;
	index=index+1;
	//std::cout<<"new "<<index<<std::endl;
}

template<class Type>
Line<Type>::Line(int col,Type initvalue)
{
	index=index+1;
	cols=col;
	data=new Type[cols];
	for(int i=0;i<cols;i++)
	{
		*(data+i)=initvalue;
	}
	//std::cout<<"new "<<index<<std::endl;
}

template<class Type>
Line<Type>::~Line()
{
     cleardata();
     //std::cout<<"destroy "<<index;
     index=index-1;
     if(this->istemp)
     {
    	 this->tempcout=tempcout-1;
    	// std::cout<<" temp  "<<tempcout;
     }
     if(index<=tempcout)
     {
    	 if(!istemp)
    	 {
    		 clearTemps();
    	 }
     }
    // std::cout<<std::endl;
}
template<class Type>
void Line<Type>::cleardata()
{

	delete []data;
}
template<class Type>
void Line<Type>::initdata(int col)
{

	data=new Type[col];
}

template<class Type>
void Line<Type>::setNext(Line<Type> * p)
{
    if(this->istemp)
    {
    	this->next=p;
    }
}
template<class Type>
void Line<Type>::deletethis()
{
	//std::cout<<"delete this;"<<std::endl;
	Line<Type> *pv,*nt;
    if(this->istemp)
    {
        pv=this->privious;
        nt=this->next;
        if(pv)
        {
        	if(nt)
        	{
        	  	(*pv).next=nt;
        	    (*nt).privious=pv;
        	}
        	else
        	{
        		(*pv).next=nullptr;
        		end=pv;
        	}
        }
        else
        {
        	if(nt)
        	{
        		begin=nt;
        		(*nt).privious=nullptr;
        	}
        	else
        	{
        		begin=nullptr;
        		end=nullptr;
        	}
        }
    	delete this;
    }
}
template<class Type>
int  Line<Type>::getCols()
{
    return this->cols;
}
template<class Type>
void Line<Type>::setPrivious(Line<Type> * p)
{
    if(this->istemp)
    {
    	this->privious=p;
    }
}

template<class Type>
void Line<Type>::show()
{
	  std::cout<<"size:"<<cols<<std::endl;
  for(int i=0;i<cols;i++)
  {
	  std::cout<<*(data+i)<<" \t ";
  }
  std::cout<<std::endl;
}
template<class Type>
Line<Type> * Line<Type>::getNext()
{
    return this->next;
}
template<class Type>
Line<Type> * Line<Type>::addTempNode()
{

    Line<Type> * tp=new Line(cols);
    (*tp).istemp=true;
    tempcout=tempcout+1;
    if(!begin)
    {
 	 //std::cout<<"add 2"<<std::endl;
 	   this->begin=tp;
 	   this->end=tp;
 	   //std::cout<<"add 3"<<std::endl;
    }
    else
    {
 	   //std::cout<<"add 4"<<std::endl;
 	   (*end).setNext(tp);
 	   (*tp).setPrivious(end);
 	  end=tp;
    }
   // std::cout<<"new temp "<<index<<std::endl;
    return tp;
}
template<class Type>
Line<Type> * Line<Type>::addTempNode(int col)
{
	Line<Type> * tp;
	if(col>0)
	{
		 tp=new Line(col);
		    (*tp).istemp=true;
		    tempcout=tempcout+1;
		    if(!begin)
		    {
		 	 //std::cout<<"add 2"<<std::endl;
		 	   begin=tp;
		 	   end=tp;
		 	   //std::cout<<"add 3"<<std::endl;
		    }
		    else
		    {
		 	   //std::cout<<"add 4"<<std::endl;
		 	   (*end).setNext(tp);
		 	   (*tp).setPrivious(end);
		 	  end=tp;
		    }
		    //std::cout<<"new static temp "<<index<<std::endl;
	}
	else
	{
		throw CalulateException(2);
	}
    return tp;
}
template<class Type>
void Line<Type>::clearTemps()
{
    Line<Type> * tp=this->begin;
    while(tp)
    {
    	Line<Type> *p=tp;
    	tp=(*tp).next;
    	delete p;
    }
    end=nullptr;
    begin=nullptr;
}
template<class Type>
Type & Line<Type>::operator[](int col)
{
	return *(data+col);
}
template<class Type>
Line<Type> & Line<Type>::operator=(Line<Type> &n)
{
	if(this->cols!=n.cols)
	{
		this->cleardata();
		this->initdata(n.cols);
		this->cols=n.cols;
	}

	for(int i=0;i<cols;i++)
				{
			     *(data+i)=n[i];
				}
	if(n.istemp)
	{
		n.deletethis();
	}
	//this->clearTemps();
	return (*this);
}
template<class Type>
Line<Type> & Line<Type>::operator+(Line<Type> &n)
{
	Line<Type> * tp;
	if(this->cols==n.cols)
	{
	     if(this->istemp)
	     {
	    	for(int i=0;i<cols;i++)
	    	{
	    		*(data+i)=n[i]+(*(data+i));
	    	}
	    	if(n.istemp)
	    		{
	    		n.deletethis();
	    		}
	    	return (*this);
	     }
	     else
	     {
	    	 if(n.istemp)
	    	 {
	    		 for(int i=0;i<cols;i++)
	    		 {
	    		 	 n[i]=n[i]+(*(data+i));
	    		 }
	    		return n;
	    	 }
	    	 else
	    	 {
	    		 tp=addTempNode();
	    		 for(int i=0;i<cols;i++)
	    		    {
	    		    	(*tp)[i]=n[i]+(*(data+i));
	    		    }
	    		 return (*tp);
	    	 }
	     }
	}
	else
	{
		throw CalulateException(1);
	}
}
template<class Type>
Line<Type> & Line<Type>::operator*(Line<Type> &n)
{
	Line<Type> * tp;
	if(this->cols==n.cols)
	{
	     if(this->istemp)
	     {
	    	for(int i=0;i<cols;i++)
	    	{
	    		*(data+i)=n[i]*(*(data+i));
	    	}
	    	if(n.istemp)
	    		{
	    		n.deletethis();
	    		}
	    	return (*this);
	     }
	     else
	     {
	    	 if(n.istemp)
	    	 {
	    		 for(int i=0;i<cols;i++)
	    		 {
	    		 	 n[i]=n[i]*(*(data+i));
	    		 }
	    		return n;
	    	 }
	    	 else
	    	 {
	    		 tp=addTempNode();
	    		 for(int i=0;i<cols;i++)
	    		    {
	    		    	(*tp)[i]=n[i]*(*(data+i));
	    		    }
	    		 return (*tp);
	    	 }
	     }
	}
	else
	{
		throw CalulateException(1);
	}
}
template<class Type>
Line<Type> & operator*(Type tv,Line<Type> &n)
{
  return (n*tv);
}
template<class Type>
Line<Type> & Line<Type>::operator-(Line<Type> &n)
{
	Line<Type> * tp;
	if(this->cols==n.cols)
	{
	     if(this->istemp)
	     {
	    	for(int i=0;i<cols;i++)
	    	{
	    		*(data+i)=(*(data+i))-n[i];
	    	}
	    	if(n.istemp)
	    		{
	    		n.deletethis();
	    		}
	    	return (*this);
	     }
	     else
	     {
	    	 if(n.istemp)
	    	 {
	    		 for(int i=0;i<cols;i++)
	    		 {
	    		 	 n[i]=(*(data+i))-n[i];
	    		 }
	    		return n;
	    	 }
	    	 else
	    	 {
	    		 tp=addTempNode();
	    		 for(int i=0;i<cols;i++)
	    		    {
	    		    	(*tp)[i]=(*(data+i))-n[i];
	    		    }
	    		 return (*tp);
	    	 }
	     }
	}
	else
	{
		throw CalulateException(1);
	}
}
template<class Type>
Line<Type> & Line<Type>::operator/(Line<Type> &n)
{
	Line<Type> * tp;
	if(this->cols==n.cols)
	{
	     if(this->istemp)
	     {
	    	for(int i=0;i<cols;i++)
	    	{
	    		*(data+i)=(*(data+i))/n[i];
	    	}
	    	if(n.istemp)
	    		{
	    		n.deletethis();
	    		}
	    	return (*this);
	     }
	     else
	     {
	    	 if(n.istemp)
	    	 {
	    		 for(int i=0;i<cols;i++)
	    		 {
	    		 	 n[i]=(*(data+i))/n[i];
	    		 }
	    		return n;
	    	 }
	    	 else
	    	 {
	    		 tp=addTempNode();
	    		 for(int i=0;i<cols;i++)
	    		    {
	    		    	(*tp)[i]=(*(data+i))/n[i];
	    		    }
	    		 return (*tp);
	    	 }
	     }
	}
	else
	{
		throw CalulateException(1);
	}
}
template<class Type>
Line<Type> & Line<Type>::operator-()
{
	Line<Type> * tp;
	if(istemp)
	{
		for(int i=0;i<cols;i++)
		{

			*(data+i)=-(*(data+i));
		}
		return (*this);
	}
	else
	{
		tp=addTempNode();
		for(int i=0;i<cols;i++)
			{

				(*tp)[i]=-(*(data+i));
			}
		return (*tp);
	}
}
template<class Type>
Line<Type> & Line<Type>::operator+()
{

		return (*this);
}
template<class Type>
Line<Type> & Line<Type>::operator+(Type d)
{
	Line<Type> * tp;
	if(istemp)
	{
	 for(int i=0;i<cols;i++)
	 {
		 *(data+i)=(*(data+i))+d;
	 }
	 return (* this);
	}
	else
	{
		tp=addTempNode(cols);
		 for(int i=0;i<cols;i++)
			 {
			 (*tp)[i]=(*(data+i))+d;
			 }
		 return (*tp);

	}
}

template<class Type>
Line<Type> & Line<Type>::operator-(Type d)
{
	Line<Type> * tp;
	if(istemp)
	{
	 for(int i=0;i<cols;i++)
	 {
		 *(data+i)=(*(data+i))-d;
	 }
	 return (* this);
	}
	else
	{
		tp=addTempNode(cols);
		 for(int i=0;i<cols;i++)
			 {
			 (*tp)[i]=(*(data+i))-d;
			 }
		 return (*tp);

	}
}
template<class Type>
Line<Type> & Line<Type>::operator*(Type d)
{
	Line<Type> * tp;
	if(istemp)
	{
	 for(int i=0;i<cols;i++)
	 {
		 *(data+i)=(*(data+i))*d;
	 }
	 return (* this);
	}
	else
	{
		tp=addTempNode(cols);
		 for(int i=0;i<cols;i++)
			 {
			 (*tp)[i]=(*(data+i))*d;
			 }
		 return (*tp);

	}
}
template<class Type>
Line<Type> & Line<Type>::operator/(Type d)
{
	Line<Type> * tp;
	if(istemp)
	{
	 for(int i=0;i<cols;i++)
	 {
		 *(data+i)=(*(data+i))/d;
	 }

	 return (* this);
	}
	else
	{
		tp=addTempNode(cols);
		 for(int i=0;i<cols;i++)
			 {
			 (*tp)[i]=(*(data+i))/d;
			 }
		 return (*tp);

	}
}
template<class Type>
Line<Type> & Line<Type>::operation(Type (* function)(Type))
{
	Line<Type> * tp;
	if(istemp)
	{
	 for(int i=0;i<cols;i++)
	 {
		 *(data+i)=function((*(data+i)));
	 }
	 return (* this);
	}
	else
	{
		tp=addTempNode(cols);
		 for(int i=0;i<cols;i++)
			 {
				 (*tp)[i]=(*function)((*(data+i)));
			 }
		 return (*tp);

	}
}
template<class Type>
Line<Type> & Line<Type>::operation(Type (* function)(Type,Type),Type parameter)
{
	Line<Type> * tp;
	if(istemp)
	{
	 for(int i=0;i<cols;i++)
	 {
		 *(data+i)=function((*(data+i)),parameter);
	 }
	 return (* this);
	}
	else
	{
		tp=addTempNode(cols);
		 for(int i=0;i<cols;i++)
			 {
				 (*tp)[i]=function((*(data+i)),parameter);
			 }
		 return (*tp);

	}
}
template<class Type>
Line<Type> & Line<Type>::Linespace(int col)
{
	Line<Type> *tp=addTempNode(col);
	for(int i=0;i<col;i++)
	{
		(*tp)[i]=i;
	}
	return (*tp);
}
template<class Type>
Line<Type> & Line<Type>::ones(int col)
{
	Line<Type> *tp=addTempNode(col);
	for(int i=0;i<col;i++)
	{
		(*tp)[i]=1.0;
	}
	return (*tp);
}
template<class Type>
Line<Type> & Line<Type>::ones()
{
	for(int i=0;i<cols;i++)
	{
		(*(data+i))=1.0;
	}
	return (*this);
}
template<class Type>
Line<Type> & Line<Type>::zeros(int col)
{
	Line<Type> *tp=addTempNode(col);
	for(int i=0;i<col;i++)
	{
		(*tp)[i]=0;
	}
	return (*tp);
}
template<class Type>
Line<Type> & Line<Type>::zeros()
{
	for(int i=0;i<cols;i++)
	{
		(*(data+i))=0;
	}
	return (*this);
}
template<class Type>
Line<Type> & Line<Type>::Linespace(int first,int last,bool stop)
{
	int size;
	Line<Type> *tp;
	if(stop)
	{
		size=last-first;
	}
	else
	{
		size=last-first+1;
	}
	size=last-first;
	if(size>0)
	{
		tp=addTempNode(size);

		for(int i=0;i<size;i++)
		{
			(*tp)[i]=i+first;
		}
	}
	else
	{
		throw CalulateException(2);
	}

	return (*tp);
}
template<class Type>
Type  Line<Type>::getsum()
{
	Type result=0;
	for(int i=0;i<cols;i++)
	{
		result=result+(*(data+i));
	}
	return result;
}
#endif /* LINE_H_ */
