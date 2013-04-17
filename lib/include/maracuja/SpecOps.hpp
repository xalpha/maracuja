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


#pragma once

///
/// \file    SpecOps.hpp
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

#ifndef __SPECTOPS_H_INCLUDED__
#define __SPECTOPS_H_INCLUDED__

#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <maracuja/Spectrum.hpp>

namespace maracuja {

class SpecOps
{
	public:
  		
		SpecOps(const maracuja::Spectrum& spec);
		
		double interpolateLinearAt(double x);
		double interpolateCubicAt(double x);
		double areaLinear();
		double areaLinear(const maracuja::Spectrum &spec);
		
		maracuja::Spectrum getSpectrum() const;
		maracuja::Spectrum* pairwiseMultiplication(const maracuja::Spectrum&);
		maracuja::Spectrum* pairwiseMultiplication(const maracuja::Spectrum&, int normalization_type, double samplerate);
		maracuja::Spectrum* adaptTo(double new_start, double new_end, double samplerate, bool normalize, double r_area);
		maracuja::Spectrum* adaptTo(const maracuja::Spectrum&, bool normalize);
		
		void normalization_longify(double &new_start, double &new_end, const maracuja::Spectrum&);
		void normalization_direct(double &new_start, double &new_end, const maracuja::Spectrum&);
		void normalization_self(double &new_start, double &new_end);
		void normalization_bigger(double &new_start, double &new_end, const maracuja::Spectrum&);
		void normalization_smaller(double &new_start, double &new_end, const maracuja::Spectrum&);

	private:
		
		maracuja::Spectrum s;

};

}

#endif