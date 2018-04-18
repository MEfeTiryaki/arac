/*
 name : Arac2Model.hpp
 Author : Selçuk Ercan , M. Efe Tiryaki

 */

#pragma once

#include "arac_model/Model/KulmanModel.hpp"
#include "arac_model/Module/Tekerlek.hpp"
#include <vector>

namespace kuco {

class Arac2Model : public KulmanModel
{
 public:
  Arac2Model();

  virtual ~Arac2Model();

  virtual void initilize();

  virtual void create();

  virtual void advance();

  virtual void reset();

  //void setTekerlek(Tekerlek tekerlek);

  std::vector<Tekerlek*>& getTekerlek();


 protected:

  // vector içinde pointer ne kadar doğru bir yaklaşım emin değilim ama dursun
  Tekerlek* tekerlekL_;
  Tekerlek* tekerlekR_;

  std::vector<Tekerlek*>* tekerlekler_;
};

} /* namespace kuco */