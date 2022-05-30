# Mini-Projet Test & Maintenance

> Ce document décrit le sujet pour le mini-projet de cours _Tests et Maintenance_ en IS2A4. Le travail est à faire en binôme et doit être complètement fourni dans un dépôt `gitlab`.  

## Contexte

L’objectif est de faire un petit programme simple de traitement d’un fichier `CSV` qui contient une liste de chercheurs et d’en fournir un sous-ensemble au format `YAML`. Ce mini-projet visera à utiliser toutes les techniques de tests, maintenance et _clean code_ vues en cours.

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

Il s’agit de réaliser un programme (normalement relativement court) qui lit un fichier `CSV` provenant de csrankings.org, d’en faire une recherche simple sur l’affiliation et de fournir la liste des chercheurs de cette affiliation qui ont une page [Google Scholar](https://scholar.google.fr). Le format de sortie devra être au format `YAML` sous la forme (en supposant que l’on fasse une recherche sur l’`University of Hildesheim`):

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

On pourra afficher le résultat sur la sortie standard ou dans un fichier (par exemple ici : `University of Hildesheim.yml`). En supposant que votre programme s’appelle projet, on l’utilisera de la manière suivante:

```bash
./projet fichier.csv “Lieu Affiliation”
```

Les `"` seront à utiliser lorsque l’affiliation contient des espaces. Quand il n’y en a pas, on utilisera directement comme pour l’exemple suivant:

```bash
./projet csrankings.csv CRIStAL
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

Ce projet est à réaliser en `C` de préférence mais il peut également être fait en `Java`. Dans ce cas les tests unitaires seront fait avec `jUnit` [Développons en Java - JUnit](https://www.jmdoudoux.fr/java/dej/chap-junit.htm)

## Déliverables

Il faudra donner accès à votre dépôt `GIT` qui contiendra le code du programme principal, les tests, le moyen de compiler votre programme et les fichiers de configuration `gitlab-ci.yml`, `.pre-commit-config.yaml`… et un fichier `README.md` qui expliquera ce que vous avez réalisé. 

