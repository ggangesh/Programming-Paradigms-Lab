#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Expr
{
    public:
    bool b;//to represent a expressio is a constant


    char op;
    int val;
    Expr *L;
    Expr *R;

    public :

    Expr(char op1,Expr* L1,Expr* R1)// to assign two expressions with a operator
    {
        b=false;
        op=op1;
        val=0;
        L=L1;
        R=R1;
    }

    Expr(char x1)//to assign a variable
    {
        b=false;
        op=x1;
        val=0;
        L=NULL;
        R=NULL;
    }

    Expr(int val1)//to assign a constant
    {
        b=true;
        val=val1;
        op='\0';
        L=NULL;
        R=NULL;
    }

    Expr()//default constructor
    {
        b=false;
        op='\0';
        val=0;
        L=NULL;
        R=NULL;
    }

};//End of class Expr


class primitive : public Expr
{
    public :

    Expr* primitiveDeriv(Expr* e)
    {


        if (e->b==true)//expression is a constant
        {
            Expr* d= new Expr(0);//assign 0

            return d;
        }// end of the case expression is a constant

        else //expression is not a constant
        {

            if ((e->op!='*')&&(e->op!='+'))//expression is a variable
            {
                if(e->op=='x')// variable x
                {
                    Expr* d= new Expr(1);//assign 1

                    return d;
                }

                else// some other variable
                {
                    Expr* d= new Expr(0);//assign 0

                    return d;
                }
            }// end of the case the expression is a variable
        }//end of condition the expression is not a constant

    }//end of deriv()

    void primitiveDisplay(Expr* r)
    {
        if(r->b==true)//expression is a constant
        {
            cout<<r->val;
        }

        else//expression is not a constant
        {
            if((r->op!='+')&&(r->op!='*'))//expression is a variable
            {
                cout<<r->op;
            }
        }
    }//end of display()

};//End of the class primitive

void print(Expr* r);
Expr* derivative(Expr* e);

class add : public Expr
{
    public :

    Expr* addDeriv(Expr* e)
    {
        Expr* d= new Expr('+',derivative(e->L),derivative(e->R));

        return d;
    }//end of deriv()

    void addDisplay(Expr* r)
    {
        cout<<"(";
        print(r->L);
        cout<<")";
        cout<<"+";
        cout<<"(";
        print(r->R);
        cout<<")";
    }

};//End of the class add




class multiply : public Expr
{
    public :

    Expr* multiplyDeriv(Expr* e)
    {
        Expr* e1= new Expr('*',e->R,derivative(e->L));
        Expr* e2= new Expr('*',e->L,derivative(e->R));

        Expr* d= new Expr('+',e1,e2);

        return d;
    }//end of deriv()

    void multiplyDisplay(Expr* r)
    {
        cout<<"(";
        print(r->L);
        cout<<")";
        cout<<"*";
        cout<<"(";
        print(r->R);
        cout<<")";
    }//end of display()

};//End of the class multiply



Expr* inputExp(string s);



int main()
{
    Expr *exp= new Expr();
    Expr *result= new Expr();
    string s;

    cout<<"Enter the expression in the format : (expression 1),operator,(expression 2)"<<endl;
    cout<<endl<<"Without commas and any spaces"<<endl<<endl;

    cin>>s;

    cout<<endl;

    exp=inputExp(s);

    result=derivative(exp);

    cout<<"Derivative is :";

    cout<<endl<<endl;
    print(result);

    cout<<endl<<endl;

    return 0;

}//End of main()

Expr* inputExp(string s)
{


    Expr *result1= new Expr();


    if((s.size()==1)&&(s.at(0)!='*')&&(s.at(0)!='+')&&((s.at(0)<48)||(s.at(0)>57)))//expression is a variable
    {
        Expr *result1= new Expr(s.at(0));

        return result1;

    }

    else//expression is not a variable
    {
        int len,i,c;
        len=s.length();
        c=0;

        for(i=0;i<len;i++)
        {
            if((s.at(i)>=48)&&(s.at(i)<=57));//digit do nothing

            else
            {
                c=1;//expression is combination of two expressions
            }

        }

        if(c==0)//expression is a constant
        {
            int n;
            stringstream(s) >> n;

            Expr *result1= new Expr(n);

            return result1;
        }

        else//expression is an operation on two expressions
        {

            int start1,end1,start2,end2;

            i=1;

            start1=1;
            int n1,n2;//to store  no. of opening and closing parenthesis respectively
            n1=1;n2=0;

            while(n1!=n2)
            {
                if((s.at(i))=='(')
                {
                    n1++;
                }

                if((s.at(i))==')')
                {
                    n2++;
                }

                i++;
            }

            i--;

            end1=i-1;

            start2=i+3;

            n1=1;n2=0;

            end2=len-2;

            string s1(s,start1,(end1-start1 + 1));
            string s2(s,start2,(end2-start2 + 1));

            Expr *result1= new Expr(s.at(i+1),inputExp(s1),inputExp(s2));

            return result1;

        }//end of the condition expression is an operation on two expressions

    }//end of the condition expression is not a variable

}//end of inputExp()



Expr* derivative(Expr* e)
{
    if ((e->op!='*')&&(e->op!='+'))
    {
        Expr* d= new Expr();

        primitive a;

        d = a.primitiveDeriv(e);

        return d;
    }



    else// expression is neither a constant nor a variable
    {
            if(e->op=='+')//derivative of sum
            {
                Expr* d= new Expr();

                add a;

                d = a.addDeriv(e);

                return d;
            }

            if(e->op=='*')//derivative of product
            {
                Expr* d= new Expr();

                multiply a;

                d = a.multiplyDeriv(e);

                return d;
            }

    }// end of the case expression is neither a constant nor a variable

}//end of function derivative

void print(Expr* r)
{
    if((r->op!='+')&&(r->op!='*'))
    {

        primitive a;

        a.primitiveDisplay(r);
    }

    else
    {
        if(r->op=='+')
        {

            add a;


            a.addDisplay(r);
        }

        if(r->op=='*')
        {

            multiply a;

            a.multiplyDisplay(r);
        }
    }
}//end of print()
