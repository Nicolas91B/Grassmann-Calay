#pragma once

#include "K_blade.hpp"

namespace gca {

	class GCA_bivector : public K_blade {

		void setBases( 	unsigned char comp0, unsigned char comp1, unsigned char comp2, 
				unsigned char comp3, unsigned char comp4, unsigned char comp5 ){

			if( base.empty() ){
				base.push_back(comp0);
				base.push_back(comp1);
				base.push_back(comp2);
				base.push_back(comp3);
				base.push_back(comp4);
				base.push_back(comp5);
			}
			else{	
				base[0]= comp0;
				base[1]= comp1;
				base[2]= comp2;
				base[3]= comp3;
				base[4]= comp4;
				base[5]= comp5;
			}
		}

	public:
		//Constructeur vide
		GCA_bivector(): K_blade(6) {
			setBases(12, 10, 9, 6, 5, 3);
		}

		//Constructeur par recopie
		GCA_bivector(const K_blade& other): K_blade(6) {
			setBases(12, 10, 9, 6, 5, 3);
			*this = other;
		}

		//Constructeur à paramètres
		GCA_bivector(float e1, float e2, float e3, float e4, float e5, float e6): K_blade(6) {
			setBases(12, 10, 9, 6, 5, 3);
			*this << e1, e2, e3, e4, e5, e6;
		}

		//Destructeur 
		~GCA_bivector() {}

		//Surcharge de =
		GCA_bivector& operator = (const K_blade& other) {

			if( base != other.base ) { 
				fprintf( stderr, "Incompatible types ! \n");
				return *this;
			}
			K_blade::operator=(other); 
			setBases(12, 10, 9, 6, 5, 3);
			return *this;
		}

		K_blade operator~() const {
			unsigned int c= 15;
			K_blade res(this->size());

			res.base.push_back( (~(base[5])) & c );
			res[5] =  (*this)[0];
			res.base.push_back( (~(base[4])) & c );
			res[4] = -1 * (*this)[1];
			res.base.push_back( (~(base[3])) & c );
			res[3] =  (*this)[2];
			res.base.push_back( (~(base[2])) & c );
			res[2] = (*this)[3];
			res.base.push_back( (~(base[1])) & c );
			res[1] =  -1*(*this)[4];
			res.base.push_back( (~(base[0])) & c );
			res[0] = (*this)[5];
			
			return res;
			 
		}	

	};

//---------------------------------------------------------------------------

	class GCA_antibivector : public K_blade {

		void setBases( 	unsigned char comp0, unsigned char comp1, unsigned char comp2, 
				unsigned char comp3, unsigned char comp4, unsigned char comp5 ){

			if( base.empty() ){
				base.push_back(comp0);
				base.push_back(comp1);
				base.push_back(comp2);
				base.push_back(comp3);
				base.push_back(comp4);
				base.push_back(comp5);
			}
			else{	
				base[0]= comp0;
				base[1]= comp1;
				base[2]= comp2;
				base[3]= comp3;
				base[4]= comp4;
				base[5]= comp5;
			}
		}

	public:
		//Constructeur vide
		GCA_antibivector(): K_blade(6) {
			setBases(12, 10, 9, 6, 5, 3);
		}

		//Constructeur par recopie
		GCA_antibivector(const K_blade& other): K_blade(6) {
			setBases(12, 10, 9, 6, 5, 3);
			*this = other;
		}

		//Constructeur à paramètres
		GCA_antibivector(float e1, float e2, float e3, float e4, float e5, float e6): K_blade(6) {
			setBases(12, 10, 9, 6, 5, 3);
			*this << e1, e2, e3, e4, e5, e6;
		}

		//Destructeur
		~GCA_antibivector() {}

		//Surcharge de =
		GCA_antibivector& operator = (const K_blade& other) {

			if( base != other.base ) {
				fprintf( stderr, "Incompatible types ! \n");
				return *this;
			}
			K_blade::operator=(other); 
			setBases(12, 10, 9, 6, 5, 3);
			return *this;
		}

		K_blade operator~() const {
			unsigned int c= 15;
			K_blade res(this->size());

			res.base.push_back( (~(base[5])) & c );
			res[5] =  (*this)[0];
			res.base.push_back( (~(base[4])) & c );
			res[4] = -1 * (*this)[1];
			res.base.push_back( (~(base[3])) & c );
			res[3] =  (*this)[2];
			res.base.push_back( (~(base[2])) & c );
			res[2] = (*this)[3];
			res.base.push_back( (~(base[1])) & c );
			res[1] =  -1*(*this)[4];
			res.base.push_back( (~(base[0])) & c );
			res[0] = (*this)[5];

			return res;
			 
		}		

	};
}
