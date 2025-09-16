#include<iostream>
#include<vector>
using namespace std;
int MAX_BOOK_ISSUES=5;
int MAX_LENDING_DAYS=10;
static int current_date=1;
class Credential{
    public:
    string name;
    string password:
    // Credential();
    void setCredential(string name,string pass){
        this->name=name;
        this->password=pass;
    }
    string getName(){
        return this->name;
    }
};
class Book{
    string bookId;
    int quantity;
    string name;
    public:
    Book(int quan,string name){
        this->quantity=quan;
        this->name=name;
        this->bookId=getUniqueId();
    }
    string getBookId(){
        return this->bookId;
    }
    string getUniqueId(){
        static int bid=0;
        bid++;
        string code="book";
        code+=char('0'+bid);
        return code;
    }
    string getName(){
        return this->name;
    }
    int getQuantity(){
        return this->quantity;
    }
    void updateQuantiy(int val){
        this->quantity=val;
    }
};
class CheckoutBook{
    string checkoutBookId;
    string bookId;
    int checkout;
    public:
    CheckoutBook(string bookid ,int date){
        this->bookId=bookid;
        this->checkout=date;
        this->checkoutBookId=getUniqueId();
    }
    string getUniqueId(){
        static int cbid=0;
        cbid++;
        string code="checkoutbook";
        code+=char('0'+cbid);
        return code;
    }
    string getbookID(){
        return this->bookId;
    }
    int getCheckout(){
        return this->checkout;
    }
};
class User:public Credential{
    string userId;
    vector<CheckoutBook> userbooks;
    public:
    int getTotalBooks(){
        return userbooks.size();
    }
    vector<CheckoutBook> getCheckoutBook(){
        return this->userbooks;
    }
    string getUniqueId(){
        static int uid=0;
        uid++;
        string code="user";
        code+=char('0'+uid);
        return code;
    }
    void assignBook(CheckoutBook checkbook){
        userbooks.push_back(checkbook);
        return ;
    }
    void removeBooks(){
        int n=userbooks.size();
        while(n--){
            userbooks.pop_back();
        }
        return ;
    }
    void userCredential(){
        cout<<"User Name: "<<cre.getName()<<"\n";
    }
    void bookList(){
        for(int i=0;i<userbooks.size();i++){
            cout<<i+1<<". Book id:"<<userbooks[i].getbookID()<<" and Checkout Date"<<userbooks[i].getCheckout()<<"\n";
        }
    }
};
class Librarian{
    int fine;
    vector<Book> books;
    public:
    Librarian(vector<Book> books,int fine){
        this->books=books;
        this->fine=fine;
    }
    void bookList(){
        for(int i=0;i<books.size();i++){
            cout<<i+1<<". id: "<<books[i].getBookId()<<", Name: "<<books[i].getName()<<", Quantity: "<<books[i].getQuantity()<<"\n";
        }
    }
    void addBook(Book book){
        books.push_back(book);
    }
    void issueRequest(User &user,Book &book,int date){
        for(int i=0;i<books.size();i++){
            if(book.getBookId()==books[i].getBookId()){
                if(books[i].getQuantity()==0){
                    cout<<book.getName()<<" is not available now! You came later"<<"\n";
                    return ;
                }
                break;
            }
        }
        if(user.getTotalBooks()==MAX_BOOK_ISSUES){
            cout<<" You can't issue more book! Please checkout a book then come again"<<"\n";
            return ;
        }
        if((date-current_date)>MAX_LENDING_DAYS){
            cout<<"You cannot lend book for more than 10 days"<<"\n";
            return ;
        }
        for(int i=0;i<books.size();i++){
            if(book.getBookId()==books[i].getBookId()){
                int totalbookcnt=books[i].getQuantity();
                books[i].updateQuantiy(totalbookcnt-1);
                break;
            }
        }
        CheckoutBook check(book.getBookId(),date);
        user.assignBook(check);
        cout<<"Issue request accepted"<<"\n";
        return;
    }
    void removeBook(Book book){
        books.push_back(book);
    }
    int updateSheffandcalculateFine(vector<CheckoutBook> checkoutbook){
        int cost=0;

        for(int i=0;i<checkoutbook.size();i++){
            for(int j=0;j<books.size();j++){
                if(checkoutbook[i].getbookID()==books[i].getBookId()){
                    int totalBook=books[i].getQuantity();
                    books[i].updateQuantiy(totalBook+1);
                    break;
                }
            }
            if(checkoutbook[i].getCheckout()>current_date){
                cost+=fine*(checkoutbook[i].getCheckout()>current_date);
            }
        }
        return cost;
    }
    void returnBook(User &user){
        int totalcost=updateSheffandcalculateFine(user.getCheckoutBook());
        cout<<"You have to pay fine of INR: "<<totalcost<<"\n";
        user.removeBooks();
        cout<<"Books are returned"<<"\n";
        return ;
    }
};
int main(){
    // Book b1(2,"AfterDark");
    // Book b2(3,"Book Theft");
    // Book b3(1,"Ugly Love");
    // Book b4(5,"Alchemist");
    // Book b5(1,"A Good Girl");
    // Book b6(1,"Deep Work");
    // vector<Book> books={b1,b2,b3,b4};
    // Credential c1("Rahul");
    User u1;
    u1.setCredential("Tahul","paswrod");
    u1.getName();
    // User u2("Raj");
    // User u3("Arjun");
    // Librarian l1(books,24);
    // l1.bookList();
    // l1.issueRequest(u1,b1,3);
    // // l1.bookList();
    // u1.bookList();
    // l1.issueRequest(u1,b2,4);
    // l1.issueRequest(u1,b3,6);
    // l1.issueRequest(u1,b4,7);
    // // l1.issueRequest(u1,b5,9);
    // // l1.issueRequest(u1,b6,7);
    // l1.issueRequest(u1,b3,7);
    // l1.bookList();
    return 0;
}