/*
 * Common.h
 *
 *  Created on: 2018��8��30��
 *      Author: YAO
 */

#ifndef COMMON_H_
#define COMMON_H_
#include "LineOp.h"
#include "MetrixOp.h"
#include "baseFunction.h"
#include "baseClass.h"
template<class type>
class LDiffusion:public Calculable<Line<type>>
{
private :
	Line<type> tdata;
	Line<type> rdata;
	int order=5;
	int size=1;
	type dx;
	type visc=1E-8;
	int boundarytype=1;
public:
	LDiffusion(int size,type dx,int boundarytype=1,int order=7,type visc=1E-8);
	~LDiffusion(){};
    void diffuse(Line<type> &data,Line<type> &result);
    Line<type>& calculate(Line<type> &data);
};
template<class type>
LDiffusion<type>::LDiffusion(int size,type dx,int boundarytype,int order,type visc)
{
	this->boundarytype=boundarytype;
	this->order=order;
	this->size=size;
	tdata=tdata.zeros(this->size+order-1);
	rdata=rdata.zeros(this->size);
	this->visc=visc;
	this->dx=dx;
}
template<class type>
void LDiffusion<type>::diffuse(Line<type> &data,Line<type> &result)
{
	int size=data.getCols();
	if(order==7)
	{
		tdata=weno_1D_extendBoundary(data,boundarytype,order);
		for(int i=3;i<size+3;i++)
		{
			result[i-3]= (-49.0/18.0*tdata[i]+1.5*(tdata[i-1]+tdata[i+1])-
					0.15*(tdata[i-2]+tdata[i+2])+1.0/90.0*(tdata[i+3]+tdata[i-3]))*visc
					/(dx*dx);
		}
	}
}
template<class type>
Line<type> & LDiffusion<type>::calculate(Line<type> &data)
{

	this->diffuse(data,this->rdata);
	return rdata;
}


#endif /* COMMON_H_ */
