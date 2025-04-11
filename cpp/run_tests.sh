#!/bin/bash

# Vérifier qu'on a bien reçu deux arguments
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <executable_path> <output_file>"
    exit 1
fi

EXECUTABLE=$1
OUTPUT_FILE=$2
THREADS_LIST="1 2 4 8 16 32"
TOTAL_TESTS=$(echo "$THREADS_LIST" | wc -w)  # Nombre total de tests
CURRENT_TEST=1  # Initialiser le compteur de tests

# Effacer les anciens résultats
echo "Threads,ExecutionTime" > "$OUTPUT_FILE"

# Couleur violet
VIOLET='\033[0;35m'
NC='\033[0m'  # Pas de couleur (reset)

# Exécuter les tests
for threads in $THREADS_LIST; do
    # Calculer le pourcentage d'avancement
    PERCENT=$(( (CURRENT_TEST * 100) / TOTAL_TESTS ))
    
    # Afficher l'avancement avec texte violet
    echo -e "${VIOLET}[${PERCENT}%] Running with $threads threads...${NC}"
    
    # Exécuter et mesurer le temps d'exécution
    START_TIME=$(date +%s.%N)
    
    # Assure-toi que l'argument --force est passé correctement
    $EXECUTABLE $threads --force
    
    END_TIME=$(date +%s.%N)

    # Calcul du temps écoulé
    EXECUTION_TIME=$(echo "$END_TIME - $START_TIME" | bc)
    
    # Enregistrer le résultat
    echo "$threads,$EXECUTION_TIME" >> "$OUTPUT_FILE"
    echo "-----------------------------"
    
    # Incrémenter le compteur de tests
    CURRENT_TEST=$((CURRENT_TEST + 1))
done

echo "Tests done. Results in $OUTPUT_FILE."

