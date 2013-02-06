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


    void MSImage::clear()
    {
        this->m_channels.resize(0);
    }


    void MSImage::addChannel( const Channel& channel)
    {
        this->m_channels.push_back(channel);
    }


    void MSImage::setImage(unsigned channelIdx, std::shared_ptr<cimg_library::CImg<uint8_t> > imageToAdd)
    {
        this->m_channels[channelIdx].setImage(imageToAdd);
    }


    const std::vector<Channel>& MSImage::channels() const
    {
        return this->m_channels;
    }


    std::vector<Channel>& MSImage::channels()
    {
        return this->m_channels;
    }


    std::vector<double> MSImage::computeCoefficients( const Spectrum& spectrum)
    {
        // calculation of the multiplicative coefficient for each channel for the considered spectrum
        std::vector<double> coeffs(m_channels.size());
        double compensationCoeff;
        for (unsigned idx = 0; idx < m_channels.size(); idx++)
        {
            double dp;
            Eigen::VectorXd spectralData = spectrum.data();
            Eigen::VectorXd filter_i = m_channels[idx].filter().data();
            coeffs[idx] = spectralData.adjoint()*(filter_i);
            coeffs[idx] = coeffs[idx]/filter_i.sum();
            compensationCoeff = m_channels[idx].lossCalculation();
            // compensation of the losses due to the filter and the camera sensitivity for each channel
            coeffs[idx] = coeffs[idx] * compensationCoeff;
        }

        return coeffs;
    }


    std::vector<std::vector<double> > MSImage::computeBalancedCoefficients( const std::vector<Spectrum>& spectrums)
    {
        // init the coefficients
        std::vector<std::vector<double> > allCoeffs(spectrums.size());
        for (unsigned idx = 0; idx < spectrums.size(); idx++)
            allCoeffs[idx] = computeCoefficients(spectrums[idx]);

        // white balance for a "white signal" (1 for every wavelength)

        // calculation of the theoretical value for each channel
        std::vector<double> spectralValues(m_channels.size());
        Eigen::VectorXd spectrumTmp;
        for (unsigned idx = 0; idx < m_channels.size(); idx++)
        {
            spectrumTmp = m_channels[idx].filter().data(); // filter's values
            for (unsigned wavelengthIdx = 0; wavelengthIdx < spectrumTmp.size(); wavelengthIdx++)
                spectrumTmp(wavelengthIdx) = spectrumTmp(wavelengthIdx) * m_channels[idx].sensor().data()(wavelengthIdx);
            spectralValues[idx] = spectrumTmp.sum();
        }

        std::vector<double> expected_RGB(spectrums.size());
        std::vector<double> whiteBalanceCoeffs(spectrums.size());
        std::vector<double> reconstructedRGB(spectrums.size());
        double correctionCoeff;

        for (unsigned spectrumIdx = 0; spectrumIdx < spectrums.size(); spectrumIdx++)
        {
            // calculation of the expected RGB values and the white balance coefficients
            expected_RGB[spectrumIdx] = spectrums[spectrumIdx].data().sum();
            if (expected_RGB[spectrumIdx] != 0)
                whiteBalanceCoeffs[spectrumIdx] = 255/expected_RGB[spectrumIdx];

            // calculation of the RGB values that we reconstruct with the coefficients
            for (unsigned channelIdx = 0; channelIdx < m_channels.size(); channelIdx++)
                reconstructedRGB[spectrumIdx] = reconstructedRGB[spectrumIdx] + allCoeffs[spectrumIdx][channelIdx] * spectralValues[channelIdx];

            // white balance and RGB loss compensation
            correctionCoeff = whiteBalanceCoeffs[spectrumIdx] * expected_RGB[spectrumIdx] / reconstructedRGB[spectrumIdx];
            for (unsigned channelIdx = 0; channelIdx < m_channels.size(); channelIdx++)
                allCoeffs[spectrumIdx][channelIdx] = allCoeffs[spectrumIdx][channelIdx] * correctionCoeff * spectralValues[channelIdx] / 255;
                // allCoeffs[RGBidx][channelIdx] = allCoeffs[RGBidx][channelIdx] * correctionCoeff; // if the white balance is not already done in the picture
        }

        return allCoeffs;
    }

    cimg_library::CImg<uint8_t> MSImage::convolute(const Spectrum &spectrum)
    {
        // calculation of the multiplicative coefficient for each channel for the considered spectrum
        std::vector<double> coeffs = computeCoefficients(spectrum);

        // multiplication of the images by the previously calculated coefficients
        cimg_library::CImg<uint8_t> result( m_channels[0].img().width(),
                                            m_channels[0].img().height(),
                                            1, 1, 0 );

        // reconstruct the image
        for( size_t i=0; i<m_channels.size(); i++ )
            result += coeffs[i] * m_channels[i].img();

        return result;
    }


    cimg_library::CImg<uint8_t> MSImage::convolute( const std::vector<maracuja::Spectrum>& spectra, bool balanced )
    {
        // init stuff
        cimg_library::CImg<uint8_t> result( m_channels[0].img().width(),
                                            m_channels[0].img().height(),
                                            1, spectra.size(), 0 );

        // compute coefficients and recover the image
        std::vector<std::vector<double> > coeffs;
        if( balanced )
        {
            // compute balanced coefficients
            coeffs = computeBalancedCoefficients( spectra );

            // assemble the image
            for( int c=0; c<result.spectrum(); c++ )
                for( size_t i=0; i<m_channels.size(); i++ )
                    result.get_shared_channel(c) += coeffs[c][i] * m_channels[i].img();
        }
        else
        {
            // compute coefficients
            coeffs.resize( spectra.size() );
            for( unsigned s = 0; s < spectra.size(); s++ )
                coeffs[s] = computeCoefficients( spectra[s] );

            std::vector<cimg_library::CImg<float> > channels(m_channels.size());
            for( size_t c=0; c<m_channels.size(); c++ )
                channels[c] = m_channels[c].img();

            // assemble the image
            cimg_library::CImg<float> resultF( m_channels[0].img().width(),
                                               m_channels[0].img().height(),
                                               1, spectra.size(), 0 );
            for( int c=0; c<result.spectrum(); c++ )
                for( size_t i=0; i<m_channels.size(); i++ )
                    resultF.get_shared_channel(c) += coeffs[c][i] * channels[i];

            resultF.normalize( 0, 255 );
            result = resultF;
        }

        return result;
    }


    void MSImage::load( const std::string& filename )
    {
        // load the document
        std::string directory = filename.substr( 0, filename.find_last_of('/')+1 );
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
            imageFilename = directory + imageFilename;
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
            appendTextElement( doc, *channel, std::string("Id"), toString(m_channels[i].id() ) );
            appendTextElement( doc, *channel, std::string("Name"), m_channels[i].name() );

            // add the filter
            tinyxml2::XMLNode* filter = channel->InsertEndChild( doc.NewElement( "Filter" ) );
            appendTextElement( doc, *filter, std::string("Start"), toString( m_channels[i].filter().start() ) );
            appendTextElement( doc, *filter, std::string("End"), toString( m_channels[i].filter().end() ) );
            appendTextElement( doc, *filter, std::string("Data"), toString( m_channels[i].filter().data() ) );

            // add the sensor
            tinyxml2::XMLNode* sensor = channel->InsertEndChild( doc.NewElement( "Sensor" ) );
            appendTextElement( doc, *sensor, std::string("Start"), toString( m_channels[i].sensor().start() ) );
            appendTextElement( doc, *sensor, std::string("End"), toString( m_channels[i].sensor().end() ) );
            appendTextElement( doc, *sensor, std::string("Data"), toString( m_channels[i].sensor().data() ) );

            // save the image
            std::string channelFilename = baseFilename + "-" + toString( m_channels[i].id()) + ".png";
            m_channels[i].img().save_png( channelFilename.c_str() );
            appendTextElement( doc, *channel, std::string("Image"), channelFilename.substr( channelFilename.find_last_of('/')+1, channelFilename.size()-1 ) );
        }

        // wrap up
        doc.SaveFile( (filename.substr( 0, filename.find_last_of('.') ) + ".msx").c_str() );
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
