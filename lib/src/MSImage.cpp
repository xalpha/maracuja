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

    void MSImage::setImage(unsigned channelIdx, std::shared_ptr<cimg_library::CImg<uint8_t> > imageToAdd)
    {
        this->m_channels[channelIdx].setImage(imageToAdd);
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
//        resultImage = coeffs[0]*((this->m_channels)[0].getImg());
//        for (unsigned idx = 1; idx < this->getChannelsNumber(); idx++)
//        {
//            resultImage = resultImage + coeffs[idx]*((this->m_channels)[idx].getImg());
//        }

        return resultImage;
    }

    std::vector<std::vector<double> > MSImage::initialization(std::vector<Spectrum> spectrums)
    {
        std::vector<std::vector<double> > allCoeffs(spectrums.size());
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

    cimg_library::CImg<uint8_t> MSImage::imageReconstruction(std::vector<std::vector<double> > reconstructionCoeffs, unsigned channelIdx)
    {
        if (channelIdx < reconstructionCoeffs.size())
        {
            cimg_library::CImg<uint8_t> resultImage;
//            // the next line is the initialization at the good size!
//            resultImage = reconstructionCoeffs[channelIdx][0]*((this->m_channels)[0].getImg());
//            for (unsigned idx = 1; idx < this->getChannelsNumber(); idx++)
//            {
//                resultImage = resultImage + reconstructionCoeffs[channelIdx][idx]*((this->m_channels)[idx].getImg());
//            }

            return resultImage;
        }
    }


    void MSImage::load( const std::string& filename )
    {
        // load the document
        tinyxml2::XMLDocument doc;
        int loadStatus = doc.LoadFile( filename.c_str() );
        if( tinyxml2::XML_SUCCESS != loadStatus )
            throw std::runtime_error( "MSImage::load: " + std::string( doc.GetErrorStr1() ) );

        // get the root
        tinyxml2::XMLNode* root = doc.FirstChildElement( "MultispectralImage" );
        if( root == 0 )
            throw std::runtime_error( "MSImage::load: root node not found." );

        // get the channels
        tinyxml2::XMLNode* channels = root->FirstChildElement( "Channels" );
        if( channels == 0 )
            throw std::runtime_error( "MSImage::load: no channels." );

        // run over all the channels
        m_channels.clear();
        for( tinyxml2::XMLNode* chPtr=channels->FirstChildElement( "Channel" ); chPtr != 0; chPtr = chPtr->NextSiblingElement( "Channel" ) )
        {
            Channel ch;
            int id;
            std::string name, imageFilename;
            double fs, fe, ss, se;
            std::vector<double> fd, sd;

            // get channel id & name
            str2scalar( getElementValue( chPtr, "Id" ), id);
            name = getElementValue( chPtr, "Name" );

            // get channel filter
            tinyxml2::XMLNode* filterNode = chPtr->FirstChildElement( "Filter" );
            str2scalar( getElementValue( filterNode, "Start" ), fs);
            str2scalar( getElementValue( filterNode, "End" ), fe );
            str2vector( getElementValue( filterNode, "Data" ), fd );
            Spectrum filter( fs, fe, fd );

            // get channel sensor
            tinyxml2::XMLNode* sensorNode = chPtr->FirstChildElement( "Sensor" );
            str2scalar( getElementValue( sensorNode, "Start" ), ss);
            str2scalar( getElementValue( sensorNode, "End" ), se );
            str2vector( getElementValue( sensorNode, "Data" ), sd );
            Spectrum sensor( ss, se, sd );

            // get the image
            imageFilename = getElementValue( chPtr, "Image" );
            std::shared_ptr< cimg_library::CImg<uint8_t> > image( new cimg_library::CImg<uint8_t>() );
            image->load( imageFilename.c_str() );

            // add the image
            m_channels.push_back( Channel( id, name, filter, sensor, image ) );
        }
    }


    void MSImage::save( const std::string& filename )
    {
        // init stuff
        tinyxml2::XMLDocument doc;
        std::string baseFilename = filename.substr( 0, filename.find_last_of('.') );

        // add root
        tinyxml2::XMLNode* root = doc.InsertEndChild( doc.NewElement( "MultispectralImage" ) );

        // run over the channels
        tinyxml2::XMLNode* channels = root->InsertEndChild( doc.NewElement( "Channels" ) );
        for( size_t i=0; i<m_channels.size(); i++ )
        {
            // init channel
            tinyxml2::XMLNode* channel = channels->InsertEndChild( doc.NewElement( "Channel" ) );

            // add channel id & name
            appendTextElement( doc, *channel, std::string("Id"), toString(m_channels[i].getId() ) );
            appendTextElement( doc, *channel, std::string("Name"), m_channels[i].getName() );

            // add the filter
            tinyxml2::XMLNode* filter = channel->InsertEndChild( doc.NewElement( "Filter" ) );
            appendTextElement( doc, *filter, std::string("Start"), toString( m_channels[i].getFilter().getStart() ) );
            appendTextElement( doc, *filter, std::string("End"), toString( m_channels[i].getFilter().getEnd() ) );
            appendTextElement( doc, *filter, std::string("Data"), toString( m_channels[i].getFilter().getData() ) );

            // add the sensor
            tinyxml2::XMLNode* sensor = channel->InsertEndChild( doc.NewElement( "Sensor" ) );
            appendTextElement( doc, *sensor, std::string("Start"), toString( m_channels[i].getSensor().getStart() ) );
            appendTextElement( doc, *sensor, std::string("End"), toString( m_channels[i].getSensor().getEnd() ) );
            appendTextElement( doc, *sensor, std::string("Data"), toString( m_channels[i].getSensor().getData() ) );

            // save the image
            std::string channelFilename = baseFilename + "-" + toString(m_channels[i].getId()) + ".png";
            m_channels[i].getImg()->save( channelFilename.c_str() );
        }

        // wrap up
        doc.SaveFile( filename.c_str() );
    }


    std::string MSImage::getElementValue( tinyxml2::XMLNode* node, std::string name )
    {
        tinyxml2::XMLNode* childTag = node->FirstChildElement( name.c_str() );
        if( childTag != 0 )
        {
            tinyxml2::XMLNode* childText = childTag->FirstChild();
            if( childText != 0 )
                return std::string( childText->Value() );
        }
        return std::string();
    }


    void MSImage::appendTextElement( tinyxml2::XMLDocument& doc,
                                     tinyxml2::XMLNode& node,
                                     std::string name,
                                     std::string val )
    {
        tinyxml2::XMLNode* tmp = node.InsertEndChild( doc.NewElement( name.c_str() ) );
        tmp->InsertEndChild( doc.NewText( val.c_str() ));
    }

} // end namespace maracuja
