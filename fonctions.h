#ifndef __fonctions_H_
#define __fonctions_H_


/*
Auteurs : Thomas, Margaux, Marc
Date : 22 mai 2022
Résumé : Structure décrivant un pixel, qui comprend les valeurs des 3 couleurs que peut prendre le pixel (red,green,blue).
*/ 
typedef struct{
	int r;
	int g;
	int b;
} pixel;

/*
Auteurs : Thomas, Margaux, Marc
Date : 22 mai 2022
Résumé : Structure qui décrit une image, qui comprend un type (P3), une hauteur, une largeur, une valeur max () et un tableau de pixels.
*/ 
typedef struct{
	char* type;
	int hauteur;
	int largeur;
	int valeur_max;
	pixel** tabpixels;
} img;

/*
Auteurs : Thomas, Margaux, Marc
Date : 22 mai 2022
Résumé : permet d'allouer un tableau à 2 entrées de taille n pour la largeur et m pour la hauteur. Chaque case contiendra les paramètres de la couleur du pixel (r,g,b). 
Entrées : un tableau 2D de pixels (pointeur de pointeurs), la largeur et la hauteur.  
Sorties : retourne un tableau de pixels .
*/
pixel** AllouerPixels (pixel** tab, int n, int m);

/*
Auteurs : Thomas, Margaux, Marc
Date : 22 mai 2022
Résumé : permet d'allouer une image (donc alloue l'image, son type et le tableau de pixels) 
Entrées : 
sorties : retourne un pointeur du type image.
*/
img* AllouerImage();

/*
Auteurs : Thomas, Margaux, Marc
Date : 22 mai 2022
Résumé : permet d'ouvrir le fichier prit en paramètre en mode lecture, et d'initialiser une structure image qui contient les valeurs en lien avec le fichier (hauteur, largeur, remplir le tableau de pixel). 
Entrées : un pointeur de char qui correspond au fichier ppm à lire. 
Sorties : retourne un pointeur du type image.
*/
img* Chargement(char* imageppm);

/*
Auteurs : Thomas, Margaux, Marc
Date : 22 mai 2022
Résumé : permet d'ouvrir un fichier passé en parametre en mode écriture et y écrit les données d'une variable de type img. 
Entrées : un pointeur d'image qui correspond à l'image a transcrire dans le fichier, un pointeur de char qui correspond au fichier ppm dans lequel écrire. 
Sorties : retourne un entier (0 si erreur, 1 si bon)
*/
int Sauvegarde (img* image, char* fichierE);

/*
Auteurs : Thomas, Margaux, Marc
Date : 24 mai 2022
Résumé : permet de calculer la luminance de chaque pixel et transforme l'image en couleur en une image en niveau de gris. 
Entrées : une structure contenant l'image en couleur. 
Sorties : l'image en niveau de gris
*/
img* Transformation_gris (img* image); 

/*
Auteurs : Thomas, Margaux, Marc
Date : 24 mai 2022
Résumé : permet de binariser une image. On détermine la valeur (entre blanc et noir) de chaque pixel en fonction de la valeur passée en paramètre   
Entrées : une structure contenant l'image en couleur, une valeur entière qui correspond à la valeur médiane de l'image. 
Sorties : l'image binarisée
*/
img* Binarisation (img* image,int seuil);

/*
Auteurs : Thomas, Margaux, Marc
Date : 25 mai 2022
Résumé : Créer une croix de largeur passée en parametre dans ume un fichier ppm (passé en parmètre) dont l'utilisateur défini les dimensions (paramètres x et y)  
Entrées : le fichier dans lequel créer l'image (char*), les dimensions de l'image (int) et la largeur de la croix (int)
Sorties : 
*/
img* Croix (char* fichierC, int x, int y, int largeurC);

/*
Auteurs : Thomas, Margaux, Marc
Date : 25 mai 2022
Résumé : Créer le miroir (symétrie axiale d'axe vertical) d'une image passée en paramètre
Entrées : l'image originale
Sorties : l'image après transfo miroir
*/
img* Miroir (img* image);

/*
Auteurs : Thomas, Margaux, Marc
Date : 25 mai 2022
Résumé : Effectue la rotation d'une image à 90 degrés dans le sens des aiguilles d'une montre
Entrées : l'image originale
Sorties : l'image rotationnée
*/
img* Rotation (img* image);

/*
Auteurs : Thomas, Margaux, Marc
Date : 25 mai 2022
Résumé : Transforme une image en son negatif
Entrées : l'image originale
Sorties : l'image en négatif
*/
img* Negatif (img* image);

/*
Auteurs : Thomas, Margaux, Marc
Date : 26 mai 2022
Résumé : Alloue une matrice de convolution
Entrées : 
Sorties : un tableau de floats de taille 3 3
*/
float** AllouerMatConv();

/*
Auteurs : Thomas, Margaux, Marc
Date : 26 mai 2022
Résumé : Permet d'appliquer un effet à une image par convolution
Entrées : l'image originale et la matrice de convolution
Sorties : image apres transo convolution
*/
img* Convolution (img* image, float** filtre);

/*
Auteurs : Thomas, Margaux, Marc
Date :  03 juin 2022
Résumé : Permet de créer un fichier .txt qui contient les valeurs de l'histogramme
Entrées : le pointeur d'entier avec les valeurs de l'histo et le fichier 
Sorties : 
*/
int SauvegardeHisto(int* histo, char* fichierTxt); 

/*
Auteurs : Thomas, Margaux, Marc
Date :  03 juin 2022
Résumé : Permet de créer un graphique qui comprend les valeurs de l'histogramme 
Entrées : le fichier txt qui contient les valeurs de l'histogramme 
Sorties : 
*/
void AffichageHisto (char* imagetxt); 

/*
Auteurs : Thomas, Margaux, Marc
Date : 26 mai 2022
Résumé : Permet de déterminer l'histogramme d'une image
Entrées : l'image en niveau de gris
Sorties : le tableau d'histogramme
*/
int* Histogramme (img* image);

/*
Auteurs : Thomas, Margaux, Marc
Date : 27 mai 2022
Résumé : Permet de recadrer dynmiquement une image
Entrées : l'image originale
Sorties : l'image recadrée dynamiquement
*/
img* RecadrageDynamique(img* image);

/*
Auteurs : Thomas, Margaux, Marc
Date : 03 juin 2022
Résumé : Permet d'appliquer une érosion sur une image
Entrées : l'image originale
Sorties : l'image après érosion
*/
img* erosion (img* image, img* croix);

/*
Auteurs : Thomas, Margaux, Marc
Date : 03 juin 2022
Résumé : Permet d'appliquer une dilatation sur une image
Entrées : l'image originale
Sorties : l'image après dilatation
*/
img* dilatation (img* image, img* croix);


//PROCEDURES LIBERATION MEMOIRE
void LibTab(pixel** tab, int n);
void LibMatConv(float** tab, int n);
void LibImg(img* image);

/*
Auteurs : Thomas, Margaux, Marc
Date : 05 juin 2022
Résumé : Effectue un zoom sur une image
Entrées : l'image originale, et le coefficiant de zoom
Sorties : l'image après zoom
*/
img* zoom (img* image, int coefzoom);

/*
Auteurs : Thomas, Margaux, Marc
Date : 05 juin 2022
Résumé : Effectue un zoom sur une image
Entrées : l'image originale, et le coefficiant de dézoom
Sorties : l'image après dézoom
*/
img* dezoom (img* image, int coefdezoom); 

#endif



