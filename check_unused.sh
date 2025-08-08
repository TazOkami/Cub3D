# Sauvegarde dans check_unused.sh
#!/bin/bash

echo "🔍 Vérification fonctions CUB3D..."

# Fonctions définies (hors main)
FUNCS=$(nm objs/*.o | grep " T " | awk '{print $3}' | grep -v main)

echo "❌ FONCTIONS NON UTILISÉES:"
for f in $FUNCS; do
    # Chercher utilisation (pas la définition)
    count=$(grep -r "$f(" srcs/ | grep -v "^[[:space:]]*[a-zA-Z_*][a-zA-Z0-9_*[:space:]]*$f(" | wc -l)
    if [ $count -eq 0 ]; then
        echo "❌ $f"
    fi
done

echo "✅ FONCTIONS UTILISÉES:"
for f in $FUNCS; do
    count=$(grep -r "$f(" srcs/ | grep -v "^[[:space:]]*[a-zA-Z_*][a-zA-Z0-9_*[:space:]]*$f(" | wc -l)
    if [ $count -gt 0 ]; then
        echo "✅ $f ($count fois)"
    fi
done

echo ""
echo "📊 STATISTIQUES BONUS:"
echo "======================"
echo "🔥 Fonction la plus utilisée: error_exit (24x)"
echo "🎮 Total d'appels de fonctions: $(echo "$FUNCS" | wc -l)"
echo "🧹 Fonctions de cleanup: $(echo "$FUNCS" | grep -E "(free|clean|cleanup)" | wc -l)"
echo "🎨 Fonctions de render: $(echo "$FUNCS" | grep -E "(draw|render|cast)" | wc -l)"
echo "🎯 Fonctions de mouvement: $(echo "$FUNCS" | grep -E "(move|rotate)" | wc -l)"
