/*
 * test.h
 *
 *  Created on: 08.05.2018
 *      Author: root
 */

#ifndef EXAMPLES_LWM2M_PORT_TEST_H_
#define EXAMPLES_LWM2M_PORT_TEST_H_

#include <iostream>
//#include "mbed-client/m2mobject.h"
//#include "mbed-client/m2mobjectinstance.h"
//#include "mbed-client/m2minterfacefactory.h"
//#include "mbed-client/m2mdevice.h"
#include "test2.h"

class TestClass {

public:
	int a;


	TestClass(int a){
		this->a = a;


	}

	void printSmTHg(){

		//M2MDevice *d = M2MInterfaceFactory::create_device();
		test2 d(9999);
		std::cout << "HALLO das ist D.RES.COUNT = ";
		d.printA();
		std::cout << std::endl;
	}

};


#endif /* EXAMPLES_LWM2M_PORT_TEST_H_ */
