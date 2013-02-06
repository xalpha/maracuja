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


    Spectrum::Spectrum( const Spectrum& spec )
    {
        *this = spec;
    }


    Spectrum::Spectrum( double start, double end, const Eigen::VectorXd& data  )
    {
        m_start = start;
        m_end = end;
        m_data = data;
    }


    Spectrum::Spectrum( double start, double end, const std::vector<double>& data  )
    {
        m_start = start;
        m_end = end;
        m_data = toEigen( data );
    }


    Spectrum::~Spectrum() {
        // TODO Auto-generated destructor stub
    }

    void Spectrum::set(double startVal, double endVal, Eigen::VectorXd data)
    {
        this->m_start = startVal;
        this->m_end = endVal;
        this->m_data = data;
    }

    void Spectrum::operator =( const Spectrum& spec )
    {
        m_start = spec.m_start;
        m_end = spec.m_end;
        m_data = spec.m_data;
    }


    void Spectrum::operator *( double coeff )
    {
        m_data *= coeff;
    }


    double Spectrum::start() const
    {
        return this->m_start;
    }

    double Spectrum::end() const
    {
        return this->m_end;
    }

    const Eigen::VectorXd& Spectrum::data() const
    {
        return this->m_data;
    }

    Eigen::VectorXd Spectrum::toEigen( const std::vector<double>& vec )
    {
        Eigen::VectorXd result = Eigen::VectorXd::Zero(vec.size());
        for( size_t i=0; i<vec.size(); i++ )
            result(i) = vec[i];

        return result;
    }

} // end namespace maracuja
