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

#include <QtGui/QApplication>
#include <MaracujaMS.hpp>

#include <omp.h>
#include <iostream>


int main(int argc, char *argv[])
{
//#ifdef OMP_H
//    std::cout << "omp_get_max_threads: " << omp_get_max_threads() << std::endl;
//    omp_set_num_threads( omp_get_max_threads() / 2 );
//    std::cout << "omp_get_num_threads: " << omp_get_max_threads() << std::endl;
//#endif




    QApplication a(argc, argv);
    MaracujaMS w;
    w.show();

    return a.exec();
}
