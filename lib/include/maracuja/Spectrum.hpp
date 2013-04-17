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
    virtual ~Spectrum();

    void set(T startVal, T endVal, const VectorX& data);

    void operator =( const Spectrum& spec );
    void operator *( double coeff );

    double start() const;
    double end() const;
    const VectorX& data() const;

protected:
    VectorX toEigen( const std::vector<T>& vec );

protected:
    T m_start; /// begin wavelength of the spectrum definition
    T m_end; /// begin wavelength of the spectrum definition
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
}


template <typename T>
inline Spectrum<T>::Spectrum( T start, T end, const std::vector<T>& data  )
{
    m_start = start;
    m_end = end;
    m_data = toEigen( data );
}


template <typename T>
inline Spectrum<T>::~Spectrum()
{
    // TODO Auto-generated destructor stub
}


template <typename T>
inline void Spectrum<T>::set(T startVal, T endVal, const typename Spectrum<T>::VectorX& data)
{
    m_start = startVal;
    m_end = endVal;
    m_data = data;
}


template <typename T>
inline void Spectrum<T>::operator =( const Spectrum& spec )
{
    m_start = spec.m_start;
    m_end = spec.m_end;
    m_data = spec.m_data;
}


template <typename T>
inline void Spectrum<T>::operator *( double coeff )
{
    m_data *= coeff;
}


template <typename T>
inline double Spectrum<T>::start() const
{
    return m_start;
}


template <typename T>
inline double Spectrum<T>::end() const
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


} // end namespace maracuja
