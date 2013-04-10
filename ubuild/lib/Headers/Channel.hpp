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


#pragma once

///
/// \file    Channel.hpp
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


#include <memory>

#include <maracuja/util.hpp>
#include <maracuja/Spectrum.hpp>

namespace maracuja
{

class Channel
{
public:
    Channel();
    Channel( const Channel& ch );
    Channel( int id, const std::string& name,
             const Spectrum& filter, const Spectrum& sensor,
             std::shared_ptr< cimg_library::CImg<uint8_t> > image );

    virtual ~Channel();

    void operator =( const Channel& ch );

    int id() const;
    const std::string& name() const;
    const Spectrum& filter() const;
    const Spectrum& sensor() const;
    const cimg_library::CImg<uint8_t>& img() const;
    //cimg_library::CImg<uint8_t>& img();
    void set(double id, const Spectrum& filter, const Spectrum& sensor, const std::string& name);
    void set(std::shared_ptr<cimg_library::CImg<uint8_t> > image);

    double lossCalculation();
    cimg_library::CImg<uint8_t> lossCompensation(double compensationCoeff);

    void check() const;

protected:
    bool m_isConfigured;
    bool m_hasImage;

    int m_id; /// channel id
    std::string m_name; /// channel name
    Spectrum m_filter; /// trasmission spectra of the filter
    Spectrum m_sensor; /// sensitivity spectra of the sensor
    std::shared_ptr< cimg_library::CImg<uint8_t> > m_image;

};

} // end namespace maracuja
