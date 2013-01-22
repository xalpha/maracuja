/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
// This file is part of maracuja, a C++ library for multispectral images       //
//                                                                             //
// Copyright (C) 2013 Alexandru Duliu, Anne-Claire Morvan                      //
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
/// \file    Spectrum.hpp
/// \class   Spectrum
///
/// \package maracuja
/// \version 0.1.0
///
/// \brief   base class for spectrum segmentation
///
/// \author  Alexandru Duliu, Anne-Claire Morvan
/// \date    Jan 15, 2013
///


#include <maracuja/Spectrum.hpp>


namespace maracuja
{

    Spectrum::Spectrum()
    {

    }


    Spectrum::~Spectrum() {
        // TODO Auto-generated destructor stub
    }


    double Spectrum::getStart()
    {
        return this->m_start;
    }

    double Spectrum::getEnd()
    {
        return this->m_end;
    }

    Eigen::VectorXd Spectrum::getData()
    {
        return this->m_data;
    }

    Eigen::VectorXd Spectrum::multiplicateSpectrum(double coeff)
    {
        Eigen::VectorXd result;
        result = coeff * this->m_data;
        return result;
    }

} // end namespace maracuja
