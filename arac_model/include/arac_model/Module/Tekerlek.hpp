/*
 name : Tekerlek.hpp
 Author : Selçuk Ercan , M. Efe Tiryaki

*/

#pragma once

#include "arac_model/Module/ModuleBase.hpp"

/* Kulman Controller namespace */
namespace kuco {


class Tekerlek: public ModuleBase
{
 public:
  // Constructor.
  Tekerlek();

  // Destructor.
  virtual ~Tekerlek();

  // Init
  virtual void init(int argc, char **argv);

  // Create
  virtual void create();

  // Advance
  virtual void advance();




};

} /* namespace kuco */
