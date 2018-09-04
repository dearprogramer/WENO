/*
 * LineOp.h
 *
 *  Created on: 2018��7��22��
 *      Author: YAO
 */

#ifndef LINEOP_H_
#define LINEOP_H_
#include<cmath>
#include "Line.h"
using namespace std;
template<class Type>
Line<Type> & sin(Line<Type> & n)
{
	return n.operation(std::sin);
}
template<class Type>
Line<Type> & cos(Line<Type> & n)
{
	return n.operation(std::cos);
}

template<class Type>
Line<Type> & tan(Line<Type> & n)
{
	return n.operation(std::tan);
}
template<class Type>
Line<Type> & log(Line<Type> & n)
{
	return n.operation(std::log);
}
template<class Type>
Line<Type> & exp(Line<Type> & n)
{
	return n.operation(std::exp);
}
template<class Type>
Line<Type> & pow(Line<Type> & n,Type parameter)
{
	return n.operation(std::pow,parameter);
}
template<class Type>
Line<Type> & sqrt(Line<Type> & n)
{
	return n.operation(std::sqrt);
}

template<class Type>
Line<Type> & abs(Line<Type> & n)
{
	return n.operation(std::abs);
}
template<class Type>
Line<Type> & sinh(Line<Type> & n)
{
	return n.operation(std::sinh);
}
template<class Type>
Line<Type> & atan(Line<Type> & n)
{
	return n.operation(std::atan);
}
template<class Type>
Line<Type> & asin(Line<Type> & n)
{
	return n.operation(std::asin);
}
template<class Type>
Type sum(Line<Type> & n)
{
	return n.getsum();
}
#endif /* LINEOP_H_ */
