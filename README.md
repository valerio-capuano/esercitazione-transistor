# Caratterizzazione di un transistor (JFET)

Analisi dati e fit delle curve caratteristiche corrente-tensione $I(V_{DS})$ di un transistor al variare della tensione di gate $V_g$, realizzata con **ROOT** (CERN).

## Descrizione dell'analisi
Lo script `fit.cpp` legge 6 dataset sperimentali (`dati_0.txt` – `dati_5.txt`) corrispondenti a diverse tensioni di gate ($V_g = 0,\, 0.2,\, 0.4,\, 0.6,\, 0.8,\, 1.5\text{ V}$) e confronta due modelli di fit per ciascuna curva:

* **Modello esponenziale:** $I(V_{DS}) = p_0 \left(1 - e^{p_1 V_{DS}}\right)$
* **Modello a tangente iperbolica:** $I(V_{DS}) = p_0 \tanh(p_1 V_{DS})(1 + p_2 V_{DS})$

I parametri estratti dai fit vengono salvati in `parametri_exp.txt` e `parametri_tanh.txt`, insieme ai grafici sovrapposti in formato vettoriale (`fit_exp.pdf` e `fit_tanh.pdf`).

## Struttura del repository
* `fit.cpp` — Macro C++ per ROOT che esegue la lettura dei dati, i fit e il salvataggio dei grafici.
* `dati_0.txt` ... `dati_5.txt` — Dataset sperimentali ($V_{DS}$, $\sigma_{V}$, $I$, $\sigma_{I}$).
* `parametri_exp.txt`, `parametri_tanh.txt` — Parametri ottimali estratti dai fit per ogni $V_g$.
* `fit_exp.pdf`, `fit_tanh.pdf` — Grafici delle curve caratteristiche fittate.

## Requisiti
* **ROOT** (CERN)

## Come eseguire il codice
```bash
root -l -q fit.cpp
```