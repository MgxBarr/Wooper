#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <getopt.h>

#include "fonctions.h"



int main(int argc, char** argv){

    img* image;

    //Initialisation d'une variable pour chaque option, qui sert a compter le nombre de fois que chacune est appelée
    int bin=0;
    int renfcon=0;
    int dil=0;
    int ero=0;
    int flou=0;
    int cont=0;
    int gris=0;
    int reca=0;
    int croix=0;

    int miroir=0;
    int rota=0;
    int neg=0;

    char* i="";
    char* o="";
    int seuil=0;
    int xcroix=0;
    int ycroix=0;
    int largeurcroix=0;

    int fs=0;


    int zoo=0;
    int dezoo=0;

    if (argc<=1) {
        printf("Ecrivez ./img -h pour voir l'aide du programme\n");
        exit(EXIT_SUCCESS);
    }
    //Utilisation de getopt pour gérer les arguments
    int options=0;
    int argcompt=1;
    while ((options = getopt (argc, argv, "hb:cdefi:lgo:rxnmpvZz")) != -1) {
        switch (options) {

            //-h : affiche une aide sur votre programme et quitte le programme avec un code de retour égal à 0
            case 'h':
                printf ("Voici les différentes options que vous pouvez ajouter : \n");
                printf ("--------------------------------------------------------------------------------\n");
                printf("-h : affiche une aide \n");
                printf("-b seuil : permet de binariser votre image avec la valeur du seuil à préciser \n");
                printf("-c : réalise un renforcement de contraste \n");
                printf("-d : réalise une dilatation \n");
                printf("-e : réalise une érosion \n");
                printf("-f : réalise un flou \n");
                printf("-i fichier : définit le fichier d entrée (obligatoire) \n");
                printf("-l : réalise une détection de contours/lignes \n");
                printf("-g : convertit l’image en niveau de gris \n");
                printf("-o fichier : définit le fichier de sortie \n");
                printf("-r : réalise un recadrage dynamique \n");
                printf("-x largeur hauteur épaisseur : réalise une croix aux dimensions spécifiées \n");
                printf("-m : réalise le miroir de l’image \n");
                printf("-p : réalise une rotation de  90° dans le sens horaire \n");
                printf("-n : réalise le négatif de l’image \n");
                printf("-Z : réalise un zoom x2 de l'image \n");
                printf("-z : réalise un dézoom x2 de l'image\n");
                printf ("--------------------------------------------------------------------------------\n");
                exit(EXIT_SUCCESS);
                break;

            //-b seuil : binarise une image    
            case 'b':
                bin++;
                seuil=atoi(optarg);
                //Si il n'y a pas de valeur de seuil lors de l'appel de la fonction binarisation
                if (!seuil) {
                    printf("Veuillez spécifier une valeur de seuil pour apeller binarisation\n");
                    exit(EXIT_SUCCESS);
                }
                break;

            //-c : réalise un renforcement de contraste
            case 'c':
                renfcon++;
                break;

            //-d : réalise une dilatation
            case 'd':
                dil++;
                break;

            //-e : réalise une érosion
            case 'e':
                ero++;
                break;

            //-f : réalise un flou
            case 'f':
                flou++;
                break;

            //-i fichier : définit le fichier d’entrée, OBLIGATOIRE 
            case 'i':
                i=optarg;
                //printf (" fichier entrée %s\n", optarg);                                                              
                image=Chargement(i);
                argcompt++;
                break;

            //-l : réalise une détection de contours/lignes
            case 'l':
                cont++;
                break;

            //-g : convertit l’image en niveau de gris
            case 'g':
                gris++;
                break;

            //-o fichier : définit le fichier de sortie
            case 'o':
                o=optarg;
                //printf (" fichier sortie %s\n", optarg);    
                fs=1;
                argcompt++;
                break;

            //-r : réalise un recadrage dynamique + BONUS histogramme png
            case 'r':
                reca++;
                break;

            //-x largeur hauteur épaisseur : réalise une croix aux dimensions spécifiées
            case 'x':
                croix++;
                xcroix=atoi(argv[argcompt+1]);
                ycroix=atoi(argv[argcompt+2]);
                largeurcroix=atoi(argv[argcompt+3]);
                printf("%d %d %d\n",xcroix,ycroix,largeurcroix);                                                                                    //XXXXXXXXXXXXXXXXXXXX
                break;




            //-n : négatif de l'image
            case 'n':
                neg++;
                break;

            //-m : miroir de l'image
            case 'm':
                miroir++;
                break;

            //-p : rotation 90° dans le sens des aiguilles d'une montre de l'image
            case 'p' :
                rota++;
                break;



                //BONUS

            //-Z : réalise un zoom * 2 sur une image
            case 'Z':
                zoo++;
                break;

            //-z : réalise un zoom / 2 sur une image
            case 'z':
                dezoo++;
                break;


            //DEFAULT
            default:
                break;
            
        } //end switch  
        argcompt++; 
    } //end while



    //Si il n'y a pas de fichier d'entrée, on le dit et on quitte le programme
    if (i && !i[0]) {
        printf("Veuillez spécifier un fichier d'entrée\n");
        exit(EXIT_SUCCESS);
    }



        //Matrices Convolution

    float** Elementaire=AllouerMatConv();       //Matrice Convolution Elementaire
    Elementaire[0][0]=0;
    Elementaire[0][1]=0;
    Elementaire[0][2]=0;
    Elementaire[1][0]=0;
    Elementaire[1][1]=1;
    Elementaire[1][2]=0;
    Elementaire[2][0]=0;
    Elementaire[2][1]=0;
    Elementaire[2][2]=0;

    float** RenfoContraste=AllouerMatConv();     //Matrice Convolution Renforcement Contraste
    RenfoContraste[0][0]=0;
    RenfoContraste[0][1]=-1;
    RenfoContraste[0][2]=0;
    RenfoContraste[1][0]=-1;
    RenfoContraste[1][1]=5;
    RenfoContraste[1][2]=-1;
    RenfoContraste[2][0]=0;
    RenfoContraste[2][1]=-1;
    RenfoContraste[2][2]=0;

    float** Floutage=AllouerMatConv();          //Matrice Convolution Floutage
    Floutage[0][0]=0.0625;
    Floutage[0][1]=0.125;
    Floutage[0][2]=0.0625;
    Floutage[1][0]=0.125;
    Floutage[1][1]=0.25;
    Floutage[1][2]=0.125;
    Floutage[2][0]=0.0625;
    Floutage[2][1]=0.125;
    Floutage[2][2]=0.0625;

    float** Contours=AllouerMatConv();           //Matrice Convolution Contour
    Contours[0][0]=-1;
    Contours[0][1]=-1;
    Contours[0][2]=-1;
    Contours[1][0]=-1;
    Contours[1][1]=8;
    Contours[1][2]=-1;
    Contours[2][0]=-1;
    Contours[2][1]=-1;
    Contours[2][2]=-1;




    //Boucle qui applique les fonctions en fonciton des options appelées
    for(int i=0; i<argc; i++) {

        //Binarisation
        if (bin>=1){
            image=Binarisation(image,seuil);
            bin--;
        }

        //Renforcement Contraste
        if (renfcon>=1){
            image=Convolution(image,RenfoContraste);
            renfcon--;
        }

        //Dilatation
        if (dil>=1){
            img* CroixSeg;
            CroixSeg=Croix("CroixSeg.ppm",5,5,1);
            img* imagegdil;
            imagegdil=AllouerImage();
            imagegdil->type="P3";
            imagegdil->valeur_max=255;
            imagegdil->tabpixels=AllouerPixels(imagegdil->tabpixels, image->hauteur, image->largeur);
            imagegdil=Transformation_gris(image);
            image=dilatation(imagegdil,CroixSeg);
            dil--;
        }

        //Erosion
        if (ero>=1){
            img* CroixSeg;
            CroixSeg=Croix("CroixSeg.ppm",5,5,1);
            img* imagegero;
            imagegero=AllouerImage();
            imagegero->type="P3";
            imagegero->valeur_max=255;
            imagegero->tabpixels=AllouerPixels(imagegero->tabpixels, image->hauteur, image->largeur);
            imagegero=Transformation_gris(image);
            image=erosion(imagegero,CroixSeg);
            ero--;
        }

        //Flou
        if (flou>=1){
            image=Convolution(image,Floutage);
            flou--;
        }

        //Contour
        if (cont>=1){
            image=Convolution(image,Contours);
            cont--;
        }

        //Transfo niveau gris
        if (gris>=1){
            image=Transformation_gris(image);
            gris--;
        }

        //Recadrage Dynamique
        if (reca>=1){
            image=RecadrageDynamique(image);            
            reca--;
        }

        //Croix                                                
        if (croix>=1){
            image->tabpixels=realloc(image->tabpixels, xcroix*sizeof(pixel*));
            for (int cr = 0; cr < xcroix; cr++) {
                image->tabpixels[cr]=realloc(image->tabpixels[cr], ycroix*sizeof(pixel));
            }
            image->hauteur=ycroix;
            image->largeur=xcroix;
            image=Croix(o,xcroix,ycroix,largeurcroix);
            croix--;
        }

        //Négatif
        if (neg>=1){
            image=Negatif(image);
            neg--;
        }

        //Miroir
        if (miroir>=1){
            image=Miroir(image);
            miroir--;
        }

        //Rotation
        if (rota>=1){
            image=Rotation(image);
            rota--;
        }



        //Bonus Zoom
        if (zoo>=1) {      
            image=zoom(image,2);
            zoo--;
        }

        //Bonus Dezoom
        if (dezoo>=1) {  
            image=dezoom(image,2);
            dezoo--;
        }


    } //end for





    //Affichage / Sauvegade de l'image
    if (!fs) {              //Si il n'y a pas de fichier de sortie, on affiche les valeurs de l'image dans le terminal
        printf("%s\n", image->type);
        printf("%d %d\n", image->hauteur, image->largeur);
        printf("%d\n", image->valeur_max);
        for (int lig = 0; lig < image->hauteur; lig++) {
            for (int col = 0; col < image->largeur; col++) {
                printf("%d\n", image->tabpixels[lig][col].r);
                printf("%d\n", image->tabpixels[lig][col].g);
                printf("%d\n", image->tabpixels[lig][col].b);
            }        
        }
    }
    else {                  //Si il y a un fichier de sortie, on sauvegarde l'image dans celui ci
        Sauvegarde(image,o);
    } 


    /*
    //LIBERER TOUS MES COPAINS
    LibImg(image);
    LibMatConv(Elementaire,3);
    LibMatConv(RenfoContraste,3);
    LibMatConv(Floutage,3);
    LibMatConv(Contours,3);
    */
    return 0;
}