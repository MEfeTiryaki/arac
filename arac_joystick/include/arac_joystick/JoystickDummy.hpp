/*
 * joystickHandlerBase.cpp
 *
 *  Created on: Jan 28, 2018
 *      Author: efe
 */

#include "arac_joystick/JoystickHandlerBase.hpp"


class JoystickDummy : public JoystickHandlerBase{
public:
  virtual JoystickDummy();

  virtual ~JoystickDummy();

  virtual void advance() override;

 private:


};
