# Projet C++ embarqué
## _Drone militaire_

![logo](https://user-images.githubusercontent.com/60011578/236699551-7745a4e5-4dee-4b0c-b410-08744eef314c.png?width=500&height=500)

[![GitHub stars](https://img.shields.io/github/stars/themlphdstudent/awesome-github-profile-readme-templates.svg)](https://youtu.be/dQw4w9WgXcQ)
[![GitHub contributors](https://img.shields.io/github/contributors/themlphdstudent/awesome-github-profile-readme-templates.svg?color=blue)](https://user-images.githubusercontent.com/60011578/236701340-5b089617-cd39-4fb2-a12b-aab835183ec8.png)

## Contexte

Nous sommes en 2024, 3ème guerre mondiale. Un de nos drones a photographié
une base militaire ennemie de nuit et dissimulé les coordonnées du lieu (37°42'41.9"S 144°59'33.0"E). Cette image 
doit être récupérée et analysée pour déterminer les actions à mener.

![DroneIMG37337](https://user-images.githubusercontent.com/60011578/236699905-1da852e8-2a47-4851-b63e-983793c0ca20.png)

## Objectifs

* Transmettre l’image et son information cachée en utilisant de la 
stéganographie et le protocole mqtt

* Récupérer l’image et découvrir les coordonnées du cliché

## Organisation

* Pour ce projet en groupe, vous serez séparés en deux équipes (équipe
Drone et équipe Base). Vous allez partager un nouveau GitHub public 
et publier votre code et captures d’écran, sur ce repo en séparant les 
deux projets (Drone et Base). 
* Vous proposerez des pull requests, branches, commits etc entre les 
membres de l’équipe, ou du groupe si vous êtes seul dans l’équipe.
* Un ReadMe sera disponible dans chaque projet, résumant l’utilisation 
du programme.
* Le PAQL en annexe devra être respecté.
* Aucun code commenté ne sera commité dans la branche principale 
release/main

## Parie Drone

Vous aurez pour mission de créer un programme console avec Qt en C++ qui charge le fichier DroneIMG37337.png et y ajoute via un algorithme au choix autre que steghide, les coordonnées GPS 37°42'41.9"S 144°59'33.0"E. Le fichier sera envoyé sur le broker : mqtt://broker.emqx.io:1883, topic /ynov/bordeaux/NomDuGitHubDuGroupe avec un QoS 2.

## Partie Base

Vous aurez pour mission de créer un programme graphique avec QtDesign en C++ qui se connecte au broker : mqtt://broker.emqx.io:1883, et s’abonne au topic:/ynov/bordeaux/NomDuGitHubDuGroupe avec un QoS 2. Une fois le fichier récupéré, vous devrez découvrir les coordonnées cachées dans l’image et afficher l’image, ainsi que les coordonnées GPS. 

![imageResultat](https://user-images.githubusercontent.com/60011578/236700179-dce998b5-24c3-44de-92ac-70f48fe06009.png)

## Demonstration 

Ci-dessous ce trouve le rendu final du projet représenter par une vidéo. Dans cette vidéo on peut voir l'utilisation de notre IHM qui reçoit et decrypte l'image afin d'y trouver les coordonnées qui y sont cachées.

https://user-images.githubusercontent.com/60011578/236699369-2f734e0f-4ee9-4101-a671-624b34181587.mp4

