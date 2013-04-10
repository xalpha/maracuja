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

#include <stdlib.h>
#include <iterator>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <string.h>
#include <SSM.hpp>

using namespace std;

void SSM::parseFile(const std::string& filename) {
    QFile file(QString(filename.c_str()));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "Error", file.errorString());
        return;
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();    
        QStringList fields = line.split(";");    
        
        if (fields.isEmpty() || fields.size() < 2) {
            QMessageBox::information(0, "Error", "File is corrupted or invalid!");
            return;
        }
        
        this->wavelengths.push_back(fields.at(0).toDouble());
        this->peaks.push_back(fields.at(1).toDouble());
    }

    file.close();

}

std::vector<double> SSM::getWavelengths() {
    return this->wavelengths;
}

Eigen::VectorXd SSM::getWavelengthsasEigen() {
    Eigen::VectorXd data;
    if (this->getNumOfRows() < 0) {
        data = Eigen::VectorXd::Zero(0);
        return data;
	   }
	   data = Eigen::VectorXd::Zero(this->getNumOfRows());
	
	   for (int i=0; i<this->getNumOfRows(); i++) {
		      data[i] = this->wavelengths[i];
	   }
	   return data;
	   
}

Eigen::VectorXd SSM::getPeaksasEigen() {
	   Eigen::VectorXd data;
	   if (this->getNumOfRows() < 0) {
		      data = Eigen::VectorXd::Zero(1);
		      return data;
	   }
	   data = Eigen::VectorXd::Zero(this->getNumOfRows());
	
	   for (int i=0; i<this->getNumOfRows(); i++) {
		      data[i] = this->peaks[i];
	   }
	   return data;
	   
}

std::vector<double> SSM::getPeaks() {
	   return this->peaks;
}

double SSM::getFirstWavelength() {
	   if (this->getNumOfRows() < 0) {
	       return 0.0;
	   }
	   return this->wavelengths[0];
	   
}

double SSM::getLastWavelength() {
	   if (this->getNumOfRows() < 0) {
	       return 0.0;
	   }
	   return this->wavelengths[this->getNumOfRows() - 1];
	   
}

int SSM::getNumOfRows() {
	   return this->wavelengths.size();
}