//============================================================================
// Name        : Tan.cpp
// Author      : tanyao
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "MetrixOp.h"
#include <math.h>
#include "LineOp.h"
#include "Weno1D.h"
#include "DataSave.h"
#include "readData.h"
//#include "Variables.h"
#include "sess.h"
#include "baseFunction.h"
#include "HClass.h"
#include "Common.h"
using namespace std;
/*
Line<double> &vadd(Line<double> &ta,Line<double> &tb)
		{
	return ta+tb;
		}
		*/
Node<Line<double>,double> &cos(Node<Line<double>,double> &tn)
		{
	     cout<<"cos :"<<endl;
	     return Node<Line<double>,double>::addtempnode(tn,cos<double>);
		};
void advfunc()
{
    int pn=321;
    dtype pi=3.1415926;
    dtype dx=1.0/(pn-1);
	dtype dt=pow(dx,5.0/3.0)*0.1;
	dtype t=3.0;
	dtype t0=3.0;
	int dn=int(0.05/dt);
	DataSave<double> ds("data5");
	Weno1D w1(pn,dx);
	NodeOp<Line<double>,double> difx(&w1);
	Line<dtype> axis,ydata,zdata,tdata,theory;
	axis=axis.Linespace(pn)*dx;
	ydata=cos(axis*2*pi);
	zdata=ydata;
	Variable<Line<double>,double> vy(&ydata);
	Session<Line<double>,double> se(t,dt,2);

	ds.writeheader(pn+1);
//*dx;

	ydata.show();
	se.start();
	vy=-difx(vy);
	se.over();
	while(t>0)
	{
	t=se.run(dn);
    ds.writeLine(t0-t,vy.getdata());
    theory=cos(axis*2*pi)*cos((t0-t)*2*pi)+sin(axis*2*pi)*sin((t0-t)*2*pi);
    dtype erro=sum(pow((theory-ydata),2.0))/(pn-1);
    dtype erro1=sum(abs(theory-ydata))/(pn-1);
	std::cout<<(t0-t)<<" "<<ydata[40]<<" "<<theory[40]<<" erro "<<erro
	<<" log2 "<<log2(erro)<<" erro 1 "<<erro1<<" log2 er1  "<<log2(erro1)<<std::endl;
	}
}
void tbegers()
{
	 int pn=1601;
	   dtype pi=3.1415926;
	    dtype dx=1.0/(pn-1);
		dtype dt=dx*0.05;
		dtype t=0.5;
		dtype t0=t;
		int dn=int(0.005/dt);
		DataSave<double> ds("data10");
		Weno1D w1(pn,dx);
		LDiffusion<dtype> dif(pn,dx,1,7,1E-3);
		NodeOp <Line<double>,double> difuse(&dif);
		w1.setextendtype(1);
		w1.setboudaryconditon(1);
		NodeOp<Line<double>,double> difx(&w1);
		Line<dtype> axis(pn),ydata(pn),zdata(pn),tdata(pn),theory(pn);
		axis=axis.Linespace(pn)*dx;
		ydata=cos(axis*2*pi);
		Variable<Line<double>,double> vy(&ydata);
		Bergers<dtype> bg(&vy,pn);
		w1.sethclass(&bg);
		Session<Line<double>,double> se(t,dt,2);
		vy.getdata().show();
		ds.writeheader(pn+1);
		se.start();
		vy=-difx(vy*vy*0.5)+difuse(vy);
		se.over();
		while(t>0)
		{
			t=se.run(dn);
		    ds.writeLine(t0-t,vy.getdata());
		    cout<<"time:"<<(t0-t);
		    vy.getdata().show();
		}
		/*
*/

}
void begers()
{
	 int pn= 201;
	   dtype pi=3.1415926;
	    dtype dx=1.0/(pn-1);
	    dtype dt=dx;
		dtype t=0.5;
		dtype t0=t;
		double vp0 = 0.2;
		double vm0 =1.0;
		int dn=int(0.05/dt);
		DataSave<double> ds("data9");
		Weno1D w1(pn,dx);
		w1.setextendtype(3);
		w1.setboudaryconditon(3);
		NodeOp<Line<double>,double> difx(&w1);
		Line<dtype> axis(pn),ydata(pn),zdata(pn),tdata(pn),theory(pn);
		axis=axis.Linespace(pn)*dx;
		ydata=axis;
		Variable<Line<double>,double> vy(&ydata);
		Bergers<dtype> bg(&vy,pn);
		w1.sethclass(&bg);
		Session<Line<double>,double> se(t,dt,2);
		ds.writeheader(pn+1);
		zdata=weno_1D_extendBoundary<dtype>(axis,3,5);
		zdata.show();
		for(int i=0;i<int(pn/2);i++)
		{
	       ydata[i]=vm0;
	       ydata[i+pn/2]=vp0;

		}
		ydata[pn-1]=vp0;
		//w1.caculate(ydata);

		se.start();
		vy=-difx(vy*vy*0.5);
		se.over();
		vy.getdata().show();

		//t=se.run(100);
	 	//vy.getdata().show();

		while(t>0)
		{
			t=se.run(dn);
		    ds.writeLine(t0-t,vy.getdata());
		    cout<<"time:"<<(t0-t);
		    vy.getdata().show();
		}

		vy.getdata().show();
		cout<<"terminate";
}
int main()
{
	//advfunc();
	tbegers();
	/*
	int pn=201;
	dtype pi=3.1415926;
	dtype dx=1.0/(pn-1);
		//dtype dt=pow(dx*0.1,5.0/3.0);
	dtype dt=dx*0.1;
	dtype t=0.5;
	dtype t0=t;
	Line<dtype> t1(pn),t2(pn),axis(pn);
	t1=t1.Linespace(pn);
	axis=axis.Linespace(pn)*dx;
	t1=cos(axis*2*pi);
	//t1=t1.ones(pn);
	LDiffusion<dtype> dif(pn,dx,1,7);
	Variable<Line<double>,double> vy(&t1);
	NodeOp <Line<double>,double> difuse(&dif);
	Session<Line<double>,double> se(t,dt,2);

    se.start();
    vy=-difuse(vy);
    se.over();
    se.run(2);
    vy.getdata().show();


	//advfunc();

   int pn=201;
   dtype pi=3.1415926;
    dtype dx=1.0/(pn-1);
	//dtype dt=pow(dx*0.1,5.0/3.0);
    dtype dt=dx*0.1;
	dtype t=0.5;
	dtype t0=t;
	double vp0 = 0.2;
	double vm0 =1.0;
	DataSave<double> ds("data4");
	Weno1D w1(pn,dx);
	//w1.setHfunc(lax_fux<dtype>);
	w1.setextendtype(3);
	w1.setboudaryconditon(3);
	NodeOp<Line<double>,double> difx(&w1);
	Line<dtype> axis,ydata,zdata,tdata,theory;
	axis=axis.Linespace(pn)*dx;
	ydata=axis;
	Variable<Line<double>,double> vy(&ydata);
	Bergers<dtype> bg(&vy,pn);
	w1.sethclass(&bg);
	Session<Line<double>,double> se(t,dt,2);
	ds.writeheader(pn+1);
	zdata=weno_1D_extendBoundary<dtype>(axis,3,5);
	zdata.show();
	for(int i=0;i<int(pn/2);i++)
	{
       ydata[i]=vm0;
       ydata[i+pn/2]=vp0;
	}
	ydata[pn-1]=vp0;
	//w1.caculate(ydata);

	se.start();
	vy=-difx(vy*vy*0.5);
	se.over();
	vy.getdata().show();
	//t=se.run(100);
 	//vy.getdata().show();

	while(t>0)
	{
		t=se.run(5);
	    ds.writeLine(t0-t,vy.getdata());
	}

	vy.getdata().show();
	cout<<"terminate";
	/*
 	//t=se.run(10);

 	//zdata.show();


	//DataSave<dtype> ds;
	//ds.writeheader(pn+1);

Line<double> data,data1,data2,data3;
int pn=21;
double dx=1/(pn-1);
data=data.Linespace(21);
data1=data*2.0;
data2=data*3.0;
Weno1D w1(pn,0.01);
NodeOp<Line<double>,double> difx(&w1);
Variable<Line<double>,double> vb(&data1);
Variable<Line<double>,double> vc(&data2);
Variable<Line<double>,double> va(&data);
Session<Line<double>,double> se(2.0,1.0,1);
vc.getdata().show();
se.start();
vc=vb*1.2;//+va*vb+difx(va);//+cos(vc);//+vb*va-data+3.0;
vc=va*1.2;
//va*2;
se.over();
se.run(1);
vc.getdata().show();

se.run(1);
vc.getdata().show();

cout<<"show:"<<endl;
vc.getdata().show();
va.calculate();
vb.calculate();
vc.calculate();
va.updatedata();
vb.updatedata();
vc.updatedata();
vc.getdata().show();


va.setdata(&data3);
vc.calculate();
vc.updatedata();
vc.getdata().show();

vb.getdata().show();
vb.calculate();
vb.updatedata();
vb.getdata().show();


va.getdata().show();
vb.getdata().show();
vc.getdata().show();
Session<Line<double>,double>  se(1.0,0.01,0);
se.init();
se.run(1);
va.getdata().show();
vb.getdata().show();
vc.getdata().show();
//se.test();
//vb.getdata().show();

vc.travelNodes();
vc.calculate();
vb.getdata().show();
vb.calculate();
vb.getdata().show();
vc.getdata().show();


*/
/*
*/
/*
	    int pn=21;
	    dtype pi=3.1415926;
	    dtype dx=1.0/(pn-1);
		dtype dt=pow(dx,5.0/3.0);
		dtype t=3.0;
		dtype t0=3.0;
		int index=0;
		Weno1D w1(pn,dx);
		Line<dtype> axis,ydata,zdata,tdata,theory;
		axis=axis.Linespace(pn)*dx;//*dx;
		ydata=cos(axis*2*pi);
		ydata.show();
		DataSave<dtype> ds;
		ds.writeheader(pn+1);

		//tdata=w1.weno5rd(ydata);
		//tdata.show();

		//zdata=w1.weno3rd(ydata);
		//tdata=w1.RK3Method(ydata, dt, t);
		//tdata.show();
        while(t>0)
        {
        	if(index%2==0)
        	{
                theory=cos(axis*2*pi)*cos((t0-t)*2*pi)+sin(axis*2*pi)*sin((t0-t)*2*pi);
                dtype erro=sum(pow((theory-ydata),2.0))/(pn-1);
                dtype erro1=sum(abs(theory-ydata))/(pn-1);
                ds.writeLine(index,ydata);
        		std::cout<<index<<" "<<ydata[40]<<" "<<theory[40]<<" erro "<<erro

        				<<" log2 "<<log2(erro)<<" erro 1 "<<erro1<<" log2 er1  "<<log2(erro1)<<std::endl;
        	}
        	try
        	{
        		ydata=w1.RK3Method(ydata, dt, t);
        	}
        	catch(CalulateException e)
        	{
        		std::cout<<e.what();
        	}

        	index=index+1;
        }
        */
        /*
		//tdata=w1.RK3Method(ydata, dt, t);
		//zdata.show();
		//tdata.show();

*/
	return 0;
}
