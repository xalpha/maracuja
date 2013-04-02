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

#pragma once

#include <cstdint>
#include <memory>


#include <QDialog>
#include <QMainWindow>

#include <maracuja/util.hpp>
#include <maracuja/MSImage.hpp>
#include <SSM.hpp>

namespace Ui {
    class MaracujaMS;
}


class MaracujaMS : public QMainWindow
{
    Q_OBJECT

public:
    explicit MaracujaMS(QWidget *parent = 0);
    ~MaracujaMS();
    void updateComboBox();

public slots:
    void on_addChannel();
    void on_addDefaultChannels();
    void on_loadImage();
    void on_showImage();
    void on_calculation();
    void on_saveRGB();
    void on_loadMS();
    void on_saveMS();
	void on_load_spectrum1();
	void on_load_spectrum2();
	void on_show_spectrum1();
	void on_show_spectrum2();
	void on_multiply_spectra();

protected:
    void cimg2qimg( const cimg_library::CImg<uint8_t>& src, QImage& dst );
	void on_load_spectrum(maracuja::Spectrum& spec);
	void on_show_spectrum(maracuja::Spectrum& spec, int graph);

protected:
    // ui
    Ui::MaracujaMS *ui;

    // data
    std::string m_lastDir;
    maracuja::MSImage m_MSImage;
    cimg_library::CImg<uint8_t> m_imageRGB;
	maracuja::Spectrum a;
	maracuja::Spectrum b;

};

