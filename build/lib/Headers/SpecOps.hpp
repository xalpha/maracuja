//SpectrumProduct.hpp

#ifndef __SPECTOPS_H_INCLUDED__
#define __SPECTOPS_H_INCLUDED__

#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <maracuja/Spectrum.hpp>

namespace maracuja {

class SpecOps
{
	public:
  		
		SpecOps(const maracuja::Spectrum& spec);
		
		double interpolateLinearAt(double x);
		double interpolateCubicAt(double x);
		
		maracuja::Spectrum getSpectrum() const;
		maracuja::Spectrum* pairwiseMultiplication(maracuja::Spectrum&);
		maracuja::Spectrum* pairwiseMultiplication(maracuja::Spectrum&, int normalization_type, double samplerate);
		maracuja::Spectrum* adaptTo(double new_start, double new_end, double samplerate, bool normalize);
		maracuja::Spectrum* adaptTo(const maracuja::Spectrum&, bool normalize);
		
		void normalization_longify(double &new_start, double &new_end, maracuja::Spectrum&);
		void normalization_direct(double &new_start, double &new_end, maracuja::Spectrum&);
		void normalization_self(double &new_start, double &new_end);
		void normalization_bigger(double &new_start, double &new_end, maracuja::Spectrum&);
		void normalization_smaller(double &new_start, double &new_end, maracuja::Spectrum&);

	private:
		
		maracuja::Spectrum s;

};

}

#endif