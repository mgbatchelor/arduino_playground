class Brain {

  public:
    Brain();
    void record(int sensorValue);
    int average();
    int bufferSize;

  private:
    int history [50];
    int pointer;
    
    int pop();
    void push(int value);
    int sum();
    
};

