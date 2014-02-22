#pragma once

#include "K_blade.hpp"

namespace gca {

	class GCA_trivector : public K_blade {

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
		GCA_trivector(): K_blade(4) {
			setBases(14, 13, 11, 7);
		}

		//Constructeur par recopie
		GCA_trivector(const K_blade& other): K_blade(4) {
			setBases(14, 13, 11, 7);
			*this = other;
		}

		//Constructeur à paramètres
		GCA_trivector(float e1, float e2, float e3, float e4): K_blade(4) {
			setBases(14, 13, 11, 7);
			*this << e1, e2, e3, e4;
		}

		//Destructeur.
		~GCA_trivector() {}

		//Surcharge de =
		GCA_trivector& operator= (const K_blade& other){

			if( base != other.base ) { 
				fprintf( stderr, "Incompatible types ! \n");
				return *this;
			}
			K_blade::operator=(other); 
			setBases(14, 13, 11, 7);
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
					res[i-1] =  (*this)[size - i ];
				else
					res[i-1] = -1 * (*this)[size - i ];
				++i;
			}

			return res;
			 
		}

	};

//---------------------------------------------------------------------------

	class GCA_antivector : public K_blade {

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
		GCA_antivector(): K_blade(4) {
			setBases(14, 13, 11, 7);
		}

		//Constructeur par recopie
		GCA_antivector(const K_blade& other): K_blade(4) {
			setBases(14, 13, 11, 7);
			*this = other;
		}

		//Constructeur à paramètres
		GCA_antivector(float e1, float e2, float e3, float e4): K_blade(4) {
			setBases(14, 13, 11, 7);
			*this << e1, e2, e3, e4;
		}

		//Destructeur. Utile ?
		~GCA_antivector() {}

		//Surcharge de =
		GCA_antivector& operator = (const K_blade& other){

			if( base != other.base ) { 
				fprintf( stderr, "Incompatible types ! \n");
				return *this;
			}
			K_blade::operator=(other); 
			setBases(14, 13, 11, 7);
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
					res[i] =  (*this)[size - i -1];
				else
					res[i] = -1 * (*this)[size - i -1];
				++i;
			}

			return res;
			 
		}

	};

}
