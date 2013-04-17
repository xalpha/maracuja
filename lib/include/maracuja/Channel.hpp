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

template <typename T, typename Ti>
class Channel
{
public:
    typedef cimg_library::CImg<Ti> Image;

public:
    Channel();
    Channel( const Channel& ch );
    Channel( int id, const std::string& name,
             const Spectrum<T>& filter, const Spectrum<T>& sensor,
             std::shared_ptr<Image> image );

    virtual ~Channel();

    void operator =( const Channel& ch );

    int id() const;
    const std::string& name() const;
    const Spectrum<T>& filter() const;
    const Spectrum<T>& sensor() const;
    const Image& image() const;
    void set(double id, const Spectrum<T>& filter, const Spectrum<T>& sensor, const std::string& name);
    void set(std::shared_ptr<Image> image);

    T lossCalculation();
    Image lossCompensation(T compensationCoeff);

    void check() const;

protected:
    bool m_isConfigured;
    bool m_hasImage;

    int m_id; /// channel id
    std::string m_name; /// channel name
    Spectrum<T> m_filter; /// trasmission spectra of the filter
    Spectrum<T> m_sensor; /// sensitivity spectra of the sensor
    std::shared_ptr<Image> m_image;

};


/////
// Implementation
///

template <typename T, typename Ti>
inline Channel<T,Ti>::Channel() :
    m_isConfigured(false),
    m_hasImage(false),
    m_image( new Image() )
{

}


template <typename T, typename Ti>
inline Channel<T,Ti>::Channel( const Channel& ch )
{
    *this = ch;
}


template <typename T, typename Ti>
inline Channel<T,Ti>::Channel( int id, const std::string& name,
                               const Spectrum<T>& filter, const Spectrum<T>& sensor,
                               std::shared_ptr<Channel<T,Ti>::Image> image )
{
    set( id, filter, sensor, name );
    set( image );
}


template <typename T, typename Ti>
inline Channel<T,Ti>::~Channel() {
    // TODO Auto-generated destructor stub
}


template <typename T, typename Ti>
inline void Channel<T,Ti>::operator =( const Channel& ch )
{
    m_id = ch.m_id;
    m_name = ch.m_name;
    m_filter = ch.m_filter;
    m_sensor = ch.m_sensor;
    m_image = ch.m_image;
    m_isConfigured = ch.m_isConfigured;
    m_hasImage = ch.m_hasImage;
}


template <typename T, typename Ti>
inline int Channel<T,Ti>::id() const
{
    return m_id;
}


template <typename T, typename Ti>
inline const std::string& Channel<T,Ti>::name() const
{
    return m_name;
}


template <typename T, typename Ti>
inline const Spectrum<T>& Channel<T,Ti>::filter() const
{
    return m_filter;
}


template <typename T, typename Ti>
inline const Spectrum<T>& Channel<T,Ti>::sensor() const
{
    return m_sensor;
}


template <typename T, typename Ti>
inline const typename Channel<T,Ti>::Image& Channel<T,Ti>::image() const
{
    return *m_image;
}


template <typename T, typename Ti>
inline void Channel<T,Ti>::set(double id, const Spectrum<T>& filter, const Spectrum<T>& sensor, const std::string& name)
{
    m_id = id;
    m_filter = filter;
    m_sensor = sensor;
    m_name = name;
    m_isConfigured = true;
}


template <typename T, typename Ti>
inline void Channel<T,Ti>::set(std::shared_ptr<Channel<T,Ti>::Image> image)
{
    m_image = image;
    m_hasImage = true;
}

template <typename T, typename Ti>
inline T Channel<T,Ti>::lossCalculation()
{
    // this function returns a multiplicative coefficient,
    // which compensate the loss due to the filter
    // and the loss due to the sensitivity

    T coeff = 1; // out put of the function

    // compensation of the loss, which comes from the filter's use
    T max = m_filter.data().maxCoeff();
    if (max != 0)
    {
        coeff = coeff/max;
    }

    // compensation of the loss, which comes from the camera sensitivity
    T coeff_tmp = m_filter.data().adjoint()*(m_sensor.data());
    if (coeff_tmp != 0)
    {
        T sum_filter = m_filter.data().sum();
        coeff_tmp = sum_filter/coeff_tmp;
    } // coeff_tmp = sum(filter's values) / dot product(filter's values and sensitivity's values)

    coeff = coeff * coeff_tmp;
    return coeff;
}


template <typename T, typename Ti>
inline typename Channel<T,Ti>::Image Channel<T,Ti>::lossCompensation(T compensationCoeff)
{
    Image compensatedImg;
    compensatedImg = compensationCoeff * (*m_image);
    return compensatedImg;
    //m_image *= compensationCoeff;
}


template <typename T, typename Ti>
inline void Channel<T,Ti>::check() const
{
    if( !m_isConfigured )
        throw std::runtime_error("Channel<T,Ti>::check: channel \"" + m_name + "\" is not configured.");
    if( !m_hasImage )
        throw std::runtime_error("Channel<T,Ti>::check: channel \"" + m_name + "\" has no image.");
}


} // end namespace maracuja
