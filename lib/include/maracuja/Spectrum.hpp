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

class Spectrum
{
public:
    Spectrum();
    Spectrum( const Spectrum& spec );
    Spectrum( double start, double end, const Eigen::VectorXd& data  );
    Spectrum( double start, double end, const std::vector<double>& data  );
	Spectrum( double start, double end, const Eigen::VectorXd& data, double samplerate  );
    Spectrum( double start, double end, const std::vector<double>& data, double samplerate  );
    virtual ~Spectrum();

    void set(double startVal, double endVal, Eigen::VectorXd data);
	void set(double startVal, double endVal, Eigen::VectorXd data, double samplerate);
	void calculateSamplerate(const Eigen::VectorXd& wldata);
	void calculateSamplerate(const std::vector<double>& wldata);

    void operator =( const Spectrum& spec );
    void operator *( double coeff );

	double samplerate() const;
    double start() const;
    double end() const;

    const Eigen::VectorXd& data() const;

protected:
    Eigen::VectorXd toEigen( const std::vector<double>& vec );

protected:
    double m_start; /// begin wavelength of the spectrum definition
    double m_end; /// begin wavelength of the spectrum definition
	  double m_sample_rate = 0.0; //NEW: distance from one sample to another in nm
    Eigen::VectorXd m_data; /// values of the function through the spectrum
};

} // end namespace maracuja
