/*
 * HClass.h
 *
 *  Created on: 2018Äê8ÔÂ23ÈÕ
 *      Author: YAO
 */

#ifndef HCLASS_H_
#define HCLASS_H_
#include "baseClass.h"
#include "LineOp.h"
#include "gragh.h"
template<class type>
class Bergers:public Hbase<type>
{
private:
	Variable<Line<type>,type> * origin=nullptr;
	Line<type> bdata;
	Line<type> odata;
	int size;
public:
	Bergers(Variable<Line<type>,type> * data,int size);
	~Bergers();
	void getRP(int index,type *origin,type *dp,type *dm,int order);
    type getRM(int index,type v,int order);
    void update();

};

template<class type>
Bergers<type>::Bergers(Variable<Line<type>,type> * data,int size):Hbase<type>()
{
	this->origin=data;
	bdata=bdata.zeros(size-1);
	odata=odata.zeros(size);
	this->size=size;
}
template<class type>
void Bergers<type>::getRP(int index,type *data,type *dp,type *dm,int order)
{
     pair<int ,type> *tp=new pair<int,type>[order];
     type max=0;
     /*
     for(int i=0;i<order;i++)
     {
    	 if(max<abs(bdata[i+index])) max=bdata[i+index];
    	 //*(tp+i)=pair<int,type>(i,bdata[i+index]);
     }

     for(int i=0;i<order;i++)
     {
    	 for(int j=i+1;j<order;j++)
    	 {
    		 pair<int ,type> temp;
    		 if(tp[i].second>tp[j].second)
    		 {
    			 temp=tp[i];
    			 tp[i]=tp[j];
    			tp[j]=temp;
    		 }
    	 }
     }
     */
     for(int i=0;i<order;i++)
     {
    	// if(tp[i].first==i) tempv=bdata[index+i];
    	 *(dp+i)=(*(data+i)+abs(odata[i+index])*(odata[i+index]))*0.5;
    	 *(dm+i)=(*(data+i)-abs(odata[i+index])*(odata[i+index]))*0.5;
     }
     /*
     if(index==102)
     {
    	 for(int m=0;m<5;m++)
    	 {
    		 cout<<"tp: "<<m<<" key "<<tp[m].first<<" vlaue"<<tp[m].second<<endl;
    	 }
     }
     */
     delete [] tp;


}
template<class type>
type Bergers<type>::getRM(int index,type v,int order)
{
   return v;
}
template<class type>
void Bergers<type>::update()
{
	for(int i=0;i<size-1;i++)
	{
		bdata[i]=((*origin).getdata()[i]+(*origin).getdata()[i+1])*0.5;
	}
	bdata=weno_1D_extendBoundary(bdata,1,5);
	odata=weno_1D_extendBoundary<type>((*origin).getdata(),1,5);
}
template<class type>
Bergers<type>::~Bergers()
{

}
#endif /* HCLASS_H_ */
