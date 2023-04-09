# Projet CSVtoJSONorYAML
Ce projet est un convertisseur de données CSV vers les formats JSON ou YAML. Il a été développé par Alexandre REVILLON et Arthur DUPIRE.

# Description
Le programme lit un fichier CSV contenant des informations sur des membres et génère un fichier JSON ou YAML avec ces informations. Le fichier CSV doit être situé dans le répertoire ./includes/ et nommé csrankings.csv. Les données sont filtrées et affichées en fonction des paramètres spécifiés lors de l'exécution du programme.

#Compilation
Pour compiler le projet, utilisez la commande suivante :

- Pour compiler que le projet sans les tests:

``` bash
make main
```

- Pour compiler que les tests:

```bash
make tests
```

- Pour compiler le projet ainsi que les tests:

```bash
make
```

# Utilisation
Voici comment exécuter le programme :

```
./convert_csrankings [options]
```

- ```-t <format>```: Spécifie le format de sortie. Les valeurs possibles sont yaml et json. Par défaut, le format est YAML.
- ```-o <nom_du_fichier>```: Active l'enregistrement des données dans un fichier. Le fichier sera sauvegardé avec le nom spécifié et l'extension appropriée (.json ou .yaml).
- ```-f <flags>``` : Filtre les colonnes à afficher ou enregistrer. Les valeurs possibles sont n (nom), a (affiliation), h (page d'accueil) et s (ID Scholar). Par exemple, ```-f nas``` affichera ou enregistrera seulement les colonnes Nom, Affiliation et ID Scholar.
- ```-s <affiliation>``` : Filtre les membres par affiliation. Affiche ou enregistre seulement les membres ayant l'affiliation spécifiée.

# Exemples d'utilisation
- Convertir le CSV en JSON et afficher le résultat :
```bash
./convert_csrankings -t json
```


- Convertir le CSV en YAML, filtrer les colonnes et enregistrer le résultat dans un fichier :
```bash
./convert_csrankings -t yaml -f nas -o resultat
```


- Convertir le CSV en JSON, filtrer les membres par affiliation et afficher le résultat :
```bash
./convert_csrankings -t json -s "University of Example"
```
