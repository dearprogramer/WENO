/*
 * node.h
 *
 *  Created on: 2018年8月8日
 *      Author: YAO
 */

#ifndef NODE_H_
#define NODE_H_
/*
 * Node.h
 *
 *  Created on: 2018年8月8日
 *      Author: YAO
 */

#include<iostream>
#include "baseClass.h"
using namespace std;
template <class datatype,class basetype>
datatype & vequal(datatype &ta,datatype &tb)
{
	ta=tb;
	return ta;
}

template <class datatype,class basetype>
datatype & equals(datatype &ta,datatype &tb)
{
	//ta=tb;
	return ta;
}
template <class datatype,class basetype>
datatype & vadd(datatype &ta,datatype &tb)
{
	return ta+tb;
}

template <class datatype,class basetype>
datatype & vadd(datatype &ta,basetype tv)
{
	return (ta+tv);
}


template <class datatype,class basetype>
datatype & vminus(datatype &ta,basetype tv)
{
	return ta-tv;
}

template <class datatype,class basetype>
datatype & vminus(datatype &ta)
{
	return -ta;
}
template <class datatype,class basetype>
datatype & vminus(datatype &ta,datatype &tb)
{
	return ta-tb;
}

template <class datatype,class basetype>
datatype & vmultiply(datatype &ta,datatype &tb)
{
	return ta*tb;
}

template <class datatype,class basetype>
datatype & vmultiply(datatype &ta,basetype tv)
{
	return ta*tv;
}

template <class datatype,class basetype>
datatype & vdivide(datatype & ta,datatype & tb)
{
	return ta/tb;
}

template <class datatype,class basetype>
datatype & vdivide(datatype & ta,basetype & tb)
{
	return ta/tb;
}
;
template <class datatype,class basetype>
class Node
{
protected :
	int type=0;
	bool root=false;
	basetype pa=0;
	datatype *da=nullptr;
	datatype *db=nullptr;
	datatype *dc=nullptr;
	basetype pb=0;
	Node<datatype, basetype> * next=nullptr;
	Node<datatype, basetype> * privious=nullptr;
	Node<datatype, basetype> * leftchild=nullptr;
	Node<datatype, basetype> * rightchild=nullptr;
	int no=0;
	bool visited=false;
	bool istemp=false;
	static int tempcount;
	static int count;
	void setleftchild(Node<datatype, basetype> *cl);
	void setrightchild(Node<datatype, basetype> *cr);
	void setprivious(Node<datatype, basetype> * p);
	void setnext(Node<datatype, basetype> * n);
	void addnode();
	void deletethis();

	void settemp(bool value=true);

private :
	static Node<datatype, basetype> * begin;
	static Node<datatype, basetype> * end;
	datatype & (*func1)(datatype &,datatype &)=NULL;
	datatype & (*func2)(datatype &,basetype)=NULL;
	datatype & (*func3)(datatype &)=NULL;


public :
	Node();
	Node(datatype *ta); //0
	Node(Node<datatype, basetype> * tn); //8
	Node(datatype *ta,datatype *tb,datatype & (* func)(datatype &,datatype &)); //1
	Node(datatype *ta,basetype tv,datatype &(* func)(datatype &,basetype )); //2
	Node(datatype *ta,datatype &(* func)(datatype &)); //3
	Node(Node<datatype, basetype> * tn,datatype * tv,datatype & (* func)(datatype &,datatype &));//4
	Node(Node<datatype, basetype> * tn,basetype tv,datatype & (* func)(datatype &,basetype ));//5
	Node(Node<datatype, basetype> * tn,datatype & (* func)(datatype &));
	Node(Node<datatype, basetype> * tm,Node<datatype, basetype>*  tn,datatype & (* func)(datatype &,datatype &));
    bool isroot();
	bool istempnode();
	int gettype();
	int  getindex();
	void setroot(bool value);
	static Node<datatype, basetype> * getbegin();
	static Node<datatype, basetype> & addtempnode(Node<datatype, basetype> &tn,datatype &(* func)(datatype &));
	static Node<datatype, basetype> & addtempnode(Node<datatype, basetype> &tn,basetype  ta,datatype &(* func)(datatype &,basetype));

	Node<datatype, basetype> & operator-();
	Node<datatype, basetype> & operator+();
	Node<datatype, basetype> & operator+(Node<datatype, basetype> & tn);
	Node<datatype, basetype> & operator-(Node<datatype, basetype> & tn);
	Node<datatype, basetype> & operator*(Node<datatype, basetype> & tn);
	Node<datatype, basetype> & operator/(Node<datatype, basetype> & tn);

	Node<datatype, basetype> & operator+(basetype tn);
	Node<datatype, basetype> & operator-(basetype tn);
	Node<datatype, basetype> & operator*(basetype  tn);
	Node<datatype, basetype> & operator/(basetype  tn);

	Node<datatype, basetype> & operator+(datatype &tn);
	Node<datatype, basetype> & operator-(datatype &tn);
	Node<datatype, basetype> & operator*(datatype &tn);
	Node<datatype, basetype> & operator/(datatype &tn);

	Node<datatype, basetype> * getnext();
	Node<datatype, basetype> * getleftchild();
	Node<datatype, basetype> * getrightchild();
	Node<datatype, basetype> * getprivious();
    virtual ~Node()
    {
    	count=count-1;
    	if(istemp)
    	{
    		deletethis();
    	}

    	if(dc)
    		{
    		datatype *ts;
    		ts=dc;
    		delete ts;
    		}

    	cout<<"destory "<<no<<" tempcout "<<tempcount<<" cout "<<count<<endl;
    	if(count<=tempcount)
    	{
    		if(!istemp)
    		{
    			Node<datatype, basetype> *tp=begin;
    			   while(tp)
    			    {
    			    Node<datatype, basetype> *p;
    			                p=tp;
    			    			tp=(*p).next;
    			    			delete p;
    			    		}
    		}
    	}
    }
    ;
    virtual datatype & caculate()
    {
    	switch(type)
    	{
    	case 0:
    		return (*da);
    		break;
    	case 1:
    		return func1(*da,*db);
    	break;
    	case 2:
    		return func2(*da,pa);
    		break;
    	case 3:
    		return func1(*da,(*leftchild).caculate());
    		break;
    	case 4:
    		return func3(*da);
    		break;
    	case 5:
    		return func2((*leftchild).caculate(),pa);
    		break;
    	case 6:
    		return func3((*leftchild).caculate());
    		break;
    	case 7:
    		return func1((*leftchild).caculate(),(*rightchild).caculate());
    		break;
    	case  8:
    		return (*leftchild).caculate();
    		break;
    	case  9:
    		return (*dc);
    		break;
    	}
    };
};
template <class datatype,class basetype>
class NodeOp:public Node<datatype,basetype>
{
private:

	Calculable<datatype> *tc;
	int optype=0;
public:
	virtual datatype& caculate()
	{
	   if(this->tc)
	   {
		   switch(optype)
		   {
		   case 0:
			   return (*(this->dc));
			   break;
		   case 1:
			   return (*tc).calculate((*(this->da)));
			   break;
		   case 2:
			   return (*tc).calculate((*this->leftchild).caculate());
			   break;
		   }

	   }
	};
	NodeOp(Calculable<datatype> *pc);
	NodeOp(Calculable<datatype> *pc,Node<datatype ,basetype> *tn);
	NodeOp(Calculable<datatype> *pc,datatype *tn);
	void setOp(Calculable<datatype> *pc);
	Node<datatype ,basetype> &operator()(Node<datatype ,basetype> &tn);
	Node<datatype ,basetype> &operator()(datatype &tn);
	virtual ~NodeOp(){};
};

template <class datatype,class basetype>
int Node<datatype,basetype>::count=0;

template <class datatype,class basetype>
int Node<datatype,basetype>::tempcount=0;

template <class datatype,class basetype>
Node<datatype,basetype>* Node<datatype,basetype>::begin=nullptr;

template <class datatype,class basetype>
Node<datatype,basetype>* Node<datatype,basetype>::end=nullptr;
template <class datatype,class basetype>
Node<datatype,basetype>& Node<datatype,basetype>::addtempnode(Node<datatype, basetype> &tn,datatype &(* func)(datatype &))
{
	Node<datatype,basetype> *tp=new Node<datatype,basetype>(&tn,func);
	(*tp).settemp(true);
	return (*tp);
}
template <class datatype,class basetype>
Node<datatype,basetype>& Node<datatype,basetype>::addtempnode(Node<datatype, basetype> &tn,basetype  ta,datatype &(* func)(datatype &,basetype))
{
	Node<datatype,basetype> *tp=new Node<datatype,basetype>(&tn,ta,func);
	(*tp).settemp(true);
	return (*tp);
}
template <class datatype,class basetype>
Node<datatype,basetype>::Node()
{
	this->type=9;
	dc=new datatype();
	no=count;
	cout<<"new node"<<no<<" type "<<type<<endl;
	count=count+1;
};
template <class datatype,class basetype>
Node<datatype,basetype>::Node(datatype *ta)
{
	this->type=0;
	no=count;
	cout<<"new node"<<no<<" type "<<type<<endl;
	count=count+1;
};
template <class datatype,class basetype>
Node<datatype,basetype>::Node(Node<datatype,basetype> *tn)
{
	this->type=8;
	this->leftchild=tn;
	no=count;
	cout<<"new node"<<no<<" type "<<type<<endl;
	count=count+1;
};
template <class datatype,class basetype>
Node<datatype,basetype>::Node(datatype *ta,datatype *tb,datatype & (* func)(datatype &,datatype &))
{
	this->type=1;
	da=ta;
	db=tb;
	func1=func;
	no=count;
	cout<<"new node"<<no<<" type "<<type<<endl;
	count=count+1;
};
template <class datatype,class basetype>
Node<datatype,basetype>::Node(datatype *ta,basetype tv,datatype &(* func)(datatype &,basetype ))
{
	this->type=2;
	da=ta;
	pa=tv;
	func2=func;
	no=count;
	cout<<"new node"<<no<<" type "<<type<<endl;
	count=count+1;
}
template <class datatype,class basetype>
Node<datatype,basetype>::Node(Node<datatype,basetype> * tn,datatype *tv,datatype & (* func)(datatype &,datatype &))
{
	this->type=3;
	this->leftchild=tn;
	da=tv;
	func1=func;
	no=count;
	cout<<"new node"<<no<<" type "<<type<<endl;
	count=count+1;
}
;
template <class datatype,class basetype>
Node<datatype,basetype>::Node(datatype *ta,datatype &(* func)(datatype &))
{
	this->type=4;
	da=ta;
	func3=func;
	no=count;
	cout<<"new node"<<no<<endl<<" type "<<type;
	count=count+1;
}

template <class datatype,class basetype>
Node<datatype,basetype>::Node(Node<datatype,basetype> * tn,basetype tv,datatype &(* func)(datatype &,basetype ))
{
	this->type=5;
	leftchild=tn;
	pa=tv;
	func2=func;
	no=count;
	cout<<"new node"<<no<<" type "<<type<<endl;
	count=count+1;
}

template <class datatype,class basetype>
 Node<datatype,basetype>::Node(Node<datatype,basetype> * tn,datatype &(* func)(datatype &))
{
	this->type=6;
	leftchild=tn;
	func3=func;
	no=count;
	cout<<"new node"<<no<<endl<<" type "<<type;
	count=count+1;
}

template <class datatype,class basetype>
Node<datatype,basetype>::Node(Node<datatype,basetype> * tm,Node<datatype,basetype>*  tn,datatype & (* func)(datatype &,datatype &))
{
	this->type=7;
	leftchild=tm;
	rightchild=tn;
	func1=func;
	no=count;
	cout<<"new node"<<no<<endl;
	count=count+1;
}

template <class datatype,class basetype>
void Node<datatype,basetype>::addnode()
{
	//cout<<"new tempnode "<<tempcount<<" "<<count;
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
	tempcount=tempcount+1;
}
template <class datatype,class basetype>
void Node<datatype,basetype>::deletethis()
{
	Node<datatype,basetype> *pv,*nt;
	pv=this->privious;
	nt=this->next;
    tempcount=tempcount-1;

	cout<<"dlete tempnode "<<tempcount<<" "<<no<<endl;
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
}
template <class datatype,class basetype>
void Node<datatype,basetype>::settemp(bool value)
{
	if(istemp!=value)
	{
		if(value)
		{
			this->addnode();
		}
		else
		{
			this->deletethis();
		}
	}
	this->istemp=value;

}

template <class datatype,class basetype>
void Node<datatype,basetype>::setleftchild(Node *cl)
{
	this->leftchild=cl;
}

template <class datatype,class basetype>
void Node<datatype,basetype>::setrightchild(Node *cr)
{
	this->rightchild=cr;
}

template <class datatype,class basetype>
void Node<datatype,basetype>::setprivious(Node *p)
{
	this->privious=p;

}

template <class datatype,class basetype>
void Node<datatype,basetype>::setnext(Node *tn)
{
	this->next=tn;
}

template <class datatype,class basetype>
void Node<datatype,basetype>::setroot(bool value)
{
   this->root=value;
}
template <class datatype,class basetype>
int Node<datatype,basetype>::gettype()
{
	return type;
}
template <class datatype,class basetype>
int Node<datatype,basetype>::getindex()
{
	return no;
}

template <class datatype,class basetype>
bool Node<datatype,basetype>::istempnode()
{
	return istemp;
}

template <class datatype,class basetype>
Node<datatype,basetype> * Node<datatype,basetype>::getnext()
{
	return this->next;
}
template <class datatype,class basetype>
Node<datatype,basetype> * Node<datatype,basetype>::getbegin()
{
	return begin;
}
template <class datatype,class basetype>
Node<datatype,basetype> * Node<datatype,basetype>::getprivious()
{
	return this->privious;
}

template <class datatype,class basetype>
Node<datatype,basetype> * Node<datatype,basetype>::getleftchild()
{
	return this->leftchild;
}


template <class datatype,class basetype>
Node<datatype,basetype> * Node<datatype,basetype>::getrightchild()
{
	return this->rightchild;
}


template <class datatype,class basetype>
bool Node<datatype,basetype>::isroot()
{
	return this->root;
}
template <class datatype,class basetype>
Node<datatype,basetype> & Node<datatype,basetype>::operator+(Node<datatype,basetype> & tn)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(this,&tn,vadd);
	(*tp).settemp(true);
	return (*tp);
}
template <class datatype,class basetype>
Node<datatype,basetype> & Node<datatype,basetype>::operator-(Node<datatype,basetype> &tn)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(this,&tn,vminus);
	(*tp).settemp(true);
	return (*tp);
}
;
template <class datatype,class basetype>
Node<datatype,basetype> & Node<datatype,basetype>::operator*(Node<datatype,basetype> &tn)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(this,&tn,vmultiply<datatype, basetype>);
	(*tp).settemp(true);
	return (*tp);
};
template <class datatype,class basetype>
Node<datatype,basetype> & Node<datatype,basetype>::operator/(Node<datatype,basetype> &tn)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(this,&tn,vdivide<datatype, basetype>);
	(*tp).settemp(true);
	return (*tp);
};

template <class datatype,class basetype>
Node<datatype,basetype> & Node<datatype,basetype>::operator+(datatype & tn)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(this,&tn,vadd<datatype, basetype>);
	(*tp).settemp(true);
	return (*tp);
};
template <class datatype,class basetype>
Node<datatype,basetype> & Node<datatype,basetype>::operator-(datatype &tn)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(this,&tn,vminus<datatype, basetype>);
	(*tp).settemp(true);
	return (*tp);
}
;
template <class datatype,class basetype>
Node<datatype,basetype> & Node<datatype,basetype>::operator*(datatype &tn)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(this,&tn,vmultiply<datatype, basetype>);
	(*tp).settemp(true);
	return (*tp);
}
;
template <class datatype,class basetype>
Node<datatype,basetype> & Node<datatype,basetype>::operator/(datatype &tn)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(this,tn,vdivide<datatype, basetype>);
	(*tp).settemp(true);
	return (*tp);
}
template <class datatype,class basetype>
Node<datatype,basetype> & Node<datatype,basetype>::operator+(basetype tn)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(this,tn,vadd<datatype, basetype>);
	(*tp).settemp(true);
	return (*tp);
};
template <class datatype,class basetype>
Node<datatype,basetype> & Node<datatype,basetype>::operator-(basetype tn)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(this,tn,vminus<datatype, basetype>);
	(*tp).settemp(true);
	return (*tp);
}
;
template <class datatype,class basetype>
Node<datatype,basetype> & Node<datatype,basetype>::operator-()
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(this,vminus<datatype, basetype>);
	(*tp).settemp(true);
	return (*tp);
}
;
template <class datatype,class basetype>
Node<datatype,basetype> & Node<datatype,basetype>::operator+()
{
	return (*this);
}
;
template <class datatype,class basetype>
Node<datatype,basetype> & Node<datatype,basetype>::operator*(basetype tn)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(this,tn,vmultiply<datatype, basetype>);
	(*tp).settemp(true);
	return (*tp);
}
;
template <class datatype,class basetype>
Node<datatype,basetype> & Node<datatype,basetype>::operator/(basetype tn)
{
	Node<datatype,basetype> * tp=new Node<datatype,basetype>(this,tn,vdivide<datatype, basetype>);
	(*tp).settemp(true);
	return (*tp);
}

//node op
template<class datatype,class basetype>
NodeOp<datatype,basetype>::NodeOp(Calculable<datatype> *pc):Node<datatype,basetype>()
{
	tc=pc;
	optype=0;
}
template<class datatype,class basetype>
NodeOp<datatype,basetype>::NodeOp(Calculable<datatype> *pc,Node<datatype ,basetype> *tn):Node<datatype,basetype>()
{
	tc=pc;
	this->leftchild=tn;
	optype=2;
}

template<class datatype,class basetype>
NodeOp<datatype,basetype>::NodeOp(Calculable<datatype> *pc,datatype *tn):Node<datatype,basetype>()
{
	tc=pc;
	this->da=tn;
	optype=1;
}

template<class datatype,class basetype>
void NodeOp<datatype,basetype>::setOp(Calculable<datatype> *pc)
{
	tc=pc;
}
template<class datatype,class basetype>
Node<datatype ,basetype> & NodeOp<datatype,basetype>::operator()(Node<datatype ,basetype> &tn)
{
	NodeOp<datatype,basetype> * tp=new NodeOp(tc,&tn);
	(*tp).settemp(true);
     return (*tp);
}
template<class datatype,class basetype>
Node<datatype ,basetype> & NodeOp<datatype,basetype>::operator()(datatype &tn)
{
	NodeOp<datatype,basetype> * tp=new NodeOp(tc,&tn);
	(*tp).settemp(true);
     return (*tp);
}

#endif /* NODE_H_ */
