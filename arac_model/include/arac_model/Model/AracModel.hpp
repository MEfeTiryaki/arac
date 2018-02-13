/*
 name : AracModel.hpp
 Author : Selçuk Ercan , M. Efe Tiryaki

*/

#pragma once

#include "arac_model/Model/KulmanModel.hpp"
#include "arac_model/Module/Tekerlek.hpp"
namespace kuco {

class AracModel: public KulmanModel
{
 public:
   AracModel();

   virtual ~AracModel();

   virtual void initilize();

   virtual void create();

   virtual void advance();

   virtual void reset();

 protected:

   // vector içinde pointer ne kadar doğru bir yaklaşım emin değilim ama dursun
   std::vector<Tekerlek*> tekerlekler_;

};

} /* namespace kuco */
