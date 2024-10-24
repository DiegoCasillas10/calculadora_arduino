void setup() {
 pinMode(2, INPUT);//A
 pinMode(3, INPUT);//B
 pinMode(4, INPUT);//C
 pinMode(5, INPUT);//D
 pinMode(14, INPUT);//E
 pinMode(15, INPUT);//F

 pinMode(6, INPUT); //X
 pinMode(7, INPUT); //Y
 pinMode(8, INPUT); //Z

 pinMode(9, OUTPUT); // Residuo
 pinMode(10, OUTPUT); // Infinito
 pinMode(11, OUTPUT); // Suma,Producto,Divisor,Verdadero
 pinMode(12, OUTPUT); // Acarreo,cociente
 pinMode(13, OUTPUT); // Error
 pinMode(16, OUTPUT); // Decimal
}
void loop() {
   int X = digitalRead(6);
   int Y = digitalRead(7);
   int Z = digitalRead(8);
  //////////////////////////////////////////////////////Suma |0|0|0|
 if (!X && !Y && !Z) { 
  
  int A = digitalRead(2);
  int B = digitalRead(3);
  int C = digitalRead(4);
  int D = digitalRead(5); 
  int E = digitalRead(14);
  int F = digitalRead(15);
  int W=(E & F);

  if ((E && !F) || (!E && F)) { 
    digitalWrite(16, HIGH); 
  } else if((!E && !F)){
     digitalWrite(16, LOW);
  }else{
    digitalWrite(16, LOW);
  }

  int resultado = (A ^ B ^ C ^ D ^ W); // Suma sin acarreo
  int acarreo = ((A & B) | (B & C) | (C & D) | (D & W)); // Cálculo del acarreo
 
  digitalWrite(11, resultado);
  digitalWrite(12, acarreo);
}else{
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
 
}
 ////////////////////////////////////////////////// Resta |0|0|1|
 if (!X && !Y && Z) { 
 digitalWrite(11, LOW);
   digitalWrite(12, LOW);
    int a = digitalRead(2);
    int b = digitalRead(3);
    int c = digitalRead(4);
    int d = digitalRead(5); 
    int E = digitalRead(14);
    int F = digitalRead(15);
    
  
  if ((E && !F) || (!E && F)) { 
    digitalWrite(16, HIGH); 
  } else if((!E && !F) | (E && F)){
     digitalWrite(16, LOW);
  }

    int resultado = (a & !b & !c & !d) | (!a & !b & c & d) | (!a & b & !c & d) | (!a & b & c & !d);

    digitalWrite(11, resultado);
  }else{
    digitalWrite(11, LOW);
  }
 ////////////////////////////////////////////////// Multiplicacion |0|1|0|
 if (!X && Y && !Z) { 
   digitalWrite(11, LOW);
   digitalWrite(12, LOW);
   int A = digitalRead(2);
   int B = digitalRead(3);
   int C = digitalRead(4);
   int D = digitalRead(5);
   int E = digitalRead(14);
   int F = digitalRead(15);
   int W = LOW;
  
  if ((E & !F) || (!E & F)) { 
    digitalWrite(16, HIGH); 
    W=LOW;
  } else if((!E & !F)){
     digitalWrite(16, LOW);
     W=LOW;
  } else if(E & F){
    W=HIGH;
    digitalWrite(16, LOW);
  }

   int producto = A & B & C & D ; 
   digitalWrite(11, producto); 
 }else {
   digitalWrite(11, LOW);
 }
    
 ////////////////////// División|0|1|1|
if (!X && Y && Z) { 
  int A = digitalRead(2);
  int B = digitalRead(3);
  int E = digitalRead(14);
  int C = digitalRead(4);
  int D = digitalRead(5);
  int F = digitalRead(15);

  // Convertir ABE y CDF a números decimales
  int ABE = (A << 2) | (B << 1) | E; // Corrimiento para ABE
  int CDF = (C << 2) | (D << 1) | F; // Corrimiento para CDF

  if (!CDF) {  // CDF == 000, División por cero
    digitalWrite(13, HIGH); // Error activo
    digitalWrite(10, HIGH); // Infinito (división por cero podría considerarse como tal)
    digitalWrite(11, LOW);  // Divisor no válido
    digitalWrite(12, LOW);  // Cociente no definido
    digitalWrite(9, LOW);   // Residuo no definido
  } else {
    digitalWrite(13, LOW);  // No hay error
    digitalWrite(10, LOW);  // No infinito
    digitalWrite(11, HIGH); // Divisor válido

    int quotient = ABE / CDF;
    int remainder = ABE % CDF;

    // Configurar cociente
    if (quotient > 0) {
      digitalWrite(12, HIGH);
    } else {
      digitalWrite(12, LOW);
    }

    // Configurar residuo
    if (remainder > 0) {
      digitalWrite(9, HIGH);
    } else {
      digitalWrite(9, LOW);
    }
  }

  

} else {
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);    
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(16, LOW); // Asegurarse de manejar el estado de pin 16 también aquí
}
//////////////////////////////////////////////////////AND |1|0|0|
 if (X && !Y && !Z) { 
   digitalWrite(11, LOW);
   digitalWrite(12, LOW);
   int A = digitalRead(2);
   int B = digitalRead(3);
   int C = digitalRead(4);
   int D = digitalRead(5);
   int E = digitalRead(14);
   int F = digitalRead(15);
   int W = LOW;
  
  if ((E && !F) || (!E && F)) { 
    digitalWrite(16, HIGH); 
    W=LOW;
  } else if((!E && !F)){
     digitalWrite(16, LOW);
     W=LOW;
  } else if(E && F){
    W=HIGH;
    digitalWrite(16, LOW);
  }

   int producto = W && A && B && C && D ; 
   digitalWrite(11, producto); 
 }
 else {
   digitalWrite(11, LOW);
 }
    
 //////////////////////////////////////////////////////XOR |1|0|1|
 if (X && !Y && Z) { 
   int A = digitalRead(2);
   int B = digitalRead(3);
   int C = digitalRead(4);
   int D = digitalRead(5); 
   int E = digitalRead(14);
   int F = digitalRead(15);
   int W = LOW;

    W = (E ^ F);
   if ((E && !F) || (!E && F)) { 
    digitalWrite(16, HIGH); 
  } else if((!E && !F)){
     digitalWrite(16, LOW);
  } else if(E && F){
    digitalWrite(16, LOW);
  }

   int OP = (W ^ A ^ B ^ C ^ D);
   digitalWrite(11, OP);
  }else {
   digitalWrite(11, LOW);
 }
 //////////////////////////////////////////////////////OR |1|1|0|
 if (X && Y && !Z) { 
   int A = digitalRead(2);
   int B = digitalRead(3);
   int C = digitalRead(4);
   int D = digitalRead(5); 
   int E = digitalRead(14);
   int F = digitalRead(15);
   int W = LOW;

   if ((E && !F) || (!E && F)) { 
    digitalWrite(16, HIGH); 
    W=LOW;
  } else if((!E && !F)){
     digitalWrite(16, LOW);
     W=LOW;
  } else if(E && F){
    W=HIGH;
    digitalWrite(16, LOW);
  }

   int OP = (W || A || B || C || D); 
   digitalWrite(11, OP);
  }else {
   digitalWrite(11, LOW);
 }
 //////////////////////////////////////////////////////NOT |1|1|1|
 if (X && Y && Z) { 
   int A = digitalRead(2);
   int B = digitalRead(3);
   int C = digitalRead(4);
   int D = digitalRead(5);
   int E = digitalRead(14);
   int F = digitalRead(15);
   int W = LOW; 


  if ((E && !F) || (!E && F)) { 
    digitalWrite(16, LOW); 
    W=LOW;
  } else if((!E && !F)){
     digitalWrite(16, HIGH);
     W=LOW;
  } else if(E && F){
    W=HIGH;
    digitalWrite(16, HIGH);
  }

  

  if (A == LOW) {
    digitalWrite(10, HIGH);  
  } else {
    digitalWrite(10, LOW); 
  }
  if (B == LOW) {
    digitalWrite(11, HIGH); 
  } else {
    digitalWrite(11, LOW); 
  }
  if (C == LOW) {
    digitalWrite(12, HIGH); 
  } else {
    digitalWrite(12, LOW); 
  }
  if (D == LOW) {
    digitalWrite(9, HIGH); 
  } else {
    digitalWrite(9, LOW); 
  }
}
}