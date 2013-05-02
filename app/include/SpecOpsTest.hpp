////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This file is part of MaracujaMS, a C++ UI image segmentation               //
//                                                                            //
// Copyright (C) 2013 Alexandru Duliu, Anne-Claire Morvan, Christoph Baur     //
//                                                                            //
// MaracujaMS is free software; you can redistribute it and/or                //
// modify it under the terms of the GNU  General Public License               //
// as published by the Free Software Foundation; either version 3             //
// of the License, or (at your option) any later version.                     //
//                                                                            //
// MaracujaMS is distributed in the hope that it will be useful,              //
// but WITHOUT ANY WARRANTY; without even the implied warranty of             //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              //
// GNU General Public License for more details.                               //
//                                                                            //
// You should have received a copy of the GNU General Public License          //
// along with MaracujaMS. If not, see <http://www.gnu.org/licenses/>.         //
//                                                                            //
///////////////////////////////////////////////////////////////////////////////

#ifndef __SPECOPSTEST_H_INCLUDED__
#define __SPECOPSTEST_H_INCLUDED__

#include <maracuja/Spectrum.hpp>
#include <maracuja/SpecOps.hpp>
#include <Eigen/Core>
#include <Eigen/Geometry>

class SpecOpsTest
{
	public:
  		
		SpecOpsTest();
		
		void OnesOnly(maracuja::Spectrum<double> &a, maracuja::Spectrum<double>  &b);
		void RandomARandomBEqualSize(maracuja::Spectrum<double>  &a, maracuja::Spectrum<double>  &b);
		void RandomARandomBDifferentSize(maracuja::Spectrum<double>  &a, maracuja::Spectrum<double>  &b);
		void emptyARandomB(maracuja::Spectrum<double>  &a, maracuja::Spectrum<double>  &b);
		void emptyBRandomA(maracuja::Spectrum<double>  &a, maracuja::Spectrum<double>  &b);
		
	protected:
		
		double get_random(double, double);

};

#endif