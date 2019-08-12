int F_pos,S_pos,T_pos,L_pos,E_pos,i,k,val1,val2,val3,val4,flg;
String r1,r2,r3,r4;
String readString;
char message[50];
void setup() 
{
  Serial.begin(9600);
  i=0;

  for(k=2;k<14;k++)
  {
   pinMode(k,OUTPUT);
   digitalWrite(k,HIGH); 
  }
}

void loop() 
{

  while (Serial.available()) 
  {
    char c = Serial.read(); 
    readString += c;
    message[i++]=c;
    delay(2);
    if(c==']')
    {
      Serial.println(message);
      Serial.println(i);
      flg=0;
      break;
    }
  }
  if((message[0]=='[')&&(flg == 0))
  {
      if (readString.length() >0) 
      {
          F_pos=readString.indexOf('F');
          S_pos=readString.indexOf('S');
          T_pos=readString.indexOf('T');
          L_pos=readString.indexOf('L');
          E_pos=readString.indexOf('!');
          r1=String(readString.substring(F_pos+1, S_pos)); 
          r2=String(readString.substring(S_pos+1, T_pos)); 
          r3=String(readString.substring(T_pos+1, L_pos)); 
          r4=String(readString.substring(L_pos+1, E_pos)); 
          Serial.print("Values:");
          Serial.println(r1);
          Serial.println(r2);
          Serial.println(r3);
          Serial.println(r4);
          val1 = r1.toInt();
          val2 = r2.toInt();
          val3 = r3.toInt();
          val4 = r4.toInt();
          readString=" ";
          flg =1;
          for(k=0;k<=i;k++)
          {
           message[k]=char(0); 
          }
          i=0;   
      }
  }
      if(flg == 1)
      {
          if((val1 == -1)&&(val2 == -1)&&(val3 == -1)&&(val4 == -1))
          {
           for(k=2;k<14;k++)
           {
            digitalWrite(k,HIGH); 
           }
          }
          else if((val1 >= val2)&&(val1 >= val3)&&(val1 >= val4))
          {
           digitalWrite(2,LOW);
           digitalWrite(4,HIGH);
           digitalWrite(5,LOW);
           digitalWrite(8,LOW);
           digitalWrite(11,LOW);
           if(val1>10)
           {
            val1 = val1 - 10;
           }
           for(k=0;k<val1;k++)
           {
            delay(1000);
            delay(1000);
           }
           delay(2000);
           digitalWrite(3,LOW);
           digitalWrite(2,HIGH);
           delay(2000);
           digitalWrite(3,HIGH);
           val1 = -1;
          }
          else if((val2 >= val1)&&(val2 >= val3)&&(val2 >= val4))
          {
           digitalWrite(4,LOW);
           digitalWrite(5,HIGH);
           digitalWrite(7,LOW);
           digitalWrite(8,LOW);
           digitalWrite(11,LOW);
           if(val2>10)
           {
            val2 = val2 - 10;
           }
           for(k=0;k<val2;k++)
           {
            delay(1000);
            delay(1000);
           }
           delay(2000);
           digitalWrite(6,LOW);
           digitalWrite(7,HIGH);
           delay(2000);
           digitalWrite(6,HIGH);
           val2 = -1;
          }
          else if((val3 >= val1)&&(val3 >= val2)&&(val3 >= val4))
          {
           digitalWrite(4,LOW);
           digitalWrite(5,LOW);
           digitalWrite(8,HIGH);
           digitalWrite(10,LOW);
           digitalWrite(11,LOW);
           if(val3>10)
           {
            val3 = val3 - 10;
           }
           for(k=0;k<val3;k++)
           {
            delay(1000);
            delay(1000);
           }
           delay(2000);
           digitalWrite(9,LOW);
           digitalWrite(10,HIGH);
           delay(2000);
           digitalWrite(9,HIGH);
           val3 = -1;
          }
          else if((val4 >= val1)&&(val4 >= val2)&&(val4 >= val3))
          {
           digitalWrite(4,LOW);
           digitalWrite(5,LOW);
           digitalWrite(8,LOW);
           digitalWrite(11,HIGH);
           digitalWrite(13,LOW);
           if(val4>10)
           {
            val4 = val4 - 10;
           }
           for(k=0;k<val4;k++)
           {
            delay(1000);
            delay(1000);
           }
           delay(2000);
           digitalWrite(12,LOW);
           digitalWrite(13,HIGH);
           delay(2000);
           digitalWrite(12,HIGH);
           val4 = -1;
          }             
      } 
}
