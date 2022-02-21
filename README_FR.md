# PageRank Implementation in C

## Description
Implémentation de l’algorithme PageRank. Utilisé comme travail pratique individuel pour le cours *Calcul Haute Performance* donné à l’UVSQ-ISTY, diplôme d’ingénieur en informatique.

### Dataset format
Ce programme s’exécutera sur tout ensemble de données qui respecte le format de données suivant :
> \# ligne commentée  
> NOEUD_1[TAB]NOEUD_2  
> NOEUD_1[TAB]NOEUD_2  
> NOEUD_1[TAB]NOEUD_2  
> NOEUD_1[TAB]NOEUD_2

NOEUD_x: devrait être un entier concernant le type de donnée uint (entier non signé) qui fait 4 octets.

## Benchmark
Le benchmark est fait en exécutant l’algorithme pagerank sur plusieurs valeurs de facteur de dumping allant de 0 à 1 avec un pas égal à 0,025.  
Le critère de performance est le temps pris pour chaque "run". Les données inscrites sur le fichier de sortie est la moyenne de 10 runs (MAX_AVG_ITER).

### Benchmark output data format
Le fichier de données de sortie de référence aura le format suivant (il s’agit de données d’échantillon) :
> \# damping; time; iters; node; prob  
> 0.000; 0.00000080; 1; 6; 0.142857  
> 0.025; 0.00000110; 4; 1; 0.145243  
> 0.050; 0.00000160; 4; 1; 0.147638  
> 0.075; 0.00000180; 5; 1; 0.150042  
> . . .    
> 0.925; 0.00003570; 149; 5; 0.224650  
> 0.950; 0.00005390; 226; 5; 0.243999  
> 0.975; 0.00010860; 457; 5; 0.287968  
> 1.000; 0.00011870; 500; 6; 0.525783

La 1ère valeur décrit : le facteur d’amortissement choisi pour l’analyse.  
La 2ème valeur décrit : le temps nécessaire à l’algorithme pour trouver la solution ou pour atteindre le maximum d’itérations.  
La 3ème valeur décrit : le nombre d’itérations nécessaires pour converger ou le maximum si ce n’est pas le cas.  
La 4ème valeur décrit : le noeud le plus important trouvé.  
La 5e valeur décrit : la probabilité la plus élevée trouvée (équivalente au noeud le plus important).

## Code
### scripts d'utilités

- **gnuplot_script.gnu**: un script "gnuplot" pour tracer le graphique de performance.
- **run_script.sh**: un script bash qui installe la bibliothèque *gnuplot* si elle n’est pas installée, compile le projet, l’exécute en utilisant le fichier d’entrée (passé en argument) et crée le graphique de performance (*plot.png*).

### programme principale
Il existe 3 versions de compilation différentes :
1. default (utilisé pour produire un résumé simple)
2. debug (utilisé pour les sorties de débogage verbeuses)
3. benchmark (utilisé pour exécuter un benchmark)

## Compilation & Execution
### Compilation
* version 'default' : `make clean && make`
* version 'debug' : `make clean && make debug`
* version 'benchmark' : `make clean && make benchmark`

### Execution
* version 'default' : `./program [filename] [max_iter] [damping_factor]`
* version 'debug' : `./program [filename] [max_iter] [damping_factor]`
* version 'benchmark' : `./benchmark [filename]`

## Extra
Vous pouvez exécuter le script de traçage en utilisant le script gnuplot sur un fichier de données respectant le format de sortie des données de référence : `gnuplot gnuplot_script.gnu`

![](plot.png)
