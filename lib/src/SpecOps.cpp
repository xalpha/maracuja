/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
// This file is part of maracuja, a C++ library for multispectral images       //
//                                                                             //
// Copyright (C) 2013 Alexandru Duliu, Anne-Claire Morvan, Christoph Baur      //
//                                                                             //
// maracuja is free software; you can redistribute it and/or                   //
// modify it under the terms of the GNU Lesser General Public                  //
// License as published by the Free Software Foundation; either                //
// version 3 of the License, or (at your option) any later version.            //
//                                                                             //
// maracuja is distributed in the hope that it will be useful, but WITHOUT ANY //
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS   //
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or the  //
// GNU General Public License for more details.                                //
//                                                                             //
// You should have received a copy of the GNU Lesser General Public            //
// License along with maracuja. If not, see <http://www.gnu.org/licenses/>.    //
//                                                                             //
////////////////////////////////////////////////////////////////////////////////

///
/// \file    SpecOps.cpp
/// \class   SpecOps
///
/// \package maracuja
/// \version 0.1.0
///
/// \brief   base class for spectrum operations
///
/// \details this is the class providing operations on spectrums of type Spectrum such as multiplication, interpolation and normalization
///
/// \author  Christoph Baur
/// \date    April 09, 2013
///

#include <stdlib.h>
#include <cmath>
#include <maracuja/SpecOps.hpp>

namespace maracuja
{

SpecOps::SpecOps(const maracuja::Spectrum& spec) {
	this->s.set(spec.start(), spec.end(), spec.data(), spec.samplerate());
	//*this = spec;
}

maracuja::Spectrum* SpecOps::pairwiseMultiplication(const maracuja::Spectrum& spec) {
	return this->pairwiseMultiplication(spec, 1, spec.samplerate());
}

/** Multiplies two spectras pairwise and returns a new spectrum. Spectras of different sizes need to be normalized
 *  (1) Merge the dimension of both spectrum vectors and get the maximum size of both spectra combined
 *  (2) Use the dimension of spectrum a
 *  (3) Use the dimension of spectrum b
 *  (4) Use the bigger one of both
 *  (5) Use the smaller one of both
 *  In any case, the vectors of both spectra contain interpolation values
 */
maracuja::Spectrum* SpecOps::pairwiseMultiplication(const maracuja::Spectrum& spec, int normalization_type, double samplerate) {
	maracuja::Spectrum* result = new maracuja::Spectrum();
	Eigen::VectorXd a,b;
	SpecOps fac = SpecOps(spec);
	double new_start, new_end;
	
	//normalize spec and this
	// -> take start and end of both spectra and compare them
	// -> return new start and end for resulting spectra
	if (normalization_type == 1) {
		this->normalization_longify(new_start, new_end, spec);
	} else if (normalization_type == 2) {
		this->normalization_self(new_start, new_end);
	} else	if (normalization_type == 3) {
		this->normalization_direct(new_start, new_end, spec);
	} else	if (normalization_type == 4) {
		this->normalization_bigger(new_start, new_end, spec);
	} else	if (normalization_type == 5) {
		this->normalization_smaller(new_start, new_end, spec);
	} else {
		this->normalization_longify(new_start, new_end, spec);
	}
	
	std::cout << "New Start: " << new_start << " New End: " << new_end << std::endl;
 	
	int size = (int) (new_end - new_start)/samplerate + 1;
	a = Eigen::VectorXd::Zero(size);
	b = Eigen::VectorXd::Zero(size);
	
	for (int i=0; i<size; i++) {
		a[i] = this->interpolateLinearAt(new_start + i*samplerate);
		//std::cout << "pairwiseMultiplication - interpolation for spectrum a at x=" << new_start + i*samplerate << ": " << a[i] << std::endl;
		b[i] = fac.interpolateLinearAt(new_start + i*samplerate);
		//std::cout << "pairwiseMultiplication - interpolation for spectrum b at x=" << new_start + i*samplerate << ": " << b[i] << std::endl;
	}
	
	//multiply previously created vectors pairwise
	//yep, this loop can be shrinked to only one, but performance is not a hassle right now
	Eigen::VectorXd resulting_vector = Eigen::VectorXd::Zero(size);
	for (int i=0; i<size; i++) {
		resulting_vector[i] = a[i]*b[i];
	}
	
	result->set(new_start, new_end, resulting_vector, samplerate);
	
	return result;
}


maracuja::Spectrum* SpecOps::adaptTo(double new_start, double new_end, double samplerate, bool normalize) {
	maracuja::Spectrum* result = new maracuja::Spectrum();
	
	int size = (int) (new_end - new_start)/samplerate + 1;
	Eigen::VectorXd data = Eigen::VectorXd::Zero(size);
	
	double peak = 0.0;
	for (int i=0; i<size; i++) {
		data[i] = this->interpolateLinearAt(new_start + i*samplerate);
		if (data[i] > peak) {
			peak = data[i];
		}
	}
	
	if (normalize) {
		for (int i=0; i<size; i++) {
			data[i] = data[i] / peak;
		}
	}
	
	result->set(new_start, new_end, data, samplerate);
	return result;
}


maracuja::Spectrum* SpecOps::adaptTo(const maracuja::Spectrum &spec, bool normalize) {
	double samplerate = fabs(spec.end() - spec.start())/(spec.data().size() - 1);
	this->adaptTo(spec.start(), spec.end(), samplerate, normalize);
}


double SpecOps::interpolateLinearAt(double x) {
	if (x < this->s.start() || x > this->s.end()) {
		return 0.0;
	}
	
	/* Find index of surrounding discretized values
	 * by this: val = (x - start)/samplerate
	 * -> floor(val) -> index of lower discrete value
	 * -> ceil(val) -> index of higher discrete value */
	double d_index = (x - this->s.start())/this->s.samplerate();
	double l_index = floor(d_index);
	double r_index = ceil(d_index);
	
	Eigen::VectorXd data = this->s.data();
	/* Catching edge cases */
	if (data.size() < 1) {
	    return 0.0;
	}
	if (data.size() < 2) {
		return data[0];
	}
	if (this->s.end() == this->s.start()) {
	    return data[0];    
	}
	if (this->s.samplerate() == 0){
       return data[0];	
	}
	if (l_index > (data.size() - 1)) {
        l_index = data.size() - 2;
	}
	if (r_index > (data.size() - 1)) {
		r_index = data.size() - 1;
	}
	if (l_index < 0) {
		l_index = 0;
	}
	if (r_index < 0) {
		r_index = 0;
	}
	
	//Debug prints
	/*std::cout << "Samplerate: " << this->s.samplerate() << std::endl;
	std::cout << "Lower Index: " << l_index << std::endl;
	std::cout << "Upper Index: " << r_index << std::endl;
	std::cout << "Amount of Values: " << data.size() << std::endl;*/
	
	double gradient = (data[(int)r_index] - data[(int)l_index]) / (this->s.samplerate());
 	
	return data[(int)l_index] + (d_index - l_index)*gradient;
}


double SpecOps::interpolateCubicAt(double x) {
	if (x < this->s.start() || x > this->s.end()) {
		return 0.0;
	}
	if (this->s.data().size() < 4) {
		//fallback to linear interpolation
		return this->interpolateLinearAt(x);
	}
	double index[] = {0.0, 0.0, 0.0, 0.0};
	double a0, a1, a2, a3;
	
	//Todo: Find indexes of four discrete values surrounding x
	double d_index = (x - this->s.start())/this->s.samplerate();
	double l_index = floor(d_index);
	double r_index = ceil(d_index);
	if (l_index >= 1) {//location is fine
		index[0] = l_index - this->s.samplerate();
		index[1] = l_index;
		index[2] = l_index + this->s.samplerate();
		index[3] = l_index + this->s.samplerate() * 2;
	} else {//we have to look further right for appropriate discrete values
		index[0] = l_index;
		index[1] = l_index + this->s.samplerate();
		index[2] = l_index + this->s.samplerate() * 2;
		index[3] = l_index + this->s.samplerate() * 3;
	}

	a0 = index[3] - index[2] - index[0] + index[1];
	a1 = index[0] - index[1] - index[0];
	a2 = index[2] - index[0];
	a3 = index[1];

	return(a0*(x*x*x) + a1*(x*x) + a2*x + a3);
}

maracuja::Spectrum SpecOps::getSpectrum() const {
	return this->s;
}

void SpecOps::normalization_longify(double &new_start, double &new_end, const maracuja::Spectrum &b) {
	//calculate the sizes of both spectra and create a mergesize
	if (this->s.end() > b.end()) {
		new_end = this->s.end();
	} else {
		new_end = b.end();
	}
	
	if (this->s.start() < b.start()) {
		new_start = this->s.start();
	} else {
		new_start = b.start();
	}
	
}

void SpecOps::normalization_direct(double &new_start, double &new_end, const maracuja::Spectrum &b) {
	new_end = b.end();
	new_start = b.start();
}

void SpecOps::normalization_self(double &new_start, double &new_end) {
	new_end = this->s.end();
	new_start = this->s.start();
}

void SpecOps::normalization_bigger(double &new_start, double &new_end, const maracuja::Spectrum &b) {
	if (abs(this->s.end() - this->s.start()) > abs(b.end() - b.start())) {
		new_end = this->s.end();
		new_start = this->s.start();
	} else {
		new_end = b.end();
		new_start = b.start();
	}
	
}

void SpecOps::normalization_smaller(double &new_start, double &new_end, const maracuja::Spectrum &b) {
	if (abs(this->s.end() - this->s.start()) < abs(b.end() - b.start())) {
		new_end = this->s.end();
		new_start = this->s.start();
	} else {
		new_end = b.end();
		new_start = b.start();
	}
	
}

}
