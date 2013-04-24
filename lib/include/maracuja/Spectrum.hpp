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
/// \file    Spectrum.hpp
/// \class   Spectrum
///
/// \package maracuja
/// \version 0.1.0
///
/// \brief   base class for spectrum segmentation
///
/// \details this is base container for curve values
///
/// \author  Alexandru Duliu, Anne-Claire Morvan
/// \date    Jan 15, 2013
///

#include <maracuja/util.hpp>


namespace maracuja
{

template <typename T>
class Spectrum
{
public:
    typedef Eigen::Matrix<T,Eigen::Dynamic,1> VectorX;

public:
    Spectrum();
    Spectrum( const Spectrum& spec );
    Spectrum( T start, T end, const VectorX& data  );
    Spectrum( T start, T end, const std::vector<T>& data  );
    Spectrum( T start, T end, T samplerate );
    virtual ~Spectrum();

    void operator =( const Spectrum& spec );
    void operator *( T coeff );

    T start() const;
    T end() const;
    T samplerate() const;
    const VectorX& data() const;

    void resample( T start, T end );
    void resample( T samplerate );
    void resample( T start, T end, T samplerate );
    void resample( const Spectrum<T>& spec );

protected:
    VectorX toEigen( const std::vector<T>& vec );
    T calculateSamplerate( T start, T end, size_t count );
    size_t calculateCoefficients( T start, T end, T samplerate );

protected:
    T m_start; /// begin wavelength of the spectrum definition
    T m_end; /// begin wavelength of the spectrum definition
    T m_sample_rate = 0.0; /// distance from one sample to another in nm
    VectorX m_data; /// values of the function through the spectrum
};


/////
// Implementation
///
template <typename T>
inline Spectrum<T>::Spectrum()
{
    // TODO: find something insteresting to do here
}


template <typename T>
inline Spectrum<T>::Spectrum( const Spectrum<T>& spec )
{
    *this = spec;
}


template <typename T>
inline Spectrum<T>::Spectrum( T start, T end, const Spectrum<T>::VectorX& data  )
{
    m_start = start;
    m_end = end;
    m_data = data;
    m_sample_rate = calculateSamplerate( m_start, m_end, m_data.size() );
}


template <typename T>
inline Spectrum<T>::Spectrum( T start, T end, const std::vector<T>& data  )
{
    m_start = start;
    m_end = end;
    m_data = toEigen( data );
    m_sample_rate = calculateSamplerate( m_start, m_end, m_data.size() );
}


template <typename T>
inline Spectrum<T>::~Spectrum()
{
    // TODO Auto-generated destructor stub
}


template <typename T>
inline void Spectrum<T>::operator =( const Spectrum& spec )
{
    m_start = spec.m_start;
    m_end = spec.m_end;
    m_sample_rate = spec.m_sample_rate;
    m_data = spec.m_data;
}


template <typename T>
inline void Spectrum<T>::operator *( T coeff )
{
    m_data *= coeff;
}


template <typename T>
inline T Spectrum<T>::start() const
{
    return m_start;
}


template <typename T>
inline T Spectrum<T>::end() const
{
    return m_end;
}


template <typename T>
inline const typename Spectrum<T>::VectorX& Spectrum<T>::data() const
{
    return m_data;
}


template <typename T>
inline typename Spectrum<T>::VectorX Spectrum<T>::toEigen( const std::vector<T>& vec )
{
    VectorX result = Eigen::VectorXd::Zero(vec.size());
    for( size_t i=0; i<vec.size(); i++ )
        result(i) = vec[i];

    return result;
}


template <typename T>
inline T Spectrum<T>::calculateSamplerate( T start, T end, size_t count )
{
    if( count == 0 )
        return static_cast<T>(0);
    else
        return fabs( end - start ) / static_cast<T>(count);
}


template <typename T>
inline size_t Spectrum<T>::calculateCoefficients( T start, T end, T samplerate )
{
    return static_cast<size_t>( iround( fabs(end-start) / samplerate ) );
}


template <typename T>
inline void Spectrum<T>::resample( T start, T end )
{
    // TODO
}


template <typename T>
inline void Spectrum<T>::resample( T samplerate )
{
    // get the new size of the image
    int count = static_cast<int>(static_cast<T>(m_data.size()) * (samplerate / m_sample_rate));

    // convert to CImg and resample using bicubic interpolation
    cimg_library::CImg<T> img( m_data.data(), m_data.size(), 1, 1, 1, false );
    img.resize( count, -100, -100, -100, 5 );

    // write results
    m_data = Spectrum<T>::VectorX::Zero(count);
    for( int i=0; i<count; i++ )
        m_data(i) = img.data()[i];
    m_sample_rate = samplerate;
}


template <typename T>
inline void Spectrum<T>::resample( T start, T end, T samplerate )
{
    // TODO
}


template <typename T>
inline void Spectrum<T>::resample( const Spectrum<T>& spec )
{
    resample( spec.m_start, spec.m_end, spec.m_sample_rate );
}


} // end namespace maracuja
