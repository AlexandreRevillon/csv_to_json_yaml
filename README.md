# Mini-Projet Test & Maintenance

> Ce document décrit le sujet pour le mini-projet de cours _Tests et Maintenance_ en ISA4. Le travail est à faire en binôme et doit être complètement fourni dans un dépôt `gitlab` de préférence sur celui de l'[université](gitlab.univ-lille.fr/) ou sur [gitlab.com](https://gitlab.com). 

## Contexte

L’objectif est de faire un petit programme simple de traitement d’un fichier `CSV` qui contient une liste de chercheurs et d’en fournir un sous-ensemble au format `YAML` ou `JSON`. Ce mini-projet visera à utiliser toutes les techniques de tests, maintenance et _clean code_ vues en cours.

## Données sources

Le fichier de données `csrankings.csv` vient du site [CSRankings: Computer Science Rankings](https://csrankings.org)] qui cherche à classer les chercheurs et institutions du monde en fonction de leur thématiques de recherche. Le site propose un moteur de recherche mais fournit également les données brutes sous la forme d’un tableau contenant les colonnes suivantes:

```csv
name,affiliation,homepage,scholarid
```

où:
-  `name` représente le chercheur sous la forme _Prénom Nom_
-  `affiliation` représente  l’institut qui héberge le chercheur
-  `homepage` la page par défaut du chercheur
-  `scholarid` son identifiant sur le site [Google Scholar](https://scholar.google.fr/).  Par exemple un chercheur ayant l’identifiant `pzwDiKgAAAAJ` aura comme page sur google scholar la page suivante [François Boulier - Google Scholar](https://scholar.google.fr/citations?user=pzwDiKgAAAAJ). Au maximum l’identifiant fait 13 caractères (12 caractères dans le cas classique et 13 caractères lorsqu’il n’y pas de profil google scholar dans ce cas l’identifiant est `NOSCHOLARPAGE`). 

## Programme à réaliser

Il s’agit de réaliser un programme (normalement relativement court) qui lit un fichier `CSV` provenant de csrankings.org, de faire des opérations simples dessus (recherche et/ou filtrage) et de fournir le résultat au format `YAML` ou `JSON` suivant la commande entrée par l'utilisateur. La liste des options possibles est la suivante:

- `-t [yaml, json]`: spécifie le format de sortie. Si cette option n'est pas utilisée, la valeur par défaut est `yaml`.
- `-o [nom_fichier]`: permet d'enregistrer le résultat dans le fichier spécifié. Si cette option n'est pas utilisée, le programme affiche le résultat sur la sortie standard. 
- `-f [nahs]`: permet de sélectionner les informations à afficher par chercheur (`n` pour le nom, `a` pour l'affiliation, `h` pour la homepage, `s` pour le profil google scholar). Plusieurs filtres peuvent être utilisés par exemple `-f n -f a` ou `-f na` doivent permettre d'afficher les noms et les affiliations des chercheurs.
- `-s "Lieu Affiliation`: permet de rechercher uniquement les chercheurs affiliés à une institution. Les guillements sont à utiliser uniquement quand l'affiliation contient des espaces comme par exemple `-s "University of Hildesheim"`.

À supposer que votre programme s'appelle `projet`. La commande `./projet -t yaml -f ns -s "University of Hildesheim"` devrait fournir le résultat suivant:

```yaml
--- 
affiliation: "University of Hildesheim"
members: 
    -
    name: "Klaus Schmid"
    scholar: dK9g6a4AAAAJ
  -
    name: "Klaus-Dieter Althoff"
    scholar: i4hdvtYAAAAJ
  -
    name: "Lars Schmidt-Thieme"
    scholar: l3taTdYAAAAJ
```

## Méthodologie 

Au delà de la réalisation du programme, il faudra mettre en application les différentes méthodes vues en cours (TDD,  Tests, Code…) . Plus spécifiquement, l’évaluation prendra en compte les éléments suivants:

- [ ] mise en place des tests unitaires, tests d’intégration
- [ ] couverture de code
- [ ] compilation / build automatique
- [ ] respect des principes de clean code (nom de variables / fonctions / classes, principes DRY, KISS…)
- [ ] mise en place d’un pipeline d’intégration continue sous gitlab
- [ ] mise en place de la validation des commits via `pre-commit`
- [ ] indentation du code, validation des fichiers  (`yamllint`) …
- [ ] …

Ce projet est à réaliser en `C` en se basant sur le TP vu à la première séance.

## Déliverables

Il faudra donner accès à votre dépôt `GIT` qui contiendra le code du programme principal, les tests, le moyen de compiler votre programme et les fichiers de configuration `gitlab-ci.yml`, `.pre-commit-config.yaml`… et un fichier `README.md` qui expliquera ce que vous avez réalisé. La date limite de rendu est le dimanche 9 avril à 23:59. Assurez-vous que votre enseignant à accès à votre dépot git.

