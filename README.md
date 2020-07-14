# PI-FINAL
 Final de Programacion Imperativa ITBA Primer Cuatrimestre 2020
 
Integrantes: Federico Gustavo Rojas Pelliccia - Roberto Franco Rodriguez Tulasne - Leonardo Agustín D'Agostino

Para compilar el trabajo simplemente escribir make en la consola, pues el archivo .make tiene como nombre makefile por lo que es automáticamente reconocido por make. Al ejecutar esta instrucción se generaran ambos ejecutables: finalBUE y finalVAN.

Luego ecribir las siguientes lineas en consola y ejecutar para generar las queries:

./finalBUE arbolesBUE.csv barriosBUE.csv
./finalVAN arbolesVAN.csv barriosVAN.csv

Una vez creadas las queries estas se pueden visualizar de la siguiente forma:

cat query1BUE.csv
cat query2BUE.csv
cat query3BUE.csv

cat query1VAN.csv
cat query2VAN.csv
cat query3VAN.csv

Se puede utilizar make clean para eliminar los ejecutables.