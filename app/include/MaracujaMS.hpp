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
    void on_hide_spectrum1();
    void on_hide_spectrum2();
    void on_apply_spectrum1();
    void on_apply_spectrum2();
    void on_apply_filter();
    void on_apply_sensor();
    void on_apply_both();
    void on_toggle_filter_spectrum();
    void on_toggle_sensor_spectrum();
    void on_toggle_filter_sensor_convolution();
    
    void on_multiply_spectra();
    void on_add_dummy_spectra();

protected:
    //void cimg2qimg( const cimg_library::CImg<uint8_t>& src, QImage& dst );
    void cimg2qimg( const cimg_library::CImg<float>& src, QImage& dst );
    void on_load_spectrum(maracuja::Spectrum<double>& spec, bool& available);
    void on_show_spectrum(const maracuja::Spectrum<double>& spec, int graph);
    void on_apply_spectrum(maracuja::Spectrum<double>&);
    void on_hide_spectrum(int);

protected:
    // ui
    Ui::MaracujaMS *ui;

    // data
    std::string m_lastDir;
    maracuja::MSImage<double,float> m_MSImage;
    cimg_library::CImg<float> m_imageRGB;
    maracuja::Spectrum<double> a;
    maracuja::Spectrum<double> b;
    bool a_is_available = false;
    bool b_is_available = false;
    bool filter_on = false;
    bool sensor_on = false;
    bool filter_sensor_on = false;

};

