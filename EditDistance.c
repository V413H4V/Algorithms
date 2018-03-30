#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*############################################
# Author: Vaibhav Murkute
# Program: Edit Distance - Dynamic Programming
# Date: 20/03/2018
##############################################*/


int minInt(int a, int b, int c);

int main()
{
    char input[202];
    char* str1;
    char* str2;

    memset(input,'\0',sizeof(input));

    do{
        printf("Enter two words separated by a space (e.g.: cat someone).Stop with: -1 -1 :\n");
        fgets(input,sizeof(input),stdin);
        input[strcspn(input,"\n")]='\0';   // to remove trailing new line character put by fgets()

        if(strcmp(input,"-1 -1")==0 || strcmp(input,"-1") == 0){
            break;
        }

        str1 = strtok(input," ");
        str2 = strtok(NULL," ");    // considering only two words entered by user

        printf("\n\r");
        printf("First: %s\n",str1);
        printf("Second: %s\n",str2);
        printf("\n");

        int distMatrix[strlen(str1)+1][strlen(str2)+1];
        memset(distMatrix,'\0',sizeof(distMatrix[0][0])*(strlen(str1)+1)*(strlen(str2)+1)); // clearing distMatrix

        // initializing 1st row and 1st column of distance Matrix
        int i=0;
        for(;i<=strlen(str2);i++){
            distMatrix[0][i] = i;
        }

        int j=0;
        for(;j<=strlen(str1);j++){
            distMatrix[j][0] = j;
        }

        int p,q;
        for(p=0;str1[p];p++){
            for(q=0;str2[q];q++){
                if(str1[p] == str2[q]){
                    distMatrix[p+1][q+1] = distMatrix[p][q];
                }else{
                    distMatrix[p+1][q+1] = minInt(distMatrix[p+1][q],distMatrix[p][q],distMatrix[p][q+1]) + 1;
                }
            }
        }

        int x,y;
        for(x=0; x <= (strlen(str1)+1);x++){

            for(y=0;y <= (strlen(str2)+1);y++){

                if((y-2) >= 0 && (x)==0){
                    printf("%3c|",str2[y-2]);
                }else if((x-1) >= 0 && (y-1) >= 0){
                    printf("%3d|",distMatrix[x-1][y-1]);
                }else if((x-2) >= 0 && (y) == 0){
                    printf("%3c|",str1[x-2]);
                }else{
                    printf("%4c",'|');
                }

            }

            printf("\n\r");

            int z;
            for(z=0; z < 4*y; z++){
                printf("-");
            }

            printf("\n\r");
        }

        printf("\nEdit distance: %d\n", distMatrix[strlen(str1)][strlen(str2)]);

        printf("\n\r");

        int s = strlen(str1);
        int t = strlen(str2);
        int counter=0;
        char alignStr1[100];
        char alignStr2[100];
        char costStr[100];

        memset(alignStr1,'\0',sizeof(alignStr1));
        memset(alignStr2,'\0',sizeof(alignStr2));
        memset(costStr,'\0',sizeof(costStr));

        while(s > 0 || t > 0){
            if(str1[s-1] == str2[t-1]){
                costStr[counter] = '.';
                alignStr1[counter] = str1[s-1];
                alignStr2[counter] = str2[t-1];
                counter++;
                if(s>0)
                    s--;
                if(t>0)
                    t--;
                continue;

            }else{
                if((distMatrix[s][t]-1) == (distMatrix[s-1][t-1])){
                    costStr[counter] = 'X';
                    alignStr1[counter] = str1[s-1];
                    alignStr2[counter] = str2[t-1];
                    counter++;
                    if(s>0)
                        s--;
                    if(t>0)
                        t--;
                    continue;

                }else if((distMatrix[s][t]-1) == (distMatrix[s][t-1])){
                    costStr[counter] = 'X';
                    alignStr1[counter] = '-';
                    alignStr2[counter] = str2[t-1];
                    counter++;
                    if(t>0)
                        t--;
                    continue;

                }else if((distMatrix[s][t]-1) == (distMatrix[s-1][t])){
                    costStr[counter] = 'X';
                    alignStr1[counter] = str1[s-1];
                    alignStr2[counter] = '-';
                    counter++;
                    if(s>0)
                        s--;
                    continue;

                }
            }
        }

        printf("Alignment:\n\n\r");

        int temp1 = strlen(alignStr1)-1;
        for(;temp1>=0;temp1--){
            printf("%c ",alignStr1[temp1]);
        }
        printf("\n\r");

        int temp2 = strlen(alignStr2)-1;
        for(;temp2>=0;temp2--){
            printf("%c ",alignStr2[temp2]);
        }
        printf("\n\r");

        int temp3 = strlen(costStr)-1;
        for(;temp3>=0;temp3--){
            printf("%c ",costStr[temp3]);
        }
        printf("\n\r");

        printf("\n\r=========================================================================================\n\n\r");

    }while(strcmp(input,"-1 -1") != 0 && strcmp(input,"-1") != 0);


    return 0;
}

int minInt(int a, int b, int c){
    int min=a;
    min = (min < b) ? min : b;
    min = (min < c) ? min : c;

    return min;
}
