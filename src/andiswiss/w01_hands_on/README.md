# System-Programmierung
## Hands-on zu Lektion 1
Für Slides und Code Beispiele, siehe [Lektion 1](../../../fhnw-syspr/blob/master/01/README.md)

> *Achtung: Arbeiten Sie nicht direkt auf diesem Repository.*<br/>
> *[Erstellen Sie eine persönliche Kopie, mit diesem GitHub Classroom Link](https://classroom.github.com/a/-xV9LSkq).*

### a) int Wertebereich, 15'
* Schreiben Sie ein Programm *my_range.c*, das den Wertebereich des Typs *int* ausgibt:<pre>
    $ ./my_range
    INT_MIN, INT_MAX</pre>
* Nutzen Sie aus, dass *INT_MAX + 1 = INT_MIN* gilt.
* Die Ausgabe von *int* Werten ist möglich mit *%d*, z.B.<pre>
    printf("%d\n", i); // \n = newline character</pre>

### b) Argumente lesen, 15'
* Command-Line Argumente als Parameter von main:<pre>
    int main(int argc, char *argv[]);</pre>
* Schreiben Sie ein Programm *my_args.c*, das alle Command-Line Argumente mit Index ausgibt:<pre>
    $ ./my_args hoi => 0: ./my_args, 1: hoi</pre>
* Erweitern Sie das Programm, dass es einen Fehler ausgibt, falls ein Argument nicht aus [a-z]* besteht.

### c) Bäume, 15'
* Erstellen Sie eine Datei *my_tree.c* mit einem Struct Typ Tree mit Zeigern auf *left*, *right* vom selben Typ, und einem String *label* von maximal 32 Byte Länge.
* Instanzieren Sie einen binären Baum mit 3 Blättern, verwenden Sie dazu die Funktionen malloc und free.

### d) Makefile, 15'
* Erstellen Sie ein *makefile* für Ihren Hands-on Code.
* Verwenden Sie die Compiler Flags aus dem Script.
* Korrigieren Sie allfällige neue Kompilationsfehler.
* Führen Sie *make clean* aus, vor dem *git commit*.
