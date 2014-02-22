#pragma once

#include "K_blade.hpp"

namespace gca {

	class GCA_vector : public K_blade {

		void setBases( unsigned char comp0, unsigned char comp1, unsigned char comp2, unsigned char comp3 ){

			if( base.empty() ){
				base.push_back(comp0);
				base.push_back(comp1);
				base.push_back(comp2);
				base.push_back(comp3);
			}
			else{	
				base[0]= comp0;
				base[1]= comp1;
				base[2]= comp2;
				base[3]= comp3;
			}
		}

	public:
		//Constructeur vide
		GCA_vector(): K_blade(4) {
			setBases(8, 4, 2, 1);
		}

		//Constructeur par recopie
		GCA_vector(const K_blade& other): K_blade(4) {
			setBases(8, 4, 2, 1);
			*this = other;
		}

		//Constructeur à paramètres
		GCA_vector(float e1, float e2, float e3, float e4): K_blade(4) {
			setBases(8, 4, 2, 1);
			*this << e1, e2, e3, e4;
		}

		//Destructeur. Utile ?
		~GCA_vector() {}

		//Surcharge de =
		GCA_vector& operator = (const K_blade& other){

			if( base != other.base ) { // Ne fonctionne pas si on le place dans K_blade
				fprintf( stderr, "Incompatible types ! \n");
				return *this;
			}
			K_blade::operator=(other); 
			setBases(8, 4, 2, 1);
			return *this;
		}

		K_blade operator~() const {
			unsigned int c= 15;
			int size = this->size();
			K_blade res(size);
			int i = 1;

			for(std::vector<unsigned int>::const_reverse_iterator abase = this->base.rbegin(); abase != this->base.rend(); ++abase){

				res.base.push_back( (~(*abase)) & c );

				if( i % 2 == 0)
					res[i-1] =  (*this)[size - i];
				else
					res[i-1] = -1 * (*this)[size - i];
				++i;
			}

			return res;
			 
		}

	};


//---------------------------------------------------------------------------

	class GCA_antitrivector : public K_blade {

		void setBases( unsigned char comp0, unsigned char comp1, unsigned char comp2, unsigned char comp3 ){

			if( base.empty() ){
				base.push_back(comp0);
				base.push_back(comp1);
				base.push_back(comp2);
				base.push_back(comp3);
			}
			else{	
				base[0]= comp0;
				base[1]= comp1;
				base[2]= comp2;
				base[3]= comp3;
			}
		}

	public:
		//Constructeur vide
		GCA_antitrivector(): K_blade(4) {
			setBases(8, 4, 2, 1);
		}

		//Constructeur par recopie
		GCA_antitrivector(const K_blade& other): K_blade(4) {
			setBases(8, 4, 2, 1);
			*this = other;
		}

		//Constructeur à paramètres
		GCA_antitrivector(float e1, float e2, float e3, float e4): K_blade(4) {
			setBases(8, 4, 2, 1);
			*this << e1, e2, e3, e4;
		}

		//Destructeur. Utile ?
		~GCA_antitrivector() {}

		//Surcharge de =
		GCA_antitrivector& operator= (const K_blade& other){

			if( base != other.base ) {
				fprintf( stderr, "Incompatible types ! \n");
				return *this;
			}
			K_blade::operator=(other); 
			setBases(8, 4, 2, 1);
			return *this;
		}

		K_blade operator~() const {
			unsigned int c= 15;
			int size = this->size();
			K_blade res(size);
			int i = 0;

			for(std::vector<unsigned int>::const_reverse_iterator abase = this->base.rbegin(); abase != this->base.rend(); ++abase){

				res.base.push_back( (~(*abase)) & c );

				if( i % 2 == 0)
					res[i] =  (*this)[size - i - 1];
				else
					res[i] = -1 * (*this)[size - 1 - i];
				++i;
			}

			return res;
			 
		}


	};
}
