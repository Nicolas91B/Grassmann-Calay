#pragma once

#include "K_blade.hpp"

namespace gca {

	class GCA_quadvector : public K_blade {

		void setBases( unsigned int comp0 ){

			if( base.empty() )
				base.push_back(comp0);
			else
				base[0]= comp0;
		}

	public:
		//Constructeur vide
		GCA_quadvector(): K_blade(1) {
			setBases(15);
		}

		//Constructeur par recopie
		GCA_quadvector(const K_blade& other): K_blade(1) {
			setBases(15);
			*this = other;
		}

		//Constructeur à paramètres
		GCA_quadvector(float e1): K_blade(1) {
			setBases(15);
			*this << e1;
		}

		//Destructeur.
		~GCA_quadvector() {}

		//Surcharge de =
		GCA_quadvector& operator = (const K_blade& other){
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
			
			res.base.push_back(0);
			res[0] =  (*this)[0];
			
			return res; 
		}
	};

//---------------------------------------------------------------------------

	class GCA_antiscalar : public K_blade {

		void setBases( unsigned int comp0 ){

			if( base.empty() )
				base.push_back(comp0);
			else
				base[0]= comp0;
		}

	public:
		//Constructeur vide
		GCA_antiscalar(): K_blade(1) {
			setBases(0);
		}

		//Constructeur par recopie
		GCA_antiscalar(const K_blade& other): K_blade(1) {
			setBases(0);
			*this = other;
		}

		//Constructeur à paramètres
		GCA_antiscalar(float e1): K_blade(1) {
			setBases(0);
			*this << e1;
		}

		//Destructeur.
		~GCA_antiscalar() {}

		//Surcharge de =
		GCA_antiscalar& operator = (const K_blade& other){
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

	
}
