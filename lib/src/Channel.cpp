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
/// \file    Channel.cpp
/// \class   Channel
///
/// \package maracuja
/// \version 0.1.0
///
/// \brief   base class for channel's characteristics memorization
///
/// \author  Alexandru Duliu, Anne-Claire Morvan
/// \date    Jan 15, 2013
///


#include <maracuja/Channel.hpp>


namespace maracuja
{

    Channel::Channel()
    {

    }


    Channel::Channel( const Channel& ch )
    {
        *this = ch;
    }


    Channel::Channel( int id, const std::string& name,
                      const Spectrum& filter, const Spectrum& sensor,
                      std::shared_ptr< cimg_library::CImg<uint8_t> > image )
    {
        m_id = id;
        m_name = name;
        m_filter = filter;
        m_sensor = sensor;
        m_image = image;
    }


    Channel::~Channel() {
        // TODO Auto-generated destructor stub
    }


    void Channel::operator =( const Channel& ch )
    {
        m_id = ch.m_id;
        m_name = ch.m_name;
        m_filter = ch.m_filter;
        m_sensor = ch.m_sensor;
        m_image = ch.m_image;
    }


    int Channel::getId()
    {
        return this->m_id;
    }

    std::string& Channel::getName()
    {
        return this->m_name;
    }

    Spectrum& Channel::getFilter()
    {
        return this->m_filter;
    }

    Spectrum& Channel::getSensor()
    {
        return this->m_sensor;
    }

    cimg_library::CImg<uint8_t>& Channel::getImg()
    {
        return *m_image;
    }

    double Channel::lossCalculation()
    {
        // this function returns a multiplicative coefficient,
        // which compensate the loss due to the filter
        // and the loss due to the sensitivity

        double coeff = 1; // out put of the function

        // compensation of the loss, which comes from the filter's use
        double max = this->m_filter.getData().maxCoeff();
        if (max != 0)
        {
            coeff = coeff/max;
        }

        // compensation of the loss, which comes from the camera sensitivity
        double coeff_tmp = this->m_filter.getData().adjoint()*(this->m_sensor.getData());
        if (coeff_tmp != 0)
        {
            double sum_filter = this->m_filter.getData().sum();
            coeff_tmp = sum_filter/coeff_tmp;
        } // coeff_tmp = sum(filter's values) / dot product(filter's values and sensitivity's values)

        coeff = coeff * coeff_tmp;
        return coeff;
    }

    cimg_library::CImg<uint8_t> Channel::lossCompensation(double compensationCoeff)
    {
        cimg_library::CImg<uint8_t> compensatedImg;
        compensatedImg = compensationCoeff * (*m_image);
        return compensatedImg;
        //this->m_image *= compensationCoeff;
    }


} // end namespace maracuja
