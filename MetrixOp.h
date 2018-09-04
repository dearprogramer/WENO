/*
 * MetrixOp.h
 *
 *  Created on: 2018��7��21��
 *      Author: YAO
 */

#ifndef METRIXOP_H_
#define METRIXOP_H_
#include "Metrix.h"
#include <cmath>
template<class Type>
Metrix<Type> & sin(Metrix<Type> &m)
{
	return m.operation(std::sin);
}
template<class Type>
Metrix<Type> & cos(Metrix<Type> &m)
{
	return m.operation(std::cos);
}
template<class Type>
Metrix<Type> & sqrt(Metrix<Type> &m)
{
	return m.operation(std::sqrt);
}
template<class Type>
Metrix<Type> & abs(Metrix<Type> &m)
{
	return m.operation(std::abs);
}
template<class Type>
Metrix<Type> & exp(Metrix<Type> &m)
{
	return m.operation(std::exp);
}
template<class Type>
Metrix<Type> & tan(Metrix<Type> &m)
{
	return m.operation(std::tan);
}

template<class Type>
Metrix<Type> & log(Metrix<Type> &m)
{
	return m.operation(std::log);
}
#endif /* METRIXOP_H_ */
