#pragma once

#include "K_blade.hpp"

namespace gca {

	class GCA_scalar : public K_blade {

		void setBases( unsigned int comp0 ){
			if( base.empty() )
				base.push_back(comp0);
			else
				base[0]= comp0;
		}

	public:
		//Constructeur vide
		GCA_scalar(): K_blade(1) {
			setBases(0);
		}

		//Constructeur par recopie
		GCA_scalar(const K_blade& other): K_blade(1) {
			setBases(0);
			*this = other;
		}

		//Constructeur à paramètres
		GCA_scalar(float e1): K_blade(1) {
			setBases(0);
			*this << e1;
		}

		//Destructeur.
		~GCA_scalar() {}

		//Surcharge de =
		GCA_scalar& operator= (const K_blade& other){
			if( base != other.base ) {
				fprintf( stderr, "Incompatible types ! \n");
				return *this;
			}
			K_blade::operator=(other); 
			setBases(0);
			return *this;
		}

		K_blade operator~() const {
			int size = this->size();
			K_blade res(size);
			
			res.base.push_back( 15 );
			res[0] =  (*this)[0];
			
			return res; 
		}

	};

//---------------------------------------------------------------------------

	class GCA_antiquadvector : public K_blade {

		void setBases( unsigned int comp0 ){
			if( base.empty() )
				base.push_back(comp0);
			else
				base[0]= comp0;
		}

	public:
		//Constructeur vide
		GCA_antiquadvector(): K_blade(1) {
			setBases(15);
		}

		//Constructeur par recopie
		GCA_antiquadvector(const K_blade& other): K_blade(1) {
			setBases(15);
			*this = other;
		}

		//Constructeur à paramètres
		GCA_antiquadvector(float e1): K_blade(1) {
			setBases(15);
			*this << e1;
		}

		//Destructeur. Utile ?
		~GCA_antiquadvector() {}

		//Surcharge de =
		GCA_antiquadvector& operator= (const K_blade& other){
			if( base != other.base ) { 
				fprintf( stderr, "Incompatible types ! \n");
				return *this;
			}
			K_blade::operator=(other); 
			setBases(15);
			return *this;
		}



		K_blade operator~() const {
			int size = this->size();
			K_blade res(size);
			
			res.base.push_back( 0 );
			res[0] =  (*this)[0];
			
			return res; 
		}

	};
}
