#include <iostream>
#include <string>
using namespace std;
#define ll long long
#define ull unsigned long long
#define mod 1000000007
#define stack_size 3000

//*****************************************************************
//           Structure which hold biginteger and operator
//*****************************************************************
struct number
{
    string num;
    bool is_operator;
    char op;
};

//*****************************************************************
//                  Implementation of custom stack DS
//*****************************************************************
class C_stack
{
    number a[stack_size];
    int top;

public:
    C_stack()
    {
        top = -1;
    }

    void c_push(number ox)
    {
        if (top == stack_size - 1)
        {
            //  cout<<"stack overflow\n";
            return;
        }
        top++;
        a[top] = ox;
    }

    void c_pop()
    {
        if (top == -1)
        {
            // cout<<"stack underflow\n";
            return;
        }
        top = top - 1;
    }

    number c_top()
    {
        if (top == -1)
        {
            // cout << "stack is empty\n";
            cout<<"";
        }
        return a[top];
    }

    bool c_empty()
    {
        return (top == -1);
    }
};

//*****************************************************************
//                  Parsing the input string into objects
//*****************************************************************
int parse(string expression, number *infix)
{
    int n = 0;
    int i = 0;
    while (i < expression.size())
    {
        string curr = "";
        while ((i < expression.size()) && (expression[i] != '+') && (expression[i] != '-') && (expression[i] != 'x') && (expression[i] != '/'))
        {
            curr.push_back(expression[i]);
            i++;
        }
        // cout<<curr<<"\n";
        infix[n].num = curr;
        infix[n].is_operator = 0;
        n++;

        if (i < expression.size())
        {
            infix[n].num = "";
            infix[n].is_operator = 1;
            infix[n].op = expression[i];
            n++;
            i++;
        }
    }
    return n;
}

//*****************************************************************
//                  assigning priorities
//*****************************************************************
int getpriority(char op)
{
    if (op == 'x' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    return 0;
}

//*****************************************************************
//                  Infix to postfix
//*****************************************************************
void infix_to_postfix(number *infix, int n, number *postfix)
{
    int pi = 0;
    int ii = 0;
    C_stack st;

    for (int i = 0; i < n; i++)
    {
        if (!infix[i].is_operator)
        {
            postfix[pi++] = infix[i];
        }
        else
        {
            if (st.c_empty())
            {
                st.c_push(infix[i]);
            }
            else
            {
                if (getpriority(infix[i].op) > getpriority(st.c_top().op))
                {
                    st.c_push(infix[i]);
                }
                else
                {
                    while (!st.c_empty() && (getpriority(infix[i].op) <= getpriority(st.c_top().op)))
                    {
                        postfix[pi++] = st.c_top();
                        st.c_pop();
                    }
                    st.c_push(infix[i]);
                }
            }
        }
    }
    while (!st.c_empty())
    {
        postfix[pi++] = st.c_top();
        st.c_pop();
    }
}

void stringPreProcessing(string &s)
{
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        if ((s[i] == '0') && (i != n - 1))
        {
            s.erase(s.begin());
        }
        if (s[i] != '0')
        {
            break;
        }
    }
}

int compare(string s1, string s2)
{
    stringPreProcessing(s1);
    stringPreProcessing(s2);
    // cout<<s1<<" , "<<s2<<"\n";
    int n = s1.size();
    int m = s2.size();
    if (n < m)
        return -1;
    if (n > m)
        return 1;

    for (int i = 0; i < n; i++)
    {
        if ((s1[i] - '0') > (s2[i] - '0'))
            return 1;
        else if ((s1[i] - '0') < (s2[i] - '0'))
            return -1;
    }
    return 0;
}

//*****************************************************************
//           Reverse the string passed by reference
//*****************************************************************
void reverse(string &s)
{
    int n = s.size();
    for (int i = 0; i < (n / 2); i++)
    {
        swap(s[i], s[n - i - 1]);
    }
}
//*****************************************************************
//                  Big Integer Addition
//*****************************************************************
number bint_add(number a, number b)
{
    stringPreProcessing(a.num);
    stringPreProcessing(b.num);
    reverse(a.num);
    reverse(b.num);
    string ans = "";
    int carry = 0;
    int n = a.num.size();
    int m = b.num.size();
    int i = 0;
    int j = 0;
    while (i < n && j < m)
    {
        // cout<<(int)(a.num[i] - '0')<<" <-> "<<(int)(b.num[j] - '0')<<"\n";
        int temp = (int)(a.num[i] - '0') + (int)(b.num[j] - '0') + carry;
        carry = temp / 10;
        ans.push_back((temp % 10) + '0');
        i++;
        j++;
    }
    while (i < n)
    {
        // cout<<(int)(a.num[i] - '0')<<"\n";
        int temp = (int)(a.num[i] - '0') + carry;
        carry = temp / 10;
        ans.push_back((temp % 10) + '0');
        i++;
    }
    while (j < m)
    {
        // cout<<(int)(b.num[j] - '0')<<"\n";
        int temp = (int)(b.num[j] - '0') + carry;
        carry = temp / 10;
        ans.push_back((temp % 10) + '0');
        j++;
    }
    if (carry > 0)
    {
        ans.push_back((carry) + '0');
    }
    reverse(ans);
    number answer;
    answer.num = ans;
    answer.is_operator = 0;
    return answer;
}

//*****************************************************************
//                  Big Integer Subtraction
//*****************************************************************
number bint_sub(number a, number b)
{
    stringPreProcessing(a.num);
    stringPreProcessing(b.num);
    reverse(a.num);
    reverse(b.num);
    string ans = "";
    int n = a.num.size();
    int m = b.num.size();
    int i = 0, j = 0;
    int borrow = 0;
    while (i < n && j < m)
    {
        int num1 = (int)(a.num[i] - '0');
        int num2 = (int)(b.num[j] - '0');
        num1 = (num1 - borrow);
        if (num1 >= num2)
        {
            int temp = num1 - num2;
            ans.push_back((char)(temp + '0'));
            borrow = 0;
        }
        else
        {
            int temp = (num1 + 10) - num2;
            borrow = 1;
            ans.push_back((char)(temp + '0'));
        }
        i++;
        j++;
    }
    while (i < n)
    {
        if (borrow == 1)
        {
            int num = (int)(a.num[i] - '0');
            num = num - 1;
            if (num < 0)
            {
                num = num + 10;
                borrow = 1;
                ans.push_back((char)(num + '0'));
                i++;
            }
            else
            {
                ans.push_back((char)(num + '0'));
                borrow = 0;
                i++;
            }
        }
        else
        {
            int temp = (int)(a.num[i] - '0');
            ans.push_back((char)(temp + '0'));
            i++;
        }
    }

    reverse(ans);
    number answer;
    answer.num = ans;
    answer.is_operator = 0;
    return answer;
}

//*****************************************************************
//                  Big Integer Multiplication
//*****************************************************************
number bint_mul(number a, number b) // handle num*0 case
{
    stringPreProcessing(a.num);
    stringPreProcessing(b.num);
    reverse(a.num);
    reverse(b.num);
    int result[3500] = {};
    int n = a.num.size();
    int m = b.num.size();

    for (int i = 0; i < n; i++)
    {
        int carry = 0;
        for (int j = 0; j < m; j++)
        {
            int prod = ((int)(a.num[i] - '0') * (int)(b.num[j] - '0')) + result[i + j] + carry;
            carry = prod / 10;
            result[i + j] = prod % 10;
        }
        if (carry > 0)
            result[i + m] += carry;
    }

    string ans = "";
    int i = 3500 - 1;
    while (i >= 0 && result[i] == 0)
        i--;
    if (i == -1)
        ans = "0";
    else
        while (i >= 0)
            ans.push_back(result[i--] + '0');

    number answer;
    answer.num = ans;
    answer.is_operator = 0;

    return answer;
}

//*****************************************************************
//                  Big Integer Division
//*****************************************************************
number bint_div(number a, number b, number &rem)
{
    int result[3500] = {};
    int n = a.num.size();
    int m = b.num.size();
    string zero = "0";
    if (compare(b.num, zero) == 0)
    {
        number nan;
        nan.is_operator = 1;
        return a;
    }
    stringPreProcessing(a.num);
    stringPreProcessing(b.num);

    number answer;
    answer.is_operator = 0;
    answer.num = "";
    number curr;
    curr.num = "";
    curr.is_operator = 0;
    int i = 0;
    while (i < n)
    {
        int temp_ans = 1;
        while (i < n && curr.num.length() <= b.num.length()) // compare(curr.num , b.num)<=0 )
        {
            curr.num += a.num[i];
            i++;
        }
        stringPreProcessing(curr.num);
        // cout<<curr.num<<"/"<<b.num<<" = ";
        number temp = b;
        while (compare(curr.num, temp.num) >= 0)
        {
            curr = bint_sub(curr, temp);
            temp_ans++;
        }
        // cout<<temp_ans<<" - "<<curr.num<<"\n";
        string x = to_string(temp_ans - 1);
        answer.num += (x);
    }
    stringPreProcessing(curr.num);
    rem = curr;

    return answer;
}

//*****************************************************************
//          Evaluation of postfix expressions using BODMAS
//*****************************************************************
number postfix_eval(number *postfix, int n)
{
    C_stack st;
    for (int i = 0; i < n; i++)
    {
        if (!postfix[i].is_operator)
        {
            st.c_push(postfix[i]);
        }
        else
        {
            number a1 = st.c_top();
            st.c_pop();
            number a2 = st.c_top();
            st.c_pop();
            number ans;

            switch (postfix[i].op)
            {
            case '+':
                ans = bint_add(a2, a1);
                break;
            case '-':
                ans = bint_sub(a2, a1);
                break;
            case 'x':
                ans = bint_mul(a2, a1);
                break;
            case '/':
                ans = bint_div(a2, a1, ans);
                break;
            }
            st.c_push(ans);
        }
    }
    return st.c_top();
}

//*****************************************************************
//               Option 1: function implementing expression eval
//*****************************************************************
void expression_eval()
{
    string expression;

    cin >> expression;
    number infix[3000];

    int n = parse(expression, infix);
    number postfix[n + 1];
    infix_to_postfix(infix, n, postfix);
    // for(int i = 0 ; i < n ; i++)
    // {
    //    cout<<"("<<postfix[i].num<<" , "<<postfix[i].is_operator<<" , "<<postfix[i].op<<" ) \n";
    // }

    number answer = postfix_eval(postfix, n);
    cout << answer.num << "\n";
}

//*****************************************************************
//               Option 2: function implementing Exponentition
//*****************************************************************
number power(number x, number y)
{
    number rem;
    number b;
    b.num = "2";
    if (y.num == "0")
    {
        rem.num = "1";
    }
    else if ((int)(y.num[y.num.size()-1] - '0')%2 == 0)
    {
        number temp = power(x, bint_div(y,b,rem)); 
        rem =  bint_mul(temp, temp);
    }
    else
    {
        number temp = power(x, bint_div(y,b,rem)); 
        temp = bint_mul(temp, temp);
        rem = bint_mul(x, temp);
    }
    return rem;
}
/*
*/
void Exponentiation()
{
    string base;
    string exp;
    cin >> base >> exp;

    number b, temp;
    b.num = base;
    b.is_operator = 0;
    temp.num = exp;
    temp.is_operator = 0;

    number ans = power(b, temp);
    cout<<ans.num<<"\n";
}

//*****************************************************************
//               Option 3: function implementing GCD
//*****************************************************************
number Gcd(number a, number b) // problem in GCD 100 and 20
{
    string zero = "0";
    if (compare(b.num, zero) == 0)
    {
        return a;
    }
    number rem;
    bint_div(a, b, rem);
    return Gcd(b, rem);
}

void GCD_Driver()
{
    number num1, num2;
    cin >> num1.num >> num2.num;
    num1.is_operator = 0;
    num2.is_operator = 0;
    if (compare(num1.num, num2.num) <= 0)
    {
        number ans = Gcd(num2, num1);

        cout << ans.num << "\n";
        return;
    }
    number ans = Gcd(num1, num2);
    cout << ans.num << "\n";
}

//*****************************************************************
//               Option 4: function implementing Factorial
//*****************************************************************
void Factorial()
{
    long long n;
    cin >> n;
    number temp;
    temp.num = "1";
    temp.is_operator = 0;
    for (int i = 2; i <= n; i++)
    {
        number temp2;
        temp2.num = to_string(i);
        temp2.is_operator = 0;
        temp = bint_mul(temp, temp2);
    }
    cout << temp.num << "\n";
}

//*****************************************************************
//              Main Function
//*****************************************************************
int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // implementing switch case for taking decision based on choice
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        expression_eval(); // 1000+4564-76846x5465/10000
        break;
    case 2:
        Exponentiation();
        break;
    case 3:
        GCD_Driver();
        break;
    case 4:
        Factorial();
        break;
    default:
        cout<<"choose valid option\n";
    }

    return 0;
}
