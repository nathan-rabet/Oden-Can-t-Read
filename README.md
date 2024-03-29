# Oden Can't Read (OCR)

Il s'agit d'un programme de détection optique de caractères (ou *optical character recognition*, OCR) réalisé lors de notre troisième semestre à EPITA.
![Segmentation](https://user-images.githubusercontent.com/13369175/102380416-2e6f7e80-3fc8-11eb-8bc7-1ab05dbc7ea6.png)


# Exécution de l'interface graphique
![Interface OCR](https://user-images.githubusercontent.com/13369175/102357792-032c6580-3faf-11eb-9265-53ef588f7070.png)

Pour ouvrir l'interface graphique :

- Faites `make interface` ou tout simplement `make` dans un terminal.

- Éxecutez le fichier `mainINTERFACE.o`

# Entrainement des réseaux de neurones multicouches
Aucun réseau n'est actuellement entrainé.

Pour lui permettre de détecter correctement les caractrères, il faut le faire !

- Faites `make train` dans un terminal.

- Lancez le fichier `mainTRAIN.o`

## Utilisation de l'outil d'entrainement des réseaux
![Dashboard](https://user-images.githubusercontent.com/13369175/102359802-88187e80-3fb1-11eb-97e8-5c46c7185737.png)

Une fois le fichier `mainTRAIN.o` lancé, vous pouvez faire plusieurs actions :
### Graphique de progression
Le tableau de progression accessible en appuyant sur la touche <kbd>Enter</kbd>.

Il permet de suivre en direct l'avancement de l'apprentissage supervisé.

Pour actualiser les barres de progression, il faut appuyer de nouveau sur la touche <kbd>Enter</kbd>.

### Test de fiabilité
![Accuracy test](https://user-images.githubusercontent.com/13369175/102369282-0e39c280-3fbc-11eb-99d1-65359c1f4897.png)
Si vous souhaitez tester vos réseaux de neurones alors qu'ils sont toujours en train d'apprendre, vous pouvez susprendre le processus et lancer un test sur **1000 images aléatoires** en appuyant sur <kbd>t</kbd>.

### Sauvegarde des réseaux de neurones
![image](https://user-images.githubusercontent.com/13369175/102371086-1c88de00-3fbe-11eb-957c-12482b4ae7a6.png)
Les réseaux sont de base enregistrés automatiquement à chaque *batch* au format JSON vers `data/networks/~training`.

Cepdendant, si vous souhaitez les enregistrer manuellement, il vous suffit d'appuyer sur <kbd>s</kbd>.

## Génération d'une banque de donnée
La banque de donnée fournie dans `data/dataset` n'est qu'un échantillon de test et n'est donc pas très efficiente pour un apprentisage correct.
Pour en générer une nouvelle, exécutez le script [*Processing*](https://processing.org) du nom de `danielGEN.pde` situé dans `data/dataset`
