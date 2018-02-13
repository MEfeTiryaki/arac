/*
 name : Govde.hpp
 Author : Selçuk Ercan , M. Efe Tiryaki

*/

#pragma once

#include "arac_model/Module/ModuleBase.hpp"

/* Kulman Controller namespace */
namespace kuco {


class Govde : public ModuleBase
{
 public:
  // Constructor.
  Govde();

  // Destructor.
  virtual ~Govde();

  // Init
  virtual void initilize();

  // Create
  virtual void create();

  // Advance
  virtual void advance();



};

} /* namespace kuco */
