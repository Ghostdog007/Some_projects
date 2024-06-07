#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Account{
    //attributes
    private:
    int balance{0};
    string name;
    public:
    //methods
    void set_name(string text){
        name=text;
        cout<<"Name set to "<<text<<endl;
    }
    int show_bal(){
        return balance;
    }
    void set_bal(int bal){
        balance=bal;
    }
    void deposit(int dep){
        balance+=dep;
    }
    string show_name(){
        return name;
    }

    void pay_to(Account &name,int money){
        if(balance>=money){
            balance=balance-money;
            name.balance+=money;
            cout<<" Amount of  "<<money<<" paid to "<<name.show_name()<<endl;
        }
        else
            cout<<"Insufficient funds"<<endl;
    }
};

bool search_name(vector <Account*> vec,string s_name){
    for(auto mow:vec){
        if(mow->show_name()==s_name){
            return true;
        }
    }
    return false;
}

int main(){
    char prompt{};
    vector <Account*> Account_List{};
    Account*temp=nullptr;
    
    do{
        cout<<"C:Creating an account"<<endl
        <<"D:Deposit in a account"<<endl
        <<"B:Check balance"<<endl
        <<"T:transferring money from base account to someplace else"<<endl
        <<"R:Remove Account"<<endl
        <<"E:End"<<endl
        <<"S:See active account"<<endl
        <<"A:Set active account"<<endl;
        cout<<"Enter prompt:";
        cin>>prompt;
        
        if(prompt=='C'){
            string input;
            cout<<"Enter account name:";
            cin.ignore();
            getline(cin,input);
            Account*account_new=NULL;
            account_new=new Account;
            account_new->set_name(input);
            Account_List.push_back(account_new);
            temp=account_new;
        }
        else if(prompt=='S'){
            if(temp!=nullptr)
                cout<<"Active account name:"<<temp->show_name()<<endl;
            else{
                cout<<"No active account"<<endl;
            cout<<"Give account name you want to set as active:"<<endl;
            string s_name;
            cin.ignore();
            getline(cin,s_name);
            if(search_name(Account_List,s_name)){
                for(auto val:Account_List){
                    if (val->show_name()==s_name)
                        temp=val;
                    break;
                }
                cout<<"Active account set to "<<temp->show_name()<<endl;
            }
            else
                cout<<"Account name not found,pls try again."<<endl;
        } }


        else if(prompt=='B'){
            if(temp!=nullptr)
                cout<<"Amount in :  "<<temp->show_name()<<" is "<<temp->show_bal()<<endl;
            else
                cout<<"No active account"<<endl;
        }
        else if(prompt=='T'){
            if(temp!=nullptr){
                cout<<"Enter account name to be transferred to:"<<endl;
                string s_name;
                cin.ignore();
                getline(cin,s_name);
                int amount;
                cout<<"Enter amount to be deposited from active account:"<<endl;
                cin >> amount;

                if(search_name(Account_List,s_name) and temp->show_name()!=s_name){
                    for(auto val:Account_List){
                        if(val->show_name()==s_name){
                            temp->pay_to(*val,amount);
                        }
                    }
                }
                else
                    cout<<"Account not found pls try again."<<endl;
            }
            else
                cout<<"No active account"<<endl;
        }
        else if(prompt=='R'){
            if(temp!=nullptr){
                cout<<"Do you want to remove the active account(Y/N):";
                char confirmation;
                cin >> confirmation;
                if(confirmation=='Y'){
                    for (int i{0};i<Account_List.size();i++){
                        if(Account_List[i]->show_name()==temp->show_name()){
                            Account_List.erase(Account_List.begin()+i);
                            delete temp;
                            temp=nullptr;
                            break;
                        }
                    }
                }
                else{
                    cout<<"Enter Account name to be deleted:"<<endl;
                    string s_name;
                    cin.ignore();
                    getline(cin,s_name);
                    if(search_name(Account_List,s_name)){
                        for(auto val:Account_List){
                            if(val->show_name()==s_name){
                                temp=val;
                                break;
                            }
                        }
                        for (int i{0};i<Account_List.size();i++){
                            if(Account_List[i]->show_name()==temp->show_name()){
                                Account_List.erase(Account_List.begin()+i);
                                delete temp;
                                temp=nullptr;
                                break;
                            }
                        }
                    }
                    else
                        cout<<"Account not found pls try again."<<endl;
                }
            }
            else
                cout<<"No active account"<<endl;
        }
        else if(prompt=='A'){
            if(temp!=nullptr)
                cout<<"Active account is "<<temp->show_name()<<endl;
            else
                cout<<"No active account"<<endl;
            cout<<"Here are the Account names"<<endl;
            for (auto val:Account_List){
                cout<<val->show_name()<<endl;
            }
            bool done{false};
            while(!done){
                cout<<"Enter account name:";
                string s_name;
                cin.ignore();
                getline(cin,s_name);
                if(!search_name(Account_List,s_name)){
                    cout<<"Incorrect name given"<<endl;
                    cout<<"pls try again";
                }else{
                    for(auto val:Account_List){
                        if(val->show_name()==s_name){
                            temp=val;
                            cout<<"Active account set to  "<<temp->show_name()<<endl;
                            break;
                        }
                    }
                    done=true;
                }
            }
        }
        else if(prompt=='D'){
            if(temp!=nullptr){
                cout<<"Deposit Amount : ";
                int amount;
                cin >> amount;
                temp->deposit(amount);
                cout<<"Amount succesfully deposited"<<endl;
            }
            else
                cout<<"No active account"<<endl;
        }

    }while(prompt!='E');
    cout<<"End of application"<<endl;
    
    return 0;
}
