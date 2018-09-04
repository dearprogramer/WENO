/*
 * baseClass.h
 *
 *  Created on: 2018Äê8ÔÂ9ÈÕ
 *      Author: YAO
 */

#ifndef BASECLASS_H_
#define BASECLASS_H_
template<class datatype>
class Calculable
{
public:
	virtual datatype& calculate(datatype &data){};
	Calculable();
	virtual ~Calculable(){};
};
template<class datatype>
Calculable<datatype>::Calculable()
{
}
template<class datatype>
class Hbase
{
public:
	Hbase(){};
	virtual void getRP(int index,datatype *origin,datatype *dp,datatype *dm,int order)
	{

	};
	virtual datatype getRM(int index,datatype p,int order)
	{
		return p;
	};
	virtual ~Hbase(){};
	virtual void update(){};
};
#endif /* BASECLASS_H_ */
