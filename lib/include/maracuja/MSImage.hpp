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
/// \file    MSImage.hpp
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


#include <maracuja/util.hpp>
#include <maracuja/Spectrum.hpp>
#include <maracuja/Channel.hpp>
#include <maracuja/SpecOps.hpp>

#include <tinyxml2.h>


namespace maracuja
{

    class MSImage
    {
        public:
            MSImage( size_t channels=0 );
            MSImage( const MSImage& msi );
            virtual ~MSImage();

            void operator =( const MSImage& msi );

            void clear();
            void addChannel( const Channel& channel);
            void setImage(unsigned channelIdx, std::shared_ptr<cimg_library::CImg<uint8_t> > imageToAdd);
            void setTimestamp( const std::string& timestamp );

            const std::vector<Channel>& channels() const;
            std::vector<Channel>& channels();
            const std::string& timestamp() const;

            std::vector<double> computeCoefficients(const Spectrum &spectrum);
            std::vector<std::vector<double> > computeBalancedCoefficients(const std::vector<maracuja::Spectrum> &spectrums);

            cimg_library::CImg<uint8_t> convolute( const Spectrum& spectrum);
            cimg_library::CImg<double> convolute_double( const Spectrum& spectrum);
            cimg_library::CImg<uint8_t> convolute( const std::vector<maracuja::Spectrum>& spectra, bool balanced=false );

            cimg_library::CImg<uint8_t> rgb( bool whitebalance=true );

            void load( const std::string& filename );
            void save( const std::string& filename );

    protected:
            void checkChannels();

            std::string getElementValue( tinyxml2::XMLNode* node, std::string name );
            void appendTextElement( tinyxml2::XMLDocument& doc, tinyxml2::XMLNode& node, std::string name, std::string val );

        protected:
            std::vector<Channel> m_channels;
            std::string m_timestamp;
    };

} // end namespace maracuja
