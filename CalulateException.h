/*
 * CalulateException.h
 *
 *  Created on: 2018��7��14��
 *      Author: YAO
 */

#ifndef CALULATEEXCEPTION_H_
#define CALULATEEXCEPTION_H_

#include <exception>

class CalulateException: public std::exception {
private :
	int type;
public:
	static const int SIZE_DIFFERENT=1;
	static const int OUT_OF_BOUNDARY=2;
	CalulateException(int type);
	~CalulateException()throw();

	const char* what();
};

#endif /* CALULATEEXCEPTION_H_ */
