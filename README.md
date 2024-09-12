# WOOPER - P1 Projet S2

# Projet de traitement d'image PPM

Programme qui permet d'effectuer différentes modifications sur des images PPM de type P3.


# Qu'est-ce que le traitement d'images ? 

Le traitement d'images étudie les images numériques et leurs transformations, dans le but d'améliorer leur qualité ou d'en extraire de l'information. 
Pour comprendre le traitement d'image, il faut d'abord comprendre ce qu'est une image. 
Les images ont de nombreux paramètres : 
- la résolution d'acquisition et le mode de codage utilisé lors de la numérisation
- les réglages optiques utilisés (dont la mise au point) qui déterminent par exemple la netteté de l'image
- les conditions d'éclairage
- le bruit de la chaîne de transmission d'image

Chaque image a un certain nombre de pixels, qui est une combinaison de couleurs (rouge, bleu et vert). La manipulation de ces paramètres nous permettent de traiter l'image, c'est à dire de la modifier. 
Par exemple la binariser, faire une rotation, un effet miroir, modifier la couleur des pixels etc.


# Utilisation

Téléchargez le dossier, déplacez vous dedans, compilez avec make clean et make, puis executez le programme avec ./img

Vous pouvez utiliser différentes commandes après le ./img, pour avoir l'aide du programme, écrivez ./img -h

    
# Exemples de commandes :

./img -i bender.ppm -o bendergris.ppm -g

./img -i bender.ppm -o rota.ppm -p -p

./img -i bender.ppm -c




