/*
 * gragh.h
 *
 *  Created on: 2018年8月10日
 *      Author: YAO
 */

#ifndef GRAGH_H_
#define GRAGH_H_
/*
 * Variables.h
 *
 *  Created on: 2018年8月3日
 *      Author: YAO
 */

#ifndef VARIABLES_H_
#define VARIABLES_H_

#include "node.h"
#include <string>

template <class datatype,class basetype>
class Variable:public Node<datatype,basetype>
{
private:
	datatype * vdata=nullptr;
	datatype tempdata;
	Node<datatype, basetype> *rootnode=nullptr;
	//Node<datatype, basetype> *outnode=nullptr;
	static int vcount;
	static Variable<datatype, basetype> *begin;
	static Variable<datatype, basetype> *end;
	Variable<datatype, basetype> * vprivious=nullptr;
	Variable<datatype, basetype> * vnext=nullptr;
	string name;
	int index=0;
	bool vistemp=false;
	bool isalive=false;
	void addtolist();
	void deletefromlist();
	void clearlist();
	void settemp();
	static int vtempcount;

public:
	Variable(datatype *data);
	~Variable();
	void travelNodes(Node<datatype, basetype> *tp);
	void travelNodes();
	datatype & getdata();
	datatype & getresult();
	void calculate();
	bool isActive();
	static Variable * getbegin();
	static Variable * getend();
	Variable * getnext();
	Variable * getprivious();
	void updatedata();
	bool setdata(datatype * data);
	static int getcount();
	datatype & caculate();
    Variable<datatype,basetype> &operator=(Variable<datatype,basetype> & tv);
    void operator=(Node<datatype, basetype> &tn);
    void operator=(datatype & tb);
};


template <class datatype,class basetype>
int Variable<datatype, basetype>::vcount=0;
template <class datatype,class basetype>
int Variable<datatype, basetype>::vtempcount=0;

template <class datatype,class basetype>
Variable<datatype, basetype>* Variable<datatype, basetype>::end=nullptr;

template <class datatype,class basetype>
Variable<datatype, basetype>* Variable<datatype, basetype>::begin=nullptr;

template <class datatype,class basetype>
datatype & Variable<datatype, basetype>::getdata()
{
	return (*vdata);
}
template <class datatype,class basetype>
datatype & Variable<datatype, basetype>::getresult()
{
	return this->tempdata;
}
template <class datatype,class basetype>
int  Variable<datatype, basetype>::getcount()
{
	return vcount;
}
template <class datatype,class basetype>
bool  Variable<datatype, basetype>::isActive()
{
	return this->isalive;
}

template <class datatype,class basetype>
Variable<datatype, basetype> * Variable<datatype, basetype>::getbegin()
{
	return begin;
}

template <class datatype,class basetype>
Variable<datatype, basetype> * Variable<datatype, basetype>::getend()
{
	return end;
}
template <class datatype,class basetype>
Variable<datatype, basetype> * Variable<datatype, basetype>::getprivious()
{
	return vprivious;
}

template <class datatype,class basetype>
Variable<datatype, basetype> * Variable<datatype, basetype>::getnext()
{
	return vnext;
}
template <class datatype,class basetype>
Variable<datatype, basetype>::Variable(datatype *data):Node<datatype, basetype>(data)
{
	this->vdata=data;
	tempdata=(*data)*0;
	vcount=vcount+1;
	cout<<"new variable"<<vcount<<endl;
}
template <class datatype,class basetype>
Variable<datatype, basetype>::~Variable()
{
	vcount=vcount-1;
	 	if(rootnode)
	 	{
			Node<datatype, basetype> * tp;
			tp=rootnode;
			delete tp;
	 	}
	if(!vistemp)
	{
		 if(isalive) deletefromlist();
		 if(vtempcount>=vcount)
		 {
			 this->clearlist();
		 }
	}

	 if(vistemp)
	 {
		 vtempcount=vtempcount-1;
	 }
	cout<<"destory variable"<<vcount<<endl;
}

template <class datatype,class basetype>
Node<datatype, basetype> & operator+(basetype  tv,Node<datatype, basetype> &tb)
{
	return (tb+tv);
}
template <class datatype,class basetype>
Node<datatype, basetype> & operator*(basetype  tv,Node<datatype, basetype> &tb)
{
	return (tb*tv);
}
;
template <class datatype,class basetype>
Node<datatype, basetype> & operator-(basetype  tv,Node<datatype, basetype> &tb)
{
	return (tb-tv);
}
;
template <class datatype,class basetype>
Node<datatype, basetype> & operator/(basetype  tv,Node<datatype, basetype> &tb)
{
	return (tb/tv);
}
;
template <class datatype,class basetype>
void Variable<datatype, basetype>::operator=(Node<datatype, basetype> &tn)
{
   // this->rootnode=vequal

	if(!rootnode)
	{
	      this->rootnode=new Node<datatype, basetype>(&tn,&tempdata,vequal<datatype, basetype>);
	      (*rootnode).setroot(true);
	      this->isalive=true;
	      addtolist();
	}
	else
	{
			Variable<datatype,basetype> *tv=new Variable(vdata);
			(*tv).settemp();
			(*tv).rootnode=new Node<datatype, basetype>(&tn,&tempdata,vequal<datatype, basetype>);
			(*tv).isalive=true;
	}
}
;
template <class datatype,class basetype>
Variable<datatype, basetype> & Variable<datatype, basetype>::operator=(Variable<datatype, basetype> &tv )
{
    this->setdata(tv.vdata);
    return (*this);
}
template <class datatype,class basetype>
void Variable<datatype, basetype>::operator=(datatype &tn)
{

		if(!rootnode)
		{
		      this->rootnode=new Node<datatype, basetype>(&tn,&tempdata,vequal<datatype, basetype>);
		      (*rootnode).setroot(true);
		      this->isalive=true;
		      addtolist();
		}
		else
		{
				Variable<datatype,basetype> *tv=new Variable(vdata);
				(*tv).settemp();
				(*tv).rootnode=new Node<datatype, basetype>(&tn,&tempdata,vequal<datatype, basetype>);
				(*tv).isatcive=true;
		}
}
template <class datatype,class basetype>
void Variable<datatype, basetype>::calculate()
{
	//cout<<"calculate "<<endl;
	if(rootnode)
	{
		(*rootnode).caculate();
	}
}
template <class datatype,class basetype>
datatype &Variable<datatype,basetype>::caculate()
{
	return (*vdata);
}
template <class datatype,class basetype>
bool Variable<datatype,basetype>::setdata(datatype *data)
{
	if(data)
	{
	vdata=data;
	this->da=data;
	return true;
	}
	else
		return false;

}
template <class datatype,class basetype>
void Variable<datatype, basetype>::updatedata()
{
     if(vdata)
     {
    	 (*vdata)=tempdata;
     }
}

template <class datatype,class basetype>
void Variable<datatype, basetype>::settemp()
{
    vistemp=true;
    this->addtolist();
    vtempcount=vtempcount+1;
}

template <class datatype,class basetype>
void Variable<datatype, basetype>::clearlist()
{
	Variable<datatype, basetype> *tp;
	tp=begin;
	while(tp)
	{
		Variable<datatype, basetype> *p;
		p=tp;
		(*p).deletefromlist();
		tp=(*p).vnext;
	}
}
template <class datatype,class basetype>
void Variable<datatype, basetype>::addtolist()
{
	if(begin)
	{
		(*end).vnext=this;
		this->vprivious=end;
		end=this;
	}
	else
	{
		begin=this;
		end=this;
	}
}
template <class datatype,class basetype>
void Variable<datatype, basetype>::deletefromlist()
{
	Variable *pv,*nt;
	    pv=vprivious;
	    nt=vnext;
	     if(pv)
	        {
	        	if(nt)
	        	{
	        	  	(*pv).vnext=nt;
	        	    (*nt).vprivious=pv;
	        	}
	        	else
	        	{
	        		(*pv).vnext=nullptr;
	        		end=pv;
	        	}
	        }
	        else
	        {
	        	if(nt)
	        	{
	        		begin=nt;
	        		(*nt).vprivious=nullptr;
	        	}
	        	else
	        	{
	        		begin=nullptr;
	        		end=nullptr;
	        	}
	        }
	     if(vistemp) delete this;
}
template <class datatype,class basetype>
void Variable<datatype, basetype>::travelNodes()
{
	this->travelNodes(rootnode);
}
template <class datatype,class basetype>
void Variable<datatype, basetype>::travelNodes(Node<datatype, basetype> *tp)
{
	Node<datatype, basetype> *tl;
	Node<datatype, basetype> *tr;
	tl=(*tp).getleftchild();
	tr=(*tp).getrightchild();
	cout<<"travel:"<<(*tp).getindex()<<endl;
	if(tl)
		{
		this->travelNodes(tl);
		//cout<<"travel:"<<(*tl).getindex()<<endl;
		}
	if(tr)
		{
		this->travelNodes(tr);
		//cout<<"travel:"<<(*tr).getindex()<<endl;
		}
}
#endif /* VARIABLES_H_ */
#endif /* GRAGH_H_ */
