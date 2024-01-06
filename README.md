# Homework 

Per compilare il programma seguire i seguenti passaggi: 

```bash
$ mkdir build
$ cd build 
$ cmake ..
$ make  
```

Per eseguire il programma basta avviare l'eseguibile `main` che viene creato nella sottocartella `build/src`. Quest'ultimo crea un file di output `coordinates.txt`, tale file può essere utilizzato per visualizzare la simulazione tramite `visualizer.py` (contenuto nella sottocartella `src`).

Quindi per eseguire una simulazione la lista dei comandi da eseguire è (all'interno della cartella build):

```bash
$ ./src/main
$ python3 ../src/visualizer.py  
```