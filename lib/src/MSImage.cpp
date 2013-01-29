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

    void MSImage::init()
    {
        this->m_channels.resize(0);
    }

    void MSImage::addChannel(Channel channel)
    {
        this->m_channels.push_back(channel);
    }

    std::vector<double> MSImage::coefficientsCalculation(Spectrum spectrum)
    {
        // calculation of the multiplicative coefficient for each channel for the considered spectrum
        std::vector<double> coeffs(this->getChannelsNumber());
        double compensationCoeff;
        for (unsigned idx = 0; idx < this->getChannelsNumber(); idx++)
        {
            double dp;
            Eigen::VectorXd spectralData = spectrum.getData();
            Eigen::VectorXd filter_i = this->getChannel(idx).getFilter().getData();
            coeffs[idx] = spectralData.adjoint()*(filter_i);
            coeffs[idx] = coeffs[idx]/filter_i.sum();
            compensationCoeff = this->getChannel(idx).lossCalculation();
            // compensation of the losses due to the filter and the camera sensitivity for each channel
            coeffs[idx] = coeffs[idx] * compensationCoeff;
        }

        return coeffs;
    }

    cimg_library::CImg<uint8_t> MSImage::convolute(Spectrum spectrum)
    {
         // calculation of the multiplicative coefficient for each channel for the considered spectrum
        std::vector<double> coeffs(0);
        coeffs = this->coefficientsCalculation(spectrum);

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

    std::vector<std::vector<double>> MSImage::initialization(std::vector<Spectrum> spectrums)
    {
        std::vector<std::vector<double>> allCoeffs(spectrums.size());
        for (unsigned idx = 0; idx < spectrums.size(); idx++)
        {
            allCoeffs[idx] = this->coefficientsCalculation(spectrums[idx]);
        }

    // white balance for a "white signal" (1 for every wavelength)

        // calculation of the theoretical value for each channel
        std::vector<double> spectralValues(this->getChannelsNumber());
        Eigen::VectorXd spectrumTmp;
        for (unsigned idx = 0; idx < this->getChannelsNumber(); idx++)
        {
            spectrumTmp = this->getChannel(idx).getFilter().getData(); // filter's values
            for (unsigned wavelengthIdx = 0; wavelengthIdx < spectrumTmp.size(); wavelengthIdx++)
            {
                spectrumTmp(wavelengthIdx) = spectrumTmp(wavelengthIdx) * this->getChannel(idx).getSensor().getData()(wavelengthIdx);
            }
            spectralValues[idx] = spectrumTmp.sum();
        }


        std::vector<double> expected_RGB(spectrums.size());
        std::vector<double> whiteBalanceCoeffs(spectrums.size());
        std::vector<double> reconstructedRGB(spectrums.size());
        double correctionCoeff;

        for (unsigned RGBidx = 0; RGBidx < spectrums.size(); RGBidx++)
        {
            // calculation of the expected RGB values and the white balance coefficients
            expected_RGB[RGBidx] = spectrums[RGBidx].getData().sum();
            if (expected_RGB[RGBidx] != 0)
            {
                whiteBalanceCoeffs[RGBidx] = 255/expected_RGB[RGBidx];
            }

            // calculation of the RGB values that we reconstruct with the coefficients
            for (unsigned channelIdx = 0; channelIdx < this->getChannelsNumber(); channelIdx++)
            {
                reconstructedRGB[RGBidx] = reconstructedRGB[RGBidx] + allCoeffs[RGBidx][channelIdx] * spectralValues[channelIdx];
            }

            // white balance and RGB loss compensation
            correctionCoeff = whiteBalanceCoeffs[RGBidx] * expected_RGB[RGBidx] / reconstructedRGB[RGBidx];
            for (unsigned channelIdx = 0; channelIdx < this->getChannelsNumber(); channelIdx++)
            {
                allCoeffs[RGBidx][channelIdx] = allCoeffs[RGBidx][channelIdx] * correctionCoeff;
            }
        }

        return allCoeffs;

    }

    cimg_library::CImg<uint8_t> MSImage::imageReconstruction(std::vector<std::vector<double>> reconstructionCoeffs, unsigned channelIdx)
    {
        if (channelIdx < reconstructionCoeffs.size())
        {
            cimg_library::CImg<uint8_t> resultImage;
            // the next line is the initialization at the good size!
            resultImage = reconstructionCoeffs[channelIdx][0]*((this->m_channels)[0].getImg());
            for (unsigned idx = 1; idx < this->getChannelsNumber(); idx++)
            {
                resultImage = resultImage + reconstructionCoeffs[channelIdx][idx]*((this->m_channels)[idx].getImg());
            }

            return resultImage;
        }
    }

} // end namespace maracuja
