#define MAX_CALLBACKS 10

typedef struct tc {
  void (*callbackPtr)(void);
  unsigned int period;
  unsigned int count;
} TCallbackInfo;

class CTimer{
  protected:
    TCallbackInfo _callbacks[MAX_CALLBACKS];
    int _callbackCount;

    friend void handleInterrupt();

  public:
    CTimer();
    
    int attachCallback(void (*callback)(void), unsigned int period);
    int changePeriod(int callbackNumber, unsigned int newPeriod);
    void startTimer();
    void stopTimer();


    ~CTimer();
};
