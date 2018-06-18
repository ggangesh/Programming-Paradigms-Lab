
//This is the updated version of previous program of symbolic differentiation using inheritance

//This version uses various features of inheritance, virtual functions and polymorphism. While the older version contained every
// member of class as public and the derived classes didnt use any property of inheritance

//One additional operator(-) of subtraction is added

#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

class Expr
{
    public:
    bool b;//to represent a expressio is a constant
    char op;

    double val;
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

    Expr(double val1)//to assign a constant
    {
        b=true;
        val=val1;
        op='\0';
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

   Expr(Expr* e1)//to assign complete value from a pointer
   {
        b=e1->b;
        op=e1->op;
        val=e1->val;
        L=e1->L;
        R=e1->R;
   }

    Expr()//default constructor
    {
        b=false;
        op='\0';
        val=0;
        L=NULL;
        R=NULL;
    }

    virtual Expr* Deriv()
    {
        return NULL;
    }

    virtual void Display()
    {
        return ;
    }

    virtual void Value(double x)
    {
        return;
    }

};//End of class Expr


class primitive : public Expr
{
    public :

    primitive(Expr* e1=NULL):Expr(e1){}

    Expr* Deriv()
    {


        if (b==true)//expression is a constant
        {
            Expr* d= new Expr(0);//assign 0

            return d;
        }// end of the case expression is a constant

        else //expression is not a constant
        {

            if ((op!='*')&&(op!='+')&&(op!='-'))//expression is a variable
            {
                if(op=='x')// variable x
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

    void Display()
    {
        if(b==true)//expression is a constant
        {
            cout<<val;
        }

        else//expression is not a constant
        {
            if((op!='+')&&(op!='*')&&(op!='-'))//expression is a variable
            {
                cout<<op;
            }
        }
    }//end of display()

    void Value(double x)
    {
        if(b==true)//expression is a value
        {
        }

        else
        {
            if (op=='x')//expression is x variable
            {
                b=true;
                op='\0';
                val=x;
            }// end of the case the expression is x variable
        }

    }

};//End of the class primitive

void print(Expr* r);
Expr* derivative(Expr* e);
void Valuation(Expr* r,double x);

class add : public Expr
{
    public :

    add(Expr* e1=NULL):Expr(e1){}

    Expr* Deriv()
    {
        Expr* d= new Expr('+',derivative(L),derivative(R));

        return d;
    }//end of deriv()

    void Display()
    {
        cout<<"(";
        print(L);
        cout<<")";
        cout<<"+";
        cout<<"(";
        print(R);
        cout<<")";
    }

    void Value(double x)
    {
        Valuation(L,x);
        double v1;
        v1=L->val;

        Valuation(R,x);
        double v2;
        v2=R->val;

        b=true;
        op='\0';
        val=v1+v2;
        L=NULL;
        R=NULL;

    }//end of Value()



};//End of the class add


class subtract : public Expr
{
    public :

    subtract(Expr* e1=NULL):Expr(e1){}

    Expr* Deriv()
    {
        Expr* d= new Expr('-',derivative(L),derivative(R));

        return d;
    }//end of deriv()

    void Display()
    {
        cout<<"(";
        print(L);
        cout<<")";
        cout<<"-";
        cout<<"(";
        print(R);
        cout<<")";
    }

    void Value(double x)
    {
        Valuation(L,x);
        double v1;
        v1=L->val;

        Valuation(R,x);
        double v2;
        v2=R->val;

        b=true;
        op='\0';
        val=v1-v2;
        L=NULL;
        R=NULL;

    }//end of Value()

};//End of the class add





class multiply : public Expr
{
    public :

    multiply(Expr* e1=NULL):Expr(e1){}

    Expr* Deriv()
    {
        Expr* l= new Expr('*',R,derivative(L));
        Expr* r= new Expr('*',L,derivative(R));

        Expr* d= new Expr('+',l,r);

        return d;
    }//end of deriv()

    void Display()
    {
        cout<<"(";
        print(L);
        cout<<")";
        cout<<"*";
        cout<<"(";
        print(R);
        cout<<")";
    }//end of display()

    void Value(double x)
    {
        Valuation(L,x);
        double v1;
        v1=L->val;

        Valuation(R,x);
        double v2;
        v2=R->val;

        b=true;
        op='\0';
        val=v1*v2;
        L=NULL;
        R=NULL;

    }//end of Value()

};//End of the class multiply



Expr* inputExp(string s);



int main()
{
    Expr *exp= new Expr();
    Expr *der= new Expr();
    string s;
    int c=0;
    double x,vexp,vder,e;

    x=1;

    cout<<"Enter the expression in the format : (expression 1),operator,(expression 2)"<<endl;
    cout<<endl<<"Without commas and any spaces"<<endl<<endl;

    cin>>s;

    cout<<endl<<"Enter the value of epsilon : "<<endl;
    cin>>e;

    cout<<endl;

    exp=inputExp(s);


    Valuation(exp,x);
    vexp=exp->val;//calculating value of expression
    exp=inputExp(s);//restoring the expression


    der=derivative(exp);
    exp=inputExp(s);//restoring the expression

    cout<<"Derivative of expression is :";

    cout<<endl<<endl;
    print(der);//displaying derivative expression

    Valuation(der,x);
    vder=der->val;//calculating the value of derivative
    der=derivative(exp);//restoring the derivative
    exp=inputExp(s);//restoring the expression


    while((abs(vexp)>e)&&(c<=10000))
    {
        x=x-(vexp/vder);//updating x


        Valuation(exp,x);
        vexp=exp->val;//updating value of expression
        exp=inputExp(s);//restoring the expression


        Valuation(der,x);
        vder=der->val;//updating the value of derivative
        der=derivative(exp);//restoring the derivative
        exp=inputExp(s);//restoring the expression

    }

    cout<<endl<<endl;
    if(c>10000)
    {
        cout<<"No root found";
    }

    else
    {
        cout<<"The root of the expression is x = "<<x;
    }

    cout<<endl<<endl;

    return 0;

}//End of main()

Expr* inputExp(string s)
{


    Expr *result1= new Expr();


    if((s.size()==1)&&(s.at(0)!='*')&&(s.at(0)!='+')&&(s.at(0)!='-')&&((s.at(0)<48)||(s.at(0)>57)))//expression is a variable
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
    Expr* expr;

    if ((e->op!='*')&&(e->op!='+')&&(e->op!='-'))//expression is either a constant or variable
    {
        Expr* d= new Expr();

        primitive a(e);

        expr=&a;

        d = expr->Deriv();

        return d;
    }



    else// expression is neither a constant nor a variable
    {
            if(e->op=='+')//derivative of sum
            {
                Expr* d= new Expr();

                add a(e);

                expr=&a;

                d = expr->Deriv();

                return d;
            }

            if(e->op=='-')//derivative of sum
            {
                Expr* d= new Expr();

                subtract a(e);

                expr=&a;

                d = expr->Deriv();

                return d;
            }

            if(e->op=='*')//derivative of product
            {
                Expr* d= new Expr();

                multiply a(e);

                expr=&a;

                d = expr->Deriv();

                return d;
            }

    }// end of the case expression is neither a constant nor a variable

}//end of function derivative

void print(Expr* r)
{
    Expr* expr;

    if((r->op!='+')&&(r->op!='*')&&(r->op!='-'))
    {

        primitive a(r);

        expr=&a;

        expr->Display();
    }

    else
    {
        if(r->op=='+')
        {

            add a(r);

            expr=&a;

            expr->Display();
        }

        if(r->op=='-')
        {

            subtract a(r);

            expr=&a;

            expr->Display();
        }

        if(r->op=='*')
        {

            multiply a(r);

            expr=&a;

            expr->Display();
        }
    }
}//end of print()

void Valuation(Expr* r,double x)
{
    Expr* expr;

    if((r->op!='+')&&(r->op!='*')&&(r->op!='-'))
    {

        primitive a(r);

        expr=&a;

        expr->Value(x);

        r->b=expr->b;
        r->op=expr->op;
        r->val=expr->val;
        r->L=expr->L;
        r->R=expr->R;

    }

    else
    {
        if(r->op=='+')
        {

            add a(r);

            expr=&a;

            expr->Value(x);

            r->b=expr->b;
            r->op=expr->op;
            r->val=expr->val;
            r->L=expr->L;
            r->R=expr->R;
        }

        if(r->op=='-')
        {

            subtract a(r);

            expr=&a;

            expr->Value(x);

            r->b=expr->b;
            r->op=expr->op;
            r->val=expr->val;
            r->L=expr->L;
            r->R=expr->R;
        }

        if(r->op=='*')
        {

            multiply a(r);

            expr=&a;

            expr->Value(x);

            r->b=expr->b;
            r->op=expr->op;
            r->val=expr->val;
            r->L=expr->L;
            r->R=expr->R;
        }
    }
}//End of valuation()
