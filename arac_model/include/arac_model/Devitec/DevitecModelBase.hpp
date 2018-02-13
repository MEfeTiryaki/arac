/*
 Ad : DevitecModelBase.hpp
 Yazar : M. Efe Tiryaki

 Açıklama : Bu class gazebo benzetimi içierisinde eklenen değişik deviteç
    türlerinin devimsel özelliklerini gerçeklemek için yaratılmıştır.
    Controller_frame'den bağımsız olarak tasarlanmasının sebebi, gerçek kulman
    üzerinde de burada çalışan denetleyici yapısının kulman güdümcüsünden
    bağımsız olarak daha yüksek sıklıkta (frekansda) çalışması beklendiği içindir.
*/

#pragma once

#include "arac_model/Devitec/Denetleyici.hpp"

namespace kuco {


class DevitecModelBase
{
 public:
   DevitecModelBase();

   virtual ~DevitecModelBase();

   virtual void initilize();

   virtual void create();

   virtual void advance();

   virtual void reset();

 protected:

   Denetleyici duranDeneyleyici_;
   Denetleyici konumDeneyleyici_;
   Denetleyici konumHizDeneyleyici_;
   Denetleyici konumHizErkDeneyleyici_;


};

} /* namespace kuco */
