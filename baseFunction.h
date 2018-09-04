/*
 * baseFunction.h
 *
 *  Created on: 2018Äê7ÔÂ17ÈÕ
 *      Author: YAO
 */

#ifndef BASEFUNCTION_H_
#define BASEFUNCTION_H_
const double ebson=1e-6;
template<class Type>
Line<Type> & lax_fux(Line<Type> & a,Line<Type> &b)
{
	return (a+b);
}
template<class Type>
Type  lax_fux(Type  a,Type b)
{
	return (a+b);
}
template<class dtype>
Line <dtype> & weno_1D_extendBoundary(Line <dtype>& data,int type,int order)
{
	int size=data.getCols()+order-1;
	int cols=data.getCols();
	int halforder=(order/2);
	Line<dtype> * tp=Line<dtype>::addTempNode(size);
	if(type==1)
	{
		for(int i=0;i<halforder;i++)
		{
			(*tp)[i]=data[cols+i-halforder-1];
			(*tp)[size-halforder+i]=data[i+1];
		}
		for(int i=0;i<cols;i++)
		{
			(*tp)[i+halforder]=data[i];
		}
	}
	if(type==2)
	{
		for(int i=0;i<halforder;i++)
		{
			(*tp)[i]=pow(10*(halforder-i),10);
			(*tp)[size-halforder+i]=pow(10*i+10,10);

		}
		for(int i=0;i<cols;i++)
		{
			(*tp)[i+halforder]=data[i];
		}
	}
	if(type==3)
	{
		for(int i=0;i<halforder;i++)
		{
			(*tp)[halforder-i-1]=data[i];
			(*tp)[size-halforder+i]=data[cols-i-1];

		}
		for(int i=0;i<cols;i++)
		{
			(*tp)[i+halforder]=data[i];
		}
	}
	return (*tp);
}
template<class type>
type WENO3P(type a1,type a2,type a3)
{
	type v[2],alpha[2],beta[2],total,rt;
	v[0]=0.5*a2+0.5*a3;
	v[1]=-0.5*a1+1.5*a2;
	beta[0]=(a3-a2)*(a3-a2);
	beta[1]=(a2-a1)*(a2-a1);
	alpha[0]=(2.0/3.0)/((beta[0]+ebson)*(beta[0]+ebson));
	alpha[1]=(1.0/3.0)/((beta[0]+ebson)*(beta[0]+ebson));
	total=alpha[0]+alpha[1];
	rt=v[0]*(alpha[0]/total)+v[1]*(alpha[1]/total);
	return rt;
}
template<class type>
type WENO3M(type a1,type a2,type a3)
{
	type v[2],alpha[2],beta[2],total,rt;
	v[0]=0.5*a2+0.5*a3;
	v[1]=-0.5*a1+1.5*a2;
	beta[0]=(a3-a2)*(a3-a2);
	beta[1]=(a2-a1)*(a2-a1);
	alpha[0]=(1.0/3.0)/((beta[0]+ebson)*(beta[0]+ebson));
	alpha[1]=(2.0/3.0)/((beta[0]+ebson)*(beta[0]+ebson));
	total=alpha[0]+alpha[1];
	rt=v[0]*(alpha[0]/total)+v[1]*(alpha[1]/total);
	return rt;
}
template<class type>
void WENO3(type a1,type a2,type a3,type &rt_m,type &rt_p)
{
	type v[2],alpha[2],beta[2],total,rt;
	v[0]=0.5*a2+0.5*a3;
	v[1]=-0.5*a1+1.5*a2;

	beta[0]=(a3-a2)*(a3-a2);
	beta[1]=(a2-a1)*(a2-a1);

	beta[0]=1.0/((beta[0]+ebson)*(beta[0]+ebson));
	beta[1]=1.0/((beta[1]+ebson)*(beta[1]+ebson));

	alpha[0]=(1.0/3.0)*beta[0];
	alpha[1]=(2.0/3.0)*beta[1];
	total=alpha[0]+alpha[1];
	rt=v[0]*(alpha[0]/total)+v[1]*(alpha[1]/total);
	rt_p=rt;

	alpha[0]=(2.0/3.0)*beta[0];
	alpha[1]=(1.0/3.0)*beta[1];
	total=alpha[0]+alpha[1];
	rt_m=v[0]*(alpha[0]/total)+v[1]*(alpha[1]/total);
}
template<class type>
type WENO5P(type a1,type a2,type a3,type a4,type a5)
{
	type v[3],alpha[3],beta[3],total,rt;
	v[0]=(1.0/3.0)*a3+(5.0/6.0)*a4+(-1.0/6.0)*a5;
	v[1]=(-1.0/6.0)*a2+(5.0/6.0)*a3+(1.0/3.0)*a4;
	v[2]=(1.0/3.0)*a1+(-7.0/6.0)*a2+(11.0/6.0)*a3;
	beta[0]=13.0/12.0*(a3-2*a4+a5)*(a3-2*a4+a5)+1.0/4.0*(3*a3-4*a4+a5)*(3*a3-4*a4+a5);
	beta[1]=13.0/12.0*(a2-2*a3+a4)*(a2-2*a3+a4)+1.0/4.0*(a2-a4)*(a2-a4);
	beta[2]=13.0/12.0*(a1-2*a2+a3)*(a1-2*a2+a3)+1.0/4.0*(a1-4*a2+3*a3)*(a1-4*a2+3*a3);
	alpha[0]=(0.1)/((beta[0]+ebson)*(beta[0]+ebson));
	alpha[1]=(0.6)/((beta[1]+ebson)*(beta[1]+ebson));
	alpha[2]=(0.3)/((beta[2]+ebson)*(beta[2]+ebson));
	total=alpha[0]+alpha[1]+alpha[2];
	rt=v[0]*(alpha[0]/total)+v[1]*(alpha[1]/total)+v[2]*(alpha[2]/total);
	return rt;
}
template<class type>
type WENO5M(type a1,type a2,type a3,type a4,type a5)
{
	type v[3],alpha[3],beta[3],total,rt;
	v[0]=(1.0/3.0)*a3+(5.0/6.0)*a4+(-1.0/6.0)*a5;
	v[1]=(-1.0/6.0)*a2+(5.0/6.0)*a3+(1.0/3.0)*a4;
	v[2]=(1.0/3.0)*a1+(-7.0/6.0)*a2+(11.0/6.0)*a3;
	beta[0]=13.0/12.0*(a3-2*a4+a5)*(a3-2*a4+a5)+1.0/4.0*(3*a3-4*a4+a5)*(3*a3-4*a4+a5);
	beta[1]=13.0/12.0*(a2-2*a3+a4)*(a2-2*a3+a4)+1.0/4.0*(a2-a4)*(a2-a4);
	beta[2]=13.0/12.0*(a1-2*a2+a3)*(a1-2*a2+a3)+1.0/4.0*(a1-4*a2+3*a3)*(a1-4*a2+3*a3);

	alpha[0]=(0.3)/((beta[0]+ebson)*(beta[0]+ebson));
	alpha[1]=(0.6)/((beta[1]+ebson)*(beta[1]+ebson));
	alpha[2]=(0.1)/((beta[2]+ebson)*(beta[2]+ebson));
	total=alpha[0]+alpha[1]+alpha[2];
	rt=v[0]*(alpha[0]/total)+v[1]*(alpha[1]/total)+v[2]*(alpha[2]/total);
	return rt;
}

template<class type>
void WENO5(type a1,type a2,type a3,type a4,type a5,type &rt_m,type &rt_p)
{
	type v[3],alpha[3],beta[3],total;
	v[0]=(1.0/3.0)*a3+(5.0/6.0)*a4+(-1.0/6.0)*a5;
	v[1]=(-1.0/6.0)*a2+(5.0/6.0)*a3+(1.0/3.0)*a4;
	v[2]=(1.0/3.0)*a1+(-7.0/6.0)*a2+(11.0/6.0)*a3;
	beta[0]=13.0/12.0*(a3-2*a4+a5)*(a3-2*a4+a5)+1.0/4.0*(3*a3-4*a4+a5)*(3*a3-4*a4+a5);
	beta[1]=13.0/12.0*(a2-2*a3+a4)*(a2-2*a3+a4)+1.0/4.0*(a2-a4)*(a2-a4);
	beta[2]=13.0/12.0*(a1-2*a2+a3)*(a1-2*a2+a3)+1.0/4.0*(a1-4*a2+3*a3)*(a1-4*a2+3*a3);

	beta[0]=1.0/((beta[0]+ebson)*(beta[0]+ebson));
	beta[1]=1.0/((beta[1]+ebson)*(beta[1]+ebson));
	beta[2]=1.0/((beta[2]+ebson)*(beta[2]+ebson));

	alpha[0]=(0.1)*beta[0];
	alpha[1]=(0.6)*beta[1];
	alpha[2]=(0.3)*beta[2];
	total=alpha[0]+alpha[1]+alpha[2];
	rt_p=v[0]*(alpha[0]/total)+v[1]*(alpha[1]/total)+v[2]*(alpha[2]/total);

	alpha[0]=(0.3)*beta[0];
	alpha[1]=(0.6)*beta[1];
	alpha[2]=(0.1)*beta[2];
	total=alpha[0]+alpha[1]+alpha[2];
	rt_m=v[0]*(alpha[0]/total)+v[1]*(alpha[1]/total)+v[2]*(alpha[2]/total);
}
#endif /* BASEFUNCTION_H_ */
