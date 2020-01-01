void initHAL()
{
  display.println("Init HAL");
  initServo();
  initLegs();
  display.display();
}

void initLegs() {

}

void updateLegs() {
  legs[LEGLF].angle = ikLegLF.solve();
  legs[LEGRF].angle = ikLegRF.solve();
  legs[LEGLB].angle = ikLegLB.solve();
  legs[LEGRB].angle = ikLegRB.solve();
}

double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
  return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint16_t angleToPulse(double angleRad) {
  // TODO, angle expected to be between 0 and 180 deg (0 and PI)
  
  double pulse = mapf(angleRad, 0, M_PI, 600, 2400);
  // from Adafruit PWM lib
  double pulselength;
  pulselength = 1000000; // 1,000,000 us per second

  // Read prescale
  uint16_t prescale = pwm.readPrescale();

  // Calculate the pulse for PWM based on Equation 1 from the datasheet section
  // 7.3.5
  prescale += 1;
  pulselength *= prescale;
  pulselength /= pwm.getOscillatorFrequency();
  pulse /= pulselength;

  return pulse;
}

void setLegPWM(leg &_leg)
{
  
  // TODO limits and angle normalize
  pwm.setPWM(_leg.pin.alpha,  0, (_leg.angle.alpha + _leg.trim.alpha));
  pwm.setPWM(_leg.pin.beta,   0, (_leg.angle.beta  + _leg.trim.beta));
  pwm.setPWM(_leg.pin.gamma,  0, (_leg.angle.gamma + _leg.trim.gamma));
}
