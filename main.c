#include <stdio.h>
#include <stdlib.h>



//Calendar
int calCell[14][13]={1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,1,1,0,0,0,0,0,0,1,1,1,1,
                    1,1,1,0,0,0,0,0,0,1,1,1,1,
                    1,1,1,0,0,0,0,0,0,0,1,1,1,
                    1,1,1,0,0,0,0,0,0,0,1,1,1,
                    1,1,1,0,0,0,0,0,0,0,1,1,1,
                    1,1,1,0,0,0,0,0,0,0,1,1,1,
                    1,1,1,0,0,0,0,0,0,0,1,1,1,
                    1,1,1,1,1,1,1,0,0,0,1,1,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1}; //1 : covered, 0 : not covered

int pieces[10][4][4]={0,1,0,0,0,1,0,0,0,1,0,0,1,1,0,0,
                    0,1,0,0,0,1,0,0,1,1,1,0,0,0,0,0,
                    1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,
                    1,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,
                    0,1,0,0,0,1,0,0,1,1,0,0,1,0,0,0,
                    1,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,
                    1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,
                    0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,
                    1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,
                    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0};

int piecesNb = 10;

//Every rotations of pieces
int rotations[40][4][4];
int rotationNb;

int usedPiece[10]={0,0,0,0,0,0,0,0,0,0}; //0 : unused, 1 ; used

int solutionNb = 0;

//Memorize solution found (check if a solution is counted twice)
int calSolution[14][13]={1,1,1,1,1,1,1,1,1,1,1,1,1,
                        1,1,1,1,1,1,1,1,1,1,1,1,1,
                        1,1,1,1,1,1,1,1,1,1,1,1,1,
                        1,1,1,0,0,0,0,0,0,1,1,1,1,
                        1,1,1,0,0,0,0,0,0,1,1,1,1,
                        1,1,1,0,0,0,0,0,0,0,1,1,1,
                        1,1,1,0,0,0,0,0,0,0,1,1,1,
                        1,1,1,0,0,0,0,0,0,0,1,1,1,
                        1,1,1,0,0,0,0,0,0,0,1,1,1,
                        1,1,1,0,0,0,0,0,0,0,1,1,1,
                        1,1,1,1,1,1,1,0,0,0,1,1,1,
                        1,1,1,1,1,1,1,1,1,1,1,1,1,
                        1,1,1,1,1,1,1,1,1,1,1,1,1,
                        1,1,1,1,1,1,1,1,1,1,1,1,1};




void rotate(int piece[4][4], int rotation[4][4]){

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            rotation[3-j][i] = piece[i][j];
        }
    }

}


void createRotation(){

    int piecesDone = 0;

    for(int k=0; k<piecesNb; k++){
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                rotations[4*k][i][j] = pieces[k][i][j];
            }
        }

        piecesDone++;

        rotate(pieces[k], rotations[piecesDone]);
        piecesDone++;

        rotate(rotations[piecesDone-1], rotations[piecesDone]);
        piecesDone++;

        rotate(rotations[piecesDone-1], rotations[piecesDone]);
        piecesDone++;

    }

}


void coverDate(int month, int qt, int day){

    //month
    if(month>0 && month<7){
        calCell[3][month+2] = 1;
    }
    if(month>6 && month<13){
        calCell[4][month-4] = 1;
    }

    //qt
    if(qt>0 && qt<8){
        calCell[5][qt+2]=1;
    }
    if(qt>7 && qt<15){
        calCell[6][qt-5]=1;
    }
    if(qt>14 && qt<22){
        calCell[7][qt-12]=1;
    }
    if(qt>21 && qt<29){
        calCell[8][qt-19]=1;
    }
    if(qt>28 && qt<32){
        calCell[9][qt-26]=1;
    }

    //day
    if(day>0 && day<5){
        calCell[9][day+5]=1;
    }
    if(day>4 && day<8){
        calCell[10][day+2]=1;
    }

}


//check if a piece can cover
int coverTF(int l, int c,int i1, int j1, int piece[4][4]){

    int booleen = 0;
    for(int i=l; i<l+4; i++){
        for(int j=c; j<c+4; j++){
            if((calCell[i][j]!=0) && (piece[i-l][j-c]==1)){

                return 0;
            }
            if(i==i1 && j==j1 && piece[i-l][j-c]==1){
                booleen=1;
            }
        }
    }

    return booleen;
}


//covers calendar with the number of the piece (1 to 10)
void cover(int l, int c, int piece[4][4], int k){

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(piece[i][j]){
                calCell[l+i][c+j]=k+1;
            }
        }
    }

}


void cancelPiece(int l, int c, int piece[4][4]){

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            //if value != 0
            if(piece[i][j]){
                calCell[l+i][c+j]=0;
            }
        }
    }

}


//Check if a solution has already been counted
int solutionCounted(){

    for(int i=3; i<11; i++){
        for(int j=3; j<10; j++){
            if(calCell[i][j]!= calSolution[i][j]){
                return 0;
            }
        }
    }

    return 1;
}


//cover the calendar with the pieces and count solutions
void coverCal(int calCell[14][13]){

    int i,j;
    //Through the calendar
    for(i=3; i<11; i++)
        for(j=3; j<10; j++)
            //When an empty call is found
            if(calCell[i][j]==0) {goto cover;}

            //Case with no solution
            if(solutionNb==0){
                solutionNb++;
                for(int i=3; i<11; i++){
                    for(int j=3; j<10; j++){
                        calSolution[i][j] = calCell[i][j];
                    }
                }
            }
            else{
                //Add a new solution
                if(solutionCounted() == 0){
                    solutionNb++;
                    for(int i=3; i<11; i++){
                        for(int j=3; j<10; j++){
                            calSolution[i][j] = calCell[i][j];
                        }
                    }
                }
            }

            cover:
                for(int pc=0; pc<10;pc++){
                    if(usedPiece[pc]==0){
                        if(pc==3 || pc==8 || pc==9){
                            rotationNb=2;
                        }
                        else{
                            rotationNb=4;
                        }

                        //Try to cover with the piece unused
                        for(int n=0;n<rotationNb;n++){
                                int i1=i-3;
                                if(i1<0) {i1=0;}
                                int j1=j-3;
                                if(j1<0) {j1=0;}

                                for(int i2=i1; i2<i1+4 ; i2++){
                                    for(int j2=j1; j2<j1+4; j2++){

                                    if( coverTF(i2,j2,i,j,rotations[4*pc+n]))
                                    {
                                        cover(i2,j2,rotations[4*pc+n],pc);
                                        usedPiece[pc]=1;
                                        coverCal(calCell);
                                        cancelPiece(i2,j2,rotations[4*pc+n]);
                                        usedPiece[pc]=0;
                                    }
                                }
                            }
                        }
                    }
                }

}


int main()
{

    createRotation();
    coverDate(7,8,1);
    coverCal(calCell);


    printf("%  2d solutions\n",solutionNb);


    return 0;

}



