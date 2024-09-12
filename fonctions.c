#include "fonctions.h"

#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 




//ALLOUER IMAGE
img* AllouerImage() {
  img* image;
  image=malloc(1*sizeof(img));
  image->type=malloc(1000*sizeof(char));
  return image;
}


//ALLOUER PIXELS
pixel** AllouerPixels (pixel** tab, int n, int m) {
  tab=malloc(n*sizeof(pixel*));
  for (int i = 0; i < n; i++) {
    tab[i]=malloc(m*sizeof(pixel));
  }
  return tab;
}


//CHARGEMENT
img* Chargement(char* imageppm) {

  //On crée et alloue l'image à retourner
  img* image;
  image=AllouerImage();

  //on créer un pointeur de fichier vide
  FILE* fichier;
  fichier=NULL;

  //on se sert du pointeur de fichier pour ouvrir le fichier en paramètre en mode lecture
  fichier=fopen(imageppm, "r");

  //Si le pointeur de fichier est vide, on indique qu'il ne s'est pas ouvert : Erreur
  if (fichier==NULL) {
    printf("Erreur ouverture fichier \n");
  }

  //Sinon, on effectue la lecture
  else {
    fscanf(fichier, "%s", image->type);         //On lit la première ligne du fichier pour récupérer le type de l'image (qui est un char* dans notre struct img)
    fseek(fichier, 2, SEEK_SET);                //On se sert de la fonction fseek, qui nous permet de nous placer 2 cases après le début du fichier (d'ou le 2 pour le nombre, et SEEK_SET pour dire début du fichier)
    fscanf(fichier,"%d",&image->hauteur);       //On lit donc la 2eme ligne et on récupère la largeur et la hauteur (qui sont des entiers dans notre struct img)
    fscanf(fichier,"%d",&image->largeur);       
    fscanf(fichier,"%d",&image->valeur_max);     //On lit la 3ème ligne et on récupère la valeur max (luminance)

    image->tabpixels=AllouerPixels(image->tabpixels,image->hauteur, image->largeur);

    /*
    Notre tableau est en 2D, on effectue donc une double boucle pour récupérer chaque pixel
    Un pixel contient 3 valeurs, on récupère donc les valeurs 3 par 3 (d'où les 3 fscanf) 
    */
    for (int i = 0; i < image->hauteur; i++) {
      for (int j = 0; j < image->largeur; j++) {
        fscanf(fichier,"%d",&image->tabpixels[i][j].r);
        fscanf(fichier,"%d",&image->tabpixels[i][j].g);
        fscanf(fichier,"%d",&image->tabpixels[i][j].b);
      } //end for j 
    } //end for i
    fclose(fichier);
  } //end else

  //On retourne l'image
  return image;
}


//SAUVEGARDE
int Sauvegarde (img* image, char* fichierE) {
	//Initialisation des variables, dont un pointeur de fichier pour le fichier dans lequel écrire
  int res=1;
	FILE* fichier;
  //Ouverture du fichier en mode écriture

	fichier=fopen(fichierE, "w+");

  //Si le pointeur de fichier est vide, on le signale
	if (fichier == NULL) {
    printf("Erreur ouverture fichier \n");
    res=0;
  }
  //Sinon on écrit
  else {
    //Ecriture du type, de la largeur et de la hauteur, et de la luminance
    fprintf(fichier, "%s\n", image->type);
    fprintf(fichier, "%d %d\n", image->largeur, image->hauteur);
    fprintf(fichier, "%d\n", image->valeur_max);

    //Ecriture de chaque pixel
    for (int i = 0; i < image->hauteur; i++) {
      for (int j = 0; j < image->largeur; j++) {
        fprintf(fichier,"%d\n",image->tabpixels[i][j].r);
        fprintf(fichier,"%d\n",image->tabpixels[i][j].g);
        fprintf(fichier,"%d\n",image->tabpixels[i][j].b);
      } //end for j 
    } //end for i
    fclose(fichier);
  }
  return res;
}


//TRANSORMATION GRIS
img* Transformation_gris (img* image){
  int luminance=0;
  //On parcourt chaque pixel 
  for (int i=0;i<image->hauteur;i++){
    for (int j=0;j<image->largeur;j++){
      
      //Calcul de la luminance pour chaque pixel, et affectation de cette dernière à chaque couleur (r,g,b). 
      luminance=(0.2126*image->tabpixels[i][j].r)+(0.7152*image->tabpixels[i][j].g)+(0.0722*image->tabpixels[i][j].b);
      image->tabpixels[i][j].r=luminance;
      image->tabpixels[i][j].g=luminance;
      image->tabpixels[i][j].b=luminance;
    }
  }
  
  return image;
} 


//BINARISATION
img* Binarisation (img* image,int seuil){

  int m;

  // On parcourt les pixels de l'image
  for (int i=0;i<image->hauteur;i++){
    for (int j=0;j<image->largeur;j++){
      m=(image->tabpixels[i][j].r+image->tabpixels[i][j].g+image->tabpixels[i][j].b)/3;

      //Si la valeur moyenne du pixel est plus grande que le seuil, on met le pixel blanc
      if (m>seuil) {
        image->tabpixels[i][j].r=255;
        image->tabpixels[i][j].g=255;
        image->tabpixels[i][j].b=255;
      }
      //Sinon on le met en noir
      else {
        image->tabpixels[i][j].r=0;
        image->tabpixels[i][j].g=0;
        image->tabpixels[i][j].b=0;   
      }

    } //end for j
  }
  return image;
}


//CROIX
img* Croix (char* fichierC, int x, int y, int largeurC) { //x : ie largeur   y : ie hauteur 

  //Si mauvaises valeurs, pour éviter croix non centrée
  if ((largeurC%2==0 && (x%2!=0 || y%2!=0)) || (largeurC%2!=0 && (x%2==0 || y%2==0))) {
    printf("Veuillez entre des valeurs correctes (paires/paire ou impaires/impair");
  }

  //Initialisation et allocation de la croix
  img* croix;
  croix=AllouerImage();
  croix->tabpixels=AllouerPixels(croix->tabpixels, y, x);
  croix->type="P3";
  croix->hauteur=y;
  croix->largeur=x;
  croix->valeur_max=255;


  //On remplit l'image de blanc
  for (int i = 0; i < y; i++) {
      for (int j = 0; j < x; j++) {
          croix->tabpixels[i][j].r=255;
          croix->tabpixels[i][j].g=255;
          croix->tabpixels[i][j].b=255;
      }
  }

  //Partie horizontale de la croix (on divise l'image en 2, a laquelle on soustrait la moitié de la largeur)
  int p=(x/2)-(largeurC/2);
  for (int l1= 0; l1 < y; l1++) {
      for (int  l2= 0; l2 < largeurC; l2++) {
          croix->tabpixels[l1][p+l2].r=0;
          croix->tabpixels[l1][p+l2].g=0;
          croix->tabpixels[l1][p+l2].b=0;
      }
  }

  //Partie verticale, même calcul mais pour la colonne
  int q=(y/2)-(largeurC/2);
  for (int l3= 0; l3 < x; l3++) {
      for (int  l4= 0; l4 < largeurC; l4++) {
          croix->tabpixels[q+l4][l3].r=0;
          croix->tabpixels[q+l4][l3].g=0;
          croix->tabpixels[q+l4][l3].b=0;
      }
  }

  //Sauvegarde(croix, fichierC);
  return croix;
}


//MIROIR
img* Miroir (img* image) {
  
  //Allocation et Initialisation de la struct image miroir
  img* miroir;
  miroir=AllouerImage();
  miroir->type="P3";
  miroir->hauteur=image->hauteur;
  miroir->largeur=image->largeur;
  miroir->valeur_max=255;
  miroir->tabpixels=AllouerPixels(miroir->tabpixels, image->hauteur, image->largeur);

  //On "échange les colonnes"
  for (int i = 0; i < miroir->hauteur; i++) {
    for (int j = miroir->largeur; j >0 ; j--) {
      miroir->tabpixels[i][miroir->largeur-j]=image->tabpixels[i][j];
    }  
  }

  return miroir;
}


//ROTATION
img* Rotation (img* image) {
  
  //Allocation et Initialisation de la struct image rotate
  img* rota;
  rota=AllouerImage();
  rota->type="P3";
  rota->hauteur=image->hauteur;
  rota->largeur=image->largeur;
  rota->valeur_max=255;
  rota->tabpixels=AllouerPixels(rota->tabpixels, rota->hauteur, rota->largeur);

  //La colonne i devient la ligne i
  for (int i = 0; i < rota->hauteur; i++) {
    for (int j = 0; j < rota->largeur; j++) {
      rota->tabpixels[i][j]=image->tabpixels[rota->hauteur - j - 1][i];
    }
  }

  return rota;
}


//NEGATIF
img* Negatif (img* image) {
  
  //Allocation et Initialisation de la struct image negatif
  img* negatif;
  negatif=AllouerImage();
  negatif->type="P3";
  negatif->hauteur=image->hauteur;
  negatif->largeur=image->largeur;
  negatif->valeur_max=255;
  negatif->tabpixels=AllouerPixels(negatif->tabpixels, negatif->hauteur, negatif->largeur);

  //On applique simplement la formule de negatif pour chaque composante de chaque pixel
  for (int i = 0; i < negatif->hauteur; i++) {
    for (int j = 0; j < negatif->largeur; j++) {
      negatif->tabpixels[i][j].r=255-image->tabpixels[i][j].r;
      negatif->tabpixels[i][j].g=255-image->tabpixels[i][j].g;
      negatif->tabpixels[i][j].b=255-image->tabpixels[i][j].b;
    }
  }
  
  return negatif;
}


//CONVOLUTION
float** AllouerMatConv () {         //Fonction qui sert à allouer les matrices de convolution
  float** tab;
  tab=malloc(3*sizeof(float*));
  for (int i = 0; i < 3; i++) {
    tab[i]=malloc(3*sizeof(float));
  } 
  return tab;
}

img* Convolution (img* image, float** filtre) {
  
  //Alloc et initialisation de l'image apres convolution
  img* imagec;
  imagec=AllouerImage();
  imagec->type="P3";
  imagec->hauteur=image->hauteur-2;       //On perd la premiere et derniere ligne par convolution
  imagec->largeur=image->largeur-2;       //On perd la premiere et derniere colonne par convolution
  imagec->valeur_max=255;
  imagec->tabpixels=AllouerPixels(imagec->tabpixels, imagec->hauteur, imagec->largeur);

  int convor, convog, convob;
  //Pour chaque pixel, on calcule la valeur convolutionnée et on la met dans la nouvelle matrice, qui est donc plus petite (d'ou le décallage des indices)
  for (int i = 1; i < (image->hauteur-2); i++) {
    for (int j = 1; j < (image->largeur-2); j++) {
      convor=(filtre[0][0]*image->tabpixels[i-1][j-1].r)+(filtre[0][1]*image->tabpixels[i-1][j].r)+(filtre[0][2]*image->tabpixels[i-1][j+1].r)+(filtre[1][0]*image->tabpixels[i][j-1].r)+(filtre[1][1]*image->tabpixels[i][j].r)+(filtre[1][2]*image->tabpixels[i][j+1].r)+(filtre[2][0]*image->tabpixels[i+1][j-1].r)+(filtre[2][1]*image->tabpixels[i+1][j].r)+(filtre[2][2]*image->tabpixels[i+1][j+1].r);
      convog=(filtre[0][0]*image->tabpixels[i-1][j-1].g)+(filtre[0][1]*image->tabpixels[i-1][j].g)+(filtre[0][2]*image->tabpixels[i-1][j+1].g)+(filtre[1][0]*image->tabpixels[i][j-1].g)+(filtre[1][1]*image->tabpixels[i][j].g)+(filtre[1][2]*image->tabpixels[i][j+1].g)+(filtre[2][0]*image->tabpixels[i+1][j-1].g)+(filtre[2][1]*image->tabpixels[i+1][j].g)+(filtre[2][2]*image->tabpixels[i+1][j+1].g);
      convob=(filtre[0][0]*image->tabpixels[i-1][j-1].b)+(filtre[0][1]*image->tabpixels[i-1][j].b)+(filtre[0][2]*image->tabpixels[i-1][j+1].b)+(filtre[1][0]*image->tabpixels[i][j-1].b)+(filtre[1][1]*image->tabpixels[i][j].b)+(filtre[1][2]*image->tabpixels[i][j+1].b)+(filtre[2][0]*image->tabpixels[i+1][j-1].b)+(filtre[2][1]*image->tabpixels[i+1][j].b)+(filtre[2][2]*image->tabpixels[i+1][j+1].b);
      //On remplit la nouvelle image avec les valeurs calculées par convolution : si la valeur est negative, on la met à 0, et si elle est supérieure à 255, on la met a 255
      if (convor<0) {
        convor=0;
      }
      if (convog<0) {
        convog=0;
      }
      if (convob<0) {
        convob=0;
      }
      if (convor>255) {
        convor=255;
      }
      if (convog>255) {
        convog=255;
      }
      if (convob>255) {
        convob=255;
      }
      imagec->tabpixels[i-1][j-1].r=convor;
      imagec->tabpixels[i-1][j-1].g=convog;
      imagec->tabpixels[i-1][j-1].b=convob;
    }
  } //end for i
  
  return imagec;
}


//HISTOGRAMME
int SauvegardeHisto(int* histo, char* fichierTxt) {
	//Initialisation des variables, dont un pointeur de fichier pour le fichier dans lequel écrire
  int res=1;
	FILE* fichier;

  //Ouverture du fichier en mode écriture
	fichier=fopen(fichierTxt, "w+");

  //Si le pointeur de fichier est vide, on le signale
	if (fichier == NULL) {
    printf("Erreur ouverture fichier \n");
    res=0;
  }
  //Sinon on écrit
  else {
    //Ecriture de chaque ligne 
    for (int i = 0; i < 256; i++) {
      fprintf(fichier,"%d %d\n",i, histo[i]);
    }
  }
  fclose(fichier); 
  return res;
}


void AffichageHisto (char* imagetxt){
  //création de la chaine qui comprend toutes les commandes pour modifier le graphique (titre, taille abscisse, légendes...)
  char * commandes[] = {"set title \"Histogramme\"", "set xlabel \"Valeurs de luminance\"", "set ylabel \"Nb occurrences\"", "set yrange [0:4000]" , "set xrange [0:300]", "set terminal 'png'", "set output 'histo'", "plot 'histo.txt' t 'Valeurs' with impulses"};
  
  //ouverture du fichier en mode écriture 
  FILE *gnuplot = popen("gnuplot", "w"); 
  
  if (!gnuplot) {
      perror("popen");
      exit(EXIT_FAILURE);
  }
  //on exécute chaque commandes
  for (int i=0; i < 8; i++){ // 8=nb de commandes appelées 
      fprintf(gnuplot, "%s \n", commandes[i]); 
  }

  fflush(gnuplot);
  pclose(gnuplot);
  //exit(EXIT_SUCCESS);
}


int* Histogramme (img* image) {
  image=Transformation_gris(image);
  //Allocation et initialisation du tableau Histogramme
  int* Histo;
  Histo=malloc(256*sizeof(int));
  for (int i = 0; i < 256; i++) {
    Histo[i]=0;
  }
  

  //On parcourt l'image en niveau de gris (donc chaque couleur du pixel a le meme valeur, cest pk on regarde que le rouge), et pour chaque valeur de luminance, on compte son nombre d'apparitions
  for (int i = 0; i < image->hauteur; i++) {
    for (int j = 0; j < image->largeur; j++) {
      Histo[image->tabpixels[i][j].r]++;
    }  
  }

  //Bonus histogramme 
  SauvegardeHisto(Histo,"histo.txt");
  AffichageHisto("histo.txt"); 

  return(Histo);
}


//RECADRAGE DYNAMIQUE
img* RecadrageDynamique(img* image) {
  int* tab;
  tab=malloc(256*sizeof(int));
  tab=Histogramme(image);
  float max=0;
  float min=10000;
  float imax=0;
  float imin=0;
  for (int i = 0; i < 256; i++) {
    if (tab[i]>max) {
      max=tab[i];
      imax=i;
    }
    if (tab[i]<min &&tab[i]!=0) {
      min=tab[i];
      imin=i;
    }
  }
  float Delta=(255/(imax-imin));
  int l;
  for (int i=0;i<image->hauteur;i++){
    for (int j=0;j<image->largeur;j++){
      l=((image->tabpixels[i][j].r)-imin)*Delta;
      image->tabpixels[i][j].r=l;
      image->tabpixels[i][j].g=l;
      image->tabpixels[i][j].b=l;
    }
  }

  return image;
}





//EROSION
img* erosion (img* image, img* croix) {
  //Allocation de l'image pour appliquer l'érosion
  img* imagee;
  imagee=AllouerImage();
  imagee->type="P3";
  imagee->valeur_max=255;
  imagee->hauteur=image->hauteur-4;
  imagee->largeur=image->largeur-4; 
  imagee->tabpixels=AllouerPixels(imagee->tabpixels, imagee->hauteur, imagee->largeur);

  //Erosion : on prend la valeur de chaque pixel correspondant à ceux de la croix, et pour chaque pixel, on prend le MIN de ces valeurs et c'est notre nouvelle valeur
  for (int i = 2; i < imagee->hauteur; i++) { 
    for (int j = 2; j < imagee->largeur; j++) {
      int min=1000;

      /*
        x
        |
      --+--
        |
        |
      */
      if (image->tabpixels[i-2][j].r<min) {
        min=image->tabpixels[i-2][j].r;
      }

      /*
        |
        x
      --+--
        |
        |
      */
      if (image->tabpixels[i-1][j].r<min) {
        min=image->tabpixels[i-1][j].r;
      }

      /*
        |
        |
      --+--
        x
        |
      */
      if (image->tabpixels[i+1][j].r<min) {
        min=image->tabpixels[i+1][j].r;
      }

      /*
        |
        |
      --+--
        |
        x
      */
      if (image->tabpixels[i+2][j].r<min) {
        min=image->tabpixels[i+2][j].r;
      }

      /*
        |
        |
      x-+--
        |
        |
      */
      if (image->tabpixels[i][j-2].r<min) {
        min=image->tabpixels[i][j-2].r;
      }

      /*
        |
        |
      -x+--
        |
        |
      */
      if (image->tabpixels[i][j-1].r<min) {
        min=image->tabpixels[i][j-1].r;
      }

      /*
        |
        |
      --+x-
        |
        |
      */
      if (image->tabpixels[i][j+1].r<min) {
        min=image->tabpixels[i][j+1].r;
      }

      /*
        |
        |
      --+-x
        |
        |
      */
      if (image->tabpixels[i][j+2].r<min) {
        min=image->tabpixels[i][j+2].r;
      }


      imagee->tabpixels[i][j].r=min;
      imagee->tabpixels[i][j].g=min;
      imagee->tabpixels[i][j].b=min;
    } //end for j
  } //end for i

  return imagee;
}


//DILATATION
img* dilatation (img* image, img* croix) {
  //Allocation de l'image pour effectuer l'érosion
  img* imaged;
  imaged=AllouerImage();
  imaged->type="P3";
  imaged->valeur_max=255;
  imaged->hauteur=image->hauteur-4;
  imaged->largeur=image->largeur-4; 
  imaged->tabpixels=AllouerPixels(imaged->tabpixels, imaged->hauteur, imaged->largeur);

  //Dilatation : on prend la valeur de chaque pixel correspondant à ceux de la croix, et pour chaque pixel, on prend le MAX de ces valeurs et c'est notre nouvelle valeur
  for (int i = 2; i < imaged->hauteur; i++) { 
    for (int j = 2; j < imaged->largeur; j++) {
      int max=0;

      /*
        x
        |
      --+--
        |
        |
      */
      if (image->tabpixels[i-2][j].r>max) {
        max=image->tabpixels[i-2][j].r;
      }

      /*
        |
        x
      --+--
        |
        |
      */
      if (image->tabpixels[i-1][j].r>max) {
        max=image->tabpixels[i-1][j].r;
      }

      /*
        |
        |
      --+--
        x
        |
      */
      if (image->tabpixels[i+1][j].r>max) {
        max=image->tabpixels[i+1][j].r;
      }

      /*
        |
        |
      --+--
        |
        x
      */
      if (image->tabpixels[i+2][j].r>max) {
        max=image->tabpixels[i+2][j].r;
      }

      /*
        |
        |
      x-+--
        |
        |
      */
      if (image->tabpixels[i][j-2].r>max) {
        max=image->tabpixels[i][j-2].r;
      }

      /*
        |
        |
      -x+--
        |
        |
      */
      if (image->tabpixels[i][j-1].r>max) {
        max=image->tabpixels[i][j-1].r;
      }

      /*
        |
        |
      --+x-
        |
        |
      */
      if (image->tabpixels[i][j+1].r>max) {
        max=image->tabpixels[i][j+1].r;
      }

      /*
        |
        |
      --+-x
        |
        |
      */
      if (image->tabpixels[i][j+2].r>max) {
        max=image->tabpixels[i][j+2].r;
      }


      imaged->tabpixels[i][j].r=max;
      imaged->tabpixels[i][j].g=max;
      imaged->tabpixels[i][j].b=max;
    } //end for j
  } //end for i

  return imaged;
}





//Procédures de libération de mémoire
void LibTab(pixel** tab, int n) {
  for (int i=0;i<n;i++){
    free(tab[i]);
  }
  free(tab);
  tab=NULL;
} 

void LibMatConv(float** tab, int n) {
  for (int i=0;i<n;i++){
    free(tab[i]);
  }
  free(tab);
  tab=NULL;
} 

void LibImg(img* image) {
  LibTab(image->tabpixels, image->hauteur);
  free(image->type);
  free(image);
}





//ZOOM
img* zoom (img* image, int coefzoom) {

  //Allocation et initialisation de l'image zoomée
  img* imgz;
  imgz=AllouerImage();
  imgz->type="P3";
  imgz->valeur_max=255;
  imgz->hauteur=image->hauteur/coefzoom;
  imgz->largeur=image->largeur/coefzoom;
  imgz->tabpixels=AllouerPixels(imgz->tabpixels, imgz->hauteur, imgz->largeur);

  /*Comme l'image zoomée est de taille réduite, on prend les pixels qui nous intéresse
  exemple : 
  image 256 256
  la nouvelle taille est donc 128 128, on va donc prendre les pixels de 64 64 à 256-64 256-64
  */
  for (int i = imgz->hauteur/coefzoom; i < image->hauteur-(imgz->hauteur/coefzoom); i++) { 
    for (int j = imgz->largeur/coefzoom; j < image->largeur-(imgz->largeur/coefzoom); j++) {
      imgz->tabpixels[i-(imgz->hauteur/coefzoom)][j-(imgz->largeur/coefzoom)]=image->tabpixels[i][j];
    }
  }
  
  return imgz;
}


//DEZOOM
img* dezoom (img* image, int coefdezoom) {

  //Allocation et initialisation de l'image zoomée
  img* imgdz;
  imgdz=AllouerImage();
  imgdz->type="P3";
  imgdz->valeur_max=255;
  imgdz->hauteur=image->hauteur*coefdezoom;
  imgdz->largeur=image->largeur*coefdezoom;
  imgdz->tabpixels=AllouerPixels(imgdz->tabpixels, imgdz->hauteur, imgdz->largeur);

  //on remplit l'image de pixels noirs
  for (int ii = 0; ii < imgdz->hauteur; ii++) { 
    for (int jj = 0; jj < imgdz->largeur; jj++) {
      imgdz->tabpixels[ii][jj].r=0;
      imgdz->tabpixels[ii][jj].g=0;
      imgdz->tabpixels[ii][jj].b=0;
    }
  }

  //meme principe que zoom, mais image plus grande
  for (int i = 0; i < image->hauteur; i++) { 
    for (int j = 0; j < image->largeur; j++) {
      imgdz->tabpixels[i+(image->hauteur/coefdezoom)][j+(image->largeur/coefdezoom)]=image->tabpixels[i][j];
    }
  }
  
  return imgdz;
}