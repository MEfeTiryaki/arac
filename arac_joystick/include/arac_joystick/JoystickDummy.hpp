/*
 * joystickHandlerBase.cpp
 *
 *  Created on: Jan 28, 2018
 *      Author: efe
 */

#include "arac_joystick/JoystickHandlerBase.hpp"

 namespace joystick {
class JoystickDummy : public JoystickHandlerBase{
public:
  JoystickDummy(kuco::State& state);

  virtual ~JoystickDummy();

  virtual void advance() override;

 private:


};

}