/*
 * Weno1D.cpp
 *
 *  Created on: 2018Äê7ÔÂ17ÈÕ
 *      Author: YAO
 */

#include "Weno1D.h"
#include "baseFunction.h"
//#include "LineOp.h"
Line<dtype>& Weno1D::weno3rd(Line<dtype> &input)
{
	//input.show();

	this->tempr=weno_1D_extendBoundary(input,1,3);
	//tempr.show();
	int size=input.getCols();
	Line<dtype> *tp=Line<dtype>::addTempNode(size-1);
	this->half_m=input.zeros(size);
	this->half_p=input.zeros(size);
	this->flux=input.zeros(size);

	for(int i=0;i<size;i++)
	{
		WENO3(tempr[i],tempr[1+i],tempr[2+i],half_m[i],half_p[i]);
	}

	if(this->h_func==NULL)
	{
		(*tp)=half_m;
	}
	else
	{
		for(int i=0;i<size-1;i++)
		{
			(*tp)[i]=this->h_func(half_m[i],half_p[i]);
		}
	}
    return (*tp);
}
void Weno1D::setHfunc(dtype (*func)(dtype,dtype))
{
	this->h_func=func;
}
void Weno1D::setboudaryconditon(int condition)
{
	this->boudarytype=condition;
}
void Weno1D::setextendtype(int extend)
{
	this->extendtype=extend;
}
Line<dtype>& Weno1D::weno5rd(Line<dtype> &input)
{
	//input.show();

//this->tempr=weno_1D_extendBoundary(input,this->extendtype,5);
	this->tempr=weno_1D_extendBoundary(input,this->extendtype,5);
	//cout<<"tempr"<<endl;
    //tempr.show();
	int size=this->cols;
	Line<dtype> *tp=Line<dtype>::addTempNode(size-1);
	this->half_m=input.zeros(size-1);
	this->half_p=input.zeros(size-1);
	this->flux=input.zeros(size-1);
	if(!hf)
	{

		for(int i=0;i<size-1;i++)
		{
			WENO5(tempr[i],tempr[1+i],tempr[2+i],tempr[3+i],tempr[4+i],half_m[i],half_p[i]);
		}

		if(this->h_func==NULL)
		{
			(*tp)=half_m;
		}
		else
		{
			for(int i=0;i<size-1;i++)
			{
				(*tp)[i]=this->h_func(half_m[i],half_p[i]);
			}
		}
	}
	else
	{
		(*hf).update();
		for(int i=0;i<size-1;i++)
		{
			dtype temp_m[5];
			dtype temp_p[5];
			dtype tv_p;
			dtype tv_m;
			(*hf).getRP(i,&(tempr[i]),&(temp_m[0]),&(temp_p[0]),5);
			tv_p=WENO5P(temp_p[0],temp_p[1],temp_p[2],temp_p[3],temp_p[4]);
			tv_m=WENO5M(temp_m[0],temp_m[1],temp_m[2],temp_m[3],temp_m[4]);
			(*tp)[i]=tv_p+tv_m;
		}
	}

    return (*tp);
}
void Weno1D::sethclass(Hbase<dtype>*hc)
{
	this->hf=hc;
}

void Weno1D::test()
{

}
Line<dtype>& Weno1D::partialX(Line<dtype> &input,int boudarytype)
{
	int size=input.getCols();
	Line<dtype> *tp=Line<dtype>::addTempNode(size+1);
    if(this->x_uniform)
    {
        for(int i=1;i<size;i++)
        {
        	(*tp)[i]=(input[i]-input[i-1])/dx;
        }
    }
    else
    {
    	for(int i=1;i<size;i++)
    	{
    		(*tp)[i]=(input[i]-input[i-1])*2.0/(this->x_axis[i+1]-this->x_axis[i-1]);
    	}
    }
    if(boudarytype==1)
    {

    	if(this->x_uniform)
    	{
    		//(*tp)[0]=(*tp)[size-1];

    		dtype tv=(input[0]-input[size-1])/dx;
    		(*tp)[0]=tv;
    		(*tp)[size]=tv;

    	}
    	else
    	{
    		dtype tv=(input[0]-input[size-1])*2.0/(x_axis[size]-x_axis[size-1]+x_axis[1]-x_axis[0]);
    		(*tp)[0]=tv;
    		(*tp)[size]=tv;
    	}
    }
    if(boudarytype==2)
    {
    	(*tp)[0]=0.0;
    	(*tp)[size]=0.0;
    }
    if(boudarytype==3)
    {
    	(*tp)[0]=(*tp)[1];
    	(*tp)[size]=(*tp)[size-1];
    }
   return (*tp);
}
Line<dtype> & Weno1D::caculate(Line<dtype> &input)
{
	int size=input.getCols();
	Line<dtype> *tp=Line<dtype>::addTempNode(size);
	//(*tp)=this->weno3rd(input);
	(*tp)=this->weno5rd(input);
	(*tp)=this->partialX((*tp), 1);
	return (*tp);

}
 Line<dtype> & Weno1D::calculate(Line<dtype> &input)
{
	int size=input.getCols();
	Line<dtype> *tp=Line<dtype>::addTempNode(size);
	//(*tp)=this->weno3rd(input);
	(*tp)=this->weno5rd(input);
	//cout<<"tp"<<endl;
	//(*tp).show();
	(*tp)=this->partialX((*tp), this->boudarytype);
	return (*tp);

}
Weno1D::Weno1D(int cols,dtype dx)
{

	this->dx=dx;
	this->x_uniform=true;
	this->cols=cols;
	this->data=Line<dtype>::zeros(cols);
	this->flux=Line<dtype>::zeros(cols);
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			this->Rmetrix_m[i][j]=0;
			this->Rmetrix_p[i][j]=0;
			if(i==j)
			{
				Rmetrix_m[i][j]=1;
				this->Rmetrix_p[i][j]=1.0;
			}
		}
	}
	// TODO Auto-generated constructor stub

}
Line<dtype> & Weno1D::RK3Method(Line<dtype> &input,dtype dt,dtype &t)
{
	int size=input.getCols();
	Line<dtype> *tp=Line<dtype>::addTempNode(size);
	this->rk_1=input-caculate(input)*dt;
	this->rk_2=rk_1*1.0/4.0+input*(3.0/4.0)-caculate(rk_1)*(dt*1.0/4.0);
    (*tp)=rk_2*(2.0/3.0)+input*(1.0/3.0)-caculate(rk_2)*(dt*2.0/3.0);
	t=t-dt;
	return (*tp);

}
void Weno1D::getbegersRMetix(int index)
{

}
Weno1D::Weno1D(int cols,Line<dtype> &x_axis,dtype dx):Calculable<Line<dtype>>()
{
 this->dx=dx;
 this->x_uniform=false;
 this->x_axis=x_axis;
 this->x_axis=Line<dtype>::zeros(cols);
}
Weno1D::~Weno1D()
{
	// TODO Auto-generated destructor stub
}

