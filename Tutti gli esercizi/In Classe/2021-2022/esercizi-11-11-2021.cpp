/*
ESERCIZIO. Definire una superclasse ContoBancario e due sue sottoclassi ContoCorrente e ContoDiRisparmio che soddisfano le seguenti specifiche:

1) Ogni ContoBancario è caratterizzato da un saldo e rende disponibili due funzionalità di deposito e prelievo: double deposita(double) e double preleva(double) che ritornano il saldo aggiornato dopo l’operazione di deposito/prelievo.
2) Ogni ContoCorrente è caratterizzato anche da una spesa fissa uguale per ogni ContoCorrente che deve essere detratta dal saldo ad ogni operazione di deposito e prelievo.
3) Ogni ContoDiRisparmio deve avere un saldo non negativo e pertanto non tutti i prelievi sono permessi; d’altra parte, le operazioni di deposito e prelievo non comportano costi aggiuntivi e restituiscono il saldo aggiornato.
4) Si definisca inoltre una classe ContoArancio derivata da ContoDiRisparmio. La classe ContoArancio deve avere un ContoCorrente di appoggio: quando si deposita una somma S su un ContoArancio, S viene prelevata dal ContoCorrente di appoggio; d’altra parte, i prelievi di una somma S da un ContoArancio vengono depositati nel ContoCorrente di appoggio.
*/


#include<iostream>

int main() {
  ContoCorrente cc(2000);
  ContoArancio ca(cc,1500);
  ca.deposita(350); ca.preleva(400); cc.preleva(150); 
  std::cout << cc.getSaldo() << std::endl; // stampa: 1897
  std::cout << ca.getSaldo() << std::endl; // stampa: 1450
}

