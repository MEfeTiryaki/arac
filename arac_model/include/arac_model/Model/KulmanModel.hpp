/*
 name : Kulman.hpp
 Author : Selçuk Ercan , M. Efe Tiryaki

*/

#include "arac_model/Module/Govde.hpp"
#pragma once


namespace kuco {

class KulmanModel
{
 public:
   KulmanModel();

   virtual ~KulmanModel();

   virtual void initilize();

   virtual void create();

   virtual void advance();

   virtual void reset();

  void setGovde(Govde* govde);
  Govde& getGovde();
 protected:

   // Her kulmanın gövdesi olması gerektigi için gövdeyi kulmanda tanımlıyoruz
   // bu class'tan çıkan çocuklar da kullana bilsin diye protected olarak tanımlandı
   Govde* govde_;

};

} /* namespace kuco */
