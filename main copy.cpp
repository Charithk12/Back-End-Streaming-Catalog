//
//  main.cpp2//  Project 1
//
//  Created by Charith Kondapally on 4/18/22.
//

#include <iostream>
using namespace std;
/* For this project, I will be using 3 classes. one to check if date is valid or invalid, moveie node which is going to be a circular linked list which will then be linked to the double linked list and lastly the category list which is a double linked list which will be pointing to the movies. Category class and the movie class will have their own nodes becasue they are part of different lists which will just be pointing in the end
 */
class Date{ // This class is for entering date, checking if date is valid and printing it
public:
    int month;
    int day;
    int year;
    bool valid = false;
    
    //default constructor to access date from other classes.
    Date(){}
    //constructor to check if date is valid
    Date(int mont, int dt, int yr){
        //checking if date is valid for months wirh 31 days
        if((mont == 1 || mont == 3 || mont == 5 || mont == 7 || mont == 8 || mont == 10 || mont == 12) && (dt > 0 && dt <= 31)){
            month = mont;
            day = dt;
            year = yr;
            valid = true;
        }
        //February only has 28 days with 29 days during leap year.
        if(mont == 2 && dt >= 1 && dt < 30){
            if(dt == 29 && yr % 4 == 0){
                month = mont;
                day = dt;
                year = yr;
                valid = true;
            }
            else{
                cout << "invalid date for the movie" << endl;
                return;
                
            }
        }
        //checking if the date is valid for months with 30 days.
        if((mont == 3 || mont == 6 || mont == 9 || mont == 11) && dt >= 1 && dt <= 30){ //checking if the date is valid for March
            month = mont;
            day = dt;
            year = yr;
            valid = true;
        }
        
    }
    // This function checks if data is valid for the delete movie before date function.
    bool validDate(Date dt){
        if(year < dt.year){
            return true;
        }
        if(year == dt.year){
            if(month < dt.month){
                return true;
            }
            if(month == dt.month){
                if(day < dt.day){
                    return true;
                }
            }
            else{
                
             return false;
            }
        }
        return false;
    }
    
    void printDate(){
        if(valid == true){
            cout << month << "," << day << "," << year;
        }
        else{
            cout << "Invalid date for the movies" << endl;
        }
    }
    
};
struct Node{ // This is for circular linked lists which is for the movie class
    string data; //string to store the name of the movie
    Node* next; //points to the next movie in the movie list
    Node* prev; //pointer to the previous movie in the movie list
    bool headd = false; //used to check if head exists and it is used in print functions and just to update head
    Date dt; // used to check if date is valid for the movie that is entered
    Node(){} //default constructor to access Node structure from any class
    Node(string info, Date date){ //constructor to check the date for the movie.
        dt = date;
        if(dt.valid == false){
            cout << "The date is not valid, movie cannot be added" << endl;
            return;
        }
        else{
        data = info;
        next = NULL;
        prev = NULL;
        headd = false;
    }
    }
};
class CircularLL{ // this class is for the movies as the list is circular
public:
    Node* head; // first node of the list
    Node* tail; // last node of the list
    int counter; // used to find the index but has a counter to keep track of the number of movies in the movie list.
    
    CircularLL(){ // default constructor to help access code from other classes and lists
        head = NULL;
        tail = NULL;
        counter = 0;
    }
    //this function returns head of the list
   
    
    void addMovieNode(string info, Date dt){ // adds new movie to the movie list with name and date
        Node* temp = new Node(info, dt);
        if(head == NULL){ // checks if the list is empty
            temp->headd = true;
            head = temp;
            tail = temp;
            tail->next = head;
            head->prev = tail;
            counter += 1;
        }
        else{
            //Searches if movie is in the list.
            Node* curr = tail->next;
            if(temp->data == head->data){
                cout << temp->data << " is in list" << endl;
                return;
            }
            while(curr != tail->next){
                if(temp->data == curr->data){
                    //if the current name is equal to the one we are searching for, return current.
                    cout << temp->data << " is in the list" << endl;
                    return;
                }
                curr = curr -> next;
            }
            if(temp->data < head->data){
                temp->next = head;
                head->prev = temp;
                head = temp;
                head->prev = tail;
                tail->next = head;
                head->headd = false;
                temp->headd = true;
                counter += 1;
            }
            
            //inserting elsewhere in the list
            else{
                Node* cur = head;
                while(cur->next != head && cur->next->data < temp->data){
                    cur = cur->next;
                }
                temp->next = cur->next;
                cur->next = temp;
                temp->next->prev = temp;
                temp->prev = cur;

                if(temp->next == head){
                    tail = temp;
                    tail->next = head;
                }
                counter += 1;
            }
        }
    }
    
    //removes movie from the list.
    void deleteMovie(string info){
        if(head == NULL){
            cout << "Nothing in list" << endl;
            return;
        }
        // checking if the first node it to be deleted
        if(tail->next->data == info){
            head->next->prev = tail;
            head->next->headd = true;
            tail->next = head->next;
            head = head->next;
            counter -= 1;
            return;
        }
        Node* curr = tail->next->next;
        while(curr->next != head){
            if(curr->data == info){
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                counter -=1;
                return;
            }
            curr = curr -> next;
        }
        
        if(tail->prev->next->data == info){
            tail->prev->next = head;
            head->prev = tail->prev;
            tail = tail->prev;
            counter -= 1;
            return;
        }
        
    }
    Node* heads(){
        return head;
    }
    //number of nodes in list
    int counterr(){
        return counter;
    }
    
    
    
    //prints all the movies.
    void moviePrint(Node* print){
        if(head == NULL){ // checking if list is empty
            cout << "List is empty" << endl;
            return;
        }
        else{
            cout << print->data << ", "; // printing movies through recursion
            if(print->next->headd == true){
                cout << endl;
                return;
            }
            moviePrint(print->next);
        }
    }
};
struct Node1{
    string data; //used to insert the name of the category
    Node1* prev; //points to the previous node in the category list
    Node1* next; //points to the next node of the category list
    CircularLL* movies; // this pointer is used to access the movie list and link it to the category list.
    Node1(){}//default constructor
    
    Node1(string info){ //constructor with the name of the category
        data = info;
        prev = NULL;
        next = NULL;
        movies = NULL;
    }
};
class DoubleLL{ // using this class for the category
public:
    Node1* head; // points to the first node in the category list
    Node1* tail; // points to the last node in the category list
    int counter; // used to keep track of the number of categories created.

    DoubleLL(){ // default constructor
        head = NULL;
        tail = NULL;
        counter = 0;
    }
    
    // returns the firts node of the category list
    Node1* hhead(){
        return head;
    }
    //returns the number of categories in list
    int getnumcats(){
        return counter;
    }
    
    //adding new category to the list
    void addCategory(string info){
        Node1* temp = new Node1(info);
        if(head == NULL){// checks if the first node is empty of not
            head = temp;
            tail = temp;
        }
        else{ // tail poiner next is the new node inserted while head remains the same
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
        counter += 1; // update counter when inserting
    }
    
    //Removing category from the list.
    void deleteCategory(string info){
        if(head == NULL){//if the movie list is empty
            cout << "Category list is empty" << endl;
            return;
        }
        if(head->data == info){ // checking the first node
            head = head->next;
            counter -= 1;
            return;
        }
        
        Node1* curr = head -> next; // deleting the node elsewhere in the list
        while(curr -> next != NULL){
            if(curr->data == info){
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                counter -=1;
                return;
            }
            curr = curr -> next;
        }
        if(tail->data == info){ // deleting the node from the last node of the list
            tail = tail->prev;
            tail->next = NULL;
            counter -= 1;
            return;
        }
        
    }

    // searches the entire category to find the simple category. linear search
    Node1* searchCategory(string info){
        Node1* curr = head;
        while(curr != NULL){
            if(curr->data == info){
                //if the current name is equal to the one we are searching for, return current.
                //cout << cur->name << " has been found" << endl;
                return curr;
            }
            curr = curr -> next;
        }
        //if not found, return null
        cout << "Category not in list" << endl;
        return NULL;
    }
    
    // Adding movie in the given category
    void addMovieCategory(string info, string cat, Date dt){
        Node1* temp = searchCategory(cat); // checks if category exists before inserting the mivie in the list
        if(temp == NULL){
            cout << "No such Category" << endl;
            return;
        }
        if(temp->movies == NULL){ // making new node pointer if there are no movies
            temp->movies = new CircularLL();
        }
        
        temp->movies->addMovieNode(info, dt); // inserting new movie with the date
    }
    
    void categoryMoviesPrint(Node1* info){ // print all movies within the category
        if(info == NULL){
            return;
        }
        cout << info->data << ": ";
        info->movies->moviePrint(info->movies->heads());
    }
    
    //using Bunary search to find the movie within the category
    int binarySearch(Node1* category, string info, int low, int high){
        if(category->movies == NULL){ // checking if any movies exist in the category
            cout << "No such category" << endl;
            return false;
        }
        int midd;
        Node* middle = category->movies->heads();
        bool valid = false;
        if(low > high){ // checking the placement
            valid = false;
        }
        else {
            midd = (low + high) / 2;
            for(int i = 0; i < midd; i++){
                middle = middle->next;
            }
            if(middle->data == info ){
                valid = true;
            }
            else{
                if(middle->data < info){
                    valid = binarySearch(category, info, midd + 1, high);
                }
                else{
                    valid = binarySearch(category, info, low, midd - 1);
                }
            }
        }
        return valid;
    }
    
    // index function
    int index(Node1* category, string info){
        if(category->movies == NULL){ // checks if there are any movies in the given category
            cout << "Category has no movies" << endl;
            return NULL;
        }
        Node* cur = category->movies->heads();
        for(int i = 0; i < category->movies->counterr(); i++){ // returns the index
            if(cur->data == info){
                cout << "Index of " << info << ": " << i << endl;
                return i;
            }
            cur = cur->next;
        }
        cout << "No movie in category"<< endl;
        return NULL;
    }
    
    // used to search for the given movie
    bool movieSearch(string info){
        Node1* curcat = head;
        while(curcat != NULL){
            if(binarySearch(curcat, info, 0, curcat->movies->counterr())){ // using binary serch to find from all the categories
                cout << info << " Movie exists in category: " << curcat->data << endl;
                return true;
            }
            curcat = curcat->next;
        }
        // else return false
        cout << info << " movie not in any list" << endl;
        return false;
    }
    
    //prints every movie
    void printMovies(){
        Node1* cat = head;
        while(cat != NULL){
            categoryMoviesPrint(cat);
            cat = cat->next;
        }
    }
    
    // removes movie from the list if before the date
    void deleteMovieDate(Date dt){
        Node1* curr; // checking both the category and the movies
        Node* cur;
        curr = head;
        while(curr != NULL){
            if(curr->movies->heads()->dt.validDate(dt)){
                cout << curr->movies->heads()->data << " has been deleted" << endl;
                curr->movies->deleteMovie(curr->movies->heads()->data);
            }
            for(cur = curr->movies->heads()->next; !cur->headd; cur = cur->next){
                if(cur->dt.validDate(dt)){
                    cout << cur->data << " has been deleted" << endl;
                    curr->movies->deleteMovie(cur->data);
                }
            }
            curr = curr -> next;
        }
    }
    
};




int main() {
    //make a catalog with the name Netflix
    DoubleLL MyIndianTv;

    // making 4 new categories
    MyIndianTv.addCategory("children");
    MyIndianTv.addCategory("action");
    MyIndianTv.addCategory("crime");
    MyIndianTv.addCategory("bollywood");

    
    // adding movies to children category
    MyIndianTv.addMovieCategory("Batman", "children", Date(10,23,2001));
    MyIndianTv.addMovieCategory("Lion King", "children", Date(6,24,1994));
    MyIndianTv.addMovieCategory("Paddington 2", "children", Date(11,14,2001));
    MyIndianTv.addMovieCategory("Transformers", "children", Date(11,27,2013));
    MyIndianTv.addMovieCategory("Spider man", "children", Date(7,28,1996));
    
    // adding movies to action category
    MyIndianTv.addMovieCategory("Black Panther", "action", Date(7,9,2009));
    MyIndianTv.addMovieCategory("Die hard", "action", Date(5,13,2009));
    MyIndianTv.addMovieCategory("Fast and Furious", "action", Date(1,30,2009));
    MyIndianTv.addMovieCategory("Mission Impossible", "action", Date(11,21,2009));
    MyIndianTv.addMovieCategory("Hunger Games", "action", Date(5,25,2009));
    
    //creating movie list for crime category
    MyIndianTv.addMovieCategory("Crime investigation department", "crime", Date(6,25,2010));
    MyIndianTv.addMovieCategory("Pink", "crime", Date(7,30,2004));
    MyIndianTv.addMovieCategory("No time to die", "crime", Date(9,27,2002));
    MyIndianTv.addMovieCategory("Joker", "crime", Date(12,13,1996));
    
    
    //creating movie list for bollywood category
    MyIndianTv.addMovieCategory("Dilwale dulhania le jayenge", "bollywood", Date(9,5,2017));
    MyIndianTv.addMovieCategory("Kabhi khushi kabi gham", "bollywood", Date(7,19,2013));
    MyIndianTv.addMovieCategory("Kuch kuch hota hai", "bollywood", Date(12,20,1996));
    MyIndianTv.addMovieCategory("Sholay", "bollywood", Date(6,24,2016));
    
    //printing all movies in a categoy
    cout << "------- Printing movies from category -------" << endl;

    MyIndianTv.categoryMoviesPrint(MyIndianTv.searchCategory("bollywood"));
    cout <<"" <<endl;
    
    //printing all the movies within the movie list
    cout << "------- Printing every movie from MyIndianTv -------" << endl;
    MyIndianTv.printMovies();
    cout <<"" <<endl;
    
    // searching if category exists.
    cout << "------- Searching if categpory exists -------" << endl;
    cout << "The " << MyIndianTv.searchCategory("crime")->data << " category exists " << endl;
    MyIndianTv.searchCategory("horror") -> data;
    MyIndianTv.searchCategory("drama") -> data;
    cout <<"" <<endl;
    
    
    
        
    //showing that you cannot add a movie with an invalid date, or a movie that it already in the list.
    cout << "------- Testing alternate conditions -------" << endl;
    MyIndianTv.addMovieCategory("Black Panther", "action", Date(2,29,2003));
    MyIndianTv.addMovieCategory("Star Wars", "king", Date(5,25,1977));
    cout <<"" <<endl;
    
    
    // using binary search to find movies within the category
    cout << "------- Binary Search Category -------" << endl;
    cout << (MyIndianTv.binarySearch(MyIndianTv.searchCategory("children"), "Transformers", 0, MyIndianTv.searchCategory("children")->movies->counterr()) ? "Transformers exists" : "Transformers dosent exist") << endl;
    
    cout << (MyIndianTv.binarySearch(MyIndianTv.searchCategory("bollywood"), "Kabhi khushi kabi gham", 0, MyIndianTv.searchCategory("bollywood")->movies->counterr()) ? "Kabhi khushi kabi gham exists" : "Kabhi khushi kabi gham dosent exist") << endl;
    
    cout << (MyIndianTv.binarySearch(MyIndianTv.searchCategory("crime"), "dhoom", 0, MyIndianTv.searchCategory("crime")->movies->counterr()) ? "Pink exists" : "Pink dosent exist") << endl;
    cout <<"" <<endl;
    
    //Index
    cout << "------- Index for the movies within the list -------" << endl;
    MyIndianTv.index(MyIndianTv.searchCategory("action"), "Fast and Furious");
    MyIndianTv.index(MyIndianTv.searchCategory("bollywood"), "Kuch kuch hota hai");
    cout <<"" <<endl;
    
    // searching for movie by going through all the categories.
    cout << "------- Movie search -------" << endl;
    MyIndianTv.movieSearch("No time to die");
    MyIndianTv.movieSearch("Kingsman");
    cout <<"" <<endl;
    
    //removing a category and all the movies in it
    cout << "------- Delete category -------" << endl;
    MyIndianTv.deleteCategory("action");
    cout << "after deleting action category: " << endl;
    MyIndianTv.printMovies();
    cout <<"" <<endl;
    
    //removing all movies before a date
    cout << "------- Deleting movie by a date -------" << endl;
    MyIndianTv.deleteMovieDate(Date(5,3,2002));
    //will delete Lion King, Matilda, Jerry Maguire, The Titanic, Scream
    cout << endl << "After deleting the movies " << endl;
    MyIndianTv.printMovies();
    cout <<"" <<endl;
    
    
    return 0;
}



