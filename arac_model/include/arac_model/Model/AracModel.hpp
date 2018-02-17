/*
 name : AracModel.hpp
 Author : Selçuk Ercan , M. Efe Tiryaki

 */

#pragma once

#include "arac_model/Model/KulmanModel.hpp"
#include "arac_model/Module/Tekerlek.hpp"
#include <vector>

namespace kuco {

class AracModel : public KulmanModel
{
 public:
  AracModel();

  virtual ~AracModel();

  virtual void initilize();

  virtual void create();

  virtual void advance();

  virtual void reset();

  //void setTekerlek(Tekerlek tekerlek);

  std::vector<Tekerlek*>& getTekerlek();


 protected:

  // vector içinde pointer ne kadar doğru bir yaklaşım emin değilim ama dursun
  Tekerlek* tekerlekLF_;
  Tekerlek* tekerlekRF_;
  Tekerlek* tekerlekLH_;
  Tekerlek* tekerlekRH_;

  std::vector<Tekerlek*>* tekerlekler_;
};

} /* namespace kuco */
