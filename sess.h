/*
 * sess.h
 *
 *  Created on: 2018��8��7��
 *      Author: YAO
 */

#ifndef SESS_H_
#define SESS_H_
#include <iostream>
#include "gragh.h"
using namespace std;

template<class datatype,class basetype>
class Session
	{
	private :
	basetype dt=0;
	basetype t=0;
	int method=1;
	int mode=1;
	int vcount=0;
	int order=1;

	datatype **td=nullptr;
	datatype **origin=nullptr;
	void RK3Method();
	void normalMethod();
	void resetvalue();
	void backtovariable();
	void NormalCaculate();
	void DoNothing();
	void ( Session<datatype,basetype>:: *func)();
	void datatovariable(int index);
	void copydata(int from,int to);
	void reset();
	Variable<datatype,basetype> *begin=nullptr;
	Variable<datatype,basetype> *end=nullptr;
	static bool isbusy;
	int state=0;
	void init();

	public:
	Session(basetype st,basetype sdt,int smethod=0);
	~Session();
	const static int PDV_METHOD=1;
	const static int RK3_METHOD=2;
	const static int NORMAL_CACULATE=0;
	const static int PARAMLLEL=0;
	const static int SERIAL=1;
	void caculate();
	void test();
	void start();
	void over();
	basetype run(int times=1);
	};
template<class datatype,class basetype>
bool Session<datatype,basetype>::isbusy=false;
template<class datatype,class basetype>
Session<datatype,basetype>::Session(basetype st,basetype sdt,int smethod)
{
	cout<<"here session:";
    t=st;
	dt=sdt;
	method=smethod;
	cout<<"here session:";
	if(method==0) order=0;
	if(method==1) order=0;
	if(method==2) order=3;
	func=&Session<datatype,basetype>::DoNothing;
}
template<class datatype,class basetype>
void Session<datatype,basetype>::start()
{
	if(!isbusy)
	{
		if(state==0)
		{
			begin=Variable<datatype,basetype>::getbegin();
			isbusy=true;
			state=1;
		}
	}

}
template<class datatype,class basetype>
void Session<datatype,basetype>::reset()
{
     if(origin)
     {
    	 datatype ** tp;
    	 tp=origin;
    	 delete []tp;
     }
     if(td)
     {
    		for(int i=0;i<order;i++)
    			{
    			datatype * tp;
    			tp=(*(td+i));
    			delete[] tp;
    			}
     }
     begin=nullptr;
     end=nullptr;
     state=0;
     func=DoNothing;

}
template<class datatype,class basetype>
void Session<datatype,basetype>::over()
{
	if(state==1)
	{
		if(!begin)
				{
				begin=Variable<datatype,basetype>::getbegin();
				}
			else{
				begin=(*begin).getnext();
			}
			end=Variable<datatype,basetype>::getend();
		    Variable<datatype,basetype> * tp=begin;
		    int tv=0;
		    while(tp)
		    {
		    	tp=(*tp).getnext();
		    	tv=tv+1;
		    }
		    vcount=tv;
		    state=2;
		    init();
		    cout<<" over "<<vcount<<endl;
		    switch(method)
		    {
		    case 0:
		    	func=&Session<datatype,basetype>::NormalCaculate;
		    	break;
		    case 1:
		    	func=&Session<datatype,basetype>::normalMethod;
		    	break;
		    case 2:
		    	func=&Session<datatype,basetype>::RK3Method;
		    	break;
		    default:
		    	func=&Session<datatype,basetype>::DoNothing;

		    }
	}

}
template<class datatype,class basetype>
Session<datatype,basetype>::~Session()
{
	if(td)
	{
		for(int i=0;i<order;i++)
		{
			delete[] td[i];
		}
		delete []td;

	}
	if(origin)
	{
		delete []origin;
	}

}
template<class datatype,class basetype>
void Session<datatype,basetype>::backtovariable()
{
	//cout<<"backtovariable"<<endl;
	Variable<datatype,basetype> *tp=Variable<datatype,basetype>::getbegin();
	for(int i=0;i<vcount;i++)
	{
		Variable<datatype,basetype> *p;
		p=tp;
       if(tp)
    	   {
    	   (*tp).setdata( *(origin+i));
    	   tp=(*p).getnext();
    	   }
	}
}

template<class datatype,class basetype>
void Session<datatype,basetype>::datatovariable(int index)
{
	//cout<<"datatovariable"<<endl;
	if((index<=order) &&(index>0))
	{
		Variable<datatype,basetype> *tp=Variable<datatype,basetype>::getbegin();
		for(int i=0;i<vcount;i++)
		{
			Variable<datatype,basetype> *p;
			p=tp;
	       if(tp)
	    	   {
	    	   (*tp).setdata( &((*(td+index-1))[i]));
	    	   tp=(*p).getnext();
	    	   }
		}
	}

}
template<class datatype,class basetype>
void Session<datatype,basetype>::resetvalue()
{
	//cout<<"resetvalue :"<<endl;
	if(td)
	{
	    for(int i=0;i<vcount;i++)
	    {

	   	 ((*td)[i])=(*(*(origin+i)));
	    }
	}
}

template<class datatype,class basetype>
void Session<datatype,basetype>::DoNothing()
{

}
template<class datatype,class basetype>
void Session<datatype,basetype>::init()
{
	func=&Session<datatype,basetype>::test;
	cout<<"init "<<vcount<<endl;
	origin=new datatype* [vcount];
	Variable<datatype,basetype> *tp=Variable<datatype,basetype>::getbegin();
	for(int i=0;i<vcount;i++)
	{
		Variable<datatype,basetype> *p;
		p=tp;
       if(tp)
    	   {
    	   *(origin+i)=&((*tp).getdata());

    	     tp=(*p).getnext();
    	   }
	}
	if(order>0)
	{
		 td=new datatype *[order];
		    	 for(int i=0;i<order;i++)
		    	 {
		    	*(td+i)=new datatype[vcount];
		    	 }
	}
}
template<class datatype,class basetype>
void Session<datatype,basetype>::copydata(int from ,int to)
{
	if((from>0)&&(from<=order)&&(to>0)&&(to<=order))
	{
		for(int i=0;i<vcount;i++)
		{
			(*(td+to-1))[i]=*(td+from-1)[i];
		}
	}
	if((from==0)&&(to>0)&&(to<=order))
	{
	    for(int i=0;i<vcount;i++)
	    {
	   	 (*(td+to-1))[i]=*(*(origin)+i);
	    }
	}
	if((to==0)&&(from>0)&&(from<=order))
	{
	    for(int i=0;i<vcount;i++)
	    {
	   	 *(*(origin)+i)=(*(td+to-1))[i];
	    }
	}
}
template<class datatype,class basetype>
void Session<datatype,basetype>::normalMethod()
{
	/*
	cout<<"normalmethod"<<endl;
	this->resetvalue();
	cout<<"normalmethod 1"<<endl;
	datatovariable(1);
	caculate();
	cout<<"normalmethod 4"<<endl;

	for(int i=0;i<vcount;i++)
	{

		 *(*(origin+i))=((*td)[i])*dt+( *(*(origin+i)));
	}*/
	cout<<"normalMethod"<<endl;
	caculate();
	Variable<datatype,basetype> *tp=Variable<datatype,basetype>::getbegin();
	for(int i=0;i<vcount;i++)
	{
		Variable<datatype,basetype> *p;
		p=tp;
       if(tp)
    	   {
    	   (**(origin+i))=(*tp).getresult()*dt+ (**(origin+i));
    	     tp=(*p).getnext();
    	   }
	}
}
template<class datatype,class basetype>
void Session<datatype,basetype>::NormalCaculate()
{
	//cout<<"NormalCaculate"<<endl;
	caculate();
	Variable<datatype,basetype> *tp=Variable<datatype,basetype>::getbegin();
	for(int i=0;i<vcount;i++)
	{
		Variable<datatype,basetype> *p;
		p=tp;
       if(tp)
    	   {
    	   (**(origin+i))=(*tp).getresult();
    	     tp=(*p).getnext();
    	   }
	}
}
template<class datatype,class basetype>
void Session<datatype,basetype>::RK3Method()
{

	Variable<datatype,basetype> * tp=begin;
	Variable<datatype,basetype> *p;
	caculate();
	//cout<<"RK3Method"<<endl;
	for(int i=0;i<vcount;i++)
	{

		p=tp;
       if(tp)
    	   {
    	   (*td)[i]=(*tp).getresult()*dt+(**(origin+i));
    	   //(**(origin+i))=(*tp).getresult()*dt+ (**(origin+i));
    	     tp=(*p).getnext();
    	   }
	}
	this->datatovariable(1);
	caculate();
	tp=begin;
	for(int i=0;i<vcount;i++)
	{
		p=tp;
       if(tp)
    	   {
    	   (*(td+1))[i]=(*tp).getresult()*dt*(1.0/4.0)+(**(origin+i))*(3.0/4.0)+((*td)[i])*(1.0/4.0);
    	     tp=(*p).getnext();
    	   }
	}
	this->datatovariable(2);
	caculate();
	tp=begin;
	for(int i=0;i<vcount;i++)
	{
		p=tp;
       if(tp)
    	   {
    	   (**(origin+i))=(*tp).getresult()*dt*(2.0/3.0)+(**(origin+i))*(1.0/3.0)+((*(td+1))[i])*(2.0/3.0);
    	   //(**(origin+i))=(*tp).getresult()*dt+ (**(origin+i));
    	     tp=(*p).getnext();
    	   }
	}
	//this->copydata(3, 0);
	this->backtovariable();

}
template<class datatype,class basetype>
void Session<datatype,basetype>::test()
{   cout<<"test"<<endl;
	/*
	cout<<"test"<<endl;
	for(int i=0;i<vcount;i++)
	{
		(**(origin+i)).show();
	}
	//this->caculate();
    this->resetvalue();
	for(int i=0;i<vcount;i++)
	{
		(*td)[i].show();
	}

	this->datatovariable(1);
	Variable<datatype,basetype> *tp=Variable<datatype,basetype>::getbegin();
	for(int i=0;i<vcount;i++)
	{
		Variable<datatype,basetype> *p;
		p=tp;
       if(tp)
    	   {
    	 (*tp).getdata().show();

    	     tp=(*p).getnext();
    	   }
	}*/

}
template<class datatype,class basetype>
void Session<datatype,basetype>::caculate()
{
	//cout<<"caculate "<<endl;
		Variable<datatype,basetype> *tp=Variable<datatype,basetype>::getbegin();
		for(int i=0;i<vcount;i++)
		{
			Variable<datatype,basetype> *p;
			p=tp;
	       if(tp)
	    	   {
	    	   //cout<<"caculate "<<i<<endl;
	    	   (*tp).calculate();
	    	   tp=(*p).getnext();
	    	   //cout<<"caculate "<<i<<" over "<<endl;
	    	   }
		}
}
template<class datatype,class basetype>
basetype Session<datatype,basetype>::run(int times)
{
	//cout<<"run"<<endl;
	   for(int i=0;i<times;i++)
	   {
		   (this->*func)();
		   t=t-dt;
		   if(t<0) break;
	   }
   return t;
}
#endif /* SESS_H_ */
