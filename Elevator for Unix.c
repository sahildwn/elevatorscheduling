#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX_ELEVATORS 10            //you can change the global max no of elevators from here


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-----PLEASE READ BELOW INFO BEFORE RUNNING THIS CODE---------@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//before any user runs this code please always remove the following 3 files that are schedule.txt s_e.txt and s_p.txt from there virtual machine desktop
//use the command-------> ( rm schedule.txt s_e.txt s_p.txt ) <--------- to remove these files
//now make fresh new files of them again so that the data from the code is written to them
//use the command -----> ( touch schedule.txt s_e.txt s_p.txt )<--------to make these files
//you will get certain warnings from after compiling this code but the code will run
// use this format while running the compiled a.out file ---->>>> ( a.out on k passenger.txt schedule.txt s_e.txt s_p.txt ) <<<-------- for example --(compiled_file 0 4 passenger1.txt schedule.txt s_e.txt s_p.txt)
// command line arguments starts from "on" which allows user to select whether code should run the online or the offline algorithm
// "k" is the no of elevators, if you want to set limit on k you can change the global variable of "MAX_ELEVATORS" ...rest are the files where the code will store the output
//


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


typedef struct      //here we define a stucture for an elevator with the below variables
{

    int cpass;      //value to store count of passengers
    int cf;         //value to store current floor
    int outtime;    //value to store time when passenger comes out of an elevator after reachinf destination
    int intimeafter;    //value to store after passenger goes in the elevator
    int ecount;         //value to store value of total passengers served by Elevator
    int purpose;        //value to store variable to update the purpose
    int arrivaltime;    //value to store passenger arrives and pushes the elevator button
    int delay;          //value to store time taken by the elevator to reach the passenger
    int des;            //value to store destination floor
    int cur;            //value to store current floor
    int elfcount;       //value of total floors covered by Elevator
    int g;              //value for storing elevator is going up or down towards the passenger's floor
    int delaycp;        //value for storing time by elevator to reach from its current floor to passenger floor
    int og;             //value to store time taken by passenger to arrive to destination
    int p;              //value to store purpose
    int eid;            //value to store elevator id
    int ft;             //value to store the minimum time to reach passenger's destination
    int s;              //value to store sign whether elevator is moving up or down



} elevator;


int etime(int s, int cflr, int dflr)    //this function returns the time from passenger's current floor to the destination
{
    int X = dflr - cflr;            // difference between current and destination floor of the passenger
    int result;

                                    // when s==0 means elevator moving down and s==1 means its moving up

    if (s==1 && X== 1)              //elevator moving up and needs to cover 1 floor
    {
        return 3;
    }

   else if (s==1 && X>1)            //elevator moving up and needs to cover more than 1 floor
    {
        int f = 3;
        while( X > 1)
        {
            f = f + 2;              //adding 2seconds if the elevator is covering more than one floor
            X = X - 1;
        }
        return f;
    }

    else if(s==0 && dflr == 1 && X == -1)        //elevator moving down while destination is 1st floor and needs to cover 1 floor
    {
        return 2;
    }
    else if(s==0 && dflr == 1 && X == -2)           //elevator moving down while destination is 1st floor and needs to cover 2 floor
    {
        return 4;
    }
    else if(s==0 && dflr == 1 && X<-2)              //elevator moving down while destination is 1st floor and needs to cover more than 1 floor
    {
        int f = 4;
        while (X < -2 )
        {
            f = f + 1;
            X = X + 1;
        }
        return f;
    }

    else if(s==0 && dflr > 1 && X == -1)            //elevator moving down while destination is other than 1st floor and needs to cover 1 floor
    {
        return 2;
    }
    else if(s==0 && dflr > 1 && X <-1)              //elevator moving down while destination is other than 1st floor and needs to cover more than 1 floor
    {
        int f = 2;

        while (X < -1 )
        {
            f = f + 1;
            X = X + 1;
        }
        return f;

    }
    else if(s==2 && X == 0)                         //elevator is on the same floor
    {
        return 0;
    }


}






int elevatorSelect(int **A, int n,elevator e[], int noe, int ftime)
//this is the program that does the selection of an elevator based upon which is closest to the passenger
{

    int i = n+1;            //current index
    int j =0;
    int r =0;


    if(ftime < noe)                     //if elevators are not busy
    {

        for(j =0; j<noe; j++)
        {
            if( e[j].p == 3 )           //initially every elevator's purpose will be set to 3 as they will first pick up the passengers
            {                              //so for example if there are 4 elevators this condition will make sure every elevator is used consecutively
                return j;                       //once all the four elevators purpose is not 3 then only next condition is follwed
                break;
            }
            else
            {
//                printf("checking next elevator");

            }
        }
    }
    else if(ftime >= noe)           //if all the elevators are busy
    {


//        printf("ALL ELEVATOR BUSY\n");
//        csign = checkUpDown(A,i);
        for(r = 0; r < noe; r++)
        {


            e[r].s = checkEUD(e[r].cf, *(*(A+i)+ 2));       //checks the sign where the elevator is heading up or down to pick up the passenger


//            printf("Elevator %d will be available at %d sec\n\n",r+1,e[r].outtime);



            e[r].delay = etime(  e[r].s, e[r].cf, *(*(A+i)+ 2)  );      //this calculates the time taken to reach from elevator's floor to the arrival floor of the passenger


            e[r].ft = e[r].delay + e[r].outtime;
//            printf("Time E%d will take to reach from %d to %d is : %d\n\n",r+1,e[r].cf, *(*(A+i)+ 2),e[r].delay);
//            printf("Elevator %d will reach passenger at %d\n\n",r+1,e[r].ft);
        }

//        printf("NEXT ELEVATOR WILL BE %d\n\n",findmin(e,noe)+1);
        return findmin(e,noe);                  //this returns the minimum or best value based upon the time taken by elevator to reach the passenger's destination


    }
}







int findmin(elevator e[],int noe)           //this returns the minimum value based upon the time taken by them to reach the passenger
{
//    printf("value of noe is %d\n",noe);
    int i,loc=0;
    int min = e[0].ft;
    for( i = 0; i < noe; i++)
    {
        if(e[i].ft < min)
        {
            min = e[i].ft;
            loc = i;                           //returns the index of the array e
        }

    }
//    printf("value of index for minimum element is %d\n",loc);
    return loc;
}



int checkEUD(int cflr, int dflr)            //this returns the sign, if elevator moving up return 1, down return 0 and if same floor return 0
{
    int d;
    d = dflr - cflr;

//    printf("value of d !!! is %d\n",d);
    //printf("value of A+2 is is %d\n",(*(A+i)+2));
    if(d > 0)
    {
        return 1;
    }
    else if(d < 0)
    {
        return 0;
    }
    else if( d == 0)
    {
        return 2;
    }
}



int checkUpDown(int **A, int i)         //returns 1 if elevator at index i is going up else 0 if going down
{
    int c1,c2,d;
    c1 = *(*(A+i)+3);                   //destination floor of the
    c2 = *(*(A+i)+2);                   //current floor of the
    d = c1 - c2;

//    printf("value of d !!! is %d\n",d);
    //printf("value of A+2 is is %d\n",(*(A+i)+2));
    if(d > 0)
    {
        return 1;
    }
    else if(d < 0)
    {
        return 0;
    }
}




void setupElevators(elevator e[], int size)         //initializes every elevators with the below variables
{
    int i;
    for(i = 0; i < size; i++)
    {
        e[i].cpass = 0;
        e[i].cf=1;
        e[i].outtime = 0;
        e[i].intimeafter = 0;
        e[i].ecount = 0;
        e[i].purpose = 3;
        e[i].arrivaltime = 0;
        e[i].delay = 0;
        e[i].des;
        e[i].elfcount = 0;
        e[i].g;
        e[i].delaycp;
        e[i].og;
        e[i].p = 3;
        e[i].eid;
        e[i].ft;
        e[i].s;


    }
}



void setupElevators(elevator [], int);




//<-----------------------------------------------------MAIN()----------------------------------------------------------->




int main(int argc, char *argv[])
{
    FILE *fp;                                                   //initializing file pointer
    int nr=1,nc=1,mycol =0;

    int p2 =3, p3 =3;
    char ch;

    fp = fopen(argv[3], "r");                                   //open passenger.txt file to read it
    // It succeeded!

    if(fp == NULL)                                              //if file is empty
    {
        printf("file not present");
        exit(1);
    }



    while((ch = fgetc(fp)) != EOF)                              //calculating the no of rows and columns in input file
    {
//        ch = fgetc(fp);
        if(ch == '\t')
        {
            nc++;
            mycol = nc;

        }
        else if(ch == '\n')
        {
            nr++;
            nc = 1;

        }


    }

    int rows = nr;
    //int prows = 2*nr;
    int columns = mycol;
//    printf("value of rows is %d\n",nr);
//    printf("value of column is %d\n",mycol);



    fseek(fp, 0, SEEK_SET);                         //reset the pointer to start or 0


    int **A, j,i;

    A = (int **)malloc(rows*sizeof(int *));         // allot dynamic memory to A for no of rows



    while(!feof(fp))                                //here we convert the input file to a 2D matrix and allot dynamic memory for columns
    {
        for (i=0; i<rows; i++)
        {
            *(A+i) = (int *)malloc(columns*sizeof(int));
            for (j=0; j<columns; j++)
            {
                fscanf(fp, "%d", &A[i][j]);
            }
        }
    }

//uncomment below code to print the 2-D matrix
//    for(i=0; i<rows; i++)
//    {
//        for(j=0; j<columns; j++)
//            printf("%d\t",  *(*(A+i)+j) );
//
//        printf("\n");
//    }




    int eid =1;
    int k = 0,F,X,csign;

    char f;
    int ftime=0;


    FILE *fp1,*fp3,*fp2;                    //initialize 3 pointers for schedule.txt, s_e.txt and s_p.txt files


    fp1 = fopen(argv[4],"a+");                      //schedule.txt file open and append below sentence
    fprintf(fp1,"Time\tEID\tFloor\tPurpose\n");
    fclose(fp1);


    fp2 = fopen(argv[5],"a+");                      //s_e.txt file open and append below sentence
    fprintf(fp2,"Time\tFloor\tPurpose\n");
    fclose(fp2);



    fp3 = fopen(argv[6],"a+");                      //s_p.txt file open and append below sentence
//    fprintf(fp3,"PID\tEID\tINTIME\tOUTTIME\n");
    fclose(fp3);



//<---------------------------------------ONLINE AND OFFLINE ALGORITMS BELOW----------------------------------------->






    int noe,y=0,a,t=0;
    elevator e[MAX_ELEVATORS];
//    elevator e[MAX_ELEVATORS];
    i=0;
    noe = atoi(argv[2]);                                    //no of elevators also atoi converts strings argument to integer

    setupElevators(e, noe);                                //based upon the no of elevators each elevator will be initialized with certain parameters and that too in a structure
    a = atoi(argv[1]);                                     //check for online or offline input








//<-----------------------------------OFFLINE ALGORITHM--------------------------------->

    if( a == 1) //OFFLINE ALGORITHM
    {

        for(i=0; i<rows; i++)
        {

            if( e[y].cpass<10 && (*(*(A+i)+ 1)) < 86400 && *(*(A+i)+ 2) > 0)    //if passenger count in one elevator is less than 10, passenger arrival time is within 86400 seconds
            {

                csign = checkUpDown(A,i);                       //checks at index i or row of the file where is the elevator heading up or down


                e[y].g = checkEUD(e[y].cf,  *(*(A+i)+2));       //check whether elevator is going up or down towards the passenger's floor

                e[y].delaycp = etime( e[y].g, e[y].cf,   *(*(A+i)+2) );         //time by elevator to reach from its current floor to passenger floor

                e[y].og = e[y].outtime + e[y].delaycp;          //time taken by passenger to arrive to destination

                e[y].arrivaltime = *(*(A+i)+1);



                if(  (*(*(A+i)+ 1)) >  e[y].og)                         //when passenger arrives after elevator reaches arrival floor : ie elevator reaches before passenger
                {
                    e[y].intimeafter = e[y].arrivaltime + 2;

                }
                else if( (*(*(A+i)+ 1)) <  e[y].og )                    //when passenger arrives before the elevator reaches arrival floor : ie elevator takes time to arrive
                {
                    e[y].intimeafter = e[y].outtime + 2 + e[y].delaycp;
                }
                else if( (*(*(A+i)+ 1)) ==  e[y].og )                   //when passenger arrives at the same moment as elevator
                {
                    e[y].intimeafter = e[y].arrivaltime + 2;
                }




                e[y].delay = etime(  csign, *(*(A+i)+ 2), *(*(A+i)+ 3)  );          // time taken by elevator to reach from arrival floor to its destination floor

                e[y].outtime = e[y].intimeafter + 2 + e[y].delay;                   //2 seconds addition for coming out of the elevator


                e[y].p=3;                                                   //opening the schedule.txt file and updating data ---> time e_id fl purpose
                fp1 = fopen(argv[4],"a+");
                fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].intimeafter-2,y+1,*(*(A+i)+ 2),e[y].p );
                fclose(fp1);

                fp2 = fopen(argv[5],"a+");                                   //opening the s_e.txt file and updating data ----> time fl purpose
                fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                fclose(fp2);


                fp3 = fopen(argv[6],"a+");                                  //opening the s_p.txt file and updating the data  --->  p_id e_id in_time off_time
                fprintf(fp3,"%d\t%d\t%d\t%d\n",*(*(A+i)),y+1,e[y].intimeafter,e[y].outtime );
                fclose(fp3);

                e[y].cpass++;               //increment the passenger count in order to check maximum no of passengers in one elevator is not greater than 10, also this value is reset to 0
                e[y].ecount++;              //increment the passenger count in order to return total passengers served by this elevator, also this count wont be reset as it sis required at the end


                if(i+1<rows)                //here we check whether passengers are arriving at the same arrival time and on the same floor
                {

                    F = *(*(A+i+1)+2) - *(*(A+i)+2);        //difference between current floor of the i th and the i+1 th passenger
                    X = *(*(A+i+1)+1) - *(*(A+i)+1);        //difference between the arrival time of the i th and the i + 1 th passenger

                    if(F == 0 && X == 0 && e[y].cpass<10)   //if both the passengers are on the same floor and arrive at the same arrival time
                    {

                        y = y;

                        e[y].p = 3;
                        e[y].intimeafter = e[y].intimeafter -1;



                    }

                    else if(F != 0 && X == 0 && e[y].cpass<10)  //if both passenger arrives at the same time but differenct floors
                    {                                               // in this case we reset the no of passengers to 0 and start opening all the files and writing data in it


                        e[y].cpass = 0;

                        e[y].cf = *(*(A+i)+3);
                        if(csign == 1)                              //when elevator is moving up below are the list of changes we make in purposes
                        {
                            e[y].p = 1;  //up                                            // purpose changed from picking up the passenger to moving up
                            fp1 = fopen(argv[4],"a+");                          //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].intimeafter,y+1,*(*(A+i)+ 2),e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                          //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                            e[y].p = 5;  //stop                                          //purpose changed from moving up to stop
                            fp1 = fopen(argv[4],"a+");                                          //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].outtime-2,y+1,e[y].cf,e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                      //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                            e[y].p = 4;  //drop off                                       //purpose changed from stopping to dropping off passengers
                            fp1 = fopen(argv[4],"a+");                                  //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].outtime,y+1,e[y].cf,e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                          //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                        }
                        else
                        {
                            e[y].p = 2;  //down                             //when elevator is moving down, below are the list of changes we make in purposes and other data
                            fp1 = fopen(argv[4],"a+");                          //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].intimeafter,y+1,*(*(A+i)+ 2),e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                              //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                            e[y].p = 5;  //stop
                            fp1 = fopen(argv[4],"a+");                      //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].outtime-2,y+1,e[y].cf,e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                          //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                            e[y].p = 4;  //drop
                            fp1 = fopen(argv[4],"a+");                              //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].outtime,y+1,e[y].cf,e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                      //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);
                        }

                        e[y].des = *(*(A+i)+ 3);
                        e[y].cur = *(*(A+i)+ 2);
                        e[y].elfcount = e[y].elfcount + abs(e[y].des - e[y].cur);       //this calculates the no of floors the elevator has covered

                        e[y].cf = *(*(A+i)+3);

                        ftime++;

                        if(*(*(A+i)+ 2) > 0 && (*(*(A+i+1)+ 1)) <= 86400)
                        {


                            y = elevatorSelect(A,i,e, noe,ftime);               //this is where we call the elevator for the next passenger
                        }




                    }

                    else if( (F != 0 || F==0) && X != 0 )       //if  both passengers arrive at different floors ad different times
                    {


                        e[y].cpass = 0;

                        e[y].cf = *(*(A+i)+3);
                        if(csign == 1)
                        {
                            e[y].p = 1;  //up
                            fp1 = fopen(argv[4],"a+");                                   //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].intimeafter,y+1,*(*(A+i)+ 2),e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                          //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                            e[y].p = 5;  //up
                            fp1 = fopen(argv[4],"a+");                                      //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].outtime-2,y+1,e[y].cf,e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                              //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                            e[y].p = 4;  //up
                            fp1 = fopen(argv[4],"a+");                                          //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].outtime,y+1,e[y].cf,e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                          //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                        }
                        else
                        {
                            e[y].p = 2;  //down
                            fp1 = fopen(argv[4],"a+");                                              //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].intimeafter,y+1,*(*(A+i)+ 2),e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                          //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                            e[y].p = 5;  //stop
                            fp1 = fopen(argv[4],"a+");                                              //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].outtime-2,y+1,e[y].cf,e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                              //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                            e[y].p = 4;  //drop
                            fp1 = fopen(argv[4],"a+");                                                  //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].outtime,y+1,e[y].cf,e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                              //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);
                        }

                        e[y].des = *(*(A+i)+ 3);
                        e[y].cur = *(*(A+i)+ 2);
                        e[y].elfcount = e[y].elfcount + abs(e[y].des - e[y].cur);

                        e[y].cf = *(*(A+i)+3);

                        ftime++;

                        if(*(*(A+i)+ 2) > 0 && (*(*(A+i+1)+ 1)) < 86400)
                        {


                            y= elevatorSelect(A,i,e, noe,ftime);        //this is where we call the elevator for the next passenger
                        }
                        else
                        {
                            break;
                        }


//
                    }


                }
                else
                {
//                index >rows
                }
//


            }//after for if statemnt
            else if(*(*(A+i)+ 2) == 0)
            {
//            printf("Caught exception row exceeded range\n");
            }
            else
            {
                printf("arrival time exceeds 86400 sec\n");
            }


        }


    }


//<--------------------------------------------ONLINE ALGORITHM------------------------------------------------->



    else if( a == 0)  //ONLINE ALGORITHM
    {
        while(t < 86400)        //if timer is running within 86400 seconds
        {


            if(  t == *(*(A+i)+1 ) )        //if the timer and the passenger's arrival time matches
            {

                y = elevatorSelect(A,i,e, noe,ftime);       //select an elevator at that instant with no future data

                if( e[y].cpass<10 && *(*(A+i)+ 2) > 0)
                {

                    csign = checkUpDown(A,i);


                    e[y].g = checkEUD(e[y].cf,  *(*(A+i)+2));

                    e[y].delaycp = etime( e[y].g, e[y].cf,   *(*(A+i)+2) );

                    e[y].og = e[y].outtime + e[y].delaycp;

                    e[y].arrivaltime = *(*(A+i)+1);


                    if(  (*(*(A+i)+ 1)) >  e[y].og)
                    {
                        e[y].intimeafter = e[y].arrivaltime + 2;

                    }
                    else if( (*(*(A+i)+ 1)) <  e[y].og )
                    {
                        e[y].intimeafter = e[y].outtime + 2 + e[y].delaycp;
                    }
                    else if( (*(*(A+i)+ 1)) ==  e[y].og )
                    {
                        e[y].intimeafter = e[y].arrivaltime + 2;
                    }




                    e[y].delay = etime(  csign, *(*(A+i)+ 2), *(*(A+i)+ 3)  );          // time to reach from pass flr to dest flr

                    e[y].outtime = e[y].intimeafter + 2 + e[y].delay;


                    e[y].p=3;
                    fp1 = fopen(argv[4],"a+");                                          //opening the schedule.txt file and updating data ---> time e_id fl purpose
                    fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].intimeafter-2,y+1,*(*(A+i)+ 2),e[y].p );
                    fclose(fp1);

                    fp2 = fopen(argv[5],"a+");                                          //opening the s_e.txt file and updating data ----> time fl purpose
                    fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                    fclose(fp2);

                    fp3 = fopen(argv[6],"a+");                                      //opening the s_p.txt file and updating the data  --->  p_id e_id in_time off_time
                    fprintf(fp3,"%d\t%d\t%d\t%d\n",*(*(A+i)),y+1,e[y].intimeafter,e[y].outtime );
                    fclose(fp3);


                    e[y].cpass++;
                    e[y].ecount++;



                    F = *(*(A+i+1)+2) - *(*(A+i)+2);            //checks the difference between the ith passenger's current floor and i+1th passenger's current floor
                    X = *(*(A+i+1)+1) - *(*(A+i)+1);            //checks the diffirence between the arrival time of the ith passenger and the i+1th passenger

                    if(F == 0 && X == 0 && e[y].cpass<10)
                    {


                        i++;
                        e[y].p = 3;
                        e[y].intimeafter = e[y].intimeafter -1;



                    }

                    else if(F != 0 && X == 0 && e[y].cpass<10)
                    {


                        e[y].cpass = 0;

                        e[y].cf = *(*(A+i)+3);
                        if(csign == 1)
                        {
                            e[y].p = 1;  //up
                            fp1 = fopen(argv[4],"a+");                                                  //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].intimeafter,y+1,*(*(A+i)+ 2),e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                          //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                            e[y].p = 5;  //up
                            fp1 = fopen(argv[4],"a+");                                                  //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].outtime-2,y+1,e[y].cf,e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                          //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                            e[y].p = 4;  //up
                            fp1 = fopen(argv[4],"a+");                                                  //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].outtime,y+1,e[y].cf,e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                              //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                        }
                        else
                        {
                            e[y].p = 2;  //down
                            fp1 = fopen(argv[4],"a+");                                                  //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].intimeafter,y+1,*(*(A+i)+ 2),e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                          //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                            e[y].p = 5;  //stop
                            fp1 = fopen(argv[4],"a+");                                                  //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].outtime-2,y+1,e[y].cf,e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                          //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                            e[y].p = 4;  //drop
                            fp1 = fopen(argv[4],"a+");                                                  //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].outtime,y+1,e[y].cf,e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                              //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);
                        }

                        e[y].des = *(*(A+i)+ 3);
                        e[y].cur = *(*(A+i)+ 2);
                        e[y].elfcount = e[y].elfcount + abs(e[y].des - e[y].cur);

                        e[y].cf = *(*(A+i)+3);


                        i++;
                        ftime++;


                    }

                    else if( (F != 0 || F==0) && X != 0 )
                    {



                        e[y].cpass = 0;

                        e[y].cf = *(*(A+i)+3);
                        if(csign == 1)
                        {
                            e[y].p = 1;  //up
                            fp1 = fopen(argv[4],"a+");                                              //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].intimeafter,y+1,*(*(A+i)+ 2),e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                              //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                            e[y].p = 5;  //up
                            fp1 = fopen(argv[4],"a+");                                                      //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].outtime-2,y+1,e[y].cf,e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                                      //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                            e[y].p = 4;  //up
                            fp1 = fopen(argv[4],"a+");                                          //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].outtime,y+1,e[y].cf,e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                                  //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                        }
                        else
                        {
                            e[y].p = 2;  //down
                            fp1 = fopen(argv[4],"a+");                                      //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].intimeafter,y+1,*(*(A+i)+ 2),e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                  //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                            e[y].p = 5;  //stop
                            fp1 = fopen(argv[4],"a+");                                          //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].outtime-2,y+1,e[y].cf,e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                                  //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);

                            e[y].p = 4;  //drop
                            fp1 = fopen(argv[4],"a+");                                              //opening the schedule.txt file and updating data ---> time e_id fl purpose
                            fprintf(fp1,"%d\t%d\t%d\t%d\n",e[y].outtime,y+1,e[y].cf,e[y].p );
                            fclose(fp1);

                            fp2 = fopen(argv[5],"a+");                                          //opening the s_e.txt file and updating data ----> time fl purpose
                            fprintf(fp2,"%d\t%d\t%d\n",*(*(A+i)+ 1),*(*(A+i)+ 2),e[y].p );
                            fclose(fp2);
                        }

                        e[y].des = *(*(A+i)+ 3);
                        e[y].cur = *(*(A+i)+ 2);
                        e[y].elfcount = e[y].elfcount + abs(e[y].des - e[y].cur);

                        e[y].cf = *(*(A+i)+3);


                        i++;
                        t++;
                        ftime++;


//
                    }


                    else
                    {
//                index >rows
                    }
//


                    //after for if statemnt
                }
            }
            else
            {
//                printf("%d seconds have passed\n",t);
                t++;
            }



            if(t==86400 || *(*(A+i)+1 )==0 )            //breaks....if time reaches 86400 seconds or last line of the input file is not present
            {
                break;
            }

        } //while
    }




//<--------------------------------------------------METRIC CALCULATIONS------------------------------------------------------------->





    FILE *fp5;                                          //initialize a pointer for opening and reading s_p.txt file
    int passrow=1,passcolum=1,mypascol =0;


    char chp;
// Attempt to open the file "file.txt" with reading persmissions.
    fp5 = fopen(argv[6], "r");
// It succeeded!

    if(fp5 == NULL)
    {
        printf("passenger file not present");
        exit(1);
    }

    while(!feof(fp5))                               //row and columns calculations
    {
        chp = fgetc(fp5);
        if(chp == '\t')
        {
            passcolum++;
            mypascol = passcolum;

        }
        else if(chp == '\n')
        {
            passrow++;
            passcolum = 1;

        }
    }

    int rowsp = passrow;
//int prows = 2*nr;
    int columnsp = mypascol;
//    printf("value of rows is %d\n",rowsp);
//    printf("value of column is %d\n",columnsp);




    fseek(fp5, 0, SEEK_SET);                //resetting the file pointer to zero

    int **P, m, n;



    P = (int **)malloc(rowsp*sizeof(int *));    //allocate dynamic memory to rows




    while(!feof(fp5))                               //converting the input file into a 2D matrix
    {
        for (m=0; m<rowsp; m++)
        {
            *(P+m) = (int *)malloc(columnsp*sizeof(int));
            for (n=0; n<columnsp; n++)
            {
                fscanf(fp5, "%d", &P[m][n]);                //converting the s_p.txt file into a 2-D file using pointer to pointer method
            }
        }
    }

//    printf("value of rowsp is %d\n",rowsp);
//    printf("value of columnsp is %d\n",columnsp);
    i=0;
    j=0;
    printf("\n\n");



//<----------------------------Average waiting time = Σ(time get in an elevator – arrival time) / number of passengers-------------------->

    int sum = 0;
    i =0;

    for(i=0; i<rowsp-1; i++)
    {

        sum = sum + (   *(*(P+i)+2) - *(*(A+i)+1)   );                              //time get in an elevator – arrival time

    }

    int avgwait;

    avgwait = sum/rowsp-1;

    printf("value of avgwait is %d seconds \n\n",avgwait);              //<<<<<<<<<<<<<<<FIRST METRIC
//
    i =0;



//<-----------------------------Maximal waiting time = max (time get in an elevator – arrival time)------------------------>

    int max = ( *(*(P)+2) - *(*(A)+1) ) ;
    for(i=0; i<rowsp-1; i++)
    {

//        printf( "value of %d diff of intime arrtime is :%d\n",i,*(*(P+i)+2) - *(*(A+i)+1)   );

        if( max <  (*(*(P+i)+2) - *(*(A+i)+1))  )
        {
            max = (*(*(P+i)+2) - *(*(A+i)+1));              //max (time get in an elevator – arrival time)
        }


    }

    printf("value of max wait time is %d seconds \n\n",max);            //<<<<<<<<<<<<<<<SECOND METRIC




//<----------------------Average time to arrive destination = Σ(time get off an elevator – arrival time) / number of passengers-------------->

    int sum2 = 0;
    i =0;

    for(i=0; i<rowsp-1; i++)
    {

        sum2 = sum2 + (   *(*(P+i)+3) - *(*(A+i)+1)   );            //time get off an elevator – arrival time

    }

    int avgdest;

    avgdest = sum2/rowsp-1;

    printf("value of avgdest is %d seconds \n\n",avgdest);          //<<<<<<<<<<<<<<<THIRD METRIC




//<---------------------Maximal time to arrive destination = max (time get off an elevator – arrival time) --------------->


    i =0;


    int max2 = ( *(*(P)+3) - *(*(A)+1) ) ;
    for(i=0; i<rowsp-1; i++)
    {


        //printf( "value of %d outtime arrtime is :%d\n",i,*(*(P+i)+3) - *(*(A+i)+1)   );

        if( max2 <  (*(*(P+i)+3) - *(*(A+i)+1))  )
        {
            max2 = (*(*(P+i)+3) - *(*(A+i)+1));                     //max (time get off an elevator – arrival time)
        }


    }

    printf("value of max time to arrive destination is %d seconds \n\n",max2);      //<<<<<<<<<<<<<<<FOURTH METRIC





//<-----------------------------------total passengers served by Elevator and total floors traveled by Elevator---------->

    for(i = 0; i<noe; i++)
    {



        printf("value of total passengers served by Elevator %d is %d\n",i+1,e[i].ecount);      //<<<<<<<<<<<<<<<FIFTH METRIC
        printf("value of total floors traveled by Elevator %d is %d\n",i+1,e[i].elfcount);      //<<<<<<<<<<<<<<<SIXTH METRIC
        printf("\n");
    }


    for(i = 0; i<noe; i++)                                                      //opening and printing metric 5th and 6th in s_e.txt file
    {

        fp2 = fopen(argv[5],"a+");
        fprintf(fp2,"value of total passengers served by Elevator %d is %d\n",i+1,e[i].ecount);
        fprintf(fp2,"value of total floors traveled by Elevator %d is %d\n",i+1,e[i].elfcount);
        fclose(fp2);
    }

    fp3 = fopen(argv[6],"a+");                                                     //opening and printing metric 5th and 6th in s_p.txt file
    fprintf(fp3,"Average waiting time is : %d seconds \n\n",avgwait);
    fprintf(fp3,"Maximal waiting time is : %d seconds \n\n",max);
    fprintf(fp3,"Average time to arrive destination is : %d seconds \n\n",avgdest);
    fprintf(fp3,"Maximal time to arrive destination is %d seconds \n\n",max2);
    fclose(fp3);





    printf("<--------------------SCHEDULING DONE !!! FILES ARE READY !!!------------------------>\n");




    return 0;

}
