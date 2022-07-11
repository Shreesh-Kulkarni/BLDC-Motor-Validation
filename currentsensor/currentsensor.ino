//variables for measured voltage and current
double Vout=0;
double current=0;
//scale factor for Hall Effect sensor depending on the model
//const double scalef=0.185;//5A
const double scalef=0.1;//20A
//const double scalef=0.066;//30A
int analogpin=A0;
const double vref=3.30;
const double resconv= 1024;
double resADC= vref/resconv;
double zerop= vref/2;

void setup()
{
   Serial.begin(9600);
}

void loop()
{
  for(int i=0;i<1000;i++)
  {
    Vout=(Vout+(resADC*analogRead(analogpin)));
    delay(1);

  }
  Vout/=1000;
  current=(Vout-zerop)/scalef;
  Serial.print(current,2);
  Serial.println("Amps");
  
}