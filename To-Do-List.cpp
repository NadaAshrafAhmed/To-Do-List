#include <iostream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <strstream>

using namespace std;

struct date{

    int year ;
    int month ;
    int day ;
    friend bool operator== ( date & d1 , date & d2 ) ;
    friend bool operator< ( date & d1 , date & d2 ) ;
    friend istream& operator>>(istream& in , date& d1) ;
};

bool operator== ( date & d1 , date & d2 ){

    if( d1.year==d2.year && d1.month==d2.month && d1.day==d2.day ){
        return true ;
    }
    else{
        return false ;
    }
}

bool operator< ( date & d1 , date & d2 ){

    if( d1.year<d2.year ){
        return true ;
    }
    else if( d1.year==d2.year && d1.month<d2.month ){
        return true ;
    }
    else if( d1.year==d2.year && d1.month==d2.month && d1.day<d2.day ){
        return true ;
    }
    else{
        return false ;
    }
}

istream& operator>>(istream& in , date& d1){

       cout<<"Enter day: ";   in>>d1.day;
       cout<<"Enter month: ";  in>>d1.month;
       cout<<"Enter year: ";  in>>d1.year;
       return in;
    }

struct data{

    string name;
    string description;
    int priority;
    date time ;
    int days;

    friend bool operator== ( data & d1 , data & d2 ) ;
    friend istream& operator>>(istream& in , data& d1) ;

};

bool operator== ( data & d1 , data & d2 ){

    if( d1.name==d2.name && d1.description==d2.description && d1.priority==d2.priority && d1.time==d2.time && d1.days==d2.days ){

        return true ;
    }
    else{

        return false ;
    }
}

istream& operator>>(istream& in , data& d1){
        cin.ignore() ;
       cout<<"Enter name: ";   getline(in,d1.name);
       cout<<"Enter Description: ";  getline(in,d1.description) ;
       cout<<"Enter Priority: ";  in>>d1.priority;
       cout<<"Enter Due Date: " << endl ;  in>>d1.time;
       cout<<"#Days It Takes: ";  in>>d1.days;

       return in;
    }

template <class T>
class task {
private:

    T d ;

    task<T>* next;

public:
    task(){

        d.name=d.description="" ;
        d.time.year=d.time.month=d.time.day=d.priority=d.days=0;
        next=NULL;
    }

    task( T t, task<T>* nextptr = NULL ){
        d=t;
        next=nextptr;
    }

    string getname(){ return d.name ; }
    string getdesc(){ return d.description ; }
    int getp(){ return d.priority ; }
    int getyear(){ return d.time.year ;}
    int getmonth(){ return d.time.month ; }
    int getday(){ return d.time.day ; }
    date getdate(){ return d.time ; }
    int getdays () {return d.days;}
    T getd(){ return d ; }
    void setd( T a ){ d = a ; }

    void setNext(task* ptr){ next = ptr ; }
    task* getNext(){ return next ; }

    friend ostream& operator<< (ostream& out, task<T> *t){

        out << "Name: " << t->getname() << endl ;
        out << "Description: " << t->getdesc() << endl ;
        out << "Priority: " << t->getp() << endl ;
        out << "Due Date: " << t->getday() << "-" << t->getmonth() << "-" << t->getyear() << endl ;
        out << "#Days It Takes: " << t->getdays() << endl ;

        return out;
    }

    task operator= (task<T> t){

        d=t.d;
        next=t.next;
        return t;
    }
    ~task () { }
};

template <class T>
class List{

private:
    task<T>* head;
    task<T>* tail;

public:
    List(){
        head = NULL ;
        tail = NULL ;
    }

    task<T>* get_head(){ return head ; }

    void AddToHead ( T t )
    {
        task<T>* ptr = new task<T>( t , head );
        head=ptr;
        if (tail==NULL)
        {
           tail = ptr;
        }
    }

    void AddtoTail ( T t )
    {
        task<T>* ptr = new task<T>( t,NULL );
        if (head== NULL) //empty list
        {
            head=tail=ptr;
        }
        else
        {
            tail->setNext(ptr);
            tail = ptr;
        }
    }

    void Insert (T t)
    {
         task<T>* ptr = new task<T>( t,NULL );
         task<T>* headptr = head;
         task<T>* prev=head;
         while (headptr!=NULL)
         {
             if (headptr->getp()>=ptr->getp())
             {
                 break;
             }
             prev=headptr;
             headptr=headptr->getNext();
         }
         if(headptr==prev&&prev==NULL)
		 {
			 head=ptr;
			 tail=ptr;
		 }
         else if(headptr==prev&&prev==head)
         {
             AddToHead(t);
         }
         else if(headptr==prev&&prev==NULL)
         {
             AddtoTail(t);
         }
         else
         {
            ptr->setNext(headptr);
            prev->setNext(ptr);
         }
    }

    friend ostream& operator<<(ostream& out, List<T> l){

        task<T>* headptr = l.head;

        while( headptr!=NULL ){

           out<<headptr;
           headptr=headptr->getNext() ;
        }

        return out;
    }

    T removeHead(){

        if( head==NULL ){

            T info ;
            cout << "The List is empty!!!" << endl ;
            return info ;
        }

        T info = head->getd() ;
        task<T>* ptr = head ;
        head = head->getNext() ;
        delete ptr ;

        return info ;
    }

    T removeTail() {

        if( tail==NULL ){

            T info ;
            cout << "The List is empty!!!" << endl ;
            return info ;
        }
        else if( tail==head ){

            tail = NULL ;

            return removeHead() ;
        }

        T info = tail->getd() ;

        task<T>* ptr = tail ;
        task<T>* temp = head ;

        while( temp->getNext()!=tail ){

            temp = temp->getNext() ;
        }

        task<T>* n = NULL ;
        temp->setNext(n) ;
        tail = temp ;
        delete ptr ;

        return info ;
    }

    int sizee(){

        task<T>* h = head ;
        task<T>* t = tail ;
        int c = 0 ;

        while( h!=t ){

            h = h->getNext() ;
            c ++ ;
        }
        c++ ;

        return c ;
    }

    T removeFromIndex( int i ){

        if ( i>=sizee() ){
            T info ;
            cout << "This index is not included in the List!!!" << endl ;
            return info ;
        }
        else if( i==0 ){

            return removeHead() ;
        }
        else if( i==sizee()-1 ){

            return removeTail() ;

        }
        else{

            int c = 0 ;
            task<T>* ptr = head ;
            task<T>* pptr = head ;

            while( c<i-1 ){
                pptr = pptr->getNext() ;
                c ++ ;
            }

            ptr = pptr->getNext() ;
            pptr->setNext( ptr->getNext() ) ;

            T info = ptr->getd() ;

            delete ptr ;
            return info ;
        }
    }

    bool searchh( T item ){

        task<T>* ptr = head ;
        task<T>* temp = NULL ;

        while( ptr!=temp ){

            T info = ptr->getd() ;

            if( info==item ){

                return true ;
            }
            else{

                ptr = ptr->getNext() ;
            }
        }

        return false ;
    }

    T removeItem( T item ){

        if( !searchh(item) ){

            T info ;
            cout << "The Task is not found!!" << endl ;
            return info ;
        }
        else{

            task<T>* ptr = head ;

            while( true ){

                T info = ptr->getd() ;

                if( info==item ){
                    break ;
                }
                else{

                    ptr = ptr->getNext() ;
                }
            }

            if( ptr==head ){

                return removeHead() ;
            }
            else if( ptr==tail ){

                    return removeTail() ;
            }
            else{

                T info = ptr->getd() ;

                task<T>* pptr = head ;

                while( pptr->getNext()!=ptr ){

                    pptr = pptr->getNext() ;
                }

                pptr->setNext( ptr->getNext() ) ;

                delete ptr ;

                return info ;
            }
        }
    }

    date curr_time(){

        date curr ;

        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        curr.year = (now->tm_year + 1900) ;
        curr.month = (now->tm_mon + 1) ;
        curr.day = now->tm_mday ;

        return curr ;
    }

    bool isPassed( task<T> t ){

        date d1 = t.getdate() , d2 = curr_time() ;

        return d1 < d2 ;
    }

    void removeWithPredicate( bool(List<T>::*p)(task<T> t) ){

       task<T>* ptr = head ;
       T info , temp ;

       while( ptr!=NULL ){

            if( (this->*p)( *ptr ) ){

                if( ptr==head ){

                    temp = removeHead() ;
                    ptr = head ;
                }
                else if( ptr==tail ){

                    temp = removeTail() ;
                    break ;
                }
                else{

                    info = ptr->getd() ;
                    temp = removeItem( info ) ;
                    ptr = ptr->getNext() ;
                }
            }
            else{
                ptr = ptr->getNext() ;
            }

       }


    }

    void mergeSort_ (task<T>** a,bool (List<T>::*comp)(task<T> task1, task<T> task2), int order)
	{
		task<T>* head_=*a;
		task<T>* s=NULL;//start
		task<T>* m=NULL;//mid
		task<T>* one;//one step
		task<T>* two;//two steps
		if(head_==NULL||head_->getNext()==NULL)//base case
		{
			s=head_;
			m=NULL;
			return;
		}
		else
		{
			one=head_;
			two=head_->getNext();
			while (two!=NULL)
			{
				two=two->getNext();
				if(two!=NULL)
				{
					one=one->getNext();
					two=two->getNext();
				}
			}
		}
		s=head_;
		m=one->getNext();
		one->setNext(NULL);
		mergeSort_(&s,comp,order);
		mergeSort_(&m,comp,order);
		task<T>*t;//temp
		task<T>*p;//privious
		if(order==1)
		{
			if(!((this->*comp)(*s,*m)))
			{
				t=s;
				s=m;
				m=t;
			}
			t=s;
			while(m!=NULL)
			{
				if((this->*comp)(*t,*m))
				{
					p=t;
					t=t->getNext();
				}
				else
				{
					task<T>*k;
					k=m;
					m=m->getNext();
					k->setNext(t);
					p->setNext(k);
					p=k;
				}
				if(t==NULL)
				{
					p->setNext(m);
					break;
				}
			}
			//delete *a ;
			*a=s;
		}
		else if(order==2)
		{
			if(!((this->*comp)(*m,*s)))
			{
				t=s;
				s=m;
				m=t;
			}
			t=s;
			while(m!=NULL)
			{
				if((this->*comp)(*m,*t))
				{
					p=t;
					t=t->getNext();
				}
				else
				{
					task<T>*k;
					k=m;
					m=m->getNext();
					k->setNext(t);
					p->setNext(k);
					p=k;
				}
				if(t==NULL)
				{
					p->setNext(m);
					break;
				}
			}
			//delete *a ;
			*a=s;
		}

	}

	bool orderByDuration (task<T> task1, task<T> task2)
	{
		return (task1.getdays() <= task2.getdays());
	}
	bool orderByPriority (task<T> task1, task<T> task2)
	{
		return (task1.getp() <= task2.getp());
	}
	bool orderByName (task<T> task1, task<T> task2)
	{
		return (task1.getname() <= task2.getname());
	}
	bool orderByDate  (task<T> task1, task<T> task2)
	{
		bool k=false;
		date d1=task1.getdate(),d2=task2.getdate();
		if(d1.year<d1.year)
		{
			k=true;
		}
		if(d1.year==d2.year&&d1.month<d2.month)
		{
			k=true;
		}
		if(d1.year==d2.year&&d1.month==d2.month&&d1.day<=d2.day)
		{
			k=true;
		}

		return k;
	}
	void mergeSort (bool (List<T>::*comp)(task<T> task1, task<T> task2), int order)
	{
		mergeSort_( &head,comp ,order);
		task<T>* p=head;
		while(p!=NULL)
		{
			tail=p;
			p=p->getNext();
		}
	}
	List<T> Merge (List<T> anotherList)
	{
		List<T> m;
		task<T>*p=head;
		while(p!=NULL)
		{
			m.Insert(p->getd());
			p=p->getNext();
		}
		p=anotherList.head;
		while(p!=NULL)
		{
			m.Insert(p->getd());
			p=p->getNext();
		}
		return m;
	}

    ~List(){

        if( head!=NULL ){
            delete head ;
        }

        if( tail!=NULL ){
            delete tail ;
        }
    }
};

void load ( fstream& f , List<data> &l ){

    f.seekg(0,ios::end);
    short length;
    length = f.tellg();
    f.seekg(0,ios::beg);

    char* buffer = new char[length];

    f.read(buffer,length);

    istrstream strbuf(buffer) ;

    data t ;

    int c = 0 ;

    for(int i=0;i<3;i++){

        char a[100] ;
        strbuf.getline( a , 100  ) ;
        t.name = a ;
        strbuf.getline( a , 100 ) ;
        t.description = a ;
        char temp[10];
        strbuf.getline( temp ,10 ) ;
        t.priority=0;
        for (int i=0;i<10;i++)
        {
            if(temp[i]=='\0')
            {
                break;
            }
            t.priority*=10;
            t.priority+=(temp[i]-'0');
        }

        strbuf.getline( temp ,10 , ' ' ) ;
        t.time.day=0;
        for (int i=0;i<10;i++)
        {
            if(temp[i]=='\0')
            {
                break;
            }
            t.time.day*=10;
            t.time.day+=(temp[i]-'0');
        }

        strbuf.getline( temp ,10, ' ' ) ;
        t.time.month=0;
        for (int i=0;i<10;i++)
        {
            if(temp[i]=='\0')
            {
                break;
            }
            t.time.month*=10;
            t.time.month+=(temp[i]-'0');
        }

        strbuf.getline( temp ,10 ) ;
        t.time.year=0;
        for (int i=0;i<10;i++)
        {
            if(temp[i]=='\0')
            {
                break;
            }
            t.time.year*=10;
            t.time.year+=(temp[i]-'0');
        }

        strbuf.getline( temp ,10 ) ;
        t.days=0;
        for (int i=0;i<10;i++)
        {
            if(temp[i]=='\0')
            {
                break;
            }
            t.days*=10;
            t.days+=(temp[i]-'0');
        }

        c+= t.name.size() + t.description.size() + 26 ;
        l.Insert( t ) ;
    }

}


/*void display (fstream& f){

   cout<<load(f);
}*/

void addtask (fstream& f , List<data> l){

    data d1;
    cin>>d1;
    l.Insert(d1);
    f<<d1.name<<'\n'<<d1.description<<'\n'<<d1.priority<<'\n'<<d1.time.day<<' '<<d1.time.month<<' '<<d1.time.year<<'\n'<<d1.days<<'\n';

}

/*void save (fstream& f , List<data> l){

  cout<<"These are your tasks: "<<endl;
  cout<<"Do you want to add any further tasks ? (Yes/No)"<<endl;
  string choice;
  cin>>choice;
  if (choice=="Yes" || choice=="yes"){
          addtask(f,l);
          cout<<endl<<"                     Thank You!"<<endl;
      }

  if (choice=="No" || choice=="no"){

      cout<<endl<<"                     Thank You!"<<endl;
  }
}*/

void offload( fstream& f , List<data> l ){

    task<data> *t = l.get_head() ;

    data d ;

    f.clear();
    f.seekp(0,ios::beg);

    while( t!=NULL ){

        d = t->getd() ;

        f<<d.name<<'\n'<<d.description<<'\n'<<d.priority<<'\n'<<d.time.day<<' '<<d.time.month<<' '<<d.time.year<<'\n'<<d.days<<'\n';

        t = t->getNext() ;
    }
}

int main()
{
    List<data> l;

    fstream file;
    file.open("MyTask.txt");

    load(file,l) ;

    cout<<"Hey there! , this your To-Do-List Program " <<endl;

    int x ;
    data d , temp ;

    bool k = true ;

    while( k ){

        int choice ;

        cout << "1)Add\n2)Remove\n3)Sort\n4)Merge\n5)Display\n6)Exit" << endl ;

        cin >> choice ;

        switch( choice ){

        case 1:
        {
            cout << "1)Add to Head\n2)Add to Tail\n3)Insert" << endl ;

            cin >> x ;
            cin >> d ;
            switch( x ){

            case 1:
                l.AddToHead(d) ;
                break ;

            case 2:
                l.AddtoTail(d) ;
                break ;

            case 3:
                l.Insert(d) ;
                break ;

            default :
                    cout << "Invalid input!!!" << endl ;
                    break ;
            }
            break ;
        }
            case 2:
            {
                cout << "1)Remove from Head\n2)Remove from Tail\n3)Remove from Index\n4)Remove Item\n5)Remove with Predicate" << endl ;
                cin >> x ;

                switch( x ){

                    case 1:
                        temp = l.removeHead() ;
                        break ;

                    case 2:
                        temp = l.removeTail() ;
                        break ;

                    case 3:
                        int index ;
                        cout << "Enter the Index :" ; cin >> index ;
                        temp = l.removeFromIndex( index ) ;
                        break ;

                    case 4:
                        cout << "Enter the Task:" << endl ;
                        cin >> d ;
                        l.removeItem(d) ;
                        break ;

                    case 5:
                        l.removeWithPredicate( &List<data>::isPassed ) ;
                        break ;

                    default :
                        cout << "Invalid input" << endl ;
                        break ;
                }
                break ;
            }
            case 3:
            {
              int y , z ;
              cout << "1)Ascending\n2)Descending" << endl ;
              cin >> y ;
              cout << "Order by:\n1)Name\n2)Priority\n3)Duration\n4)Date" << endl ;
              cin >> z ;

              switch( z ){

                case 1:
                    l.mergeSort(&List<data>::orderByName,y) ;
                    break ;

                case 2:
                    l.mergeSort(&List<data>::orderByPriority,y) ;
                    break ;

                case 3:
                    l.mergeSort(&List<data>::orderByDuration,y) ;
                    break ;

                case 4:
                    l.mergeSort(&List<data>::orderByDate,y) ;
                    break ;

                default :
                    cout << "Invalid input!!!" << endl ;
                    break ;
              }
              break ;
            }
        case 4:
            {
            int n ;
            List<data> l2 ;
            List<data> l3 ;
            cout << "Enter the number of Tasks in the new List:" << endl ;
            cin >> n ;
            data d1 ;
            for( int j=0 ; j<n ; j++ ){

                cin >> d1 ;
                l2.Insert(d1) ;
            }

            l3 = l.Merge(l2) ;

            cout << "The new Merged List: " << endl ;
            cout << l3 ;
            break ;
            }
        case 5:
        {
            cout<<l;
            break;
        }
        case 6:
        {
            k = false ;
            break ;
        }

        default :
        {
            cout << "Invalid input!!!" << endl ;
            break ;
        }

        }
    }

    file.close();

    return 0;
}
