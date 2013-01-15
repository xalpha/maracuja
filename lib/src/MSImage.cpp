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
/// \file    MSImage.cpp
/// \class   MSImage
///
/// \package maracuja
/// \version 0.1.0
///
/// \brief   base class for image segmentation
///
/// \details this is base container for multispectral images
///
/// \author  Alexandru Duliu, Anne-Claire Morvan
/// \date    Jan 15, 2013
///


#include <maracuja/MSImage.hpp>


namespace maracuja
{

    MSImage::MSImage()
    {

    }


    MSImage::~MSImage() {
        // TODO Auto-generated destructor stub
    }

    int MSImage::getChannelsNumber()
    {
        return ( (int) (this->m_channels).size());
    }

    std::vector<Channel> MSImage::getChannels()
    {
        return this->m_channels;
    }

    Channel MSImage::getChannel(int channelIdx)
    {
        return (this->getChannels())[channelIdx];
    }

    cimg_library::CImg<uint8_t> MSImage::convolute(Spectrum spectrum)
    {
        // calculation of the multiplicative coefficient for each channel for the considered spectrum
        std::vector<double> coeffs(this->getChannelsNumber());
        for (unsigned idx = 0; idx < this->getChannelsNumber(); idx++)
        {
            double dp;
            Eigen::VectorXd spectralData = spectrum.getData();
            Eigen::VectorXd filter_i = (this->m_channels)[idx].getFilter().getData();
            coeffs[idx] = spectralData.adjoint()*(filter_i);
        }

        // multiplication of the images by the previously calculated coefficients
        cimg_library::CImg<uint8_t> resultImage;
        // the next line is the initialization at the good size!
        resultImage = coeffs[0]*((this->m_channels)[0].getImg());
        for (unsigned idx = 1; idx < this->getChannelsNumber(); idx++)
        {
            resultImage = resultImage + coeffs[idx]*((this->m_channels)[idx].getImg());
        }

        return resultImage;
    }


} // end namespace maracuja
