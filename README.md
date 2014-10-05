zhaw_os_linux
=============

zyklischen buffer für prodzuzenten/konsumenten schreiben mit locks
1000 einträge, alle ints
3 threads oroduzieren zufallszahlen
3 threads konsumieren und geben sie aus. 
wenn buffer leer, warten konsumenten 
wenn buffer voll, warten produzenten
gelöst mit funktionen pull get