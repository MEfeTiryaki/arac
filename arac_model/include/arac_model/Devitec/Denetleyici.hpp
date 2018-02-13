/*
 Ad : Denetleyici.hpp
 Yazar : M. Efe Tiryaki

 Açıklama : Bu class gazebo benzetimi içierisinde eklenen değişik deviteç
    türlerinin devimsel özelliklerini gerçeklemek için yaratılmıştır.
    Controller_frame'den bağımsız olarak tasarlanmasının sebebi, gerçek kulman
    üzerinde de burada çalışan denetleyici yapısının kulman güdümcüsünden
    bağımsız olarak daha yüksek sıklıkta (frekansda) çalışması beklendiği içindir.
*/

#pragma once

namespace kuco {


class Denetleyici
{
 public:
   Denetleyici();

   virtual ~Denetleyici();

   virtual void initilize();

   virtual void create();

   virtual void advance();

   virtual void reset();

 protected:

   // proportional gain
   double oransalEdinc;
   // integral gain
   double tumlevselEdinc;
   // derivative gain
   double turevselEdinc;

};

} /* namespace kuco */
