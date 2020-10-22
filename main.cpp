/**
 * Observer Design Pattern
 *
 * Intent: Lets you define a subscription mechanism to notify multiple objects
 * about any events that happen to the object they're observing.
 *
 * Note that there's a lot of different terms with similar meaning associated
 * with this pattern. Just remember that the Subject is also called the
 * Publisher and the Observer is often called the Subscriber and vice versa.
 * Also the verbs "observe", "listen" or "track" usually mean the same thing.
 */

#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <streambuf>
# include <ctime>
#include <fstream>

class IObserver {
    std::string str_;
 public:
    IObserver(std::string s):str_(s){};
    std::string get(){return str_;}
    virtual ~IObserver() = default;
    virtual void Execute(std::ofstream& ){};
};

class Observer : public IObserver {
 public:
    Observer(std::string s):IObserver(s){};
    virtual ~Observer() {
    }
    void Execute(std::ofstream& File) override {
      std::cout<<get()<<" ";
        File<<get()<<" ";
    }
};
class ISubject {
 public:
  virtual ~ISubject(){};
  virtual void Attach(IObserver *observer) = 0;
  virtual void Detach(IObserver *observer) = 0;
  virtual void Notify(std::ofstream&) = 0;
};

/**
 * The Subject owns some important state and notifies observers when the state
 * changes.
 */

class Subject : public ISubject {
    unsigned _size;
    public:
    virtual ~Subject() override{
        std::cout << "Goodbye, I was the Subject.\n";
    }
    Subject(unsigned size):_size(size){
        read();
    };
  /**
   * The subscription management methods.
   */
    void Attach(IObserver *observer) override {
        list_observer_.push_back(observer);
    }
    void Detach(IObserver *observer) override {
        list_observer_.remove(observer);
    }
    void Notify(std::ofstream& f) override {
        std::list<IObserver *>::iterator iterator = list_observer_.begin();
        std::cout<<"bulk: ";
        f<<"bulk: ";
        while (iterator != list_observer_.end()) {
            (*iterator)->Execute(f);
            ++iterator;
        }
        std::cout<<std::endl;
        f<<std::endl;
        list_observer_.clear();
    }
//
//    void Publish() {
//        if(list_observer_.size() > _size)
//            Notify();
//    }
    
   const std::string getFileName() const{
       std::time_t result = std::time(nullptr);
       std::stringstream ss;
       ss << result;
       std::string name = ss.str();
       return name;
    }
//    friend std::ostream& operator<<(std::ostream& os, const std::string& str){
//        os << str<< ",";
////        File<<str;
//        return os;
//    }
//    void print(std::string str){
//        static bool startFlag = true;
//        std::string end = "\n";
//        if(startFlag)
//            startFlag = false;
//        else if(str.compare(0, 4, "   b")){
//            std::cout<<end; File<<end;}
//        std::cout<<str; File<<str;
//    }
  void read() {
      std::string line;
      unsigned flag = 0;
      std::string fileName = getFileName();
      File.open(fileName);
      while(!std::cin.eof()){
          std::getline(std::cin, line);
          if (!line.compare("{")) {
              if(list_observer_.size() && !flag){
                  Notify(File);
              }
              ++flag;
              continue;
          }
          else if(!line.compare("}")){
              if(flag) --flag;
              if(!flag) Notify(File);
              continue;
          }
          
          Attach(new Observer(line));
          if(list_observer_.size() >= _size && !flag)
            Notify(File);
      }
      if(!flag &&list_observer_.size())
          Notify(File);
      list_observer_.clear();
      File.close();
  }

 private:
  std::list<IObserver *> list_observer_;
  std::ofstream File;

};

int main() {
 
//    std::istringstream iss("\
//{\n\
//cmd1\n\
//cmd2\n\
//{\n\
//cmd3\n\
//cmd4\n\
//}\n\
//cmd5\n\
//cmd6\n\
//}");
//    std::istringstream iss("\
//cmd1\n\
//cmd2\n\
//{\n\
//cmd3\n\
//cmd4\n\
//cmd5\n\
//cmd6\n\
//cmd7\n\
//}");
//    std::istringstream iss("\
//cmd2\n\
//cmd3\n\
//{\n\
//cmd4\n\
//cmd5\n\
//cmd6\n\
//cmd7");
//    std::streambuf * buf = std::cin.rdbuf(iss.rdbuf());
//    std::cin.rdbuf(iss.rdbuf());
    Subject *subject = new Subject(3);
    delete subject;
  return 0;
}
