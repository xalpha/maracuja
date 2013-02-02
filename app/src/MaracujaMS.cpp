////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This file is part of MaracujaMS, a C++ UI image segmentation               //
//                                                                            //
// Copyright (C) 2013 Alexandru Duliu, Anne-Claire Morvan                     //
//                                                                            //
// MaracujaMS is free software; you can redistribute it and/or                //
// modify it under the terms of the GNU  General Public License               //
// as published by the Free Software Foundation; either version 3             //
// of the License, or (at your option) any later version.                     //
//                                                                            //
// MaracujaMS is distributed in the hope that it will be useful,              //
// but WITHOUT ANY WARRANTY; without even the implied warranty of             //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              //
// GNU General Public License for more details.                               //
//                                                                            //
// You should have received a copy of the GNU General Public License          //
// along with MaracujaMS. If not, see <http://www.gnu.org/licenses/>.         //
//                                                                            //
///////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <stdexcept>
#include <cmath>

#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QProgressDialog>
#include <QStringList>
#include <QGraphicsPixmapItem>

#include <maracuja/util.hpp>
#include <maracuja/MSImage.hpp>

#include "ui_MaracujaMS.h"
#include <MaracujaMS.hpp>


MaracujaMS::MaracujaMS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MaracujaMS)
{
    ui->setupUi(this);

    connect( ui->filter_load_image, SIGNAL(clicked(bool)), this, SLOT(on_loadImage(void)) );
    connect( ui->add_channel, SIGNAL(clicked(bool)), this, SLOT(on_addChannel(void)) );
}


MaracujaMS::~MaracujaMS()
{
    delete ui;
}

void MaracujaMS::updateComboBox()
{
    ui->channel_choice->clear();
    QStringList nameList;
    for (unsigned idx = 0; idx < m_MSImages.getChannelsNumber(); idx ++)
    {
        nameList << QString(m_MSImages.getChannel(idx).getName().c_str());
    }
    const QStringList choiceList = nameList;
    ui->channel_choice->addItems(choiceList);
}


void MaracujaMS::on_loadImage()
{
    try
    {
        std::string imagePath = QFileDialog::getOpenFileName(this, "Load Image", ".", "Images (*.bmp *.png *.xpm *.jpg *.tif *.tiff)").toStdString();

        if( imagePath.size() > 0 )
        {
            // load image
//            cimg_library::CImg<uint8_t> image;
//            image.load( imagePath.c_str() );
            m_tempImage.load( imagePath.c_str() );
            unsigned writeIdx = 0;
            while (QString(m_MSImages.getChannel(writeIdx).getName().c_str()) != ui->channel_choice->currentText() && writeIdx < m_MSImages.getChannelsNumber())
            {
                writeIdx++;
            }
            m_MSImages.setImage(writeIdx, m_tempImage);

//            // convert image to Qt
//            QImage imageQt( image.width(), image.height(), QImage::Format_RGB888 );
//            for( int y=0; y<image.height(); y++ )
//            {
//                for( int x=0; x<image.width(); x++ )
//                {
//                    QColor col( image(x,y,0,0),
//                                image(x,y,0,1),
//                                image(x,y,0,2) );
//                    imageQt.setPixel( x, y, col.rgb() );
//                }
//            }

//            // set the images
//            ui->view->setAxisBackground(QPixmap::fromImage(imageQt), true, Qt::IgnoreAspectRatio );
//            ui->view->xAxis->setRange(0, imageQt.width() );
//            ui->view->yAxis->setRange(0, imageQt.height() );
//            ui->view->replot();
        }

    }
    catch( std::exception &e )
    {
        ui->statusBar->showMessage( QString( e.what() ), 5000 );
        std::cerr << e.what() << std::endl;
        QMessageBox::critical(this, "Error", QString( e.what() ) );
    }
}


void MaracujaMS::on_addChannel()
{
    try
    {
        std::string filterName = ui->filter_name->text().toStdString();
        int filterId = ui->filter_id->value();
        double startVal = ui->filter_begin->value();
        double endVal = ui->filter_end->value();

        // extraction of the values of the filter
        std::vector<double> filterValues(0);
        std::stringstream ssf;
        std::string filt = ui->filter_values->text().toStdString();
        ssf << filt;
        ssf.seekg(std::ios::beg);
        double temp;
        while (!ssf.eof())
        {
            ssf >> temp;
            filterValues.push_back(temp);
        }
        maracuja::Spectrum filterSpectrum;
        unsigned values_nb = (unsigned) filterValues.size();
        Eigen::VectorXd filter(values_nb);
        for (unsigned writeIdx = 0; writeIdx < values_nb; writeIdx++)
        {
            filter(writeIdx) = filterValues[writeIdx];
        }
        filterSpectrum.setValues(startVal, endVal, filter);

        // extraction of the values of the sensitivity
        std::vector<double> sensitValues(0);
        std::stringstream sss;
        std::string sensit = ui->filter_values->text().toStdString();
        sss << sensit;
        sss.seekg(std::ios::beg);
        while (!sss.eof())
        {
            sss >> temp;
            sensitValues.push_back(temp);
        }
        maracuja::Spectrum sensitSpectrum;
        values_nb = (unsigned) sensitValues.size();
        Eigen::VectorXd sensitivity(values_nb);
        for (unsigned writeIdx = 0; writeIdx < values_nb; writeIdx++)
        {
            sensitivity(writeIdx) = sensitValues[writeIdx];
        }
        sensitSpectrum.setValues(startVal, endVal, sensitivity);

        // add the channel to the m_MSImages
        maracuja::Channel tempChannel;
        tempChannel.setValues(filterId, filterSpectrum, sensitSpectrum, filterName);
        this->m_MSImages.addChannel(tempChannel);

        this->updateComboBox();

    }
    catch( std::exception &e )
    {
        ui->statusBar->showMessage( QString( e.what() ), 5000 );
        std::cerr << e.what() << std::endl;
        QMessageBox::critical(this, "Error", QString( e.what() ) );
    }
}
