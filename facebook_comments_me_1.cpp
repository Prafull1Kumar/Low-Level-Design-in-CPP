
#include <iostream>
#include <vector>
#include <unordered_map>
// #include<bits/stdc++.h>
using namespace std;
class User{
    private:
    int id;
    string name;
    int getUniqueId();
    public:
    User(string);
    int gettId();
    string getName();
};
class Comment{
    private:
    int id;
    string comment;
    User user;
    vector<Comment> replies;
    int getUniqueId();
    public:
    Comment(string,User);
    int getId();
    void setComment(string);
    string getComment();
    void pushreply(Comment);
    void getReplies();
};
class Post{
    private:
    int id;
    User user;
    unordered_map<int,Comment> comments;
    int getUniqueId();
    public:
    Post(User);
    int getId();
    void postComment(Comment);
    void showComments();
    void replyOnComment(int,Comment);
    void deleteComment(int);
};
int User::getUniqueId(){
    static int userid=0;
    userid++;
    return userid;
}
User::User(string name){
    this->name=name;
    this->id=User::getUniqueId();
}
int User::gettId(){
    return this->id;
}
string User::getName(){
    return this->name;
}
Comment::Comment(string text,User user):user(user){
    this->comment=text;
    // this->user=user;
    this->id=Comment::getUniqueId();
}
int Comment::getUniqueId(){
    static int commentId=0;
    commentId++;
    return commentId;
}

int Comment::getId(){
    return this->id;
}
void Comment::setComment(string com){
    this->comment=com;
}
void Comment::pushreply(Comment com){
    replies.push_back(com);
}
string Comment::getComment(){
    return this->comment;
}
void Comment::getReplies(){
    if(replies.size()>0){
        cout<<"       Replies:-"<<"\n";
        for(int i=0;i<replies.size();i++){
            cout<<"          "<<i+1<<". "<<replies[i].getComment()<<" : "<<replies[i].getId()<<"\n";
        }
    }
}

int Post::getUniqueId(){
    static int postId=0;
    postId++;
    return postId;
}
Post::Post(User user):user(user){
    this->id=Post::getUniqueId();
}
int Post::getId(){
    return this->id;
}
void Post::postComment(Comment text){
    if(comments.find(text.getId())==comments.end()){
        comments.insert(make_pair(text.getId(),text));
    }
}
void Post::showComments(){
    int i=1;
    for(auto it=comments.begin();it!=comments.end();it++){
        cout<<i<<". "<<it->second.getComment()<<" "<<it->second.getId()<<"\n";
        it->second.getReplies();
        cout<<"\n";
        i++;
    }
}
void Post::replyOnComment(int commentId,Comment text){
    comments.find(commentId)->second.pushreply(text);
    // it->second.pushreply();
}
void Post::deleteComment(int id){
    comments.erase(comments.find(id));
}
int main(){
    cout<<"Hello world"<<"\n";
    User u1("Raj");
    User u2("Rishi");
    User u3("Ravi");
    Comment c1("I am Raj",u1);
    Comment c2("I am Rashi",u2);
    Comment c3("I am ravi",u3);
    Post p1(u1);
    p1.postComment(c2);
    p1.postComment(c3);
    p1.showComments();
    Comment c4("hello ravi",u1);
    Comment c5("hello rishi",u1);
    p1.replyOnComment(2,c5);
    p1.replyOnComment(3,c4);
    Comment c6("good what aboout you raj",u2);
    Comment c7("better than before",u1);
    p1.replyOnComment(2,c6);
    p1.replyOnComment(2,c7);
    p1.showComments();
    p1.deleteComment(3);
    p1.showComments();
    return 0;
}