# Fel i koden till d77.1

Felen är att:

1. rad 12 ska vara `res = res << 1;` och inte `res = res << 2;`  
   res << 1 är detsamma som res * 2, res << 2 är detsamma som res *4.
2. rad 19 och rad 20 ska innehålla  
   `randNumber = myexp2(random(2, 11));`  
   och inte  
   `randNumber = myexp2(random(2, 10));`  
   Om man fixar fel 1 så kommer randNumber att få mellan 4 och 512, inte
   4 och 1024!
