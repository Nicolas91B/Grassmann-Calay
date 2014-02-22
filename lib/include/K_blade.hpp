#pragma once 

#include <Eigen/Dense>
#include <iostream>
#include <ostream>
#include <vector>
#include <map>
#include <limits>
using namespace Eigen;


namespace gca{

	class K_blade : public VectorXd { 

	private:

		int wedgefactor( const std::vector<unsigned int>& B1, const std::vector<unsigned int>& B2, int i, int j ) const{

			int s= B1[0] + B2[0];

			if ( !B1[0] || !B2[0] )  return 1;

			switch( s ){

				case 16 : 	if( i < j  ) 	return 1; break;
				case 20 : 	if( i == 0 || j == 0 || i == 5 || j == 5 
								|| (B1[0] == 12 && j == 3) || (B1[0] == 8 && i == 3)  ) 	return 1; break;
				case 22 : 	if( B1[0] == 14 ){
								if( B1[i] == 14 || B1[i] == 11)
									return 1;
							}
							else{
								if( B2[j] == 14 || B2[j] == 11)
									return 1;
							}
							break;

				case 24 : 	if( !(B1[i] == 10 || B1[i] == 5 || B2[j] == 10 || B2[j] == 5) ) 	return 1; break; 


				default: 	fprintf(stderr, "Fatal Error : Grade %d > 4\n", s );
			}

			return -1;
		}

	public:				
		std::vector<unsigned int> base;
		typedef VectorXd Base;


		//Constructeur vide
		K_blade(int size): VectorXd(size) { }

		//Surchage de ==
		bool operator==(const K_blade& other) const{
		
			bool r= this->Base::operator==(other); 
			return r && base == other.base;
		}

		//Surcharge de =
		template<typename OtherDerived>
		K_blade& operator= (const MatrixBase<OtherDerived>& other){
			
			Base::operator=(other);
			return *this;
		}

		//Wedge Product
		K_blade operator^(const K_blade& other) const{
			std::map<unsigned int, double> tmp;
			for (int i = 0; i < this->size(); ++i)
				for (int j = 0; j < other.size(); ++j)

					if( (base[i] ^ other.base[j]) == (base[i] + other.base[j]) ){
						int f= wedgefactor( base, other.base, i, j );
					
						tmp[ base[i]^other.base[j] ] += (*this)[i] * other[j] * f;
					}

			K_blade result(tmp.size());
			int i = 0;
			for (std::map<unsigned int, double>::reverse_iterator atmp = tmp.rbegin(); atmp != tmp.rend(); ++atmp)
			{
				result[i] = atmp->second;
				result.base.push_back(atmp->first);
				++i;
			}
			return result;
		}		

		friend K_blade operator-(const K_blade& R)  {
			
			K_blade res( R.size() );

			for (int i= 0; i < R.size(); ++i){

				res.base.push_back(R.base[i]);
				res[i] = -1* R[i];
			}

			return res;
			 
		}

		bool empty() const{
			
			return base.empty();
		}

		size_t size() const{
			
			return base.size();
		}

		friend std::ostream& operator<< (std::ostream& flux, const K_blade& k){

			if( k.empty() ){
				flux << "Fatal Error (904): Bad init\n";
				
			}
			else{ 
				flux << "\n   ------------------- : ";
				for( int i= 0; i < k.size(); ++i ){
					flux << "\n > ";
					flux << k[i];
				/*-----------------------------------------*/	
					flux << ".e";

					unsigned char index= 8;

					for( int j= 0; j < 4; ++j){
						if( index & k.base[i] )
							flux << j+1;
		
						index= index >> 1; 
					}
				/*-----------------------------------------*/				
				}
			}
			flux << "\n";
			return (flux);
		}

		//Obsolète ?
		void show(){

			if( this->empty() ){
				fprintf( stderr, "Fatal Error: 904\n" );
				return;
			} 
		
			std::cout << "----------------------";
			for( int i= 0; i < this->size(); ++i ){
				std::cout << std::endl << " > " << (*this)[i] << ".e";

				unsigned char index= 8;

				for( int j= 0; j < 4; ++j){
					if( index & base[i] )
						std::cout << j+1;
		
					index= index >> 1; 
				}				
			}
		}
	};
}
