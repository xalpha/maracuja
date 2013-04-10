////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This file is part of MaracujaMS, a C++ UI image segmentation               //
//                                                                            //
// Copyright (C) 2013 Alexandru Duliu, Anne-Claire Morvan, Christoph Baur     //
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

#ifndef __SSM_H_INCLUDED__
#define __SSM_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>

class SSM
{
	public:
	   void parseFile(const std::string&);

    std::vector<double> getWavelengths();
    std::vector<double> getPeaks();
    
    Eigen::VectorXd getPeaksasEigen();
    Eigen::VectorXd getWavelengthsasEigen();
    
    double getFirstWavelength();
    double getLastWavelength();
    
    int getNumOfRows();

	private:
		
		  std::vector<double> wavelengths;
		  std::vector<double> peaks;

};

#endif