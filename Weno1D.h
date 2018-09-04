/*
 * Weno1D.h
 *
 *  Created on: 2018Äê7ÔÂ17ÈÕ
 *      Author: YAO
 */
#include "LineOp.h"
#include "sess.h"
#include "baseClass.h"
#ifndef WENO1D_H_
#define WENO1D_H_
typedef double dtype;
class Weno1D :public Calculable<Line<dtype>>
{
private:
	int cols;
	int order;
	int extendtype=1;
	int boudarytype=1;
	bool x_uniform;
	dtype Rmetrix_p[5][5];
	dtype Rmetrix_m[5][5];
	Line<dtype> data;
	dtype dx;
	dtype dt;
	Hbase<dtype> *hf=nullptr;
	dtype (*h_func)(dtype,dtype)=NULL;
	Line<dtype> x_axis;
	Line<dtype> half_p;
	Line<dtype> half_m;
	Line<dtype> tempr;
	Line<dtype> flux;
	Line<dtype> pt_x;
	Line<dtype> rk_1;
	Line<dtype> rk_2;
	Line<dtype> rk_f;

public:
	Weno1D(int cols,dtype dx);
	Weno1D(int cols,Line<dtype> &x_axis,dtype dt);
	Line<dtype> & weno3rd(Line<dtype> &input);
	Line<dtype> & weno5rd(Line<dtype> &input);
	void setHfunc(dtype(*func)(dtype,dtype));
	Line<dtype> &getHalf_p();
	Line<dtype> &partialX(Line<dtype> &input,int boudarytype);
	Line<dtype> &getHalf_m();
	Line<dtype> &caculate(Line<dtype> &input);
	virtual Line<dtype> &calculate(Line<dtype> &input);
	Line<dtype> &getdata();
	Line<dtype> & RK3Method(Line<dtype> &input,dtype dt,dtype &t);
	void setfunc(dtype (*func)(dtype,dtype));
	void sethclass(Hbase<dtype> *hc);
	void setboudaryconditon(int condition);
	void setextendtype(int extend);
	void getbegersRMetix(int i);
	void test();
	virtual ~Weno1D();
};


#endif /* WENO1D_H_ */
