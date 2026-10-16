#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"

/*
 * Quellenhinweise:
 *
 * {fmt}:
 * https://fmt.dev/latest/api/
 *
 * C++ Speicherdauer und Linkage:
 * https://en.cppreference.com/w/cpp/language/storage_duration
 *
 * Dynamische Speicherverwaltung mit new:
 * https://en.cppreference.com/w/cpp/language/new
 *
 * delete:
 * https://en.cppreference.com/w/cpp/language/delete
 *
 * Hinweis:
 * Die konkrete Zuordnung zu Stack, Heap, .data, .bss, .rodata und .text
 * ist implementierungs- bzw. systemabhängig. Die hier verwendete Darstellung
 * entspricht der typischen Speicherorganisation eines kompilierten
 * C++-Programms unter Linux.
 * 
 * Erstellt von ChatGPT
 */


/* Teil 1 - 1*/
int globalVar = 1;              // typischerweise .data
int globalVar0 = 0;             // typischerweise .bss
int globalVarNone;              // automatisch 0, typischerweise .bss
int globalVar2 = 43654789;      // typischerweise .data
static int globalStatic = 5;    // statische Speicherdauer, internal linkage
const int globalConst = 3;      // konstant, typischerweise .rodata

void foo();

int main(int argc, char **argv) {

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", tea::PROJECT_NAME);

    /* INSERT YOUR CODE HERE */

    /* Teil 1 - 2*/
    fmt::println("\nTeil 1");
    fmt::println("[main] globalVar = {} (Adresse: {})", globalVar, fmt::ptr(&globalVar));
    fmt::println("[main] globalVar0 = {} (Adresse: {})", globalVar0, fmt::ptr(&globalVar0));
    fmt::println("[main] globalVarNone = {} (Adresse: {})", globalVarNone, fmt::ptr(&globalVarNone));
    fmt::println("[main] globalVar2 = {} (Adresse: {})", globalVar2, fmt::ptr(&globalVar2));
    fmt::println("[main] globalStatic = {} (Adresse: {})", globalStatic, fmt::ptr(&globalStatic));
    fmt::println("[main] globalConst = {} (Adresse: {})", globalConst, fmt::ptr(&globalConst));


    /*Teil 2*/
    fmt::println("\n\nTeil 2");
    int localVar = 2;
    static int localVarStatic = 2;
    const int localVarConst = 2;
    fmt::println("[main] localVar = {} (Adresse: {})", localVar, fmt::ptr(&localVar));
    fmt::println("[main] localVarStatic = {} (Adresse: {})", localVarStatic, fmt::ptr(&localVarStatic));
    fmt::println("[main] localVarConst = {} (Adresse: {})", localVarConst, fmt::ptr(&localVarConst));

    /*Teil 3*/
    fmt::println("\n\nTeil 3");
    /*
     * *heapVar:
     *   Der Wert des dynamisch erzeugten int -> 3
     *
     * heapVar:
     *   Die Adresse des dynamisch erzeugten int auf dem Heap
     *
     * &heapVar:
     *   Die Adresse der Pointer-Variable selbst.
     *   heapVar ist eine lokale Variable und liegt typischerweise
     *   auf dem Stack.
     * Quelle: ChatGPT
     */
    int* heapVar = new int(3);
    fmt::print("[main] heapVar = {} (Adresse: {})", *heapVar, fmt::ptr(heapVar));
    /*
     * Optional interessant für den Vergleich:
     * Hier sieht man die Adresse der Pointer-Variable selbst.
     */
    fmt::println("[main] Pointervariable heapVar selbst liegt bei: {}", fmt::ptr(&heapVar));
    delete heapVar;
    /*
     * Nach delete zeigt der alte Pointer auf keinen gültigen
     * int mehr. Daher setzen wir ihn vorsichtshalber auf nullptr.
     */
    heapVar = nullptr;
    
    /*Teil 4*/
    fmt::println("\n\nTeil 4");
    foo();
    fmt::println("Adresse von foo: {}\n", fmt::ptr(&foo));

    /* ========================================================
    * Zusatz: Fazit
    * ========================================================
    */

    fmt::println("\n\nFazit");

    fmt::println(
        "Der Arbeitsspeicher eines Programms ist schematisch in verschiedene "
        "Bereiche des virtuellen Adressraums aufgeteilt."
    );

    fmt::println(
        "Das .text-Segment befindet sich typischerweise bei niedrigeren Adressen "
        "und enthält den ausführbaren Programmcode, zum Beispiel main() und foo()."
    );

    fmt::println(
        "Das .data-Segment enthält globale und statische Variablen, die bereits "
        "mit einem Wert initialisiert wurden, zum Beispiel globalVar, globalVar2, "
        "globalStatic und localVarStatic."
    );

    fmt::println(
        "Das .bss-Segment enthält globale und statische Variablen, die nicht "
        "explizit initialisiert oder mit 0 initialisiert wurden. "
        "Diese Variablen werden beim Programmstart mit 0 initialisiert."
    );

    fmt::println(
        "Konstante Daten wie globalConst befinden sich typischerweise in einem "
        "nur lesbaren Speicherbereich, beispielsweise .rodata."
    );

    fmt::println(
        "Der Heap dient zur dynamischen Speicherverwaltung. Speicher, der mit "
        "new reserviert wird, liegt typischerweise im Heap und muss später mit "
        "delete wieder freigegeben werden."
    );

    fmt::println(
        "Der Heap wächst im vereinfachten Speicherbild typischerweise in Richtung "
        "höherer Speicheradressen."
    );

    fmt::println(
        "Der Stack befindet sich typischerweise im Bereich hoher Adressen. "
        "Dort liegen unter anderem normale lokale Variablen und Informationen "
        "zu Funktionsaufrufen."
    );

    fmt::println(
        "Der Stack wächst im vereinfachten Speicherbild typischerweise in Richtung "
        "niedrigerer Speicheradressen."
    );

    fmt::println(
        "Eine lokale static-Variable wie localVarStatic ist eine Ausnahme: "
        "Obwohl sie innerhalb einer Funktion deklariert wird, besitzt sie statische "
        "Speicherdauer und liegt daher typischerweise nicht auf dem Stack."
    );

    fmt::println(
        "Stack und Heap müssen unterschieden werden, da Stack-Speicher automatisch "
        "verwaltet wird, während dynamisch mit new reservierter Heap-Speicher "
        "explizit mit delete freigegeben werden muss."
    );

    fmt::println(
        "Zeiger speichern Speicheradressen und ermöglichen dadurch den Zugriff "
        "auf Objekte in anderen Speicherbereichen. Die lokale Pointervariable "
        "heapVar liegt beispielsweise typischerweise auf dem Stack, während der "
        "in heapVar gespeicherte Wert auf den mit new erzeugten int im Heap zeigt."
    );

    fmt::println(
        "Die angezeigten Speicheradressen sind virtuelle Adressen. Ihre absoluten "
        "Werte können sich zwischen verschiedenen Programmstarts ändern."
    );


    /* ========================================================
     * Skizze des Arbeitsspeichers
     * ========================================================
     */

    fmt::print(R"(

    Schematische Darstellung des Arbeitsspeichers:

            höhere Adressen
        +---------------------------+
        |           Stack           |
        |---------------------------|
        | localVar                  |
        | localVarConst             |
        | heapVar (Pointer)         |
        | Funktionsaufrufe          |
        | ...                       |
        +---------------------------+
                |
                |
                v

        +---------------------------+
        |           Heap            |
        |---------------------------|
        | *heapVar = 3              |
        | durch new reserviert      |
        | durch delete freigegeben  |
        +---------------------------+

        +---------------------------+
        |      .bss / .data         |
        |---------------------------|
        | globalVar                 |
        | globalVar0                |
        | globalVarNone             |
        | globalVar2                |
        | globalStatic              |
        | localVarStatic            |
        +---------------------------+

        +---------------------------+
        |          .rodata          |
        |---------------------------|
        | globalConst               |
        | weitere Konstanten        |
        +---------------------------+

        +---------------------------+
        |           .text           |
        |---------------------------|
        | main()                    |
        | foo()                     |
        | weiterer Programmcode     |
        +---------------------------+
            niedrigere Adressen

    )");
    fmt::println("Quelle Fazit: ChatGPT");
    fmt::println("BSS stands for “Block Started by Symbol“. It is the traditional name for the memory section that typically contains global or static variables that are zero-initialized or not explicitly initialized.");
    fmt::println("RODATA stands for “Read-Only Data”. It typically contains constants that should not be modified.");

    return 0; /* exit gracefully*/
}

void foo(){
        fmt::println("Hello from foo!");
    }