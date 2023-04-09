# Projet CSVtoJSONorYAML
Ce projet est un convertisseur de données CSV vers les formats JSON ou YAML. Il a été développé par Alexandre REVILLON et Arthur DUPIRE.

# Description
Le programme lit un fichier CSV contenant des informations sur des membres et génère un fichier JSON ou YAML avec ces informations. Le fichier CSV doit être situé dans le répertoire ./includes/ et nommé csrankings.csv. Les données sont filtrées et affichées en fonction des paramètres spécifiés lors de l'exécution du programme.


# Réalisations et Fonctions

Dans ce projet, nous avons développé un programme permettant de convertir un fichier CSV en formats JSON ou YAML. Les données du fichier CSV sont filtrées et affichées en fonction des paramètres spécifiés lors de l'exécution du programme. Voici une liste des fonctions clés du programme et leur utilité :

- `main()` : Fonction principale qui gère les arguments de la ligne de commande et appelle la fonction `read_csv()` avec les paramètres appropriés.
- `trim_unwanted_chars()` : Supprime les caractères indésirables d'une chaîne de caractères.
- `write_output()` : Écrit les différentes informations dans le fichier de sortie en fonction des paramètres spécifiés. Prend en charge les formats JSON et YAML.
- `open_csv_file()` : Ouvre le fichier CSV et vérifie s'il a été correctement ouvert.
- `close_output_file()` : Ferme les fichiers de sortie après avoir écrit la chaîne finale.
- `prepare_output_file()` : Prépare le fichier de sortie en fonction des paramètres donnés et écrit les informations d'en-tête.
- `should_print_member()` : Vérifie si un membre doit être affiché ou non en fonction des paramètres donnés.
- `process_line()` : Traite une ligne du fichier CSV, extrait les informations et les stocke dans une structure Membre.
- `read_csv()` : Lit le fichier CSV et affiche ou écrit dans un fichier JSON ou YAML la sortie en fonction des paramètres.

Le programme prend en charge plusieurs options pour personnaliser le filtrage des données, le format de sortie et le nom du fichier de sortie, comme expliqué dans la section "Utilisation" du README.


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
