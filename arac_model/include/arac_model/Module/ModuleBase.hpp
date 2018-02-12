/*
 name : ModuleBase.hpp
 Author : Selçuk Ercan , M. Efe Tiryaki

*/


#pragma once

/* Kulman Controller namespace */
namespace kuco {


class ModuleBase
{
 public:
  // Constructor.
  ModuleBase();

  // Destructor.
  virtual ~ModuleBase();

  // Init
  virtual void init(int argc, char **argv);

  // Create
  virtual void create();

  // Advance
  virtual void advance();

  // Bu işlevler çocukarda değişmeyeceği için virtual tanımlanmadı.
  std::string getName();
  void setName(std::string name);

  void getDesiredState();
  void getMeasuredState();

 protected:

  std::string name_;

  std::vector<double> measuredState;
  std::vector<double> desiredState;

};

} /* namespace kuco */
