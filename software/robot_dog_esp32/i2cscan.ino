void displayI2CScan()
{
  for (byte i = 8; i < 120; i++)
  {
    Wire.beginTransmission (i);        // Begin I2C transmission Address (i)
    if (Wire.endTransmission () == 0)  // Receive 0 = success (ACK response) 
    {
      display.print (i, DEC);
      display.print (" (0x");
      display.print (i, HEX);
      display.print ("), ");
    }
  }
    
  display.display();
}
