#include <iostream>
using namespace std;

class board
{
    int a[8][8];
    int i,j;

    //public member functions and variables :
public:

    int c;//c storess the number of queens placed
    //constuctor :
    board()
    {

        c=0;

        //code to initialize the board
        for(i=0; i<8; i++)
        {
            for(j=0; j<8; j++)
            {
                a[i][j]=0;
            }
        }

        i=0;
        j=0;
    }//end of board()



    void FillNext()
    {
        if((i>8)&&(c<8))

        {
            BackTrack();

        }


        if(Valid(i,j))
        {
            c++;
            a[i][j]=1;
            i++;
            j=0;
        }

        else
        {
            PosUpdate();
        }
    }//end of FillNext()

    void PosUpdate()
    {

        j++;

        if(j>7)// no valid position found
        {
            BackTrack();

        }
    }//end of PosUpdate()

    bool Valid(int p, int q)
    {
        bool checkLD,checkRD,checkR,checkC;
        checkLD=true;
        checkRD=true;
        checkR=true;
        checkC=true;

        int x,y;

        for(x=0; x<8; x++) //to check whether row is valid
        {
            if(a[p][x]==1)
            {
                checkR=false;
            }
        }

        for(x=0; x<8; x++) //to check whether column is valid
        {
            if(a[x][q]==1)
            {
                checkC=false;
            }
        }

        //To check whether left diagonal is valid
        x=p;
        y=q;
        while((x<8)&&(y<8))
        {
            if(a[x][y]==1)
            {
                checkLD=false;
            }

            x++;
            y++;
        }

        x=p;
        y=q;
        while((x>=0)&&(y>=0))
        {
            if(a[x][y]==1)
            {
                checkLD=false;
            }

            x--;
            y--;
        }

        //To check whether right diagonal is valid
        x=p;
        y=q;
        while((x>=0)&&(y<8))
        {
            if(a[x][y]==1)
            {
                checkRD=false;
            }

            x--;
            y++;
        }

        x=p;
        y=q;
        while((x<8)&&(y>=0))
        {
            if(a[x][y]==1)
            {
                checkRD=false;
            }

            x++;
            y--;
        }


        return (checkLD&&checkRD&&checkR&&checkC&&(p<8)&&(q<8));


    }//end of Valid()

    void Display()
    {
        for(int x=0; x<8; x++)
        {
            for(int y=0; y<8; y++)
            {
                cout<<a[x][y]<<"   ";
            }//end of inner loop

            cout<<endl;
        }//end of outer loop

        cout<<endl;
    }//end of Display()

    void BackTrack()
    {
        c--;
        i=i-1;

        for(j=0; j<8; j++)
        {
            if(a[i][j]==1)
            {
                a[i][j]=0;
                j++;
                break;
            }
        }

    }//end of BackTrack()

    int Geti()
    {
        return i;
    }

};



int main()
{
    board b;
    int numsoln;
    numsoln=0;

    while (b.Geti()>=0)
    {

        if(b.c<8)
        {

            b.FillNext();

        }

        else
        {
            if(b.c==8)
            {
                cout<<"Board number : "<<(numsoln+1)<<endl;
                b.Display();
                b.BackTrack();
                numsoln++;
            }

            else
            {

                return -1;
            }
        }
    }//end of while
    cout<<"Total number of possibilities : "<<numsoln;
    return 0;
}//end of main()
