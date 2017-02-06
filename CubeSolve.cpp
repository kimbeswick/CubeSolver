#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/**

*/

void readInputFile(char file_name[]);

void makeTable(int dim);

struct piece manipulate(int dim,int orientation,int piecenum,
int units_per,int arX[],int arY[],int arZ[]);

int refTable[3][3][3];


/**Structure:
-We want an array of struct pieces.
-Each piece will contain a linked list.
-Each linked list will comprise of nodes.
-Each node will contain a bitmap representing
the orientation/shift data of the entire piece.
The node will also have a pointer to the next element.
*/

struct bitmap_node {
    int bitmap;
    struct bitmap_node *link;
};

struct linked_list {
    struct bitmap_node b_n;
};

struct piece {
    char ID;
    struct linked_list LL;
};

struct piece array_of_pieces[7];

struct bitmap_node *head=NULL;
struct bitmap_node *curr=NULL;


void insertFirst(int data, struct linked_list LinkedL)
{
   //create a link
   struct node *nod = struct bitmap_node;

   //nod->key = key;
   nod->bitmap = data;
	
   //point it to old first node
   nod->next = head;
	
   //point first to new first node
   head = nod;
}

int main(int argc, char *argv[])  {
    if (argc!=2) {
        printf("Only a run with one text-file argument will be accepted.\ni.e. main input.txt\n");
        return -1;
    }
    char input_file[30];
    strcpy(input_file,argv[1]);
    if ((fopen(input_file,"r"))==NULL) { //If file does not exist
        printf("Error: File not found!\n");
        return -1;
    }
    else {
        readInputFile(input_file);
    }
    return 0;
}

void readInputFile(char file_name[]) {
    int counter, dimension, total_chunks, piece_num, num_of_units;
    int arrX[5]; 
    int arrY[5]; 
    int arrZ[5];
    FILE *file_to_read = fopen(file_name, "r");
    char line[15];
    fgets(line, sizeof(line), file_to_read);
    sscanf(line,"%d",&dimension); //AKA 'N'
    fgets(line, sizeof(line), file_to_read);
    sscanf(line,"%d",&total_chunks); //AKA 'P'
    printf("Logging: Total chunks = %d\n",total_chunks);
    makeTable(dimension);
    
    for (counter=0; counter<total_chunks; counter++) {
        fgets(line, sizeof(line), file_to_read);
        sscanf(line,"%d",&piece_num);
        printf("Logging: Counter is %d\n",counter);
        fgets(line, sizeof(line), file_to_read);
        sscanf(line,"%d",&num_of_units);
        printf("Logging: Piece_Num is %d, with %d units\n",piece_num,num_of_units);
    
        char piece_num_file_str[20]; //It will become 'piece#.txt'
        char piece_num_str[3];
        sprintf(piece_num_str, "%d", piece_num); //Cast piece_num into a string
        strcpy(piece_num_file_str, "piece");
        strcat(piece_num_file_str, piece_num_str);
        strcat(piece_num_file_str, ".txt");
        FILE *file_to_write = fopen(piece_num_file_str, "w");

        if (num_of_units==1) {
            fgets(line, sizeof(line), file_to_read);
            sscanf(line,"%d%d%d",&arrX[0],&arrY[0],&arrZ[0]);
            
            manipulate(dimension,21,piece_num,num_of_units,arrX,arrY,arrZ);
        
            fprintf(file_to_write, "%d\n", arrX[0]);
            fprintf(file_to_write, "%d\n", arrY[0]);
            fprintf(file_to_write, "%d\n", arrZ[0]);
        }
        else if (num_of_units==2) {
            fgets(line, sizeof(line), file_to_read);
            sscanf(line,"%d%d%d",&arrX[0],&arrY[0],&arrZ[0]);
            fgets(line, sizeof(line), file_to_read);
            sscanf(line,"%d%d%d",&arrX[1],&arrY[1],&arrZ[1]);
            
            manipulate(dimension,21,piece_num,num_of_units,arrX,arrY,arrZ);
        
            fprintf(file_to_write, "%d %d\n", arrX[0],arrX[1]);
            fprintf(file_to_write, "%d %d\n", arrY[0],arrY[1]);
            fprintf(file_to_write, "%d %d\n", arrZ[0],arrZ[1]);
        }
        else if (num_of_units==3) {
            fgets(line, sizeof(line), file_to_read);
            sscanf(line,"%d%d%d",&arrX[0],&arrY[0],&arrZ[0]);
            fgets(line, sizeof(line), file_to_read);
            sscanf(line,"%d%d%d",&arrX[1],&arrY[1],&arrZ[1]);
            fgets(line, sizeof(line), file_to_read);
            sscanf(line,"%d%d%d",&arrX[2],&arrY[2],&arrZ[2]);
            
            manipulate(dimension,21,piece_num,num_of_units,arrX,arrY,arrZ);
    
            fprintf(file_to_write, "%d %d %d\n", arrX[0],arrX[1],
            arrX[2]);
            fprintf(file_to_write, "%d %d %d\n", arrY[0],arrY[1],
            arrY[2]);
            fprintf(file_to_write, "%d %d %d\n", arrZ[0],arrZ[1],
            arrZ[2]);
        }
        else if (num_of_units==4) {
            fgets(line, sizeof(line), file_to_read);
            sscanf(line,"%d%d%d",&arrX[0],&arrY[0],&arrZ[0]);
            fgets(line, sizeof(line), file_to_read);
            sscanf(line,"%d%d%d",&arrX[1],&arrY[1],&arrZ[1]);
            fgets(line, sizeof(line), file_to_read);
            sscanf(line,"%d%d%d",&arrX[2],&arrY[2],&arrZ[2]);
            fgets(line, sizeof(line), file_to_read);
            sscanf(line,"%d%d%d",&arrX[3],&arrY[3],&arrZ[3]);

            manipulate(dimension,21,piece_num,num_of_units,arrX,arrY,arrZ);
    
            fprintf(file_to_write, "%d %d %d %d\n", arrX[0],arrX[1],
            arrX[2],arrX[3]);
            fprintf(file_to_write, "%d %d %d %d\n", arrY[0],arrY[1],
            arrY[2],arrY[3]);
            fprintf(file_to_write, "%d %d %d %d\n", arrZ[0],arrZ[1],
            arrZ[2],arrZ[3]);
        }
        else if (num_of_units==5) {
            fgets(line, sizeof(line), file_to_read);
            sscanf(line,"%d%d%d",&arrX[0],&arrY[0],&arrZ[0]);
            fgets(line, sizeof(line), file_to_read);
            sscanf(line,"%d%d%d",&arrX[1],&arrY[1],&arrZ[1]);
            fgets(line, sizeof(line), file_to_read);
            sscanf(line,"%d%d%d",&arrX[2],&arrY[2],&arrZ[2]);
            fgets(line, sizeof(line), file_to_read);
            sscanf(line,"%d%d%d",&arrX[3],&arrY[3],&arrZ[3]);
            fgets(line, sizeof(line), file_to_read);
            sscanf(line,"%d%d%d",&arrX[4],&arrY[4],&arrZ[4]);
            
            manipulate(dimension,21,piece_num,num_of_units,arrX,arrY,arrZ);
    
            fprintf(file_to_write, "%d %d %d %d %d\n", arrX[0],arrX[1],
            arrX[2],arrX[3],arrX[4]);
            fprintf(file_to_write, "%d %d %d %d %d\n", arrY[0],arrY[1],
            arrY[2],arrY[3],arrY[4]);
            fprintf(file_to_write, "%d %d %d %d %d\n", arrZ[0],arrZ[1],
            arrZ[2],arrZ[3],arrZ[4]);
        }
        else {
            printf("Number of units out of bounds!\n");
            return;
        }
        printf("Logging: %s created!\n",piece_num_file_str);
        printf("-----------------------------------------------\n");
        fclose(file_to_write);
    }
    fclose(file_to_read);
}

struct piece manipulate(int dim,int orientation,int piecenum, int units_per,int arX[],int arY[],int arZ[]) {
    struct piece p;
    struct linked_list LIL;
    //bitmap=0;
    int counter;
    int newX[5];
    int newY[5];
    int newZ[5];
    
    //Rotate all units:
    for (counter=0; counter<units_per; counter++) {
        int x=arX[counter];
        int y=arY[counter];
        int z=arZ[counter];
        
        switch(orientation){
            case 1: 
                newX[counter]=x;
                newY[counter]=y;
                newZ[counter]=z;
                //store() relative to manipulate()
                break;
            case 2:
                newX[counter]=y;
                newY[counter]=x;
                newZ[counter]=z;
                break;
            case 3:
                newX[counter]=z;
                newY[counter]=x;
                newZ[counter]=y;
                break;
            case 4:
                newX[counter]=-y;
                newY[counter]=x;
                newZ[counter]=z;
                break;
            case 5:
                newX[counter]=-z;
                newY[counter]=y;
                newZ[counter]=x;
                break;
            case 6:
                newX[counter]=-x;
                newY[counter]=z;
                newZ[counter]=y;
                break;
            case 7:
                newX[counter]=-x;
                newY[counter]=-y;
                newZ[counter]=z;
                break;
            case 8:
                newX[counter]=-y;
                newY[counter]=-z;
                newZ[counter]=x;
                break;
            case 9:
                newX[counter]=-z;
                newY[counter]=-x;
                newZ[counter]=y;
                break;
            case 10:
                newX[counter]=y;
                newY[counter]=-x;
                newZ[counter]=z;
                break;
            case 11:
                newX[counter]=z;
                newY[counter]=-y;
                newZ[counter]=x;
                break;
            case 12:
                newX[counter]=x;
                newY[counter]=-z;
                newZ[counter]=y;
                break;
            case 13:
                newX[counter]=x;
                newY[counter]=z;
                newZ[counter]=-y;
                break;
            case 14:
                newX[counter]=y;
                newY[counter]=x;
                newZ[counter]=-z;
                break;
            case 15:
                newX[counter]=z;
                newY[counter]=y;
                newZ[counter]=-x;
                break;
            case 16:
                newX[counter]=-z;
                newY[counter]=x;
                newZ[counter]=-y;
                break;
            case 17:
                newX[counter]=-x;
                newY[counter]=y;
                newZ[counter]=-z;
                break;
            case 18:
                newX[counter]=-y;
                newY[counter]=z;
                newZ[counter]=-x;
                break;
            case 19:
                newX[counter]=-x;
                newY[counter]=-z;
                newZ[counter]=-y;
                break;
            case 20:
                newX[counter]=-z;
                newY[counter]=-x;
                newZ[counter]=-y;
                break;
            case 21:
                newX[counter]=-y;
                newY[counter]=-x;
                newZ[counter]=-z;
                break;
            case 22:
                newX[counter]=z;
                newY[counter]=-x;
                newZ[counter]=-y;
                break;
            case 23:
                newX[counter]=y;
                newY[counter]=-z;
                newZ[counter]=-x;
                break;
            case 24:
                newX[counter]=x;
                newY[counter]=-y;
                newZ[counter]=-z;
                break;
        }
        printf("Logging: Case 21 Rotation: x = %d, y = %d, z = %d\n",
        newX[counter],newY[counter],newZ[counter]);
 
    }
    
    //-------------------------------------------
    //Now, normalize all units:
    
    //Find min:
    int i;
    int minX=0, minY=0, minZ=0;
    for (i=0; i<units_per; i++) {
        if (newX[i]<minX)
            minX=newX[i];
        if (newY[i]<minY)
            minY=newY[i];
        if (newZ[i]<minZ)
            minZ=newZ[i];
    }
    printf("Logging: Lowest X is %d, Lowest Y is %d, Lowest Z is %d\n",minX,minY,minZ);
    minX*=-1;
    minY*=-1;
    minZ*=-1;
    
    //Now, use the min to shift back to the origin:
    for (i=0; i<units_per; i++) {
        newX[i]+=minX;
        newY[i]+=minY;
        newZ[i]+=minZ;
        printf("Logging: Balanced X is %d, Y is %d, Z is %d\n",newX[i],newY[i],newZ[i]);
    }
    store(piecenum,orientation,0,units_per,newX,newY,newZ);
    
    //-------------------------------------------
    //Now, do every legal shift:
    
    //We'll grab the maxes first to see how far we can shift:
    int maxX=0, maxY=0, maxZ=0;
    for (i=0; i<units_per; i++) {
        if (newX[i]>maxX)
            maxX=newX[i];
        if (newY[i]>maxY)
            maxY=newY[i];
        if (newZ[i]>maxZ)
            maxZ=newZ[i];
    }
    printf("Logging: Highest X is %d, Topest Y is %d, Maxiest Z is %d\n",maxX,maxY,maxZ);
    int canAddToX=dim-maxX;
    int canAddToY=dim-maxY;
    int canAddToZ=dim-maxZ;
    //Shift and store ALL possible positions of the piece:
    //int alreadyAddedToX=0,alreadyAddedToY=0,alreadyAddedToZ=0;
    int a,b,c,d,shift_num=0;
    int bip[units_per];
    for (a=0; a<=canAddToX; a++) {
        for (b=0; b<=canAddToY; b++) {
            for (c=0; c<=canAddToZ; c++) {
                
                for (d=0; d<units_per; d++) { //Does shift.  Shift is initially zero.
                    int xEntry=newX[d]+a;
                    int yEntry=newY[d]+b;
                    int zEntry=newZ[d]+c;
                    
                    bip[d]|=refTable[xEntry][yEntry][zEntry]; //Correlates charted units to refTable
                    printf("%d",bip.bitmap);
                }
                for (i=0; i<units_per; i++) { //Adds all the correlated units to make ONE bitmap
                    bitmap+=bip[i];
                }
                shift_num++;
            }
        }
    }
        
    //INSERT bitmap INTO LINKED LIST:
    //LL MIGHT need to be referenced by the struct, piece
    //i.e. insert(bitmap,pie.LIL);
    insert(bitmap,LIL);
    return bitmap;
}

void makeTable(int dim) {
    int indeX, indeY, indeZ,ctr=0;
    for (indeX=0; indeX<dim; indeX++)
        for (indeY=0; indeY<dim; indeY++)
            for (indeZ=0; indeZ<dim; indeZ++) {
                refTable[indeX][indeY][indeZ] = 1 << ctr;
                printf("%d",refTable[indeX][indeY][indeZ]);
                ctr++;
            }
}
