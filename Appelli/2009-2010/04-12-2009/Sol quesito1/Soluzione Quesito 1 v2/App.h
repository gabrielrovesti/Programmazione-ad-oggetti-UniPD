#ifndef APP_H
#define APP_H
class App{
private:
    double memMB;
    bool internet;
public:
    App(double,bool);
    double GetMem() const;
    bool GetInternet() const;
    virtual ~App();
};
#endif