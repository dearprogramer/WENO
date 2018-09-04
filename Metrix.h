/*
 * Metrix.h
 *
 *  Created on: 2018Äê7ÔÂ20ÈÕ
 *      Author: YAO
 */
#include "CalulateException.h"
#include <iostream>
#ifndef METRIX_H_
#define METRIX_H_

template <class Type>
class Metrix
{
private :
	int cols,rows;
	Type **data=nullptr;
    static int index;
    bool istemp=false;
    Metrix<Type> * next=NULL;
    Metrix<Type> * privious=NULL;
    static Metrix<Type> * begin;
    static Metrix<Type> * end;
    static int tempcout;
    void clearTemps();
    void clearData();
    void deletethis();
    void initData(int row,int col);
    Metrix<Type> * addTempNode();

    void setTemp(bool istempnode);
	void setPrivious(Metrix<Type> *p);
	void setNext(Metrix<Type> *p);
	Metrix<Type> * nextnode();
public:
	static Metrix<Type> &ones(int row,int col);
	static Metrix<Type> &zeros(int row,int col);
	static Metrix<Type> &unit(int row);
    static Metrix<Type> * addTempNode(int row,int col);
	Metrix<Type> &zeros();
	Metrix<Type> &ones();
	Type * operator[](int row);
	Metrix(int rows,int cols,Type initvalue=0);
	void travelTemps();
	//Metrix(int rows,int cols,bool istemp);
	Metrix();
	bool isTempNode();

	int getrows();
	int getcols();
	void show();
	Metrix<Type> & operator+(Metrix<Type>  &n1);
	Metrix<Type> & operator=(Metrix<Type>  &n1);
	bool operator==(Metrix<Type>  &n1);
	Metrix<Type> & operator*(Metrix<Type>  &n1);
	Metrix<Type> & operator*(Type  n1);
	Metrix<Type> & operator/(Type  n1);
	Metrix<Type> & operator-(Metrix<Type>  &n1);
	Metrix<Type> & operator/(Metrix<Type>  &n1);
	Metrix<Type> & transpose();
	Metrix<Type> & operator-();
	Metrix<Type> & operation(Type (*func)(Type));
	Metrix<Type> & operation(Type (*func)(Type,Type),Type parameter);
	~Metrix();
};
template <class Type>
int Metrix<Type>::index=0;
template <class Type>
int Metrix<Type>::tempcout=0;
template <class Type>
Metrix<Type> * Metrix<Type>::end=nullptr;
template <class Type>
Metrix<Type> * Metrix<Type>::begin=nullptr;

template<class Type>
Metrix<Type> & Metrix<Type>::ones(int row,int col)
{
	Metrix<Type> *tp=addTempNode(row, col);
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			(*tp)[i][j]=1.0;
		}
	}
	return (*tp);
}
template<class Type>
Metrix<Type> & Metrix<Type>::ones()
{

	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
				{
					(*(data+i))[j]=1.0;
				}
	}
		return (*this);
}
template<class Type>
Metrix<Type> & Metrix<Type>::zeros(int row,int col)
{
	Metrix<Type> *tp=addTempNode(row, col);
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
			{
				(*tp)[i][j]=0.0;
			}
	}
	return (*tp);
}
template<class Type>
Metrix<Type> & Metrix<Type>::zeros()
{
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			(*(data+i))[j]=0.0;
		}
	}
	return (*this);
}
template<class Type>
Metrix<Type> & Metrix<Type>::unit(int row)
{
	Metrix<Type> *tp=addTempNode(row, row);
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<row;j++)
		{
			(*tp)[i][j]=0.0;
		}
	}
	for(int i=0;i<row;i++)
	{
				(*tp)[i][i]=1.0;

	}
		return (*tp);
}
/*
template<class Type>
Metrix<Type>::Metrix(int rows,int cols,bool istemp)
{
	this->rows=rows;
	this->cols=cols;
	data=new Type *[rows];
	for(int i=0;i<rows;i++)
	{
		*(data+i)=new Type[cols];
	}
	this->tempcout=this->tempcout+1;
	index=index+1;
	this->istemp=true;
	std::cout<<"new temp :"<<index<<std::endl;
}
*/

template<class Type>
void Metrix<Type>::deletethis()
{
	//std::cout<<"delete this;"<<std::endl;
	Metrix<Type> *pv,*nt;
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
Metrix<Type>::Metrix(int rows,int cols,Type initvalue)
{
	this->rows=rows;
	this->cols=cols;
	data=new Type *[rows];
	for(int i=0;i<rows;i++)
	{
		*(data+i)=new Type[cols];
	}
    for(int i=0;i<rows;i++)
  	   {
  	   for(int j=0;j<cols;j++)
  		   {
  		   (*(data+i))[j]=initvalue;
  		   }
  	   }
	index=index+1;
	std::cout<<"new :"<<index<<std::endl;

}
template<class Type>
Metrix<Type>::Metrix()
{
  this->rows=0;
  this->cols=0;
  index=index+1;
  std::cout<<"new :"<<index<<std::endl;
}
template <class Type>
Metrix<Type>::~Metrix()
{
	for(int i=0;i<this->rows;i++)
	{
		delete[] data[i];
	}
	delete []data;
	index=index-1;
	 std::cout<<"destroy :"<<index<<std::endl;
	if(this->istemp)
	{
		tempcout=tempcout-1;
	}
	else
	{
		if(index==tempcout)
		{
	       this->clearTemps();
		}
	}


};
template<class Type>
void Metrix<Type>::clearTemps()
{
   Metrix<Type> * tp=Metrix<Type>::begin;
   while(tp)
   {
	   Metrix<Type> *a=tp;
	   tp=(*tp).nextnode();
	  // std::cout<<"clear"<<std::endl;
	   delete a;
   }
   this->begin=nullptr;
   this->end=nullptr;
};
template<class Type>
void Metrix<Type>::clearData()
{
	for(int i=0;i<this->rows;i++)
	{
		delete[] data[i];
	}
	delete []data;
};
template<class Type>
bool Metrix<Type>::isTempNode()
{
    return this->istemp;
};
template<class Type>
void Metrix<Type>::setTemp(bool istempnode)
{
	if(istempnode)
	{
		this->istemp=istempnode;
		this->tempcout=this->tempcout+1;
		std::cout<<"new temp :"<<index<<std::endl;
	}

}
template<class Type>
void Metrix<Type>::initData(int row,int col)
{
	this->rows=row;
	this->cols=col;
	data=new Type *[row];
	for(int i=0;i<row;i++)
	{
		*(data+i)=new Type[col];
	}
};
template<class Type>
void Metrix<Type>::setPrivious(Metrix<Type> *p)
{
     if(this->istemp)
     {
    	// std::cout<<"set p ";
    	 this->privious=p;
     }
}
template<class Type>
void Metrix<Type>::setNext(Metrix<Type> *p)
{
     if(this->istemp)
     {
    	// std::cout<<"set p ";
    	 this->next=p;
     }
}
template<class Type>
void Metrix<Type>::show()
{
    for(int i=0;i<rows;i++)
    {
    	for(int j=0;j<cols;j++)
    	{
    		std::cout<<  (*(data+i))[j]<<" \t ";
    	}
    	std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
template<class Type>
void Metrix<Type>::travelTemps()
{
	 Metrix<Type> * tp=Metrix<Type>::begin;
	 int cout=0;
	   while(tp)
	   {
		   Metrix<Type> *a=tp;
		   tp=(*a).nextnode();
		   std::cout<<"travel "<<cout<<(*a).getcols()<<std::endl;
	   }
}
template<class Type>
Metrix<Type> * Metrix<Type>::addTempNode()
{
	//std::cout<<"add"<<std::endl;
   Metrix<Type> * tp=new Metrix<Type>(rows,cols);
   (*tp).setTemp(true);
  // std::cout<<"add 1"<<std::endl;
   if(!begin)
   {
	 std::cout<<"add 2"<<std::endl;
	   this->begin=tp;
	   this->end=tp;
	   //std::cout<<"add 3"<<std::endl;
   }
   else
   {
	   std::cout<<"add 4"<<std::endl;
	   (*end).setNext(tp);
	   (*tp).setPrivious(end);
	  end=tp;
   }
 //  std::cout<<"add 5"<<std::endl;
   return tp;
}
template<class Type>
Metrix<Type> * Metrix<Type>::addTempNode(int row,int col)
{
	//std::cout<<"add"<<std::endl;
   Metrix<Type> * tp=new Metrix<Type>(row,col);
   (*tp).istemp=true;
  // std::cout<<"add 1"<<std::endl;
   if(!begin)
   {
	// std::cout<<"add 2"<<std::endl;
	  begin=tp;
	   end=tp;
	   //std::cout<<"add 3"<<std::endl;
   }
   else
   {
	  // std::cout<<"add 4"<<std::endl;
	   (*end).setNext(tp);
	   (*tp).setPrivious(end);
	  end=tp;
   }
 //  std::cout<<"add 5"<<std::endl;
   return tp;
}
template<class Type>
int Metrix<Type>::getrows()
{
    return this->rows;
}

template<class Type>
int Metrix<Type>::getcols()
{
    return this->cols;
}
template<class Type>
Metrix<Type> * Metrix<Type>::nextnode()
{
	return  this->next;
}
template<class Type>
Type * Metrix<Type>::operator [](int row)
{
  return *(data+row);
}
template<class Type>
Metrix<Type> & Metrix<Type>::operator+(Metrix &n1)
{
	Metrix<Type> *tp;
	 std::cout<<"plus start"<<std::endl;
   if((n1.getcols()==cols)&&(n1.getrows()==rows))
   {
	   if(this->istemp)
	   {
		      for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*(data+i))[j]=(*(data+i))[j]+n1[i][j];
		    		   }
		    	   }
		      if(n1.istemp)  n1.deletethis();
		      return (*this);
	   }
	   else
	   {
		   if(n1.isTempNode())
		   {
			   for(int i=0;i<rows;i++)
				 {
					 for(int j=0;j<cols;j++)
					    {
						 n1[i][j]=(*(data+i))[j]+n1[i][j];
					    }
				}
			   return n1;
		   }
		   else
		   {
		       tp=this->addTempNode();
		       for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*tp)[i][j]=(*(data+i))[j]+n1[i][j];
		    		   }
		    	   }
			   };
		   std::cout<<"plus finished"<<std::endl;
		     return (*tp);
		   }
	   }
}

template<class Type>
Metrix<Type> & Metrix<Type>::operator-(Metrix &n1)
{
	Metrix<Type> *tp;
	 std::cout<<"plus start"<<std::endl;
   if((n1.getcols()==cols)&&(n1.getrows()==rows))
   {
	   if(this->istemp)
	   {
		      for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*(data+i))[j]=(*(data+i))[j]-n1[i][j];
		    		   }
		    	   }
		      if(n1.istemp)  n1.deletethis();
		      return (*this);
	   }
	   else
	   {
		   if(n1.isTempNode())
		   {
			   for(int i=0;i<rows;i++)
				 {
					 for(int j=0;j<cols;j++)
					    {
						 n1[i][j]=(*(data+i))[j]-n1[i][j];
					    }
				}
			   return n1;
		   }
		   else
		   {
		       tp=this->addTempNode();
		       for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*tp)[i][j]=(*(data+i))[j]-n1[i][j];
		    		   }
		    	   }
			   };
		   std::cout<<"plus finished"<<std::endl;
		     return (*tp);
		   }
	   }
}
template<class Type>
Metrix<Type> & Metrix<Type>::operator-()
{
	Metrix<Type> *tp;
	   if(this->istemp)
	   {
		      for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*(data+i))[j]=-(*(data+i))[j];
		    		   }
		    	   }
		      return (*this);
	   }
	   else
	   {

		       tp=this->addTempNode();
		       for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*tp)[i][j]=-(*(data+i))[j];
		    		   }
		    	   }
		   std::cout<<"plus finished"<<std::endl;
		     return (*tp);
		   }
}
template<class Type>
Metrix<Type> & Metrix<Type>::operation(Type (*func)(Type))
{
	Metrix<Type> *tp;
	   if(this->istemp)
	   {
		      for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*(data+i))[j]=func((*(data+i))[j]);
		    		   }
		    	   }
		      return (*this);
	   }
	   else
	   {

		       tp=this->addTempNode();
		       for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*tp)[i][j]=func((*(data+i))[j]);
		    		   }
		    	   }
		   std::cout<<"plus finished"<<std::endl;
		     return (*tp);
		   }
}
template<class Type>
Metrix<Type> & Metrix<Type>::operation(Type (*func)(Type,Type),Type parameter)
{
	Metrix<Type> *tp;
	   if(this->istemp)
	   {
		      for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*(data+i))[j]=func((*(data+i))[j],parameter);
		    		   }
		    	   }
		      return (*this);
	   }
	   else
	   {

		       tp=this->addTempNode();
		       for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*tp)[i][j]=func((*(data+i))[j],parameter);
		    		   }
		    	   }
		   std::cout<<"plus finished"<<std::endl;
		     return (*tp);
		   }
}
template<class Type>
Metrix<Type> & Metrix<Type>::operator*(Type n1)
{
	Metrix<Type> *tp;
	   if(this->istemp)
	   {
		      for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*(data+i))[j]=((*(data+i))[j])*n1;
		    		   }
		    	   }
		      return (*this);
	   }
	   else
	   {

		       tp=this->addTempNode();
		       for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*tp)[i][j]=-((*(data+i))[j])*n1;
		    		   }
		    	   }
		   std::cout<<"plus finished"<<std::endl;
		     return (*tp);
		   }
}
template<class Type>
Metrix<Type> & Metrix<Type>::operator*(Metrix &n1)
{
	Metrix<Type> *tp;
	 std::cout<<"plus start"<<std::endl;
   if((n1.getcols()==cols)&&(n1.getrows()==rows))
   {
	   if(this->istemp)
	   {
		      for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*(data+i))[j]=(*(data+i))[j]*n1[i][j];
		    		   }
		    	   }
		      if(n1.istemp)  n1.deletethis();
		      return (*this);
	   }
	   else
	   {
		   if(n1.isTempNode())
		   {
			   for(int i=0;i<rows;i++)
				 {
					 for(int j=0;j<cols;j++)
					    {
						 n1[i][j]=(*(data+i))[j]*n1[i][j];
					    }
				}
			   return n1;
		   }
		   else
		   {
		       tp=this->addTempNode();
		       for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*tp)[i][j]=(*(data+i))[j]*n1[i][j];
		    		   }
		    	   }
			   };
		   std::cout<<"plus finished"<<std::endl;
		     return (*tp);
		   }
	   }
}
template<class Type>
Metrix<Type> & Metrix<Type>::operator/(Metrix &n1)
{
	Metrix<Type> *tp;
	 std::cout<<"plus start"<<std::endl;
   if((n1.getcols()==cols)&&(n1.getrows()==rows))
   {
	   if(this->istemp)
	   {
		      for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*(data+i))[j]=(*(data+i))[j]/n1[i][j];
		    		   }
		    	   }
		      if(n1.istemp)  n1.deletethis();
		      return (*this);
	   }
	   else
	   {
		   if(n1.isTempNode())
		   {
			   for(int i=0;i<rows;i++)
				 {
					 for(int j=0;j<cols;j++)
					    {
						 n1[i][j]=(*(data+i))[j]/n1[i][j];
					    }
				}
			   return n1;
		   }
		   else
		   {
		       tp=this->addTempNode();
		       for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*tp)[i][j]=(*(data+i))[j]/n1[i][j];
		    		   }
		    	   }
			   };
		  // std::cout<<"plus finished"<<std::endl;
		     return (*tp);
		   }
	   }
}
template<class Type>
Metrix<Type> & Metrix<Type>::operator/(Type n1)
{
	Metrix<Type> *tp;
	   if(this->istemp)
	   {
		      for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*(data+i))[j]=((*(data+i))[j])/n1;
		    		   }
		    	   }
		      return (*this);
	   }
	   else
	   {

		       tp=this->addTempNode();
		       for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*tp)[i][j]=-((*(data+i))[j])/n1;
		    		   }
		    	   }
		   std::cout<<"plus finished"<<std::endl;
		     return (*tp);
		   }
}
template<class Type>
bool Metrix<Type>::operator==(Metrix &n1)
{
	 bool result=true;
   if((n1.getcols()==cols)&&(n1.getrows()==rows))
   {
       for(int i=0;i<rows;i++)
    	   {
    	   for(int j=0;j<cols;j++)
    		   {
    		 if( (*(data+i))[j]!=n1[i][j])
    			 {
    			 return false;
    			 }
    		   }
    	   }
	   }
      else
      {
    	  return false;
      };
   return result;
}
template<class Type>
Metrix<Type> & Metrix<Type>::operator=(Metrix &n1)
{
	 std::cout<<"plus start"<<std::endl;
   if((n1.getcols()==cols)&&(n1.getrows()==rows))
   {
       for(int i=0;i<rows;i++)
    	   {
    	   for(int j=0;j<cols;j++)
    		   {
    		  (*(data+i))[j]=n1[i][j];
    		   }
    	   }
	   }
      else
      {
     this->clearData();
     this->initData(n1.getrows(), n1.getcols());
     for(int i=0;i<rows;i++)
  	   {
  	   for(int j=0;j<cols;j++)
  		   {
  		  (*(data+i))[j]=n1[i][j];
  		   }
  	   }
      };
   if(n1.istemp)  n1.deletethis();
   std::cout<<"equal finished"<<std::endl;

   return (*this);
}
template<class Type>
Metrix<Type> & Metrix<Type>::transpose()
{
	Metrix<Type> *tp=addTempNode(cols, rows);
		      for(int i=0;i<rows;i++)
		    	   {
		    	   for(int j=0;j<cols;j++)
		    		   {
		    		   (*tp)[j][i]=-(*(data+i))[j];
		    		   }
		    	   }
		      return (*tp);
}
#endif /* METRIX_H_ */
