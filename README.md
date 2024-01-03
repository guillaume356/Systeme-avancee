## 📚 Travaux Pratiques (TP)

Les travaux pratiques sont des exercices préparatoires pour aborder des concepts fondamentaux (dont certains nécessaires à la réalisation du MiniShell). Chaque TP comprend un ensemble d'exercices pratiques pour renforcer les connaissances en programmation système.

### TP 1 à TP 6

- **TP 1**: Initiation aux appels systèmes et gestion de fichiers.
- **TP 2**: Programmation avancée en C et manipulation de processus.
- **TP 3**: Introduction à la programmation concurrente avec les threads.
- **TP 4**: Approfondissement des connaissances en programmation système.
- **TP 5**: Utilisation de Jenkins et Docker pour l'intégration continue.
- **TP 6**: Configuration de services réseau avec DHCP et déploiement de Wordpress.

---

# 🐚 Projet MiniShell

Le projet MiniShell est une implémentation simplifiée d'un shell Unix, réalisée en langage C. Ce projet vise à comprendre les mécanismes des shells en manipulant des appels systèmes de bas niveau et en fournissant des commandes basiques. 🛠️

## 🌟 Fonctionnalités

- `date.c`: Implémentation de la commande date 📅.
- `ls.c`: Implémentation de la commande ls 📂.
- `main.c`: Point d'entrée principal du MiniShell 🔑.
- Historique (commandes appelées précédemment).
- Gestion des erreurs grâce à la variable globale `errno`.
- Implémentation des opérateurs de contrôle `&&` (ET logique) et `||` (OU logique) pour une gestion fluide des commandes.
- D'autres utilitaires comme `who`, `ps`, etc.

## 🔧 Compilation et Exécution

1. Compiler le projet avec le `Makefile` fourni. 🏗️
2. Exécuter le binaire généré pour démarrer le MiniShell. 🚀

## 📄 Documentation Doxygen

Une documentation complète du code a été générée à l'aide de Doxygen. Elle offre un aperçu détaillé de chaque fonction, structure et dépendance utilisée dans le projet. Vous pouvez consulter cette documentation dans le répertoire `Projet_MiniShell/doc`. Elle est disponible sous forme HTML et LaTeX pour une consultation facile.

## 🔍 Difficultés rencontrées

- **Gestion des pipes**: La mise en œuvre des pipes pour connecter la sortie d'une commande à l'entrée d'une autre s'est avérée complexe, notamment pour gérer correctement les cas d'arrière-plan. La synchronisation et la gestion des différents états du shell ont représenté un défi important. (Cette partie n'a pas été finalisé).
- **Structure du projet**: La conception initiale de la structure du projet nous a posé quelques problèmes. La structure est devenue assez dense et quelque peu bancale au fur et à mesure que de nouvelles fonctionnalités étaient ajoutées. Cela a nécessité des ajustements constants pour maintenir la cohérence et l'efficacité.

## 🛠️ Choix de conception

- **Un fichier par commande**: Nous avons opté pour une structure où chaque commande est implémentée dans un fichier séparé (par exemple `date.c`, `ls.c`). Ce choix a été guidé par le désir de maintenir le code organisé et modulaire. Cela facilite la maintenance et le test de chaque commande individuellement, bien que cela ait ajouté une complexité initiale lors de l'établissement de la structure de projet globale.

## 👥 Auteurs

- [Guillaume](https://github.com/guillaume356) 👨‍💻
- [Bastian](https://github.com/bastianfbr) 👨‍💻

---
