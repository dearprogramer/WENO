/*
 * Variables.h
 *
 *  Created on: 2018Äê8ÔÂ3ÈÕ
 *      Author: YAO
 */

#ifndef VARIABLES_H_
#define VARIABLES_H_

/*
#include "node.h"
#include <string>
template <class datatype,class basetype>
class Variable
{
private:
	datatype * data=nullptr;
	datatype tempdata;
	Node<datatype, basetype> *rootnode=nullptr;
	Node<datatype, basetype> *outnode=nullptr;
	static int count;
	static Variable *begin;
	static Variable *end;
	Variable * privious=nullptr;
	Variable * next=nullptr;
	string name;
	int index=0;
	bool isalive=false;
public:
	Variable(datatype *data);
	~Variable();
	//friend class NodeOp<datatype,basetype>;
	//friend NodeOp<datatype,basetype> & operator()(NodeOp<datatype,basetype> &tb,Variable<datatype,basetype> &tv);
	void travelNodes(Node<datatype, basetype> *tp);
	void travelNodes();
	datatype & getdata();
	datatype & getresult();
	Node<datatype,basetype> *getoutnode();
	void calculate();
	bool isActive();
	bool setdata(datatype *vdata);
	static Variable * getbegin();
	static Variable * getend();
	Variable * getnext();
	Variable * getprivious();
	void updatedata();
	static int getcount();
	Node<datatype, basetype> & operator-(Variable & tb);
    Node<datatype, basetype> & operator+(Variable & tb);
    Node<datatype, basetype> & operator*(Variable & tb);
    Node<datatype, basetype> & operator/(Variable & tb);

	Node<datatype, basetype> & operator-(datatype & tb);
    Node<datatype, basetype> & operator+(datatype & tb);
    Node<datatype, basetype> & operator*(datatype & tb);
    Node<datatype, basetype> & operator/(datatype & tb);

	Node<datatype, basetype> & operator-(basetype tv);
    Node<datatype, basetype> & operator+(basetype tv);
    Node<datatype, basetype> & operator*(basetype tv);
    Node<datatype, basetype> & operator/(basetype tv);


	Node<datatype, basetype> & operator-(Node<datatype, basetype> &tn);
    Node<datatype, basetype> & operator+(Node<datatype, basetype> &tn);
    Node<datatype, basetype> & operator*(Node<datatype, basetype> &tn);
    Node<datatype, basetype> & operator/(Node<datatype, basetype> &tn);

    Node<datatype, basetype> & operator=(Node<datatype, basetype> &tn);
    Node<datatype, basetype> & operator=(Variable & tb);
    Node<datatype, basetype> & operator=(datatype & tb);
};


template <class datatype,class basetype>
int Variable<datatype, basetype>::count=0;

template <class datatype,class basetype>
Variable<datatype, basetype>* Variable<datatype, basetype>::end=nullptr;

template <class datatype,class basetype>
Variable<datatype, basetype>* Variable<datatype, basetype>::begin=nullptr;

template <class datatype,class basetype>
datatype & Variable<datatype, basetype>::getdata()
{
	return (*data);
}
template <class datatype,class basetype>
datatype & Variable<datatype, basetype>::getresult()
{
	return this->tempdata;
}
template <class datatype,class basetype>
Node<datatype, basetype> * Variable<datatype, basetype>::getoutnode()
{
	return this->outnode;
}
template <class datatype,class basetype>
int  Variable<datatype, basetype>::getcount()
{
	return count;
}
template <class datatype,class basetype>
bool  Variable<datatype, basetype>::isActive()
{
	return this->isalive;
}
template <class datatype,class basetype>
bool  Variable<datatype, basetype>::setdata(datatype *vdata)
{
	if(vdata)
	{
		cout<<"setdata"<<endl;
		data=vdata;
		(*outnode).setdata(data);
		return true;
	}
	else return false;
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
	return privious;
}

template <class datatype,class basetype>
Variable<datatype, basetype> * Variable<datatype, basetype>::getnext()
{
	return next;
}
template <class datatype,class basetype>
Variable<datatype, basetype>::Variable(datatype *data)
{
	this->data=data;
	if(begin)
	{
		(*end).next=this;
		this->privious=end;
		end=this;
	}
	else
	{
		begin=this;
		end=this;
	}
	tempdata=(*data)*0;

	this->count=count+1;
	this->outnode=new Node<datatype, basetype>(data);
	cout<<"new variable"<<count<<endl;
}
template <class datatype,class basetype>
Variable<datatype, basetype>::~Variable()
{
	this->data=data;
	this->count=count-1;
	if(count==0)
	{
		Node<datatype,basetype> *tp=Node<datatype,basetype>::getbegin();

		    while(tp)
		    {
		    	Node<datatype,basetype> *p=tp;
		    	tp=(*tp).getnext();
		    	delete p;
		    }

	}
	Variable *pv,*nt;
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
	cout<<"destory variable"<<count<<endl;
}
template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator-(Variable & tb)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(outnode,tb.outnode,vminus<datatype, basetype>);
	return (*tp);
}
template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator+(Variable & tb)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(outnode,tb.outnode,vadd<datatype, basetype>);
	return (*tp);
}

template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator*(Variable & tb)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(outnode,tb.outnode,vmultiply<datatype, basetype>);
	return (*tp);
}
template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator/(Variable & tb)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(outnode,tb.outnode,vdivide<datatype, basetype>);
	return (*tp);
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
NodeOp<datatype, basetype> & operator()(NodeOp<datatype, basetype> &tb,Variable<datatype, basetype> &tv)
{

	NodeOp<datatype,basetype> * tp=new NodeOp<datatype,basetype>()
	return tb(tv.getoutnode());
}
;
template <class datatype,class basetype>
Node<datatype, basetype> & operator/(basetype  tv,Node<datatype, basetype> &tb)
{
	return (tb/tv);
}
;


template <class datatype,class basetype>
Node<datatype, basetype> & operator+(basetype  tv,Variable<datatype, basetype> &tb)
{
	return (tb+tv);
}
template <class datatype,class basetype>
Node<datatype, basetype> & operator*(basetype  tv,Variable<datatype, basetype> &tb)
{
	return (tb*tv);
}
;
template <class datatype,class basetype>
Node<datatype, basetype> & operator-(basetype  tv,Variable<datatype, basetype> &tb)
{
	return (tb-tv);
}
;
template <class datatype,class basetype>
Node<datatype, basetype> & operator/(basetype  tv,Variable<datatype, basetype> &tb)
{
	return (tb/tv);
}
;

template <class datatype,class basetype>
Node<datatype, basetype> & operator+(datatype  tv,Variable<datatype, basetype> &tb)
{
	return (tb+tv);
}
template <class datatype,class basetype>
Node<datatype, basetype> & operator*(datatype  tv,Variable<datatype, basetype> &tb)
{
	return (tb*tv);
}
;
template <class datatype,class basetype>
Node<datatype, basetype> & operator-(datatype  tv,Variable<datatype, basetype> &tb)
{
	return (tb-tv);
}
;
template <class datatype,class basetype>
Node<datatype, basetype> & operator/(datatype  tv,Variable<datatype, basetype> &tb)
{
	return (tb/tv);
}

template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator+(datatype &  tv)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(outnode,&tv,vadd<datatype, basetype>);
	return (*tp);
}

template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator-(datatype &  tv)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(outnode,&tv,vminus<datatype, basetype>);
	return (*tp);
}
template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator*(datatype &  tv)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(outnode,&tv,vmultiply<datatype, basetype>);
	return (*tp);

}
template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator/(datatype &  tv)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(outnode,&tv,vdivide<datatype, basetype>);
	return (*tp);
}


template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator+(basetype  tv)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(outnode,tv,vadd<datatype, basetype>);
	return (*tp);
}

template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator-(basetype  tv)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(outnode,tv,vminus<datatype, basetype>);
	return (*tp);
}

template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator*(basetype  tv)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(outnode,tv,vmultiply<datatype, basetype>);
	return (*tp);

}
template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator/(basetype  tv)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(outnode,tv,vdivide<datatype, basetype>);
	return (*tp);
}

template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator+(Node<datatype, basetype> &tn)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(&tn,outnode,vadd<datatype, basetype>);
	return (*tp);
}

template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator-(Node<datatype, basetype> &tn)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(&tn,outnode,vminus<datatype, basetype>);
	return tp;
}

template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator*(Node<datatype, basetype> &tn)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(&tn,outnode,vmultiply<datatype, basetype>);
	return tp;
}
template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator/(Node<datatype, basetype> &tn)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(&tn,outnode,vdivide<datatype, basetype>);
	return tp;
}
;
template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator=(Node<datatype, basetype> &tn)
{
   // this->rootnode=vequal
	rootnode=new Node<datatype, basetype>(&tn,&tempdata,vequal<datatype, basetype>);
    (*rootnode).setroot(true);
    this->isalive=true;
    return (*rootnode);
}
;
template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator=(datatype &tn)
{
      this->rootnode=new Node<datatype, basetype>(&tn,&tempdata,vequal<datatype, basetype>);
      (*rootnode).setroot(true);
      this->isalive=true;
      return (*rootnode);
}
template <class datatype,class basetype>
Node<datatype, basetype> & Variable<datatype, basetype>::operator=(Variable &tn)
{
      this->rootnode=new Node<datatype, basetype>(tn.outnode,&tempdata,vequal<datatype, basetype>);
      (*rootnode).setroot(true);
      this->isalive=true;

      return (*rootnode);
}
template <class datatype,class basetype>
void Variable<datatype, basetype>::calculate()
{
	cout<<"calculate "<<endl;
	if(rootnode)
	{
		(*rootnode).caculate();
	}
}
template <class datatype,class basetype>
void Variable<datatype, basetype>::updatedata()
{
     if(data)
     {
    	 (*data)=tempdata;
     }
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
*/
#endif /* VARIABLES_H_ */
