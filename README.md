## **🌿 PERFECT ! SETUP BRANCHES PERSONNELLES !**

---

## **📋 CRÉATION DES BRANCHES**

### **🎯 TOI (TazOkami) :**
```bash
# Créer et switch sur ta branche
git checkout -b Tazokami
git push -u origin Tazokami

# Vérifier
git branch -a
# * Tazokami
#   main  
#   remotes/origin/Tazokami
#   remotes/origin/main
```

### **👨‍💻 TON PARTNER (Malafont) :**
```bash
# Il doit d'abord clone le repo
git clone https://github.com/TazOkami/Cub3D.git
cd Cub3D

# Puis créer sa branche
git checkout -b Malafont
git push -u origin Malafont
```

---

## **📋 WORKFLOW QUOTIDIEN AVEC VOS BRANCHES**

### **🌅 DÉBUT DE JOURNÉE :**
```bash
# 1. Récupérer les dernières updates
git checkout main
git pull origin main

# 2. Aller sur TA branche
git checkout Tazokami  # ou Malafont pour lui

# 3. Intégrer les changements de main
git merge main

# 4. Récupérer aussi les changements de ton partner
git pull origin Malafont  # toi tu récupères ses trucs
# lui il fait : git pull origin Tazokami
```

### **💾 SAUVEGARDER TON TRAVAIL :**
```bash
# Sur ta branche Tazokami
git add .
git commit -m "✨ Raycasting: Add wall collision detection"
git push origin Tazokami
```

### **🔄 PARTAGER AVEC TON PARTNER :**
```bash
# Mettre tes changements sur main
git checkout main
git merge Tazokami
git push origin main

# Lui signaler sur Discord/Slack :
# "Hey j'ai merge mes trucs sur main, fais un pull !"
```

---

## **📋 RÉPARTITION SUGGÉRÉE**

### **🎮 TazOkami (toi) :**
```bash
# Tes domaines
├── srcs/raycasting/     # Ray algorithm
├── srcs/render/         # MLX rendering  
├── srcs/player/         # Player movement
├── includes/render.h    # Tes headers
```

### **🗺️ Malafont (partner) :**
```bash
# Ses domaines  
├── srcs/parsing/        # Map parsing
├── srcs/validation/     # Input validation
├── srcs/textures/       # Texture loading
├── includes/parsing.h   # Ses headers
```

### **🤝 PARTAGÉ (attention!) :**
```bash
├── srcs/main.c          # Point d'entrée
├── includes/cub3d.h     # Header principal
├── Makefile             # Compilation
```

---

## **📋 COMMANDES UTILES POUR VOS BRANCHES**

### **👀 VOIR CE QUE FAIT TON PARTNER :**
```bash
# Voir ses derniers commits
git log origin/Malafont --oneline -5

# Voir les différences entre vos branches  
git diff Tazokami..Malafont

# Récupérer UN commit spécifique de sa branche
git cherry-pick <commit-hash>
```

### **📊 ÉTAT DES BRANCHES :**
```bash
# Voir toutes les branches
git branch -a

# Voir qui a modifié quoi
git log --graph --oneline --all

# Voir les fichiers modifiés par branche
git diff --name-only main..Tazokami
git diff --name-only main..Malafont
```

---

## **📋 MERGE FINAL (QUAND READY)**

### **🎯 Quand vous voulez combiner vos travaux :**

```bash
# 1. TOI - Merger tes trucs sur main
git checkout main
git pull origin main
git merge Tazokami
git push origin main

# 2. LUI - Merger ses trucs  
git checkout main
git pull origin main          # récupère tes changements
git merge Malafont
git push origin main

# 3. VOUS DEUX - Récupérer la version finale
git checkout Tazokami         # ta branche
git merge main               # récupérer tout

git checkout Malafont        # sa branche  
git merge main               # récupérer tout
```

---

## **📋 RÉSOLUTION DE CONFLITS ENTRE VOS BRANCHES**

### **🚨 Si vous modifiez le même fichier :**

```bash
# Merger sa branche dans la tienne
git checkout Tazokami
git merge Malafont

# Si conflit dans srcs/main.c :
code srcs/main.c

# Tu verras :
# <<<<<<< HEAD (tes trucs)
# ======= 
# >>>>>>> Malafont (ses trucs)

# Garder les deux ou choisir
git add srcs/main.c
git commit -m "🔀 Merge Malafont changes into Tazokami"
git push origin Tazokami
```

---

## **📋 RÈGLES POUR VOS BRANCHES PERSO**

### **✅ BONNES PRATIQUES :**

```bash
# Commits clairs avec vos noms
git commit -m "🎮 [Tazokami] Add raycasting core algorithm"
git commit -m "🗺️ [Malafont] Add map validation functions"

# Sync régulier entre vous
git pull origin Malafont  # toi récupérer ses trucs
git pull origin Tazokami  # lui récupérer tes trucs

# Test avant merge
make fclean && make && ./cub3D maps/test.cub
```

### **🗣️ COMMUNICATION :**
```bash
# Sur Discord/Slack quand tu push :
"🚀 [Tazokami] Pushed raycasting algo to my branch"
"🚀 [Malafont] Pushed map parser to my branch" 

# Quand tu merge sur main :
"⚠️ Merged to main - please pull!"
```

---

## **🎯 VOUS ÊTES SETUP ! PRÊTS À CODER !**

```bash
# TOI maintenant :
git checkout Tazokami
echo "🎮 Working on Tazokami branch - ready to code raycasting!"

# LUI quand il clone :  
# git checkout Malafont
# echo "🗺️ Working on Malafont branch - ready to code parsing!"
```

**🤝 Vos branches sont prêtes ! Au boulot les champions ! 🚀**
