Nume:Anton Stefan

Grupă:311CC

# Tema 1 SD

Organizare
-
1. Tema a fost realizata folosind liste dublu inlantuite, lucru cu pointerii si cu memoria, si concepte matematice de baza.

***Detalii Generale:***
* A fost creata cate o functie pentru fiecare filtru/statistica ceruta. Totodata, implementarea listei dublu inlantuite a fost creata intr-un fisier separat, pentru a oferi modularizare codului. Fiecare functie a fost declarata intr-un fisier header inainte de o implementa propriu-zis.
* Tema a fost una interesanta pentru o introducere in calcului filtrelor.
* Implementarea este una naiva, neavand foarte multe optimizari, insa timpul de rulare pe teste este unul decent.

***Observatii enunt:***
* La partea de completare, se putea formula mai bine partea de calcul al coeficientului C, deoarece se intelegea ca se iau capetele din dreapta din ambele intervale.

Implementare
-

* Din pacate tema nu a fost implementata integral.
* Pentru functia de eliminare a exceptiilor mi-am populat o lista noua cu elementele care respectau constrangerile din enunt, am dezalocat lista initiala, si am schimbat referinta head-ului meu sa pointeze catre head-ul noii liste create
* Pentru functia de filtrare mediana, mi-am creat, din nou, o noua lista, in care adaug elementul median din fiecare interval. Pentru aceasta, mi-am format noi liste continand doar cele 5 elemente, pe care le-am sortat, ca mai apoi sa iau elementul din centru.
* Asemanator am lucrat si la cea cu medii aritmetice, numai ca acum am calculat media intervalului.
* Pentru functia de uniformizare in timp, am verificat diferenta dintre 2 timestampuri consecutive, ca mai apoi sa modific acel timestamp care nu se incadra in acel interval.
* Pentru partea de statistica, am sortat intreaga lista, ca mai apoi sa iau primul numar din interval pe care l-am folosit ca prim capat de interval, pe care mai apoi il incrementez cu acel range dat de ei.

