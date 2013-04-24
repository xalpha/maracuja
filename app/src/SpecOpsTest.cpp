/*
 * Testcases for class SpecOps
 * providing evidence for the proper functioning of class SpecOps
 * all values of the spectrums are calculated randomly
 */

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <SpecOpsTest.hpp>

SpecOpsTest::SpecOpsTest() {
	//on cunstruction plant a seed for srand
	srand(time(NULL));
}

void SpecOpsTest::OnesOnly(maracuja::Spectrum &a, maracuja::Spectrum &b) {
    int span = 1000;
    double start = 199.0;
    double end = 800.0;
	
    Eigen::VectorXd vec = Eigen::VectorXd::Ones(span);
    a.set(start, end, vec, (fabs(end-start)/span) );
    b.set(start, end, vec, (fabs(end-start)/span) );
}

void SpecOpsTest::RandomARandomBEqualSize(maracuja::Spectrum &a, maracuja::Spectrum &b) {
    int span = 20;
    double start = 199.0;
    double end = 800.0;
	
    Eigen::VectorXd vec_a = Eigen::VectorXd::Zero(span);
    Eigen::VectorXd vec_b = Eigen::VectorXd::Zero(span);
    for (int i=0; i<span; i++) {
        vec_a[i] = this->get_random(0.0, 10.0);
        vec_b[i] = this->get_random(0.0, 10.0);
    }
    
    a.set(start, end, vec_a);
    b.set(start, end, vec_b);
    
};

void SpecOpsTest::RandomARandomBDifferentSize(maracuja::Spectrum &a, maracuja::Spectrum &b) {
    double start_a = 199.0;
    double end_a = 800.0;
    int span_a = (int) end_a - start_a;
    double start_b = 400.0;
    double end_b = 1000.0;
    int span_b = (int) end_b - start_b;
	
    Eigen::VectorXd vec_a = Eigen::VectorXd::Zero(span_a);
    Eigen::VectorXd vec_b = Eigen::VectorXd::Zero(span_b);
    for (int i=0; i<span_a; i++) {
        vec_a[i] = this->get_random(0.0, 10.0);
    }
    for (int i=0; i<span_b; i++) {
        vec_b[i] = this->get_random(0.0, 10.0);
    }
    
    a.set(start_a, end_a, vec_a);
    b.set(start_a, end_a, vec_b);
    
}

void SpecOpsTest::emptyARandomB(maracuja::Spectrum &a, maracuja::Spectrum &b) {
    int span = 1000;
    double start = 199.0;
    double end = 800.0;
	
    Eigen::VectorXd vec_a = Eigen::VectorXd::Zero(0);
    Eigen::VectorXd vec_b = Eigen::VectorXd::Zero(span);
    for (int i=0; i<span; i++) {
        vec_b[i] = this->get_random(0.0, 10.0);
    }
    
    a.set(0.0, 0.0, vec_a);
    b.set(start, end, vec_b);
}

void SpecOpsTest::emptyBRandomA(maracuja::Spectrum &a, maracuja::Spectrum &b) {
    
}

//little helper to get random doubles
double SpecOpsTest::get_random(double min, double max) {
    //Returns a random double between min and max
    return (max - min) * ( (double)rand() / (double)RAND_MAX ) + min;
}