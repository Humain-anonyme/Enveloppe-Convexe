Nom 1 : TEKPA                                   
Prénom : Max
Groupe TD : 4
Groupe TP : 7
       
Nom 2 : TRAN
Prénom : Thien-Loc
Groupe TD : 
Groupe TP : 7




                        Fonctionnement du Projet : Enveloppe convexe dans le plan


Pour compiler le programme, décompressez l'archive et ouvrez un terminal dans le dossier décompressé. 
Tapez la commande suivante dans la ligne de commande :

clang -std=c17 -Wall -Wfatal-errors convexe.c -o conv -lMLV

Après compitalion, Pour exécuter le programme avec l'option de sélection de points au clic de souris, tapez :

./conv

Pour exécuter le programme avec l'option de génération aléatoire de points, tapez :

./conv -r

Après avoir choisi l'option souhaitée, un message s'affichera dans votre terminal 
vous demandant le nombre maximal de points que vous souhaitez tracer. 
Entrez une valeur et la fenêtre s'ouvrira automatiquement. 

Pour fermer la fenêtre à la fin du programme, appuyez sur la touche q.

Les points générés aléatoirement avec l'option '-r' ne sont pas générés de manière contrôlée.
Nous avons essayé de mettre en place une option qui permet à l'utilisateur de fermer la fenêtre même en cours d'exécution, 
mais nous n'avons pas réussi à la faire fonctionner correctement. 
Par ailleurs, nous n'avons pas réussi à mettre en place l'option permettant l'affichage terminal. 
En général, nous n'avons pas réussi à implémenter toutes les options concernant l'environnement graphique. 
Pour l'instant, seules les options décrites ci-dessus fonctionnent."















