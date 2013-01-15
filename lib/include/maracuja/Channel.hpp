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


#include <maracuja/util.hpp>
#include <maracuja/Spectrum.hpp>

namespace maracuja
{

class Channel
{
public:
    Channel();
    virtual ~Channel();
    int getId();
    Spectrum getFilter();
    Spectrum getSensor();
    cimg_library::CImg<uint8_t> getImg();
    std::string getName();

protected:
    int m_id; /// channel id
    Spectrum m_filter; /// trasmission spectra of the filter
    Spectrum m_sensor; /// sensitivity spectra of the sensor
    cimg_library::CImg<uint8_t> m_image;
    std::string m_name; /// channel name
};

} // end namespace maracuja
