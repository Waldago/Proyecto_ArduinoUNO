void setup()                           // Prog_37_1
   {   
        for (int j=2; j<19; j++)
        pinMode(j, OUTPUT);
   }

void loop()
   {
        for (int j=2; j<10; j++)
           {
              digitalWrite(j, HIGH);     //Levantamos la columna
              for (int k= 10 ; k<18 ; k++)
                 {
                     digitalWrite(k, LOW);   //Encendemos el punto
                     delay(250);
                     digitalWrite(k, HIGH);  //Apagamos el punto
                 }
              digitalWrite(j, LOW);                //Bajamos la columna
           }
    }