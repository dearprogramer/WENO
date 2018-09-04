/*
 * CalulateException.cpp
 *
 *  Created on: 2018��7��14��
 *      Author: YAO
 */

#include "CalulateException.h"
#include <string>
CalulateException::CalulateException(int type) {
	// TODO Auto-generated constructor stub
	this->type=type;

}
;
CalulateException::~CalulateException()throw() {
	// TODO Auto-generated destructor stub
};
const char* CalulateException::what()
{
	std::string ts="";
	switch(this->type)
	{
	case SIZE_DIFFERENT:
	ts="the two variable have different Shape";
	break;
	case OUT_OF_BOUNDARY:
	ts="the index is out of boundary";
	break;
	default:
		ts="Calcultaet Erro";
	}
	return ts.c_str();
}
