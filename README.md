# Rhino ITA:

## DIPENDENZE
Per funzionare il programma ha bisogno delle seguenti librerie:

* Qt5 (ma anche le 4 potrebbero funzionare)
* QWT (testato con le qwt-6.1.5)
* Root (testato con root_v6.22.02.Linux-ubuntu18-x86_64-gcc7.5.tar.gz)

## INSTALLAZIONE

1. Clonati il progetto in locale 
2. Crea una cartella 'build' nella cartella principale del progetto ed entra
3. cmake

## ELEMENTI DELLLA GUI
### BARRA IN ALTO
File:

* Load File: apre una finestra per la selezione di un file di spettro da analizzare. I tipi permessi sono i file di tasso e i chn.
* Save Fit: apre una finestra per scegliere un nuovo file di testo su cui salvare le righe della tabella che si deciso di salvare (vedere resto del manuale). Le righe verranno salvata in ordine crescente di energia.
* Quit: esce dal programma.

Help:

* Contents: apre una finestra con alcune informazioni sul programma.
* Manual: apre una finestra con questo manuale.

### PARTE DI DESTRA
Tasti:

* E: cancella i marker inseriti nello spettro
* W: esegue il fit (o l'integrale scelto tramite cursore).
* S: effettuato un fit, marca la riga (o le righe) corrispendonte come da salvare. Equivale a cliccare sulla check box della colonna Save nella tabella. Se gia' selezionate, il marker viene tolto.
* A: scorre lo spettro verso sinistra.
* D: scorre lo spettro verso destra. 
* E: sovrappone sul fit il grafico delle singole gaussiane usate per fittare i picchi.

Tab bar:

* Fit options:

    * Fit Method: permette di scegliere il metodo di fit da utilizzare.
    * Background Fit: permette di scegliere quale funzione di fit utilizzare per il background (Best non e' per ora implementato).
    
* Calibrate: Permette di calibrare uno spettro e di effettuare un rebinning (vedere le apposite sezioni per le due procedure).
* Tools:

    * Print Histo: permette di stampare cio' che compare nel canvas dello spettro (quindi anche fit visibili al momento) o creare un'immagine di tipo pdf.
    * Save image: permette di salvare cio' che compare nel canvas dello spettro nei piu' comuni formati di immagini (jpeg, png, bmp).
    * C: permette di aprire la tavoletta dei colori per poter scegliere con quale colore rappresentare l'elemento scelta nel menu a tendina adiacente.

* Indicatori:

    * Number of channels: indica il numero di canali letti del file di spettro caricato.
    * Live Time: legge il live time dello spettro caricato. Il valore viene usato per il calcolo dei conteggi al secondo.
 

### TABELLA:

* Mean: valore medio della gaussiana usata per fittare il picco
* Mean Err: errore sul valore medio
* FWHM: FWHM della gaussiana usata per fittare il picco
* FWHM Err: errore sulla FWHM
* Net Area: area della gaussiana (sottraendo il valore del fondo)
* Net Area Err: errore sulla Net Area
* Counts/s: Net Area diviso il Live Time
* Counts/s Err: errore sui Counts/s
* Save: selezionabile per salvare la riga corrispondente nel file di testo. 
* Red Chi Sqr: chi quadrato ridotto del fit effettuato
* Bg Fit: tipo di funzione scelta per fittare il fondo (0=lineare, 1=quadratica, 2=sigmoide)


### CANVAS DELLO SPETTRO:
Muoversi nello spettro:

* Rotella del mouse: zoom-in, zoom-out
* Tasto rotella con trascinamento: seleziona il range energetico da zoomare (le y non sono importanti)
* Frecce sinistra e destra della GUI per muoversi a sinistra e destra (in alternativa tasto A e tasto D della tua tastiera)
* Tasto destro del mouse: zoom-out completo

Eseguire i fit:
* Tasto sinistro: posiziona un marker all'energia (o canale) puntato.
* Tasto W della GUI o W della tastiera effettua il fit (o l'integrale). Vedere la sezione FIT E INTEGRALI del manuale per avere piu' informazioni

### FIT E INTEGRALI:

* Fit singolo picco: posizionare due marker a sinistra e a destra del picco (o viceversa), POI selezionare il picco posizionando un marker al suo centro. A quel punto premere il tasto di fit.
* Fit multiplo di picchi: posizionare due marker a sinistra e a destra del gruppo di picchi che si vuole fittare (solo due marker non due per ciascun picco), POI selezionare i picchi posizionando un marker su ognuno di essi. A quel punto premere il tasto di fit.
* Aggiungere un picco: se si effettua un fit di una finestra energetica e ci si accorge che in quella finestra era presente uno o piu' picchi che non sono stati selezionati per essere fittati e' possibile aggiungerli successivamente. Per farlo bisogno posizionare un marker sul picco da aggiungere al fit (l'importante che questo picco cada comunque all'interno dei due marker iniziali) e cliccare nuovamente il tasto di fit. Ripetere questa azione per ogni picco da aggiungere in quanto non e' possibile aggiungere piu' di un picco in un colpo solo al fit gia' effettuato.
* Integrale: posizionare due marker come limite inferiore e limite superiore della zona di cui si vuole sapre il numero di conteggi. Tale valore verra' inserito nella colonna Net Area anche se ovviemente non e' stato sottratto alcun fondo per tale calcolo.
* Righe tabella: ogni picco fittato e ogni integrale generera' all'inizio della tabella una riga e spostera' i fit precedenti verso il basso. L'ultimo fit/integrale eseguito (in termini di tempo) risultara' quindi sempre all'inizio della tabella e sara' evidenziato da uno sfondo azzurro nella colonna Save. Se si effettua quindi un fit multiplo di picchi verranno generate tot righe all'inizio della tabella tutte con la cella Save in azzurro. Le righe evidenziate in tale modo possono essere salvate digitando il tasto S della GUI o il tasto S della tastiera. Risultera' possibile comunque salvare o togliere dal salvataggio anche le righe precedentemente eseguite andando a cliccare direttametne sulla loro check box.
* Premendo il tasto E della GUI o E della tastiera si possono visualizzare sovrapposte al fit le curve delle gaussiane usate per fittare lo spettro. Torna utile in caso di picchi molto ravvicinati.

### REBINNING
Per effetturare un rebinning dello spettro e' sufficiente spostarsi nel tab "Calibrate" (sezione destra della GUI), inserire il numero di bin da raggruppare e schiacciare il pulsante "B" della GUI.

### CALIBRAZIONE
E' possibile ricalibrare lo spettro visualizzato. Per fare cio' spostatevi prima nel tab "Calibrate". 
Posizionate un marker nel punto dello spettro di cui conoscete l'energia. Verra' visualizzato di conseguenza nella casella "Channel" il numero di canale corrispondente. Nella casella di fianco inserite il valore di energia e premete il tasto "Add Point". Nel menu a tendina verra' visualizzato il punto di calibrazione che avete appena creato.
Quando saranno stati creati con il procedimento appena indicato almeno due punti, sara' possibile premere il tasto "Calibrate" per effettuare la calibrazione dello spettro.
In caso si volesse rieffettuare tale procedura con altri valori premere il tasto "Clear All" e riniziare.


### ALTRE COSE DA DIRE:
* Se si carica un file, si esegue un fit e poi si carica un altro file, la tabella non viene cancellata ma le righe rimarranno. Cio' e' voluto perche' da la possibilita' di inserire nella stessa tabella (e nello stesso file di salvataggio) picchi di spettri diversi. Stara a voi poi ricordarvi la provenienza di ciascuno.

### BACHI (e fastidi) GIA' INDIVIDUATI:

* Tabella, colonna Save: la cella Save di ogni riga e' editabile, ovvero ci si puo' scrivere dentro. Molto fastidioso se dopo aver salvato ci si vuole spostare con i tasti A e D della tastiera. Ovviamente succede solo quando si va a cliccare con il mouse sulla checkbox
* Fit e marker: non esiste la possibilita' di annullare un fit. Per quanto questo generi semplicemente una o piu' righe nella tabella che possono anche non essere salvate posso capire il fastidio della cosa.
* Rebinning: quando si esegue un rebinnaggio di uno spettro, l'ultimo fit o integrale eseguito non viene cancellato, questo fa si che ci si ritrovi con uno fit fluttuante o immerso nello spettro.
* Tanti altri: e' possibile che se esguite delle azioni nell'ordine sbagliato compaiano altri bachi e il programma possa anche bloccarsi. Segnalatemi questi comportamenti anomali in modo da eliminarli nelle prossime release.
